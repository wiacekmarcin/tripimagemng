#include "worker.h"

#include "ui_workers.h"
#include "ui_workerthread.h"

#include <QTextLayout>
#include <QtWidgets/QVBoxLayout>

WorkerWigdet::WorkerWigdet(QWidget *parent):
    QWidget(parent), ui(new Ui::Workers())
{
    ui->setupUi(this);
    task = QMap<int, struct WorkerWigdetStruct> ();
}

void WorkerWigdet::handleProgress(int id, int progress)
{
    if (task.contains(id)) {
        task[id].progresBar->setValue(progress);
        task[id].progress = progress;
    }
}

void WorkerWigdet::addProgress(const QString &name, int id)
{
    if (!task.contains(id)) {
        task[id] = WorkerWigdetStruct();
        task[id].progresBar = new QProgressBar(this);
        task[id].progresBar->setMinimum(0);
        task[id].progresBar->setMaximum(100);
        int row = ui->gridLayout->rowCount();
        QLabel * l = new QLabel(name, this);
        l->setObjectName(QString("%1%2").arg(name).arg(row));
        ui->gridLayout->addWidget(l, row, 0);
        ui->gridLayout->addWidget(task[id].progresBar, row, 1);
    }
    task[id].isRuning = true;
    task[id].progress = 0;
}

void WorkerWigdet::setFinish(int id)
{
    if (task.contains(id)) {
        task[id].isRuning = false;
        task[id].progresBar->setValue(100);
        task[id].progress = 100;
    }
}






















WorkerThreadWidget::WorkerThreadWidget(QWidget *parent) :
    /*QWidget(parent),*/ ui(new Ui::WorkerThread), mProgress(0)
{
    Qt::HANDLE b = QThread::currentThreadId();
    unsigned int * c;
    c = (unsigned int*)b;
    qDebug(QString("%1").arg(*c).toStdString().c_str());

    ui->setupUi(this);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);
    parent->layout()->addWidget(this);
}

WorkerThreadWidget::~WorkerThreadWidget()
{
    delete ui;
}

void WorkerThreadWidget::setLabel(const QString &label)
{
    ui->lTitle->setText(label);
}

void WorkerThreadWidget::addText(const QString &info)
{
    ui->plainTextEdit->appendPlainText(info);
}

void WorkerThreadWidget::setProgress(const int value)
{
    ui->progressBar->setValue(value);
}

/** WorkerThread *********************************************/
WorkerThread::WorkerThread(const QString &Title) :
    //QThread(this),
    id(0),
    widget(NULL),
    progress(0),
    success(0),
    title(Title)
{

}

WorkerThread::~WorkerThread()
{
    if (widget)
        delete widget;
}

void WorkerThread::setWidget(QWidget *frame)
{
    if (frame) {
        widget = new WorkerThreadWidget(frame);
        connect(this, SIGNAL(change(int)), widget, SLOT(setProgress(int)));
        connect(this, SIGNAL(addText(QString)), widget, SLOT(addText(QString)));
    }
}

void WorkerThread::setProgress(int progress)
{
    if (this->progress != progress) {
        this->progress = progress;
        emit change(progress);
        emit changeProgress(id, progress);
    }
}

void WorkerThread::addInfo(const QString &info)
{
    emit addText(info);
}

/*****************************/

Workers::Workers(QWidget *frameInfo, QWidget *frameTask) :
    QWidget(frameInfo), ui(new Ui::Workers), frameTab(frameTask), id(1)
{
    ui->setupUi(this);
    frameInfo->layout()->addWidget(this);

}

Workers::~Workers() {
    delete ui;
    for (QMap<int, sWorkerThread> ::const_iterator it = workers.begin(); it != workers.end(); ++it) {
        //if (it.value().worker->isRunning()) {
        //    it.value().worker->terminate();
        //}
        delete it.value().worker;
    }
}

void Workers::setFrameTask(QWidget *frame)
{
    frameTab = frame;
}

void Workers::addWorker(WorkerThread *worker)
{
    worker->setParent(this);
    worker->setId(id);
    worker->setWidget(frameTab);
    connect(worker, SIGNAL(resultReady(int, int)), this, SLOT(handleResults(int, int)));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(worker, SIGNAL(changeProgress(int,int)), this, SLOT(handleProgres(int,int)));


    sWorkerThread sWorker;
    sWorker.worker = worker;
    sWorker.isRun = true;
    sWorker.label = new QLabel(worker->getTitle(), this);
    sWorker.progresBar = new QProgressBar(this);
    sWorker.progresBar->setMinimum(0);
    sWorker.progresBar->setMaximum(100);
    sWorker.progresBar->setValue(0);

    ui->gridLayout->addWidget(sWorker.label);
    ui->gridLayout->addWidget(sWorker.progresBar);

    workers[id] = sWorker;

    ++id;
    //worker->start();
}

void Workers::handleResults(int id, int result) {
    workers[id].isRun = false;
    workers[id].result = result;
}

void Workers::handleProgres(int id, int progress)
{
    workers[id].progresBar->setValue(progress);
}











