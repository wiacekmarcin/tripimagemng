#ifndef AUTHORS_H
#define AUTHORS_H

#include <QObject>
#include <QString>
#include <QVector>

struct Author {
    QString name;
    QString shortname;
    QString dirname;
};


class Authors : public QObject
{
    Q_OBJECT
public:
    explicit Authors(QObject *parent = 0);
    void addAuthor(const QString &name, const QString &shortname, const QString &dir);
    void delAuthor(const QString &dir);

signals:

public slots:



private:
    QVector<struct Author> mAuthors;

};

#endif // AUTHORS_H
