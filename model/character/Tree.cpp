//
// Created by Yixiang Tu on 07/06/2018.
//

#include "Tree.h"
#include "../../template/BWorldScene.h"

Tree::Tree(BWorldScene* parent, int id, b2World* parentWorld, const QString& name, TreeTrunk* treeTrunk)
  : BCharacter(parent, id, parentWorld, name), trunk(treeTrunk) {
  _reward = 500;
  _canBeDestroyed = true;
  collisionGroup = 0b00100000;
  collisionMask = 0b11100000;
  _maxHp = 40;
  //_bodyDef->gravityScale = 0;
}

void Tree::constructVertices() {
  _newColor = _color = QVector4D(0.134f, 0.542f, 0.134f, 1.0f);

  topBranch = new BodyPart;
  topBranch->setColor(_color);
  topBranch->addVertex(QVector3D(0, 1.5f, -1));
  topBranch->addVertex(QVector3D(-1.5f, 0, -1));
  topBranch->addVertex(QVector3D(0, 0, 0.5f));
  topBranch->addVertex(QVector3D(1.5f, 0, -1));
  topBranch->addVertex(QVector3D(0, 0, -2.5f));
  topBranch->drawTriangle(0, 1, 2);
  topBranch->drawTriangle(0, 2, 3);
  topBranch->drawTriangle(0, 1, 4);
  topBranch->drawTriangle(0, 4, 3);
  partList.push_back(topBranch);

  leftBranch = new BodyPart;
  leftBranch->setColor(_color);
  leftBranch->addVertex(QVector3D(-1.25f, 0, -1));
  leftBranch->addVertex(QVector3D(-2.25f, -1.5f, -1));
  leftBranch->addVertex(QVector3D(-1.25f, -1.5f, 0));
  leftBranch->addVertex(QVector3D(-0.25f, -1.5f, -1));
  leftBranch->addVertex(QVector3D(-1.25f, -1.5f, -2));
  leftBranch->drawTriangle(0, 1, 2);
  leftBranch->drawTriangle(0, 2, 3);
  leftBranch->drawTriangle(0, 1, 4);
  leftBranch->drawTriangle(0, 4, 3);
  partList.push_back(leftBranch);

  rightBranch = new BodyPart;
  rightBranch->setColor(_color);
  rightBranch->addVertex(QVector3D(1.25f, 0, -1));
  rightBranch->addVertex(QVector3D(0.25f, -1.5f, -1));
  rightBranch->addVertex(QVector3D(1.25f, -1.5f, 0));
  rightBranch->addVertex(QVector3D(2.25f, -1.5f, -1));
  rightBranch->addVertex(QVector3D(1.25f, -1.5f, -2));
  rightBranch->drawTriangle(0, 1, 2);
  rightBranch->drawTriangle(0, 2, 3);
  rightBranch->drawTriangle(0, 1, 4);
  rightBranch->drawTriangle(0, 4, 3);
  partList.push_back(rightBranch);


}

void Tree::initializeBBody() {
  b2Vec2 vertices1[7] = {
    b2Vec2(0, _halfHeight),
    b2Vec2(-_halfWidth / 1.5f, 0),
    b2Vec2(-_halfWidth / 1.65f, 0),
    b2Vec2(0, _halfHeight / 1.1f),
    b2Vec2(_halfWidth / 1.65f, 0),
    b2Vec2(_halfWidth / 1.5f, 0),
    b2Vec2(0, _halfHeight)
  };
  b2Vec2 vertices2[4] = {
    b2Vec2(-_halfWidth / 1.8f, 0),
    b2Vec2(-_halfWidth, -_halfHeight),
    b2Vec2(-_halfWidth + 0.1f, -_halfHeight),
    b2Vec2(-_halfWidth / 1.8f, -_halfHeight * (1 - 1.0f / 1.1f))
  };
  b2Vec2 vertices3[4] = {
    b2Vec2(_halfWidth / 1.8f, 0),
    b2Vec2(_halfWidth, -_halfHeight),
    b2Vec2(_halfWidth - 0.1f, -_halfHeight),
    b2Vec2(_halfWidth / 1.8f, -_halfHeight * (1 - 1.0f / 1.1f))
  };
  //_bodyDef->fixedRotation = true;
  _fixtureDef->filter.categoryBits = collisionGroup;
  _fixtureDef->filter.maskBits = collisionMask;
  _this = _parentWorld->CreateBody(_bodyDef);
  ((b2PolygonShape*) _shape)->Set(vertices1, 4);
  _fixtureDef->shape = _shape;
  _this->CreateFixture(_fixtureDef);
  ((b2PolygonShape*) _shape)->Set(vertices1 + 3, 4);
  _fixtureDef->shape = _shape;
  _this->CreateFixture(_fixtureDef);
  ((b2PolygonShape*) _shape)->Set(vertices2, 4);
  _fixtureDef->shape = _shape;
  _this->CreateFixture(_fixtureDef);
  ((b2PolygonShape*) _shape)->Set(vertices3, 4);
  _fixtureDef->shape = _shape;
  _this->CreateFixture(_fixtureDef);
  _this->SetUserData(reinterpret_cast<void*> (&_name));
  if (visible) {
    constructVertices();
  }
}

void Tree::updateGLVertices(GLVertex*& target) {
  if (_toBeDestroyed) {
    for (auto* p: partList) {
      p->setColor(_newColor);
      p->writeGLVerticesWithNewColor(target);
    }
  } else {
    BCharacter::updateGLVertices(target);
  }
}

void Tree::onFrame() {
  if (_toBeDestroyed) {
    _newColor.setW(_newColor.w() - 0.04f);
    if (_newColor.w() <= 0) {
      _newColor.setW(0);
      //_toBeDestroyed = false;
      _toBeRemoved = true;
    }
    trunk->transform().translate(0, _this->GetLinearVelocity().y / 40, 0);
  } else {
    _this->SetAwake(_inRange);
    for (auto* p: partList) {
      p->setDamage((float) _damage / _maxHp);
    }
  }
  BCharacter::onFrame();
}

int Tree::blend() const {
  return 1;
}

const int Tree::count() const {
  return 100;
}

void Tree::onDestroy() {
  _parent->addScore(_reward);
  _this->GetFixtureList()->SetDensity(0.001f);
  _this->ResetMassData();
  _newColor = DARKRED;
  auto hang = _jointMap["hang"];
  if (hang) {
    _parentWorld->DestroyJoint(hang);
  }
}

void Tree::initializePosition(float x, float y) {
  //originalPosition = b2Vec2(x, y);
  BPolygon::initializePosition(x, y);
}

void Tree::initializeSize(float halfWidth, float halfHeight, float depth) {
  _halfWidth = halfWidth;
  _halfHeight = halfHeight;
  _depth = depth;
}
