#include "accountinfo.h"
#include "share/commontools.h"
#include "parsers/jsonparser.h"
#include "share/debug.h"

AccountInfo::AccountInfo(const QString &uiq, const QString &aiq, const QString &at, const QString &rt) :
    userInfoQuery(uiq),
    aboutInfoQuery(aiq),    
    query(EUserInfoQuery),
    queryStr(userInfoQuery)
{
    accountData.accessToken = at;
    accountData.refreshToken = rt;

    //We need to use this signal to postpone the next call for getting "about" info.
    connect(this, SIGNAL(signalToCallSetInfo()), this, SLOT(setInfo()), Qt::QueuedConnection);
}

void AccountInfo::slotReplyFinished(QNetworkReply*)
{
    parseReply();

    replyStr.clear();

    if(query == EUserInfoQuery)
    {
        queryStr = aboutInfoQuery;
        query = EAboutInfoQuery;

        //setInfo();

        //We need to use this signal to postpone the next call for getting "about" info.
        emit signalToCallSetInfo();
    }
    else if(query == EAboutInfoQuery)
    {
        queryStr = userInfoQuery;
        query = EUserInfoQuery;

        emit signalAccountInfo(accountData);
    }
}

void AccountInfo::setInfo(void)
{
    DEBUG;

    CommonTools::setHeader(accountData.accessToken, request);
    request.setRawHeader("Content-Type", "application/json");

    getRequest(queryStr);
}

void AccountInfo::parseReply(void)
{
    DEBUG << "<===============================================================================================================";
    DEBUG << "replyStr" << replyStr;
    DEBUG << "===============================================================================================================>";

    JSONParser jParser;

    if(query == EUserInfoQuery)
    {
        accountData.name = jParser.getPlainParam(replyStr, QString("name"));
        accountData.email = jParser.getPlainParam(replyStr, QString("email"));
    }
    else if(query == EAboutInfoQuery)
    {
        accountData.domainSharingPolicy = jParser.getPlainParam(replyStr, QString("domainSharingPolicy"));
        accountData.permissionId = jParser.getPlainParam(replyStr, QString("permissionId"));
        accountData.quotaBytesTotal = jParser.getPlainParam(replyStr, QString("quotaBytesTotal")).toLongLong();
        accountData.quotaBytesUsed = jParser.getPlainParam(replyStr, QString("quotaBytesUsed")).toLongLong();
        accountData.quotaBytesUsedInTrash = jParser.getPlainParam(replyStr, QString("quotaBytesUsedInTrash")).toLongLong();
    }
}

AccountInfo::Data AccountInfo::getData(void) const
{
    return accountData;
}


