#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QLabel>

class Window : public QWidget {
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);

private slots:
    void showHelp();
    void generateElements();
    void saveToFile();
    void saveToBinaryFile();
    void clearTable();

private:
    void setupUi();
    void calculateAndSetValues(int row, double x, double y, double radius, double height, const QString &type);
    double calculateCircleArea(double radius);
    double calculateCirclePerimeter(double radius);
    double calculateCylinderArea(double radius, double height);
    double calculateCylinderVolume(double radius, double height);

    QTableWidget *tableWidget;
    QPushButton *helpButton;
    QPushButton *generateButton;
    QPushButton *saveButton;
    QPushButton *saveBinaryButton;
    QPushButton *clearButton;
    QLabel *statusIndicator;
    QLabel *statusIndicatorBinary;
};

#endif
