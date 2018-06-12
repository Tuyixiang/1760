//
// Created by Yixiang Tu on 08/06/2018.
//

#ifndef INC_1760_GAMEGLOBALS_H
#define INC_1760_GAMEGLOBALS_H


class GameGlobals {
private:
  GameGlobals() = default;

public:
  static GameGlobals& instance() {
    static GameGlobals singleton;
    return singleton;
  }

  GameGlobals(const GameGlobals& e) = delete;

  void operator=(const GameGlobals& e) = delete;

  void reset() {
    score = shooted = 0;
  }

  int score = 0;

  int shooted = 0;

};


#endif //INC_1760_GAMEGLOBALS_H
