//
// Created by Yixiang Tu on 28/05/2018.
//

#ifndef INC_1760_MAINMENUSCENE_H
#define INC_1760_MAINMENUSCENE_H

#include "../template/Scene.h"

class MainMenuScene : public Scene {

private:
  bool mouseMoved;
  QPoint lastMousePosition;
  QVector2D lastCameraTarget;

public:
  explicit MainMenuScene(GLWidget* parent);

  void onInitialize() final {}

  bool keyPress(int key) final;

  void cleanBoxes();

  //  Move camera according to mouse movement
  void mouseMove(const QPoint& position) final;

  void onFrame() final;
};

#endif //INC_1760_MAINMENUSCENE_H
