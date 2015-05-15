#ifndef YANDEXMUSICAPI_H
#define YANDEXMUSICAPI_H

#include <QHash>
#include <QString>
#include <QtNetwork>


class YandexmusicApi
{

public:
  YandexmusicApi();
  ~YandexmusicApi();
  QString getTrackUrl(const QString &storageDir);
  QList<QList<QString> > getTrackInfo(const QString &name);
  QList<QList<QString> > getArtistInfo(const QString &name);
  QList<QList<QString> > getAlbumInfo(const QString &name);

private:
  void getUsernameAndPassword();
};

#endif // YANDEXMUSICAPI_H
