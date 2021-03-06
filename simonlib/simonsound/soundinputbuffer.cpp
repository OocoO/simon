/*   Copyright (C) 2010 Grasch Peter <peter.grasch@bedahr.org>
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

#include "soundinputbuffer.h"
#include "simonsoundinput.h"
#include <QMutexLocker>
#include <KDebug>

SoundInputBuffer::SoundInputBuffer(SimonSoundInput* input): SoundBuffer(input),
  m_input(input), m_buffer(0), m_bufferLength(0)
{
  start(QThread::HighestPriority); // make sure we don't lose samples on slow maschines
}

void SoundInputBuffer::write(const char *toWrite, qint64 len)
{
//   kDebug() << "Writing: " << len;

  m_bufferAllocLock.lock();
  m_buffer = (char*) realloc(m_buffer,sizeof(char)*(m_bufferLength+len+1));
 
  memcpy(m_buffer + m_bufferLength, toWrite, len);
  
  m_bufferLength += len;
  m_bufferLock.release(len);
  m_bufferAllocLock.unlock();
}

void SoundInputBuffer::run()
{
  while (m_shouldBeRunning)
  {
    //fill buffer to buffer length
    int bufferSize = m_input->bufferSize();

    while (!m_bufferLock.tryAcquire(bufferSize, 50)) {
      if (!m_shouldBeRunning) {
        deleteLater();
        return;
      }
    }

    m_bufferAllocLock.lock();
//     kDebug() << "new buffer length: " << bufferSize;
    QByteArray currentData(m_buffer, bufferSize);


    char *newBuffer = (char*) malloc(sizeof(char)*(m_bufferLength-bufferSize+1));

    memcpy(newBuffer, m_buffer+bufferSize, m_bufferLength - bufferSize);
    
    char *oldBuffer = m_buffer;
    m_buffer = newBuffer;
    m_bufferLength -= bufferSize;
    m_bufferAllocLock.unlock();
    free(oldBuffer);

    //m_input->processData(m_buffer.left(bufferSize));
    m_input->processData(currentData);


    //kDebug()  << "Local buffer size before removing data: " << m_buffer.length();
    //m_buffer.remove(0, bufferSize);
    if (m_bufferLength > 20*bufferSize) // drop data as a last resort 
    {
      kDebug()  << "EMERGENCY: Clearing buffer " << m_bufferLength;
      m_bufferAllocLock.lock();
      free(m_buffer);
      m_buffer = 0;
      m_bufferLength = 0;
      m_bufferLock.acquire(m_bufferLock.available());
      m_bufferAllocLock.unlock();
    }

    //m_buffer = m_buffer.mid(bufferSize);
//     kDebug()  << "Local buffer size: " << m_bufferLength;
  }
  deleteLater();
}

void SoundInputBuffer::stop()
{
  kDebug() << "Set should be running to false";
  m_shouldBeRunning = false;
}

SoundInputBuffer::~SoundInputBuffer()
{
  free (m_buffer);
}

