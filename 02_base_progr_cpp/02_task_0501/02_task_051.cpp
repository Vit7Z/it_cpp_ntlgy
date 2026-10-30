#include <iostream>
#include <fstream>
#include <string>
#include <clocale>
#include <locale.h>
#include <windows.h>

class Figure {
  private:
    unsigned short numberOfSides;
    std::string name;

  protected:
    Figure(unsigned short numberOfSides_, std::string name_) {
      numberOfSides = numberOfSides_;
      name = name_;
    }

  public:
    void printData() {
      std::cout << name << ": " << numberOfSides << std::endl;
    }

    Figure() : Figure(0, "Фигура") {}
};//class

class Triangle:public Figure
{
  public:
    Triangle():Figure (3, "Треугольник") { }
};//class

class Quadrangle :public Figure
{
  public:
    Quadrangle() :Figure(4, "Четырехугольник") { }
};//class



int main(int argc, char** argv)
{
  setlocale(0, "Rus");
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);

  Figure someFigure;

  Triangle someTriangle;

  Quadrangle someQuadrangle;

  someFigure.printData();

  someTriangle.printData();

  someQuadrangle.printData();

  return 0;
}
