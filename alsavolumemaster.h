#include <unistd.h>
#include <fcntl.h>
#include <alsa/asoundlib.h>

void alsaMasterVolume(long* output) {
	snd_mixer_t* handle;
	snd_mixer_selem_id_t* sid;

	static const char* mix_name = "Master";
	static const char* card = "default";
	static int mix_index = 0;

	snd_mixer_selem_id_alloca(&sid);

	snd_mixer_selem_id_set_index(sid, mix_index);
	snd_mixer_selem_id_set_name(sid, mix_name);

	snd_mixer_open(&handle, 0);
	snd_mixer_attach(handle, card);
	snd_mixer_selem_register(handle, NULL, NULL);
	snd_mixer_load(handle);

	snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);

	long minv, maxv;

	snd_mixer_selem_get_playback_volume_range(elem, &minv, &maxv);

	snd_mixer_selem_get_playback_volume(elem, 0, output);

	*output -= minv;
	maxv -= minv;
	*output = 100 * (*output) / maxv; 
	snd_mixer_close(handle);
}

