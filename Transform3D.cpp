//
// Created by Yixiang Tu on 27/05/2018.
//

#include "Transform3D.h"

const QMatrix4x4& Transform3D::matrix() {
  if (changed) {
    world.setToIdentity();
    world.translate(_position);
    world.rotate(_rotation);
    world.scale(_size);
    changed = false;
  }
  return world;
}
