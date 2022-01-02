TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        check.cpp \
        generate.cpp \
        main.cpp \
        bgtext.cpp \
        menu.cpp \
        move.cpp

include(/Users/elisee/Documents/SAE/menuCs/CASALISHOOTER/MinGL2/mingl.pri)

HEADERS += \
    bgtext.h \
    check.h \
    generate.h \
    menu.h \
    move.h \
    mystruct.h
