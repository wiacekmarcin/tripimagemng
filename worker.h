#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include <QWidget>
#include <QMap>
#include <QPair>
#include <QLabel>
#include <QProgressBar>

namespace Ui {
class Workers;
class WorkerThread;
}

enum _errors { W_OK = 0, W_ERROR, WFS_EMPTY };

struct WorkerWigdetStruct {
    bool isRuning;
    QProgressBar * progresBar;
    float progress;
    int id;
};

class WorkerWigdet {
public:

    explicit WorkerWigdet (QWidget *parent = 0);
    ~WorkerWigdet();

public slots:
    void handleProgress(int id, int progress);
    void addProgress(const QString & name, int id);
    void setFinish(int id);

private:
    Ui::Workers *ui;
    QMap<int, struct WorkerWigdetStruct> task;
};

class WorkerThreadWidget : public QWidget {
    Q_OBJECT
public:
    explicit WorkerThreadWidget(QWidget * parent);
    ~WorkerThreadWidget();

public slots:
    void setProgress(const int value);
    void addText(const QString & info);

private:
    Ui::WorkerThread * ui;
    int mProgress;
};











class WorkerThread : public QObject /* QThread*/
{
    Q_OBJECT
public:
    explicit WorkerThread(const QString & Title);
    virtual ~WorkerThread();

    virtual int doWork() { return W_OK; }

    void setWidget(QWidget * frame);

    void run() {
        setProgress(100);
        success = doWork();
        emit resultReady(id, success);
    }

    void setId(int id_) { id = id_; }

    QString getTitle() const { return title; }

signals:
     void resultReady(const int id, const int re);
     void changeProgress(const int id, int progress);
     void change(int progress);
     void addText(const QString &info);

protected:
    void setProgress(int progress);
    void addInfo(const QString & info);

private:
     int id;
     WorkerThreadWidget * widget;
     int progress;
     int success;
     QString title;
};

struct sWorkerThread {
    WorkerThread * worker;
    bool isRun;
    QLabel * label;
    QProgressBar * progresBar;
    int result;
};


class Workers : public QWidget
{
    Q_OBJECT
public:
    explicit Workers( QWidget * frameInfo, QWidget * frameTask = 0);
    ~Workers();
    void setFrameTask(QWidget * frame);

    void addWorker(WorkerThread * worker);



public slots:


private:

    unsigned int id;
    QMap<int, sWorkerThread>  workers;
    QWidget * frameTab;
};



#endif // WORKER_H
