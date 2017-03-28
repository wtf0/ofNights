#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    usingCamera = true;
    
    if(usingCamera == false){
        vidPlayer.load(ofToDataPath("fingers.mov"));
        vidPlayer.setLoopState(OF_LOOP_NORMAL);
        
        videoTexture.allocate(vidPlayer.getWidth(), vidPlayer.getHeight(), GL_RGBA);
        grayPixels.allocate(vidPlayer.getWidth(), vidPlayer.getHeight(), OF_IMAGE_GRAYSCALE);
        backgroundPixels.allocate(vidPlayer.getWidth(), vidPlayer.getHeight(), OF_IMAGE_GRAYSCALE);
        subtracted.allocate(vidPlayer.getWidth(), vidPlayer.getHeight(), OF_IMAGE_GRAYSCALE);
        cvSubtracted.allocate(vidPlayer.getWidth(), vidPlayer.getHeight());
        vidPlayer.play();
        capBackground = false;
    }else{
        camWidth = 640;
        camHeight = 480;
        
        vector<ofVideoDevice> devices = camera.listDevices();
        for(int i = 0; i < devices.size(); i++){
            if(devices[i].bAvailable){
                cout << devices[i].id << " " << devices[i].deviceName << endl;
            }
        }
        camera.setDeviceID(0);
        camera.initGrabber(camWidth, camHeight);
        videoTexture.allocate(camWidth, camHeight, OF_PIXELS_RGBA);
        grayPixels.allocate(camWidth, camHeight, OF_IMAGE_GRAYSCALE);
        backgroundPixels.allocate(camWidth, camHeight, OF_IMAGE_GRAYSCALE);
        subtracted.allocate(camWidth, camHeight, OF_IMAGE_GRAYSCALE);
        cvSubtracted.allocate(camWidth, camHeight);
        capBackground = true;
    }
    

}

//--------------------------------------------------------------
void ofApp::update(){
    
    if(vidPlayer.getCurrentFrame() == 10){
        capBackground = true;
    }
    
    int videoWidth;
    int videoHeight;
    if(usingCamera == false) {
        videoWidth = vidPlayer.getWidth();
        videoHeight = vidPlayer.getHeight();
        vidPlayer.update();
        
        pixels = vidPlayer.getPixels();

    }else{
        videoWidth = camWidth;
        videoHeight = camHeight;
        camera.update();
        pixels = camera.getPixels();
    }
    
    
    videoTexture.loadData(pixels);
    
    for(int y = 0; y < videoHeight; y ++){
        for(int x = 0; x < videoWidth; x++){
            ofColor tmpColour = pixels.getColor(x,y);
            ofColor gray;
            gray.set((tmpColour.r *0.3) + (tmpColour.g * 0.59) + (tmpColour.b * 0.11));
            grayPixels.setColor(x,y, gray);
        }
    }
    
    if(capBackground == true){
        
        backgroundPixels = grayPixels;
        capBackground = false;
        
    }
    
    int numChannels = grayPixels.getNumChannels();
    for(int i = 0; i < grayPixels.size(); i++){
        
        int grayDiff;
        if(grayPixels[i*numChannels] > backgroundPixels[i*numChannels]){
            grayDiff = grayPixels[i*numChannels] - backgroundPixels[i*numChannels];
        }else if(backgroundPixels[i*numChannels] > grayPixels[i*numChannels]){
            grayDiff = backgroundPixels[i*numChannels] - grayPixels[i*numChannels];
        }
        int threshold = 40;
        
        if(grayDiff > threshold){
            subtracted[i] = 255;
        }else{
            subtracted[i] = 0;
        }
        
    }
    
    cvSubtracted.setFromPixels(subtracted);
    contourFinder.findContours(cvSubtracted, 30, (videoWidth * videoHeight)*0.25, 15, true);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255,255,255);
    videoTexture.draw(10, 10);
    ofTexture grayTexture;
    grayTexture.loadData(grayPixels);
    grayTexture.draw(videoTexture.getWidth() + 10, 10);
    
    ofTexture bgTexture;
    bgTexture.loadData(backgroundPixels);
    bgTexture.draw(10, videoTexture.getHeight() + 10);
    
    ofTexture subTexture;
    subTexture.loadData(subtracted);
    subTexture.draw(videoTexture.getWidth() + 10, videoTexture.getHeight() + 10);
    
    for(int i = 0; i < contourFinder.nBlobs; i++){
        
        contourFinder.blobs[i].draw(videoTexture.getWidth() + 10, videoTexture.getHeight() + 10);
        
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if(key == 'c'){
        capBackground = true;
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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
