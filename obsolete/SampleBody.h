//
// Created by Yixiang Tu on 27/05/2018.
//

#ifndef INC_1760_SAMPLEBODY_H
#define INC_1760_SAMPLEBODY_H

#include "../template/BBody.h"
#include "../model/ShaderSource.h"
#include "../template/Scene.h"
#include "../GLWidget.h"
#include <cmath>


/**
 *  Create derived classes of Body like SampleBody.
 *
 *  Class Body is abstract and shouldn't be instantiated.
 *
 *  SampleBody contains the minimal elements a body class should have.
 */

class SampleBody : public Body {

public:


#ifndef NDEBUG

  const QString className() override {
    return QString("SampleBody");
  }

#endif


  SampleBody(const Scene* parent, int id);

  void onFrame() final;

  //  Typically we'll simply use this frag source
  const QString& fragSource() const final {

    /**
     *  src::frag and src::vert will return a default shader program.
     *
     *  src::fragNoLight and src::vertNoLight will return another,
     *      where light is not calculated, and where the original
     *      vertex colors are displayed as they are.
     */
    return src::fragGlossy;
  }

  //  Typically we'll simply use this vert source
  const QString& vertSource() const final {
    return src::vertTwoLights;
  }

  const Vertex* vertices() override {
    return _vertices;
  }

  void draw(const QMatrix4x4& perspective, const QMatrix4x4& camera, const QVector3D& uniformLight,
            const QVector4D& light, GLWidget* parent) override ;


protected:


  const Vertex _vertices[8] = {
    Vertex(QVector3D(0.5f, 0.5f, 0.5f), QVector4D(1.0f, 1.0f, 0.1f, 1.0f)),
    Vertex(QVector3D(-0.5f, 0.5f, 0.5f), QVector4D(1.0f, 1.0f, 0.1f, 1.0f)),
    Vertex(QVector3D(-0.5f, -0.5f, 0.5f), QVector4D(1.0f, 1.0f, 0.1f, 1.0f)),
    Vertex(QVector3D(0.5f, -0.5f, 0.5f), QVector4D(1.0f, 1.0f, 0.1f, 1.0f)),
    Vertex(QVector3D(0.5f, 0.5f, -0.5f), QVector4D(1.0f, 1.0f, 0.1f, 1.0f)),
    Vertex(QVector3D(-0.5f, 0.5f, -0.5f), QVector4D(1.0f, 1.0f, 0.1f, 1.0f)),
    Vertex(QVector3D(-0.5f, -0.5f, -0.5f), QVector4D(1.0f, 1.0f, 0.1f, 1.0f)),
    Vertex(QVector3D(0.5f, -0.5f, -0.5f), QVector4D(1.0f, 1.0f, 0.1f, 1.0f))
  };

  /*
   *  You may also want to create a derived class of Body,
   *    to perform physical actions with member variables
   *    like velocity.
   */
};

#endif //INC_1760_SAMPLEBODY_H
