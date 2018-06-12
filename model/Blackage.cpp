//
// Created by Yixiang Tu on 04/06/2018.
//

#include "Blackage.h"
#include "../GLWidget.h"

void Blackage::initializeShader() {

  if (_style == fadeIn) {
    for (auto& e: _vertices) {
      e.color() = BLACK;
    }
  }
  addTriangle(0, 2, 1);
  addTriangle(1, 2, 3);

  Body::initializeShader();
}

const Vertex* Blackage::vertices() {
  return (Vertex*) (_vertices);
}

void Blackage::draw(const QMatrix4x4& perspective, const QMatrix4x4& camera, const QVector3D& uniformLight,
                    const QVector4D& light, GLWidget* parent) {

  //parent->glClear(GL_DEPTH_BUFFER_BIT);
  _verticesChanged = true;
  Body::draw(perspective, camera, uniformLight, light, parent);

}

void Blackage::updateGLVertices(GLVertex*& target) {
  if (_style == fadeOut) {
    for (int i = 0; i < 6; i++) {
      float a = (target + i)->color().w();
      a = (a + 0.003f) / 0.98f;
      (target + i)->color().setW(a);
    }
  } else {
    for (int i = 0; i < 6; i++) {
      float a = (target + i)->color().w();
      a = a * 0.98f - 0.003f;
      (target + i)->color().setW(a);
    }
  }
  //target += 6;
}

void Blackage::onFrame() {
}
