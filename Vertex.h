//
// Created by Yixiang Tu on 28/05/2018.
//

#ifndef INC_1760_VERTEX_H
#define INC_1760_VERTEX_H

#include <QVector3D>
#include <QVector4D>
#include "global/Macro.h"

/**
 * This class is used to create vertices with position & color information
 * Color is stored by (r, g, b, a), with range [0,1]
 */
class Vertex {

public:
  Vertex() = default;

  Vertex(const QVector3D& position, const QVector4D& color) : _position(position), _color(color) {}

  Vertex(const QVector3D& position, const QVector3D& color) : _position(position), _color(QVector4D(color, 1.0f)) {}

  const QVector3D& position() const {
    return _position;
  }

  const QVector4D& color() const {
    return _color;
  }

  virtual const Vertex vertex() {
    return Vertex(_position, _color);
  }

private:
  const QVector3D _position;
  const QVector4D _color;
};

class MovableVertex {

public:
  MovableVertex() = default;

  MovableVertex(const QVector3D& position, const QVector4D& color) :
    _position(position),
    _color(color) {}

  QVector3D& position() {
    return _position;
  }

  QVector4D& color() {
    return _color;
  }

  virtual void onFrame() {}


protected:
  QVector3D _position;
  QVector4D _color;
};




#endif //INC_1760_VERTEX_H
