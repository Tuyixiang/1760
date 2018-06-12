//
// Created by Yixiang Tu on 04/06/2018.
//

#ifndef INC_1760_BLACKAGE_H
#define INC_1760_BLACKAGE_H
#include "../template/Body.h"
#include "../global/Colors.h"
#include "ShaderSource.h"

class Blackage : public Body {

protected:

  bool _style;

  bool _toBeDestroyed = false;

  int blend() const override {
    return 2;
  }

  MovableVertex _vertices[4] = {
    MovableVertex(QVector3D(-1.6f, -1, 0), QVector4D(0, 0, 0, 0)),
    MovableVertex(QVector3D(-1.6f, 1, 0), QVector4D(0, 0, 0, 0)),
    MovableVertex(QVector3D(1.6f, -1, 0), QVector4D(0, 0, 0, 0)),
    MovableVertex(QVector3D(1.6f, 1, 0), QVector4D(0, 0, 0, 0)),
  };

public:

  enum {
    fadeIn = false,
    fadeOut = true
  };

#ifndef NDEBUG

  const QString className() override {
    return QString("Blackage");
  }

#endif

  Blackage(const Scene* parent, int id, bool style) : Body(parent, id), _style(style) {}

  void initializeShader() override;

  const Vertex* vertices() override;

  void onFrame() override;

  void draw(const QMatrix4x4& perspective, const QMatrix4x4& camera, const QVector3D& uniformLight,
            const QVector4D& light, GLWidget* parent) override;

  void setStyle(bool style) {
    _style = style;
  }

  //  Typically we'll simply use this frag source
  const QString& fragSource() const final {
    return src::fragNoLightComp;
  }

  //  Typically we'll simply use this vert source
  const QString& vertSource() const final {
    return src::vertNoLightComp;
  }

  void updateGLVertices(GLVertex*& target) override;

};


#endif //INC_1760_BLACKAGE_H
