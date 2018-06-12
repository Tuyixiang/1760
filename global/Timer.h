//
// Created by Yixiang Tu on 25/05/2018.
//

#ifndef INC_1760_TIMER_H
#define INC_1760_TIMER_H
#include <QTimer>
#include <QObject>
#include <chrono>
#include <map>
#include <queue>

/**
 * 1. Timed invocation:
 * <ul>
 * <li>initializePeriod(int ms);
 * <li>connectSlot(QObject*, slot);
 * <li>updatePeriod(int ms);
 * <li>disconnectAllSlots();
 * </ul>
 * 2. Steady time counter:
 * <ul>
 * <li>startTimer(int timerId = -1);
 * <li>etTime(int timerId = -1);
 * </ul>
 * 3. FPS counter:
 * <ul>
 * <li>
 */
class Timer: public QObject {

  Q_OBJECT

private:
  Timer();

public:
  Timer(const Timer& e) = delete;
  void operator=(const Timer& e) = delete;

  static Timer& instance() {
    static Timer singleton;
    return singleton;
  }

  /// 1. Timed invocation:
private:
  QTimer* timer;
  int period = 16;
public:
  void initializePeriod(int ms);
  void updatePeriod(int ms);
  void connectSlot(const QObject* object, const char* slot);
  void disconnectAllSlots();

  /// 2. Steady time counter:
  /* Counts milliseconds steadily.
   * This is introduced because the QTimer is unstable when busy.
   */
private:
  std::chrono::time_point<std::chrono::steady_clock> startTime;
  std::map<int, long long> timeCounters;
  std::map<int, int> lastCall;
public:
  void startTimer(int timerId = -1);
  int getTime(int timerId = -1);
  int lastPeriod(int timerId = -1);

  /// 3. FPS counter:
private:
  static const int fpsTimer = 0x9cd10ba8;
  std::queue<int> frameTime;
  int _frameCounter = 0;
public:
  int refresh();
  int frameCounter();

};


#endif //INC_1760_TIMER_H
