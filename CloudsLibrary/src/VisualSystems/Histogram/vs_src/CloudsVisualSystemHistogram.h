//
// CLOUDS Interactive Documentary
//
// VISUAL SYSTEMS
//
// Welcome to the Histogram CloudsVisualSystem
//
//
//

#pragma once

#include "CloudsVisualSystem.h"
#include "ofOpenALSoundPlayer_TimelineAdditions.h"

enum HistogramMode
{
    HISTOGRAM_MODE_BARS,
    HISTOGRAM_MODE_LINES,
    HISTOGRAM_MODE_POINTS
};

enum HistogramSource
{
    HISTOGRAM_SOURCE_RANDOM,
    HISTOGRAM_SOURCE_AUDIO
};

class CloudsVisualSystemHistogram : public CloudsVisualSystem {
  public:
    
	//TODO: Change this to the name of your visual system
	//This determines your data path so name it at first!
	//ie getVisualSystemDataPath() uses this
    string getSystemName(){
		return "Histogram";
	}

	//These methods let us add custom GUI parameters and respond to their events
    void selfSetupGui();
    void selfGuiEvent(ofxUIEventArgs &e);
    
	//Use system gui for global or logical settings, for exmpl
    void selfSetupSystemGui();
    void guiSystemEvent(ofxUIEventArgs &e);
    
	//use render gui for display settings, like changing colors
    void selfSetupRenderGui();
    void guiRenderEvent(ofxUIEventArgs &e);

	// selfSetup is called when the visual system is first instantiated
	// This will be called during a "loading" screen, so any big images or
	// geometry should be loaded here
    void selfSetup();
    void selfSetDefaults();

	// selfBegin is called when the system is ready to be shown
	// this is a good time to prepare for transitions
	// but try to keep it light weight as to not cause stuttering
    void selfBegin();

	// selfPresetLoaded is called whenever a new preset is triggered
	// it'll be called right before selfBegin() and you may wish to
	// refresh anything that a preset may offset, such as stored colors or particles
	void selfPresetLoaded(string presetPath);
    
	//do things like ofRotate/ofTranslate here
	//any type of transformation that doesn't have to do with the camera
    void selfSceneTransformation();
	
	//normal update call
	void selfUpdate();

	// selfDraw draws in 3D using the default ofEasyCamera
	// you can change the camera by returning getCameraRef()
    void selfDraw();
		
    // draw any debug stuff here
	void selfDrawDebug();

	// or you can use selfDrawBackground to do 2D drawings that don't use the 3D camera
	void selfDrawBackground();

	// this is called when your system is no longer drawing.
	// Right after this selfUpdate() and selfDraw() won't be called any more
	void selfEnd();

	// this is called when you should clear all the memory and delet anything you made in setup
    void selfExit();

	//events are called when the system is active
	//Feel free to make things interactive for you, and for the user!
    void selfKeyPressed(ofKeyEventArgs & args);
    void selfKeyReleased(ofKeyEventArgs & args);
    
    void selfMouseDragged(ofMouseEventArgs& data);
    void selfMouseMoved(ofMouseEventArgs& data);
    void selfMousePressed(ofMouseEventArgs& data);
    void selfMouseReleased(ofMouseEventArgs& data);
	

    // if you use a custom camera to fly through the scene
	// you must implement this method for the transitions to work properly
//	ofCamera& getCameraRef(){
//		return myCustomCamera;
//	}

    void stopSound();
    void reloadSound();
    
	void addRandomPoint();
    void addSoundPoint();
    
protected:
    ofxUISuperCanvas* customGui;
    
    bool bDoAlphaBlending;
    bool bDoDepthTesting;
	
    vector<float> dataPoints;
    int maxNumDataPoints;
    
    int noiseValue;
    int n;
    
    float t;
    
    ofDirectory soundsDir;
    int selectedSoundsIdx;
    ofOpenALSoundPlayer_TimelineAdditions soundPlayer;
    float levelAdjust;
    
    ofMesh histoMesh;
    
    float hueMax, hueMin;
    float satBase, satRange;
    float briBase, briRange;
    float alpha;
    
    ofColor colorFg;
    ofColor colorClear;
    
    float rowSpacer;
    float colSpacer;
    float colWidth;
    float colHeightMin, colHeightMax;
    int numRows;
    int colsPerRow;
    float lineWidth;
    
    HistogramMode mode;
    HistogramSource source;

    bool bSeparateFeeds;
    float sampleOffset;
    
    vector<float>& getFFT();
    void generateEnvelope(int size);

    float lastFFTPosition;
    float dampening;
    int averageSize;
    bool useEnvelope;
    vector<float> envelope;
    vector<float> dampened;
    
    float fogDensity;
    
    float fMainGain;
};
