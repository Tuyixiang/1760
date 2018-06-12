//
// Created by Yixiang Tu on 31/05/2018.
//

#include "GroupedBody.h"
#include "../template/Scene.h"
#include "../GLWidget.h"


void GroupedBody::initializeShader() {
  drawingBundle->program = new QOpenGLShaderProgram();
  drawingBundle->program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertSource());
  drawingBundle->program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragSource());
  //drawingBundle->program->link();
  drawingBundle->program->bind();

  positionMatrix = drawingBundle->program->uniformLocation("positionMatrix");
  perspectiveMatrix = drawingBundle->program->uniformLocation("perspectiveMatrix");
  lightSourcePosition = drawingBundle->program->uniformLocation("lightSourcePosition");
  normalMatrix = drawingBundle->program->uniformLocation("normalMatrix");
  uniformLightDirection = drawingBundle->program->uniformLocation("uniformLightDirection");

  drawingBundle->vbo.create();
  drawingBundle->vbo.bind();
  drawingBundle->vbo.setUsagePattern(QOpenGLBuffer::DynamicDraw);
  //  Copy the vertices information to buffer
  drawingBundle->vbo.allocate(size());

  drawingBundle->vao.create();
  drawingBundle->vao.bind();
  //  AttributeArray stores vertex position, color, and normal vector
  drawingBundle->program->enableAttributeArray(0);
  drawingBundle->program->enableAttributeArray(1);
  drawingBundle->program->enableAttributeArray(2);
  //  Inform shader program of how to read this continuous data
  drawingBundle->program->setAttributeBuffer(0, GL_FLOAT, GLVertex::positionOffset(), GLVertex::PositionTupleSize,
                                             GLVertex::stride());
  drawingBundle->program->setAttributeBuffer(1, GL_FLOAT, GLVertex::colorOffset(), GLVertex::ColorTupleSize,
                                             GLVertex::stride());
  drawingBundle->program->setAttributeBuffer(2, GL_FLOAT, GLVertex::normalOffset(), GLVertex::NormalTupleSize,
                                             GLVertex::stride());

  //GLVertex* data = static_cast<GLVertex*>(drawingBundle->vbo.map(QOpenGLBuffer::WriteOnly));
  //for (auto pair: _bodyMap) {
  //  pair.second->updateGLVertices(data);
  //}
  //drawingBundle->vbo.unmap();

  drawingBundle->vao.release();
  drawingBundle->vbo.release();
  drawingBundle->program->release();


  _initialized = true;
}

void GroupedBody::draw(const QMatrix4x4& perspective, const QMatrix4x4& camera, const QVector3D& uniformLight,
                       const QVector4D& light, GLWidget* parent) {
  parent->glEnable(GL_DEPTH_TEST);
  drawingBundle->program->bind();
  drawingBundle->vbo.bind();
  GLVertex* data = static_cast<GLVertex*>(drawingBundle->vbo.map(QOpenGLBuffer::WriteOnly));
  for (auto pair: _bodyMap) {
    pair.second->updateGLVertices(data);
  }
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
}
