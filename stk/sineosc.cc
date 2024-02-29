// sineosc.cpp
 
#include "stk/FileLoop.h"
#include "stk/FileWvOut.h"
using namespace stk;
 
int main()
{
  // Set the global sample rate before creating class instances.
  Stk::setSampleRate( 44100.0 );
 
  FileLoop input;
  FileWvOut output;
 
  // Load the sine wave file.
  input.openFile( "rawwaves/crashcym.raw", true );
 
  // Open a 16-bit, one-channel WAV formatted output file
  output.openFile( "hellosine.wav", 1, FileWrite::FILE_WAV, Stk::STK_SINT16 );
 
  // input.setFrequency( 440.0 );
 
  // Run the oscillator for 40000 samples, writing to the output file
  for ( int i=0; i<400000; i++ )
    output.tick( input.tick() );
 
  return 0;
}
