//
// Created by Yixiang Tu on 27/05/2018.
//

#ifndef INC_1760_BODY_H
#define INC_1760_BODY_H

#include <QOpenGLBuffer>
#include <QMatrix>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include "../global/Macro.h"
#include "../GLVertex.h"
#include "../Transform3D.h"
#include "../global/Timer.h"
#include "../Vertex.h"
#include <vector>
#include <QVector>

class GLWidget;

class Scene;

/// See model/SampleBody.h on how to construct and manage a static object
/// See model/GlossyBackground.h on how to manage a dynamic object
class Body {
public:
#ifndef NDEBUG

  virtual const QString className() = 0;

#endif

  //  For each type of bodies, a derived class must be used.
  //  The virtual functions must also be implemented.

  Body(const Scene* parent, int id) : _parent(parent), _id(id) {

#ifndef NDEBUG
    //Message::instance().show("Body constructed");
#endif
  }

  virtual ~Body();

  virtual void initializeShader();

  virtual void draw(const QMatrix4x4& perspective, const QMatrix4x4& camera, const QVector3D& uniformLight,
                    const QVector4D& light, GLWidget* parent);

  virtual const GLVertex* glVertices() const {
    return _glVertices.data();
  }

  virtual const int size() const {
    return count() * sizeof(GLVertex);
  }

  virtual const int count() const {
    return (int) _glVertices.size();
  }

  virtual bool initialized() const {
    return _initialized;
  }

  virtual bool verticesChanged() const {
    return _verticesChanged;
  }

  virtual void refreshDraw();

  virtual void onFrame();

  Transform3D& transform();

  virtual void updateGLVertices(GLVertex*& target) {}

  bool& toBeDestroyed() {
    return _toBeDestroyed;
  }

  bool& toBeRemoved() {
    return _toBeRemoved;
  }

protected:
  virtual void addTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3);

  virtual void addTriangle(int v1, int v2, int v3);

  virtual int blend() const {
    return 0;
  }

  std::vector<GLVertex> _glVertices;
  int glVertexCount = 0;

  const Scene* _parent;

  /**
   *  If this body is to be removed (e.g. out of sight),
   *    mark this true.
   *  It shall be removed in Scene::render()
   */
  bool _toBeDestroyed = false;
  bool _toBeRemoved = false;
  bool _initialized = false;
  bool _verticesChanged = false;

  const int _id;

  /// Shader information
  virtual const QString& fragSource() const = 0;

  virtual const QString& vertSource() const = 0;

  /// Drawing information
  struct DrawingBundle {
    QOpenGLShaderProgram* program = nullptr;
    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;

    ~DrawingBundle();
  } * drawingBundle = new DrawingBundle;

  Transform3D _transform;
  int positionMatrix;
  int perspectiveMatrix;
  int lightSourcePosition;
  int normalMatrix;
  int uniformLightDirection;

  virtual const Vertex* vertices() {
    return _vertices;
  }

  int refreshDrawCountDown = 0;


private:
  const Vertex _vertices[0];
};


#endif //INC_1760_BODY_H
