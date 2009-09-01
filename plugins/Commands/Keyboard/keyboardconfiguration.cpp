/*
 *   Copyright (C) 2009 Dominik Neumeister & Mario Strametz <neudob06@edvhtl.at>  <strmam06@htl-kaindorf.ac.at>
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

#include "keyboardconfiguration.h"
#include "keyboardcommandmanager.h"
#include "keyboardbutton.h"
#include "keyboardtab.h"
#include "keyboardset.h"
#include "keyboardsetxmlreader.h"
#include "keyboardaddbuttondlg.h"
#include <QVariantList>
#include <kgenericfactory.h>
#include <QList>
#include <KAboutData>
#include <KMessageBox>
#include <QString>
#include <QDialog>
#include <qinputdialog.h>
#include <simoninfo/simoninfo.h>
#include <QTableView>


K_PLUGIN_FACTORY_DECLARATION(KeyboardCommandPluginFactory)

QPointer<KeyboardConfiguration> KeyboardConfiguration::instance;

KeyboardConfiguration::KeyboardConfiguration(QWidget *parent, const QVariantList &args)
		: CommandConfiguration("keyboard", ki18n( "Keyboard" ),
				      "0.1", ki18n("Input signes with ease"),
				      "accessories-calculator",
				      KeyboardCommandPluginFactory::componentData(),parent)
{
	Q_UNUSED(args);
	ui.setupUi(this);
	
	config = KSharedConfig::openConfig(KeyboardCommandPluginFactory::componentData(),"keyboardrc");

	QObject::connect(ui.leTrigger, SIGNAL(textChanged(QString)), this, SLOT(slotChanged()));
        connect(ui.tbAddSet, SIGNAL(clicked()), this, SLOT(addSet()));
	connect(ui.tbDeleteSet, SIGNAL(clicked()), this, SLOT(deleteSet()));
	connect(ui.tbAddTab, SIGNAL(clicked()), this, SLOT(addTab()));
	connect(ui.tbDeleteTab, SIGNAL(clicked()), this, SLOT(deleteTab()));
        connect(ui.pbAddButton, SIGNAL(clicked()), this, SLOT(addButton()));
	connect(ui.pbDeleteButton, SIGNAL(clicked()), this, SLOT(deleteButton()));
	connect(ui.pbUpButton, SIGNAL(clicked()), this, SLOT(buttonUp()));
	connect(ui.pbDownButton, SIGNAL(clicked()), this, SLOT(buttonDown()));
        connect(ui.cbSets, SIGNAL(currentIndexChanged()), this, SLOT(cbSetsIndexChanged()));
	
	//KeyboardsetXMLReader *reader = new KeyboardsetXMLReader("path");
	//setList = reader->load("path");
}

QString KeyboardConfiguration::trigger()
{
	KConfigGroup cg(config, "");
	return cg.readEntry("Trigger", i18n("Keyboard"));
}

void KeyboardConfiguration::addSet()
{	
        bool ok;
        QString inputText = QInputDialog::getText(this, "simon input", "Enter the name of the new set:", QLineEdit::Normal, QString(), &ok);
        if(ok && !inputText.isEmpty())
        {
            setList.append(new KeyboardSet(inputText));
            ui.cbSets->addItem(inputText);
            refreshCbTabs();
        }
        else
            SimonInfo::showMessage(i18n("Sorry, wrong Input"), 3000, new KIcon("accessories-calculator"));
}
void KeyboardConfiguration::deleteSet()
{	
        int setIndex = ui.cbSets->currentIndex();
        setList.removeAt(setIndex);
        ui.cbSets->removeItem(setIndex);
        refreshCbTabs();
}
void KeyboardConfiguration::addTab()
{	
	bool ok;
	QString inputText = QInputDialog::getText(this, "simon input","Enter the name of the new Tab:", QLineEdit::Normal, QString(), &ok);
        if(ok && !inputText.isEmpty() && !setList.isEmpty())
        {
            setList.at(ui.cbSets->currentIndex())->getTabList()->append(new KeyboardTab(inputText));
            refreshCbTabs();
        }
        else
            SimonInfo::showMessage(i18n("Sorry, wrong Input"), 3000, new KIcon("accessories-calculator"));
}
void KeyboardConfiguration::deleteTab()
{	
        int tabIndex = ui.cbTabs->currentIndex();
        setList.at(ui.cbSets->currentIndex())->getTabList()->removeAt(tabIndex);
        ui.cbTabs->removeItem(tabIndex);
}

void KeyboardConfiguration::cbSetsIndexChanged()
{
    refreshCbTabs();
}
void KeyboardConfiguration::refreshCbTabs()
{
    ui.cbTabs->clear();
    for(int i=0; i<setList.at(ui.cbSets->currentIndex())->getTabList()->size(); i++)
    {
        ui.cbTabs->addItem(setList.at(ui.cbSets->currentIndex())->getTabList()->at(i)->getTabName());
    }
}

void KeyboardConfiguration::addButton()
{
	bool ok;
	KeyboardAddButtonDLG *kab = new KeyboardAddButtonDLG(0,&ok);
	kab->show();
	kab->hide();
	if(ok)
	{
		//setList.at(ui.cbSets->currentIndex())->getTabList()->at(ui.cbTabs->currentIndex())->getButtonList()->append(new KeyboardButton(kab->getName(), kab->getTrigger(), kab->getValueType(), kab->getValue()));
	}
}
void KeyboardConfiguration::deleteButton()
{
	int indexOfButton = 0;//temp
	//TODO:get button index,... initiate qtablemodel for tvTabContent
        setList.at(ui.cbSets->currentIndex())->getTabList()->at(ui.cbTabs->currentIndex())->getButtonList()->removeAt(indexOfButton);
}
void KeyboardConfiguration::buttonUp()
{
	int indexOfButton = 0;//temp
	
	//TODO:get button index,... initiate qtablemodel for tvTabContent
        setList.at(ui.cbSets->currentIndex())->getTabList()->at(ui.cbTabs->currentIndex())->buttonLeft(indexOfButton);
}
void KeyboardConfiguration::buttonDown()
{
	int indexOfButton = 0;//temp
	//TODO:get button index,... initiate qtablemodel for tvTabContent
        setList.at(ui.cbSets->currentIndex())->getTabList()->at(ui.cbTabs->currentIndex())->buttonRight(indexOfButton);
}


void KeyboardConfiguration::save()
{
	Q_ASSERT(config);
	
	KConfigGroup cg(config, "");
	cg.writeEntry("Trigger", ui.leTrigger->text());

	cg.sync();
	
	emit changed(false);
}

void KeyboardConfiguration::destroy()
{
	deleteLater();
	instance=0;
}
 
void KeyboardConfiguration::load()
{
	Q_ASSERT(config);

	KConfigGroup cg(config, "");
	ui.leTrigger->setText(cg.readEntry("Trigger", i18n("Keyboard")));

	cg.sync();
	
	emit changed(false);
}
 
void KeyboardConfiguration::defaults()
{
	ui.leTrigger->setText(i18n("Keyboard"));
	save();
}

KeyboardConfiguration::~KeyboardConfiguration()
{
	
}