//
// Created by Yixiang Tu on 06/06/2018.
//

#ifndef INC_1760_NULLBODY_H
#define INC_1760_NULLBODY_H

#include "../template/Body.h"

class NullBody : public Body {

public:
#ifndef NDEBUG

  const QString className() final {
    return "NullBody";
  }

#endif

  NullBody(const Scene* parent, int id) : Body(parent, id) {}

  void initializeShader() final {}

  void draw(const QMatrix4x4& perspective, const QMatrix4x4& camera, const QVector3D& uniformLight,
            const QVector4D& light, GLWidget* parent) final {}

  const GLVertex* glVertices() const final {
    return nullptr;
  }

  const int size() const final {
    return 0;
  }

  const int count() const final {
    return 0;
  }

  bool initialized() const final {
    return true;
  }

  bool verticesChanged() const final {
    return false;
  }

  void refreshDraw() final {}

  void onFrame() final {}

  void updateGLVertices(GLVertex*& target) final {}

protected:
  void addTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3) final {}

  void addTriangle(int v1, int v2, int v3) final {}

  int blend() const final {
    return 0;
  }

  const Vertex* vertices() final {
    return nullptr;
  }

  const QString& fragSource() const final {
    static QString frag = "";
    return frag;
  }

  const QString& vertSource() const final {
    static QString vert = "";
    return vert;
  }

};


#endif //INC_1760_NULLBODY_H
