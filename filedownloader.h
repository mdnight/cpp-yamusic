#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>

class FileDownloader : public QObject
{
  Q_OBJECT
public:
  explicit FileDownloader(QUrl url);
  explicit FileDownloader();
  virtual ~FileDownloader();
  QByteArray downloadedData() const;
  void getData(const QUrl &link);
  void clearData();

signals:
  void downloaded();


private slots:
  void fileDownloaded(QNetworkReply *preply);
  void onTimeOut();

private:
  quint8 code;  //0 - успешно; 1 -- ошибка загрузки
  QNetworkAccessManager *mngr;
  QByteArray m_DownloadedData;
  QEventLoop *loop;
};

#endif // FILEDOWNLOADER_H
