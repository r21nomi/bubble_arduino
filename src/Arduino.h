#pragma once

#include "ofMain.h"
#include "ofEvents.h"

class Arduino {
private:
    void setupArduino(const int & version);
    void digitalPinChanged(const int & pinNum);
    void analogPinChanged(const int & pinNum);
    
public:
    Arduino();
    bool bSetupArduino;
    float ball_radius;
    ofArduino ard;
    
    void updateArduino();
    float GetBallRadius();
};