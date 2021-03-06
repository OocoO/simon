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

#include "runcommandviewprivate.h"
#include <simonscenarios/action.h>
#include <simonscenarios/commandmanager.h>
#include <simonscenarios/scenario.h>
#include <simonscenarios/voiceinterfacecommand.h>
#include <simonscenarios/actioncollection.h>
#include <simonscenarios/simoncommand.h>
#include "newcommand.h"
#include "manageactionsdialog.h"
#include "commandpreviewwidget.h"

#include <QWidget>
#include <QPointer>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QSize>
#include <QSortFilterProxyModel>
#include <QItemSelectionModel>

#include <KMessageBox>
#include <KIcon>
#include <KCMultiDialog>

/**
 *	@brief Constructor
 *
 *	@author Peter Grasch
 */
RunCommandViewPrivate::RunCommandViewPrivate(QWidget *parent) : QWidget(parent)
{
  ui.setupUi(this);
  ui.frmCommandInfo->hide();

  connect ( ui.pbNewCommand, SIGNAL(clicked()), this, SLOT(addCommand()));
  connect ( ui.pbEditCommand, SIGNAL(clicked()), this, SLOT(editCommand()));
  connect ( ui.pbDeleteCommand, SIGNAL(clicked()), this, SLOT(deleteCommand()));
  connect ( ui.pbManagePlugins, SIGNAL(clicked()), this, SLOT(managePlugIns()));

  connect(ui.pbTrigger, SIGNAL(clicked()), this, SLOT(triggerCommand()));

  ui.lvActions->setIconSize(QSize(24,24));
  ui.lvCommands->setIconSize(QSize(24,24));
  ui.lvActions->setSpacing(2);
  ui.lvCommands->setSpacing(2);

  ui.pbNewCommand->setIcon(KIcon("list-add"));
  ui.pbEditCommand->setIcon(KIcon("edit-rename"));
  ui.pbDeleteCommand->setIcon(KIcon("edit-delete"));
  ui.pbManagePlugins->setIcon(KIcon("configure"));

  commandsProxy = new QSortFilterProxyModel(this);
  commandsProxy->setFilterKeyColumn(0);
  commandsProxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
  ui.lvCommands->setModel(commandsProxy);

  actionsProxy = new QSortFilterProxyModel(this);
  actionsProxy->setFilterKeyColumn(0);
  actionsProxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
  ui.lvActions->setModel(actionsProxy);

  connect(ui.leCommandsFilter, SIGNAL(textChanged(QString)), commandsProxy, SLOT(setFilterRegExp(QString)));
  connect(ui.leActionsFilter, SIGNAL(textChanged(QString)), actionsProxy, SLOT(setFilterRegExp(QString)));

  connect(ui.leActionsFilter, SIGNAL(textChanged(QString)), this, SLOT(fetchCommandsFromCategory()));
  connect(ui.lvActions->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(fetchCommandsFromCategory()));
  connect(ui.lvCommands->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(updateCommandDetail()));
}


void RunCommandViewPrivate::managePlugIns()
{
  QPointer<ManageActionsDialog> dlg = new ManageActionsDialog(this);
  if (dlg->exec()) {
    emit actionsChanged();
  }
  updateCommandDetail();
  delete dlg;
}


void RunCommandViewPrivate::displayScenarioPrivate(Scenario *scenario)
{
  ui.leActionsFilter->clear();

  ActionCollection *actionCollection = scenario->actionCollection();

  commandsProxy->setSourceModel(0);

  actionsProxy->setSourceModel((QAbstractItemModel*) actionCollection->getProxy());

  ui.lvActions->setCurrentIndex(actionsProxy->index(0,0));
  updateCommandDetail();
}


void RunCommandViewPrivate::triggerCommand()
{
  Command *com = getCurrentCommand();
  Action *a = getCurrentlySelectedAction();
  if (a && a->manager())
    a->manager()->triggerCommand(com, false);
}


void RunCommandViewPrivate::addCommand()
{
  NewCommand *newCommand = new NewCommand(this);

  newCommand->registerCreators(scenario->actionCollection()->getCreateCommandWidgets(0/*newCommand*/));

  Action *a = getCurrentlySelectedAction();
  if (a && a->manager())
    newCommand->newCommand(a->manager());
  else
    newCommand->newCommand();

  delete newCommand;
}


