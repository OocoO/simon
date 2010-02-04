/*
 *   Copyright (C) 2010 Peter Grasch <grasch@simon-listens.org>
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

#include "voiceinterfacecommand.h"
#include "commandmanager.h"
#include <QMetaObject>

VoiceInterfaceCommand::VoiceInterfaceCommand(CommandManager *parentManager, const QString& trigger, const QString& iconSrc, 
			const QString& description, const QString& id, const QString& visibleTrigger) :
	Command(trigger, iconSrc, description),
	m_parentManager(parentManager),
	m_id(id), 
	m_visibleTrigger(visibleTrigger),
	m_receiver(NULL)
{
}

void VoiceInterfaceCommand::assignAction(CommandManager *parentManager, QObject *receiver, const QString& slot)
{
	m_parentManager = parentManager;
	m_receiver = receiver;
	m_slot = slot;
}

bool VoiceInterfaceCommand::triggerPrivate()
{
	if (m_receiver == NULL) return false;

	//Queued connection:
	// -: Cannot be used with types that qt doesn't know about. You need to call qRegisterMetaType
	//    If you want to invoke slots that use custom types. Refer to the qt documentation
	//    for more info
	// +: Works in multithreaded environments
	QByteArray slotName = m_slot.toAscii();
	QMetaObject::invokeMethod(m_receiver, slotName.data(), Qt::QueuedConnection);

	return true;
}

const QMap<QString,QVariant> VoiceInterfaceCommand::getValueMapPrivate() const
{
	QMap<QString,QVariant> out;

	out.insert(i18n("Visible trigger:"), m_visibleTrigger);
	return out;
}

bool VoiceInterfaceCommand::deSerializePrivate(const QDomElement& element)
{
	if (element.isNull()) return false;

	QDomElement idElement = element.firstChildElement("id");
	QDomElement visibleTriggerElement = element.firstChildElement("visibleTrigger");
	m_id = idElement.text();
	m_visibleTrigger = visibleTriggerElement.text();

	return true;
}

VoiceInterfaceCommand* VoiceInterfaceCommand::createInstance(const QDomElement& element)
{
	VoiceInterfaceCommand *guiInterfaceCommand = new VoiceInterfaceCommand(); //private constructor
	if (!guiInterfaceCommand->deSerialize(element))
	{
		delete guiInterfaceCommand;
		return NULL;
	}

	return guiInterfaceCommand;
}

QDomElement VoiceInterfaceCommand::serializePrivate(QDomDocument *doc, QDomElement& commandElem)
{
	QDomElement idElement = doc->createElement("id");
	idElement.appendChild(doc->createTextNode(m_id));

	QDomElement visibleTriggerElement = doc->createElement("visibleTrigger");
	visibleTriggerElement.appendChild(doc->createTextNode(m_visibleTrigger));

	commandElem.appendChild(idElement);
	commandElem.appendChild(visibleTriggerElement);

	return commandElem;
}


const QString VoiceInterfaceCommand::staticCategoryText()
{
	return i18n("Voice Interface");
}

const KIcon VoiceInterfaceCommand::staticCategoryIcon()
{
	return KIcon("text-speak");
}


const KIcon VoiceInterfaceCommand::getCategoryIcon() const
{
	return m_parentManager->icon();
}

const QString VoiceInterfaceCommand::getCategoryText() const
{
	return m_parentManager->name();
}

VoiceInterfaceCommand::~VoiceInterfaceCommand()
{
}

