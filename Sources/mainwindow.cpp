#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(titulo + "Notepad--");
    connect(ui->actionAbrir, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->actionNovo, SIGNAL(triggered()), this, SLOT(novoArquivo()));
    connect(ui->actionSalvar, SIGNAL(triggered()), this, SLOT(saveFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::novoArquivo()
{
    titulo = "Novo Documento de Texto.txt";
    this->setWindowTitle(titulo + " - Notepad--");
    ui->plainTextEdit->setPlainText("");
}

void MainWindow::saveFile()
{
    std::ofstream newFile("teste");
    if (newFile.is_open())
    {
        texto = ui->plainTextEdit->toPlainText();
        newFile << texto.toStdString();
        newFile.close();
    }
}

void MainWindow::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     "",
                                                     tr("All Files (*)"));
    QFile file(filePath);
    ui->plainTextEdit->clear();
    file.open(QIODevice::ReadOnly);
    
    QTextStream fileStream(&file);
    QString line;
    while(!fileStream.atEnd())
    {
        line = fileStream.readLine();
        ui->plainTextEdit->appendPlainText(line);
    }
    file.close();
    //ui->plainTextEdit->setPlainText(fileName);
}
