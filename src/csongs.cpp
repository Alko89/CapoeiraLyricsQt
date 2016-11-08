#include "csongs.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

CSongs::CSongs(QObject *parent) : QAbstractListModel(parent)
{
    CSongs::loadJson(CSongs::Json);
}

//! [3]
bool CSongs::loadJson(CSongs::SaveFormat saveFormat)
{
    QFile loadFile(saveFormat == Json
        ? QStringLiteral("/opt/sdk/componentgallery/usr/capoeiralyrics.json")
        : QStringLiteral("/opt/sdk/componentgallery/usr/capoeiralyrics.dat"));

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(saveFormat == Json
        ? QJsonDocument::fromJson(saveData)
        : QJsonDocument::fromBinaryData(saveData));

    read(loadDoc.object());

    return true;
}
//! [3]

//! [4]
bool CSongs::saveJson(CSongs::SaveFormat saveFormat) const
{
    QFile saveFile(saveFormat == Json
        ? QStringLiteral("save.json")
        : QStringLiteral("save.dat"));

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonObject gameObject;
    write(gameObject);
    QJsonDocument saveDoc(gameObject);
    saveFile.write(saveFormat == Json
        ? saveDoc.toJson()
        : saveDoc.toBinaryData());

    return true;
}
//! [4]

//! [1]
void CSongs::read(const QJsonObject &json)
{
    QJsonArray songsArray = json["songs"].toArray();
    for (int i = 0; i < songsArray.size(); ++i) {
        QJsonObject songObject = songsArray[i].toObject();

        CSong song;
        song.read(songObject);
        cSongs.append(song);
    }
}
//! [1]

//! [2]
void CSongs::write(QJsonObject &json) const
{
    /*QJsonObject playerObject;
    //mPlayer.write(playerObject);
    json["player"] = playerObject;

    QJsonArray levelArray;
    /*foreach (const Level level, mLevels) {
        QJsonObject levelObject;
        level.write(levelObject);
        levelArray.append(levelObject);
    }*/
    //json["levels"] = levelArray;
}
//! [2]


QHash<int, QByteArray> CSongs::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    return roles;
}

QVariant CSongs::data(const QModelIndex &index, int role) const {
    if(!index.isValid()) {
        return QVariant();
    }
    if(role == NameRole) {
        return QVariant(cSongs[index.row()].cTitle);
    }
    return QVariant();
}

QString CSongs::getTitle(const int i) {
    if(i < 0 || i >= cSongs.size()) {
        return "";
    }
    CSong value = cSongs[i];
    return value.cTitle;
}

QString CSongs::getSubtitle(const int i) {
    if(i < 0 || i >= cSongs.size()) {
        return "";
    }
    CSong value = cSongs[i];
    return value.cSubtitle;
}

QString CSongs::getUrl(const int i) {
    if(i < 0 || i >= cSongs.size()) {
        return "";
    }
    CSong value = cSongs[i];
    return value.cUrl;
}

QString CSongs::getYTPlayer(const int i) {
    if(i < 0 || i >= cSongs.size()) {
        return "";
    }
    CSong value = cSongs[i];
    return value.cYTPlayer;
}

QString CSongs::getText(const int i) {
    if(i < 0 || i >= cSongs.size()) {
        return "";
    }
    CSong value = cSongs[i];
    return value.cText;
}

int CSongs::getSize() {
    return cSongs.size();
}
