/**
 @file      SoundManager.h
 @author    Lukas Reuter
 @date      01.09.18

Copyright (c) 2018 till 2019, Lukas Reuter
All rights reserved.

*/

 #ifndef __SOUNDMANAGER_H__
 #define __SOUNDMANAGER_H__

 #include <cstdio>
#include <string>

 // Comment this line if you don't have the EAX 2.0 SDK installed
 //#define _USEEAX

 #ifdef _USEEAX
     #include "eax.h"
 #endif

 // OpenAl version 1.1
 //#include <al.h>
 //#include <alc.h>
 //#include <alut.h>
 //#include <vorbis/vorbisfile.h>
 // Modify this as you need.
 //#include "OgreVector3.h"
 //#include "OgreQuaternion.h"
 #include "Singleton.h"
 //#include "entityx.h"
#include "Messages.h"
    //using namespace Ogre;


 // Be very careful with these two parameters
 // It is very dependant on the audio hardware your
 // user is using. It you get too large, it may work
 // on one persons system but not on another.
 // TODO Write a fct testing the hardware !
 #define MAX_AUDIO_BUFFERS   64
 #define MAX_AUDIO_SOURCES   16

 // Used to store sound filenames
 #define MAX_FILENAME_LENGTH 40

 class SoundManager : public Singleton<SoundManager>//, public entityx::Receiver<SoundManager>
 {/*
   private:
        // EAX related
        bool isEAXPresent;
 #ifdef _USEEAX
        // EAX 2.0 GUIDs
        const GUID DSPROPSETID_EAX20_ListenerProperties
            = { 0x306a6a8, 0xb224, 0x11d2, { 0x99, 0xe5, 0x0, 0x0, 0xe8, 0xd8, 0xc7, 0x22 } };

        const GUID DSPROPSETID_EAX20_BufferProperties
            = { 0x306a6a7, 0xb224, 0x11d2, {0x99, 0xe5, 0x0, 0x0, 0xe8, 0xd8, 0xc7, 0x22 } };

        EAXSet eaxSet; // EAXSet function, retrieved if EAX Extension is supported
        EAXGet eaxGet; // EAXGet function, retrieved if EAX Extension is supported
 #endif // _USEEAX

        bool isInitialised;
        ALCdevice* mSoundDevice;
        ALCcontext* mSoundContext;

        std::string mAudioPath;

        bool isSoundOn;

        ALfloat position[3];
        ALfloat velocity[3];
        ALfloat orientation[6];

        // Needed because of hardware limitation
        // Audio sources
        unsigned int mAudioSourcesInUseCount;
        unsigned int mAudioSources[ MAX_AUDIO_SOURCES ];
        bool         mAudioSourceInUse[ MAX_AUDIO_SOURCES ];

        // Audio buffers
        unsigned int mAudioBuffersInUseCount;
        unsigned int mAudioBuffers[ MAX_AUDIO_BUFFERS ];
        bool         mAudioBufferInUse[ MAX_AUDIO_BUFFERS ];
        char         mAudioBufferFileName[ MAX_AUDIO_BUFFERS ][ MAX_FILENAME_LENGTH ];

        // Function to check if the soundFile is already loaded into a buffer
        int locateAudioBuffer( std::string filename );
        int loadAudioInToSystem( const char* filename );
        // TODO bool loadWAV( std::string filename, ALuint pDestAudioBuffer );
        bool loadOGG( std::string filename, ALuint pDestAudioBuffer );
        // TODO bool loadAU( std::string filename, ALuint pDestAudioBuffer );
        std::map<std::string,unsigned int> audioFiles;

    public:

        void receive(const ShootEvent &event);
        void receive(const ObjectDestroyed &);
        void receive(const GameStarted &event);

        void loadFiles();

        static SoundManager* mSoundManager;

        SoundManager( void );
        virtual ~SoundManager( void );
        void selfDestruct( void );
        static SoundManager* createManager( void );
        static SoundManager* getSingletonPtr( void ) { return mSoundManager; };

        bool init( void );
        bool getIsSoundOn( void ) { return isSoundOn; };
        void setAudioPath( char* path ) { mAudioPath = std::string( path ); };

        bool checkALError( void );
        bool checkALError( std::string pMsg );

        /** See http://www.openal.org/windows_enumeration.html for installing other
        *   devices. You should at least have "Generic Hardware".
        */
        /*
        std::string listAvailableDevices( void );

        // Aquire an Audio Source
        // filename = pass in the sound file to play for this source (ex. "myfile.wav")
        // audioId   = returns the AudioSource identifier you will need for the PlayAudioSource();
        bool loadAudio( std::string filename, unsigned int *audioId, bool loop );
        bool releaseAudio( unsigned int audioID );

        // Returns true if the audio is started from the beginning
        // false if error or if already playing
        bool playAudio( unsigned int audioId, bool forceRestart );
        bool stopAudio( unsigned int audioID );
        bool stopAllAudio( void );

        bool pauseAudio( unsigned int audioID );
        bool pauseAllAudio( void );
        bool resumeAudio( unsigned int audioID );
        bool resumeAllAudio( void );

        bool setSoundPosition( unsigned int audioID, Ogre::Vector3 position );

        bool setSoundPosition( unsigned int audioID, Ogre::Vector3 position,
            Ogre::Vector3 velocity, Ogre::Vector3 direction );

        bool setSound( unsigned int audioID, Ogre::Vector3 position,
            Ogre::Vector3 velocity, Ogre::Vector3 direction, float maxDistance,
            bool playNow, bool forceRestart, float minGain );

        bool setListenerPosition( Ogre::Vector3 position, Ogre::Vector3 velocity,
            Ogre::Quaternion orientation );
     */
 };

 #endif /*__SOUNDMANAGER_H__*/
