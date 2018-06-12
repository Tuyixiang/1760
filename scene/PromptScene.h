//
// Created by Yixiang Tu on 08/06/2018.
//

#ifndef INC_1760_PROMPTSCENE_H
#define INC_1760_PROMPTSCENE_H
#include "../template/Scene.h"

class PromptScene : public Scene {

protected:
  int _style;

public:
  void onInitialize() final {}

  explicit PromptScene(GLWidget* parent, int style);

  bool keyPress(int key) final;

  void mouseClick(const QPoint& position) final;

  void onFrame() final;

  enum DefaultPrompts {
    gameover = 0,
    credit = 1,
    toBeContinued = 2,
  };

};


#endif //INC_1760_PROMPTSCENE_H
