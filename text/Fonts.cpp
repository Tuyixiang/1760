//
// Created by Yixiang Tu on 03/06/2018.
//

#include "Fonts.h"

fonts::mmScene::Title::Title(Scene* parent) : Text(parent) {
  xLeft = 0;
  xRight = 1;
  yTop = 0;
  yBottom = 0.7;
  _pen.setColor(QColor(255, 255, 255, 204));
  _text = QString("Overture:");
  _text2 = QString("1760");
  alignStyle = Qt::AlignTop | Qt::AlignHCenter;
}

void fonts::mmScene::Title::draw(QPainter& painter) {
  painter.setPen(_pen);
  _font.setPointSize(_parent->height() / 20);
  _font.setFamily("Matematica");
  painter.setFont(_font);
  painter.drawText(QRect((int) (_parent->width() * xLeft),
                         (int) (_parent->height() * 0.25f),
                         (int) (_parent->width() * (xRight - xLeft)),
                         (int) (_parent->height() * (yBottom - yTop))),
                   alignStyle, _text);
  _font.setPointSize(_parent->width() * 2 / 15);
  _font.setFamily("HYAlzheimer");
  painter.setFont(_font);
  painter.drawText(QRect((int) (_parent->width() * xLeft),
                         (int) (_parent->height() * 0.3f),
                         (int) (_parent->width() * (xRight - xLeft)),
                         (int) (_parent->height() * (yBottom - yTop))),
                   alignStyle, _text2);
}

fonts::mmScene::Hint::Hint(Scene* parent) : Text(parent) {
  xLeft = 0;
  xRight = 1;
  yTop = 0.7;
  yBottom = 0.8;
  _r = _g = _b = 255;
  opacity = 0.8f;
  _font.setFamily("Athelas");
  _widthSize = 1.0f / 30;
  _text = QString("Press [Enter] to continue.");
}

fonts::as1::Score::Score(Scene* parent) : Text(parent) {
  xLeft = 0;
  xRight = 1;
  yTop = 0;
  yBottom = 1;
  _r = _g = _b = 0;
  _font.setFamily("Beleren");
  _widthSize = 1.0f / 15;
  alignStyle = Qt::AlignTop | Qt::AlignLeft;

}

void fonts::as1::Score::updateScore(int score) {
  if (_score != score) {
    _score = score;
    _blinkCounter = 32;
  }
}

void fonts::as1::Score::draw(QPainter& painter) {
  if (_blinkCounter) {
    _blinkCounter--;
    if (_blinkCounter & 0b1000) {
      _r = _g = _b = 255;
    } else {
      _r = _g = _b = 0;
    }
  } else {
    _r = _g = _b = 0;
  }
  Text::draw(painter);
}

fonts::as1::Hint::Hint(Scene* parent) : Text(parent) {
  xLeft = 0;
  xRight = 1;
  yTop = 0.92f;
  yBottom = 1;
  _r = _g = _b = 255;
  _font.setFamily("Athelas");
  _widthSize = 1.0f / 45;
  alignStyle = Qt::AlignCenter;

}

fonts::ps::Title::Title(Scene* parent) : Text(parent) {
  xLeft = 0;
  xRight = 1;
  yTop = 0.3;
  yBottom = 0.7;
  _r = _g = _b = 255;
  _font.setFamily("HYAlzheimer");
  _widthSize = 1.0f / 12.0f;
  opacity = 0.8f;
  _text = QString("1760");
  alignStyle = Qt::AlignTop | Qt::AlignHCenter;
}

fonts::ps::Hint::Hint(Scene* parent) : Text(parent) {
  xLeft = 0;
  xRight = 1;
  yTop = 0.7;
  yBottom = 0.8;
  _r = _g = _b = 255;
  opacity = 0.8f;
  _font.setFamily("Athelas");
  _widthSize = 1.0f / 30;
  _text = QString("Press [Enter] to continue.");
}

fonts::ps::Scroll::Scroll(Scene* parent) : Text(parent) {
  yTop = 0.1f;
  _r = _g = _b = 255;
  opacity = 0.9f;
  _font.setFamily("Athelas");
  alignStyle = Qt::AlignCenter;
}

void fonts::ps::Scroll::setTextList(const std::vector<Line>& textList) {
  _lineList = textList;
}

void fonts::ps::Scroll::draw(QPainter& painter) {
  switch (displayPhase) {
    case 0: {
      if (!_lineList.empty()) {
        if (_lineList[0].blank) {
          timeCounter = _lineList[0].time;
          displayPhase = 4;
          return;
        } else {
          opacity = 1.0f / 60;
          displayPhase = 1;
        }
      }
      break;
    }
    case 1: {
      opacity += 1.0f / 60;
      if (opacity >= 1.0f) {
        displayPhase = 2;
        opacity = 1.0f;
        timeCounter = _lineList.front().time;
      }
      break;
    }
    case 2: {
      if (--timeCounter == 0) {
        displayPhase = 3;
      }
      break;
    }
    case 3: {
      opacity -= 1.0f / 60;
      if (opacity <= 0.0f) {
        _lineList.erase(_lineList.begin());
        opacity = 1.0f / 60;
        displayPhase = 0;
        return;
      }
      break;
    }
    case 4: {
      if (--timeCounter == 0) {
        displayPhase = 0;
        _lineList.erase(_lineList.begin());
      }
      return;
    }
    default:break;
  }

  _pen.setColor(QColor(_r, _g, _b, static_cast<int>(opacity * 255)));
  painter.setPen(_pen);
  if (!_lineList.empty()) {
    _font.setPixelSize(_lineList[0].size * _parent->width() / 1200);
    painter.setFont(_font);
    painter.drawText(QRect(0,
                           0,
                           _parent->width(),
                           _parent->height()),
                     alignStyle, _lineList[0].content);
  }
}

void fonts::ps::Scroll::onFrame() {
  yTop -= 0.001f;
}

bool fonts::ps::Scroll::toBeRemoved() const {
  return _lineList.empty();
}
