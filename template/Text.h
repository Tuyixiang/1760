//
// Created by Yixiang Tu on 28/05/2018.
//

#ifndef INC_1760_TEXT_H
#define INC_1760_TEXT_H

#include <QPainter>

class Scene;

class Text {

public:
  explicit Text(const Scene* parent) : _parent(parent) {}

  virtual void draw(QPainter& painter);

  QString& text() {
    return _text;
  }

  QPen& pen() {
    return _pen;
  }

  QFont& font() {
    return _font;
  }

  virtual void onFrame() {};

  void setText(const QString& newString) {
    _text = newString;
  }

  void setText(QString&& newString) {
    _text = newString;
  }

protected:
  const Scene* _parent;

  //  These values have range [0,1], corresponding to the percentage of the entire screen
  float xLeft, xRight, yTop, yBottom;

  //  see "enum Qt::AlignmentFlag" for possible flags
  //  Use | to select multiple
  int alignStyle = Qt::AlignCenter;
  QPen _pen;
  QFont _font;
  QString _text;
  float _widthSize;

  int _r, _g, _b;

  /// Timed destruction
  int timeCounter = 0;
  int _time = 60;
  float opacity = 1.0f;
  float fadeSpeed = 0;

public:
  void fadeIn();

  void fadeOut();

  virtual bool toBeRemoved() const {
    return !opacity or timeCounter >= _time;
  }

  void setTime(int time) {
    _time = time;
  }

  void setColor(int r, int g, int b, int a = 255) {
    _r = r;
    _g = g;
    _b = b;
    opacity = a / 255.0f;
  }

  void setColor(float r, float g, float b, float a = 1.0f) {
    _r = static_cast<int>(r * 255);
    _g = static_cast<int>(g * 255);
    _b = static_cast<int>(b * 255);
    opacity = a;
  }

};

#endif //INC_1760_TEXT_H
