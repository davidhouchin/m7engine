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
			fprintf(stderr, "Failed to load sample: '%s'\n", filename);
			return false;
		}

		sample = al_create_sample_instance(NULL);

		if (!al_set_sample(sample, sample_data))
		{
			fprintf(stderr, "al_set_sample failed\n");
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
			fprintf(stderr, "al_install_audio failed\n");
			return false;
		}

		if (!al_init_acodec_addon())
		{
			fprintf(stderr, "al_init_acodec_addon failed\n");
			return false;
		}

		if (!al_reserve_samples(64))
		{
			fprintf(stderr, "al_reserve_samples failed\n");
			return false;
		}

		voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
		if (!voice)
		{
			fprintf(stderr, "al_create_voice failed\n");
			return false;
		}

		mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
		if (!mixer)
		{
			fprintf(stderr, "al_create_mixer failed\n");
			return false;
		}

		if (!al_attach_mixer_to_voice(mixer, voice))
		{
			fprintf(stderr, "al_attach_mixer_to_voice failed\n");
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
			fprintf(stderr, "Failed to play sample: '%s'\n", sampleName->getFilename());
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
