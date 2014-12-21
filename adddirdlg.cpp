#include "adddirdlg.h"
#include "ui_adddirdlg.h"

#include <QFileDialog>
#include <QDir>
#include <QMessageBox>

AddDirDlg::AddDirDlg(QWidget *parent, const QString &dir, const QStringList &dirList) :
    QDialog(parent),
    ui(new Ui::AddDirDlg),
    mDir(dir),
    mDirList(dirList)
{
    ui->setupUi(this);
}

AddDirDlg::~AddDirDlg()
{
    delete ui;
}

void AddDirDlg::on_pbSelectDir_clicked()
{
    QString dirname = QFileDialog::getExistingDirectory(
               this,
            tr("Select a Directory"),
            mDir.isEmpty() ? QDir::currentPath() : mDir);
    if (dirname.isEmpty())
        return;

    if (mDirList.contains(dirname)) {
        QMessageBox::warning(this, "Wybrany katalog został już dodany", "Wybierz inny katalog i spróbuj raz jeszcze.");
        return;
    }

    ui->dirname->setText(dirname);
}

void AddDirDlg::on_buttonBox_accepted()
{
    if (ui->name->text().isEmpty() || ui->shortname->text().isEmpty() || ui->dirname->text().isEmpty()) {
        return;
    }


    emit addWorkDir(ui->name->text(), ui->shortname->text(), ui->dirname->text());
}
