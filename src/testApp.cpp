#include "testApp.h"

void testApp::setup(){
    
    // 画面の基本設定
    ofBackground(0,0,0);
    ofEnableSmoothing();
    
    // 画面の混色の設定を加算合成にする
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    // 画像データの読込み
    myImage.loadImage("ryota_10.jpg");
    
    // 画像の描画位置を設定
    imgWidth  = myImage.width;
    imgHeight = myImage.height;
    
    // 画像データのビットマップ情報を配列に格納
    pixels = myImage.getPixels();
    // 初回のピクセルサイズ
    prevRadius = arduino.GetBallRadius();
    
    // ピクセル配列の初期化
    setPixels();
    
}

void testApp::update(){
    arduino.updateArduino();
    handleSequence();
    
    // ピクセルを拡大縮小を制御
    for (int i = 0; i < pixelArray.size(); i++) {
        // 拡大
        if (pixelArray[i].isUp) {
            pixelArray[i].radius++;
            if (pixelArray[i].radius > offset) pixelArray[i].isUp = false;
        }
        // 縮小
        else {
            pixelArray[i].radius--;
            if (pixelArray[i].radius < 2) pixelArray[i].isUp = true;
        }
    }
}

void testApp::draw(){
    
    // 色の設定
    ofSetColor(255, 255, 255);
    
    // 画像をintervalピクセル間隔でスキャン
    for (int i = 0; i < imgWidth; i+=interval){
        
        for (int j = 0; j < imgHeight; j+=interval){
            
            // ピクセルのRGBの値を取得
            int valueR = pixels[j*3 * imgWidth + i*3];
            int valueG = pixels[j*3 * imgWidth + i*3+1];
            int valueB = pixels[j*3 * imgWidth + i*3+2];
            
            // 取得したRGB値をもとに、円を描画
            ofSetColor(valueR, valueG, valueB, 20);
            ofCircle(drawX+i, drawY+j, pixelArray[imgWidth*i+j].radius);
            ofSetColor(valueR, valueG, valueB, 20);
            ofCircle(drawX+i, drawY+j, pixelArray[imgWidth*i+j].radius);
            ofSetColor(valueR, valueG, valueB, 20);
            ofCircle(drawX+i, drawY+j, pixelArray[imgWidth*i+j].radius);
        }
    }
    
}

// センサの値に変更があったらピクセルの更新を行う
void testApp::handleSequence(){
    if (!(arduino.GetBallRadius() > prevRadius - 10 && arduino.GetBallRadius() < prevRadius + 10)) {
        offset = arduino.GetBallRadius()/50;
        setPixels();
        prevRadius = arduino.GetBallRadius();
    }
}

// ピクセルの設定
void testApp::setPixels(){
    
    pixelArray.clear();
    
    for (int i = 0; i < myImage.width * myImage.height; i++) {
        Ball ball;
        ball.radius = ofRandom(1, offset);
        int _num = ofRandom(0, 2);
        if (_num == 0) {
            ball.isUp = false;
        }
        pixelArray.push_back(ball);
    }
    
}

void testApp::keyPressed(int key){
    //「x」キーを押すと、画面をキャプチャーする
    if(key == 'x'){
        // 位置とサイズを指定して、画面をキャプチャー
        grabbedImage.grabScreen(drawX, drawY, imgWidth, imgHeight);
        // キャプチャーした画像データを「grabbedImage.png」で保存
        grabbedImage.saveImage("grabbedImage.png");
    }
    // スペースキーでピクセルのサイズを変更
    if (key == ' ') {
        offset = ofRandom(1, maxCount);
        setPixels();
    }
}

void testApp::keyReleased(int key){
}

void testApp::mouseMoved(int x, int y){
}

void testApp::mouseDragged(int x, int y, int button){
}

void testApp::mousePressed(int x, int y, int button){
}

void testApp::mouseReleased(int x, int y, int button){
}

void testApp::windowResized(int w, int h){
    drawX = (w - imgWidth) / 2;
    drawY = (h - imgHeight) / 2;
}