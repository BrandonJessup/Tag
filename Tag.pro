TEMPLATE = app
TARGET = Tag

QT = core gui widgets sql

SOURCES += \
    buttonpanel.cpp \
    database.cpp \
    filebrowser.cpp \
    filetuple.cpp \
    main.cpp \
    searchpanel.cpp \
    selectedpanel.cpp \
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
    searchpanel.h \
    selected.h \
    selectedpanel.h \
    tagcolor.h \
    taglist.h \
    tagnamenotfoundexception.h \
    tagpanel.h \
    tagtuple.h \
    toolbar.h \
    userrole.h \
    window.h
