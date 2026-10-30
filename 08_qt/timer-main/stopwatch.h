#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QTimer>
#include <QVector>
#include <QObject>

class Stopwatch : public QObject
{
    Q_OBJECT

public:
    Stopwatch();

    void start();
    void stop();
    void reset();
    int lap();              // Метод для записи круга
    qreal lastLapTime() const; // Возвращает время последнего круга
    bool isRunning() const;
    qreal elapsedTime() const; // Возвращает текущее время

signals:
    void timeUpdated(qreal time); // Сигнал для обновления времени

private slots:
    void updateTime(); // Слот для обновления времени

private:
    QTimer timer;           // Таймер для отсчета времени
    QVector<qreal> lapTimes; // Список времен кругов
    qreal previousLapTime;   // Время предыдущего круга
    bool running;            // Флаг состояния секундомера
    qreal currentTime;       // Текущее время
};

#endif // STOPWATCH_H
