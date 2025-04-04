#ifndef AUDIO_H
#define AUDIO_H 
#include "state.hpp"
#include <glm/glm.hpp>
#include <AL/al.h>
#include <AL/alc.h>
#include <vector>

enum sound_state{
   PLAY,
   PAUSE,
   SS_SIZE_ENUM
};
enum sound_type {
   WALKING,
   ST_SIZE_ENUM,
};

class Audio {
   public:
      ALCdevice* device;
      ALCcontext* context;
      
      std::vector<ALuint> sound_effects;
   public:
      Audio() {init();}
      ~Audio() {
         alDeleteBuffers(sound_effects.size(), sound_effects.data());
         sound_effects.clear();
      }

   public:
      ALuint add_sound_effect(const char* src);
      bool remove_sound_effect(const ALuint& buffer);
   private:
      void init();
};



class Sound {
   private:
      ALuint source, buffer;
      float pitch, gain;
      bool is_loop = true;
      glm::vec3 pos, vel;
      
      std::vector<ALuint> buffers;
      std::vector<sound_state> states;
     
      ALuint walking;
   public:
      Sound():
      pitch(1.0f), gain(0.09f), pos(glm::vec3(0.0f)), vel(glm::vec3(0.0))
      {
         buffers.resize(sound_type::ST_SIZE_ENUM);
         states.resize(sound_state::SS_SIZE_ENUM);
         init();

         state.sound = this;
      }
      ~Sound() {};

   public:
      void init_sounds(Audio *audio) {
         buffers[sound_type::WALKING] = audio->add_sound_effect(WALKING_OGG);
      }
      void play_sound(sound_type type);
      void pause_sound(sound_type type);

   private:
      void init(){
         alGenSources(1, &source);
         alSourcef(source, AL_PITCH, pitch);
         alSourcef(source, AL_GAIN, gain);
         alSource3f(source, AL_POSITION, pos.x, pos.y, pos.z);
         alSource3f(source, AL_VELOCITY, vel.x, vel.y, vel.z);
         alSourcei(source, AL_LOOPING, is_loop);
      }

};

#endif 
