//
//  Walker.h
//  OpenP5Spaghetti
//
//  Created by Jonathan Minard on 10/25/13.
//
//

#pragma once

#include "ofMain.h"


class Walker {

  public:
	Walker();
	
	ofVec3f position;
    ofVec3f previousPosition;
    ofVec3f currentPosition;
    
    ofVec3f position1;
    ofVec3f previousPosition1;
    ofVec3f currentPosition1;
    
    ofColor color;
	
    static int i;
    static float j;
    static float nParticles;
    
    float maxX, minX, maxY, minY, maxZ, minZ;
    

    void init(int nParticles, ofColor color);
    void step();
    void smoothTrails();
    void doubleTrails(); 
    void gnarlyTrails();
    void draw();
    void setColor(ofColor color);
    
    //random seed for noise
    float seed;
    static float noiseSpeedx;
    static float noiseSpeedy;
    static float noiseSpeedz;
    
    static float stepSizex;
    static float stepSizey;
    static float stepSizez;
    
    static bool drawPoints;
	//float pointAlpha;
//	static bool drawLines;
//  static bool drawTriangles;
    static float lineWidth;
    
    static float saturation;
    static float brightness;
    
    //thickness of double-trails
    static float thickness;
    
    //the number of vertices in the mesh
    int numVertices;
    
    ofVboMesh mesh;
    
    
    
    
  protected:
    
//    vector<particle> particles;
    
    
    
    
  
};
