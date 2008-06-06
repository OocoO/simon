//
// C++ Implementation: selectprogrampage
//
// Description:
//
//
// Author: Peter Grasch <bedahr@gmx.net>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "selectprogrampage.h"
#include <QMessageBox>

#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QListWidget>
#include <QVBoxLayout>
#include <QWidget>

#ifdef linux
#include "../../SimonLib/ProgramManager/kdeprogrammanager.h"
#endif
#ifdef __WIN32
#include "../../SimonLib/ProgramManager/windowsprogrammanager.h"
#endif

/**
*   \brief Constructor
            Creates the wizardpage, where you can select a special categorie (audio, office, etc.).
            To this categorie you get a list of programs, which provides standardformats of this categorie.
*
*   @author Susanne Tschernegg, Peter Grasch
*   @param QWidget *parent
*/
SelectProgramPage::SelectProgramPage(QWidget* parent): QWizardPage(parent)
{
	ui.setupUi(this);
#ifdef linux
	this->programManager = new KDEProgramManager();
#endif
#ifdef __WIN32
	this->programManager = new WindowsProgramManager();
#endif

        registerField("executable*", ui.lwPrograms);

        connect(ui.lwCategories, SIGNAL(itemSelectionChanged()), this, SLOT(searchForPrograms()));
}

/**
 * \brief Initializes the page (under linux this loads the list of programs)
 * \author Peter Grasch
 */
void SelectProgramPage::initializePage()
{
	ProgramCategoryList list = programManager->readCategories();
	if (list.isEmpty()) 
		QMessageBox::critical(this, tr("Konnte keine Programmkategorien finden"), tr("Konnte keine Programmkategorien finden.\n\nM�glicherweise ist der Pfad zur categories.xml falsch gesetzt."));
	else {
		this->insertCategories(list);
		#ifdef linux
			((KDEProgramManager*) this->programManager)->loadPrograms();
		#endif
	}

}

/**
*   \brief destructor
*
*   @author Susanne Tschernegg
*/
SelectProgramPage::~SelectProgramPage()
{
    delete programManager;
}

/**
*   \brief gets the whole exe-name of the program (e.g. program.exe)
*
*   @author Susanne Tschernegg
*   @return QStirng
*       returns the name of the .exe file
*/
QString SelectProgramPage::getExecPath()
{
    QString exeStr = ui.lwPrograms->currentItem()->data(Qt::UserRole).toString();
    return exeStr;
}

/**
*   \brief gets the iconsrc of the program
*
*   @author Peter Grasch
*/
QString SelectProgramPage::getIcon()
{
    return ui.lwPrograms->currentItem()->data(Qt::UserRole+1).toString();
}


/**
*   \brief gets the name of the program
*
*   @author Susanne Tschernegg
*   @return QString
*       returns the name of the program
*/
QString SelectProgramPage::getName()
{
    return ui.lwPrograms->currentItem()->text();
}

/**
*   \brief inserts the different categories, which were listed in the categorieList.
*
*   @author Susanne Tschernegg
*   @param ProgramCategoryList categorieList
*       holds the categories, which where read out of a xml-file
*/
void SelectProgramPage::insertCategories(ProgramCategoryList categorieList)
{
    ui.lwCategories->clear();
    QListWidgetItem* item;
    for(int i=0; i<categorieList.count(); i++)
    {
        item = new QListWidgetItem(ui.lwCategories);
        item->setText(categorieList.at(i).getName());
        item->setData(Qt::UserRole, categorieList.at(i).getDescription());
        item->setIcon(categorieList.at(i).getIcon());
    }
}

/**
*   \brief inserts all given programms in a list
*
*   @author Susanne Tschernegg+
*   @param ProgramList *programList
*       is a list, which holds all programms of a specified category
*/
void SelectProgramPage::insertPrograms(ProgramList *programList)
{
    ui.lwPrograms->clear();
    QListWidgetItem* lwItem;
    for (int i=0; i<programList->count(); i++)
    {
        lwItem = new QListWidgetItem(ui.lwPrograms);
        lwItem->setText(programList->at(i).getName());
	lwItem->setIcon(programList->at(i).getIcon());
        lwItem->setData(Qt::UserRole, programList->at(i).getExec());
        lwItem->setData(Qt::UserRole+1, programList->at(i).getIconPath());
        lwItem->setData(Qt::UserRole+2, programList->at(i).getPath());
    }
}

/**
*   \brief searches for all programs, which contains the associated formats of a category
*
*   @author Susanne Tschernegg
*/
void SelectProgramPage::searchForPrograms()
{
    QString catName = ui.lwCategories->currentItem()->text();
    ProgramCategoryList catList = programManager->readCategories();
    for(int i=0; i<catList.count(); i++)
    {
        if(catName == catList.at(i).getName())
        {
            ProgramList *pl = programManager->getPrograms(catList.at(i));
            insertPrograms(pl);
	    delete pl;
            break;
        }
    }
}

/**
*   \brief returns the workingdirectory, which the user set
*
*   @author Susanne Tschernegg
*   @return QString
*       returns the workingdirectory
*/
QString SelectProgramPage::getWorkingDirectory()
{
	return ui.lwPrograms->currentItem()->data(Qt::UserRole+2).toString();
}
