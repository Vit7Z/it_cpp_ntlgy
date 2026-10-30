#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QFont>
#include "stopwatch.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  public slots:
    void ShowTimer(uint, float);
    void on_pb_lap_clicked (bool);

  private:
    Ui::MainWindow *ui;
    StopWatch* stopWatch;
};
#endif // MAINWINDOW_H
