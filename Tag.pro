TEMPLATE = app
TARGET = Tag

QT = core gui widgets sql

RC_ICONS = icon.ico

SOURCES += \
    buttonpanel.cpp \
    database.cpp \
    filebrowser.cpp \
    filetuple.cpp \
    imagetagadderdialog.cpp \
    main.cpp \
    missingfiledialog.cpp \
    prompt.cpp \
    searchpanel.cpp \
    selectedpanel.cpp \
    settings.cpp \
    tagadderdialog.cpp \
    taglist.cpp \
    tagnamenotfoundexception.cpp \
    tagpanel.cpp \
    tagtuple.cpp \
    toolbar.cpp \
    window.cpp

HEADERS += \
    buttonpanel.h \
    database.h \
    filebrowser.h \
    filetuple.h \
    imagetagadderdialog.h \
    missingfiledialog.h \
    prompt.h \
    searchpanel.h \
    selected.h \
    selectedpanel.h \
    settings.h \
    tagadderdialog.h \
    tagcolor.h \
    taglist.h \
    tagnamenotfoundexception.h \
    tagpanel.h \
    tagtuple.h \
    toolbar.h \
    userrole.h \
    window.h
