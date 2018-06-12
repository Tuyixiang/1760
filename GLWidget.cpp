//
// Created by Yixiang Tu on 25/05/2018.
//

#include <QPainter>
#include <QMessageBox>
#include "GLWidget.h"
#include "scene/MainMenuScene.h"
#include "scene/ActionScene1.h"
#include "scene/PromptScene.h"


GLWidget::GLWidget() {
  activeScene = new MainMenuScene(this);
  //activeScene = new ActionScene1(this);
  activeScene->changeIn();
  DebugText::instance().setActiveScene(activeScene);
  setMouseTracking(true);
}

GLWidget::~GLWidget() {
  makeCurrent();
}

void GLWidget::initializeGL() {
  initializeOpenGLFunctions();
  //auto version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
  //if (version[0] <= '2') {
  //  QMessageBox mes;
  //  mes.setText("OpenGL version 3.3 or later is required.\nYour OpenGL version is: " + QString(version));
  //  mes.exec();
  //  terminate();
  //}
  connect(this, SIGNAL(frameSwapped()), this, SLOT(onFrame()));
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_CULL_FACE);
  //glEnable(GL_DEPTH_COMPONENT32);
  //glDepthFunc(GL_LEQUAL);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glDepthRangef(0, 1);
  //glEnable(GL_DEPTH);

  activeScene->onInitialize();
}

void GLWidget::resizeGL(int width, int height) {
  perspective.setToIdentity();
  perspective.perspective(45.0f, width / float(height), 0.0f, 1000.0f);
}

void GLWidget::paintGL() {

  //makeCurrent();

  glEnable(GL_MULTISAMPLE);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  //glEnable(GL_BLEND);
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  //glDepthMask(GL_TRUE);

  activeScene->render(perspective);
  renderText();
  activeScene->renderBlackage(perspective);
}

/**
 * Perform transformations and render graphic
 */
void GLWidget::onFrame() {

  activeScene->onFrame();

  // Schedule a refreshDraw
  QOpenGLWidget::update();

}

void GLWidget::keyPress(int key) {
  activeScene->keyPress(key);
}

void GLWidget::keyRelease(int key) {
  activeScene->keyRelease(key);
}

void GLWidget::renderText() {
  QPainter painter(this);
  activeScene->drawText(painter);
}

void GLWidget::mouseClick(const QPoint& position) {
  activeScene->mouseClick(position);
}

void GLWidget::mouseMove(const QPoint& position) {
  activeScene->mouseMove(position);
}

void GLWidget::mouseRelease(const QPoint& position) {
  activeScene->mouseRelease(position);
}

void GLWidget::changeScene(int sceneId, void* data /* = nullptr */) {

  static int targetScene;
  static void* _data;

  if (sceneId != -1) {
    changingScene = true;
    activeScene->changeOut();
    targetScene = sceneId;
    _data = data;
  } else {
    switch (targetScene) {
      case 100: {
        delete activeScene;
        auto index = (reinterpret_cast<int*>(_data));
        activeScene = new PromptScene(this, *index);
        delete index;
        break;
      }
      case 0: {
        delete activeScene;
        activeScene = new MainMenuScene(this);
        break;
      }
      case 1: {
        delete activeScene;
        activeScene = new ActionScene1(this);
        break;
      }
      case -100: {
        terminate();
        return;
      }
      default: {
        throw std::runtime_error("Scene not found");
      }
    }
    activeScene->changeIn();
    activeScene->onInitialize();
  }

  DebugText::instance().setActiveScene(activeScene);
}

void GLWidget::changeSceneImmediately(int sceneId, void* data) {

  switch (sceneId) {
    case 100: {
      auto x = *(reinterpret_cast<int*>(data));
      delete activeScene;
      activeScene = new PromptScene(this, x);
      break;
    }
    case 0: {
      delete activeScene;
      activeScene = new MainMenuScene(this);
      break;
    }
    case 1: {
      delete activeScene;
      activeScene = new ActionScene1(this);
      break;
    }
    default: {
      throw std::runtime_error("Scene not found");
    }
  }
  //activeScene->changeIn();
  activeScene->onInitialize();


  DebugText::instance().setActiveScene(activeScene);
}

void GLWidget::nextScene() {
  changeScene(1, nullptr);
}


