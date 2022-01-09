TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

include(MinGL2/mingl.pri)

HEADERS += \
    check.h \
    bgtext.h \
    generate.h \
    menu.h \
    move.h \
    mystruct.h \
    principal.h

SOURCES += \
        generate.cpp \
        check.cpp \
        main.cpp \
        bgtext.cpp \
        menu.cpp \
        move.cpp \
        principal.cpp
