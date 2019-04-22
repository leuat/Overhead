QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle



# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += IS_DEBUG
DEFINES += GLM_ENABLE_EXPERIMENTAL
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#linux-g*{
    QMAKE_CXXFLAGS += -fopenmp
    QMAKE_CXXFLAGS +=  -Wno-unused-variable -Wno-unused-parameter -Wno-sign-compare -Wno-comment -Wno-parentheses -Wno-delete-non-virtual-dtor -Wno-missing-noreturn
#    LIBS += -fopenmp
#    QMAKE_CXXFLAGS +=  -Ofast
    QMAKE_CXXFLAGS +=  -Os  -fno-stack-protector  -ffunction-sections -fdata-sections -Wl,--gc-sections  -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-math-errno  -fmerge-all-constants
    QMAKE_CXXFLAGS += -fno-ident  -fsingle-precision-constant  -ffast-math  -Wl,-z,norelro  -Wl,--hash-style=gnu
#    QMAKE_CXXFLAGS += -s -Wl,-verbose -Wl,-Bstatic
    LIBS += -lGLEW -lGLU -lGL -lglfw

    LIBS += -L$$PWD/../libxm/build-prod/src -lxms  -lasound -ljack

#    LIBS += -lGL
#    LIBS += -ldl


#}
INCLUDEPATH +=$$PWD/../libxm/include/


SOURCES += \
        main.cpp \
    source/shader/shader.cpp \
    source/lglwrap.cpp \
    source/lxm.cpp \
    source/engine/lglobject.cpp \
    source/scene1.cpp \
    source/abstractscene.cpp \
    source/uniform.cpp \
    source/engine/lphysics.cpp
 #   source/math/vmath.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
#    source/math/vmath.h
    source/shader/shader.h \
    source/lglwrap.h \
    source/lxm.h \
    source/engine/lglobject.h \
    source/Scene1.h \
    source/abstractscene.h \
    source/uniform.h \
    source/engine/lphysics.h

