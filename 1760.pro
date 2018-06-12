#-------------------------------------------------
#
# Project created by QtCreator 2018-06-08T22:28:46
#
#-------------------------------------------------

QT       += core
QT       -= gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 1760
TEMPLATE = app
LIBS += /Users/yixiang/etc/Box2D/libliquidfun.a
INCLUDEPATH += /Users/yixiang/etc/Box2D

CONFIG += release
CONFIG-=app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG(release, debug|release) {
    CONFIG += optimize_full
    DEFINES += NDEBUG
}

SOURCES += \
        main.cpp \
        GLWidget.cpp \
        Transform3D.cpp \
        global/Message.cpp \
        global/Timer.cpp \
        model/Blackage.cpp \
        model/GlossyBackground.cpp \
        model/GlossyShard.cpp \
        model/Pollution.cpp \
        model/character/Bird.cpp \
        model/character/Protagonist.cpp \
        model/character/Tree.cpp \
        model/character/TreeTrunk.cpp \
        model/environment/Wall.cpp \
        scene/ActionScene1.cpp \
        scene/MainMenuScene.cpp \
        scene/PromptScene.cpp \
        template/BBody.cpp \
        template/BCharacter.cpp \
        template/Body.cpp \
        template/BodyPart.cpp \
        template/BPolygon.cpp \
        template/BWorldScene.cpp \
        template/Scene.cpp \
        template/Text.cpp \
        text/DebugText.cpp \
        text/Fonts.cpp \
        vertex/OscillatingVertex.cpp

HEADERS += \
        GLVertex.h \
        GLWidget.h \
        KeyMonitor.h \
        MainWindow.h \
        Transform3D.h \
        Vertex.h \
        global/Colors.h \
        global/GameGlobals.h \
        global/Macro.h \
        global/Math.h \
        global/Message.h \
        global/Random.h \
        global/Timer.h \
        model/Blackage.h \
        model/GlossyBackground.h \
        model/GlossyShard.h \
        model/Pollution.h \
        model/ShaderSource.h \
        model/character/Bird.h \
        model/character/Protagonist.h \
        model/character/Tree.h \
        model/character/TreeTrunk.h \
        model/environment/Wall.h \
        scene/ActionScene1.h \
        scene/MainMenuScene.h \
        scene/PromptScene.h \
        template/BBody.h \
        template/BCharacter.h \
        template/Body.h \
        template/BodyPart.h \
        template/BPolygon.h \
        template/BWorldScene.h \
        template/Scene.h \
        template/Text.h \
        text/DebugText.h \
        text/Fonts.h \
        vertex/OscillatingVertex.h

RESOURCES += \
    res.qrc
