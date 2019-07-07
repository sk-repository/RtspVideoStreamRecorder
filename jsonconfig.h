#ifndef JSONCONFIG_H
#define JSONCONFIG_H

//#include <QObject>
#include <QJsonDocument>
#include <QFile>
#include <QJsonArray>
#include <QDebug>
#include <QString>

class JsonConfig
{
private:
    double segment_lenght;
    QString record_path;
    double archiving_days;
    QStringList rtsp_link;
    bool ParseConfig(QJsonDocument cfg);    //JsonCfg Parsing

public:
    JsonConfig(double lenght=0, QString path=NULL, double arch_days=0, QString rtsp=NULL);  //creating object

    void ShowConfig();              //show loaded configuration
    bool LoadConfig();              //load config paramieters to class
    qint8 CountCams();              //amount of cameras from configuration
    QString ConnectLink(qint8 idx); //rtsp link of the indicated camera | not used
    QStringList ConnectLinkList();  //returns cameras list
    double SegmentLenght();         //returns value lenght record file
    QString GetPath();              //returns Path to record file
    double GetArchivingDays();      //how many file archive

};

#endif // JSONCONFIG_H
