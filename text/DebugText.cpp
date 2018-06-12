//
// Created by Yixiang Tu on 28/05/2018.
//

#include "DebugText.h"
#include "../template/Text.h"
#include "../template/Scene.h"

DebugText::DebugText() {
  _pen.setColor(QColor(0, 0, 0, 255));
  _font.setFamily("Arial");
  _font.setPixelSize(16);
  //showMessage(QString("default string"));
  alignStyle = Qt::AlignTop | Qt::AlignRight;
}

void DebugText::draw(QPainter& painter) {
  if (visible) {
    int acc = 0;
    painter.setPen(_pen);
    painter.setFont(_font);
    painter.drawText(QRect(0, 0, activeScene->width(), activeScene->height()),
                     alignStyle, _text);
    while (!instantMessageList.empty()) {
      acc += 20;
      painter.drawText(QRect(0, acc, activeScene->width(), activeScene->height()),
                       alignStyle, instantMessageList.front());
      instantMessageList.pop();
    }
    for (auto it = messageList.cbegin(); it != messageList.cend();) {
      acc += 20;
      painter.drawText(QRect(0, acc, activeScene->width(), activeScene->height()),
                       alignStyle, it->message);
      if (it->frameToBeRemoved <= Timer::instance().frameCounter()) {
        it = messageList.erase(it);
      } else {
        it++;
      }
    }
  } else {
    instantMessageList = std::queue<QString>();
    for (auto it = messageList.cbegin(); it != messageList.cend();) {
      if (it->frameToBeRemoved <= Timer::instance().frameCounter()) {
        it = messageList.erase(it);
      } else {
        it++;
      }
    }
  }
}

void DebugText::onFrame() {
  if (visible) {
    _text = QString("FPS: ") + QString::number(Timer::instance().refresh());
  } else {
    Timer::instance().refresh();
  }
}

DebugText::Bundle::Bundle(const QString&& m, int duration) {
  message = m;
  frameToBeRemoved = Timer::instance().frameCounter() + duration;
}

DebugText::Bundle::Bundle(const QString& m, int duration) {
  message = m;
  frameToBeRemoved = Timer::instance().frameCounter() + duration;
}
