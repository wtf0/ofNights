//vectorField class

#include "vectorField.h"

//--------------------------------------------------------------
vectorField::vectorField(){
    sqrtOf2 = sqrt(2.0);
}
//--------------------------------------------------------------
void vectorField::setup(int _fieldW, int _fieldH, float _scaleW, float _scaleH){
    
    fieldW = _fieldW;
    fieldH = _fieldH;
    scaleW = _scaleW;
    scaleH = _scaleH;
    
    fieldSize = fieldW * fieldH;
    
    field = new ofVec2f[fieldSize];
    
    clear();
    
}
//--------------------------------------------------------------
ofVec2f * vectorField::getField(){
    
    return field;
    
}
//--------------------------------------------------------------
void vectorField::clear(){
    for(int i = 0; i < fieldSize; i++){
        field[i].set(0,0);
    }
}
//--------------------------------------------------------------
void vectorField::set(float x, float y){
    
    for(int i = 0; i < fieldSize; i++){
        field[i].set(x,y);
    }
    
}
//--------------------------------------------------------------
void vectorField::limit(float value){
    for(int i = 0; i < fieldSize; i++){
        if(field[i].length() > value){
            field[i].normalize();
            field[i] *= value;
        }
    }
}
//--------------------------------------------------------------
void vectorField::randomField(float scale){
    for(int i = 0; i < fieldSize; i++){
        field[i].set(ofRandomf(), ofRandomf());
        field[i].normalize();
        field[i]*=scale;
    }
}
//--------------------------------------------------------------
void vectorField::blurField(float pct){
    
    int stride = 0;
    
    ofVec2f val;
    
    int ii, ss, ee, nn, ww, nw, ne, sw, se;
    
    for (int y = 1; y < fieldH-1; y++){
        
        stride = fieldW * y;
        
        for (int x = 1; x < fieldW-1; x++){
            
            val.set(0, 0);
            int num = 0;
            
            ii = stride + x;
            nn = ii - fieldW;
            ss = ii + fieldW;
            ee = ii + 1;
            ww = ii - 1;
            nw = nn + 1;
            ne = nn -1;
            sw = ss +1;
            se = ss -1;
            
            
            val = field[nn] + field[ss] + field[ee] + field[ww] + field[nw] + field[ne] + field[sw] + field[se];
            val *= 0.125;
            
            field[ii] = field[ii]*(1.0 - pct) + val*pct;
        }
    }
}
//--------------------------------------------------------------
void vectorField::setIntoField(float x, float y, ofVec2f vector){
    ofVec2f pos(x, y);
    
    if(scaleW != 0 && scaleH != 0){
        pos.x /= scaleW;
        pos.y /= scaleH;
    }
    pos.x = MIN(1, pos.x);
    pos.y = MIN(1, pos.y);
    pos.x = MAX(0, pos.x);
    pos.y = MAX(0, pos.y);
    
    pos.x *= (float)fieldW;
    pos.y *= (float)fieldH;
    
    ofVec2f p;
    ofVec2f v;
    
    ofVec2f add;
    p.set(pos.x, pos.y);
    v.set(vector.x, vector.y);
    
    int x1 = (int)p.x;
    int x2 = x1 + 1;
    
    int y1 = (int)p.y;
    int y2 = y1+1;
    
    y1 = MAX(0, y1);
    x1 = MAX(0, x1);
    
    
    for(int y = y1; y < y2; y++){
        if(y >= fieldH) break;
        for(int x = x1; x < x2; x++){
            if(x >= fieldW)break;
            
            float dist = sqrt( (x-p.x)*(x-p.x) + (y-p.y)*(y-p.y) ) / sqrtOf2;
            
            int index  = y * fieldW + x;
            add = v * (1.0 - dist) + field[index]*dist;
            field[index] = add;
            
        }
    }
}
//--------------------------------------------------------------
void vectorField::addIntoField(float x, float y, ofVec2f vector, float strength){
    
    ofVec2f pos(x, y);
    pos.x /= scaleW;
    pos.y /= scaleH;
    
    pos.x = MIN(1, pos.x);
    pos.y = MIN(1, pos.y);
    pos.x = MAX(0, pos.x);
    pos.y = MAX(0, pos.y);
    
    pos.x *= (float)fieldW;
    pos.y *= (float)fieldH;
    
    ofVec2f p;
    ofVec2f v;
    
    ofVec2f add;
    p.set(pos.x, pos.y);
    v.set(vector.x, vector.y);
    
    int x1 = (int)p.x;
    int x2 = x1 + 1;
    
    int y1 = (int)p.y;
    int y2 = y1 + 1;
    
    y1 = MAX(0, y1);
    x1 = MAX(0, x1);
    
    for(int y = y1; y < y2; y++){
        if(y >= fieldH) break;
        for(int x = x1; x < x2; x++){
            if(x >= fieldW)break;
            
            float dist = sqrt( (x-p.x)*(x-p.x) + (y-p.y)*(y-p.y) ) / sqrtOf2;
            
            int index  = y * fieldW + x;
            add = v * (1.0 - dist) + field[index]*dist;
            field[index] = add * strength + field[index] * (1.0 - strength);
            
        }
    }
}
//--------------------------------------------------------------
ofVec2f vectorField::getFromField(float x, float y){
    
    float xPos = x / scaleW;
    float yPos = y / scaleH;
    
    if(xPos < 0 || xPos > 1) return ofVec2f(0, 0);
    if(yPos < 0 || yPos > 1) return ofVec2f(0, 0);
    
    xPos *= (float)fieldW;
    yPos *= (float)fieldH;
    
    ofVec2f vel;
    vel.set(0, 0);
    
    int x1 = (int)xPos;
    int x2 = x1 + 1;
    
    int y1 = (int)yPos;
    int y2 = y1+1;
    
    float dist;
    float total = 0.0;
    
    for(int y = y1; y  <= y2; y++){
        if(y >= fieldH) break;
        for(int x = x1; x <= x2; x++){
            if(x >= fieldW)break;
            float dist = (sqrtOf2 - (sqrt( (x-xPos)*(x-xPos) + (y-yPos)*(y-yPos) ) ))/sqrtOf2;
            total += dist;
            int index  = y * fieldW + x;
            
            vel.x += field[index].x * dist*0.25;
            vel.y += field[index].y * dist*0.25;
            
        }
    }
    return vel;
    
}
//--------------------------------------------------------------
void vectorField::draw(float x, float y, float w, float h, float scaleVector){
    
    float wPct = w / (float)fieldW;
    float hPct = h / (float)fieldH;
    
    float tipX;
    float tipY;
    float vecX, vecY;
    
    float nor1X;
    float nor1Y;
    float nor2X;
    float nor2Y;
    
    for (int j = 0; j < fieldH; j++){
        
        float py = y + hPct * (float)j;
        
        for (int i = 0; i < fieldW; i++){
            
            int pos = j * fieldW + i;
            
            float px = x + wPct * (float)i;
            
            
            vecX = field[pos].x * scaleVector;
            vecY = field[pos].y * scaleVector;
            tipX = px + vecX;
            tipY = py + vecY;
            
            nor1X = -vecY;
            nor1Y = vecX;
            nor2X = vecY;
            nor2Y = -vecX;
            
            ofDrawLine(px, py, tipX, tipY);
            ofDrawLine(tipX, tipY, tipX+(nor2X * 0.5+ -vecX*0.5) , tipY+(nor2Y * 0.5 + -vecY*0.5) );
            ofDrawLine(tipX, tipY, tipX+(nor1X * 0.5+ -vecX*0.5) , tipY+(nor1Y * 0.5 + -vecY*0.5) );
            
        }
    }
}
//--------------------------------------------------------------
void vectorField::drawGrid(float x, float y, float w, float h){
    float wPct = 1.0/(float)fieldW;
    float hPct = 1.0/(float)fieldH;
    
    for (int j = 0; j < fieldH; j++){
        ofDrawLine( x, hPct * (float)j * h, x + w, hPct * (float)j * h);
    }
    for (int i = 0; i < fieldW; i++){
        ofDrawLine( wPct * (float)i * w, y,wPct * (float)i * w, y + h);
    }	
}

