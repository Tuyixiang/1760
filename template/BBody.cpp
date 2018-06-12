//
// Created by Yixiang Tu on 30/05/2018.
//

#include "BBody.h"
#include "../GLWidget.h"

BBody::~BBody() {

  _parentWorld->DestroyBody(_this);

}

void BBody::draw(const QMatrix4x4& perspective, const QMatrix4x4& camera, const QVector3D& uniformLight,
                 const QVector4D& light, GLWidget* parent) {
  if (visible) {
    try {
      Body::draw(perspective, camera, uniformLight, light, parent);
    } catch (...) {
      SM(_name + ": DRAW FAILED, RETRYING!");
      refreshDraw();
      initializeShader();
      Body::draw(perspective, camera, uniformLight, light, parent);
    }
  }
}

void BBody::transformAndWriteTriangle(GLVertex*& target, int v1, int v2, int v3) {
  _transform.setPosition(_this->GetPosition());
  const QVector3D&& p1 = _transform.position() +
                         QQuaternion::fromAxisAndAngle(QVector3D(0, 0, 1), _this->GetAngle()) *
                         _vertices[v1].position();
  const QVector3D&& p2 = _transform.position() +
                         QQuaternion::fromAxisAndAngle(QVector3D(0, 0, 1), _this->GetAngle()) *
                         _vertices[v2].position();
  const QVector3D&& p3 = _transform.position() +
                         QQuaternion::fromAxisAndAngle(QVector3D(0, 0, 1), _this->GetAngle()) *
                         _vertices[v3].position();
  const QVector3D&& normal = QVector3D::normal(p1 - p2, p2 - p3);
  target[0] = GLVertex(p1, _vertices[v1].color(), normal);
  target[1] = GLVertex(p2, _vertices[v2].color(), normal);
  target[2] = GLVertex(p3, _vertices[v3].color(), normal);
  target += 3;
}

void BBody::onFrame() {
  if (!_toBeDestroyed) {
    if (_canBeDestroyed and _damage >= _maxHp) {
      _toBeDestroyed = true;
      onDestroy();
    } else {
      _damage = 0;
    }
  }
  Body::onFrame();
}
