/* VideoInfo:
 * This example querys the PS3 for its current reslution and prints it to tty.
 * You will need something that redirects tty to see the output.
 */

#include <audio/audio.h>
#include <psl1ght/lv2/timer.h>
#include <math.h>
#include <sys/time.h> // gettimeofday, timeval, timersub
#include <time.h> // ctime
#include <assert.h>
#include <stdio.h>

#define SHW64(X) (u32)(((u64)X)>>32), (u32)(((u64)X)&0xFFFFFFFF)

sys_event_queue_t snd_queue; // Queue identifier
u64	snd_queue_key; // Queue Key

#define PI 3.14159265f

void fillBuffer(float *buf)
{
	static float pos=0;

	for (unsigned int i = 0; i < AUDIO_BLOCK_SAMPLES; ++i)
	{
		//just fill with a beautiful sine wave :P
		buf[i*2+0] = sin(pos);
		//in fact 2 different ones
		buf[i*2+1] = sin(pos*2);
		pos+=0.01f;
		if(pos>M_PI)
			pos-=2*M_PI;
	}
}

u32 playOneBlock(u64 *readIndex, float *audioDataStart)
{
	u32 ret = 0;
	//get position of the hardware
	u64 current_block = *readIndex;

	u32 audio_block_index = (current_block + 1) % AUDIO_BLOCK_8;

	sys_event_t event;
	ret = sys_event_queue_receive( snd_queue, &event, 20 * 1000);

	//get position of the block to write
	float *buf = audioDataStart + 2 /*channelcount*/ * AUDIO_BLOCK_SAMPLES * audio_block_index;
	printf( "\t\tbuf: 0x%08X.%08X\n", SHW64(buf));
	fillBuffer(buf);

	return 1;
}

int main(int argc, const char* argv[])
{
	AudioPortParam params;
	AudioPortConfig config;
	u32 portNum;

	//initialize the audio system
	int ret=audioInit();

	printf("audioInit: %d\n",ret);

	//set some parameters we want
	//either 2 or 8 channel
	params.numChannels = AUDIO_PORT_2CH;
	//8 16 or 32 block buffer
	params.numBlocks = AUDIO_BLOCK_8;
	//extended attributes
	params.attr = 0;
	//sound level (1 is default)
	params.level = 1;

	//open the port (still stopped)
	ret=audioPortOpen(&params, &portNum);
	printf("audioPortOpen: %d\n",ret);
	printf("  portNum: %d\n",portNum);

	//get the params for the buffers, etc
	ret=audioGetPortConfig(portNum, &config);
	printf("audioGetPortConfig: %d\n",ret);
	printf("  readIndex: 0x%8X\n",config.readIndex);
	printf("  status: %d\n",config.status);
	printf("  channelCount: %ld\n",config.channelCount);
	printf("  numBlocks: %ld\n",config.numBlocks);
	printf("  portSize: %d\n",config.portSize);
	printf("  audioDataStart: 0x%8X\n",config.audioDataStart);

	// create an event queue that will tell when a block is read
	ret=audioCreateNotifyEventQueue( &snd_queue, &snd_queue_key);
	printf("audioCreateNotifyEventQueue: %d\n",ret);
	printf("  snd_queue: 0x%08X.%08X\n",SHW64(snd_queue));
	printf("  snd_queue_key: 0x%08X.%08X\n", SHW64(snd_queue_key));

	// Set it to the sprx
	ret = audioSetNotifyEventQueue(snd_queue_key);
	printf("audioSetNotifyEventQueue: %d\n",ret);
	printf("  snd_queue_key: 0x%08X.%08X\n",SHW64(snd_queue_key));

	// clears the event queue
	ret = sys_event_queue_drain(snd_queue);
	printf("sys_event_queue_drain: %d\n",ret);

	//start the loop
	ret=audioPortStart(portNum);
	printf("audioPortStart: %d\n",ret);

	// To calculate the time spent playing
	struct timeval tim;
	struct timezone dummy;

	gettimeofday( &tim, &dummy);
	double t1=tim.tv_sec+(tim.tv_usec/1000000.0);

	int i=0;
	while(i<1000)
	{
		ret = playOneBlock((u64*)(u64)config.readIndex,(float*)(u64)config.audioDataStart);
		printf( "playOneBlock: %d (%d)\n", ret, i);
		if((ret)!=0)
			i++;

	}
	gettimeofday( &tim, &dummy);
	double t2=tim.tv_sec+(tim.tv_usec/1000000.0);

	printf( "Time spent playing: %.6lf\n", t2-t1);

	//shutdown in reverse order
	ret=audioPortStop(portNum);
	printf("audioPortStop: %d\n",ret);
	ret=audioRemoveNotifyEventQueue(snd_queue_key);
	printf("audioRemoveNotifyEventQueue: %d\n",ret);
	ret=audioPortClose(portNum);
	printf("audioPortClose: %d\n",ret);
	ret=sys_event_queue_destroy(snd_queue, 0);
	printf("sys_event_queue_destroy: %d\n",ret);
	ret=audioQuit();
	printf("audioQuit: %d\n",ret);

	return 0;
}
