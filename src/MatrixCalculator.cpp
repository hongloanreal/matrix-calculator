#include "MatrixCalculator.h"

MatrixCalculator::MatrixCalculator(QWidget *parent)
    : QWidget(parent)
{
    // Layout Setup
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    // Button Setup
    addButton = new QPushButton("Addition", this);
    subButton = new QPushButton("Subtraction", this);
    mulButton = new QPushButton("Multiplication", this);
    powButton = new QPushButton("Power", this);
    detButton = new QPushButton("Determinant", this);
    invButton = new QPushButton("Inverse", this);
    rankButton = new QPushButton("Rank", this);

    mainLayout->addWidget(addButton);
    mainLayout->addWidget(subButton);
    mainLayout->addWidget(mulButton);
    mainLayout->addWidget(powButton);
    mainLayout->addWidget(detButton);
    mainLayout->addWidget(invButton);
    mainLayout->addWidget(rankButton);

    // Connect buttons to slots
    connect(addButton, &QPushButton::clicked, this, &MatrixCalculator::addition);
    connect(subButton, &QPushButton::clicked, this, &MatrixCalculator::subtraction);
    connect(mulButton, &QPushButton::clicked, this, &MatrixCalculator::multiplication);
    connect(powButton, &QPushButton::clicked, this, &MatrixCalculator::power);
    connect(detButton, &QPushButton::clicked, this, &MatrixCalculator::determinant);
    connect(invButton, &QPushButton::clicked, this, &MatrixCalculator::inverse);
    connect(rankButton, &QPushButton::clicked, this, &MatrixCalculator::rank);
}

MatrixCalculator::~MatrixCalculator() {}

void MatrixCalculator::setmatrix(QVector<QVector<double>> &matrix, const QString &matrixName) {
    bool ok;
    int rows = QInputDialog::getInt(this, matrixName + " Rows", "Enter the number of rows:", 3, 1, 100, 1, &ok);
    if (!ok) return;

    int cols = QInputDialog::getInt(this, matrixName + " Columns", "Enter the number of columns:", 3, 1, 100, 1, &ok);
    if (!ok) return;

    QDialog dialog(this);
    dialog.setWindowTitle(matrixName + " Input");

    QTableWidget *tableWidget = new QTableWidget(rows, cols, &dialog);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            tableWidget->setItem(i, j, new QTableWidgetItem(QString::number(0)));
        }
    }

    int cellWidth = 100;
    int cellHeight = 80;
    tableWidget->horizontalHeader()->setDefaultSectionSize(cellWidth);
    tableWidget->verticalHeader()->setDefaultSectionSize(cellHeight);

    int tableWidth = cols * cellWidth + tableWidget->verticalHeader()->width();
    int tableHeight = rows * cellHeight + tableWidget->horizontalHeader()->height();

    QSize screenSize = QGuiApplication::primaryScreen()->availableGeometry().size();
    int maxWidth = screenSize.width() - 100;
    int maxHeight = screenSize.height() - 100;

    if (tableWidth > maxWidth || tableHeight > maxHeight) {
        tableWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        dialog.resize(qMin(maxWidth, tableWidth + 20), qMin(maxHeight, tableHeight + 50));
    } else {
        tableWidget->setMinimumSize(tableWidth, tableHeight);
        dialog.resize(tableWidth + 40, tableHeight + 60);
    }

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->addWidget(tableWidget);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        matrix.resize(rows, QVector<double>(cols, 0));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                bool ok;
                double value = tableWidget->item(i, j)->text().toDouble(&ok);
                if (!ok) {
                    QMessageBox::warning(this, "Error", "Invalid value in the matrix. Please check your input.");
                    return;
                }
                matrix[i][j] = value;
            }
        }
    } else {
        QMessageBox::information(this, matrixName, "Matrix input canceled.");
    }
}

void MatrixCalculator::displayMatrixResult(const QVector<QVector<double>>& matrix, const QString& operation) {
    QDialog resultDialog(this);
    resultDialog.setWindowTitle(operation + " Result");

    int rows = matrix.size();
    int cols = matrix[0].size();

    QTableWidget *tableWidget = new QTableWidget(rows, cols, &resultDialog);
    tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(matrix[i][j], 'f', 2));
            tableWidget->setItem(i, j, item);
        }
    }

    QVBoxLayout *layout = new QVBoxLayout(&resultDialog);
    layout->addWidget(tableWidget);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok, &resultDialog);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, &resultDialog, &QDialog::accept);

    resultDialog.resize(400, 400);
    resultDialog.exec();
}

void MatrixCalculator::addition() {
    QVector<QVector<double>> matrixA, matrixB;
    setmatrix(matrixA, "Matrix A");
    setmatrix(matrixB, "Matrix B");

    if (matrixA.size() != matrixB.size() || matrixA[0].size() != matrixB[0].size()) {
        QMessageBox::warning(this, "Error", "Matrices must have the same dimensions for addition.");
        return;
    }

    int rows = matrixA.size();
    int cols = matrixA[0].size();

    QVector<QVector<double>> result(rows, QVector<double>(cols, 0));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }

    displayMatrixResult(result, "Matrix Addition");
}

