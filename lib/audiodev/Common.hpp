#pragma once

#include <soxr.h>
#include "boo/audiodev/IAudioVoice.hpp"
#include "lib/Common.hpp"

namespace boo {

/** Pertinent information from audio backend about optimal mixed-audio representation */
struct AudioVoiceEngineMixInfo {
  double m_sampleRate = 32000.0;
  soxr_datatype_t m_sampleFormat = SOXR_FLOAT32_I;
  unsigned m_bitsPerSample = 32;
  AudioChannelSet m_channels = AudioChannelSet::Stereo;
  ChannelMap m_channelMap = {2, {AudioChannel::FrontLeft, AudioChannel::FrontRight}};
  size_t m_periodFrames = 160;
};

} // namespace boo
