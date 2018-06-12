//
// Created by Yixiang Tu on 26/05/2018.
//

#ifndef INC_1760_GLVERTEX_H
#define INC_1760_GLVERTEX_H

#include <QVector3D>

/**
 * This class is used to pipe vertex data to OpenGL rendering.
 *
 */
class GLVertex {


public:
  constexpr explicit GLVertex(const QVector3D& position = QVector3D(), const QVector4D& color = QVector4D(), const QVector3D& normal = QVector3D()) :
    _position(position), _color(color), _normal(normal) {}

  QVector3D& position() {
    return _position;
  }

  QVector4D& color() {
    return _color;
  }

  QVector3D& normal() {
    return _normal;
  }

  void translate(const QVector3D& dr) {
    _position += dr;
  }

  void translate(float dx, float dy, float dz) {
    translate(QVector3D(dx, dy, dz));
  }

  void setColor(const QVector4D& color) {
    _color = color;
  }

  void setNormal(const QVector3D& normal) {
    _normal = normal;
  }

  static const int PositionTupleSize = 3;
  static const int ColorTupleSize = 4;
  static const int NormalTupleSize = 3;

  static constexpr int positionOffset() {
    return (int) offsetof(GLVertex, _position);
  }

  static constexpr int colorOffset() {
    return (int) offsetof(GLVertex, _color);
  }

  static constexpr int normalOffset() {
    return (int) offsetof(GLVertex, _normal);
  }

  static constexpr int stride() {
    return (int) sizeof(GLVertex);
  }
  
  bool operator==(const GLVertex& other) const {
    return _position == other._position and _color == other._color and _normal == other._normal;
  }

  bool operator!=(const GLVertex& other) const {
    return _position != other._position or _color != other._color or _normal != other._normal;
  }

private:
  QVector3D _position;
  QVector4D _color;
  QVector3D _normal;
};

#endif //INC_1760_GLVERTEX_H
