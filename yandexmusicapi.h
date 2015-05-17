#ifndef YANDEXMUSICAPI_H
#define YANDEXMUSICAPI_H

#include <QHash>
#include <QString>
#include <QtNetwork>

class YandexmusicApi
{

public:
  enum class trackParameter : int {TrackId = 0, StorageDir, DurationSec, Title, AlbumId, Year, AlbumTitle, CoverUrl, Genre, ArtistName};
  enum class albumParameter : int {AlbumId = 0, StorageDir, Title, Year, CoverUri, ArtistId, ArtistName, TrackCount, Genre};
  enum class artistParameter : int {Id = 0, Name, CoverUri, Tracks, DirectAlbums, Genre};

  YandexmusicApi();
  ~YandexmusicApi();
  QString getTrackUrl(const QString &storageDir);
  QList<QList<QString> > getTrackInfo(const QString &name);
  QList<QList<QString> > getArtistInfo(const QString &name);
  QList<QList<QString> > getAlbumInfo(const QString &name);
  QString getTrackParameter(const QList<QString> &trackInfo, YandexmusicApi::trackParameter param);
  QString getAlbumParameter(const QList<QString> &albumInfo, YandexmusicApi::albumParameter param);
  QString getArtistParameter(const QList<QString> &artistInfo, YandexmusicApi::artistParameter param);

private:
  void getUsernameAndPassword();
};

#endif // YANDEXMUSICAPI_H
