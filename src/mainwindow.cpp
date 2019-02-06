#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileInfo>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto config = configEditor.readConfig();

    orbiterPath = config.orbiterPath;

    if(!QFileInfo(orbiterPath + "orbiter.exe").isFile()) {on_actionSelPath_triggered(); return;}

    // If XRSound.cfg doesn't exists or it can't be written
    if(!QFileInfo(orbiterPath + "XRSound/XRSound.cfg").isWritable()) {
        QMessageBox::critical(this, "Can't find XRSound",
                              "Can't find XRSound installation. Please make sure XRSound.cfg file already exists"
                              " in XRSound folder.");
        ui->centralWidget->setEnabled(false);
        return;
    }

    setWidgets(config);
}

void MainWindow::setWidgets(ConfigEditor::Config config)
{
    musicPath = QDir::fromNativeSeparators(config.musicFolder);
    atcPath = QDir::fromNativeSeparators(config.atcFolder);

    // System group
    int masterVolume = int(config.mastVol * 100);
    ui->mastVolLabel->setText("Master volume: " + QString::number(masterVolume) + "%");
    ui->mastVolSlider->setValue(masterVolume);

    ui->enableVerbCheck->setChecked(config.verbLog);
    ui->logAnimCheck->setChecked(config.animLog);
    ui->logThrCheck->setChecked(config.thrLog);
    ui->silenceSpCheck->setChecked(config.silenceSpace);

    ui->disApLabel->setText("Disable autopilots time acceleration threshold: " + QString::number(config.disApThr) + "x");
    ui->disApSlider->setValue(config.disApThr);

    int updateInterval = int(config.updateInt * 100);
    ui->updateIntLabel->setText("Update interval: " + QString::number(config.updateInt) + "s");
    ui->updateIntSlider->setValue(updateInterval);

    ui->musicFolderLabel->setText("Music folder: " + musicPath);

    int musicVolume = int(config.musicVol * 100);
    ui->musicVolLabel->setText("Music volume: " + QString::number(musicVolume) + "%");
    ui->musicVolSlider->setValue(musicVolume);

    QString order;
    if(config.isRandom) order = "Random";
    else order = "Sequential";
    ui->musicOrderLabel->setText("Music order: " + order);
    ui->musicRandom->setChecked(config.isRandom);
    ui->musicSeq->setChecked(!config.isRandom);

    // Sound files and groups group
    int musicPlayInt = getMode(config.musicPlayInt);
    ui->musicIntLabel->setText("Music play internal: " + config.musicPlayInt);
    ui->musicIntSlider->setValue(musicPlayInt);

    int musicPlayExt = getMode(config.musicPlayExt);
    ui->musicExtLabel->setText("Music play external: " + config.musicPlayExt);
    ui->musicExtSlider->setValue(musicPlayExt);

    ui->cabinMinLabel->setText("Cabin ambience minimum time: " + QString::number(config.cabinAmbMin) + "s");
    ui->cabinMinSlider->setValue(config.cabinAmbMin);

    ui->cabinMaxLabel->setText("Cabin ambience maximum time: " + QString::number(config.cabinAmbMax) + "s");
    ui->cabinMaxSlider->setValue(config.cabinAmbMax);


    // ATC group
    ui->atcFolderLabel->setText("ATC folder: " + atcPath);

    int atcVolume = int(config.atcVol * 100);
    ui->atcVolumeLabel->setText("ATC volume: " + QString::number(atcVolume) + "%");
    ui->atcVolSlider->setValue(atcVolume);

    ui->atcMinLabel->setText("ATC minimum time: " + QString::number(config.atcMinDelay) + "s");
    ui->atcMinSlider->setValue(config.atcMinDelay);

    ui->atcMaxLabel->setText("ATC maximum time: " + QString::number(config.atcMaxDelay) + "s");
    ui->atcMaxSlider->setValue(config.atcMaxDelay);

    ui->allowLandCheck->setChecked(config.atcWhileLand);
    ui->allowReentCheck->setChecked(config.atcWhileReent);
    ui->allowAtmCheck->setChecked(config.atcInAtm);

    ui->delayDisLabel->setText("Delay planet distance: " + QString::number(config.delayPlanDis) + "km");
    ui->delayDisSlider->setValue(config.delayPlanDis);

    ui->delayMultLabel->setText("Delay planet multiplier: " + QString::number(config.delayPlanMult) + "x");
    ui->delayMultSlider->setValue(config.delayPlanMult);
}

// Get index for the mode to set the slider
int MainWindow::getMode(QString mode)
{
    mode = mode.toLower();
    if(mode == "off") return 0;
    else if(mode == "space") return 1;
    else return 2;
}

void MainWindow::on_mastVolSlider_valueChanged(int value)
{
    ui->mastVolLabel->setText("Master volume: " + QString::number(value) + "%");
}

void MainWindow::on_disApSlider_valueChanged(int value)
{
    ui->disApLabel->setText("Disable autopilots time acceleration threshold: " + QString::number(value) + "x");
}

