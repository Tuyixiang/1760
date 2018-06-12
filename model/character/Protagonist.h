//
// Created by Yixiang Tu on 01/06/2018.
//

#ifndef INC_1760_PROTAGONIST_H
#define INC_1760_PROTAGONIST_H

#include "../../template/BCharacter.h"

class BodyPart;
class GLVertex;

class Protagonist : public BCharacter {

  friend class BWorldScene;

public:
  float walkAngle;

protected:
  BodyPart* leftLeg;
  BodyPart* rightLeg;
  BodyPart* upperBody;
  BodyPart* lowerBody;
  BodyPart* head;
  BodyPart* leftArm;
  BodyPart* rightArm;
  QVector4D color1 = QVector4D(1.0f, 0.7f, 0.0f, 1.0f);
  QVector4D color2 = QVector4D(1.0f, 0.3f, 0.0f, 1.0f);

  /// Animation
  int shakePhase = 0;
  int walkPhase = 0;
  b2Vec2 lastTwoPosition[3];

  /// Game Logic
  float toxicLevel = 0; //When this reaches 1.0f, protagonist dies
  float lastTwoYVelocity[2];  //YVelocities in the last two frames are 0 -> protagonist has landed

public:
#ifndef NDEBUG

  const QString className() override {
    return QString("Protagonist");
  }

#endif

  /// Initialization

  Protagonist(BWorldScene* parentScene, int id, b2World* parentWorld, const QString& name);

  void initializeBBody() override {
    _bodyDef->fixedRotation = true;
    BCharacter::initializeBBody();
  }

  void constructVertices() override;

  void updateGLVertices(GLVertex*& target) override;

  /// Animation

  void onFrame() override;

  /// Status

  bool land();

  int destructionCountDown = 60;
  float destructionMoveSpeed;
  void onDestroy() override;


  const int count() const override;

};


#endif //INC_1760_PROTAGONIST_H
