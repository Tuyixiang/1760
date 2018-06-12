//
// Created by Yixiang Tu on 31/05/2018.
//

#include "MainMenuScene.h"
#include "../text/Fonts.h"
#include "../model/GlossyBackground.h"
#include "../model/GlossyShard.h"
#include "../GLWidget.h"
#include "../global/Math.h"
#include "../global/GameGlobals.h"

MainMenuScene::MainMenuScene(GLWidget* parent) : Scene(parent) {

  lastMousePosition = QPoint(width() / 2, height() / 2);

  /// Set light source position
  light = QVector4D(0, 0, 1, 10000);
  uniformLight = QVector3D(0, 0, 1);

  /// Add bodies
  /*
   *  Bodies later in the list will be shown above others,
   *    regardless of their z-value.
   */
  auto background = new GlossyBackground(this, idDistributor++);
  background->setSize(20, 12, 20, 16);
  background->setColor(QVector4D(0, 0.3, 0.9, 1), QVector4D(0.1, 0.7, 1, 1));
  background->setPositionPeriod(160, 360);
  background->setColorPeriod(240, 480);
  background->setOscilationRange(QVector3D(0.15, 0.15, 0.5));
  background->transform().setPosition(0, 0, -10);
  bodyList.push_back(background);
  //bodyList.push_back(new SampleBody(this, 0));

  /// Add texts (above bodies)
  textList.push_back(new fonts::mmScene::Title(this));
  textList.push_back(new fonts::mmScene::Hint(this));

  GameGlobals::instance().reset();

}

bool MainMenuScene::keyPress(int key) {
  keyMonitor.keyPress(key);
  switch(key) {
    case Qt::Key_Escape: {
      _parent->changeScene(-100);
      return true;
    }
    case Qt::Key_Return: {
      _parent->changeScene(1);
      return true;
    }
    default: {
      return Scene::keyPress(key);
    }
  }
}

void MainMenuScene::cleanBoxes() {
  while (bodyList.size() > 1) {
    delete bodyList.back();
    bodyList.pop_back();
  }
}

void MainMenuScene::mouseMove(const QPoint& position) {
  //DebugText::instance().showInstantMessage(QString::number(position.x()) + " " + QString::number(position.y()));
  lastMousePosition = position;
  const QVector2D&& mouseTarget = QVector2D(position.x() - width() / 2, height() / 2 - position.y());
  QVector2D moveDisplacement = mouseTarget - lastCameraTarget;

  if ((lastCameraTarget - moveDisplacement).length() <= 0.1f) {
    lastCameraTarget = moveDisplacement;
  } else {
    lastCameraTarget += moveDisplacement / 60;
  }

  camera.setRotation(lastCameraTarget.length() * 8 / height(),
                     QVector3D::normal(QVector3D(0, 0, 1), QVector3D(lastCameraTarget, 0)));
}

void MainMenuScene::onFrame() {

  if (!mouseMoved) {
    mouseMove(lastMousePosition);
  }
  mouseMoved = false;

  /// Add body
  if (Random::instance().getFloat() < 1.0f / 15) {
    bodyList.push_back(new GlossyShard(this, idDistributor++));
  }
  //delete bodyList[0];
  //bodyList[0] = new BodyPuppet(this, idDistributor++);

  /// Body animation
  for (auto* body: bodyList) {
    body->onFrame();
  }

  //  Can also directly control the bodies here, for example
  //  bodyList[1]->transform().translate(0, 0.01, 0);

  /// Light source animation
  static int theta = 0;
  light = QVector4D(3 * cos(theta), 3 * sin(theta), 3, 10);
  theta += 5760 / 600;

  /// Camera manipulation
  //float dx = 0.0f, dy = 0.0f, dz = 0.0f;
  //if (keyMonitor.keyIsDown(Qt::Key_Up)) {
  //  dy -= 0.05f;
  //}
  //if (keyMonitor.keyIsDown(Qt::Key_Down)) {
  //  dy += 0.05f;
  //}
  //if (keyMonitor.keyIsDown(Qt::Key_Left)) {
  //  dx += 0.05f;
  //}
  //if (keyMonitor.keyIsDown(Qt::Key_Right)) {
  //  dx -= 0.05f;
  //}
  //camera.translate(dx, dy, dz);

  /// Text update
  for (auto* text: textList) {
    text->onFrame();
  }
  DebugText::instance().onFrame();

}
