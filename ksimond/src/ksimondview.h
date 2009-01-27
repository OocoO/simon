/*
 *  Copyright (C) 2008 Peter Grasch <grasch@simon-listens.org>
 *  
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2,
 *  or (at your option) any later version, as published by the Free
 *  Software Foundation
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details
 * 
 *  You should have received a copy of the GNU General Public
 *  License along with this program; if not, write to the
 *  Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */


#ifndef KSIMONDVIEW_H
#define KSIMONDVIEW_H

#include <QWidget>
#include <QProcess>
#include <trayiconmanager.h>

class KProcess;
class KAction;
class QCloseEvent;
class KCMultiDialog;
/**
 * This is the main view class for ksimond.  Most of the non-menu,
 * non-toolbar, and non-statusbar (e.g., non frame) GUI code should go
 * here.
 *
 * @short Main view
 * @author Peter Grasch <grasch@simon-listens.org>
 * @version 0.1
 */

class KSimondView : public QObject
{
    Q_OBJECT
public:
    /**
     * Default constructor
     */
    KSimondView(QObject* parent=0);

    /**
     * Destructor
     */
    virtual ~KSimondView();

private slots:
    void showConfigurationDialog();
    void startSimond();
    void restartSimond();
    void stopSimond();
    void simondFinished();

    void matchDisplayToState();
    void slotError(QProcess::ProcessError err);

protected:
	void closeEvent(QCloseEvent*);
	
private:
    TrayIconManager *trayIconMgr;
	KCMultiDialog *configDialog;
    KProcess *process;
    KAction *startProcess, *restartProcess, *stopProcess, *configure;
    bool stopIntended;
    bool wantReload;
};

#endif // ksimondVIEW_H
