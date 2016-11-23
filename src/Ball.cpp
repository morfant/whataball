//
//  ball.cpp
//  whataball
//
//  Created by gangil Yi on 11/23/16.
//
//

// ----Headers----
#include "Ball.h"


// ----Birth & Death----

/*
 
 // in your header files
 vector <shared_ptr<ofxBox2dCircle> > circles;
 
 // now add a circle to the vector
 shared_ptr<ofxBox2dCircle> circle = shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle);
 
 // to grab the pointer you use the get() function of shared_ptr (std::shared_ptr)
 circle.get()->setPhysics(3.0, 0.53, 0.1);
 circle.get()->setup(box2d.getWorld(), 100, 100, 10);
 circles.push_back(circle);

 */

Ball::Ball(float x, float y, float r, bool isSuper)
{
    
    radius[0] = 20;
    radius[1] = 17;
    radius[2] = 13;
    radius[3] = 10;
    radius[4] = 5;
    
    superBall = isSuper;
//    isFinished = false;
   
    curRad = radius[0];
    posX = x;
    posY = y - curRad;
    oldPosX = posX;
    oldPosY = posY;
    
//    rectArr[i] = ofRectangle(posX, (posY - radius), rectSide, rectSide);
    
    posArr.push_back( ofPoint(posX, posY) );
    stringArr.push_back("000");
    
    
    
    
//    circles.push_back(shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle));
//    circles.back().get()->setPhysics(3.0, 0.53, 0.1);
//    circles.back().get()->setup(box2d.getWorld(), posX, posY, radius);
//   
}

Ball::~Ball()
{
    
}

// getter & setter
float
Ball::getX()
{
    return posX;
}

float
Ball::getY()
{
    return posY;
}

bool
Ball::getIsSuper()
{
    return superBall;
}


b2World*
Ball::getWorld()
{
    return mWorld;
}

b2Body*
Ball::getBody()
{
    return mBody;
    
}

void
Ball::setPos(ofPoint pos)
{
    posX = pos.x;
    posY = pos.y;
}


void
Ball::setRadius(float r)
{
}

void
Ball::addText(string text){
   
    /*
     <Get next position on circle>
     
     float x = r*cos(t) + h;
     float y = r*sin(t) + k;
    */
    
//    cout << "addText()" << endl;
    
    if ((DEG_MUL*curIdx) >= 360) {
        curIdx = 0;
        
        if (radIdx < (RAD_NUM - 1)) {
//            oldPosY = oldPosY + (2*(radius[radIdx] - radius[radIdx+1]));
            oldPosY = oldPosY + 20;
        }
        
        radIdx++;
        
        if (radIdx > RAD_NUM){
            radIdx = 0;
        }
        
        cout << "radIdx: " << radIdx << endl;
        curRad = radius[radIdx];

    }
    
    float the = ofDegToRad(DEG_MUL*curIdx);
    posX = curRad*cos(the) + oldPosX;
    posY = curRad*sin(the) + oldPosY;
    
    cout << "new X/Y: " << posX << " / " << posY << endl;
    posArr.push_back(ofPoint(posX, posY));
    
    stringArr.push_back(text);
//    for (int i = 0; i < stringArr.size(); i++){
//        cout << stringArr.at(i) << endl;
//    }
    
    curIdx++;
    
    oldPosX = posX;
    oldPosY = posY;
    
}


void
Ball::addRect(){
  
}

void
Ball::renderAtBodyPosition()
{
    b2Vec2 pos = mBody->GetPosition();
    
    ofPushStyle();
    ofSetColor(250, 250, 0); // Set ball color
    ofFill();
    ofPushMatrix();
    ofTranslate(_toPixelX(pos.x), _toPixelY(pos.y));
//    ofEllipse(0, 0, radius, radius);
    ofPopMatrix();
    ofPopStyle();
}


// Update & draw
void
Ball::update()
{
    
}


void
Ball::draw()
{
    
    /*
     string info = "";
     info += "Press [c] for circles\n";
     info += "Press [b] for blocks\n";
     info += "Total Bodies: "+ofToString(box2d.getBodyCount())+"\n";
     info += "Total Joints: "+ofToString(box2d.getJointCount())+"\n\n";
     info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n";
     ofSetHexColor(0x444342);
     ofDrawBitmapString(info, 30, 30);
    */
    
    ofFill();
    ofSetHexColor(0xf6c738);
//    cout << "arr size: " << stringArr.size() << endl;
    
//    for(vector<string>::iterator it = stringArr.begin();
//        it != stringArr.end(); it++) {
//
//        ofSetHexColor(0x444342);
//        cout << stringArr[i] << endl;
//        cout << posArr[i].x << endl;
//        cout << posArr[i].y << endl;
//        
//        ofDrawBitmapString(stringArr[i], posArr[i].x, posArr[i].y);
//
//    }
//
//    if (stringArr.size() > 0) {
        for (int i = 0; i < stringArr.size(); i++){
//            cout << "in a loop" << endl;
            ofSetHexColor(0x444342);
    //        cout << stringArr[i] << endl;
    //        cout << posArr[i].x << endl;
    //        cout << posArr[i].y << endl;
            
            ofDrawBitmapString(stringArr[i], posArr[i].x, posArr[i].y);
        }
//    }
//    circles[i].get()->draw();
    
    
    // draw the ground
//    box2d.drawGround();
    
    
    
}
