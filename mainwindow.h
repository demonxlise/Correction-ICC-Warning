#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUrl>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btn_openInputFolder_clicked();

    void on_btn_openOutputFolder_clicked();

    void on_btn_convert_clicked();

private:
    void _convertedDir(QString pathInputDir,QString pathOutputDir);
    void _convertedFile(QString pathInputFile,QString pathOutputFile);
private:
    Ui::MainWindow *ui;
    QString m_inputDir;
    QString m_outputDir;
};

#endif // MAINWINDOW_H
