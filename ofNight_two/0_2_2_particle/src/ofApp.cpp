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
    
    int numParts = 10000;
    repulsionDist = 15.0;
    repulsionFrc = 0.8;
    
    for(int i = 0; i < numParts; i++){
        particle tmpPart;
        tmpPart.setPosition(ofRandom(0, width), ofRandom(0, height));
        tmpPart.setVelocity(ofRandom(-1, 1), ofRandom(-1,1));
        tmpPart.setRadius(2);
        tmpPart.setFriction(0.9);
        parts.push_back(tmpPart);
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){

    sort(parts.begin(), parts.end(), xSort);
    float ppDist;
    float frcPct;
    ofVec2f repulsionAmnt;
    ofVec2f deltaVec;
    
    float repulsionDistSqrd = repulsionDist*repulsionDist;
    float ppDistSquared;
    
    for(int i = 0; i < parts.size(); i++){
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
    
    for(int i = 0; i < parts.size(); i++){
        parts[i].draw();
    }
    
    ofDrawBitmapString(ofToString(ofGetFrameRate()), 10, 10);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
