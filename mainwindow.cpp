#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_openInputFolder_clicked()
{
    ui->ln_inputFolder->setText(QFileDialog::getExistingDirectory(this,"Выбрать каталог",ui->ln_inputFolder->text()) );
    _changeStateBtnConverted();
}

void MainWindow::on_btn_openOutputFolder_clicked()
{
    ui->ln_ouputFolder->setText(QFileDialog::getExistingDirectory(this,"Выбрать каталог",ui->ln_ouputFolder->text()) );
    _changeStateBtnConverted();
}

void MainWindow::on_btn_convert_clicked()
{
    _convertedDir(m_inputDir,m_outputDir);
}

void MainWindow::_convertedDir(QString pathInputDir, QString pathOutputDir)
{
    QDir inputDir(pathInputDir);
    QDir outputDir(pathOutputDir);

    if(!outputDir.exists())
    {
        QStringList paths = pathOutputDir.split("/");
        QString pathParentOutputDir = paths.mid(0,paths.size()-1).join("/");
        QDir paretDir(pathParentOutputDir);
        paretDir.mkdir(paths.last());
    }
    QStringList filters;
    filters << "*.png" << "*.PNG";
    QStringList inputFiles = inputDir.entryList(filters,QDir::Files);

    for(auto name : inputFiles)
    {
        QString inputNameFile = pathInputDir+"/"+name;
        QString outputNameFile = pathOutputDir+"/"+name;
        _convertedFile(inputNameFile,outputNameFile);
    }
    QStringList inputDirs = inputDir.entryList(QDir::Dirs |QDir::NoDotAndDotDot);

    for(auto nameDir : inputDirs)

    {
        QString inputNameDir = pathInputDir+"/"+nameDir;
        QString outputNameDir = pathOutputDir+"/"+nameDir;
        _convertedDir(inputNameDir,outputNameDir);
    }
}

void MainWindow::_convertedFile(QString pathInputFile, QString pathOutputFile)
{
    QPixmap pixmap;
    pixmap.load(pathInputFile);

    QFile file(pathOutputFile);
    file.open(QIODevice::WriteOnly);
    pixmap.save(&file, "PNG");
    file.close();
}

void MainWindow::_changeStateBtnConverted()
{
    if(ui->ln_inputFolder->text().isEmpty() || ui->ln_ouputFolder->text().isEmpty())
        ui->btn_convert->setEnabled(false);
    else
        ui->btn_convert->setEnabled(true);
}
