/***************************************************************************
*   Copyright (C) 2006 by Peter Grasch   *
*   bedahr@gmx.net   *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef SIMONCONTROL_H
#define SIMONCONTROL_H

/**
 *	@class SimonControl
 *	@brief The Main Control Class
 *
 * 	The Main "Control" Class. It handles all the GUI Signals and operates
 * 	accordingly. It is the main point of the simon application and as such
 * 	ties all the individual parts together
 *
 *	@version 0.1
 *	@date 07.01.2006
 *	@author Peter Grasch
 *	@todo Implementing functions
*/

#include <QMessageBox>
#include <QObject>
#include "simoninfo.h"
#include "addwordview.h"
#include "miccontrol.h"
#include "runcommand.h"
#include "eventhandler.h"
#include "juliuscontrol.h"


class SimonControl : public QObject {
	Q_OBJECT

public slots:
	void connectedToJulius();
	void disconnectedFromJulius();
	void wordRecognised(QString word);
private:
	bool active; //!< Is active?
	MicControl *mic; //!< Mic Handle
	JuliusControl *julius; //!< Julius Backend
	RunCommand *run; //!< Runs the commands
	EventHandler *eventHandler; //!< simulates keystrokes,etc.
	void initializeMic();
	
public:
	
	bool deactivateSimon();
	bool activateSimon();

	bool toggleActivition();
	bool getActivitionState();

	SimonControl();
	
	~SimonControl();

};

#endif