void MatrixCalculator::subtraction() {
    QVector<QVector<double>> matrixA, matrixB;
    setmatrix(matrixA, "Matrix A");
    setmatrix(matrixB, "Matrix B");

    if (matrixA.size() != matrixB.size() || matrixA[0].size() != matrixB[0].size()) {
        QMessageBox::warning(this, "Error", "Matrices must have the same dimensions for subtraction.");
        return;
    }

    int rows = matrixA.size();
    int cols = matrixA[0].size();

    QVector<QVector<double>> result(rows, QVector<double>(cols, 0));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[i][j] = matrixA[i][j] - matrixB[i][j];
        }
    }

    displayMatrixResult(result, "Matrix Subtraction");
}

void MatrixCalculator::multiplication() {
    QVector<QVector<double>> matrixA, matrixB;
    setmatrix(matrixA, "Matrix A");
    setmatrix(matrixB, "Matrix B");

    if (matrixA[0].size() != matrixB.size()) {
        QMessageBox::warning(this, "Error", "Number of columns in Matrix A must match the number of rows in Matrix B for multiplication.");
        return;
    }

    int rows = matrixA.size();
    int cols = matrixB[0].size();
    QVector<QVector<double>> result(rows, QVector<double>(cols, 0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            for (int k = 0; k < matrixA[0].size(); ++k) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }

    displayMatrixResult(result, "Matrix Multiplication");
}

void MatrixCalculator::determinant() {
    QVector<QVector<double>> matrixA;
    setmatrix(matrixA, "Matrix A");

    if (matrixA.size() != matrixA[0].size()) {
        QMessageBox::warning(this, "Error", "Matrix must be square to calculate determinant.");
        return;
    }

    std::function<double(const QVector<QVector<double>>&)> calculateDeterminant;
    calculateDeterminant = [&calculateDeterminant](const QVector<QVector<double>>& matrix) -> double {
        int n = matrix.size();
        if (n == 1) return matrix[0][0];
        if (n == 2) return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];

        double det = 0;
        for (int i = 0; i < n; ++i) {
            QVector<QVector<double>> subMatrix;
            for (int row = 1; row < n; ++row) {
                QVector<double> subRow;
                for (int col = 0; col < n; ++col) {
                    if (col != i) {
                        subRow.append(matrix[row][col]);
                    }
                }
                subMatrix.append(subRow);
            }
            det += matrix[0][i] * calculateDeterminant(subMatrix) * (i % 2 == 0 ? 1 : -1);
        }

        return det;
    };

    double det = calculateDeterminant(matrixA);
    QMessageBox::information(this, "Determinant", "Determinant: " + QString::number(det));
}

void MatrixCalculator::inverse() {
    QVector<QVector<double>> matrixA;
    setmatrix(matrixA, "Matrix A");

    if (matrixA.size() != matrixA[0].size()) {
        QMessageBox::warning(this, "Error", "Matrix must be square to calculate inverse.");
        return;
    }

    int n = matrixA.size();
    QVector<QVector<double>> augmented(n, QVector<double>(2 * n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            augmented[i][j] = matrixA[i][j];
        }
        augmented[i][n + i] = 1; // Identity matrix part
    }

    for (int i = 0; i < n; ++i) {
        if (augmented[i][i] == 0) {
            QMessageBox::warning(this, "Error", "Matrix is singular and cannot be inverted.");
            return;
        }

        double pivot = augmented[i][i];
        for (int j = 0; j < 2 * n; ++j) {
            augmented[i][j] /= pivot;
        }

        for (int j = 0; j < n; ++j) {
            if (j != i) {
                double factor = augmented[j][i];
                for (int k = 0; k < 2 * n; ++k) {
                    augmented[j][k] -= augmented[i][k] * factor;
                }
            }
        }
    }

    QVector<QVector<double>> inverseMatrix(n, QVector<double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inverseMatrix[i][j] = augmented[i][j + n];
        }
    }

    displayMatrixResult(inverseMatrix, "Matrix Inverse");
}

void MatrixCalculator::power() {
    QVector<QVector<double>> matrixA;
    setmatrix(matrixA, "Matrix A");

    bool ok;
    int power = QInputDialog::getInt(this, "Matrix Power", "Enter the power:", 2, -100, 100, 1, &ok);
    if (!ok) return;

    if (matrixA.size() != matrixA[0].size()) {
        QMessageBox::warning(this, "Error", "Matrix must be square for power operation.");
        return;
    }

    int n = matrixA.size();
    QVector<QVector<double>> result = matrixA;

    for (int i = 1; i < power; ++i) {
        QVector<QVector<double>> temp = result;
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                result[r][c] = 0;
                for (int k = 0; k < n; ++k) {
                    result[r][c] += temp[r][k] * matrixA[k][c];
                }
            }
        }
    }

    displayMatrixResult(result, "Matrix Power");
}

void MatrixCalculator::rank() {
    QVector<QVector<double>> matrixA;
    setmatrix(matrixA, "Matrix A");

    if (matrixA.empty()) {
        QMessageBox::warning(this, "Error", "Matrix is empty. Cannot calculate rank.");
        return;
    }

    int rows = matrixA.size();
    int cols = matrixA[0].size();

    // Perform Gaussian elimination to find rank
    int rank = 0;
    QVector<QVector<double>> augmented = matrixA;

    for (int i = 0; i < rows; ++i) {
        if (augmented[i][i] != 0) {
            ++rank;
            for (int j = i + 1; j < rows; ++j) {
                if (augmented[j][i] != 0) {
                    double factor = augmented[j][i] / augmented[i][i];
                    for (int k = 0; k < cols; ++k) {
                        augmented[j][k] -= augmented[i][k] * factor;
                    }
                }
            }
        }
    }

    QMessageBox::information(this, "Rank", "Rank of the matrix: " + QString::number(rank));
}

