//
// Created by Yixiang Tu on 30/05/2018.
//

#ifndef INC_1760_BPOLYGON_H
#define INC_1760_BPOLYGON_H

#include "BBody.h"
#include "../global/Colors.h"

/**
 *  A B-Body associated with a rect in b2World
 */
class BPolygon : public BBody {

protected:

  float _halfWidth;
  float _halfHeight;
  float _depth;
  QVector4D _color = QVector4D(0, 0, 0, 0);
  QVector4D _newColor = QVector4D(0, 0, 0, 0);

  /**
   *  Collision groups:
   *  00000001. Ground
   *  00000010. Ceiling
   *  00000100. Side Wall
   *  00001000. Boundary walls
   *  00010000. Characters
   *  00100000. Tree
   */
  unsigned short collisionGroup = 1;
  unsigned short collisionMask = 0xFFFF;

  /**
   *  The vertices are in order:
   *    0. Top Left Front
   *    1. Bottom Left Front
   *    2. Bottom Right Front
   *    3. Top Right Front
   *    4. Top Left Back
   *    5. Bottom Left Back
   *    6. Bottom Right Back
   *    7. Top Right Back
   */
  void constructVertices() override;

  const Vertex* vertices() override {
    return _vertices.data();
  }

  void updateGLVertices(GLVertex*& target) override;

public:

  /*void draw(const QMatrix4x4& perspective, const QMatrix4x4& camera, const QVector3D& uniformLight,
       const QVector4D& light, GLWidget* parent) {
    printf("draw\n");
    Body::draw(perspective, camera, uniformLight, light, parent);
  }*/

#ifndef NDEBUG

  const QString className() override {
    return QString("BPolygon");
  }

#endif


  BPolygon(const Scene* parentScene, int id, b2World* parentWorld, const QString& name);

  ~BPolygon() override;

  virtual void initializeSize(float halfWidth, float halfHeight, float depth) {
    _halfWidth = halfWidth;
    _halfHeight = halfHeight;
    _depth = depth;
    ((b2PolygonShape*) _shape)->SetAsBox(_halfWidth, _halfHeight);
  }

  void setColor(const QVector4D& color) {
    _color = color;
  }

  void initializeBBody() override;

  virtual void initializePosition(float x, float y) {
    _transform.setPosition(b2Vec2(x, y));
    _bodyDef->position = b2Vec2(x, y);
  }

  void initializeDensity(float d) {
    _fixtureDef->density = d;
  }

  void initializeFriction(float f) {
    _fixtureDef->friction = f;
  }

  enum MovementType {
    dynamic,
    still
  };

  void initializeMovementType(MovementType t) {
    if (t == dynamic) {
      _bodyDef->type = b2_dynamicBody;
    } else {
      _bodyDef->type = b2_staticBody;
    }
  }

  b2BodyDef* bodyDef() {
    return _bodyDef;
  }

  float& halfWidth() {
    return _halfWidth;
  }

  float& halfHeight() {
    return _halfHeight;
  }

  void onFrame() override {
    _transform.setPosition(_this->GetPosition());
    _transform.setRotation(_this->GetAngle() * 180 / 3.14159f);
    BBody::onFrame();
  }

};

#endif //INC_1760_BPOLYGON_H
