/*
 *   Copyright (C) 2012 Vladislav Sitalo <root@stvad.org>
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

#include "sphinxcontrol.h"
#include <KDebug>
#include <QDir>
#include <simonutils/fileutils.h>
#include <KStandardDirs>
#include <KLocale>
#include <speechmodelcompilation/modelmetadata.h>
#include <simonrecognizer/sphinxrecognitionconfiguration.h>

SphinxControl::SphinxControl(const QString& username, QObject* parent) : RecognitionControl(username, parent)
{
}

bool SphinxControl::initializeRecognition(const QString &modelPath)
{
  if (modelPath == m_lastModel) return true; //already initialized / tried to initialize with this exact model

  m_lastModel = modelPath;
  kDebug() << "Initializing";
  if (isInitialized())
  {
    kDebug() << "Initializing recognition that was already initialized; uninitializing...";
    uninitialize();
    m_startRequests = 0;
  }

  QString path = KStandardDirs::locateLocal("tmp", "/simond/"+username+"/sphinx/");
  if(!QDir(path).entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst).isEmpty())
  {
    FileUtils::removeDirRecursive(path);
    path = KStandardDirs::locateLocal("tmp", "/simond/"+username+"/sphinx/");
  }

  if (!FileUtils::unpackAll(modelPath, path)) //All becouse need to know model name to unpack jsgf&dict. Yes can get it from metadata but it would be a "crutch" on my mind
  {
    return false;
  }

  kDebug() << "Emitting recognition ready";
  emit recognitionReady();
  return true;
}

RecognitionConfiguration *SphinxControl::setupConfig()
{
  QString dirPath = KStandardDirs::locateLocal("tmp", "/simond/"+username+"/sphinx/");

  QFile metadataFile(dirPath+QLatin1String("metadata.xml"));
  if(!metadataFile.open(QIODevice::WriteOnly))
  {
    emit recognitionError(i18n("Failed to write filler to \"%1\"", dirPath+QLatin1String("metadata.xml")),
                          getBuildLog());
    return false;
  }
  ModelMetadata metadata;
  QDomDocument DomDocument;
  DomDocument.setContent(&metadataFile);
  metadata.DeserializeXml(DomDocument.documentElement());



  //TODO: set proper paramets & create sphinxrecognition

  return new SphinxRecognitionConfiguration(dirPath, dirPath+metadata.Name()+QLatin1String(".jsgf"),
                                            dirPath+metadata.Name()+QLatin1String(".dic"));
}

void SphinxControl::emitError(const QString &error)
{
  //TODO: Implement
}
