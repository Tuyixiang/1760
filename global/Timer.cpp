//
// Created by Yixiang Tu on 25/05/2018.
//

#include "Timer.h"

using namespace std::chrono;

Timer::Timer() {
  timer = new QTimer;
  startTimer(fpsTimer);
  frameTime.push(0);
}

void Timer::initializePeriod(int ms) {
  period = ms;
}

void Timer::updatePeriod(int ms) {
  period = ms;
  timer->start(period);
}

/**
 * Connect the current timer to a slot
 * @param object
 * Receiver object
 * @param slot
 * Member function
 */
void Timer::connectSlot(const QObject* object, const char* slot) {
  connect(timer, SIGNAL(timeout()), object, slot);
  timer->start(period);
}

void Timer::disconnectAllSlots() {
  disconnect(timer, SIGNAL(timeout()));
}

/**
 * Start the timer with label "timerId"
 * @param timerId
 */
void Timer::startTimer(int timerId) {
  timeCounters[timerId] = duration_cast<milliseconds>(steady_clock::now() - startTime).count();
  lastCall[timerId] = 0;
}

/**
 * Get the time passed in the timer with label "timerId"
 * @param timerId
 * @return time passed in milliseconds
 */
int Timer::getTime(int timerId) {
  int time = (int) (duration_cast<milliseconds>(steady_clock::now() - startTime).count() - timeCounters[timerId]);
  lastCall[timerId] = time;
  return lastCall[timerId];
}

/**
 *
 * @param timerId
 * @return time passed since last call on this timerId
 */
int Timer::lastPeriod(int timerId) {
  int time = (int) (duration_cast<milliseconds>(steady_clock::now() - startTime).count() - timeCounters[timerId]);
  int result = time - lastCall[timerId];
  lastCall[timerId] = time;
  return result;
}


/**
 * Called on each frame
 * @return number of frames in the last second
 */
int Timer::refresh() {
  _frameCounter++;
  if (frameTime.empty()) {
    startTimer(fpsTimer);
    frameTime.push(0);
    return 0;
  } else {
    int now = getTime(fpsTimer);
    while (!frameTime.empty() and now - frameTime.front() >= 1000) {
      frameTime.pop();
    }
    frameTime.push(now);
    return (int) frameTime.size();
  }
}

int Timer::frameCounter() {
  return _frameCounter;
}
