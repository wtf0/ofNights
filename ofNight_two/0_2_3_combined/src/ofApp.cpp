#include "ofApp.h"

static bool xSort(particle pA, particle pB){
    if(pA.pos.x < pB.pos.x){
        return true;
    }
    return false;
}

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0);
    
    width = ofGetWidth();
    height = ofGetHeight();
    
    vecSteps.x = width*0.1;
    vecSteps.y = height*0.1;
    
    vecField.setup(vecSteps.x, vecSteps.y, width, height);
    vecField.randomField(1);
    
    int numParticles = 10000;
    repulsionDist = 10.0;
    repulsionFrc = 1;
    
    for(int i = 0; i < numParticles; i++){
        particle tmpPart;
        tmpPart.setPosition(ofRandom(width*0.3,width*0.7), ofRandom(height*0.3, height*0.7));
        tmpPart.setVelocity(ofRandom(-3, 3), ofRandom(-3, 3));
        tmpPart.setRadius(3);
        tmpPart.setFriction(0.6);
        parts.push_back(tmpPart);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    vecField.blurField(0.2);
    
    for(int y = 0; y < height; y+=10){
        for(int x = 0; x < width; x +=10){
            float xPct = 0.01 * (float)x;
            float yPct = 0.01 * (float)y;
            ofVec2f dir;
            dir.x = ofSignedNoise(xPct, yPct, ofGetElapsedTimef());
            dir.y = ofSignedNoise(yPct, xPct, ofGetElapsedTimef());
            dir += vecField.getFromField(x, y);
            float strength = ofRandomf();
            if(strength < 0.5) strength = 0.5;
            vecField.addIntoField(x, y, dir, strength);
        }
    }
    
    sort(parts.begin(), parts.end(), xSort);
    float ppDist;
    float frcPct;
    ofVec2f repulsionAmnt;
    ofVec2f deltaVec;
    
    float repulsionDistSqrd = repulsionDist*repulsionDist;
    float ppDistSquared;
    
    for(int i = 0; i < parts.size(); i++){
        
        ofVec2f vec = vecField.getFromField(parts[i].pos.x, parts[i].pos.y);
        parts[i].vel += vec;
        
        for(int j = i; j >= 0; j++){
            if(j == i){
                continue;
            }
            if(fabs(parts[j].pos.x - parts[i].pos.x) > repulsionDist){
                break;
            }
            if(fabs(parts[j].pos.y - parts[i].pos.y) > repulsionDist){
                continue;
            }
            deltaVec = parts[j].pos - parts[i].pos;
            ppDistSquared = deltaVec.lengthSquared();
            if(ppDistSquared <= repulsionDistSqrd){
                ppDist = sqrt(ppDistSquared);
                frcPct = 1.0 - (ppDist/repulsionDist);
                repulsionAmnt = deltaVec.normalize() * frcPct * repulsionFrc;
                
                parts[i].vel -= repulsionAmnt;
                parts[j].vel += repulsionAmnt;
            }
        }
        /*
        ofVec2f mousePt(mouseX, mouseY);
        ofVec2f distVec = mousePt - parts[i].pos;
        float straightDist = distVec.length();
        
        if(straightDist < 100){
            float pct = straightDist/100.0;
            ofVec2f repulVec = -distVec.normalize();
            float repulsionStrength = (1.0-pct)*1.4;
            
            repulVec *= repulsionStrength;
            parts[i].vel += repulVec;
        }
         */
        if(parts[i].pos.x + parts[i].radius > width){
            parts[i].pos.x = width - parts[i].radius;
            parts[i].vel.x *= -1;
        }
        if(parts[i].pos.x - parts[i].radius < 0){
            parts[i].pos.x = parts[i].radius;
            parts[i].vel.x *= -1;
        }
        if(parts[i].pos.y + parts[i].radius > height){
            parts[i].pos.y = height - parts[i].radius;
            parts[i].vel.y *= -1;
        }
        if(parts[i].pos.y - parts[i].radius < 0){
            parts[i].pos.y = 0;
            parts[i].vel.y *= -1;
        }
        parts[i].update();
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    //vecField.draw(0,0,width,height, 10);
    for(int i = 0; i < parts.size(); i++){
        parts[i].draw();
    }
    
    ofSetColor(255,0,0);
   // ofDrawBitmapString(ofToString(ofGetFrameRate()), 10, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == ' '){
        ofToggleFullscreen();
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
    
    width = ofGetWidth();
    height = ofGetHeight();
    
    vecSteps.x = width*0.1;
    vecSteps.y = height*0.1;
    
    vecField.setup(vecSteps.x, vecSteps.y, width, height);
    vecField.randomField(1);

    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
