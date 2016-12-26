#include "csongs.h"
#include "ccrawler.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

CSongs::CSongs(QObject *parent) : QAbstractListModel(parent)
{
    CCrawler *cr = new CCrawler();
    cSongs = cr->crawlCapoeiraLyrics();

    CSongs::loadJson();
    CSongs::filter("");
}

bool CSongs::loadJson()
{
    QFile loadFile(QStringLiteral("/opt/sdk/componentgallery/usr/capoeiralyrics.json"));

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    read(loadDoc.object());

    return true;
}

bool CSongs::saveJson() const
{
    QFile saveFile(QStringLiteral("capoeiralyrics.json"));

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonObject gameObject;
    write(gameObject);
    QJsonDocument saveDoc(gameObject);
    saveFile.write(saveDoc.toJson());

    return true;
}

void CSongs::read(const QJsonObject &json)
{
    QJsonArray songsArray = json["songs"].toArray();
    for (int i = 0; i < songsArray.size(); ++i) {
        QJsonObject songObject = songsArray[i].toObject();

        CSong song;
        song.read(songObject);
        cSongs.insert(song.cTitle.toLower(), song);
    }
}

void CSongs::write(QJsonObject &json) const
{
    QJsonArray songsArray;
    foreach (const CSong song, cSongs.values()) {
        QJsonObject songObject;
        song.write(songObject);
        songsArray.append(songObject);
    }

    json["songs"] = songsArray;
}


QHash<int, QByteArray> CSongs::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[CTitleRole] = "title";
    roles[CSubtitleRole] = "subtitle";
    roles[CUrlRole] = "url";
    roles[CYTPlayerRole] = "ytplayer";
    roles[CTextRole] = "text";
    roles[CTranslationsRole] = "translations";

    return roles;
}

QVariant CSongs::data(const QModelIndex &index, int role) const {
    if(!index.isValid()) {
        return QVariant();
    }
    if(role == CTitleRole) {
        //return QVariant(cSongs[index.row()].cTitle);
        return QVariant(cFilterSongs[index.row()].cTitle);
    }
    if(role == CSubtitleRole) {
        return QVariant(cFilterSongs[index.row()].cSubtitle);
    }
    if(role == CUrlRole) {
        return QVariant(cFilterSongs[index.row()].cUrl);
    }
    if(role == CYTPlayerRole) {
        return QVariant(cFilterSongs[index.row()].cYTPlayer);
    }
    if(role == CTextRole) {
        QString text = "";

        if(cFilterSongs[index.row()].cLyrics.contains("text")){
            text = cFilterSongs[index.row()].cLyrics.value("text");
        }

        return text;
    }
    if(role == CTranslationsRole) {
        QString translations = "";

        if(cFilterSongs[index.row()].cLyrics.contains("en")){
            translations = QString("<br/>English<br/>%1").arg(
                        cFilterSongs[index.row()].cLyrics.value("en"));
        }
        if(cFilterSongs[index.row()].cLyrics.contains("ru")){
            translations = QString("%1<br/><br/>Русский<br/>%2").arg(
                        translations, cFilterSongs[index.row()].cLyrics.value("ru"));
        }

        return QVariant(translations);
    }
    return QVariant();
}

void CSongs::filter(const QString searchString) {
    if (searchString == "")
        cFilterSongs = cSongs.values();
    else {
        cFilterSongs.size();
        cFilterSongs.clear();
        cFilterSongs.size();

        QMap<QString, CSong>::iterator i;
        for (i = cSongs.begin(); i != cSongs.end(); ++i)
            if (i.key().contains(searchString))
                cFilterSongs.append(i.value());
    }
}
