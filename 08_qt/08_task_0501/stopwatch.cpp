#include "stopwatch.h"

StopWatch::StopWatch(QObject* parent): QObject{parent} {
  timer = new QTimer(this);
  minutes = 0;
  seconds = 0;
  mil_seconds = 0;

  mnt_tmp = 0;
  scd_temp = 0;

  lap.counter = 0;
  lap.min = 0;
  lap.sec = 0;

  connect(timer, &QTimer::timeout, this, &StopWatch::StartTimer);
}

StopWatch::~StopWatch() {}

void StopWatch::StartTimer() {
  timer->start(100);
  mil_seconds++;

  if (mil_seconds >= 1) {
    seconds = seconds + 0.1;
    mil_seconds = 0;
  }

  if (seconds >= 60) {
    minutes++;
    seconds = 0;
  }

  emit SignalTimer(minutes, seconds);
}

void StopWatch::StopTimer() {
  timer->stop();
  emit SignalTimer(minutes, seconds);
}

void StopWatch::ResetTime() {
  minutes = seconds = lap.counter = 0;
  lap.min = lap.sec = 0;
  emit SignalTimer(minutes, seconds);
}

LapInfo
StopWatch::GetLap ()
{
  mnt_tmp = minutes - lap.min;
  scd_temp = seconds - lap.sec;
  lap.counter++;
  emit SignalGetLap (mnt_tmp, scd_temp, lap.counter);
  lap.min = minutes;
  lap.sec = seconds;
  return lap;
}
