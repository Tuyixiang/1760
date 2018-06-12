//
// Created by Yixiang Tu on 01/06/2018.
//

#include "Wall.h"
#include "../../GLWidget.h"

void Wall::construct() {
  float halfWidth = _width / 2.0f;
  float halfHeight = _height / 2.0f;

  float _depthOffset = -2;

  _vertices.clear();

  /// Top back edge
  /// (_width + 1) vertices
  _vertices.emplace_back(QVector3D(-halfWidth,
                                   halfHeight + Random::instance().getFloat0() * 0.3f + 0.5f,
                                   -_depth + Random::instance().getFloat0() * 0.3f + _depthOffset),
                         _color);
  for (int i = 1; i < _width; i++) {
    _vertices.emplace_back(QVector3D(i - halfWidth + Random::instance().getFloat0() * 0.3f,
                                     halfHeight + Random::instance().getFloat0() * 0.3f + 0.5f,
                                     -_depth + Random::instance().getFloat0() * 0.3f + _depthOffset),
                           _color);
  }
  _vertices.emplace_back(QVector3D(halfWidth,
                                   halfHeight + Random::instance().getFloat0() * 0.3f + 0.5f,
                                   -_depth + Random::instance().getFloat0() * 0.3f + _depthOffset),
                         _color);

  /// Top front edge
  /// (_width + 2) vertices
  _vertices.emplace_back(QVector3D(-halfWidth,
                                   halfHeight + Random::instance().getFloat0() * 0.3f,
                                   Random::instance().getFloat0() * 0.3f + _depthOffset),
                         _color);
  for (int i = 1; i <= _width; i++) {
    float x = (float) i * _width / (_width + 1) - halfWidth;
    _vertices.emplace_back(QVector3D(x + Random::instance().getFloat0() * 0.3f,
                                     halfHeight + Random::instance().getFloat0() * 0.3f,
                                     Random::instance().getFloat0() * 0.3f + _depthOffset),
                           _color);
  }
  _vertices.emplace_back(QVector3D(halfWidth,
                                   halfHeight + Random::instance().getFloat0() * 0.3f,
                                   Random::instance().getFloat0() * 0.3f + _depthOffset),
                         _color);

  /// Bottom front edge
  /// (_width + 1) vertices
  _vertices.emplace_back(QVector3D(-halfWidth,
                                   -halfHeight + Random::instance().getFloat0() * 0.3f,
                                   -_depth + Random::instance().getFloat0() * 0.3f + _depthOffset),
                         _color);
  for (int i = 1; i < _width; i++) {
    _vertices.emplace_back(QVector3D(i - halfWidth + Random::instance().getFloat0() * 0.3f,
                                     -halfHeight + Random::instance().getFloat0() * 0.3f,
                                     -_depth + Random::instance().getFloat0() * 0.3f + _depthOffset),
                           _color);
  }
  _vertices.emplace_back(QVector3D(halfWidth,
                                   -halfHeight + Random::instance().getFloat0() * 0.3f,
                                   -_depth + Random::instance().getFloat0() * 0.3f + _depthOffset),
                         _color);

  /// Top front edge
  /// (_width + 2) vertices
  _vertices.emplace_back(QVector3D(-halfWidth,
                                   -halfHeight + Random::instance().getFloat0() * 0.3f,
                                   Random::instance().getFloat0() * 0.3f + _depthOffset),
                         _color);
  for (int i = 1; i <= _width; i++) {
    float x = (float) i * _width / (_width + 1) - halfWidth;
    _vertices.emplace_back(QVector3D(x + Random::instance().getFloat0() * 0.3f,
                                     -halfHeight + Random::instance().getFloat0() * 0.3f,
                                     Random::instance().getFloat0() * 0.3f + _depthOffset),
                           _color);
  }
  _vertices.emplace_back(QVector3D(halfWidth,
                                   -halfHeight + Random::instance().getFloat0() * 0.3f,
                                   Random::instance().getFloat0() * 0.3f + _depthOffset),
                         _color);


  for (int i = 0; i < _width; i++) {
    addTriangle(i, i + _width + 2, i + 1);
    addTriangle(i + _width + 2, i + 2 * _width + 3, i + 2 * _width + 4);
  }
  for (int i = 0; i <= _width; i++) {
    addTriangle(i, i + _width + 1, i + _width + 2);
    addTriangle(i + _width + 1, i + 2 * _width + 3, i + _width + 2);
  }
}

void Wall::draw(const QMatrix4x4& perspective, const QMatrix4x4& camera, const QVector3D& uniformLight,
                const QVector4D& light, GLWidget* parent) {
  Body::draw(perspective, camera, uniformLight, light, parent);
}
