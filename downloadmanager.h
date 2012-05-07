#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSettings>
#include "AppRegData.h"
#include <QDesktopServices>

class DownloadFileManager : public QObject
{
    Q_OBJECT
public:
    explicit DownloadFileManager(QObject *parent = 0);
    ~DownloadFileManager();

public:
    void startDownload(QUrl url);

public slots:
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void downloadFinished();
    void downloadReadyRead();

private:
    void setHeader(QNetworkRequest& request);

private:
    QNetworkAccessManager networkManager;
    QNetworkReply *reply;
    QNetworkRequest request;
    QString replyString;
    QString accessToken;

};

#endif // DOWNLOADMANAGER_H
