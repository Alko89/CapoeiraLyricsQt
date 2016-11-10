#ifndef CSONGS_H
#define CSONGS_H

#include <QAbstractListModel>
#include "csong.h"

class CSongs : public QAbstractListModel
{
    Q_OBJECT
public:
    enum DemoRoles {
        CTitleRole = Qt::UserRole + 1,
        CSubtitleRole,
        CUrlRole,
        CYTPlayerRole,
        CTextTole
    };

    explicit CSongs(QObject *parent = 0);

    enum SaveFormat {
        Json, Binary
    };

    bool loadJson(SaveFormat saveFormat);
    bool saveJson(SaveFormat saveFormat) const;

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;


    virtual int rowCount(const QModelIndex&) const { return cSongs.size(); }
    virtual QVariant data(const QModelIndex &index, int role) const;

    QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE QString getTitle(const int i);
    Q_INVOKABLE QString getSubtitle(const int i);
    Q_INVOKABLE QString getUrl(const int i);
    Q_INVOKABLE QString getYTPlayer(const int i);
    Q_INVOKABLE QString getText(const int i);

    Q_INVOKABLE int getSize();

private:
    QList<CSong> cSongs;
    //QMap<QString ,CSong> cSongs;

signals:

public slots:
};

#endif // CSONGS_H
