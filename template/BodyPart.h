//
// Created by Yixiang Tu on 01/06/2018.
//

#ifndef INC_1760_BODYPART_H
#define INC_1760_BODYPART_H
#include "../Vertex.h"
#include "../Transform3D.h"
#include "../GLVertex.h"
#include <vector>

class BodyPart {

protected:
  std::vector<MovableVertex> _vertices;
  std::vector<MovableVertex**> _triangles;
  Transform3D _transform;
  QVector4D _color;
  float _damage = 0;

public:
  BodyPart() {
    _vertices.clear();
    _triangles.clear();
  }

  ~BodyPart() {
    for (auto* e: _triangles) {
      delete[] e;
    }
  }

  void setColor(const QVector4D& color) {
    _color = color;
  }

  void setDamage(float damage) {
    _damage = damage;
  }

  void addVertex(const QVector3D& position, const QVector4D& color) {
    _vertices.emplace_back(position, color);
  }

  void addVertex(const QVector3D& position) {
    _vertices.emplace_back(position, _color);
  }

  void drawTriangle(int v1, int v2, int v3) {
    auto p = new MovableVertex*[3];
    p[0] = _vertices.data() + v1;
    p[1] = _vertices.data() + v2;
    p[2] = _vertices.data() + v3;
    _triangles.push_back(p);
  }

  void writeGLVertices(GLVertex*& target);

  void writeGLVerticesWithNewColor(GLVertex*& target);

  QVector3D transformedPosition(const QVector3D& position) {
    return _transform.rotation().rotatedVector(_transform.size() * (position + _transform.position()));
  }

  Transform3D& transform() {
    return _transform;
  }

};


#endif //INC_1760_BODYPART_H
