#include "yandexmusicapi.h"
#include "filedownloader.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

YandexmusicApi::YandexmusicApi(/*QString &username, QString &password*/)
{

}

YandexmusicApi::~YandexmusicApi() {}

QString YandexmusicApi::getTrackUrl(const QString &storageDir)
{
  FileDownloader *fd = new FileDownloader(QUrl(QString("https://storage.mds.yandex.net/download-info/%1/2?format=json").arg(storageDir)));
  QJsonDocument jsonDoc = QJsonDocument::fromJson(fd->downloadedData());
  fd->~FileDownloader();

  QByteArray h = QCryptographicHash::hash("XGRlBW9FXlekgbPrRHuSiA" +
                                          jsonDoc.object().value("path").toString().mid(1).toUtf8() +
                                          jsonDoc.object().value("s").toString().toUtf8(), QCryptographicHash::Md5);


  return QString("https://") + jsonDoc.object().value("host").toString() + "/get-mp3/" + QString(h.toHex()) + QString("/") +
      jsonDoc.object().value("ts").toString() + jsonDoc.object().value("path").toString();
}

QList<QList<QString> > YandexmusicApi::getTrackInfo(const QString &name)
{
  QList<QList<QString> > trackInfo{{}};
  FileDownloader *fd = new FileDownloader(QUrl(QString("https://music.yandex.ru/handlers/search.jsx?text=%1&type=tracks").arg(name)));
  QJsonDocument jsonDoc = QJsonDocument::fromJson(fd->downloadedData());
  fd->~FileDownloader();

  trackInfo[0].append(QString::number(jsonDoc.object().value("counts").toObject().value("artists").toDouble()));
  trackInfo[0].append(QString::number(jsonDoc.object().value("counts").toObject().value("albums").toDouble()));
  trackInfo[0].append(QString::number(jsonDoc.object().value("counts").toObject().value("tracks").toDouble()));

  QList<QString> tmp {};
  for(int i = 0; i < jsonDoc.object().value("tracks").toObject().value("items").toArray().count(); i++)
    {
      tmp << QString::number(jsonDoc.object().value("tracks").toObject().value("items").toArray().at(i).toObject().value("id").toDouble());
      tmp << jsonDoc.object().value("tracks").toObject().value("items").toArray().at(i).toObject().value("storageDir").toString();
      tmp << QString::number(jsonDoc.object().value("tracks").toObject().value("items").toArray().at(i).toObject().value("durationMs").toDouble() / 1000 /60);
      tmp << jsonDoc.object().value("tracks").toObject().value("items").toArray().at(i).toObject().value("title").toString();
      tmp << QString::number(jsonDoc.object().value("tracks").toObject().value("items").toArray().at(i).toObject().value("album").toObject().value("id").toDouble());
      tmp << QString::number(jsonDoc.object().value("tracks").toObject().value("items").toArray().at(0).toObject().value("album").toObject().value("year").toDouble());
      tmp << jsonDoc.object().value("tracks").toObject().value("items").toArray().at(0).toObject().value("album").toObject().value("title").toString();
      tmp << jsonDoc.object().value("tracks").toObject().value("items").toArray().at(0).toObject().value("album").toObject().value("coverUri").toString();
      tmp << jsonDoc.object().value("tracks").toObject().value("items").toArray().at(0).toObject().value("album").toObject().value("genre").toString();
      trackInfo << tmp;
      tmp.clear();
    }

  return trackInfo;
}

