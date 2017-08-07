#pragma once

#include "ofConstants.h"
#include <vector>

extern "C" {
#include "fmod.h"
#include "fmod_errors.h"
}

//		TO DO :
//		---------------------------
// 		-fft via fmod, as in the last time...
// 		-close fmod if it's up
//		-loadSoundForStreaming(char * fileName);
//		---------------------------

// 		interesting:
//		http://www.compuphase.com/mp3/mp3loops.htm


// ---------------------------------------------------------------------------- SOUND SYSTEM FMOD

// --------------------- global functions:
void ofxFmodSoundStopAll();
void ofxFmodSoundSetVolume(float vol);
void ofxFmodSoundUpdate(); // calls FMOD update.
float* ofxFmodSoundGetSpectrum(int nBands); // max 512...
void ofxFmodSetBuffersize(unsigned int bs);

// ADDITIONS:
void ofxFmodSetPreferedDevice(int device);
int ofxFmodGetPreferedDevice();

int ofxFmodGetDevice();
int ofxFmodGetNumDevices();
vector<string> ofxFmodGetDeviceNames();

bool ofxFmodSetDevice(int device);

// --------------------- player functions:
class ofxFmodSoundPlayer2 {

public:

	ofxFmodSoundPlayer2();
	~ofxFmodSoundPlayer2();

	bool load(string fileName, bool stream = false);
	void unload();
	void play();
	void stop();

	void setVolume(float vol);
	void setPan(float vol);
	void setSpeed(float spd);
	void setPaused(bool bP);
	void setLoop(bool bLp);
	void setMultiPlay(bool bMp);
	void setPosition(float pct); // 0 = start, 1 = end;
	void setPositionMS(int ms);

	float getPosition() const;
	int getPositionMS() const;
	bool isPlaying() const;
	float getSpeed() const;
	float getPan() const;
	float getVolume() const;
	bool isLoaded() const;

	static void initializeFmod();
	static void closeFmod();

	bool isStreaming;
	bool bMultiPlay;
	bool bLoop;
	bool bLoadedOk;
	bool bPaused;
	float pan; // -1 to 1
	float volume; // 0 - 1
	float internalFreq; // 44100 ?
	float speed; // -n to n, 1 = normal, -1 backwards
	unsigned int length; // in samples;

	FMOD_RESULT result;
	FMOD_CHANNEL* channel;
	FMOD_SOUND* sound;

	// Additions:
	std::string getFileName();
	void setLevel(int index, float level);
	float getLevel(int index);

	void setMix4(float l1, float l2, float l3, float l4);
	void setMix8(float l1, float l2, float l3, float l4, float l5, float l6, float l7, float l8);

	std::string fileName;
	bool bIsPlaying; // (stopped or paused means not playing)
	float levels[8];
};
