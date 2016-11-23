#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    /* BALL */
//    for (int i = 0; i < balls.size(); i++){
    for (int i = 0; i < BALL_NUM; i++){
        balls[i] = NULL;
    }
    
    /* OFXOSC */
    for (int i = 0; i < CH_NUM; i++){
        oscRecvVal[i] = 0;
        oscAddrs[i] = "/ch" + std::to_string(i);
//        cout << oscAddrs[i] << endl;
    }
    
	// listen on the given port
	cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup(PORT);
	current_msg_string = 0;

    
    /* OFXBOX2D */
	ofSetVerticalSync(true);
	ofBackgroundHex(0xfdefc2);
	ofSetLogLevel(OF_LOG_NOTICE);
	
	box2d.init();
	box2d.setGravity(0, 10);
	box2d.createBounds();
	box2d.setFPS(60.0);
	box2d.registerGrabbing();
    
	ofBackground(0, 0, 0);
}

//--------------------------------------------------------------
void ofApp::update(){

   
    /* OFXBOX2D */
	box2d.update();
    
    
    /* OFXOSC */
	// hide old messages
	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		if(timers[i] < ofGetElapsedTimef()){
			msg_strings[i] = "";
		}
	}
    
//    for (int i = 0; i < 8; i++){
//        oscRecvVal[i] = 0;
//    }
//
    
	// check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(m);
        
        /*
            ch1: Not using
            ch2, ch3: linear
            ch4, ch5: teum
            ch6, ch7, ch8: morogado (floppy, tape, tape)
        */
        
        for (int i = 0; i < CH_NUM; i++){
            if (m.getAddress() == oscAddrs[i]) {
                oscRecvVal[i] = m.getArgAsFloat(0);
                
                if (balls[i%CH_NUM] != NULL) {
//                    cout << "addText(): " << (i%CH_NUM) << endl;
                    balls[i%CH_NUM]->addText(std::to_string(oscRecvVal[i]));
                }
                
//                cout << oscAddrs[i] << "-" << i << "-" << oscRecvVal[i] << endl;
            } else {
                // unrecognized message: display on the bottom of the screen
                string msg_string;
                msg_string = m.getAddress();
                msg_string += ": ";
                for(int i = 0; i < m.getNumArgs(); i++){
                    // get the argument type
                    msg_string += m.getArgTypeName(i);
                    msg_string += ":";
                    // display the argument - make sure we get the right type
                    if(m.getArgType(i) == OFXOSC_TYPE_INT32){
                        msg_string += ofToString(m.getArgAsInt32(i));
                    }
                    else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
                        msg_string += ofToString(m.getArgAsFloat(i));
                    }
                    else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
                        msg_string += m.getArgAsString(i);
                    }
                    else{
                        msg_string += "unknown";
                    }
                }
                // add to the list of strings to display
                msg_strings[current_msg_string] = msg_string;
                timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
                current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
                // clear the next line
                msg_strings[current_msg_string] = "";
                           
                }
            }
