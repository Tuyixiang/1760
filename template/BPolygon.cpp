//
// Created by Yixiang Tu on 31/05/2018.
//

#include "BPolygon.h"

void BPolygon::constructVertices() {
  _vertices.clear();
  _vertices.emplace_back(QVector3D(-_halfWidth, _halfHeight, 0), _color);
  _vertices.emplace_back(QVector3D(-_halfWidth, -_halfHeight, -0), _color);
  _vertices.emplace_back(QVector3D(_halfWidth, -_halfHeight, -0), _color);
  _vertices.emplace_back(QVector3D(_halfWidth, _halfHeight, -0), _color);
  _vertices.emplace_back(QVector3D(-_halfWidth, _halfHeight, -_depth), _color);
  _vertices.emplace_back(QVector3D(-_halfWidth, -_halfHeight, -_depth), _color);
  _vertices.emplace_back(QVector3D(_halfWidth, -_halfHeight, -_depth), _color);
  _vertices.emplace_back(QVector3D(_halfWidth, _halfHeight, -_depth), _color);
  addTriangle(0, 1, 2);
  addTriangle(0, 2, 3);
  addTriangle(4, 0, 3);
  addTriangle(4, 3, 7);
  addTriangle(4, 5, 1);
  addTriangle(4, 1, 0);
  addTriangle(1, 5, 6);
  addTriangle(1, 6, 2);
  addTriangle(3, 2, 6);
  addTriangle(3, 6, 7);
}

void BPolygon::updateGLVertices(GLVertex*& target) {
  if (visible) {
    transformAndWriteTriangle(target, 0, 1, 2);
    transformAndWriteTriangle(target, 0, 2, 3);
    transformAndWriteTriangle(target, 4, 0, 3);
    transformAndWriteTriangle(target, 4, 3, 7);
    transformAndWriteTriangle(target, 4, 5, 1);
    transformAndWriteTriangle(target, 4, 1, 0);
    transformAndWriteTriangle(target, 1, 5, 6);
    transformAndWriteTriangle(target, 1, 6, 2);
    transformAndWriteTriangle(target, 3, 2, 6);
    transformAndWriteTriangle(target, 3, 6, 7);
  }
}

BPolygon::BPolygon(const Scene* parentScene, int id, b2World* parentWorld, const QString& name) : BBody(parentScene, id,
                                                                                                  parentWorld) {
  _name = name;
  _bodyDef = new b2BodyDef;
  _shape = new b2PolygonShape;
  _fixtureDef = new b2FixtureDef;
}

void BPolygon::initializeBBody() {
  _this = _parentWorld->CreateBody(_bodyDef);
  _fixtureDef->shape = _shape;
  _fixtureDef->filter.categoryBits = collisionGroup;
  _fixtureDef->filter.maskBits = collisionMask;
  _this->CreateFixture(_fixtureDef);
  _this->SetUserData(reinterpret_cast<void*> (&_name));
  if (visible) {
    constructVertices();
  }
}

BPolygon::~BPolygon() = default;
