#include <portaudio.h>
#include <stdio.h>
#include <math.h>

#define SAMPLE_RATE (44100)

// #define TABLE_SIZE 20000

typedef struct
{
    float pitch;
    float oldpitch;
    long n;
}   
paTestData;

static paTestData data;

// square wave callback
static int patestCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData )
{
  /* Cast data passed through stream to our structure. */
  paTestData *data = (paTestData*)userData; 
  float *out = (float*)outputBuffer;
  unsigned int i;
  (void) inputBuffer; /* Prevent unused variable warning. */

  if(data->pitch != data->oldpitch) {
    data->n = data->oldpitch * data->n / data->pitch;
    data->oldpitch = data->pitch;
  }

  for( i=0; i<framesPerBuffer; i++ )
  {
    float v = (float) sin(data->pitch * 2 * M_PI * data->n / SAMPLE_RATE);
    *out++ = v;
    *out++ = v;
    data->n++;
  }
  return 0;
}

int main()
{
  // compute sine table
  // for(int i = 0; i < TABLE_SIZE; i++)
  // {
  //   data.sine[i] = (float) sin(M_PI * 2 * i / TABLE_SIZE);
  // }
  data.pitch = 261.626;
  data.oldpitch = data.pitch;
  data.n = 0;

  // initialize portaudio
  PaError err = Pa_Initialize();
  if(err != paNoError) goto error;

  // open a stream
  PaStream *stream;
  err = Pa_OpenDefaultStream( &stream,
                              0, // no input
                              2, // 2 output
                              paFloat32,
                              SAMPLE_RATE,
                              50,
                              patestCallback,
                              &data);
  if(err != paNoError) goto error;

  // start stream
  err = Pa_StartStream(stream);
  if(err != paNoError) goto error;

  // Pa_Sleep(10000);
  while(scanf("%f", &data.pitch) != EOF)
  {

  }

  err = Pa_StopStream( stream );
  if( err != paNoError ) goto error;
  
  // terminate portaudio
  err = Pa_Terminate();
  if(err != paNoError) goto error;

error:
  fprintf(stderr, "PortAudio error: %s\n", Pa_GetErrorText(err));
  return 1;
}
