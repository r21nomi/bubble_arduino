#include "Arduino.h"

Arduino::Arduino() {
    ard.connect("/dev/cu.usbmodemfa131", 57600);
    // Arduinoとの接続を監視するリスナー
	ofAddListener(ard.EInitialized, this, &Arduino::setupArduino);
	bSetupArduino	= false;	// flag so we setup arduino when its ready, you don't need to touch this :)
}

void Arduino::setupArduino(const int & version){
	// remove listener because we don't need it anymore
	ofRemoveListener(ard.EInitialized, this, &Arduino::setupArduino);
    
    // it is now safe to send commands to the Arduino
    bSetupArduino = true;
    
    // print firmware name and version to the console
    ofLogNotice() << ard.getFirmwareName();
    ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();
    
    // set pin A0 to analog input
    ard.sendAnalogPinReporting(0, ARD_ANALOG);
    
    // set pin D11 as PWM (analog output)
	ard.sendDigitalPinMode(11, ARD_PWM);
	
    // Listen for changes on the digital and analog pins
    ofAddListener(ard.EDigitalPinChanged, this, &Arduino::digitalPinChanged);
    ofAddListener(ard.EAnalogPinChanged, this, &Arduino::analogPinChanged);
}

void Arduino::updateArduino(){
    
	// update the arduino, get any data or messages.
    // the call to ard.update() is required
	ard.update();
	
	// do not send anything until the arduino has been set up
	if (bSetupArduino) {
        // fade the led connected to pin D11
		ard.sendPwm(11, (int)(128 + 128 * sin(ofGetElapsedTimef())));   // pwm...
	}
    
}

void Arduino::digitalPinChanged(const int & pinNum){
    
}

void Arduino::analogPinChanged(const int & pinNum){
    ball_radius = ard.getAnalog(pinNum);
    ofLogNotice() << ard.getAnalog(pinNum);
}

float Arduino::GetBallRadius(){
    return ball_radius;
}