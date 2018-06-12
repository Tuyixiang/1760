//
// Created by Yixiang Tu on 30/05/2018.
//

#ifndef INC_1760_BBODY_H
#define INC_1760_BBODY_H

#include "Body.h"
#include "../model/ShaderSource.h"

class BBody : public Body {

  friend class GroupedBody;

public:
  BBody(const Scene* parent, int id, b2World* parentWorld) : Body(parent, id), _parentWorld(parentWorld) {
    _transform.setPosition(0, 0, 0);
  }

  ~BBody() override;

  void onFrame() override;

  void draw(const QMatrix4x4& perspective, const QMatrix4x4& camera, const QVector3D& uniformLight,
            const QVector4D& light, GLWidget* parent) override;

  b2Body* body() {
    return _this;
  }

  std::map<QString, b2Joint*>& jointMap() {
    return _jointMap;
  };

protected:

  QString _name;

  void transformAndWriteTriangle(GLVertex*& target, int v1, int v2, int v3);

  std::vector<Vertex> _vertices;

  virtual void constructVertices() = 0;

  virtual void initializeBBody() = 0;

  //  Typically we'll simply use this frag source
  const QString& fragSource() const override {
    return src::fragBWorldComp;
  }

  //  Typically we'll simply use this vert source
  const QString& vertSource() const override {
    return src::vertTwoLightsComp;
  }

  b2World* const _parentWorld;
  b2Body* _this = nullptr;
  b2BodyDef* _bodyDef = nullptr;
  b2Shape* _shape = nullptr;
  b2FixtureDef* _fixtureDef = nullptr;
  std::map<QString, b2Joint*> _jointMap;

  /// Game Logic
protected:
  int _maxHp = 0x7fffffff;
  int _damage = 0;
  bool _canBeDestroyed = false;
  QVector4D _color;

  bool visible = true;


public:

  void setVisibility(bool vis) {
    visible = vis;
  }

  void setMaxHp(int hp) {
    _maxHp = hp;
  }

  void damage(int amount) {
    _damage += amount;
  }

  bool& canBeDestroyed() {
    return _canBeDestroyed;
  }

  virtual void onDestroy() {}

};


#endif //INC_1760_BBODY_H