//
//        if(m.getAddress() == "/ch1"){
//            
//		} else if(m.getAddress() == "/ch2"){
//			// both the arguments are int32's
//            oscRecvVal[1] = m.getArgAsFloat(1);
//            cout << "ch2 received" << endl;
//		} else if(m.getAddress() == "/ch3"){
//			mouseButtonState = m.getArgAsString(0);
//		} else if(m.getAddress() == "/ch4"){
//			// the single argument is a string
//			mouseButtonState = m.getArgAsString(0);
//		} else if(m.getAddress() == "/ch5"){
//			// the single argument is a string
//			mouseButtonState = m.getArgAsString(0);
//		} else if(m.getAddress() == "/ch6"){
//			// the single argument is a string
//			mouseButtonState = m.getArgAsString(0);
//		} else if(m.getAddress() == "/ch7"){
//			// the single argument is a string
//			mouseButtonState = m.getArgAsString(0);
//		} else if(m.getAddress() == "/ch8"){
//			// the single argument is a string
//			mouseButtonState = m.getArgAsString(0);
//		} else{
//			// unrecognized message: display on the bottom of the screen
//			string msg_string;
//			msg_string = m.getAddress();
//			msg_string += ": ";
//			for(int i = 0; i < m.getNumArgs(); i++){
//				// get the argument type
//				msg_string += m.getArgTypeName(i);
//				msg_string += ":";
//				// display the argument - make sure we get the right type
//				if(m.getArgType(i) == OFXOSC_TYPE_INT32){
//					msg_string += ofToString(m.getArgAsInt32(i));
//				}
//				else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
//					msg_string += ofToString(m.getArgAsFloat(i));
//				}
//				else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
//					msg_string += m.getArgAsString(i);
//				}
//				else{
//					msg_string += "unknown";
//				}
//			}
//			// add to the list of strings to display
//			msg_strings[current_msg_string] = msg_string;
//			timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
//			current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
//			// clear the next line
//			msg_strings[current_msg_string] = "";
//		}

	}
    
    /* BALL */
    for (int i = 0; i < BALL_NUM; i++){
        if (balls[i] != NULL) {
            balls[i]->update();
        }
    }
 
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    /* BALL */
//    for (vector<Ball*>::iterator it = balls.begin(); it != balls.end(); it++) {
//        (*it)->draw();
//    }
//
    for (int i = 0; i < BALL_NUM; i++){
//        cout << "balls size: " << balls.size() << endl;
        
        if (balls[i] != NULL) {
            balls[i]->draw();
        }
    }
 

//	for(int i=0; i<circles.size(); i++) {
//		ofFill();
//		ofSetHexColor(0xf6c738);
//		circles[i].get()->draw();
//	}
//	
//	for(int i=0; i<boxes.size(); i++) {
//		ofFill();
//		ofSetHexColor(0xBF2545);
//		boxes[i].get()->draw();
//	}
//
	// draw the ground
	box2d.drawGround();
	
	string info = "";
	info += "Press [c] for circles\n";
	info += "Press [b] for blocks\n";
	info += "Total Bodies: "+ofToString(box2d.getBodyCount())+"\n";
	info += "Total Joints: "+ofToString(box2d.getJointCount())+"\n\n";
	info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n";
	ofSetHexColor(0x444342);
	ofDrawBitmapString(info, 30, 30);
    
    /* OSC */
//	string buf;
//	buf = "listening for osc messages on port" + ofToString(PORT);
//	ofDrawBitmapString(buf, 10, 20);
//    
//    if(receivedImage.getWidth() > 0){
//        ofDrawBitmapString("Image:", 10, 160);
//        receivedImage.draw(10, 180);
//    }
//
//	// draw mouse state
//	buf = "mouse: " + ofToString(mouseX, 4) +  " " + ofToString(mouseY, 4);
//	ofDrawBitmapString(buf, 430, 20);
//	ofDrawBitmapString(mouseButtonState, 580, 20);
//
//	for(int i = 0; i < NUM_MSG_STRINGS; i++){
//		ofDrawBitmapString(msg_strings[i], 10, 40 + 15 * i);
//	}



}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    float mx = ofGetMouseX();
    float my = ofGetMouseY();
    
	if(key == 'c') {
		float r = ofRandom(4, 20);
		circles.push_back(shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle));
		circles.back().get()->setPhysics(3.0, 0.53, 0.1);

		circles.back().get()->setup(box2d.getWorld(), mx, my, r);
	}
	
	if(key == 'b') {
		float w = ofRandom(4, 20);
		float h = ofRandom(4, 20);
		boxes.push_back(shared_ptr<ofxBox2dRect>(new ofxBox2dRect));
		boxes.back().get()->setPhysics(3.0, 0.53, 0.1);
		boxes.back().get()->setup(box2d.getWorld(), mx, my, w, h);
	}
	
	if(key == 't') ofToggleFullscreen();
    
    
    if(key == '1'){
        balls[0] = new Ball(300, 100, RAD, false);
    } else if (key == '2') {
        balls[1] = new Ball(600, 100, RAD, false);
    } else if (key == '3') {
        balls[2] = new Ball(900, 300, RAD, false);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
