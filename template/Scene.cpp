//
// Created by Yixiang Tu on 28/05/2018.
//

#include "Scene.h"
#include "../GLWidget.h"
#include "../model/Blackage.h"
#include "../scene/PromptScene.h"

Scene::~Scene() {
  for (auto* p: bodyList) {
    delete p;
  }
  bodyList = std::vector<Body*>();
  for (auto* p: textList) {
    delete p;
  }
  textList = std::vector<Text*>();
}

const int Scene::height() const {
  return _parent->height();
}

const int Scene::width() const {
  return _parent->width();
}

void Scene::render(const QMatrix4x4& perspective) {
  for (auto it = bodyList.begin(); it != bodyList.end();) {
    if ((*it)->toBeRemoved()) {
      delete (*it);
      it = bodyList.erase(it);
    } else if (!(*it)->initialized()) {
      (*it)->initializeShader();
    } else {
      (*it)->draw(perspective, camera.matrix(), uniformLight, light, _parent);
      it++;
    }
  }
}

void Scene::renderBlackage(const QMatrix4x4& perspective) {
  if (blackage and !blackage->initialized()) {
    blackage->initializeShader();
  }
  if (blackageSizing == 1) {
    auto newT3D = camera;
    newT3D.setPosition(0, 0, -2);
    newT3D.setRotation(QQuaternion());
    blackage->draw(perspective, newT3D.matrix(), uniformLight, light, _parent);
    if (blackage->transform().size().x() >= 1) {
      blackageSizing = 0;
      delete blackage;
      blackage = nullptr;
      SM("Blackage destroyed")
      _parent->changeScene(-1, nullptr);
    } else {
      blackage->transform().grow(0.002f, 0.002f, 0);
      blackage->transform().scale(1.02f);
    }
  } else if (blackageSizing == -1) {
    auto newT3D = camera;
    newT3D.setPosition(0, 0, -2);
    newT3D.setRotation(QQuaternion());
    blackage->draw(perspective, newT3D.matrix(), uniformLight, light, _parent);
    if (blackage->transform().size().x() <= 0.002f) {
      blackageSizing = 0;
      delete blackage;
      blackage = nullptr;
      SM("Blackage destroyed")
    } else {
      blackage->transform().scale(1 / 1.02f);
      blackage->transform().grow(-0.002f, -0.002f, 0);
    }
  }
}

bool Scene::keyPress(int key) {
  keyMonitor.keyPress(key);
  switch (key) {
#ifndef NDEBUG
    case Qt::Key_0: {
      _parent->changeScene(0, nullptr);
      return true;
    }
    case Qt::Key_1: {
      _parent->changeScene(1, nullptr);
      return true;
    }
    case Qt::Key_L: {
      _parent->changeScene(100, new int(PromptScene::DefaultPrompts::credit));
      return true;
    }
#endif
    case Qt::Key_Backslash: {
      DebugText::instance().changeVisibility();
      return true;
    }
    default: {
      return false;
    }
  }
}

bool Scene::keyRelease(int key) {
  keyMonitor.keyRelease(key);
  return false;
}

void Scene::changeOut() {

  if (!blackage) {
    blackage = new Blackage(this, idDistributor++, Blackage::fadeOut);
    blackage->transform().setSize(0.01f);
  } else {
    blackage->setStyle(Blackage::fadeOut);
  }
  blackageSizing = 1;

}

void Scene::changeIn() {

  blackage = new Blackage(this, idDistributor++, Blackage::fadeIn);
  blackageSizing = -1;

}

void Scene::drawText(QPainter& painter) {
  for (auto* text: textList) {
    text->draw(painter);
  }

  //  This debug text should be in the top layer
  DebugText::instance().draw(painter);
}
