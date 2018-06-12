//
// Created by Yixiang Tu on 04/06/2018.
//

#ifndef INC_1760_BCHARACTER_H
#define INC_1760_BCHARACTER_H
#include "BPolygon.h"
#include "BodyPart.h"
#include <vector>

class BWorldScene;

class BCharacter : public BPolygon {
protected:
  std::vector<BodyPart*> partList;

  BWorldScene* _parent;

public:
  BCharacter(BWorldScene* parent, int id, b2World* parentWorld, const QString& name);

  ~BCharacter() override;

  void onFrame() override;

  void draw(const QMatrix4x4& perspective, const QMatrix4x4& camera, const QVector3D& uniformLight,
                 const QVector4D& light, GLWidget* parent) override;

  void updateGLVertices(GLVertex*& target) override;

  const GLVertex* glVertices() const override {
    return nullptr;
  }

  /// Game Logic
protected:
  int _reward = 0;
  int _timeLasted = 0;
  int _timeOffset;
  bool _inRange = false;
  int _lifeTime;

public:
  int timeLasted() const {
    return _timeLasted;
  }

  int time() const {
    return _timeLasted + _timeOffset;
  }

  int& lifeTime() {
    return _lifeTime;
  }

  void setReward(int x) {
    _reward = x;
  }

  bool& inRange() {
    return _inRange;
  }

};


#endif //INC_1760_BCHARACTER_H
