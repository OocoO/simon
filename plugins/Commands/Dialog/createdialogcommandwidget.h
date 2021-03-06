/*
 *   Copyright (C) 2008 Peter Grasch <peter.grasch@bedahr.org>
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

#ifndef SIMON_CREATEDIALOGCOMMANDWIDGET_H_9F05429CB8EF43B8BFAC15877F9854C3
#define SIMON_CREATEDIALOGCOMMANDWIDGET_H_9F05429CB8EF43B8BFAC15877F9854C3

#include <QWidget>
#include <simonscenarios/createcommandwidget.h>
#include <simonscenarios/command.h>
#include "ui_createdialogcommandwidget.h"

class Command;
class DialogCommand;
class CommandManager;
class CommandTableModel;

/**
 *	@class CreateDialogCommandWidget
 *	@brief Provides a widget to modify the specific attributes of an DialogCommand
 *
 *	@version 0.1
 *	@date 8.10.2008
 *	@author Peter Grasch
 */
class CreateDialogCommandWidget : public CreateCommandWidget
{
  Q_OBJECT

  private:
    Ui::CreateDialogCommandWidget ui;

    CommandList m_allCommands;
    CommandTableModel *m_model;

    void initStates();

  private slots:
    void addCommandToDialog();
    void removeCommand();
    void moveUp();
    void moveDown();
    void enableButtons(const QModelIndex& index);


  public:
    Command* createCommand(const QString& name, const QString& iconSrc, const QString& description);
    void editCommand(DialogCommand *command, const QString& name, 
        const QString& iconSrc, const QString& description);

    bool init(Command* command);
    bool isComplete();

    explicit CreateDialogCommandWidget(CommandManager *manager, QWidget *parent=0);

    virtual ~CreateDialogCommandWidget();

  public slots:
    void updatePresentation(const QString& presentation);

};
#endif
