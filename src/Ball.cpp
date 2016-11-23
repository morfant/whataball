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
Ball::Ball(ofxBox2d* w, float x, float y, float r, bool isSuper)
{
   
    mWorld = w;
    radius[0] = RAD;
    radius[1] = (RAD - 60);
    radius[2] = (RAD - 100);
    radius[3] = (RAD - 130);
    radius[4] = (RAD - 150);
    
    superBall = isSuper;
//    isFinished = false;
    
    cx = x;
    cy = y;
   
    curRad = radius[0]/2;
    posX = x;
    posY = y - curRad;
    oldPosX = posX;
    oldPosY = posY;
   
//    rectArr[i] = ofRectangle(posX, (posY - radius), rectSide, rectSide);
    
    posArr.push_back( ofPoint(posX, posY) );
    stringArr.push_back("000");
    
    /* make box2d body */
    mBody = new ofxBox2dCircle;
//    mBody->setPhysics(0.0, 0.53, 0.1); // Density 0 means, static body
    mBody->setPhysics(3.0, 0.53, 0.1); // Density 0 means, static body
    mBody->setup(mWorld->getWorld(), cx, cy, curRad);
    
    
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
//    return mWorld;
}

b2Body*
Ball::getBody()
{
//    return mBody;
    
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
     int newX = (int)(center.X + radius * Math.Cos(angle));
     int newY = (int)(center.Y + radius * Math.Sin(angle));
    */
    
//    cout << "addText()" << endl;
    
    if ((DEG_MUL*curIdx) >= 360) {
        curIdx = 0;
        
        if (radIdx < (RAD_NUM - 1)) {
//            oldPosY = oldPosY + (2*(radius[radIdx] - radius[radIdx+1]));
//            oldPosY = oldPosY + 20;
        }
        
        radIdx++;
        
        if (radIdx > RAD_NUM){
            radIdx = 0;
            curIdx = 0;
        }
        
        cout << "radIdx: " << radIdx << endl;
        curRad = radius[radIdx]/2;

    }
    
    float the = ofDegToRad(DEG_MUL*curIdx);

    posX = cx + curRad*cos(the);
    posY = cy + curRad*sin(the);
    
//    cout << "new X/Y: " << posX << " / " << posY << endl;
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
//    b2Vec2 pos = mBody->GetPosition();
//    
//    ofPushStyle();
//    ofSetColor(250, 250, 0); // Set ball color
//    ofFill();
//    ofPushMatrix();
//    ofTranslate(_toPixelX(pos.x), _toPixelY(pos.y));
////    ofEllipse(0, 0, radius, radius);
//    ofPopMatrix();
//    ofPopStyle();
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
    
//    for(int i=0; i<circles.size(); i++) {

//		ofFill();
//		ofSetHexColor(0xf6c738);

        mBody->draw();
//		circles[i].get()->draw();
        
//        ofFill();
//        ofSetHexColor(0xf6c738);

        ofPushMatrix();
//        ofPoint box2dPos = circles[i].get()->getB2DPosition();
        ofPoint box2dPos = mBody->getPosition();
//        ofPoint box2dPos = mBody->getB2DPosition();
        cout << "box2dpos X/Y: " << box2dPos.x << " / " << box2dPos.y << endl;
        
        ofTranslate(box2dPos.x, box2dPos.y);
    
        for (int i = 0; i < stringArr.size(); i++){
//            ofFill();
            ofSetHexColor(0x444342);
            ofDrawBitmapString(stringArr[i], posArr[i].x - cx, posArr[i].y - cy);
//            ofDrawCircle(posArr[i].x - cx, posArr[i].y - cy, 2);
        }
    
        ofPopMatrix();
     
//	}
	
   
    
    
}
