#include "children.h"
#include "settings/settingsmanager.h"
#include "parsers/jsonparser.h"
#include "share/debug.h"

Children::Children(QObject *parent) :
    NetworkManager(parent)
{
}

void Children::fetch(const Items::Data &source)
{
    queries.setRawHeader(SettingsManager().accessToken(), request);
    getRequest(queries.construcChildrenUrl(QString("root")).toString());
}

void Children::slotReplyFinished(QNetworkReply* reply)
{
    DEBUG << replyStr;

    JSONParser jParser;
    QStringList pathValues;

    pathValues << "items";
    //DEBUG << jParser.getParams(replyStr, pathValues, QString("id"));
    //DEBUG << jParser.getParams(replyStr, pathValues, QString("selfLink"));
    //DEBUG << jParser.getParams(replyStr, pathValues, QString("childLink"));

    //updatePanelContent(false);
}

