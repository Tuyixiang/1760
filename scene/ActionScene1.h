//
// Created by Yixiang Tu on 31/05/2018.
//

#ifndef INC_1760_ACTIONSCENE1_H
#define INC_1760_ACTIONSCENE1_H
#include "../template/BWorldScene.h"

class ActionScene1 : public BWorldScene {

public:

  explicit ActionScene1(GLWidget* parent) : BWorldScene(parent) {
    memset(eventTriggered, 0, sizeof(eventTriggered));
  }

  void drawText(QPainter& painter) override;

protected:

  void initializeBodies() final;

  void initializeScene() final;

  void onEachFrame() final;

  /// Key input
  bool keyPress(int key) final;

  /// Mouse input
  QPoint mousePosition;
  bool mouseDown = false;
  void mouseMove(const QPoint& position) override;
  void mouseClick(const QPoint& position) override;
  void mouseRelease(const QPoint& position) override;

  /// Helpers
  bool outOfRange(const b2Vec2& position);

  /// Animation
  int windPhase = 0;
  int waterCreationCounter = 0;

  /// Game Logic
  int birdCounter = 0;
  int treeCounter = 0;
  bool eventTriggered[100];

protected:

  /// Game Actions
  Bird* spawnBird();

  Tree* spawnTree(float x);

  /// Hint display
  enum ControlHints {
    move = 0,
    jump = 1,
    bullets = 2,
    shoot = 3,
    choice = 4,
    coin = 5
  };
  int hintPhase = 0;
  int hintCompletion = 0;
  int hintToggleCountDown = 120;

  void manageHint();

  /// Constants
  b2ParticleDef _particleDef;
  const float ceilingHeight = 4.2f;
  const float groundHeight = -3.5f;
  const float halfWidth = 7.0f;
  const int pollutionRow = 40;
  const int pollutionCol = 64;

};


#endif //INC_1760_ACTIONSCENE1_H
