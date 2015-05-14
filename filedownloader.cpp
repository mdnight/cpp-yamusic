#include "filedownloader.h"
#include <QDebug>
#include <QTimer>

FileDownloader::FileDownloader(QUrl url) : QObject()
{
  mngr = new QNetworkAccessManager(this);
  loop = new QEventLoop;
  QObject::connect(mngr, SIGNAL(finished(QNetworkReply*)),this, SLOT(fileDownloaded(QNetworkReply*)));
  QObject::connect(mngr, SIGNAL(finished(QNetworkReply*)), loop, SLOT(quit()));

  getData(url);
}

FileDownloader::~FileDownloader()
{
  delete mngr;
  delete loop;
}

void FileDownloader::fileDownloaded(QNetworkReply *preply)
{

  m_DownloadedData = preply->readAll();
  preply->deleteLater();
  code = 0;
  qWarning() << "Success";
  emit downloaded();
}

QByteArray FileDownloader::downloadedData() const
{
  return m_DownloadedData;
}

void FileDownloader::onTimeOut()
{
  loop->quit();
  qWarning() << "Error: Link is unavaliable";
  code = 1;
}

void FileDownloader::getData(QUrl &link)
{
  QNetworkRequest *request = new QNetworkRequest(link);
  mngr->get(*request);
  QTimer::singleShot(10000, this, SLOT(onTimeOut()));
  loop->exec();
  delete request;
}