Action* RunCommandViewPrivate::getCurrentlySelectedAction()
{
  QModelIndex index = actionsProxy->mapToSource(ui.lvActions->currentIndex());
  if (!index.isValid()) return 0;

  return static_cast<Action*>(index.internalPointer());
}


void RunCommandViewPrivate::fetchCommandsFromCategory()
{
  Action *a = getCurrentlySelectedAction();
  CommandManager *cm = 0;

  if (a) cm = a->manager();

  ui.leCommandsFilter->clear();

  commandsProxy->setSourceModel(cm);
  if (cm && cm->hasCommands()) {
    ui.lvCommands->setCurrentIndex(commandsProxy->index(0,0));
  }
  else {
    //no index changed means we have to update this manually
    updateCommandDetail();
  }
}


Command* RunCommandViewPrivate::getCurrentCommand()
{
  QModelIndex index = commandsProxy->mapToSource(ui.lvCommands->currentIndex());
  if (!index.isValid()) return 0;

  return static_cast<Command*>(index.internalPointer());
}


void RunCommandViewPrivate::updateCommandDetail()
{
  Command *com = getCurrentCommand();
  if (!com) {
    ui.frmCommandInfo->hide();
    ui.pbEditCommand->setEnabled(false);
    ui.pbDeleteCommand->setEnabled(false);
    ui.lbCompleteTrigger->clear();
  }
  else {
    Action* a = getCurrentlySelectedAction();
    if (!a) return;
    ui.lbCompleteTrigger->setText('"'+QString(a->trigger()+' '+com->getTrigger()).trimmed()+'"');

    ui.frmCommandInfo->show();
    ui.pbEditCommand->setEnabled(true);
    ui.pbDeleteCommand->setEnabled(true);

    ui.lbName->setText(com->getTrigger());
    ui.lbIcon->setPixmap(KIcon(com->getIcon()).pixmap(64,64));

    QLayoutItem *child;
    while (ui.flDetails->count() > 0) {
      child = ui.flDetails->takeAt(0);
      ui.flDetails->removeItem(child);

      QWidget *widget = child->widget();
      if (widget) widget->deleteLater();
      delete child;
    }

    QMap<QString,QVariant> details = com->getValueMap();
    QStringList keys = details.keys();

    for (int i=0; i < keys.count(); i++) {
      QLabel *label = new QLabel(this);
      label->setOpenExternalLinks(true);
      label->setWordWrap(true);
      QVariant value = details.value(keys[i]);

      QString strValue;

      switch (value.type()) {
        case QVariant::Url:
          strValue = QString("<a href=\"%1\">%1</a>").arg(value.toUrl().toString());
          break;
        case QVariant::UserType:
        {
          KUrl url = value.value<KUrl>();
          if (url.isValid()) {
            strValue = QString("<a href=\"%1\">%1</a>").arg(url.prettyUrl());
            break;
          }                                       //else let it run into default
        }
        default:
          strValue = value.toString();
          break;
      }

      label->setText(strValue);

      ui.flDetails->addRow(keys[i]+':', label);
      label->setMinimumSize(label->sizeHint());
    }
  }

}


void RunCommandViewPrivate::editCommand()
{
  Command *command = getCurrentCommand();
  if (!command) return;

  NewCommand *editCommand = new NewCommand(this);
  editCommand->registerCreators(scenario->actionCollection()->getCreateCommandWidgets(0/*editCommand*/));
  editCommand->init(command);
  bool succ = editCommand->newCommand();
  if (succ) {
    ScenarioManager::getInstance()->getCurrentScenario()->removeCommand(command);
    //ScenarioManager::getInstance()->getCurrentScenario()->addCommand(newCommand);
    ui.lvCommands->setCurrentIndex(commandsProxy->index(commandsProxy->rowCount()-1, 0));
  }
}


void RunCommandViewPrivate::deleteCommand()
{
  Command *command = getCurrentCommand();
  if (!command) return;

  if (KMessageBox::questionYesNoCancel(this, i18n("Are you sure that you want to irreversibly remove the command \"%1\"?", command->getTrigger()), i18n("Remove Command")) == KMessageBox::Yes) {
    ScenarioManager::getInstance()->getCurrentScenario()->removeCommand(command);
    updateCommandDetail();
  }
}


/**
 *	@brief Destructor
 *
 *	@author Peter Grasch
 */
RunCommandViewPrivate::~RunCommandViewPrivate()
{
}
