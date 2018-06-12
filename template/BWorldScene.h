//
// Created by Yixiang Tu on 30/05/2018.
//

/*
 * NOTES
 *
 * all object are automatically at (0, 0, -10)
 *    (inside constructor)
 */
#ifndef INC_1760_BWORLDSCENE_H
#define INC_1760_BWORLDSCENE_H

#include "Scene.h"
#include "BBody.h"
#include <map>
#include "../global/Colors.h"
#include "Text.h"
#include "../model/character/TreeTrunk.h"

class BPolygon;

class Protagonist;

class BCharacter;

class Bird;

class Tree;

class Wall;

class GLWidget;

namespace fonts {
  namespace as1 {
    class Score;
  }
}

class BWorldScene : public Scene {


public:
  explicit BWorldScene(GLWidget* parent);

  ~BWorldScene() override;


  /// Box2D Functionalities

protected:

  b2World* _world = nullptr;
  b2ParticleSystem* _particleSystem = nullptr;
  std::map<QString, BBody*> bodyMap;
  std::map<QString, BCharacter*> characterMap;
  //GroupedBody* group;
  std::map<QString, Text*> textMap;
  std::vector<QString> nameList;
  int nameIndex = 0;

  float timeStep = 1.0f / 60;
  const int velocityIteration = 6;
  const int positionIteration = 2;


  void createWorld(float x, float y) {
#ifndef NDEBUG
    if (_world) {
      throw std::runtime_error("b2World already created");
    }
#endif
    _world = new b2World(b2Vec2(x, y));
  }

  void createWorld(const b2Vec2& gravity) {
#ifndef NDEBUG
    if (_world) {
      throw std::runtime_error("b2World already created");
    }
#endif
    _world = new b2World(gravity);
  }

  b2Body* findBBody(const QString& name);

  BPolygon* createRect(const char* name);

  Protagonist* createProtagonist(const char* name);

  Bird* createBird(const QString& name);

  Tree* createTree(const QString& name, TreeTrunk* treeTrunk);

  /// QGL Functionalities
public:

  void onInitialize() override;

  void render(const QMatrix4x4& perspective) override;

  void drawText(QPainter& painter) override;

  void onFrame() override;


  /// Game Logic

public:

  void addScore(int bonus);

protected:

  fonts::as1::Score* scoreText;

  Protagonist* _pro;

  float cameraCenterXWorld;
  float cameraCenterYWorld;


  virtual void initializeScene() = 0;

  virtual void initializeBodies() = 0;

  virtual void onEachFrame();

  /// Default control scripts

  void proMovementControl();

  b2Vec2 mapScreenToWorld(const QPoint& position);

  QPoint mapWorldToScreen(const b2Vec2& position);


};

#endif //INC_1760_BWORLDSCENE_H
