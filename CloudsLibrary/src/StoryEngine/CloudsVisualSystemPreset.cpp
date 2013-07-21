//
//  CloudsVisualSystemPreset.cpp
//  CLOUDS
//
//  Created by James George on 6/19/13.
//
//

#include "CloudsVisualSystemPreset.h"
#include "CloudsVisualSystem.h"
#include "ofxXmlSettings.h"

CloudsVisualSystemPreset::CloudsVisualSystemPreset(){
	system = NULL;
	indefinite = true;
	duration = 60;
	introDuration = 0;
	outroDuration = 0;
}

string CloudsVisualSystemPreset::getID(){
	return systemName + "_" + presetName;
}

void CloudsVisualSystemPreset::loadTimeInfo(){
	ofxXmlSettings timeInfo;
	string path = getDataPath() + "visualsystems/"+systemName+"/" + presetName + "/TimeInfo.xml";
	if(timeInfo.load(path) ){
		timeInfo.pushTag("timeinfo");
		indefinite = timeInfo.getValue("indefinite", true);
		duration = timeInfo.getValue("duration", 60);
		introDuration = timeInfo.getValue("introDuration", 0);
		outroDuration = timeInfo.getValue("outroDuration", 0);
	}
	else{
		ofLogError() << "Preset " << systemName << " / " << presetName << " has no time info at path" << path << ". creating default";
		if(system != NULL){
			timeInfo.addTag("timeinfo");
			timeInfo.pushTag("timeinfo");
			timeInfo.addValue("duration", duration);
			timeInfo.addValue("indefinite", indefinite);
			timeInfo.addValue("introDuration", introDuration);
			timeInfo.addValue("outroDuration", outroDuration);
			timeInfo.save(path);
		}
	}
}
