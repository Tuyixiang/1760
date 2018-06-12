//
// Created by Yixiang Tu on 28/05/2018.
//
#include "Text.h"
#include "Scene.h"

void Text::draw(QPainter& painter) {
  if (fadeSpeed) {
    opacity += fadeSpeed;
    if (opacity >= 1.0f) {
      opacity = 1.0f;
      fadeSpeed = 0;
    } else if (opacity <= 0.0f) {
      opacity = 0.0f;
    }
  }
  _pen.setColor(QColor(_r, _g, _b, static_cast<int>(opacity * 255)));
  painter.setPen(_pen);
  _font.setPixelSize(static_cast<int>(_parent->width() * _widthSize));
  painter.setFont(_font);
  painter.drawText(QRect((int) (_parent->width() * xLeft),
                         (int) (_parent->height() * yTop),
                         (int) (_parent->width() * (xRight - xLeft)),
                         (int) (_parent->height() * (yBottom - yTop))),
                   alignStyle, _text);
}

void Text::fadeIn() {
  opacity = 1.0f / 60;
  fadeSpeed = 1.0f / 60;
}

void Text::fadeOut() {
  fadeSpeed = -1.0f / 60;
}
