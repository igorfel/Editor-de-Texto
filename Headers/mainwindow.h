#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "open.h"
#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <iostream>
#include <QTextStream>
#include <QMessageBox>

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
    void saveAs();
    void sair();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString editedOrNo, nomeArquivo, texto, textoEspelho;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
