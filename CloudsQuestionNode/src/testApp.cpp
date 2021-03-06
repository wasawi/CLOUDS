#include "testApp.h"
#include "CloudsInput.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofBackground(0);
	ofSetVerticalSync(true);
	portal.cam = &easyCam;
	portal.setup();
    
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA, 4);
    
#ifdef OCULUS_RIFT
    oculusRift.baseCamera = &easyCam;
    oculusRift.setup();
#endif
}

//--------------------------------------------------------------
void testApp::update(){
	portal.update();
    
#ifdef OCULUS_RIFT
    ofRectangle viewport = oculusRift.getOculusViewport();
    ofVec3f screenPos = oculusRift.worldToScreen(portal.hoverPosition, true);
    float gazeDist = ofDist(screenPos.x, screenPos.y,
                            viewport.getCenter().x, viewport.getCenter().y);
    if (gazeDist < portal.minSelectDistance) {
        portal.startHovering();
    }
    else{
        portal.stopHovering();
    }
#else
    if(portal.screenPosition.distance( ofVec2f(GetCloudsInputX(),GetCloudsInputY())) < portal.minSelectDistance ){
        portal.startHovering();
    }
    else{
        portal.stopHovering();
    }

#endif
}

//--------------------------------------------------------------
void testApp::draw(){
    
    glDisable(GL_DEPTH_TEST);

#ifdef OCULUS_RIFT
    ofRectangle viewport = oculusRift.getOculusViewport();
    
    oculusRift.beginOverlay();
    ofPushStyle();
    ofNoFill();
    ofSetColor(255, 0, 0);
    ofCircle(oculusRift.getOverlayRectangle().getCenter(), 10);
    ofPopStyle();
    oculusRift.endOverlay();

    oculusRift.beginLeftEye();
	portal.draw();
    oculusRift.endLeftEye();
    
    oculusRift.beginRightEye();
    portal.draw();
    oculusRift.endRightEye();
    
    oculusRift.draw();
#else
    fbo.begin();
    ofClear(0,0,0,0);
	easyCam.begin();
	CloudsPortal::shader.begin();
	portal.draw();
	CloudsPortal::shader.end();
	easyCam.end();
    
//    ofPushStyle();
//	ofSetColor(portal.hovering ? ofColor::yellow : ofColor::white);
//	ofCircle(portal.screenPosition, 10);
//	ofPopStyle();
    fbo.end();
    fbo.draw(0,0);
#endif
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == 'R'){
		portal.reloadShader();
	}
    else if(key == 'f'){
        ofToggleFullscreen();
    }
    else if(key == ' '){
#ifdef OCULUS_RIFT
        oculusRift.reset();
#else
        ofPixels p;
        fbo.readToPixels(p);
        ofSaveImage(p, "SAVEFRAME.png");
#endif
    }
}

//--------------------------------------------------------------
void testApp::exit(){
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    fbo.allocate(w, h, GL_RGB, 4);
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
