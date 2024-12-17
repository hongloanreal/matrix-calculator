#ifndef MATRIXCALCULATOR_H
#define MATRIXCALCULATOR_H

#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTextEdit>
#include <QPushButton>
#include <QHeaderView>
#include <QGuiApplication>
#include <QScreen>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <QDialog>
#include <QDialogButtonBox>
#include <QVector>
//#include <functional>

class MatrixCalculator : public QWidget
{
    Q_OBJECT

public:
    explicit MatrixCalculator(QWidget *parent = nullptr); 
    ~MatrixCalculator(); 

private slots:
    void setmatrix(QVector<QVector<double>> &matrix, const QString &matrixName);
    void displayMatrixResult(const QVector<QVector<double>> &matrix, const QString &operation);
    void addition();
    void subtraction();
    void multiplication();
    void determinant();
    void inverse();
    void power();
    void rank();
    
private: 
    QTableWidget *matrixA;
    QTableWidget *matrixB;
    
    QPushButton *addButton;
    QPushButton *subButton;
    QPushButton *mulButton;
    QPushButton *detButton;
    QPushButton *invButton;
    QPushButton *powButton;
    QPushButton *rankButton;
};

#endif // MATRIXCALCULATOR_H

