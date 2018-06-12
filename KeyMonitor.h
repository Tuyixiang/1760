//
// Created by Yixiang Tu on 28/05/2018.
//

#ifndef INC_1760_KEYMONITOR_H
#define INC_1760_KEYMONITOR_H

#include "global/Macro.h"
#include <QKeyEvent>
#include <map>

class KeyMonitor {

public:
  KeyMonitor() = default;

  void keyPress(int key) {
    keyDownStatus[key] = true;
  }

  void keyRelease(int key) {
    keyDownStatus[key] = false;
  }

  bool keyIsDown(int key) {
    return keyDownStatus[key];
  }

  int DA() {
    return keyDownStatus[Qt::Key_D] - keyDownStatus[Qt::Key_A];
  }

  void reset() {
    for (auto& x: keyDownStatus) {
      x.second = false;
    }
  }

protected:
  std::map<int, bool> keyDownStatus;

};


#endif //INC_1760_KEYMONITOR_H
