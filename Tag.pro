TEMPLATE = app
TARGET = Tag

QT = core gui widgets sql

RC_ICONS = icon.ico

VERSION = 0.8.0.0

SOURCES += \
    buttonpanel.cpp \
    database.cpp \
    filebrowser.cpp \
    filetuple.cpp \
    imagetagadderdialog.cpp \
    main.cpp \
    missingfiledialog.cpp \
    progressdialog.cpp \
    prompt.cpp \
    searchpanel.cpp \
    selectedpanel.cpp \
    settings.cpp \
    tagadderdialog.cpp \
    taglist.cpp \
    tagnamenotfoundexception.cpp \
    tagpanel.cpp \
    tagtuple.cpp \
    thumbnailmanager.cpp \
    thumbnailslider.cpp \
    toolbar.cpp \
    window.cpp

HEADERS += \
    buttonpanel.h \
    database.h \
    filebrowser.h \
    filetuple.h \
    imagetagadderdialog.h \
    missingfiledialog.h \
    progressdialog.h \
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
    thumbnailmanager.h \
    thumbnailslider.h \
    toolbar.h \
    userrole.h \
    window.h
