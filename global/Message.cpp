//
// Created by Yixiang Tu on 01/06/2018.
//

#include "Message.h"
#include "../text/DebugText.h"

void Message::show(const QString& message) {
  SM(message)
}

void Message::show(const QString&& message) {
  SM(message)
}

void Message::show(const char* message) {
  SM(QString(message))
}
