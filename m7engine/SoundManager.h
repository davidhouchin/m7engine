/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/
/**
 *  Sound Manager
 *  SoundManager.h
 *  Purpose: Manager to handle sound sample modification and playback.
 *  @author David Houchin
 *  @version 1.0 7/17/14
 */

#ifndef SOUNDMANAGER_H
#define	SOUNDMANAGER_H

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdio.h>
#include "Logger.h"

namespace M7engine {
class Sample {
public:
    Sample();
    virtual ~Sample();

    /**
     *  Loads an audio sample from disk.
     *  @param *filename Char array containing filename to sample.
     */
    bool loadSample(const char *filename);
    /**
     *  Returns the sample instance being used.
     *  @return Pointer to the ALLEGRO_SAMPLE_INSTANCE being used.
     */
    ALLEGRO_SAMPLE_INSTANCE* getSample() { return sample; }
    /**
     *  Returns the filename of the sample being used.
     *  @return Char array containing filename to sample.
     */
    const char* getFilename() { return filename; }

    /**
     *  Returns sample depth of sample.
     *  @return The sample depth as an ALLEGRO_AUDIO_DEPTH.
     */
    ALLEGRO_AUDIO_DEPTH getSampleDepth() { return al_get_sample_instance_depth(this->getSample()); }

    /**
     *  Returns the length of the sample in seconds.
     *  @return The length of the sample in seconds.
     */
    float getSampleTime() { return al_get_sample_instance_time(this->getSample()); }

    /**
     *  Returns whether the sample is currently being played.
     *  @return Whether the sample is currently being played.
     */
    bool getSamplePlaying() { return al_get_sample_instance_playing(this->getSample()); }
    /**
     *  Returns the frequency of the sample.
     *  @return The frequency of the sample.
     */
    int getSampleFrequency() { return al_get_sample_instance_frequency(this->getSample()); }

    /**
     *  Returns the length of the sample.
     *  @return The length of the sample.
     */
    int getSampleLength() { return al_get_sample_instance_length(this->getSample()); }
    /**
     *  Sets the length of the sample.
     *  @param len The length of the sample.
     */
    bool setSampleLength(int len) { return (al_set_sample_instance_length(this->getSample(), len) ? true : false); }

    /**
     *  Returns the playback position of the sample.
     *  @return The playback position of the sample.
     */
    int getSamplePosition() { return al_get_sample_instance_position(this->getSample()); }
    /**
     *  Sets the playback position of the sample.
     *  @param pos The playback position of the sample to set.
     */
    bool setSamplePosition(int pos) { return (al_set_sample_instance_position(this->getSample(), pos) ? true : false); }

    /**
     *  Returns the playback speed of the sample.
     *  @return The playback speed of the sample.
     */
    float getSampleSpeed() { return al_get_sample_instance_speed(this->getSample()); }
    /**
     *  Sets the playback speed of the sample. 1.0 is normal.
     *  @param spd The playback speed to set.
     */
    bool setSampleSpeed(float spd) { return (al_set_sample_instance_speed(this->getSample(), spd) ? true : false); }

    /**
     *  Returns the gain of the sample.
     *  @return The gain of the sample.
     */
    float getSampleGain() { return al_get_sample_instance_gain(this->getSample()); }
    /**
     *  Sets the gain of the sample.
     *  @param gain The gain to set.
     */
    bool setSampleGain(float gain) { return (al_set_sample_instance_gain(this->getSample(), gain) ? true : false); }

    /**
     *  Returns the pan of the sample.
     *  @return The pan of the sample.
     */
    float getSamplePan() { return al_get_sample_instance_pan(this->getSample()); }
    /**
     *  Sets the pan of the sample. 0.0 is normal.
     *  @param pan The pan to set.
     */
    bool setSamplePan(float pan) { return (al_set_sample_instance_pan(this->getSample(), pan) ? true : false); }

    /**
     *  Returns the playmode of the sample.
     *  @return The playmode of the sample.
     */
    ALLEGRO_PLAYMODE getSamplePlayMode() { return al_get_sample_instance_playmode(this->getSample()); }
    /**
     *  Sets the playmode of the sample. Values are once, looping, or bidirectional.
     *  @param mode The playmode to set. Use 0-2.
     */
    bool setSamplePlayMode(ALLEGRO_PLAYMODE mode) { return (al_set_sample_instance_playmode(this->getSample(), mode) ? true : false); }

    /**
     *  Returns the resource name of the sample.
     *  @return Char array containing the resource name.
     */
    const char* getName(){ return this->name; }
    /**
     *  Sets the resource name of the sample.
     *  @param *name Char array containing the resource name to set.
     */
    void setName(const char *name) { this->name = name; }

private:
    ALLEGRO_SAMPLE *sample_data;
    ALLEGRO_SAMPLE_INSTANCE *sample;
    const char *filename, *name;
};

class SoundManager {
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
