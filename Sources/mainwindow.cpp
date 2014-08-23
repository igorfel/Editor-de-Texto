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
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(nomeArquivo + "Notepad--");
    novoArquivo();

    if (texto != textoEspelho)
    {
        this->setWindowTitle(nomeArquivo+ "*" + "Notepad--");
    }

    connect(ui->actionAbrir, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->actionNovo, SIGNAL(triggered()), this, SLOT(novoArquivo()));
    connect(ui->actionSalvar, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(ui->actionSalvar_Como, SIGNAL(triggered()), this, SLOT(saveAs()));
    connect(ui->actionSair, SIGNAL(triggered()), this, SLOT(sair()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::novoArquivo()
{
    editedOrNo = "Novo Documento de Texto.txt*";
    this->setWindowTitle(editedOrNo + " - Notepad--");
    ui->plainTextEdit->clear();
    nomeArquivo = editedOrNo;
}

void MainWindow::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Abrir"),
                                                     "",
                                                     tr("All Files (*)"));
    QFile file(filePath);
    file.open(QIODevice::ReadOnly);
    if(!file.isOpen())
    {
        QMessageBox::critical(this, "Erro", "Não foi possível abrir o arquivo.\n[" + file.errorString() + "]");
    }
    else
    {
        ui->plainTextEdit->clear();
        nomeArquivo = file.fileName();
        this->setWindowTitle(nomeArquivo + " - Notepad--");
        QTextStream fileStream(&file);
        QString line;
        while(!fileStream.atEnd())
        {
            line = fileStream.readLine();
            ui->plainTextEdit->appendPlainText(line);
        }

        textoEspelho = ui->plainTextEdit->toPlainText();
    }
    file.close();
}

void MainWindow::saveFile()
{
    QFile file(nomeArquivo);
    file.open(QIODevice::WriteOnly);
    texto = ui->plainTextEdit->toPlainText();
    QTextStream text(&file);
    text << texto;
    file.close();
}

void MainWindow::saveAs()
{
    QFileDialog fDialog(this);
    fDialog.setFileMode(QFileDialog::AnyFile);
    QString filePath = QFileDialog::getSaveFileName(this, tr("Salvar"),
                                                     "",
                                                     tr("All Files (*)"));

    QFile file(filePath);
    file.open(QIODevice::WriteOnly);
    texto = ui->plainTextEdit->toPlainText();
    QTextStream text(&file);
    text << texto;
    file.close();
}

void MainWindow::sair()
{
    QApplication::quit();
}
