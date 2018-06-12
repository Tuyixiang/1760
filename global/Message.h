//
// Created by Yixiang Tu on 27/05/2018.
//

#ifndef INC_1760_MESSAGE_H
#define INC_1760_MESSAGE_H

#include <cstdio>
#include <QString>

class Message {
private:
  Message() = default;

public:
  static Message& instance() {
    static Message singleton;
    return singleton;
  }

  Message(const Message& e) = delete;
  void operator=(const Message& e) = delete;

  void warn(const char* message) {
    printf("WARNING: %s\n", message);
  }

  void warn(const char* source, const char* message) {
    printf("WARNING from %s: %s\n", source, message);
  }

  void warn(const char* source, const char* message, const void* address) {
    printf("WARNING from %s: %s\n\tat %p\n", source, message, address);
  }

  void show(const QString& message);

  void show(const QString&& message);

  void show(const char* message);
};


#endif //INC_1760_MESSAGE_H
