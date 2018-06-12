//
// Created by Yixiang Tu on 30/05/2018.
//

#include "BWorldScene.h"
#include "BPolygon.h"
#include "../model/character/Protagonist.h"
#include "../model/character/Bird.h"
#include "../model/character/Tree.h"
#include "../global/Math.h"
#include "../global/GameGlobals.h"
#include "../text/Fonts.h"

BWorldScene::BWorldScene(GLWidget* parent) : Scene(parent) {
  nameList.resize(1000);
}

void BWorldScene::onInitialize() {
  initializeScene();
  initializeBodies();
  //for (auto* e: bodyList) {
  //  e->initializeShader();
  //}
  //for (auto pair: bodyMap) {
  //  pair.second->initializeShader();
  //}
  //for (auto pair: characterMap) {
  //  pair.second->initializeShader();
  //}
}

void BWorldScene::render(const QMatrix4x4& perspective) {
  for (auto it = bodyList.begin(); it != bodyList.end();) {
    if ((*it)->toBeRemoved()) {
      delete (*it);
    } else {
      (*it)->draw(perspective, camera.matrix(), uniformLight, light, _parent);
      it++;
    }
  }
  for (auto it = bodyMap.cbegin(); it != bodyMap.cend();) {
    if (it->second->toBeRemoved()) {
      delete it->second;
      it = bodyMap.erase(it);
    } else {
      it->second->draw(perspective, camera.matrix(), uniformLight, light, _parent);
      it++;
    }
  }
  for (auto it = characterMap.cbegin(); it != characterMap.cend();) {
    if (it->second->toBeRemoved()) {
      delete it->second;
      it = characterMap.erase(it);
      SM("character removed");
    } else {
      it->second->draw(perspective, camera.matrix(), uniformLight, light, _parent);
      it++;
    }
  }
  /*if (blackage) {
    if (!blackage->initialized()) {
      blackage->initializeShader();
    }
    blackage->draw(perspective, camera.matrix(), uniformLight, light, _parent);
  }*/
  //group->draw(perspective, camera.matrix(), uniformLight, light, _parent);
}

void BWorldScene::drawText(QPainter& painter) {
  for (auto it = textMap.cbegin(); it != textMap.cend();) {
    if (it->second->toBeRemoved()) {
      delete it->second;
      it = textMap.erase(it);
      SM("text removed");
    } else {
      it->second->draw(painter);
      it++;
    }
  }
  DebugText::instance().draw(painter);
}

void BWorldScene::onFrame() {
  DebugText::instance().onFrame();
  for (auto* e: bodyList) {
    e->onFrame();
  }
  for (auto pair: bodyMap) {
    pair.second->onFrame();
  }
  for (auto pair: characterMap) {
    pair.second->onFrame();
  }
  for (auto pair: textMap) {
    pair.second->onFrame();
  }
  onEachFrame();
}

BWorldScene::~BWorldScene() {
  for (auto& it : bodyMap) {
    delete it.second;
  }
  bodyMap = std::map<QString, BBody*>();
  for (auto& it : characterMap) {
    delete it.second;
  }
  characterMap = std::map<QString, BCharacter*>();
  for (auto& it : textMap) {
    delete it.second;
  }
  textMap = std::map<QString, Text*>();
  delete _world;
}

BPolygon* BWorldScene::createRect(const char* name) {
  auto newRect = new BPolygon(this, idDistributor++, _world, QString(name));
  bodyMap[name] = newRect;
  nameList[nameIndex] = QString(name);
  return newRect;
}

Protagonist* BWorldScene::createProtagonist(const char* name) {
  auto newPro = new Protagonist(this, idDistributor++, _world, QString(name));
  characterMap[name] = newPro;
  return newPro;
}

Bird* BWorldScene::createBird(const QString& name) {
  auto newBird = new Bird(this, idDistributor++, _world, name);
  characterMap[name] = newBird;
  return newBird;
}

Tree* BWorldScene::createTree(const QString& name, TreeTrunk* treeTrunk) {
  auto newTree = new Tree(this, idDistributor++, _world, name, treeTrunk);
  characterMap[name] = newTree;
  return newTree;
}

void BWorldScene::proMovementControl() {
  static const float proHorizontalSpeedLimit = 3.0f;

  if (!_pro->toBeDestroyed()) {

    /// Protagonist control
    auto proVelocity = _pro->body()->GetLinearVelocity();
    DebugText::instance().showInstantMessage("X: " + QString::number(_pro->body()->GetPosition().x));
    DebugText::instance().showInstantMessage("Y: " + QString::number(_pro->body()->GetPosition().y));
    DebugText::instance().showInstantMessage("XSpeed: " + QString::number(proVelocity.x));
    DebugText::instance().showInstantMessage("YSpeed: " + QString::number(proVelocity.y));

    b2Vec2 newVelocity = proVelocity;
    if (_pro->land()) {
      if (keyMonitor.keyIsDown(Qt::Key_Space) or keyMonitor.keyIsDown(Qt::Key_W)) {
        Message::instance().show("jump");
        newVelocity.y = 10.0f;
      }
      switch (keyMonitor.DA()) {
        case 1: {
          newVelocity.x = min(proHorizontalSpeedLimit, proVelocity.x + 0.5f);
          break;
        }
        case -1: {
          newVelocity.x = max(-proHorizontalSpeedLimit, proVelocity.x - 0.5f);
          break;
        }
        default: {
          if (abs(proVelocity.x) <= 0.5f) {
            newVelocity.x = 0.0f;
          } else {
            newVelocity.x -= sign(proVelocity.x) * 0.5f;
          }
          break;
        }
      }
    } else {
      switch (keyMonitor.DA()) {
        case 1: {
          newVelocity.x = min(proHorizontalSpeedLimit, proVelocity.x + 0.5f);
          break;
        }
        case -1: {
          newVelocity.x = max(-proHorizontalSpeedLimit, proVelocity.x - 0.5f);
          break;
        }
        default: {
        }
      }
    }

    _pro->body()->SetLinearVelocity(newVelocity);

    _pro->walkAngle = proVelocity.x / proHorizontalSpeedLimit;
  }
}

b2Vec2 BWorldScene::mapScreenToWorld(const QPoint& position) {
  float x = 13.26f * (position.x() - width() / 2) / width() - camera.position().x();
  float y = 8.31f * (height() / 2 - position.y()) / height() - camera.position().y();
  return b2Vec2(x, y);
}

QPoint BWorldScene::mapWorldToScreen(const b2Vec2& position) {
  auto x = (int) ((position.x + camera.position().x()) / 13.26f * width() + width() / 2);
  auto y = (int) (-(position.y + camera.position().y()) / 8.31f * height() + height() / 2);
  return QPoint(x, y);
}

b2Body* BWorldScene::findBBody(const QString& name) {
  return bodyMap.at(name)->body();
}

void BWorldScene::addScore(int bonus) {
  GameGlobals::instance().score += bonus;
  scoreText->updateScore(GameGlobals::instance().score);
}

void BWorldScene::onEachFrame() {
  if (!_pro->toBeDestroyed()) {
    _world->Step(timeStep, velocityIteration, positionIteration);
  }
}
