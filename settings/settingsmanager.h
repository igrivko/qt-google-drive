#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include "settings/accountinfo.h"
#include <QSettings>
#include <QVariant>

class SettingsManager : public QSettings
{
    Q_OBJECT
public:
    explicit SettingsManager(QObject *parent = 0);

public:
    void writeAccountInfo(AccountInfo::Data &data);
    int currentPanel(void);
    void setCurrentPanel(int panelNum);
    void setInitialLoading(bool initLoad);
    void setCurrentFolderPath(int panelNum, const QString &path);
    QString currentFolderPath(int panelNum);
    void setCurrentFolderURL(int panelNum, const QString &url);
    QString currentFolderURL(int panelNum);
    void setPathesURLs(int panelNum, QStringList pathes);
    QStringList pathesURLs(int panelNum);
    bool isWorkDirSet(void);
    QString workDir(void);
    void setWorkDir(const QString &workDrName);
    QString accessToken(void);
    QString refreshToken(void);
    bool initialLoading(void);
    void setCurrentAccount(int panelNum, const QString &name);
    QString currentAccount(int panelNum);
    bool isAnyAccount(void);

    //Move to public
    QVariant getValueFromGroup(const QString &group, const QString &key, const QVariant &defaultVal = QVariant());
    void setValueInGroup(const QString &group, const QString &key, const QVariant &val);

private:
    void setValueInPanelGroup(int panelNum, const QString &key, const QVariant &val);
    QVariant getValueFromPanelGroup(int panelNum, const QString &key, const QVariant &defaultVal = QVariant());
    bool exists(const QString &group, const QString &key);
};

#endif // SETTINGSMANAGER_H
