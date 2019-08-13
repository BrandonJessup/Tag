TEMPLATE = app
TARGET = Tag

QT = core gui widgets sql

SOURCES += \
    buttonpanel.cpp \
    database.cpp \
    filebrowser.cpp \
    filetuple.cpp \
    main.cpp \
    prompt.cpp \
    searchpanel.cpp \
    selectedpanel.cpp \
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
    prompt.h \
    searchpanel.h \
    selected.h \
    selectedpanel.h \
    tagadderdialog.h \
    tagcolor.h \
    taglist.h \
    tagnamenotfoundexception.h \
    tagpanel.h \
    tagtuple.h \
    toolbar.h \
    userrole.h \
    window.h
