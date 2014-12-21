#include "authorinfo.h"
#include "ui_authorinfo.h"

AuthorInfo::AuthorInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AuthorInfo)
{
    ui->setupUi(this);
}

AuthorInfo::~AuthorInfo()
{
    delete ui;
}
