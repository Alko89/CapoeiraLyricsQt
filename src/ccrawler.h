#ifndef CCRAWLER_H
#define CCRAWLER_H

#include <QNetworkAccessManager>

#include "csong.h"

class CCrawler : public QObject
{
    Q_OBJECT

    QString page;

public:
    CCrawler();
    QMap<QString, CSong> crawlCapoeiraLyrics();
    CSong crawlSong(QString url);
    QString getMatch(QString str, QString exp);

    void fetch(QString url);

public slots:
        void replyFinished(QNetworkReply*page);

private:
        QNetworkAccessManager *manager;
};

#endif // CCRAWLER_H
