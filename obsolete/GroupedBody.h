//
// Created by Yixiang Tu on 31/05/2018.
//

#ifndef INC_1760_GROUPEDBODY_H
#define INC_1760_GROUPEDBODY_H
#include "../template/BBody.h"


class GroupedBody: public Body {

protected:
  std::map<QString, BBody*>& _bodyMap;

  const Vertex vev[8] = {
    Vertex(QVector3D(0.5f, 0.5f, 0.5f), QVector4D(1.0f, 1.0f, 0.1f, 1.0f)),
    Vertex(QVector3D(-0.5f, 0.5f, 0.5f), QVector4D(1.0f, 1.0f, 0.1f, 1.0f)),
    Vertex(QVector3D(-0.5f, -0.5f, 0.5f), QVector4D(1.0f, 1.0f, 0.1f, 1.0f)),
    Vertex(QVector3D(0.5f, -0.5f, 0.5f), QVector4D(1.0f, 1.0f, 0.1f, 1.0f)),
    Vertex(QVector3D(0.5f, 0.5f, -0.5f), QVector4D(1.0f, 1.0f, 0.1f, 1.0f)),
    Vertex(QVector3D(-0.5f, 0.5f, -0.5f), QVector4D(1.0f, 1.0f, 0.1f, 1.0f)),
    Vertex(QVector3D(-0.5f, -0.5f, -0.5f), QVector4D(1.0f, 1.0f, 0.1f, 1.0f)),
    Vertex(QVector3D(0.5f, -0.5f, -0.5f), QVector4D(1.0f, 1.0f, 0.1f, 1.0f))
  };

  const Vertex* vertices() override {
    return vev;
  }

public:
#ifndef NDEBUG
  const QString className() override {
    return QString("GroupedBody");
  }
#endif

  [[deprecated]]
  GroupedBody(const Scene* parent, int id, std::map<QString, BBody*>& bodyMap) : Body(parent, id), _bodyMap(bodyMap) {

  }

  void initializeShader() override;

  void draw(const QMatrix4x4& perspective, const QMatrix4x4& camera, const QVector3D& uniformLight,
            const QVector4D& light, GLWidget* parent) override;

  void onFrame() override {}

  const int count() const override {
    return 1024;
  }

  //  Typically we'll simply use this frag source
  const QString& fragSource() const override {
    return src::fragGlossy;
  }

  //  Typically we'll simply use this vert source
  const QString& vertSource() const override {
    return src::vertTwoLights;
  }
};



#endif //INC_1760_GROUPEDBODY_H
