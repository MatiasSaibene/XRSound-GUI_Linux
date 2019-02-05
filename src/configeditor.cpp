#include "configeditor.h"

ConfigEditor::ConfigEditor() : ini(true, false, true), settings("config.cfg", QSettings::IniFormat){}

const char* toStr(double x)
{
    return QString::number(x).toStdString().c_str();
}

const char* toStr(int x)
{
    return QString::number(x).toStdString().c_str();
}

ConfigEditor::Config ConfigEditor::readConfig()
{
    settings.sync();

    settings.beginGroup("General");

    QString orbiterPath = settings.value("OrbiterPath").toString();

    settings.endGroup();

    return readConfig(orbiterPath);
}

ConfigEditor::Config ConfigEditor::readConfig(QString orbiterPath)
{
    ini.LoadFile(QString(orbiterPath + "XRSound/XRSound.cfg").toStdString().c_str());

    double mastVol = atof(ini.GetValue("SYSTEM", "MasterVolume", "1.0"));

    int verbLog = atoi(ini.GetValue("SYSTEM", "EnableVerboseLogging", "0"));
    int animLog = atoi(ini.GetValue("SYSTEM", "LogVesselAnimations", "0"));
    int thrLog = atoi(ini.GetValue("SYSTEM", "LogThrusterData", "0"));
    int silenceSpace = atoi(ini.GetValue("SYSTEM", "SilenceOfSpace", "1"));
    int disApThr = atoi(ini.GetValue("SYSTEM", "DisableAutopilotsTimeAccThreshold", "100"));

    double updateInt = atof(ini.GetValue("SYSTEM", "UpdateInterval", "0.05"));

    QString musicFolder = ini.GetValue("SYSTEM", "MusicFolder", "XRSound/Default/Music");

    double musicVol = atof(ini.GetValue("SYSTEM", "MusicVolume", "1.0"));

    bool isRandom;
    QString musicOrder = ini.GetValue("SYSTEM", "MusicOrder", "random");
    if(musicOrder.toLower() == "random") isRandom = true;
    else isRandom = false;

    QString musicPlayInt = ini.GetValue("SOUND_FILES", "MusicPlayInternal", "Off");
    musicPlayInt[0] = musicPlayInt[0].toUpper();
    QString musicPlayExt = ini.GetValue("SOUND_FILES", "MusicPlayExternal", "Space");
    musicPlayExt[0] = musicPlayExt[0].toUpper();

    int cabinAmbMin = atoi(ini.GetValue("SOUND_GROUPS", "CabinAmbienceMin", "7"));
    int cabinAmbMax = atoi(ini.GetValue("SOUND_GROUPS", "CabinAmbienceMax", "35"));

    QString atcFolder = ini.GetValue("ATC", "Folder", "XRSound/Default/Altea STS");

    double atcVol = atof(ini.GetValue("ATC", "Volume", "1.0"));

    int atcMinDelay = atoi(ini.GetValue("ATC", "MinDelay", "15"));
    int atcMaxDelay = atoi(ini.GetValue("ATC", "MaxDelay", "120"));
    int atcWhileLand = atoi(ini.GetValue("ATC", "AllowWhileLanded", "1"));
    int atcWhileReent = atoi(ini.GetValue("ATC", "AllowDuringReentry", "0"));
    int atcInAtm = atoi(ini.GetValue("ATC", "AllowInAtmosphere", "1"));
    int delayPlanDis = atoi(ini.GetValue("ATC", "DelayPlanetDistance", "400"));
    int delayPlanMult = atoi(ini.GetValue("ATC", "DelayPlanetMultiplier", "5"));

    // Return data as config struct
    return {orbiterPath, mastVol, verbLog, animLog, thrLog, silenceSpace, disApThr, updateInt,
            musicFolder, musicVol, isRandom, musicPlayInt, musicPlayExt, cabinAmbMin, cabinAmbMax,
            atcFolder, atcVol, atcMinDelay, atcMaxDelay, atcWhileLand, atcWhileReent, atcInAtm,
            delayPlanDis, delayPlanMult};
}

void ConfigEditor::writeConfig(Config config)
{
    ini.SetDoubleValue("SYSTEM", "MasterVolume", config.mastVol);

    ini.SetValue("SYSTEM", "EnableVerboseLogging", toStr(config.verbLog));
    ini.SetValue("SYSTEM", "LogVesselAnimations", toStr(config.animLog));
    ini.SetValue("SYSTEM", "LogThrusterData", toStr(config.thrLog));
    ini.SetValue("SYSTEM", "SilenceOfSpace", toStr(config.silenceSpace));
    ini.SetValue("SYSTEM", "DisableAutopilotsTimeAccThreshold", toStr(config.disApThr));

    ini.SetDoubleValue("SYSTEM", "UpdateInterval", config.updateInt);

    ini.SetValue("SYSTEM", "MusicFolder", config.musicFolder.toStdString().c_str());

    ini.SetDoubleValue("SYSTEM", "MusicVolume", config.musicVol);

    QString order;
    if(config.isRandom) order = "random";
    else order = "sequential";
    ini.SetValue("SYSTEM", "MusicOrder",  order.toStdString().c_str());

    ini.SetValue("SOUND_FILES", "MusicPlayInternal", config.musicPlayInt.toStdString().c_str());
    ini.SetValue("SOUND_FILES", "MusicPlayExternal", config.musicPlayExt.toStdString().c_str());

    ini.SetValue("SOUND_GROUPS", "CabinAmbienceMin", toStr(config.cabinAmbMin));
    ini.SetValue("SOUND_GROUPS", "CabinAmbienceMax", toStr(config.cabinAmbMax));

    ini.SetValue("ATC", "Folder", config.atcFolder.toStdString().c_str());

    ini.SetDoubleValue("ATC", "Volume", config.atcVol);

    ini.SetValue("ATC", "MinDelay", toStr(config.atcMinDelay));
    ini.SetValue("ATC", "MaxDelay", toStr(config.atcMaxDelay));
    ini.SetValue("ATC", "AllowWhileLanded", toStr(config.atcWhileLand));
    ini.SetValue("ATC", "AllowDuringReentry", toStr(config.atcWhileReent));
    ini.SetValue("ATC", "AllowInAtmosphere", toStr(config.atcInAtm));
    ini.SetValue("ATC", "DelayPlanetDistance", toStr(config.delayPlanDis));
    ini.SetValue("ATC", "DelayPlanetMultiplier", toStr(config.delayPlanMult));

    ini.SaveFile(QString(config.orbiterPath + "XRSound/XRSound.cfg").toStdString().c_str());
}

void ConfigEditor::writeConfig(QString orbiterPath)
{
    settings.clear();

    settings.beginGroup("General");

    settings.setValue("OrbiterPath", orbiterPath);

    settings.endGroup();
}
