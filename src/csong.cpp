#include "csong.h"

CSong::CSong()
{

}

void CSong::read(const QJsonObject &json)
{
    cUrl = json["url"].toString();
    cTitle = json["title"].toString();
    cSubtitle = json["subtitle"].toString();
    cYTPlayer = json["ytplayer"].toString();

    QJsonObject lyricsObject = json["lyrics"].toObject();

    QJsonObject::iterator i;
    for (i = lyricsObject.begin(); i != lyricsObject.end(); ++i)
        cLyrics.insert(i.key(), i.value().toString());
}

void CSong::write(QJsonObject &json) const
{
    json["url"] = cUrl;
    json["title"] = cTitle;
    json["subtitle"] = cSubtitle;
    json["ytplayer"] = cYTPlayer;

    QJsonObject lyricsObject;
    QMapIterator<QString, QString> i(cLyrics);
    while (i.hasNext()) {
        i.next();
        lyricsObject[i.key()] = i.value();
    }

    json["lyrics"] = lyricsObject;
}
