#-------------------------------------------------
#
# Project created by QtCreator 2016-11-13T15:22:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = audio_visualization-qt
TEMPLATE = app
LIBS += -lglut -lGL -lGLU -lasound -lfftw3 -lm -lpthread
QMAKE_CXXFLAGS += -std=c++14

SOURCES += main.cpp\
        mainwindow.cpp \
    ALSA.cpp \
    AudioInput.cpp \
    SpectrogramVisualizer.cpp \
    display.cpp


HEADERS  += mainwindow.h \
    ALSA.hpp \
    AudioInput.hpp \
    GraphicsItem.hpp \
    SpectrogramVisualizer.hpp \
    display.h \
    display_defines.h


FORMS    += mainwindow.ui
unix:!macx: LIBS += -L/usr/local/lib/ -lfftw3

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include

unix:!macx: PRE_TARGETDEPS += /usr/local/lib/libfftw3.a

unix:!macx: LIBS += -L/usr/lib/x86_64-linux-gnu/ -lfftw3f

INCLUDEPATH += /usr/lib/x86_64-linux-gnu
DEPENDPATH += /usr/lib/x86_64-linux-gnu

unix:!macx: PRE_TARGETDEPS += /usr/lib/x86_64-linux-gnu/libfftw3f.a

