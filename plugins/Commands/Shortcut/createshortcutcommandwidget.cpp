/*
 *   Copyright (C) 2008 Peter Grasch <grasch@simon-listens.org>
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

#include "createshortcutcommandwidget.h"
#include "shortcutcommand.h"

CreateShortcutCommandWidget::CreateShortcutCommandWidget(QWidget *parent) : CreateCommandWidget(parent)
{
	ui.setupUi(this);

	ui.ksShortcut->setCheckForConflictsAgainst(KKeySequenceWidget::None);

	setWindowIcon(ShortcutCommand::staticCategoryIcon());
	setWindowTitle(ShortcutCommand::staticCategoryText());
	
	connect(ui.ksShortcut, SIGNAL(keySequenceChanged (const QKeySequence &)), this, SIGNAL(completeChanged()));
}


bool CreateShortcutCommandWidget::isComplete()
{
	return !(ui.ksShortcut->keySequence().isEmpty());
}

bool CreateShortcutCommandWidget::init(Command* command)
{
	Q_ASSERT(command);
	
	ShortcutCommand *shortcutCommand = dynamic_cast<ShortcutCommand*>(command);
	if (!shortcutCommand) return false;
	
	ui.ksShortcut->setKeySequence(shortcutCommand->getShortcut());
	return true;
}

Command* CreateShortcutCommandWidget::createCommand(const QString& name, const QString& iconSrc)
{
	return new ShortcutCommand(name, iconSrc, ui.ksShortcut->keySequence());
}

CreateShortcutCommandWidget::~CreateShortcutCommandWidget()
{
}