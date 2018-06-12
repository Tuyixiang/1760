//
// Created by Yixiang Tu on 08/06/2018.
//

#ifndef INC_1760_TREETRUNK_H
#define INC_1760_TREETRUNK_H

#include "../../template/Body.h"

class TreeTrunk : public Body {

protected:
  Vertex _vertices[12] = {
    Vertex(QVector3D(-0.5f, -4, -1), QVector4D(0.54f, 0.27f, 0.09f, 1)),
    Vertex(QVector3D(0, -4, -0.5f), QVector4D(0.54f, 0.27f, 0.09f, 1)),
    Vertex(QVector3D(0.5f, -4, -1), QVector4D(0.54f, 0.27f, 0.09f, 1)),
    Vertex(QVector3D(0, -4, -1.5f), QVector4D(0.54f, 0.27f, 0.09f, 1)),
    Vertex(QVector3D(-0.5f, 2, -1), QVector4D(0.54f, 0.27f, 0.09f, 1)),
    Vertex(QVector3D(0, 2, -0.5f), QVector4D(0.54f, 0.27f, 0.09f, 1)),
    Vertex(QVector3D(0.5f, 2, -1), QVector4D(0.54f, 0.27f, 0.09f, 1)),
    Vertex(QVector3D(0, 2, -1.5f), QVector4D(0.54f, 0.27f, 0.09f, 1)),
    Vertex(QVector3D(-0.5f, 2, -1), QVector4D(1, 0.86f, 0.7f, 1)),
    Vertex(QVector3D(0, 2, -0.5f), QVector4D(1, 0.86f, 0.7f, 1)),
    Vertex(QVector3D(0.5f, 2, -1), QVector4D(1, 0.86f, 0.7f, 1)),
    Vertex(QVector3D(0, 2, -1.5f), QVector4D(1, 0.86f, 0.7f, 1))
  };

public:
#ifndef NDEBUG

  const QString className() override {
    return QString("TreeTrunk");
  }

#endif

  TreeTrunk(const Scene* parent, int id);


  //  Typically we'll simply use this frag source
  const QString& fragSource() const override;

  //  Typically we'll simply use this vert source
  const QString& vertSource() const override;

  const Vertex* vertices() override {
    return _vertices;
  }

};


#endif //INC_1760_TREETRUNK_H
