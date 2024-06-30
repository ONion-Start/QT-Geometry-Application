#include "mainwindow.h"
#include <QMessageBox>
#include <cmath>
#include <QDebug>
#include <QRandomGenerator>
#include <QDataStream>

Window::Window(QWidget *parent) : QWidget(parent) {
    setupUi();
}

void Window::setupUi() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    tableWidget = new QTableWidget(0, 8, this);
    tableWidget->setHorizontalHeaderLabels({"X", "Y", "Radius", "Height", "Type", "Area", "Perimeter", "Volume"});

    helpButton = new QPushButton("Help", this);
    generateButton = new QPushButton("Сгенерировать элементы", this);
    saveButton = new QPushButton("Занести в текстовый файл", this);
    saveBinaryButton = new QPushButton("Занести в бинарный файл", this);
    clearButton = new QPushButton("Очистить поле ввода", this);

    statusIndicator = new QLabel(this);
    statusIndicator->setFixedSize(20, 20);
    statusIndicator->setStyleSheet("background-color: red;");

    statusIndicatorBinary = new QLabel(this);
    statusIndicatorBinary->setFixedSize(20, 20);
    statusIndicatorBinary->setStyleSheet("background-color: red;");

    connect(helpButton, &QPushButton::clicked, this, &Window::showHelp);
    connect(generateButton, &QPushButton::clicked, this, &Window::generateElements);
    connect(saveButton, &QPushButton::clicked, this, &Window::saveToFile);
    connect(saveBinaryButton, &QPushButton::clicked, this, &Window::saveToBinaryFile);
    connect(clearButton, &QPushButton::clicked, this, &Window::clearTable);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(helpButton);
    buttonLayout->addWidget(generateButton);

    QHBoxLayout *saveTextLayout = new QHBoxLayout();
    saveTextLayout->addWidget(saveButton);
    saveTextLayout->addWidget(statusIndicator);

    QHBoxLayout *saveBinaryLayout = new QHBoxLayout();
    saveBinaryLayout->addWidget(saveBinaryButton);
    saveBinaryLayout->addWidget(statusIndicatorBinary);

    buttonLayout->addLayout(saveTextLayout);
    buttonLayout->addLayout(saveBinaryLayout);
    buttonLayout->addWidget(clearButton);

    mainLayout->addWidget(tableWidget);
    mainLayout->addLayout(buttonLayout);
}

void Window::showHelp() {
    QString helpText = "Задача 2: Создать базовый класс Point, который включает в себя:\n"
                       "• два числа типа double (координаты точки);\n"
                       "• конструктор с параметрами.\n"
                       "Производный от класса Point, класс Circle, который включает в себя:\n"
                       "• статическое поле имя фигуры;\n"
                       "• поле радиус;\n"
                       "• конструктор с параметрами;\n"
                       "• метод расчета площади square (2πR2);\n"
                       "• метод просмотра (наименование фигуры, площадь и периметр).\n"
                       "Производный от класса Circle, класс Cylinder, который включает в себя:\n"
                       "• статическое поле – имя фигуры;\n"
                       "• поле высота;\n"
                       "• конструктор с параметрами;\n"
                       "• метод расчета площади square(2 * площадь окружности * высоту + π* радиус * высоту);\n"
                       "• метод расчета объема volume (площадь кружности * высоту);\n"
                       "• метод просмотра (наименование фигуры, площадь и объем).\n"
                       "Разработка простейшего SDI-приложения, иллюстрирующего использование меню, корректировку, "
                       "сохранение и восстановление текстовой, числовой информации в текстовом (QTextStream) и "
                       "бинарном(QDataStream) формате.";
    QMessageBox::information(this, "Help", helpText);
}

void Window::generateElements() {
    tableWidget->setRowCount(3);  // Example row count

    // Generate random data for the table
    for (int i = 0; i < 3; ++i) {
        double x = QRandomGenerator::global()->bounded(200.0) - 100.0;
        double y = QRandomGenerator::global()->bounded(200.0) - 100.0;
        double radius = QRandomGenerator::global()->bounded(49.0) + 1.0;
        double height = QRandomGenerator::global()->bounded(99.0) + 1.0;
        QString type = (i % 2 == 0) ? "Cylinder" : "Circle";

        calculateAndSetValues(i, x, y, radius, height, type);
    }
}

void Window::calculateAndSetValues(int row, double x, double y, double radius, double height, const QString &type) {
    tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(x)));
    tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(y)));
    tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(radius)));
    tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(height)));
    tableWidget->setItem(row, 4, new QTableWidgetItem(type));

    if (type == "Circle") {
        double area = calculateCircleArea(radius);
        double perimeter = calculateCirclePerimeter(radius);
        tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(area)));
        tableWidget->setItem(row, 6, new QTableWidgetItem(QString::number(perimeter)));
        tableWidget->setItem(row, 7, new QTableWidgetItem("N/A"));
    } else if (type == "Cylinder") {
        double area = calculateCylinderArea(radius, height);
        double volume = calculateCylinderVolume(radius, height);
        tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(area)));
        tableWidget->setItem(row, 6, new QTableWidgetItem("N/A"));
        tableWidget->setItem(row, 7, new QTableWidgetItem(QString::number(volume)));
    }
}

double Window::calculateCircleArea(double radius) {
    return M_PI * radius * radius;
}

double Window::calculateCirclePerimeter(double radius) {
    return 2 * M_PI * radius;
}

double Window::calculateCylinderArea(double radius, double height) {
    return 2 * M_PI * radius * (radius + height);
}

double Window::calculateCylinderVolume(double radius, double height) {
    return M_PI * radius * radius * height;
}

void Window::saveToFile() {
    QFile file("data.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "X, Y, Radius, Height, Type, Area, Perimeter, Volume\n";
        for (int i = 0; i < tableWidget->rowCount(); ++i) {
            for (int j = 0; j < tableWidget->columnCount(); ++j) {
                if (j > 0) {
                    out << ", ";
                }
                out << tableWidget->item(i, j)->text();
            }
            out << "\n";
        }
        file.close();
        QMessageBox::information(this, "Success", "Data has been saved to file.");
        statusIndicator->setStyleSheet("background-color: green;");
    } else {
        QMessageBox::warning(this, "Error", "Failed to open file for writing.");
    }
}

void Window::saveToBinaryFile() {
    QFile file("data.bin");
    if (file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);
        out << tableWidget->rowCount();
        out << tableWidget->columnCount();
        for (int i = 0; i < tableWidget->rowCount(); ++i) {
            for (int j = 0; j < tableWidget->columnCount(); ++j) {
                out << tableWidget->item(i, j)->text();
            }
        }
        file.close();
        QMessageBox::information(this, "Success", "Data has been saved to binary file.");
        statusIndicatorBinary->setStyleSheet("background-color: green;");
    } else {
        QMessageBox::warning(this, "Error", "Failed to open binary file for writing.");
    }
}

void Window::clearTable() {
    tableWidget->clearContents();
    tableWidget->setRowCount(0);
    statusIndicator->setStyleSheet("background-color: red;");
    statusIndicatorBinary->setStyleSheet("background-color: red;");
}
