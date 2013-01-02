#ifndef QUERIES_H
#define QUERIES_H

#include <QObject>
#include <QUrl>
#include <QNetworkRequest>

class Queries : public QObject
{
     Q_OBJECT
public:
    Queries();

public:
    void userAboutInfo(QString &userInfoQuery, QString &aboutInfoQuery);
    QByteArray getCopyWebFileData(const QString &sourceName, const QString &destFolderUrl);
    QUrl constructCopyWebFileUrl(const QString &url);
    void setRawHeader(const QString &accessToken, QNetworkRequest &request);
    QByteArray getRenameWebFileData(const QString &newName);
    QUrl constructRenameWebFileUrl(const QString &sourceName);
    QByteArray getCreateFolderData(const QString &name, const QString &folderUrl);
    QUrl constructCreateFolderUrl(void);

private:
   QString urlStartPart;
};

#endif // QUERIES_H
