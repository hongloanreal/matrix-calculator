#include <QApplication>
#include <QWidget>
#include "MatrixCalculator.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MatrixCalculator calculator;
    calculator.setWindowTitle("MatCal");
    //calculator.resize(300, 300);
    calculator.show();

    return app.exec();
}

