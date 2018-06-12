//
// Created by Yixiang Tu on 28/05/2018.
//

#ifndef INC_1760_RANDOM_H
#define INC_1760_RANDOM_H

#include <random>
#include <QVector3D>
#include <cmath>

//Singleton
class Random {
private:
  Random() {
    generator.seed(rd());
  }
  std::random_device rd;
  std::mt19937 generator;

public:
  Random(const Random& e) = delete;

  static Random& instance() {
    static Random singleton;
    return singleton;
  }

  float getFloat() {
    return (float) generator() / generator.max();
  }

  float getFloat0() {
    return getBetween(-1.0f, 1.0f);
  }

  QVector3D getV3() {
    return QVector3D(getFloat0(), getFloat0(), getFloat0());
  }

  int getInt() {
    return generator();
  }

  template <class T>
    const T getBetween(const T& min, const T& max) {
    return min + getFloat() * (max - min);
  }


};


#endif //INC_1760_RANDOM_H
