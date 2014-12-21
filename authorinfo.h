#ifndef AUTHORINFO_H
#define AUTHORINFO_H

#include <QWidget>

namespace Ui {
class AuthorInfo;
}

class AuthorInfo : public QWidget
{
    Q_OBJECT

public:
    explicit AuthorInfo(QWidget *parent = 0);
    ~AuthorInfo();

private:
    Ui::AuthorInfo *ui;
};

#endif // AUTHORINFO_H
