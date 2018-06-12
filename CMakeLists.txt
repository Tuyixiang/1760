#   In Preference -> Build, Execution, Deployment -> Cmake
#   Set CMake options:
#   -DCMAKE_PREFIX_PATH=.../Qt/5.11.0/clang_64/lib/cmake
cmake_minimum_required(VERSION 3.9)
project(_1760)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_FLAGS "-fstack-protector-all")

find_package(Qt5Widgets CONFIG REQUIRED)

#   Direction to Box2D and library
INCLUDE_DIRECTORIES(/Users/yixiang/etc/Box2D)
LINK_DIRECTORIES(/Users/yixiang/etc/Box2D)

add_executable(_1760
        main.cpp
        global/Colors.h
        global/Message.cpp global/Message.h
        global/Macro.h
        global/Random.h
        global/Timer.cpp global/Timer.h
        model/character/Bird.cpp model/character/Bird.h
        model/character/Protagonist.cpp model/character/Protagonist.h
        model/environment/Wall.cpp model/environment/Wall.h
        model/Blackage.cpp model/Blackage.h
        model/GlossyBackground.cpp model/GlossyBackground.h
        model/GlossyShard.cpp model/GlossyShard.h
        model/Pollution.cpp model/Pollution.h
        model/ShaderSource.h
        scene/ActionScene1.cpp scene/ActionScene1.h
        scene/MainMenuScene.cpp scene/MainMenuScene.h
        template/Body.cpp template/Body.h
        template/BBody.cpp template/BBody.h
        template/BPolygon.cpp template/BPolygon.h
        template/BodyPart.cpp template/BodyPart.h
        template/BCharacter.cpp template/BCharacter.h
        template/Scene.cpp template/Scene.h
        template/BWorldScene.cpp template/BWorldScene.h
        template/Text.cpp template/Text.h
        text/Fonts.cpp text/Fonts.h
        text/DebugText.cpp text/DebugText.h
        GLWidget.cpp GLWidget.h
        GLVertex.h
        Transform3D.cpp Transform3D.h
        MainWindow.h
        KeyMonitor.h
        Vertex.h
        vertex/OscillatingVertex.cpp vertex/OscillatingVertex.h
        global/Math.h model/character/Tree.cpp model/character/Tree.h scene/PromptScene.cpp scene/PromptScene.h model/character/TreeTrunk.cpp model/character/TreeTrunk.h global/GameGlobals.h)
        #obsolete/GroupedBody.h obsolete/GroupedBody.cpp
        #obsolete/SampleBody.cpp obsolete/SampleBody.h
        #model/NullBody.cpp model/NullBody.h
target_link_libraries(_1760 Qt5::Widgets libliquidfun.a)