//
// Created by Yixiang Tu on 28/05/2018.
//

#ifndef INC_1760_FONTS_H
#define INC_1760_FONTS_H

#include "../template/Text.h"
#include "../template/Scene.h"

namespace fonts {
  namespace mmScene {
    class Title : public Text {
    protected:
      QString _text2;

    public:
      explicit Title(Scene* parent);

      void draw(QPainter& painter) override;
    };

    class Hint : public Text {
    public:
      explicit Hint(Scene* parent);
    };

  }

  namespace as1 {

    class Score : public Text {
    protected:
      int _score = 0;
      int _blinkCounter = 0;
    public:
      explicit Score(Scene* parent);
      void updateScore(int score);
      void draw(QPainter& painter) override;
    };

    class Hint : public Text {
    public:
      explicit Hint(Scene* parent);
    };
  }

  namespace ps {
    struct Line {
      QString content;
      int time;
      int size;
      bool blank;
      explicit Line(const QString& c, int t = 60, int s = 40) {
        content = c;
        time = t;
        size = s;
        blank = false;
      }
      explicit Line(int t = 30) {
        blank = true;
        time = t;
      }
    };
    class Title : public Text {
    public:
      explicit Title(Scene* parent);
    };

    class Hint : public Text {
    public:
      explicit Hint(Scene* parent);
    };

    class Scroll : public Text{
    protected:
      int timeCounter = 0;
      int displayPhase = 0;
      std::vector<Line> _lineList;
    public:
      explicit Scroll(Scene* parent);
      void setTextList(const std::vector<Line>& textList);
      void draw(QPainter& painter) override;
      void onFrame() override;
      bool toBeRemoved() const override;
    };
  }
}

#endif //INC_1760_FONTS_H
