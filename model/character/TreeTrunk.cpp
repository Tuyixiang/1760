//
// Created by Yixiang Tu on 08/06/2018.
//

#include "TreeTrunk.h"
#include "../ShaderSource.h"

const QString& TreeTrunk::fragSource() const {
  return src::fragBWorldComp;
}

const QString& TreeTrunk::vertSource() const {
  return src::vertTwoLightsComp;
}

TreeTrunk::TreeTrunk(const Scene* parent, int id) : Body(parent, id) {
  addTriangle(0, 1, 4);
  addTriangle(1, 5, 4);
  addTriangle(1, 2, 5);
  addTriangle(2, 6, 5);
  addTriangle(8, 9, 10);
  addTriangle(8, 10, 11);
}
