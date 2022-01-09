macos:LIBS += -L"/usr/local/opt/freeglut/lib" -L"/usr/local/opt/sfml/lib" -framework OpenGL
LIBS += -lglut -lsfml-audio
!macos:LIBS += -lGLU -lGL

INCLUDEPATH += $$PWD/include/
macos:INCLUDEPATH += /usr/local/opt/freeglut/include /usr/local/opt/sfml/include

SOURCES += \
    $$PWD/src/audio/audioengine.cpp \
    $$PWD/src/exception/cexception.cpp \
    $$PWD/src/mingl.cpp \
    $$PWD/src/event/event_manager.cpp \
    $$PWD/src/shape/circle.cpp \
    $$PWD/src/shape/line.cpp \
    $$PWD/src/shape/rectangle.cpp \
    $$PWD/src/shape/triangle.cpp \
    $$PWD/src/shape/shape.cpp \
    $$PWD/src/graphics/rgbacolor.cpp \
    $$PWD/src/graphics/vec2d.cpp \
    $$PWD/src/gui/glut_font.cpp \
    $$PWD/src/gui/sprite.cpp \
    $$PWD/src/gui/text.cpp \
    $$PWD/src/transition/transition.cpp \
    $$PWD/src/transition/transition_contract.cpp \
    $$PWD/src/transition/transition_engine.cpp

HEADERS += \
    $$PWD/include/mingl/audio/audioengine.h \
    $$PWD/include/mingl/exception/cexception.h \
    $$PWD/include/mingl/exception/cexception.hpp \
    $$PWD/include/mingl/exception/errcode.h \
    $$PWD/include/mingl/macros.h \
    $$PWD/include/mingl/mingl.h \
    $$PWD/include/mingl/event/event.hpp \
    $$PWD/include/mingl/event/event_manager.h \
    $$PWD/include/mingl/shape/circle.h \
    $$PWD/include/mingl/shape/line.h \
    $$PWD/include/mingl/shape/rectangle.h \
    $$PWD/include/mingl/shape/triangle.h \
    $$PWD/include/mingl/shape/shape.h \
    $$PWD/include/mingl/graphics/idrawable.h \
    $$PWD/include/mingl/graphics/rgbacolor.h \
    $$PWD/include/mingl/graphics/vec2d.h \
    $$PWD/include/mingl/gui/glut_font.h \
    $$PWD/include/mingl/gui/sprite.h \
    $$PWD/include/mingl/gui/text.h \
    $$PWD/include/mingl/tools/ieditable.h \
    $$PWD/include/mingl/tools/ieditable.hpp \
    $$PWD/include/mingl/tools/ifonctorunaire.hpp \
    $$PWD/include/mingl/transition/itransitionable.h \
    $$PWD/include/mingl/transition/transition.h \
    $$PWD/include/mingl/transition/transition_contract.h \
    $$PWD/include/mingl/transition/transition_engine.h \
    $$PWD/include/mingl/transition/transition_types.h
