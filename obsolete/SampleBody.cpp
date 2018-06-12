//
// Created by Yixiang Tu on 31/05/2018.
//

#include "SampleBody.h"
#include "../GLWidget.h"

SampleBody::SampleBody(const Scene* parent, int id) : Body(parent, id) {

  /** STEP1. DRAW BODY
   *
   *  In OpenGL, bodies are typically drawn with triangles.
   *  A triangle takes three vertices counter-clockwise to create a facet,
   *      (vertices clockwise will result in a facet to the back.)
   *
   *  To create a rigid body, simply record the vertex data in vertices[],
   *      and call addTriangle() on indices of three counter-clockwise vertices.
   */
  addTriangle(0, 1, 2);
  addTriangle(2, 3, 0);
  addTriangle(7, 5, 4);
  addTriangle(5, 7, 6);
  addTriangle(0, 4, 5);
  addTriangle(5, 1, 0);
  addTriangle(3, 2, 6);
  addTriangle(6, 7, 3);
  addTriangle(2, 1, 5);
  addTriangle(2, 5, 6);
  addTriangle(0, 3, 7);
  addTriangle(7, 4, 0);

  /** STEP2. INITIALIZE
   *
   *  Where would this body be in the space?
   *  See Transform3D.h for details
   */
  _transform.setPosition(0.0f, 0.0f, -3.0f);
  _transform.rotate((float) -(acos(1.0f / sqrt(3)) * 180 / 3.14), 1, 0, -1);

  /** STEP3. START A TIMER (IF NEEDED)
   *
   *  To start a timer:
   *      Timer::instance().startTimer(int timerId)
   *
   *  To get the time passed since start of the timer:
   *      Timer::instance().getTime(int timerId)
   *
   *  To get the time passed since the last call to this id:
   *      Timer::instance().lastPeriod(int timerId)
   *
   *  # ALL times are in milliseconds.
   *
   *  Also, Timer::instance().frameCounter() can return the
   *      frame counts since start of this program.
   */
  Timer::instance().startTimer(_id);
}

void SampleBody::onFrame() {

  /**
   *  This function is called after rendering a frame
   *      (or before, it's the same)
   *
   *  You may manipulate _transform here, anyway you want.
   *
   *  However, to manipulate vertex data, see GlossyBackground.h
   */
  _transform.rotate((float) Timer::instance().lastPeriod(_id) / 1000 * 180, QVector3D(1, 1, 1));
}

void SampleBody::draw(const QMatrix4x4& perspective, const QMatrix4x4& camera, const QVector3D& uniformLight,
                      const QVector4D& light, GLWidget* parent) {
  Body::draw(perspective, camera, uniformLight, light, parent);
}
