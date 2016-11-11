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
        CTextRole,
        CTranslationsRole
    };

    explicit CSongs(QObject *parent = 0);

    bool loadJson();
    bool saveJson() const;

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;


    virtual int rowCount(const QModelIndex&) const { return cFilterSongs.size(); }
    virtual QVariant data(const QModelIndex &index, int role) const;

    QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void filter(const QString searchString);

private:
    QMap<QString, CSong> cSongs;
    QList<CSong> cFilterSongs;

signals:

public slots:
};

#endif // CSONGS_H
