const int vResistorPin = A0;

class SlidingWindowFilter10 {
  private:
    enum { MAX_READING = 10 };    //число значений скользящего фильтра
    int readings[MAX_READING];  // массив для хранения значений полученных на аналоговом входе
    int readIndex;          // индекс последнего значения
    int total;              // сумма значений
    int average;            //скользящее среднее

  public:
    SlidingWindowFilter10() :
      readIndex(0),
      total(0),
      average(0)
    {
      //устанавливаем все значения в 0
      for (int i = 0; i < MAX_READING; i++) {
        readings[i] = 0;
      }
    }
    //добавляем значение в фильтр
    void push(int value)
    {
      // вычитанем последнее значение из суммы
      total = total - readings[readIndex];
      // вставляем значение
      readings[readIndex] = value;
      // добавляем значение к сумме
      total = total + readings[readIndex];
      // переставляем индекс на следующую позицию
      readIndex = readIndex + 1;
      // проверяем если мы выскочили индексом за пределы массива
      if (readIndex == MAX_READING) {
        // если да, то индекс на ноль
        readIndex = 0;
      }
      // считаем среднее:
      average = total / MAX_READING;
    }

    //получить среднее
    int get() const {
      return average;
    }
};

SlidingWindowFilter10 filter;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int ext_signal = analogRead(vResistorPin);
  ext_signal = map(ext_signal, 0, 1023, -135, 135);
	filter.push(ext_signal);

  Serial.println(filter.get());
  delay(100);
}