void MainWindow::on_updateIntSlider_valueChanged(int value)
{
    ui->updateIntLabel->setText("Update interval: " + QString::number(double(value) / 100) + "s");
}

void MainWindow::on_musicVolSlider_valueChanged(int value)
{
    ui->musicVolLabel->setText("Music volume: " + QString::number(value) + "%");
}

void MainWindow::on_musicRandom_clicked()
{
    ui->musicOrderLabel->setText("Music order: Random");
}

void MainWindow::on_musicSeq_clicked()
{
    ui->musicOrderLabel->setText("Music order: Sequential");
}

void MainWindow::on_musicIntSlider_valueChanged(int value)
{
    switch (value) {
    case 0: ui->musicIntLabel->setText("Music play internal: Off"); break;
    case 1: ui->musicIntLabel->setText("Music play internal: Space"); break;
    case 2: ui->musicIntLabel->setText("Music play internal: On"); break;
    }
}

void MainWindow::on_musicExtSlider_valueChanged(int value)
{
    switch (value) {
    case 0: ui->musicExtLabel->setText("Music play external: Off"); break;
    case 1: ui->musicExtLabel->setText("Music play external: Space"); break;
    case 2: ui->musicExtLabel->setText("Music play external: On"); break;
    }
}

void MainWindow::on_cabinMinSlider_valueChanged(int value)
{
    ui->cabinMinLabel->setText("Cabin ambience minimum time: " + QString::number(value) + "s");
    ui->cabinMaxSlider->setMinimum(value);
}

void MainWindow::on_cabinMaxSlider_valueChanged(int value)
{
    ui->cabinMaxLabel->setText("Cabin ambience maximum time: " + QString::number(value) + "s");
}

void MainWindow::on_atcVolSlider_valueChanged(int value)
{
    ui->atcVolumeLabel->setText("ATC volume: " + QString::number(value) + "%");
}

void MainWindow::on_atcMinSlider_valueChanged(int value)
{
    ui->atcMinLabel->setText("ATC minimum time: " + QString::number(value) + "s");
    ui->atcMaxSlider->setMinimum(value);
}

void MainWindow::on_atcMaxSlider_valueChanged(int value)
{
    ui->atcMaxLabel->setText("ATC maximum time: " + QString::number(value) + "s");
}

void MainWindow::on_delayDisSlider_valueChanged(int value)
{
    ui->delayDisLabel->setText("Delay planet distance: " + QString::number(value) + "km");
}

void MainWindow::on_delayMultSlider_valueChanged(int value)
{
    ui->delayMultLabel->setText("Delay planet multiplier: " + QString::number(value) + "x");
}

void MainWindow::on_musicFolderButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Select music folder", orbiterPath);

    // If user closed the dialog without choosing any folder
    if(dir.isEmpty()) {
        musicPath = "none";
        ui->musicFolderLabel->setText("Music folder: None");
        return;
    }

    // Get the folder path relative to Orbiter folder
    QString tempDir = QDir(orbiterPath).relativeFilePath(dir);

    // If the folder is outside Orbiter folder
    if(tempDir.startsWith(".")) {
        QMessageBox::warning(this, "Selected folder isn't valid",
                                                        "You must select a folder inside Orbiter folder");
        return;
    }

    ui->musicFolderLabel->setText("Music folder: " + tempDir);
}

void MainWindow::on_changeAtcButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Select ATC folder", orbiterPath);

    // If user closed the dialog without choosing any folder
    if(dir.isEmpty()) {
        atcPath = "none";
        ui->atcFolderLabel->setText("ATC folder: None");
        return;
    }

    // Get the folder path relative to Orbiter folder
    QString tempDir = QDir(orbiterPath).relativeFilePath(dir);

    // If the folder is outside Orbiter folder
    if(tempDir.startsWith(".")) {
        QMessageBox::warning(this, "Selected folder isn't valid",
                                                        "You must select a folder inside Orbiter folder");
        return;
    }

    ui->atcFolderLabel->setText("ATC folder: " + tempDir);
}

void MainWindow::on_resetSysButton_clicked()
{
    QMessageBox::StandardButton res = QMessageBox::question(this, "Reset system group values",
                                                            "Are you sure you want to reset system group values to defaults?");

    if(res != QMessageBox::Yes) return;

    ui->mastVolSlider->setValue(100);

    ui->enableVerbCheck->setChecked(false);
    ui->logAnimCheck->setChecked(false);
    ui->logThrCheck->setChecked(false);
    ui->silenceSpCheck->setChecked(true);

    ui->disApSlider->setValue(100);

    ui->updateIntSlider->setValue(5);

    musicPath = "XRSound/Default/Music";
    ui->musicFolderLabel->setText("Music folder: XRSound/Default/Music");

    ui->musicVolSlider->setValue(100);

    ui->musicOrderLabel->setText("Music order: Random");
    ui->musicRandom->setChecked(true);
}

