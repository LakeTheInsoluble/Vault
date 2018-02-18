// Copied from: https://wiki.qt.io/Download_Data_from_URL

#include "filedownloader.hh"

#include <QNetworkRequest>
#include <QNetworkReply>

FileDownloader::FileDownloader(QUrl url, QObject *parent) :
    QObject(parent)
{
    connect(&netAccessManager_, &QNetworkAccessManager::finished,
            this, &FileDownloader::fileDownloaded);

    QNetworkRequest request(url);
    netAccessManager_.get(request);
}

void FileDownloader::fileDownloaded(QNetworkReply* pReply) {
    downloadedData_ = pReply->readAll();
    pReply->deleteLater();
    emit downloaded();
}

QByteArray FileDownloader::downloadedData() const { return downloadedData_; }
