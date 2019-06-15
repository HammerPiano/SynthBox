#include <iostream>
#include <vector>
#include <alsa/asoundlib.h>
#include <signal.h>
#include <math.h>
#include <limits.h>

using std::cout;
using std::endl;
using std::vector;

const size_t BUFFER_SIZE = 1024;

bool running = true;
int main()
{
	int err = 0;
	snd_pcm_t* handle = nullptr;
	snd_pcm_sframes_t nframes = 0;
	vector<uint8_t> buffer(BUFFER_SIZE);

	err = snd_pcm_open(&handle,"default",SND_PCM_STREAM_PLAYBACK,0);	
	cout << "snd_pcm_open " << err << "\n";
	if(err < 0 )
	{
		exit(1);
	}

	err = snd_pcm_set_params(handle,SND_PCM_FORMAT_U8,SND_PCM_ACCESS_RW_INTERLEAVED,1,44100,1,500000);
	cout << "snd_pcm_set_params " << err << "\n";
	if(err < 0 )
	{
		exit(1);
	}

	while (true)
	{
		nframes = snd_pcm_writei(handle,buffer.data(),buffer.size());
		if(nframes < 0)
		{
			nframes = snd_pcm_recover(handle,nframes,0);
		}

		if(nframes < 0)
		{
			cout << "write failed " << snd_strerror(nframes);
		}


	}

	snd_pcm_close(handle);
	
	return 0;
}
