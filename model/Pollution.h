//
// Created by Yixiang Tu on 04/06/2018.
//

#ifndef INC_1760_POLLUTION_H
#define INC_1760_POLLUTION_H


#include "../template/Body.h"
#include "../vertex/OscillatingVertex.h"
#include "ShaderSource.h"
#include <vector>

class Pollution : public Body {

protected:

  std::vector<OscillatingVertex*> vertices;
  float _width;
  float _height;
  int _row;
  int _col;
  int _minPositionPeriod = 240;
  int _maxPositionPeriod = 240;
  int _minColorPeriod = 240;
  int _maxColorPeriod = 240;
  QVector4D _color;
  QVector4D _colorRange;
  QVector3D _oscilationRange = QVector3D(0.1, 0.1, 0.1);

public:
  bool** display;

  //int thisPositionPeriod = 0;
  //int thisPositionRange = 0;

public:
#ifndef NDEBUG

  const QString className() override {
    return QString("Pollution");
  }

#endif

  Pollution(const Scene* parent, int id) : Body(parent, id) {}

  ~Pollution() override;

  void setSize(float width, float height, int col, int row) {
    _width = width;
    _height = height;
    _row = row;
    _col = col;
    display = new bool*[2 * row - 2];
    for (int i = 0; i < 2 * row - 2; i++) {
      display[i] = new bool[col];
    }
  }

  void setOscilationRange(QVector3D&& range) {
    _oscilationRange = range;
  }

  void setPositionPeriod(int period) {
    _minPositionPeriod = _maxPositionPeriod = period;
  }

  void setPositionPeriod(int min, int max) {
    _minPositionPeriod = min;
    _maxPositionPeriod = max;
  }

  void setColorPeriod(int period) {
    _minColorPeriod = _maxColorPeriod = period;
  }

  void setColorPeriod(int min, int max) {
    _minColorPeriod = min;
    _maxColorPeriod = max;
  }

  void setColor(float r, float g, float b, float a = 1.0f) {
    _color = QVector4D(r, g, b, a);
    _colorRange = QVector4D(0, 0, 0, 0);
  }

  void setColor(const QVector4D& a, const QVector4D& b) {
    _color = (a + b) / 2;
    _colorRange = (b - a) / 2;
  }

  void initializeShader() override;

  void onFrame() final;

  const GLVertex* glVertices() const override {
    return nullptr;
  }

  const int count() const override {
    return _row * _col * 6;
  }

  //  Typically we'll simply use this frag source
  const QString& fragSource() const final {
    return src::fragGlossyComp;
  }

  //  Typically we'll simply use this vert source
  const QString& vertSource() const final {
    return src::vertTwoLightsComp;
  }

  void draw(const QMatrix4x4& perspective, const QMatrix4x4& camera, const QVector3D& uniformLight,
            const QVector4D& light, GLWidget* parent) override;

protected:
  void construct(float width, float height, int row, int col, float z, const QVector4D& color);

  void createGLVertices();

  void updateGLVertices(GLVertex*& target) override;

  void newAddTriangle(int v1, int v2, int v3) {
    addTriangle(vertices[v1]->vertex(), vertices[v2]->vertex(), vertices[v3]->vertex());
  }

  void writeTriangle(GLVertex* target, const Vertex& v1, const Vertex& v2, const Vertex& v3) {
    QVector3D normal = QVector3D::normal(v1.position() - v2.position(), v2.position() - v3.position());
    target[0] = GLVertex(v1.position(), v1.color(), normal);
    target[1] = GLVertex(v2.position(), v2.color(), normal);
    target[2] = GLVertex(v3.position(), v3.color(), normal);
  }

  void writeTriangle(GLVertex* target, int v1, int v2, int v3) {
    writeTriangle(target, vertices[v1]->vertex(), vertices[v2]->vertex(), vertices[v3]->vertex());
  }


};


#endif //INC_1760_POLLUTION_H
