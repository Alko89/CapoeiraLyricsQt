#include "ccrawler.h"

#include <QFile>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QByteArray>
#include <QRegularExpression>
#include <QEventLoop>

CCrawler::CCrawler()
{
    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)),
         this, SLOT(replyFinished(QNetworkReply*)));
}

QMap<QString, CSong> CCrawler::crawlCapoeiraLyrics(){
    page = "";
    fetch("http://capoeiralyrics.info");
    while(page=="");

    QMap<QString, CSong> songs;

    QRegularExpression re("songs(.+)\\.html");
    QRegularExpressionMatchIterator i = re.globalMatch(page);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        QString word = "http://capoeiralyrics.info/" + match.captured();

        CSong song = crawlSong(word);
        //songs.append(crawlSong(word));
        songs.insert(song.cTitle.toLower(), song);
    }
    return songs;
}

QString CCrawler::getMatch(QString str, QString exp){
    QRegularExpression re(exp);
    QRegularExpressionMatch match = re.match(str);
    if (match.hasMatch()) {
        return match.captured(1);
    }
    return "";
}

CSong CCrawler::crawlSong(QString url){
    page = "";
    fetch(url);
    while(page=="");

    qDebug() << url;
    QString cTitle = getMatch(page, "<h1 class='title'>(.+)</h1>");

    QString cSubtitle = getMatch(page, "<h1 class='subtitle'>(.+)</h1>");
    QString cYTPlayer = getMatch(page, "<div class='video video-container'>(.+)</div>");

    QMap<QString, QString> cLyrics;

    QRegularExpression reArticle("<article>(.+)</article>", QRegularExpression::DotMatchesEverythingOption);
    QRegularExpressionMatch matchArticle = reArticle.match(page);
    if (matchArticle.hasMatch()) {
        QString article = matchArticle.captured(1);

        int i = 0;
        QStringList alist = article.split("</article>");

        QRegularExpression reName("<a name='(.+)'></a>");
        QRegularExpressionMatchIterator iName = reName.globalMatch(page);
        while (iName.hasNext() && i < alist.length()){
            QRegularExpressionMatch matchName = iName.next();
            QString name = matchName.captured(1);

            if(name == "text")
                cLyrics.insert(name, alist[0].replace("\n", "<br />"));
            i++;
        }
    }

    CSong song;
    song.cUrl = url;
    song.cTitle = cTitle;
    song.cSubtitle = cSubtitle;
    song.cYTPlayer = cYTPlayer;
    song.cLyrics = cLyrics;
    return song;
}

void CCrawler::fetch(QString url)
{
    //manager->get(QNetworkRequest(QUrl(url)));
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
}

void CCrawler::replyFinished(QNetworkReply* reply)
{
    QByteArray data = reply->readAll();
    page = QString(data);
}
