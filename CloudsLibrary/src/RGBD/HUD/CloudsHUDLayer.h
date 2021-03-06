//
//  CloudsHUDLayer.h
//  CloudsHUDDesigner
//
//  Created by James George on 12/14/13.
//
//

#pragma once

#include "ofMain.h"
#include "ofxTween.h"
#include "CloudsSVGMesh.h"

class CloudsHUDLayer
{
	static ofShader lineShader;
  public:
	
	CloudsHUDLayer();
	
	void parse(string svgFilePath);
    void parseDirectory(string svgDirectoryPath);
	
	vector<string> textBoxIds;
	CloudsSVGMesh svg;
	
	void start(bool animate = true);
    void close(bool animate = true);
    
	void update();
	void draw();
	
    bool isOpen();
    
	bool animating;
	float delayTime;
	float startTime;
	float duration;
	
	float maxUpdateInterval;
	float lastUpdateTime;
	
	ofVec2f startPercent;
	
	ofVec2f percentComplete;
	float xlag;
	ofRectangle drawRect;
	ofVec2f startPoint;
	ofVec2f endPoint;
    
  protected:
    bool bIsOpen;
};
