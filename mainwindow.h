#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QString>
#include <QStringList>
#include <QSignalMapper>
#include <QMap>

#include "worker.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void addWorkDir(const QString &name, const QString & shortname, const QString & dirname);
    void delWorkDir(QString dirname);

private slots:
    void newSession();
    void saveSession();
    void openSession();
    void quitApp();



    void on_actionDodaj_triggered();

private:
    Ui::MainWindow *ui;
    QSqlDatabase mDatabase;
    QSignalMapper *mMapperDel;
    QString mLastAddedDir;
    QStringList mChoosedDir;
    QMap<QString, QAction*> mActionMap;

    Workers * mWorkers;
};

#endif // MAINWINDOW_H
