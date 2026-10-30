#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Подключаем сигнал обновления времени от секундомера к слоту обновления метки времени
    connect(&stopwatch, &Stopwatch::timeUpdated, this, &MainWindow::updateDisplay);

    // Изначально кнопка кругов неактивна
    ui->lapButton->setEnabled(false);
    ui->clearButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Старт/Стоп кнопка
void MainWindow::on_startStopButton_clicked()
{
    if (stopwatch.isRunning()) {
        // Останавливаем секундомер
        stopwatch.stop();
        ui->startStopButton->setText("Старт");
        ui->lapButton->setEnabled(false);        // Отключаем кнопку кругов
         ui->clearButton->setEnabled(true);
    } else {
        // Запускаем секундомер
        stopwatch.start();
        ui->startStopButton->setText("Стоп");
        ui->lapButton->setEnabled(true);   // Включаем кнопку кругов
        ui->clearButton->setEnabled(false);
    }
}

// Кнопка "Круг"
void MainWindow::on_lapButton_clicked()
{
    int lapNumber = stopwatch.lap();
    QString lapText = QString("Круг %1, время: %2 сек").arg(lapNumber).arg(stopwatch.lastLapTime());
    ui->textBrowser->append(lapText); // Добавляем информацию о круге
}

// Кнопка "Очистить"
void MainWindow::on_clearButton_clicked()
{
    // Очищаем отображаемое время и круги
    stopwatch.reset();
    ui->textBrowser->clear(); // Очищаем текстовый браузер (список кругов)

    // Кнопка для записи кругов остаётся активной, если секундомер продолжает работать
    if (stopwatch.isRunning()) {
        ui->lapButton->setEnabled(true);
    } else {
        ui->lapButton->setEnabled(false);
    }
}

// Обновление дисплея времени
void MainWindow::updateDisplay(qreal time)
{
    // Обновляем метку времени
    ui->timeLabel2->setText(QString::number(time, 'f', 1));
}
