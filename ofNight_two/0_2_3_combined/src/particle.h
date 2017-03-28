#pragma once

#include "ofMain.h"

class particle{
    
public:
    
    particle();
    void setFriction(float frictionAmnt);
    void setVelocity(float x, float y);
    void setVelocity(ofVec2f velocity);
    
    void setPosition(float x, float y);
    void setPosition(ofVec2f position);
    
    void setRadius(float _radius);
    
    void update();
    
    void addForce(float x, float y);
    void addForce(ofVec2f force);
    
    void draw();
    
    ofPoint pos;
    ofVec2f vel;
    
    float friction;
    float radius;
    
};