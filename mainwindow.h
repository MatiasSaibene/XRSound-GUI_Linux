#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "configeditor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_mastVolSlider_valueChanged(int value);

    void on_disApSlider_valueChanged(int value);

    void on_updateIntSlider_valueChanged(int value);

    void on_musicVolSlider_valueChanged(int value);

    void on_musicIntSlider_valueChanged(int value);

    void on_musicExtSlider_valueChanged(int value);

    void on_cabinMinSlider_valueChanged(int value);

    void on_cabinMaxSlider_valueChanged(int value);

    void on_atcVolSlider_valueChanged(int value);

    void on_atcMinSlider_valueChanged(int value);

    void on_atcMaxSlider_valueChanged(int value);

    void on_delayDisSlider_valueChanged(int value);

    void on_delayMultSlider_valueChanged(int value);

    void on_musicFolderButton_clicked();

    void on_changeAtcButton_clicked();

    void on_resetSysButton_clicked();

    void on_resetSndButton_clicked();

    void on_resetAtcButton_clicked();

    void on_applyButton_clicked();

    void on_actionSelPath_triggered();

    void on_actionAbout_triggered();

    void on_actionRefresh_triggered();

    void on_musicRandom_clicked();

    void on_musicSeq_clicked();

private:
    Ui::MainWindow *ui;

    void setWidgets(ConfigEditor::Config config);

    int getMode(QString mode);

    QString orbiterPath, musicPath, atcPath;

    ConfigEditor configEditor;
};

#endif // MAINWINDOW_H
