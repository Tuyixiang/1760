//
// Created by Yixiang Tu on 01/06/2018.
//

#include "BodyPart.h"
#include "../global/Colors.h"

void BodyPart::writeGLVertices(GLVertex*& target) {
  if (_damage) {
    for (auto* p: _triangles) {
      const QVector3D& v1 = transformedPosition(p[0]->position());
      const QVector3D& v2 = transformedPosition(p[1]->position());
      const QVector3D& v3 = transformedPosition(p[2]->position());
      const QVector3D& normal = QVector3D::normal(v1 - v2, v2 - v3);
      *(target++) = GLVertex(v1, DARKRED * _damage + p[0]->color() * (1 - _damage), normal);
      *(target++) = GLVertex(v2, DARKRED * _damage + p[1]->color() * (1 - _damage), normal);
      *(target++) = GLVertex(v3, DARKRED * _damage + p[2]->color() * (1 - _damage), normal);
    }
  } else {
    for (auto* p: _triangles) {
      const QVector3D& v1 = transformedPosition(p[0]->position());
      const QVector3D& v2 = transformedPosition(p[1]->position());
      const QVector3D& v3 = transformedPosition(p[2]->position());
      const QVector3D& normal = QVector3D::normal(v1 - v2, v2 - v3);
      *(target++) = GLVertex(v1, p[0]->color(), normal);
      *(target++) = GLVertex(v2, p[1]->color(), normal);
      *(target++) = GLVertex(v3, p[2]->color(), normal);
    }
  }
}

void BodyPart::writeGLVerticesWithNewColor(GLVertex*& target) {
  for (auto* p: _triangles) {
    const QVector3D& v1 = transformedPosition(p[0]->position());
    const QVector3D& v2 = transformedPosition(p[1]->position());
    const QVector3D& v3 = transformedPosition(p[2]->position());
    const QVector3D& normal = QVector3D::normal(v1 - v2, v2 - v3);
    *(target++) = GLVertex(v1, _color, normal);
    *(target++) = GLVertex(v2, _color, normal);
    *(target++) = GLVertex(v3, _color, normal);
  }
}
