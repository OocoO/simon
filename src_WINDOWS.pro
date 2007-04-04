# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: .
# Target is an application:  ./bin/simon
FORMS += ui/main.ui \
         ui/wordlist.ui \
         ui/rundialog.ui \
         ui/addword.ui \
         ui/settings.ui \
         ui/trainmain.ui
HEADERS += simonview.h \
           addwordview.h \
           simoncontrol.h \
           simoninfo.h \
           wordlistview.h \
           trainingview.h \
           juliuscontrol.h \
           wordlistmanager.h \
           command.h \
           directsoundbackend.h \
           miccontrol.h \
           modelmanager.h \
           runcommand.h \
           trainingmanager.h \
           trainingtext.h \
           soundbackend.h  \
           word.h \
           eventhandler.h \
           trayiconmanager.h \
           osd.h \
	   wavrecorder.h \
           dragtablewidget.h \
           droplistwidget.h \
           runapplicationview.h \
	   runwindowsbackend.h \
           runbackend.h \
           vumeter.h \
	   wav.h \
           settingsview.h \
           settingsmanager.h
SOURCES += main.cpp \
           simonview.cpp \
           addwordview.cpp \
           simoncontrol.cpp \
           simoninfo.cpp \
           wordlistview.cpp \
           trainingview.cpp \
           juliuscontrol.cpp \
           wordlistmanager.cpp \
           directsoundbackend.cpp \
           miccontrol.cpp \
           modelmanager.cpp \
           runcommand.cpp \
           trainingmanager.cpp \
           trainingtext.cpp \
           trayiconmanager.cpp \
           eventhandler.cpp \
           osd.cpp \
           dragtablewidget.cpp \
           droplistwidget.cpp \
           runapplicationview.cpp \
	   runwindowsbackend.cpp \
	   wav.h \
	   wavrecorder.cpp \
           settingsview.cpp \
           settingsmanager.cpp \
           vumeter.cpp
#INCLUDEPATH += /usr/include/alsa /usr/include/qt4/QtNetwork
#LIBS += -L/usr/lib/alsa-lib -lasound
QT += network xml
RESOURCES += simon.qrc
TARGET = ./bin/simon
