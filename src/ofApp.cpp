#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  
        dir.listDir("videos");
        dir.allowExt("mov");
        dir.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order
        
        for(int i = 0; i < (int)dir.size(); i++){
            string tempString = dir.getPath(i);
            //ofLogNotice("Scanning directors") << "File path found at " + tempString << endl;
            filePaths.push_back(tempString);
        }
 
        for (int i = 0; i < NUM_PLAYERS; i++) {
            auto tempPlayerFront = make_shared<ofxHapPlayer>();
            hapPlayersFront.push_back(tempPlayerFront);
            
            auto tempPlayerBack = make_shared<ofxHapPlayer>();
            hapPlayersBack.push_back(tempPlayerBack);
            
            bool isActive;
            frontPlayersActive.push_back(isActive);
            
            
            if(hapPlayersFront[i]->load(filePaths[int(ofRandom(filePaths.size() -1))])){
                ofLogNotice("Loading front videos") << "File path is: " + ofToString(hapPlayersFront[i]->getMoviePath()) + " Frame size " + ofToString(hapPlayersFront[i]->getTexture()->getWidth())  + " " + ofToString(hapPlayersFront[i]->getTexture()->getHeight()) + " Total frames: " + ofToString(hapPlayersFront[i]->getTotalNumFrames()) << endl;
                hapPlayersFront[i]->setVolume(0.2);
                hapPlayersFront[i]->play();
                hapPlayersFront[i]->setLoopState(OF_LOOP_NONE);
                frontPlayersActive[i] = true;
            }
            if(hapPlayersBack[i]->load(filePaths[int(ofRandom(filePaths.size() -1))])){
                ofLogNotice("Loading back videos") << "File path is: " + ofToString(hapPlayersBack[i]->getMoviePath()) + " Frame size " + ofToString(hapPlayersBack[i]->getTexture()->getWidth())  + " " + ofToString(hapPlayersBack[i]->getTexture()->getHeight()) + " Total frames: " + ofToString(hapPlayersBack[i]->getTotalNumFrames()) << endl;
                hapPlayersBack[i]->setLoopState(OF_LOOP_NONE);
                hapPlayersBack[i]->setVolume(0.2);
                hapPlayersBack[i]->stop();
                

            }
        }
    
  
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i = 0; i < NUM_PLAYERS; i++)
    {
        if (frontPlayersActive[i]) {
            if (hapPlayersFront[i]->getIsMovieDone()) {
                hapPlayersBack[i]->play();
                hapPlayersFront[i]->load(filePaths[int(ofRandom(filePaths.size() -1))]);
                frontPlayersActive[i]=false;
            }
        }
        if (!frontPlayersActive[i]) {
            if (hapPlayersBack[i]->getIsMovieDone()) {
                hapPlayersFront[i]->play();
                hapPlayersBack[i]->load(filePaths[int(ofRandom(filePaths.size() -1))]);
                frontPlayersActive[i] = false;
            }
        }
        if (frontPlayersActive[i]) {
            hapPlayersFront[i]->update();
        }
        if (!frontPlayersActive[i]) {
            hapPlayersBack[i]->update();
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    for (int i = 0; i < NUM_PLAYERS; i++)
    {
        int drawWidth = ofGetWidth() / NUM_PLAYERS;
        if (frontPlayersActive[i]) {
            hapPlayersFront[i]->draw(i * drawWidth, 50, drawWidth,  drawWidth / hapPlayersFront[i]->getTexture()->getWidth() *  hapPlayersFront[i]->getTexture()->getHeight());
            ofPushStyle();
            ofSetColor(255, 0, 0);
            ofDrawBitmapString("Front " + ofToString(i) + " Active ", i * drawWidth + 5, 30);
            ofPopStyle();
        }
        else if(!frontPlayersActive[i]) {
            hapPlayersBack[i]->draw(i * drawWidth, 50, drawWidth,  drawWidth / hapPlayersBack[i]->getTexture()->getWidth() *  hapPlayersBack[i]->getTexture()->getHeight());
            ofPushStyle();
            ofSetColor(255, 0, 0);
            ofDrawBitmapString("Back " + ofToString(i) + " Active ", i * drawWidth + 5, 30);
            ofPopStyle();
        }
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
