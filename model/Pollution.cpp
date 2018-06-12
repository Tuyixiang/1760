//
// Created by Yixiang Tu on 04/06/2018.
//

#include "Pollution.h"
#include "../GLWidget.h"

void Pollution::initializeShader() {

  /// 1. Draw body
  construct(_width, _height, _row, _col, 0, QVector4D(0, 0.5f, 1.0f, 1.0f));
  //createGLVertices();

  /// 2. Set initial status
  //_transform.setPosition(0.0f, 0.0f, -10.0f);

  Body::initializeShader();
  _verticesChanged = true;

}

void Pollution::onFrame() {

  for (auto* e: vertices) {
    e->onFrame();
  }

  _verticesChanged = true;
}

void Pollution::draw(const QMatrix4x4& perspective, const QMatrix4x4& camera, const QVector3D& uniformLight,
                            const QVector4D& light, GLWidget* parent) {
  Body::draw(perspective, QMatrix4x4(), uniformLight, light, parent);
}

void Pollution::construct(float width, float height, int row, int col, float z, const QVector4D& color) {
  int total = row * col - (row >> 1);
  int r = 0;
  float wCenter = width / 2;
  float hCenter = height / 2;
  vertices.assign(static_cast<unsigned long>(total), nullptr);
  for (int i = 0; i < total; i += (col << 1) - 1) {
    for (int j = 0; j < col; j++) {
      vertices[i + j] = new OscillatingVertex(
        QVector3D(
          width * j / (col - 1) - wCenter,
          height * r / (row - 1) - hCenter,
          z
        ),
        _color, _oscilationRange, _colorRange,
        _minPositionPeriod, _maxPositionPeriod, _minColorPeriod, _maxColorPeriod,
        360, OscillatingVertex::unifiedColorChange);
    }
    r++;
    if (r < row) {
      for (int j = 0; j < col - 1; j++) {
        vertices[i + j + col] = new OscillatingVertex(
          QVector3D(
            width * (0.5f + j) / (col - 1) - wCenter,
            height * r / (row - 1) - hCenter,
            z
          ),
          _color, _oscilationRange, _colorRange,
          _minPositionPeriod, _maxPositionPeriod, _minColorPeriod, _maxColorPeriod,
          360, OscillatingVertex::unifiedColorChange);
      }
      r++;
    }
  }
  /*for (auto* i: vertices) {
    printf("%f, %f, %f\n", i->position().x(), i->position().y(), i->position().z());
  }*/
}

void Pollution::createGLVertices() {
  _glVertices.clear();
  for (int r = 0, n; r < _row - 1; r++) {
    n = r * _col - (r / 2);
    if (r & 1) {
      for (int i = 0; i < _col - 2; i++) {
        newAddTriangle(n + i, n + i + 1, n + i + _col);
      }
      for (int i = 0; i < _col - 1; i++) {
        newAddTriangle(n + i, n + i + _col, n + i + _col - 1);
      }
    } else {
      for (int i = 0; i < _col - 1; i++) {
        newAddTriangle(n + i, n + i + 1, n + i + _col);
      }
      for (int i = 1; i < _col - 1; i++) {
        newAddTriangle(n + i, n + i + _col, n + i + _col - 1);
      }
    }
  }
}

void Pollution::updateGLVertices(GLVertex*& target) {
  auto initial = target;
  for (int r = 0, n; r < _row - 1; r++) {
    n = r * _col - (r / 2);
    if (r & 1) {
      for (int i = 0; i < _col - 2; i++) {
        if (display[2 * r][i]) {
          writeTriangle(target, n + i, n + i + 1, n + i + _col);
          target += 3;
        }
      }
      for (int i = 0; i < _col - 1; i++) {
        if (display[2 * r + 1][i]) {
          writeTriangle(target, n + i, n + i + _col, n + i + _col - 1);
          target += 3;
        }
      }
    } else {
      for (int i = 0; i < _col - 1; i++) {
        if (display[2 * r][i]) {
          writeTriangle(target, n + i, n + i + 1, n + i + _col);
          target += 3;
        }
      }
      for (int i = 1; i < _col - 1; i++) {
        if (display[2 * r + 1][i]) {
          writeTriangle(target, n + i, n + i + _col, n + i + _col - 1);
          target += 3;
        }
      }
    }
  }
  for (; target < initial + count() and *target != GLVertex(); target++) {
    *target = GLVertex();
  }
}

Pollution::~Pollution() {
  for (auto* p: vertices) {
    delete p;
  }
  for (int i = 0; i < 2 * _row - 2; i++) {
    delete[] display[i];
  }
}