message ( "Processing Configuration..." )

FORMS += 	Configuration/externalprogramms.ui \
		Configuration/generalsettingsdlg.ui \
		Configuration/internetextensiondlg.ui \
		Configuration/logmanagerdlg.ui \
		Configuration/networksettingsdlg.ui \
		Configuration/passwordsettingsdlg.ui \
		Configuration/systemviewdlg.ui

HEADERS += 	Configuration/externalprogrammanager.h \
		Configuration/generalsettings.h \
		Configuration/internetextensionsettings.h \
		Configuration/networksettings.h \
		Configuration/passwordsettings.h \
		Configuration/systemview.h  \
		Configuration/logview.h \
		Configuration/FirstRun/firstrunimportbomppage.h 

SOURCES += 	Configuration/externalprogrammanager.cpp \
		Configuration/generalsettings.cpp \
		Configuration/internetextensionsettings.cpp \
		Configuration/networksettings.cpp \
		Configuration/passwordsettings.cpp \
		Configuration/systemview.cpp  \
		Configuration/logview.cpp 

QT += network

include(Configuration/FirstRun/FirstRun.pri)