//
// Created by Yixiang Tu on 28/05/2018.
//

#ifndef INC_1760_GLOSSYSHARD_H
#define INC_1760_GLOSSYSHARD_H

#include "../global/Macro.h"
#include "../template/Body.h"
#include "ShaderSource.h"
#include "../template/Scene.h"
#include <cmath>

class GlossyShard : public Body {

public:
#ifndef NDEBUG
  const QString className() override {
    return QString("GlossyShard");
  }
#endif


  GlossyShard(const Scene* parent, int id);

  void onFrame() final;

  //  Typically we'll simply use this frag source
  const QString& fragSource() const final {
    return src::fragNoLightComp;
  }

  //  Typically we'll simply use this vert source
  const QString& vertSource() const final {
    return src::vertNoLightComp;
  }

  void draw(const QMatrix4x4& perspective, const QMatrix4x4& camera, const QVector3D& uniformLight,
            const QVector4D& light, GLWidget* parent) override;


protected:

  const Vertex vertices[3] = {
    Vertex(QVector3D(1.0f / 3, -2.0f / 3, -1.0f / 3), QVector4D(1.0f, 1.0f, 1.0f, 0.3f)),
    Vertex(QVector3D(-2.0f / 3, 1.0f / 3, -1.0f / 3), QVector4D(1.0f, 1.0f, 1.0f, 0.2f)),
    Vertex(QVector3D(1.0f / 3, 1.0f / 3, 2.0f / 3), QVector4D(1.0f, 1.0f, 1.0f, 0.0f))
  };

  int blend() const override {
    return 2;
  }

  QVector3D axis;
  QVector3D velocity;
};

#endif //INC_1760_GLOSSYSHARD_H
