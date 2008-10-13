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


#ifndef INTERNETEXTENSIONSETTINGS_H
#define INTERNETEXTENSIONSETTINGS_H

#include "ui_internetextensiondlg.h"
#include <QWidget>
/**
	@author Peter Grasch <bedahr@gmx.net>
*/
class InternetExtensionSettings : public QWidget
{
Q_OBJECT
private:
	Ui::InternetExtensionDlg ui;
private slots:
	void makeExample();
public:
    InternetExtensionSettings(QWidget* parent);

    ~InternetExtensionSettings();

//     virtual bool apply();
//     virtual bool init();
//     virtual bool isComplete();
//     virtual bool reset();

};

#endif