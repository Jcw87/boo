#ifndef BOO_IAUDIOMIX_HPP
#define BOO_IAUDIOMIX_HPP

#include <list>

namespace boo
{
struct AudioVoiceEngineMixInfo;
class AudioVoice;
class AudioSubmix;

/** Entity that mixes audio from several child sources (engine root or submix) */
class IAudioMix
{
    friend class AudioVoice;
    friend class AudioSubmix;
    virtual void _unbindFrom(std::list<AudioVoice*>::iterator it)=0;
    virtual void _unbindFrom(std::list<AudioSubmix*>::iterator it)=0;
public:
    virtual const AudioVoiceEngineMixInfo& mixInfo() const=0;
};

}

#endif // BOO_IAUDIOMIX_HPP
