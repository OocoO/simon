/*
 *   Copyright (C) 2014 Peter Grasch <peter.grasch@bedahr.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License version 2,
 *   or (at your option) any later version, as published by the Free
 *   Software Foundation
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "coreaudiobackend.h"
#include <simonsound/soundbackendclient.h>
#include <simonlogging/logger.h>

QStringList CoreAudioBackend::getAvailableInputDevices()
{
  return QStringList();
}

QStringList CoreAudioBackend::getAvailableOutputDevices()
{
  return QStringList();
}

bool CoreAudioBackend::check(SimonSound::SoundDeviceType type, const QString& device, int channels, int samplerate)
{
  return false;
}


QString CoreAudioBackend::getDefaultInputDevice()
{
  return QString();
}

QString CoreAudioBackend::getDefaultOutputDevice()
{
  return QString();
}


int CoreAudioBackend::bufferSize()
{
  return 0;
}


//recording
bool CoreAudioBackend::prepareRecording(const QString& device, int& channels, int& samplerate)
{
  return false;
}

bool CoreAudioBackend::startRecording(SoundBackendClient *client)
{
  return false;
}

bool CoreAudioBackend::stopRecording()
{
  return false;
}


//playback
bool CoreAudioBackend::preparePlayback(const QString& device, int& channels, int& samplerate)
{
  return false;
}

bool CoreAudioBackend::startPlayback(SoundBackendClient *client)
{
  return false;
}

bool CoreAudioBackend::stopPlayback()
{
  return false;
}

