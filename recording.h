#ifndef RECORDING_H
#define RECORDING_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QProcess>
#include <QDateTime>
#include <QDir>
#include <QFileInfo>

class Recording : public QObject
{
    Q_OBJECT
private:
    QProcess proc;
    QString prog;
    QString partpath;
    QStringList arguments;
    double archiving_days;

public:
    Recording(QString link, double lenght, QString path, qint8 cam_idx, double days);    //Base constructor
    Recording(const Recording &other);                                                   //Copying constructor
    void Start();                                                           //Start recording
    void DeleteOlderRecordsThan(qint8 days);                                //Deleting old files

    Recording &operator =(const Recording &obj);                              //Operator =

public slots:
    void slot_finished(int, QProcess::ExitStatus);                          //Fished process slot
    void slot_error(QProcess::ProcessError e);                              //Exit with error slot
};

#endif // RECORDING_H
