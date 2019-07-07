#include "recording.h"

Recording::Recording(QString link, double lenght, QString path, qint8 cam_idx, double days) : QObject(nullptr) {        //Base constructor
    qDebug() << Q_FUNC_INFO;
    prog = "ffmpeg";                                                                                                    //Extern process
    QDir dir;
    dir.mkpath( path + "cam" + QString::number(cam_idx) );                                                              //Making dirs for records file

    partpath = QString( path + "cam" + QString::number(cam_idx) + "/" + "cam" + QString::number(cam_idx) );             //Building record file path "/home/sk/rec/camX/camX"
    arguments << "-i" << link << "-vcodec" << "copy" << "-t" << QString::number(lenght*60, 'f', 0) << "-y" << partpath; //Building list of paramiters to ffmpeg
    archiving_days=days;                                                                                                //File older than 'days' will be delete

    connect( &proc, SIGNAL ( finished(int,QProcess::ExitStatus) ), this, SLOT(slot_finished ( int,QProcess::ExitStatus) ) );     //Finish catch
    connect( &proc, SIGNAL ( error(QProcess::ProcessError) ), this, SLOT(slot_error (QProcess::ProcessError) ) );                //Error catch
}

Recording::Recording(const Recording &other) : QObject(nullptr) {   //Copying constructor
    qDebug() << Q_FUNC_INFO;
    prog = other.prog;
    arguments = other.arguments;
    partpath = other.partpath;
    archiving_days = other.archiving_days;

    connect( &proc, SIGNAL( finished(int,QProcess::ExitStatus) ), this, SLOT( slot_finished(int,QProcess::ExitStatus) ) );     //Finish catch
    connect( &proc, SIGNAL( error(QProcess::ProcessError) ), this, SLOT( slot_error(QProcess::ProcessError) ) );               //Error catch
}

Recording& Recording::operator=(const Recording& obj) {
    qDebug() << Q_FUNC_INFO;
    prog = obj.prog;
    arguments = obj.arguments;
    return *this;
}

void Recording::Start() {
    qDebug() << Q_FUNC_INFO;
    if( proc.state() != QProcess::ProcessState::Running ) {                         //If process not running run new one
        auto stamp = QDateTime::currentDateTime().toString("yyyyMMdd-hhmmss");      //Get current timestamp
        arguments.removeLast();                                                     //Remove out-of-date timestamp "/home/sk/rec/camX/camX" or "/home/sk/rec/camX/camX-ddmmyy-hhmmss.mp4"
        arguments.append( QString(partpath + "-" + stamp + ".mp4") );               //Add timestamp
        proc.start ( prog, arguments );                                             //Run process
    }
}

void Recording::DeleteOlderRecordsThan(qint8 days) {
    qDebug() << Q_FUNC_INFO;
    const QDate today = QDate::currentDate();       //Get current date
    QStringList shot_path = partpath.split('/');    //Building list from string -> "/home/sk/rec/camX/camX"         //example: const QString path = QCoreApplication::applicationDirPath() + "/log/";
    shot_path.removeLast();                         //Removing last 'camX'
    QString path = shot_path.join('/');             //Joinging list after removed last element
    QString(path + "/");                            //Adding '/' char

    Q_FOREACH (auto fileInfo, QDir(path).entryInfoList(QStringList("*.mp4"), QDir::Files)) {        //Serching type file
        if(fileInfo.fileName().contains("keep")) continue;                                          //Skip
        if(fileInfo.created().date().daysTo(today) > days) {                                        //Sechring older files than 'days'
            QString filepath = fileInfo.absoluteFilePath();                                         //Building path to old file
            QDir deletefile;
            deletefile.setPath(filepath);
            deletefile.remove(filepath);                                                            //Deleting file
            qDebug() << "File " + filepath + " is deleted!";
        }
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                             SLOTS                                                   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Recording::slot_finished(int code, QProcess::ExitStatus status ) {
    qDebug() << Q_FUNC_INFO << prog << arguments;
    qDebug() << "ExitStatus:" << status;                                    //Exit status
    qDebug() << "Code:" << code;                                            //Exit code

    Recording::DeleteOlderRecordsThan( qint8(Recording::archiving_days) );  //Delete old files
    Recording::Start();                                                     //Loop recording
}

void Recording::slot_error(QProcess::ProcessError e) {
    qDebug() << Q_FUNC_INFO << e <<prog << arguments;
    qDebug() << "Error:" <<e;
}
