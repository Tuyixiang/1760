//
// Created by Yixiang Tu on 31/05/2018.
//

#include "GlossyShard.h"
#include "../GLWidget.h"

GlossyShard::GlossyShard(const Scene* parent, int id) : Body(parent, id) {

  /// 1. Draw body
  addTriangle(0, 1, 2);
  addTriangle(0, 2, 1);

  /// 2. Set initial status
  _transform.setPosition(Random::instance().getBetween(-4, 4),
                         -4,
                         Random::instance().getFloat0() - 7);
  _transform.rotate(Random::instance().getBetween(0, 360), Random::instance().getV3());
  _transform.scale(Random::instance().getBetween(0.1f, 0.2f));
  axis = Random::instance().getV3();
  velocity = Random::instance().getV3() / 2000;

  /// Initialize timer (if needed)
  Timer::instance().startTimer(_id);
}

void GlossyShard::onFrame() {
  static int cnt = 0;
  int time = Timer::instance().lastPeriod(_id);
  _transform.rotate((float) time / 1000 * 60, axis);
  _transform.translate(velocity);
  velocity += QVector3D(0, 0.0001f, 0);
  if (++cnt % 5) {
    axis += Random::instance().getV3() / 20;
    velocity += Random::instance().getV3() / 10000;
  }
  if (_transform.position().y() >= 4) {
    _toBeRemoved = true;
  }
}

void GlossyShard::draw(const QMatrix4x4& perspective, const QMatrix4x4& camera, const QVector3D& uniformLight,
                       const QVector4D& light, GLWidget* parent) {
  parent->glClear(GL_DEPTH_BUFFER_BIT);
  Body::draw(perspective, camera, uniformLight, light, parent);
}
