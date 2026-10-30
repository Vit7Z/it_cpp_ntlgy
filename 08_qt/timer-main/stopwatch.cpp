#include "stopwatch.h"

Stopwatch::Stopwatch()
    : previousLapTime(0),
    running(false),
    currentTime(0)
{
    // Настраиваем таймер на обновление времени каждые 100 мс (0.1 сек)
    connect(&timer, &QTimer::timeout, this, &Stopwatch::updateTime);
    timer.setInterval(100); // Устанавливаем интервал 0.1 сек
}

void Stopwatch::start()
{
    if (!running) {
        timer.start();
        running = true;
    }
}

void Stopwatch::stop()
{
    if (running) {
        timer.stop();
        running = false;
    }
}

void Stopwatch::reset()
{
    // Сбрасываем все данные
    timer.stop();
    running = false;
    currentTime = 0;
    previousLapTime = 0;
    lapTimes.clear();
    emit timeUpdated(0); // Сообщаем, что время сброшено
}

int Stopwatch::lap()
{
    qreal lapTime = currentTime - previousLapTime;
    lapTimes.append(lapTime);
    previousLapTime = currentTime;
    return lapTimes.size();
}

qreal Stopwatch::lastLapTime() const
{
    if (!lapTimes.isEmpty()) {
        return lapTimes.last();
    }
    return 0;
}

bool Stopwatch::isRunning() const
{
    return running;
}

qreal Stopwatch::elapsedTime() const
{
    return currentTime;
}

void Stopwatch::updateTime()
{
    currentTime += 0.1; // Увеличиваем текущее время на 0.1 секунды
    emit timeUpdated(currentTime); // Сообщаем об обновлении времени
}
