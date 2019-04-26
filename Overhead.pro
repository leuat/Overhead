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


#system($$PWD/resources/compile.sh):HAS_BIN=FALSE

linux*{
    QMAKE_CXXFLAGS += -fopenmp
    QMAKE_CXXFLAGS +=  -Wno-unused-variable -Wno-unused-parameter -Wno-sign-compare -Wno-comment -Wno-parentheses -Wno-delete-non-virtual-dtor -Wno-missing-noreturn
#    LIBS += -fopenmp
#    QMAKE_CXXFLAGS +=  -Ofast
    QMAKE_CXXFLAGS +=  -Os  -fno-stack-protector  -ffunction-sections -fdata-sections -Wl,--gc-sections  -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-math-errno  -fmerge-all-constants
    QMAKE_CXXFLAGS += -fno-ident  -fsingle-precision-constant  -ffast-math  -Wl,-z,norelro  -Wl,--hash-style=gnu
#    QMAKE_CXXFLAGS += -s -Wl,-verbose -Wl,-Bstatic
    LIBS += -lGLEW -lGLU -lGL -lglfw

    LIBS += -L$$PWD/../libxm/build-prod/src -lxms  -lasound -ljack
    LIBS += -lfreetype

#    LIBS += -lGL
#    LIBS += -ldl
    INCLUDEPATH +=$$PWD/../libxm/include/
    INCLUDEPATH += /usr/include/freetype2

}
win32-msvc*{
#    QMAKE_CXXFLAGS += -openmp
#     LIBS += -fopenmp
#    QMAKE_CXXFLAGS +=  -Ofast
#    QMAKE_CXXFLAGS +=  -Os  -fno-stack-protector  -ffunction-sections -fdata-sections   -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-math-errno  -fmerge-all-constants
#    QMAKE_CXXFLAGS += -fno-ident  -fsingle-precision-constant  -ffast-math
#    QMAKE_CXXFLAGS += -s -Wl,-verbose -Wl,-Bstatic
    QMAKE_CXXFLAGS += -O1  -fno-stack-protector  -ffunction-sections -fdata-sections
    LIBS += -L$$PWD/libs/glew-2.1.0/ -L$$PWD/libs/glfw-3.3.bin.WIN64/ -lOpenGL32  -lGLU32 -lglew32ss  -lglfw3
 #   LIBS += -lgdi32 -lshell32 -lvcruntime -lmsvcrt -lUser32
    LIBS +=  -lUser32 -lgdi32 -lshell32

   QMAKE_CXXFLAGS += -GL -GF- Gy -GA

# /GL /Os /GF /Gy /GA. In the linker you more or less want /OPT:REF and /OPT:ICF and /LTCG.
    LIBS += -OPT:REF -OPT:ICF -LTCG -VERBOSE:UNUSEDLIBS

    LIBS += -L$$PWD/libs/libxm/src/Release -lxms


    INCLUDEPATH +=$$PWD/libs/glew-2.1.0/include/
    INCLUDEPATH +=$$PWD/libs/glfw-3.3.bin.WIN64/include/
    INCLUDEPATH +=$$PWD/libs/glm

    INCLUDEPATH +=$$PWD/libs/libxm/include/
    LIBS += -lwinmm

}


SOURCES += \
        main.cpp \
    source/shader/shader.cpp \
    source/lglwrap.cpp \
    source/lxm.cpp \
    source/engine/lglobject.cpp \
    source/scene1.cpp \
    source/abstractscene.cpp \
    source/uniform.cpp \
    source/engine/lphysics.cpp \
 #   source/math/vmath.cpp
    source/engine/lfontrenderer.cpp

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
    source/engine/lphysics.h \
    source/engine/lfontrenderer.h

