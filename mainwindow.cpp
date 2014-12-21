#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adddirdlg.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Qt::HANDLE b = QThread::currentThreadId();
    unsigned int * c;
    c = (unsigned int*)b;
    qDebug(QString("%1").arg(*c).toStdString().c_str());

    ui->setupUi(this);
    ui->widget->setFrameTask(ui->tabTask);


    mDatabase = QSqlDatabase::addDatabase("QSQLITE");
    mMapperDel = new QSignalMapper(this);
    mLastAddedDir = QString();
    mChoosedDir = QStringList();
    QMap<QString, QAction*> ();
    connect(mMapperDel, SIGNAL(mapped(QString)), this, SLOT(delWorkDir(QString)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addWorkDir(const QString &name, const QString &shortname, const QString &dirname)
{
    QString d = QString("%1(%2) %3").arg(name).arg(shortname).arg(dirname);
    QAction* pAction = new QAction(dirname, this);
    pAction->setText(d);
    ui->menuUsu->addAction(pAction);
    mActionMap[dirname] = pAction;

    mLastAddedDir = dirname;
    mMapperDel->setMapping(pAction, dirname);
    mChoosedDir.append(dirname);
    connect(pAction, SIGNAL(triggered()), mMapperDel, SLOT(map()));

    mWorkers->addWorker(new WorkerThread(QString(name)));
}

void MainWindow::delWorkDir(QString dirname)
{
    qDebug("delWorkDir");
    mMapperDel->removeMappings(mActionMap[dirname]);
    ui->menuUsu->removeAction(mActionMap[dirname]);
    mActionMap.remove(dirname);
    int idx = 0;
    for (QStringList::Iterator it = mChoosedDir.begin(); it != mChoosedDir.end(); ++it) {
        if (*it == dirname) {
            mChoosedDir.removeAt(idx);
            break;
        }
        ++idx;
    }

}

void MainWindow::newSession()
{
    QString fileName;

    mDatabase.setDatabaseName(fileName);
    mDatabase.open();


    //TWORZENIE TABEL
}

void MainWindow::saveSession()
{
    mDatabase.commit();
}

void MainWindow::openSession()
{
    QString fileName;

    mDatabase.setDatabaseName(fileName);
    mDatabase.open();
}

void MainWindow::quitApp()
{
    saveSession();
}

void MainWindow::on_actionDodaj_triggered()
{
    AddDirDlg * dlg = new AddDirDlg(this, mLastAddedDir, mChoosedDir);
    connect(dlg, SIGNAL(addWorkDir(QString,QString,QString)), this, SLOT(addWorkDir(QString,QString,QString)));
    dlg->exec();
    delete dlg;
}
