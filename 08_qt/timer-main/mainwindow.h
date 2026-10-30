#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "stopwatch.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startStopButton_clicked();
    void on_lapButton_clicked();
    void on_clearButton_clicked();
    void updateDisplay(qreal time); // Слот для обновления времени

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    Stopwatch stopwatch;
};

#endif // MAINWINDOW_H
