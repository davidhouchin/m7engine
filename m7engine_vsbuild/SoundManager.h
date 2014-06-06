#ifndef SOUNDMANAGER_H
#define	SOUNDMANAGER_H

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdio.h>

namespace M7engine
{
	class Sample
	{
	public:
		Sample();
		virtual ~Sample();

		bool loadSample(const char *filename);
		ALLEGRO_SAMPLE_INSTANCE* getSample() { return sample; }
		char getFilename() { return filename; }

		ALLEGRO_AUDIO_DEPTH getSampleDepth() { return al_get_sample_instance_depth(this->getSample()); }

		bool getSamplePlaying() { return al_get_sample_instance_playing(this->getSample()); }
		int getSampleFrequency() { return al_get_sample_instance_frequency(this->getSample()); }

		int getSampleLength() { return al_get_sample_instance_length(this->getSample()); }
		bool setSampleLength(int arg) { if (al_set_sample_instance_length(this->getSample(), arg)){ return true; } else { return false; } }




	private:
		ALLEGRO_SAMPLE *sample_data;
		ALLEGRO_SAMPLE_INSTANCE *sample;
		char filename;
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
