//
// Created by Yixiang Tu on 27/05/2018.
//

#ifndef INC_1760_TRANSFORM3D_H
#define INC_1760_TRANSFORM3D_H

#include <QMatrix4x4>
#include <QVector2D>
#include <QVector3D>
#include <QQuaternion>
#include <Box2D/Box2D.h>
#include "global/Macro.h"


class Transform3D {

protected:
  bool changed = false;
  QVector3D _position;
  QQuaternion _rotation;
  QVector3D _size;
  QMatrix4x4 world;

  void checkScale() const {
    if (_size.x() < 0 or _size.y() < 0 or _size.z() < 0) {
      Message::instance().warn("Transform3D", "negative scale", this);
    }
  }

public:
  Transform3D() : changed(true), _size(1.0f, 1.0f, 1.0f) {}

  /// Translate BY
  void translate(const QVector3D& dr) {
    changed = true;
    _position += dr;
  }

  void translate(float dx, float dy, float dz) {
    translate(QVector3D(dx, dy, dz));
  }

  template<class T>
  void scale(const T& factor) {
    changed = true;
    _size *= factor;
  }

  void scale(float x, float y, float z) {
    changed = true;
    _size.setX(_size.x() * x);
    _size.setY(_size.y() * y);
    _size.setZ(_size.z() * z);
  }

  void rotate(const QQuaternion& factor) {
    changed = true;
    _rotation *= factor;
  }

  void rotate(float angle, const QVector3D& axis) {
    changed = true;
    _rotation *= QQuaternion::fromAxisAndAngle(axis, angle);
  }

  void rotate(float angle, float axisX, float axisY, float axisZ) {
    changed = true;
    _rotation *= QQuaternion::fromAxisAndAngle(axisX, axisY, axisZ, angle);
  }

  /**
   * Increase/Decrease scale
   * @param dsize
   */
  void grow(const QVector3D& dsize) {
    changed = true;
    _size += dsize;
    checkScale();
  }

  /**
   * Increase/Decrease scale
   * @param dx
   * @param dy
   * @param dz
   */
  void grow(float dx, float dy, float dz) {
    changed = true;
    _size.setX(_size.x() + dx);
    _size.setY(_size.y() + dy);
    _size.setZ(_size.z() + dz);
    checkScale();
  }

  /// Translate TO
  void setPosition(const QVector3D& newPosition) {
    changed = true;
    _position = newPosition;
  }

  void setX(float x) {
    changed = true;
    _position.setX(x);
  }

  void setY(float y) {
    changed = true;
    _position.setY(y);
  }

  void setPosition(float x, float y, float z) {
    changed = true;
    _position.setX(x);
    _position.setY(y);
    _position.setZ(z);
  }

  void setPosition(const QVector2D& newPosition) {
    changed = true;
    _position.setX(newPosition.x());
    _position.setY(newPosition.y());
  }

  void setPosition(const b2Vec2& newPosition) {
    changed = true;
    _position.setX(newPosition.x);
    _position.setY(newPosition.y);
  }

  void setSize(const QVector3D& newScale) {
    changed = true;
    _size = newScale;
    checkScale();
  }

  void setSize(float x, float y, float z) {
    changed = true;
    _size.setX(x);
    _size.setY(y);
    _size.setZ(z);
    checkScale();
  }

  void setSize(float s) {
    changed = true;
    _size.setX(s);
    _size.setY(s);
    _size.setZ(s);
    checkScale();
  }

  void setRotation(const QQuaternion& newRotation) {
    changed = true;
    _rotation = newRotation;
  }

  void setRotation(float angle, const QVector3D& axis = QVector3D(0, 0, 1)) {
    changed = true;
    _rotation = QQuaternion::fromAxisAndAngle(axis, angle);
  }

  void setRotation(float angle, float axisX, float axisY, float axisZ) {
    changed = true;
    _rotation = QQuaternion::fromAxisAndAngle(axisX, axisY, axisZ, angle);
  }

  /// Accessor
  QVector3D& position() {
    return _position;
  }

  const b2Vec2 position2D() {
    return b2Vec2(_position.x(), _position.y());
  }

  QQuaternion& rotation() {
    return _rotation;
  }

  QVector3D& size() {
    return _size;
  }

  const QMatrix4x4& matrix();


};


#endif //INC_1760_TRANSFORM3D_H
