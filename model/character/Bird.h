//
// Created by Yixiang Tu on 04/06/2018.
//

#ifndef INC_1760_BIRD_H
#define INC_1760_BIRD_H
#include "../../template/BCharacter.h"

class BodyPart;

class BWorldScene;

class Bird : public BCharacter {

protected:
  BodyPart* leftWing;
  BodyPart* rightWing;
  BodyPart* body;

public:

#ifndef NDEBUG

  const QString className() override {
    return QString("Bird");
  }

#endif

  Bird(BWorldScene* parent, int id, b2World* parentWorld, const QString& name);

  void initializeBBody() override;

  void constructVertices() override;

  void updateGLVertices(GLVertex*& target) override;

  int wingPhase = 0;
  int movePhase = 0;
  void onFrame() override;

  int flyingIn = 0;
  void flyIn();

  int blend() const override;

  const int count() const override;

  void onDestroy() override;

};


#endif //INC_1760_BIRD_H
