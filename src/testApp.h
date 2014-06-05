#pragma once

#include "ofMain.h"
#include "Arduino.h"

class Ball {
public:
    int radius = 1;
    bool isUp = true;
};

class testApp : public ofBaseApp {
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void setPixels();
    void handleSequence();
    
    ofImage myImage; //画像ファイルより読みこまれたイメージデータ
    ofImage grabbedImage; //画面をキャプチャーしたイメージデータ
    int offset     = 10;  //描画用ピクセルの半径の最大値
    int interval   = 5;  //ピクセルのスキャン間隔
    int maxCount   = 10;  //描画用ピクセルの半径を再設定する時の最大値
    int winWidth   = 0;
    int winHeight  = 0;
    int imgWidth   = 0;
    int imgHeight  = 0;
    int drawX      = 0;  //描画開始点_x
    int drawY      = 0;  //描画開始点_y
    int prevRadius = 0;
    unsigned char * pixels;  //画像のピクセルを格納する配列
    vector <Ball> pixelArray;  //画像のピクセルごとに円の大きさを格納する動的配列
    Arduino arduino;
    
};