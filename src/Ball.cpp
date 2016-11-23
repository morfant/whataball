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



Ball::Ball(b2World* aWorld, float x, float y, bool isSuper)
{
    
    superBall = isSuper;
    
    // Set Userdata
    if(superBall){
        ballUserData = SUPER_BALL;
    }else{
        ballUserData = BALL;
    }
    
    mWorld = aWorld;
    posX = x;
    posY = y;
    
    radius = 30.f;
    
    b2BodyDef myBodyDef;
    
    if (superBall) {
        myBodyDef.type = b2_staticBody;
    }else{
        myBodyDef.type = b2_dynamicBody;
    }
    
    myBodyDef.position.Set(_toWorldX(posX), _toWorldY(posY));
    mBody = mWorld -> CreateBody(&myBodyDef);
    
    mBody->SetUserData((void*)ballUserData);
    //    mBody->SetUserData(this);
    
    
    b2CircleShape myCircleShape;
    myCircleShape.m_p.Set(0, 0);
    myCircleShape.m_radius = _toWorldScale(radius/2.f);
    
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &myCircleShape;
    
    if (superBall){
        
        myFixtureDef.density = 100.f;
        myFixtureDef.restitution = 100.f;
        myFixtureDef.friction = 1.f;
        
    }else{
        
        myFixtureDef.density = 0.1f;
        myFixtureDef.restitution = 0.1f;
        myFixtureDef.friction = 0.7f;
    }
    
    myFixtureDef.filter.categoryBits = BALL_CATE_BIT;
    myFixtureDef.filter.maskBits = BALL_MASK_BIT;
    
    mBody->CreateFixture(&myFixtureDef);
    
    
}

Ball::~Ball()
{
    mWorld->DestroyBody(mBody);
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
Ball::setX(float _posX)
{
    
}

void
Ball::setY(float _posY)
{
    
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
    ofEllipse(0, 0, radius, radius);
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
    
    
    
}
