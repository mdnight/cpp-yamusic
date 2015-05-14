#ifndef YANDEXMUSICAPI_H
#define YANDEXMUSICAPI_H

#include <QHash>
#include <QString>
#include <QJsonObject>
#include <QtNetwork>


class YandexmusicApi
{

public:
  YandexmusicApi(QString &username, QString &password);
  QString getTrackUrl(const QString &storageDir);
  QList<QList<QString> > getTrackInfo(const QString &name);
  QList<QList<QString> > getArtistInfo(const QString &name);
  QList<QList<QString> > getAlbumInfo(const QString &name);



private:
  QJsonObject getAuthHeader();
  void getUsernameAndPassword();
  QJsonObject performRequest();
  QJsonObject *request;
};

#endif // YANDEXMUSICAPI_H
