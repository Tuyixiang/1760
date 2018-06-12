//
// Created by Yixiang Tu on 04/06/2018.
//

#include "BCharacter.h"
#include "BWorldScene.h"

BCharacter::BCharacter(BWorldScene* parent, int id, b2World* parentWorld, const QString& name)
  : BPolygon(parent, id, parentWorld, name), _parent(parent) {
  _timeOffset = Random::instance().getBetween(0, 86400);
}

void BCharacter::onFrame() {
  BPolygon::onFrame();
  _verticesChanged = true;
  _timeLasted++;
  DebugText::instance().showInstantMessage(_name + (_this->IsAwake() ? ": Awake" : ": Sleeping"));
}

void BCharacter::updateGLVertices(GLVertex*& target) {
  for (auto* e: partList) {
    e->writeGLVertices(target);
  }
}

BCharacter::~BCharacter() {
  for (auto* e: partList) {
    delete e;
  }
}

void BCharacter::draw(const QMatrix4x4& perspective, const QMatrix4x4& camera, const QVector3D& uniformLight,
                      const QVector4D& light, GLWidget* parent) {
  if (_inRange) {
    BBody::draw(perspective, camera, uniformLight, light, parent);
  }
}
