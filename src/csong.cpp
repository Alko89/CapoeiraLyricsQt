#include "csong.h"

CSong::CSong()
{

}

//! [0]
void CSong::read(const QJsonObject &json)
{
    cUrl = json["url"].toString();
    cTitle = json["title"].toString();
    cSubtitle = json["subtitle"].toString();
    cYTPlayer = json["ytplayer"].toString();


    //cLyrics.clear();
    QJsonObject lyricsObject = json["lyrics"].toObject();
    cText = lyricsObject["text"].toString();
    //for (int i = 0; i < lyricsArray.size(); ++i) {
        //QJsonObject lyricObject = lyricsArray[i].toObject();
        //Lyric lyric;
        //lyric.read(lyricObject);
        //cLyrics.append(lyric);
    //}
}
//! [0]

//! [1]
void CSong::write(QJsonObject &json) const
{
    /*QJsonArray lyricsArray;
    foreach (const Lyric lyric, cLyrics) {
        QJsonObject lyricObject;
        lyric.write(lyricObject);
        lyricsArray.append(lyricObject);
    }
    json["lyrics"] = lyricsArray;*/
}
//! [1]
