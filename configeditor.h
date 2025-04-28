#ifndef CONFIGEDITOR_H
#define CONFIGEDITOR_H

#include <QString>
#include "SimpleIni.h"
#include <QSettings>

class ConfigEditor{

public:
    struct Config{
        QString orbiterPath;
        double mastVol;
        int verbLog, animLog, thrLog, silenceSpace, disApThr;
        double updateInt;
        QString musicFolder;
        double musicVol;
        bool isRandom;
        QString musicPlayInt;
        QString musicPlayExt;
        int cabinAmbMin, cabinAmbMax;
        QString atcFolder;
        double atcVol;
        int atcMinDelay, atcMaxDelay, atcWhileLand, atcWhileReent, atcInAtm, delayPlanDis, delayPlanMult;
    };

    ConfigEditor();

    Config readConfig(QString orbiterPath);

    Config readConfig();

    void writeConfig(Config config);

    void writeConfig(QString orbiterPath);
private:
    CSimpleIniA ini;

    QSettings settings;
};

#endif // CONFIGEDITOR_H
