#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow (QWidget *parent)
    : QMainWindow (parent), ui (new Ui::MainWindow)
{
  ui->setupUi(this);
  stopWatch = new StopWatch(this);
  ui->pb_lap->setEnabled(false);
  ui->pb_start_stop->setCheckable(true);
  connect(ui->pb_start_stop, &QPushButton::clicked, this,
  [this] () {
    if (ui->pb_start_stop->isChecked()) {
      ui->pb_lap->setEnabled(true);
      ui->pb_start_stop->setText("Стоп");
      stopWatch->StartTimer();
    }
    else {
      ui->pb_lap->setEnabled(false);
      ui->pb_start_stop->setText("Старт");
      stopWatch->StopTimer();
    }
 });

  connect(ui->pb_reset, &QPushButton::clicked, stopWatch, &StopWatch::ResetTime);
  connect(ui->pb_reset, &QPushButton::clicked, this, [this] () {ui->txtbr_show_lap->clear();});
  connect(stopWatch, &StopWatch::SignalTimer, this, &MainWindow::ShowTimer);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::ShowTimer(uint minutes, float seconds) {
  ui->lb_count_minutes->setText(QString::number(minutes).rightJustified(2, '0'));
  ui->lb_count_seconds->setText(QString::number(seconds, 'f', 1).rightJustified(4, '0'));
}

void
MainWindow::on_pb_lap_clicked (bool checked) {
  LapInfo lap = stopWatch->GetLap();

  ui->txtbr_show_lap->append ("Круг: " + QString::number (lap.counter)
                              + " Минуты : " + QString::number (lap.min)
                              + " Секунды " + QString::number (lap.sec, 'f', 1));
}
