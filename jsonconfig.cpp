#include "jsonconfig.h"

JsonConfig::JsonConfig(double lenght, QString path, double arch_days, QString rtsp) {
    qDebug() << Q_FUNC_INFO;
    segment_lenght=lenght;
    record_path=path;
    archiving_days=arch_days;
    rtsp_link.clear();
    if( !rtsp.isNull() ) {
        rtsp_link.append(rtsp);
    }
}

void JsonConfig::ShowConfig() {
    qDebug() << Q_FUNC_INFO;
    qDebug()<< "  GeneralSettings";
    qDebug()<< "     SegmentLenghtInMins :" << segment_lenght;
    qDebug()<< "     RecordsPath :" << record_path;
    qDebug()<< "     ArchivingInDays:" << archiving_days;
    qDebug()<< "  Cameras";
//    for(QStringList::iterator it=rtsp_link.begin(); it<rtsp_link.end(); ++it) {   //another way
//        qDebug() << "  " << *it;
//    }
    for ( auto& it : rtsp_link ) {
        qDebug() << "    " << it;
    }
}

bool JsonConfig::ParseConfig(QJsonDocument cfg) {
    qDebug() << Q_FUNC_INFO;
    if( cfg["GeneralSettings"].isObject() ) {
        segment_lenght=cfg["GeneralSettings"]["SegmentLenghtInMins"].toDouble();
        record_path=cfg["GeneralSettings"]["RecordsPath"].toString();
        archiving_days=cfg["GeneralSettings"]["ArchivingInDays"].toDouble();

        if( cfg["Cameras"].isArray() ) {
            QJsonArray Cams = cfg["Cameras"].toArray();
            if( !Cams.isEmpty() ) {
                for(qint8 i=0; i<Cams.count(); ++i) {
                    JsonConfig::rtsp_link.append( Cams.at(i).toString() );
                }
                return true;
            }
        }
    }
    return false;
}

bool JsonConfig::LoadConfig() {
    qDebug() << Q_FUNC_INFO;
    QFile file;
    file.setFileName("config.json");                                                //Configuration file
    file.open(QIODevice::ReadOnly | QIODevice::Text);                               //Open file
    QJsonParseError jsonError;
    QJsonDocument configJson = QJsonDocument::fromJson(file.readAll(),&jsonError);  //Read from file
    file.close();                                                                   //Close file arfer read

    if(jsonError.error != QJsonParseError::NoError) {                               //Checking errors
        qDebug() << jsonError.errorString();
        return false;
    }
    else if( !configJson.isEmpty() ) {                                              //Object is't empty
        return JsonConfig::ParseConfig(configJson);                                 //Parse configuration paramiters
    }
    else return false;
}

QString JsonConfig::ConnectLink(qint8 idx) {
    if( rtsp_link.length() && idx>=0 ) {
            return rtsp_link.at(idx);
        }
    return QString();
}

QStringList JsonConfig::ConnectLinkList() {
    return rtsp_link;
}

qint8 JsonConfig::CountCams() {
    return rtsp_link.count();
}

double JsonConfig::SegmentLenght() {
    return segment_lenght;
}

QString JsonConfig::GetPath() {
    return record_path;
}

double JsonConfig::GetArchivingDays() {
    return archiving_days;
}
