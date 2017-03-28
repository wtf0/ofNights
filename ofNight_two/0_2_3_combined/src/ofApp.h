#pragma once

#include "ofMain.h"
#include "particle.h"
#include "vectorField.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        int width;
        int height;

        float SLnoise;
    
        vectorField vecField;
        ofVec2f vecSteps;
    
        vector <particle> parts;
    
        float repulsionDist;
        float repulsionFrc;
    
};
