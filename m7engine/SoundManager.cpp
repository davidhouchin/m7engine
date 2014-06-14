/*
* Copyright 2014 David Houchin
* This file is part of m7engine, which is free software you probably
* don't even want.. It is made available to you under the terms of
* the GNU General Public License as published by the Free Software Foundation.
* For more information, see COPYING.
*/

#include "SoundManager.h"

namespace M7engine
{
Sample::Sample()
{
}

Sample::~Sample()
{
	al_destroy_sample(sample_data);
	al_destroy_sample_instance(sample);
}

bool Sample::loadSample(const char* filename)
{
	sample_data = al_load_sample(filename);

	if (!sample_data)
	{
		Logger::getInstance()->logError(0, "Failed to load sample: '%s'", filename);
		return false;
	}

	sample = al_create_sample_instance(NULL);

	if (!al_set_sample(sample, sample_data))
	{
		Logger::getInstance()->logError(0, "al_set_sample failed failed");
		return false;
	}

	return true;
}

SoundManager::SoundManager()
{
}

SoundManager::SoundManager(const SoundManager& orig)
{
}

SoundManager::~SoundManager()
{
	al_destroy_mixer(mixer);
	al_destroy_voice(voice);
	al_uninstall_audio();
}

bool SoundManager::init()
{
	if (!al_install_audio())
	{
		Logger::getInstance()->logError(0, "al_install_audio failed");
		return false;
	}

	if (!al_init_acodec_addon())
	{
		Logger::getInstance()->logError(0, "al_init_acodec_addon failed");
		return false;
	}

	if (!al_reserve_samples(64))
	{
		Logger::getInstance()->logError(0, "al_reserve_samples failed");
		return false;
	}

	voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
	if (!voice)
	{
		Logger::getInstance()->logError(0, "al_create_voice failed");
		return false;
	}

	mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
	if (!mixer)
	{
		Logger::getInstance()->logError(0, "al_create_mixer failed");
		return false;
	}

	if (!al_attach_mixer_to_voice(mixer, voice))
	{
		Logger::getInstance()->logError(0, "al_attach_mixer_to_voice failed");
		return false;
	}

	return true;
}

bool SoundManager::playSample(Sample *sampleName)
{
	ALLEGRO_SAMPLE_INSTANCE *sample = sampleName->getSample();

	if (!al_get_sample_instance_attached(sample))
	{
		al_attach_sample_instance_to_mixer(sample, mixer);
	}

	if (al_get_sample_instance_playing(sample))
	{
		al_stop_sample_instance(sample);
	}

	if (!al_play_sample_instance(sample))
	{
		Logger::getInstance()->logError(0, "Failed to play sample: '%s'", sampleName->getFilename());
		return false;
	}

	return true;
}

bool SoundManager::stopSample(Sample *sampleName)
{
	ALLEGRO_SAMPLE_INSTANCE *sample = sampleName->getSample();

	if (al_get_sample_instance_playing(sample))
	{
		if (!al_stop_sample_instance(sample))
		{
			return false;
		}
	}

	return true;
}
}
