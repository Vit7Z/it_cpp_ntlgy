#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QTimer>

struct LapInfo
{
  float sec;
  uint16_t min, counter;
};

class StopWatch : public QObject
{
  Q_OBJECT

  public:
    explicit StopWatch(QObject *parent = nullptr);
    ~StopWatch();
    
  signals:
    void SignalTimer(uint, float);
    void SignalGetLap(uint, float, uint);
    
  public slots:
    void StartTimer();
    void StopTimer();
    void ResetTime();
    LapInfo GetLap ();

  private:
    QTimer* timer;
    uint16_t minutes, mnt_tmp, mil_seconds;
    float seconds, scd_temp;
    LapInfo lap;
};

#endif // STOPWATCH_H
