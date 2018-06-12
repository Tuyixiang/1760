//
// Created by Yixiang Tu on 07/06/2018.
//

#ifndef INC_1760_TREE_H
#define INC_1760_TREE_H
#include "../../template/BCharacter.h"

class TreeTrunk;

/**
 *  Tree has an original mass of inf
 *  Upon destruction, mass is set to zero
 */
class Tree : public BCharacter {

protected:
  BodyPart* topBranch;
  BodyPart* leftBranch;
  BodyPart* rightBranch;

  TreeTrunk* trunk;

public:

#ifndef NDEBUG

  const QString className() override {
    return QString("Bird");
  }

#endif

  Tree(BWorldScene* parent, int id, b2World* parentWorld, const QString& name, TreeTrunk* treeTrunk);

  void initializeSize(float halfWidth, float halfHeight, float depth) override;

  void initializePosition(float x, float y) override;

  void initializeBBody() override;

  void constructVertices() override;

  void updateGLVertices(GLVertex*& target) override;

  int wingPhase = 0;
  int movePhase = 0;
  void onFrame() override;

  int blend() const override;

  const int count() const override;

  void onDestroy() override;
};


#endif //INC_1760_TREE_H
