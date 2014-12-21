#include "authors.h"

Authors::Authors(QObject *parent) :
    QObject(parent)
{
    mAuthors = QVector<struct Author>();
}

void Authors::addAuthor(const QString &name, const QString &shortname, const QString &dir)
{
    struct Author a;
    a.dirname = dir;
    a.name = name;
    a.shortname = shortname;
    mAuthors.push_back(a);
}
