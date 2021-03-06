/*
 *   Copyright (C) 2010 Peter Grasch <peter.grasch@bedahr.org>
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

#include "nullrecorderclient.h"
#include "soundserver.h"
#include "loudnessmetersoundprocessor.h"
#include "vadsoundprocessor.h"

#include <QObject>
#include <KDebug>

/**
 * \brief Constructor
 */
NullRecorderClient::NullRecorderClient(const SimonSound::DeviceConfiguration& deviceConfiguration, SoundClientPriority options, QObject* parent) :
QObject(parent),
SoundInputClient(deviceConfiguration, options),
vad(new VADSoundProcessor(deviceConfiguration, true /*pass all through*/))
{
  registerSoundProcessor(vad);
  connect(vad, SIGNAL(listening()), this, SIGNAL(sampleStarted()));
  connect(vad, SIGNAL(complete(qint64, qint64)), this, SIGNAL(sampleCompleted()));
}


bool NullRecorderClient::start()
{
  return SoundServer::getInstance()->registerInputClient(this);
}


void NullRecorderClient::processPrivate(const QByteArray& data, qint64 currentTime)
{
  Q_UNUSED(data);

  float peak = vad->peak() / 32768.0f;
  emit level(currentTime, peak);
  if (vad->clipping())
    emit clippingOccured();
}


bool NullRecorderClient::finish()
{
  return SoundServer::getInstance()->deRegisterInputClient(this);
}


/**
 * \brief Destructor
 */
NullRecorderClient::~NullRecorderClient()
{
  SoundServer::getInstance()->deRegisterInputClient(this);
}
