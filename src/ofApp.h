#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxBox2d.h"
#include "Ball.h"

// listen on port 12345
#define PORT 8000
#define NUM_MSG_STRINGS 20
#define CH_NUM 8
#define BALL_NUM 3

class ofApp : public ofBaseApp {
public:
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    /* OFXOSC */
    ofTrueTypeFont font;
    ofxOscReceiver receiver;
    
    int current_msg_string;
    string msg_strings[NUM_MSG_STRINGS];
    float timers[NUM_MSG_STRINGS];
    float oscRecvVal[CH_NUM];
    string oscAddrs[CH_NUM];
    
    int mouseX, mouseY;
    string mouseButtonState;
    
    ofImage receivedImage;
    
    
    
    
    /* OFXBOX2D */
   	ofxBox2d                               box2d;   // the box2d world
	vector   <shared_ptr<ofxBox2dCircle> > circles; // default box2d circles
	vector   <shared_ptr<ofxBox2dRect> >   boxes;   // defalut box2d rects
    
    
    /* BALL */
//    Ball* balls[BALL_NUM];
    vector<Ball*> balls;
};
