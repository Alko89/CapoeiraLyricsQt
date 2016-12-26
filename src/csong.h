#ifndef CSONG_H
#define CSONG_H

#include <QObject>
#include <QJsonObject>
#include <QMap>

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
    QMap<QString, QString> cLyrics;

private:

signals:

public slots:
};

#endif // CSONG_H
