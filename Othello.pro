#-------------------------------------------------
#
# Project created by QtCreator 2014-12-06T10:20:38
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Othello
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    jeux.cpp \
    mygraphicsview.cpp \
    plateau.cpp \
    point.cpp \
    tableponderationia.cpp \
    pointjoueur.cpp \
    config/config.cpp \
    NeuraleNetwork/NeuralNetwork.cpp \
    NeuraleNetwork/Neuron.cpp \
    NeuraleNetwork/Neuronlayer.cpp \
    NeuraleNetwork/SaveManager.cpp \
    NeuralAI.cpp \
    Tournament.cpp \
    GameAI.cpp \
    MinMaxAI.cpp \
    BasicAI.cpp \
    RobionAI.cpp

HEADERS  += mainwindow.h \
    jeux.h \
    mygraphicsview.h \
    plateau.h \
    point.h \
    tableponderationia.h \
    pointjoueur.h \
    config/config.h \
    NeuraleNetwork/NeuralNetwork.h \
    NeuraleNetwork/Neuron.h \
    NeuraleNetwork/Neuronlayer.h \
    NeuraleNetwork/SaveManager.h \
    NeuralAI.h \
    Tournament.h \
    GameAI.h \
    MinMaxAI.h \
    BasicAI.h \
    RobionAI.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 


LIBS += -I/opt/intel/ipp/include -L/opt/intel/ipp/lib/intel64 -lippi -lipps -lippcore -lm -lpthread

INCLUDEPATH += /opt/intel/ipp/include
DEPENDPATH += /opt/intel/ipp/include
