/*
 *  Copyright (C) 2014-2021 Arne Morten Kvarving
 *  Copyright (C) 2016-2021 Team Kodi (https://kodi.tv)
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#pragma once

#include <algorithm>
#include <iostream>
#include <kodi/addon-instance/AudioDecoder.h>

extern "C"
{
#include "upse-internal.h"
#include "upse.h"

#include <stdint.h>
#include <stdio.h>

  struct UPSEContext
  {
    upse_module_t* mod = nullptr;
    int16_t* buf = nullptr;
    int16_t* head = nullptr;
    size_t size = 0;
  };

} /* extern "C" */

class ATTR_DLL_LOCAL CUPSECodec : public kodi::addon::CInstanceAudioDecoder
{
public:
  CUPSECodec(const kodi::addon::IInstanceInfo& instance);
  virtual ~CUPSECodec();

  bool Init(const std::string& filename,
            unsigned int filecache,
            int& channels,
            int& samplerate,
            int& bitspersample,
            int64_t& totaltime,
            int& bitrate,
            AudioEngineDataFormat& format,
            std::vector<AudioEngineChannel>& channellist) override;
  int ReadPCM(uint8_t* buffer, size_t size, size_t& actualsize) override;
  int64_t Seek(int64_t time) override;
  bool ReadTag(const std::string& filename, kodi::addon::AudioDecoderInfoTag& tag) override;

private:
  UPSEContext ctx;
  bool m_endWasReached = false;
};
