/**********************************************
*Change by TheCell(TheCell61@hotmail.com)
*I did not change much, other than headers and
*library included to the project
*Also, once you've downloaded the sdk, you must
*copy the files you've got from the sdk
*according to this template
*$MSDEV/
*		|
*		include/
*				|
*				al/
*				|
*				|  al.h
*				|  alc.h
*				|  alut.h
*		|
*		lib/
*			|
*			!  alut.lib
*			|  openal32,lib
*
*If you don't copy all the .h files into the
*include dir, you'll get compile error
*and if you don't copy the .lib files
*to the correct directory AND and add them to
*the project, you'll get link error
***********************************************/

/**********************************************
*Change:	Added stdio.h
*			changed al/alut.c to al/alut.h
*
***********************************************/

/**********************************************
*Explanation	1:Since we use printf, we MUST
*				include stdio.h to use this
*				function
*
*				2:I have been searching for
*				the alut.c files, but I have
*				not found it.  So I assume
*				that alut.h was intended
*				instead
************************************************/

#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>			//For some reason, stdio.h were not included, so I added it(TheCell)
							//See Explanation 1

#include <AL/al.h>
#include <AL/alc.h>
//#include <al/alut.c>		Since I have not found alut.c anywhere, I suppose we use alut.h
#include <AL/alut.h>		//Added by TheCell
							//See explanation 2


/*
* These are OpenAL "names" (or "objects"). They store and id of a buffer
* or a source object. Generally you would expect to see the implementation
* use values that scale up from '1', but don't count on it. The spec does
* not make this mandatory (as it is OpenGL). The id's can easily be memory
* pointers as well. It will depend on the implementation.
*/

// Buffers to hold sound data.
ALuint Buffer;

// Sources are points of emitting sound.
ALuint Source;


/*
* These are 3D cartesian vector coordinates. A structure or class would be
* a more flexible of handling these, but for the sake of simplicity we will
* just leave it as is.
*/

// Position of the source sound.
ALfloat SourcePos[] = { 0.0, 0.0, 0.0 };

// Velocity of the source sound.
ALfloat SourceVel[] = { 0.0, 0.0, 0.0 };


// Position of the Listener.
ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };

// Velocity of the Listener.
ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };

// Orientation of the Listener. (first 3 elements are "at", second 3 are "up")
// Also note that these should be units of '1'.
ALfloat ListenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };



/*
* ALboolean LoadALData()
*
*	This function will load our sample data from the disk using the Alut
*	utility and send the data into OpenAL as a buffer. A source is then
*	also created to play that buffer.
*/
ALboolean LoadALData()
{
	// Variables to load into.

	ALenum format;
	ALsizei size;
	ALvoid* data;
	ALsizei freq;
	ALboolean loop;

	// Load wav data into a buffer.

	alGenBuffers(1, &Buffer);

	if(alGetError() != AL_NO_ERROR)
		return AL_FALSE;

	alutLoadWAVFile((ALbyte *) "wavdata/FancyPants.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffer, format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);

	// Bind the buffer with the source.

	alGenSources(1, &Source);

	if(alGetError() != AL_NO_ERROR)
		return AL_FALSE;

	alSourcei (Source, AL_BUFFER,   Buffer   );
	alSourcef (Source, AL_PITCH,    1.0      );
	alSourcef (Source, AL_GAIN,     1.0      );
	alSourcefv(Source, AL_POSITION, SourcePos);
	alSourcefv(Source, AL_VELOCITY, SourceVel);
	alSourcei (Source, AL_LOOPING,  loop     );

	// Do another error check and return.

	if(alGetError() == AL_NO_ERROR)
		return AL_TRUE;

	return AL_FALSE;
}



/*
* void SetListenerValues()
*
*	We already defined certain values for the Listener, but we need
*	to tell OpenAL to use that data. This function does just that.
*/
void SetListenerValues()
{
	alListenerfv(AL_POSITION,    ListenerPos);
	alListenerfv(AL_VELOCITY,    ListenerVel);
	alListenerfv(AL_ORIENTATION, ListenerOri);
}



/*
* void KillALData()
*
*	We have allocated memory for our buffers and sources which needs
*	to be returned to the system. This function frees that memory.
*/
void KillALData()
{
	alDeleteBuffers(1, &Buffer);
	alDeleteSources(1, &Source);
	alutExit();
}




int main(int argc, char *argv[])
{
    printf("MindCode's OpenAL Lesson 1: Single Static Source\n\n");
	printf("Controls:\n");
	printf("p) Play\n");
	printf("s) Stop\n");
	printf("h) Hold (pause)\n");
	printf("q) Quit\n\n");

	// Initialize OpenAL and clear the error bit.

	alutInit(NULL, 0);
	alGetError();

	// Load the wav data.

	if(LoadALData() == AL_FALSE)
	{
	    printf("Error loading data.");
		return 0;
	}

	SetListenerValues();

	// Setup an exit procedure.

	atexit(KillALData);

	// Loop.

	ALubyte c = ' ';

	while(c != 'q')
	{
		c = getche();

		switch(c)
		{
			// Pressing 'p' will begin playing the sample.

			case 'p': alSourcePlay(Source); break;

			// Pressing 's' will stop the sample from playing.

			case 's': alSourceStop(Source); break;

			// Pressing 'h' will pause the sample.

			case 'h': alSourcePause(Source); break;
		};

	}

	return 0;
}

