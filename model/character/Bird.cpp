//
// Created by Yixiang Tu on 04/06/2018.
//

#include "Bird.h"
#include "../../global/Math.h"
#include "../../text/DebugText.h"
#include "../../template/BWorldScene.h"

Bird::Bird(BWorldScene* parent, int id, b2World* parentWorld, const QString& name)
  : BCharacter(parent, id, parentWorld, name) {

  //  Does not collide with walls
  collisionGroup = 0b00010000;
  collisionMask = 0b00000000;
  _reward = 100;
  _lifeTime = 600;
  _canBeDestroyed = true;
}

void Bird::constructVertices() {

  _newColor = _color = QVector4D(0.8f, 0.8f, 1.0f, 1.0f);

  body = new BodyPart;
  body->setColor(_color);
  body->addVertex(QVector3D(-0.25f, 0.25f, 0));
  body->addVertex(QVector3D(-0.25f, -0.25f, 0));
  body->addVertex(QVector3D(0.25f, -0.25f, 0));
  body->addVertex(QVector3D(0.25f, 0.25f, 0));
  body->drawTriangle(0, 1, 2);
  body->drawTriangle(0, 2, 3);
  partList.push_back(body);

  leftWing = new BodyPart;
  leftWing->setColor(_color);
  leftWing->addVertex(QVector3D(-0.3f, 0, 0));
  leftWing->addVertex(QVector3D(-0.7f, 0.4f, 0));
  leftWing->addVertex(QVector3D(-1.1f, 0.0f, 0));
  leftWing->drawTriangle(0, 1, 2);
  partList.push_back(leftWing);

  rightWing = new BodyPart;
  rightWing->setColor(_color);
  rightWing->addVertex(QVector3D(0.3f, 0, 0));
  rightWing->addVertex(QVector3D(0.7f, 0.4f, 0));
  rightWing->addVertex(QVector3D(1.1f, 0.0f, 0));
  rightWing->drawTriangle(0, 2, 1);
  partList.push_back(rightWing);

  _transform.scale(_halfWidth / 0.25f);

}

void Bird::onFrame() {
  if (_toBeDestroyed) {
    _newColor.setW(_newColor.w() - 0.05f);
    if (_newColor.w() <= 0) {
      _newColor.setW(0);
      _toBeRemoved = true;
      SM("remove")
    }
  } else {
    if (flyingIn) {
      auto v = _this->GetLinearVelocity();
      _this->SetLinearVelocity(v + b2Vec2(0.2f, 0));
      flyingIn--;
    }
    if (_inRange) {

      _lifeTime--;

      /// Move left and right

      _newColor = (_color * (_maxHp - _damage) + QVector4D(1, 0, 0, 1) * _damage) / _maxHp;

      wingPhase += 48;

      leftWing->transform().setRotation(sin(wingPhase) * 45, QVector3D(0, 0, 1));
      rightWing->transform().setRotation(-sin(wingPhase) * 45, QVector3D(0, 0, 1));

      auto v = _this->GetLinearVelocity();

      if (_lifeTime >= 0) {
        _this->SetLinearVelocity(v + b2Vec2(2 * (-sin(movePhase) + sin(movePhase += 36)), 0));
      } else {
        _this->SetLinearVelocity(v + b2Vec2(-0.2f, 0));
      }
    } else if (_lifeTime < 0) {
      _parent->addScore(_reward);
      _toBeRemoved = true;
    }
  }


  BCharacter::onFrame();
}

const int Bird::count() const {
  return 100;
}

void Bird::initializeBBody() {
  _bodyDef->fixedRotation = true;
  _bodyDef->gravityScale = 0;
  _bodyDef->linearDamping = 1;
  BPolygon::initializeBBody();
}

void Bird::updateGLVertices(GLVertex*& target) {
  for (auto* e: partList) {
    e->setColor(_newColor);
    e->writeGLVerticesWithNewColor(target);
  }
}

void Bird::onDestroy() {
  _this->GetFixtureList()->SetDensity(0.0001f);
  _this->ResetMassData();
  _newColor = QVector4D(1, 0, 0, 1);
  _parent->addScore(_reward);
}

int Bird::blend() const {
  return 1;
}

void Bird::flyIn() {
  _this->SetLinearVelocity(b2Vec2(-5.0f, 0));
  movePhase = Random::instance().getBetween(0, 5760);
  flyingIn = 10;
}
