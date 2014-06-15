/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/

#ifndef SOUNDMANAGER_H
#define	SOUNDMANAGER_H

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdio.h>
#include "Logger.h"

namespace M7engine
{
class Sample
{
public:
	Sample();
	virtual ~Sample();

	bool loadSample(const char *filename);
	ALLEGRO_SAMPLE_INSTANCE* getSample() { return sample; }
	const char* getFilename() { return filename; }

	ALLEGRO_AUDIO_DEPTH getSampleDepth() { return al_get_sample_instance_depth(this->getSample()); }

	float getSampleTime() { return al_get_sample_instance_time(this->getSample()); }

	bool getSamplePlaying() { return al_get_sample_instance_playing(this->getSample()); }
	int getSampleFrequency() { return al_get_sample_instance_frequency(this->getSample()); }

	int getSampleLength() { return al_get_sample_instance_length(this->getSample()); }
	bool setSampleLength(int arg) { return (al_set_sample_instance_length(this->getSample(), arg) ? true : false); }

	int getSamplePosition() { return al_get_sample_instance_position(this->getSample()); }
	bool setSamplePosition(int arg) { return (al_set_sample_instance_position(this->getSample(), arg) ? true : false); }

	float getSampleSpeed() { return al_get_sample_instance_speed(this->getSample()); }
	bool setSampleSpeed(float arg) { return (al_set_sample_instance_speed(this->getSample(), arg) ? true : false); }

	float getSampleGain() { return al_get_sample_instance_gain(this->getSample()); }
	bool setSampleGain(float arg) { return (al_set_sample_instance_gain(this->getSample(), arg) ? true : false); }

	float getSamplePan() { return al_get_sample_instance_pan(this->getSample()); }
	bool setSamplePan(float arg) { return (al_set_sample_instance_pan(this->getSample(), arg) ? true : false); }

	ALLEGRO_PLAYMODE getSamplePlayMode() { return al_get_sample_instance_playmode(this->getSample()); }
	bool setSamplePlayMode(ALLEGRO_PLAYMODE arg) { return (al_set_sample_instance_playmode(this->getSample(), arg) ? true : false); }

	const char* getName(){ return this->name; }
	void setName(const char *name) { this->name = name; }

private:
	ALLEGRO_SAMPLE *sample_data;
	ALLEGRO_SAMPLE_INSTANCE *sample;
	const char *filename, *name;
};

class SoundManager
{
public:
	SoundManager();
	SoundManager(const SoundManager& orig);
	virtual ~SoundManager();

	bool init();
	bool playSample(Sample *sampleName);
	bool stopSample(Sample *sampleName);
	ALLEGRO_MIXER* getMixer(){ return mixer; }

private:
	ALLEGRO_VOICE *voice;
	ALLEGRO_MIXER *mixer;

};
}
#endif
