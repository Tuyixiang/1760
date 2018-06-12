//
// Created by Yixiang Tu on 27/05/2018.
//

#include "Body.h"
#include "../GLWidget.h"

/*
   * NOTE ON HOW TO USE THIS
   *
   * Typically, there will be several distinct object in the scene;
   * To manipulate them, create a VBO (QOpenGLBuffer) for each of them;
   * Here's the sample to create one.
   *
   * However, if the object's shape is changing,
   * this initialization process should be partly repeated each frame,
   * in order to onFrame the vertices information.
   */
void Body::initializeShader() {
  drawingBundle->program = new QOpenGLShaderProgram();
  drawingBundle->program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertSource());
  drawingBundle->program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragSource());
  drawingBundle->program->bindAttributeLocation("position", 0);
  drawingBundle->program->bindAttributeLocation("color", 1);
  drawingBundle->program->bindAttributeLocation("normal", 2);
  drawingBundle->program->link();
  drawingBundle->program->bind();

  positionMatrix = drawingBundle->program->uniformLocation("positionMatrix");
  perspectiveMatrix = drawingBundle->program->uniformLocation("perspectiveMatrix");
  lightSourcePosition = drawingBundle->program->uniformLocation("lightSourcePosition");
  normalMatrix = drawingBundle->program->uniformLocation("normalMatrix");
  uniformLightDirection = drawingBundle->program->uniformLocation("uniformLightDirection");

  drawingBundle->vbo.create();
  drawingBundle->vbo.bind();
  /*
   * Use StaticDraw if vertices are static;
   * Otherwise, use DynamicDraw
   */
  drawingBundle->vbo.setUsagePattern(QOpenGLBuffer::DynamicDraw);
  //  Copy the vertices information to buffer
  if(glVertices()) {
    drawingBundle->vbo.allocate(glVertices(), size());
  } else {
    drawingBundle->vbo.allocate(size());
  }

  drawingBundle->vao.create();
  drawingBundle->vao.bind();
  //  AttributeArray stores vertex position, color, and normal vector
  drawingBundle->program->enableAttributeArray(0);
  drawingBundle->program->enableAttributeArray(1);
  drawingBundle->program->enableAttributeArray(2);
  //  Inform shader program of how to read this continuous data
  drawingBundle->program->setAttributeBuffer(0, GL_FLOAT, GLVertex::positionOffset(), GLVertex::PositionTupleSize, GLVertex::stride());
  drawingBundle->program->setAttributeBuffer(1, GL_FLOAT, GLVertex::colorOffset(), GLVertex::ColorTupleSize, GLVertex::stride());
  drawingBundle->program->setAttributeBuffer(2, GL_FLOAT, GLVertex::normalOffset(), GLVertex::NormalTupleSize, GLVertex::stride());

  drawingBundle->vao.release();
  drawingBundle->vbo.release();
  drawingBundle->program->release();

  _initialized = true;
}

void Body::draw(const QMatrix4x4& perspective, const QMatrix4x4& camera, const QVector3D& uniformLight,
                const QVector4D& light, GLWidget* parent) {
  //bool justInitialized = false;
  if (!_initialized) {
    initializeShader();
    //justInitialized = true;
  }
  switch (blend()) {
    case 2: {
      parent->glEnable(GL_BLEND);
      parent->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      parent->glDisable(GL_DEPTH_TEST);
      parent->glDepthMask(GL_FALSE);
      break;
    }
    case 1: {
      parent->glEnable(GL_BLEND);
      parent->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      break;
    }
    default: {
      parent->glEnable(GL_DEPTH_TEST);
      parent->glDepthMask(GL_TRUE);
      break;
    }
  }
  if (!_verticesChanged) {
    drawingBundle->program->bind();
    drawingBundle->vao.bind();
    drawingBundle->program->setUniformValue(perspectiveMatrix, perspective);
    drawingBundle->program->setUniformValue(positionMatrix, camera * _transform.matrix());
    drawingBundle->program->setUniformValue(lightSourcePosition, light);
    drawingBundle->program->setUniformValue(normalMatrix, _transform.matrix().normalMatrix());
    drawingBundle->program->setUniformValue(uniformLightDirection, uniformLight);
    parent->glDrawArrays(GL_TRIANGLES, 0, count());
    drawingBundle->vao.release();
    drawingBundle->program->release();
  } else {
    drawingBundle->program->bind();
    drawingBundle->vbo.bind();
    auto* data = static_cast<GLVertex*>(drawingBundle->vbo.map(QOpenGLBuffer::WriteOnly));
    updateGLVertices(data);
    drawingBundle->vbo.unmap();
    drawingBundle->vao.bind();
    drawingBundle->program->setUniformValue(perspectiveMatrix, perspective);
    drawingBundle->program->setUniformValue(positionMatrix, camera * _transform.matrix());
    drawingBundle->program->setUniformValue(lightSourcePosition, light);
    drawingBundle->program->setUniformValue(normalMatrix, _transform.matrix().normalMatrix());
    drawingBundle->program->setUniformValue(uniformLightDirection, uniformLight);
    parent->glDrawArrays(GL_TRIANGLES, 0, count());
    drawingBundle->vao.release();
    drawingBundle->vbo.release();
    drawingBundle->program->release();
    _verticesChanged = false;
  }
  if (blend() == 2) {
    parent->glEnable(GL_DEPTH_TEST);
    parent->glDepthMask(GL_TRUE);
  }

}

Transform3D& Body::transform() {
  return _transform;
}

/**
 * Construct a triangular side for the body.
 * NOTE that the vertices should be in counter-clockwise order,
 * otherwise, the side is only visible from the back.
 * @param v1
 * @param v2
 * @param v3
 */
void Body::addTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3) {
  QVector3D normal = QVector3D::normal(v1.position() - v2.position(), v2.position() - v3.position());
  _glVertices.emplace_back(v1.position(), v1.color(), normal);
  _glVertices.emplace_back(v2.position(), v2.color(), normal);
  _glVertices.emplace_back(v3.position(), v3.color(), normal);
  glVertexCount += 3;
}

/**
 * Construct a triangular side for the body. <br>
 * NOTE that the vertices should be in counter-clockwise order,
 * otherwise, the side is only visible from the back.<p>
 * v1~v3 are indices of vertices in "Vertex vertices[]"
 * @param v1
 * @param v2
 * @param v3
 */
void Body::addTriangle(int v1, int v2, int v3) {
  addTriangle(vertices()[v1], vertices()[v2], vertices()[v3]);
}

Body::~Body() {
  delete drawingBundle;
#ifndef NDEBUG
  //Message::instance().show("Body deleted");
#endif
}

void Body::refreshDraw() {
  delete drawingBundle;
  drawingBundle = new DrawingBundle();
  _initialized = false;
}

void Body::onFrame() {
  //if (!(refreshDrawCountDown--)) {
  //  refreshDraw();
  //  refreshDrawCountDown = Random::instance().getBetween(120, 300);
  //  SM(className() + " Refreshed");
  //}
}

Body::DrawingBundle::~DrawingBundle() {
  delete program;
  try {
    vbo.destroy();
    vao.destroy();
  } catch (...) {
    SM("FAILED TO DESTROY DRAWINGBUNDLE!");
  }
}
