#ifndef CSONG_H
#define CSONG_H

#include <QObject>
#include <QJsonObject>

class CSong
{
public:
    CSong();

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
    QString cTitle;
    QString cUrl;
    QString cSubtitle;
    QString cYTPlayer;
    QString cText;

private:
    //QList<Lyric> cLyrics;

signals:

public slots:
};

#endif // CSONG_H
