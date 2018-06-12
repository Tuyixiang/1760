//
// Created by Yixiang Tu on 01/06/2018.
//

#include "Protagonist.h"
#include "../../global/Math.h"
#include "../../text/DebugText.h"

void Protagonist::constructVertices() {

  partList.clear();

  float ratio = _halfHeight;

  leftLeg = new BodyPart;
  leftLeg->setColor(color1);
  leftLeg->addVertex(QVector3D(-0.5f, -0.6f, 0));
  leftLeg->addVertex(QVector3D(-0.3f, -1.0f, 0));
  leftLeg->addVertex(QVector3D(-0.1f, -0.6f, 0));
  leftLeg->drawTriangle(0, 1, 2);
  leftLeg->transform().setSize(ratio);
  partList.push_back(leftLeg);

  rightLeg = new BodyPart;
  rightLeg->setColor(color1);
  rightLeg->addVertex(QVector3D(0.1f, -0.6f, 0));
  rightLeg->addVertex(QVector3D(0.3f, -1.0f, 0));
  rightLeg->addVertex(QVector3D(0.5f, -0.6f, 0));
  rightLeg->drawTriangle(0, 1, 2);
  rightLeg->transform().setSize(ratio);
  partList.push_back(rightLeg);

  lowerBody = new BodyPart;
  lowerBody->setColor(color2);
  lowerBody->addVertex(QVector3D(0, 0.25f, 0));
  lowerBody->addVertex(QVector3D(-0.6f, -0.5f, 0));
  lowerBody->addVertex(QVector3D(0.6f, -0.5f, 0));
  lowerBody->drawTriangle(0, 1, 2);
  lowerBody->transform().setSize(ratio);
  partList.push_back(lowerBody);


  upperBody = new BodyPart;
  upperBody->setColor(color2);
  upperBody->addVertex(QVector3D(0, -0.25f, 0));
  upperBody->addVertex(QVector3D(0.6f, 0.5f, 0));
  upperBody->addVertex(QVector3D(-0.6f, 0.5f, 0));
  upperBody->drawTriangle(0, 1, 2);
  upperBody->transform().setSize(ratio);
  partList.push_back(upperBody);

  head = new BodyPart;
  head->setColor(color1);
  head->addVertex(QVector3D(0, 0.5f, 0));
  head->addVertex(QVector3D(0.3f, 0.9f, 0));
  head->addVertex(QVector3D(-0.3f, 0.9f, 0));
  head->drawTriangle(0, 1, 2);
  head->transform().setSize(ratio);
  partList.push_back(head);

  leftArm = new BodyPart;
  leftArm->setColor(color1);
  leftArm->addVertex(QVector3D(0.4f, 0, 0));
  leftArm->addVertex(QVector3D(0.6f, -0.25f, 0));
  leftArm->addVertex(QVector3D(0.8f, 0, 0));
  leftArm->addVertex(QVector3D(0.6f, 0.25f, 0));
  leftArm->drawTriangle(0, 1, 2);
  leftArm->drawTriangle(0, 2, 3);
  leftArm->transform().setSize(ratio);
  partList.push_back(leftArm);

  rightArm = new BodyPart;
  rightArm->setColor(color1);
  rightArm->addVertex(QVector3D(-0.8f, 0, 0));
  rightArm->addVertex(QVector3D(-0.6f, -0.25f, 0));
  rightArm->addVertex(QVector3D(-0.4f, 0, 0));
  rightArm->addVertex(QVector3D(-0.6f, 0.25f, 0));
  rightArm->drawTriangle(0, 1, 2);
  rightArm->drawTriangle(0, 2, 3);
  rightArm->transform().setSize(ratio);
  partList.push_back(rightArm);
}

void Protagonist::onFrame() {

  if (!_toBeDestroyed) {
    /// Animation
    int frame = Timer::instance().frameCounter();
    lastTwoPosition[frame % 3] = _this->GetPosition();
    lastTwoYVelocity[frame & 1] = abs(_this->GetLinearVelocity().y);
    shakePhase += 48;

    auto armPosition = b2Vec2(0, 0.02f * sin(shakePhase)) + lastTwoPosition[(frame + 1) % 3] - _this->GetPosition();
    leftArm->transform().setPosition(armPosition);
    rightArm->transform().setPosition(armPosition);
    upperBody->transform().setY(0.03f * sin(shakePhase));
    lowerBody->transform().setY(0.015f * sin(shakePhase));
    head->transform().setY(0.04f * sin(shakePhase));

    if (land() and abs(_this->GetLinearVelocity().x) > 0.1f) {
      walkPhase += 144;
    } else if (walkPhase and walkPhase != 2880 and walkPhase != 5760) {
      if (walkPhase < 1440) {
        walkPhase /= 2;
      } else if (walkPhase < 4320) {
        walkPhase = 1440 + walkPhase / 2;
      } else {
        walkPhase = (5760 - walkPhase) / 2;
      }
    }
    leftLeg->transform().setX(0.1f * sin(walkPhase));
    rightLeg->transform().setX(-0.1f * sin(walkPhase));
    head->transform().setRotation(walkAngle * 15, QVector3D(0, 1, 0));
    upperBody->transform().setRotation(walkAngle * 15, QVector3D(0, 1, 0));
    lowerBody->transform().setRotation(walkAngle * 15, QVector3D(0, 1, 0));

    /// Health Display
    toxicLevel += _damage * 0.0016f;
    if (toxicLevel >= 1) {
      _toBeDestroyed = true;
      onDestroy();
    }
    toxicLevel = max(0, toxicLevel);
    for (auto* p: partList) {
      p->setDamage(toxicLevel);
    }
    IM(toxicLevel)
  } else {
    if (--destructionCountDown == 0) {
      destructionMoveSpeed = 0.3f;
    } else if (destructionCountDown < 0) {
      for (auto* p: partList) {
        p->transform().translate(0, destructionMoveSpeed, 0);
      }
      destructionMoveSpeed -= 0.01f;
      if (destructionCountDown == -80) {
        _toBeRemoved = true;
        SM("remove")
      }
    }
  }

  BCharacter::onFrame();
}

bool Protagonist::land() {
  return (lastTwoYVelocity[0] + lastTwoYVelocity[1] < 1e-5);
}

Protagonist::Protagonist(BWorldScene* parentScene, int id, b2World* parentWorld, const QString& name) : BCharacter(
  parentScene, id, parentWorld, name) {
  _transform.translate(0, 0, -0.5f);
  collisionGroup = 0b00010000;
  collisionMask = 0xFFFF;
}

const int Protagonist::count() const {
  return 81;
}

void Protagonist::updateGLVertices(GLVertex*& target) {
  BCharacter::updateGLVertices(target);
}

void Protagonist::onDestroy() {

}
