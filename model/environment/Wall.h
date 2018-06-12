//
// Created by Yixiang Tu on 01/06/2018.
//

#ifndef INC_1760_WALL_H
#define INC_1760_WALL_H

#include "../../template/BPolygon.h"

/**
 * MUST use integer size
 */
class Wall : public Body {

protected:
  int _width;
  int _height;
  int _depth;
  QVector4D _color;
  std::vector<Vertex> _vertices;

public:
#ifndef NDEBUG

  const QString className() override {
    return QString("Wall");
  }

#endif

  /// Initialization

  Wall(const Scene* parentScene, int id) : Body(parentScene, id) {}

  void setSize(int width, int height, int depth) {
    _width = width;
    _height = height;
    _depth = depth;
  }

  void setColor(const QVector4D& color) {
    _color = color;
  }

  void initializeShader() override {
    if (!_constructed) {
      construct();
      _constructed = true;
    }
    Body::initializeShader();
  }

  void draw(const QMatrix4x4& perspective, const QMatrix4x4& camera, const QVector3D& uniformLight,
            const QVector4D& light, GLWidget* parent) override;

  //  Typically we'll simply use this frag source
  const QString& fragSource() const final {
    return src::fragGlossyComp;
  }

  //  Typically we'll simply use this vert source
  const QString& vertSource() const final {
    return src::vertTwoLightsComp;
  }

  //void addTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3) override;

protected:
  const Vertex* vertices() override {
    return _vertices.data();
  }

  void construct();

  bool _constructed = false;

};


#endif //INC_1760_WALL_H
