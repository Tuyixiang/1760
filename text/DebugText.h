//
// Created by Yixiang Tu on 28/05/2018.
//

#ifndef INC_1760_DEBUGTEXT_H
#define INC_1760_DEBUGTEXT_H

#include <vector>
#include <queue>
#include <QPainter>
#include "../global/Timer.h"
#define IM(str) DebugText::instance().showInstantMessage(QString(#str) + ": " + QString::number(str));
#define SM(str) DebugText::instance().showMessage(str);

class Scene;

class DebugText {
  friend class Message;

public:
  static DebugText& instance() {
    static DebugText singleton;
    return singleton;
  }

  DebugText(const DebugText& e) = delete;
  void operator=(const DebugText& e) = delete;

  void draw(QPainter& painter);

  void onFrame();

  void setActiveScene(Scene* s) {
    activeScene = s;
  }

  void showInstantMessage(const QString& message) {
    instantMessageList.push(message);
  }

  void showMessage(const QString& message) {
    messageList.emplace_back(message);
  }

  void showMessage(const QString&& message) {
    messageList.emplace_back(message);
  }

  void changeVisibility() {
    visible = !visible;
  }

protected:
  DebugText();

#ifndef NDEBUG
  bool visible = true;
#else
  bool visible = false;
#endif

  Scene* activeScene;

  //  see "enum Qt::AlignmentFlag" for possible flags
  //  Use | to select multiple
  int alignStyle = Qt::AlignCenter;
  QPen _pen;
  QFont _font;
  QString _text;

  struct Bundle {
    QString message;
    int frameToBeRemoved;

    explicit Bundle(const QString&& m, int duration = 60);

    explicit Bundle(const QString& m, int duration = 60);
  };

  std::vector<Bundle> messageList;
  std::queue<QString> instantMessageList;

};


#endif //INC_1760_DEBUGTEXT_H
