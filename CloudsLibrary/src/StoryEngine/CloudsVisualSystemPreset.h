#pragma once

#include "ofMain.h"

class CloudsVisualSystem;
class CloudsVisualSystemPreset {
  public:
	
	CloudsVisualSystemPreset();
	string presetName;
	string systemName;
	ofPtr<CloudsVisualSystem> system;
	
	float introDuration;
	float outroDuration;
	float duration;
	bool indefinite;
	void loadTimeInfo();
	void eraseFiles();
	
	string getID();
	string comments;
	string grade;
	bool enabled;
	bool oculusCompatible;
	
	bool defaultedToFamily;
	string conjureKeyword;
	vector<string> allKeywords; // only filled out when the preset is scheduled
	bool randomlySelected;
	
	bool stillPresent;
	float currentScore;
};