#pragma once

#include "ofMain.h"

class vectorField{
    
public:
    
    vectorField();
    void setup(int _fieldW, int _fieldH, float _scaleW, float _scaleH);
    ofVec2f * getField();
    void set(float x, float y);
    void set(ofPoint point);
    void clear();
    void limit(float value);
    void randomField(float scale);
    void blurField(float pct);
    void setIntoField(float x, float y, ofVec2f vector);
    void addIntoField(float x, float y, ofVec2f vector, float strength);
    ofVec2f getFromField(float x, float y);
    
    void draw(float x, float y, float w, float h, float scaleVector);
    void drawGrid(float x, float y, float w, float h);
    
    int fieldSize;
    int fieldW;
    int fieldH;
    float scaleW;
    float scaleH;
    ofVec2f * field;
    float sqrtOf2;
    
    
    
    
    
};