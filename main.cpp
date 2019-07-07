#include <QCoreApplication>
#include "jsonconfig.h"
#include "recording.h"

/*
 * MyLinksToTests:
 *      rtsp://admin:Admin123456@192.168.204.26:2101/Streaming/Channels/2   //pixel
 *      rtsp://admin:admin@10.1.1.246:8554/CH002.sdp                        //home
 */

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << QDateTime::currentDateTime().toString("yyyy.MM.dd-hh:mm:ss") << "RVSR start..." << endl;

    JsonConfig conf;                                    //Cfg object
    QList<Recording> rec;                               //List of recorded objects

    if( true == conf.JsonConfig::LoadConfig() ) {       //If cfg is loaded
        conf.JsonConfig::ShowConfig();                  //Show cfg in debug

        for(qint8 i=0; i<conf.CountCams(); ++i) {       //Building records objects
            Recording cam_object( conf.JsonConfig::ConnectLink(i), conf.JsonConfig::SegmentLenght(), conf.JsonConfig::GetPath(), i , conf.JsonConfig::GetArchivingDays() );
            rec.append(cam_object);                     //Add builded obcect to list
            rec.last().Start();                         //Start recording
        }
    }
    else {
        qDebug() << "The configuration file can not be opened...";
    }
    return a.exec();
}
