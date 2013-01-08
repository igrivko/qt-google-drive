#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QString>

class JSONParser
{
public:
    JSONParser();

public:   
    QString getParam(const QString &jsonStr, const QString &lVal, bool isQuotes = true);
    QStringList getParams(const QString& jsonStr, const QStringList &pathValues, const QString &lVal);

private:
    QString getToken(const QString &jsonStr, const QString &lVal, QString endDivider, bool isQuotes);


private:
    int continuePos;
};

#endif // JSONPARSER_H
