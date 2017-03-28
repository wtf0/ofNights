#include "particle.h"

particle::particle(){
    
    friction = 1.0;
    
    radius = 0;
    
}

void particle::setFriction(float frictionAmnt){
    friction = frictionAmnt;
}
void particle::setPosition(float x, float y){
    setPosition(ofVec2f(x, y));
}
void particle::setPosition(ofVec2f position){
    pos = position;
}
void particle::setVelocity(float x, float y){
    setVelocity(ofVec2f(x,y));
}
void particle::setVelocity(ofVec2f velocity){
    vel = velocity;
}
void particle::setRadius(float _radius){
    radius = _radius;
}
void particle::update(){
    vel *= friction;
    pos += vel;
}
void particle::addForce(float x, float y){
    addForce(ofVec2f(x, y));
}
void particle::addForce(ofVec2f force){
    vel+= force;
}
void particle::draw(){
    ofDrawCircle(pos.x, pos.y, radius);
}