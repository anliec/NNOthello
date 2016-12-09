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

#comment to disable Intel IPP
CONFIG += IPP

#to build using IPP
IPP {
    #add a define to use IPP function in NN sources
    DEFINES += USE_INTEL_IPP
    #add build path to IPP (using default IPP Linux path)
    unix:!macx {
        LIBS += -I/opt/intel/ipp/include -L/opt/intel/ipp/lib/intel64 -lippi -lipps -lippvm -lippcore -lm -lpthread

        INCLUDEPATH += /opt/intel/ipp/include
        DEPENDPATH += /opt/intel/ipp/include
    }
    #TODO: add build option for other OSs
}