void MainWindow::on_resetSndButton_clicked()
{
    QMessageBox::StandardButton res = QMessageBox::question(this, "Reset sound group values",
                                                            "Are you sure you want to reset sound group values to defaults?");

    if(res != QMessageBox::Yes) return;

    ui->musicIntSlider->setValue(0);
    ui->musicExtSlider->setValue(1);

    ui->cabinMinSlider->setValue(7);
    ui->cabinMaxSlider->setValue(35);
}

void MainWindow::on_resetAtcButton_clicked()
{
    QMessageBox::StandardButton res = QMessageBox::question(this, "Reset ATC group values",
                                                            "Are you sure you want to reset ATC group values to defaults?");

    if(res != QMessageBox::Yes) return;

    atcPath = "XRSound/Default/Altea STS";
    ui->atcFolderLabel->setText("ATC folder: XRSound/Default/Altea STS");

    ui->atcVolSlider->setValue(100);
    ui->atcMinSlider->setValue(15);
    ui->atcMaxSlider->setValue(120);

    ui->allowLandCheck->setChecked(true);
    ui->allowReentCheck->setChecked(false);
    ui->allowAtmCheck->setChecked(true);

    ui->delayDisSlider->setValue(400);
    ui->delayMultSlider->setValue(5);
}

void MainWindow::on_applyButton_clicked()
{
    QString intMode, extMode;

    switch (ui->musicIntSlider->value()) {
    case 0: intMode = "off"; break;
    case 1: intMode = "space"; break;
    case 2: intMode = "on"; break;
    }

    switch (ui->musicExtSlider->value()) {
    case 0: extMode = "off"; break;
    case 1: extMode = "space"; break;
    case 2: extMode = "on"; break;
    }

    configEditor.writeConfig({orbiterPath, double(ui->mastVolSlider->value()) / 100,
                               ui->enableVerbCheck->isChecked(), ui->logAnimCheck->isChecked(),
                               ui->logThrCheck->isChecked(), ui->silenceSpCheck->isChecked(),
                               ui->disApSlider->value(), double(ui->updateIntSlider->value()) / 100,
                               QDir::toNativeSeparators(musicPath), double(ui->musicVolSlider->value()) / 100,
                               ui->musicRandom->isChecked(), intMode, extMode, ui->cabinMinSlider->value(),
                               ui->cabinMaxSlider->value(), QDir::toNativeSeparators(atcPath),
                               double(ui->atcVolSlider->value()) / 100, ui->atcMinSlider->value(),
                               ui->atcMaxSlider->value(), ui->allowLandCheck->isChecked(),
                               ui->allowReentCheck->isChecked(), ui->allowAtmCheck->isChecked(),
                               ui->delayDisSlider->value(), ui->delayMultSlider->value()});
}

void MainWindow::on_actionSelPath_triggered()
{
    orbiterPath = QFileDialog::getExistingDirectory(this, "Select Orbiter folder");

    orbiterPath += "/";

    if(!QFileInfo(orbiterPath + "orbiter.exe").isFile()){
        QMessageBox::warning(this, "Wrong Orbiter folder", "Please select a correct Orbiter folder");
        ui->centralWidget->setEnabled(false);
        return;
    } else if(!QFileInfo(orbiterPath + "XRSound/XRSound.cfg").isWritable()) {
        QMessageBox::critical(this, "Can't find XRSound",
                              "Can't find XRSound installation. Please make sure XRSound.cfg file already exists"
                              " in XRSound folder.");
        ui->centralWidget->setEnabled(false);
        return;
    }

    ui->centralWidget->setEnabled(true);

    setWidgets(configEditor.readConfig(orbiterPath));
}

void MainWindow::on_actionRefresh_triggered()
{
    if(!QFileInfo(orbiterPath + "orbiter.exe").isFile()){
        QMessageBox::warning(this, "Wrong Orbiter folder", "Please select a correct Orbiter folder");
        ui->centralWidget->setEnabled(false);
        return;
    } else if(!QFileInfo(orbiterPath + "XRSound/XRSound.cfg").isWritable()) {
        QMessageBox::critical(this, "Can't find XRSound",
                              "Can't find XRSound installation. Please make sure XRSound.cfg file already exists"
                              " in XRSound folder.");
        ui->centralWidget->setEnabled(false);
        return;
    }

    ui->centralWidget->setEnabled(true);

    setWidgets(configEditor.readConfig(orbiterPath));
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "About XRSound GUI", "XRSound GUI <br>"
                                                  "A graphical interface to configure XRSound. <br> <br>"

                                                  "Version: 1.0a <br>"
                                                  "Build date: Feb 2019 <br>"
                                                  "Check for updates on <a href='https://github.com/abdullah-radwan/XRSound-GUI/releases'>"
                                                  "GitHub</a>. <br> <br> "

                                                  "Copyright © Abdullah Radwan <br>");
}

MainWindow::~MainWindow()
{
    configEditor.writeConfig(orbiterPath);
    delete ui;
}
