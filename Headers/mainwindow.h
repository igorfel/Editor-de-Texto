#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "open.h"
#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <iostream>
#include <fstream>
#include <QTextStream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void openFile();
    void novoArquivo();
    void saveFile();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString titulo, texto;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