QList<QList<QString> > YandexmusicApi::getArtistInfo(const QString &name)
{
  QList<QList<QString> > artistInfo{{}};
  FileDownloader *fd = new FileDownloader(QUrl(QString("https://music.yandex.ru/handlers/search.jsx?text=%1&type=artists").arg(name)));
  QJsonDocument jsonDoc = QJsonDocument::fromJson(fd->downloadedData());
  fd->~FileDownloader();

  artistInfo[0].append(QString::number(jsonDoc.object().value("counts").toObject().value("artists").toDouble()));
  artistInfo[0].append(QString::number(jsonDoc.object().value("counts").toObject().value("albums").toDouble()));
  artistInfo[0].append(QString::number(jsonDoc.object().value("counts").toObject().value("tracks").toDouble()));

  QList<QString> tmp {};
  for(int i = 0; i < jsonDoc.object().value("artists").toObject().value("items").toArray().count(); i++)
    {
      tmp << QString::number(jsonDoc.object().value("artists").toObject().value("items").toArray().at(i).toObject().value("id").toDouble());
      tmp << jsonDoc.object().value("artists").toObject().value("items").toArray().at(i).toObject().value("name").toString();
      tmp << jsonDoc.object().value("artists").toObject().value("items").toArray().at(i).toObject().value("cover").toObject().value("uri").toString();
      tmp << QString::number(jsonDoc.object().value("artists").toObject().value("items").toArray().at(i).toObject().value("counts").toObject().value("tracks").toDouble());
      tmp << QString::number(jsonDoc.object().value("artists").toObject().value("items").toArray().at(i).toObject().value("counts").toObject().value("directAlbums").toDouble());
      tmp << jsonDoc.object().value("artists").toObject().value("items").toArray().at(i).toObject().value("genres").toArray().at(0).toString();

      artistInfo << tmp;
      tmp.clear();
    }
  qDebug() << artistInfo;

  return artistInfo;
}

QList<QList<QString> > YandexmusicApi::getAlbumInfo(const QString &name)
{
  QList<QList<QString> > albumInfo{{}};
  FileDownloader *fd = new FileDownloader(QUrl(QString("https://music.yandex.ru/handlers/search.jsx?text=%1&type=albums").arg(name)));
  QJsonDocument jsonDoc = QJsonDocument::fromJson(fd->downloadedData());
  fd->~FileDownloader();

  albumInfo[0].append(QString::number(jsonDoc.object().value("counts").toObject().value("artists").toDouble()));
  albumInfo[0].append(QString::number(jsonDoc.object().value("counts").toObject().value("albums").toDouble()));
  albumInfo[0].append(QString::number(jsonDoc.object().value("counts").toObject().value("tracks").toDouble()));

  QList<QString> tmp {};
  for(int i = 0; i < jsonDoc.object().value("albums").toObject().value("items").toArray().count(); i++)
    {
      tmp << QString::number(jsonDoc.object().value("albums").toObject().value("items").toArray().at(i).toObject().value("id").toDouble());
      tmp << jsonDoc.object().value("albums").toObject().value("items").toArray().at(i).toObject().value("storageDir").toString();
      tmp << jsonDoc.object().value("albums").toObject().value("items").toArray().at(i).toObject().value("title").toString();
      tmp << QString::number(jsonDoc.object().value("albums").toObject().value("items").toArray().at(i).toObject().value("year").toDouble());
      tmp << jsonDoc.object().value("albums").toObject().value("items").toArray().at(i).toObject().value("coverUri").toString();
      tmp << QString::number(jsonDoc.object().value("albums").toObject().value("items").toArray().at(i).toObject().value("artists").toObject().value("id").toDouble());
      tmp << jsonDoc.object().value("albums").toObject().value("items").toArray().at(i).toObject().value("artists").toObject().value("name").toString();
      tmp << QString::number(jsonDoc.object().value("albums").toObject().value("items").toArray().at(i).toObject().value("trackCount").toDouble());
      tmp << QString::number(jsonDoc.object().value("albums").toObject().value("items").toArray().at(i).toObject().value("genre").toDouble());

      albumInfo << tmp;
      tmp.clear();
    }

  return albumInfo;
}

QString YandexmusicApi::getTrackParameter(const QList<QString> &trackInfo, trackParameter param)
{
  return trackInfo[static_cast<int>(param)];
}

QString YandexmusicApi::getAlbumParameter(const QList<QString> &albumInfo, albumParameter param)
{
  return albumInfo[static_cast<int>(param)];
}

QString YandexmusicApi::getArtistParameter(const QList<QString> &artistInfo, artistParameter param)
{
  return artistInfo[static_cast<int>(param)];
}
