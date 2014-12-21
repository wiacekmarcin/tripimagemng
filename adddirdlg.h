#ifndef ADDDIRDLG_H
#define ADDDIRDLG_H

#include <QDialog>
#include <QStringList>

namespace Ui {
class AddDirDlg;
}

class AddDirDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AddDirDlg(QWidget *parent = 0, const QString & dir = QString(), const QStringList & dirList=QStringList());
    ~AddDirDlg();
signals:
    void addWorkDir(const QString &name, const QString &shortname, const QString &dirname);

private slots:
    void on_pbSelectDir_clicked();

    void on_buttonBox_accepted();

private:
    Ui::AddDirDlg *ui;
    QString mDir;
    QStringList mDirList;
};

#endif // ADDDIRDLG_H
