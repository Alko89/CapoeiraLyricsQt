#ifndef CCRAWLER_H
#define CCRAWLER_H

#include <QNetworkAccessManager>

#include "csong.h"

class CCrawler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int pageIndex READ pageIndex WRITE setPageIndex NOTIFY pageIndexChanged)

    QString page;
    int page_i;

public:
    CCrawler();
    QMap<QString, CSong> crawlCapoeiraLyrics();
    CSong crawlSong(QString url);
    QString getMatch(QString str, QString exp);

    void fetch(QString url);

    void setPageIndex(const int index);
    int pageIndex() const;

signals:
    void pageIndexChanged();

public slots:
        void replyFinished(QNetworkReply*page);

private:
        QNetworkAccessManager *manager;
};

#endif // CCRAWLER_H
