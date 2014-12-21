#include "picture_simple.h"
#include "ui_picture_simple.h"
#include <QFile>
#include <QPainter>
#include <QPen>

QSize getImgSize(int width) {
    int height = (int)(1080.0/1920.0*width);
    return QSize(width, height);
}


PictureSimple::PictureSimple(const QString fileName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PictureSimple),
    mShowview(getImgSize(800))
{
    setMinimumSize(2*mShowview.width() + 50, mShowview.height() + 30);
    ui->setupUi(this);
    mColor = QColor(Qt::white);

    mScene.setSceneRect(QRect(0, 0, mShowview.width(), mShowview.height()) );
    ui->graphicsView->setScene(&mScene);

    if (!QFile(fileName).exists()) {
        ui->label->setText(trUtf8("Plik nie istnieje"));
        ui->graphicsView->setVisible(false);
    } else {
        mImage = QPixmap(fileName);
        drawPixmap(QRect(-1,0,mImage.width()+20,mImage.height()));
        QPixmap tmp = mImage.scaled(mShowview, Qt::KeepAspectRatio);
        mImageSceneItem = mScene.addPixmap(tmp);
        mImageSceneItem->show();
        mImagerect = new QGraphicsRectItem(0,0,mShowview.width(),mShowview.height());
        mImagerect->setPen(QPen(QColor(Qt::red)));
        mImagerect->show();
        mScene.addItem(mImagerect);
        connect(&mScene, SIGNAL(boxActive(QRectF)), this, SLOT(boxActive(QRectF)));
    }

    ui->graphicsView->show();
}

PictureSimple::~PictureSimple()
{
    delete ui;
}

void PictureSimple::boxActive(QRectF box)
{
    qDebug(QString("1. [%1,%2 - %3,%4]").arg(box.x()).arg(box.y()).arg(box.x()+box.width()).arg(box.y()+box.height()).toAscii());
    qDebug(QString("2. (%1,%2) = %3").arg(box.width()).arg(box.height()).arg(box.width()/box.height()).toAscii());
    double sx = mImage.width()/mShowview.width();
    double sy = mImage.height()/mShowview.height();
    QRectF bbox = QRect(sx*box.x(), sy*box.y(),sx*box.width(),sy*box.height());
    qDebug(QString("3. (%1,%2) = %3").arg(bbox.width()).arg(bbox.height()).arg(bbox.width()/bbox.height()).toAscii());
    drawPixmap(bbox.toRect());
}

void PictureSimple::drawPixmap(const QRect &box)
{
    mActBox = box;
    QPixmap tmp = mImage.copy(box);
    qDebug(QString("[%1,%2 - %3,%4]").arg(box.x()).arg(box.y()).arg(box.width()).arg(box.height()).toAscii());
    tmp = tmp.scaled(mShowview, Qt::KeepAspectRatio);
    qDebug(QString("[%1,%2]").arg(tmp.width()).arg(tmp.height()).toAscii());
    QPixmap view = QPixmap(mShowview);
    view.fill(mColor);
    QPainter p(&view);
    p.drawPixmap(0,0,tmp.width(), tmp.height(), tmp);
    ui->label->setPixmap(view);
}

void PictureSimple::on_pbOk_clicked()
{

}

void PictureSimple::on_pbCancel_clicked()
{

}

void PictureSimple::on_pbBackground_clicked()
{
    if (mColor == QColor(Qt::white))
        mColor = QColor(Qt::black);
    else
        mColor = QColor(Qt::white);

    drawPixmap(mActBox);
}

void GraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    if (mClicked) {
        QRectF box = getBoxRatioSize(getBoxSize(mStartPoint, mouseEvent->scenePos()));
        mStartPoint = box.topLeft();
        mEndPoint = box.bottomRight();
        qDebug(QString("[%1,%2 - %3,%4]").arg(box.x()).arg(box.y()).arg(box.width()).arg(box.height()).toAscii());
        mRectItem->setRect(box);
    }
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    mStartPoint = mouseEvent->scenePos();
    mEndPoint = mStartPoint;
    mClicked = true;
    if (mRectItem != NULL) {
        this->removeItem(mRectItem);
        delete mRectItem;
    }
    mRectItem = new QGraphicsRectItem(mStartPoint.x(), mStartPoint.y(), 10, 10);
    mRectItem->setPen(QColor(Qt::red));
    this->addItem(mRectItem);
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    mEndPoint = mouseEvent->scenePos();
    mClicked = false;
    emit boxActive(QRectF(mStartPoint,mEndPoint));

    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

QRectF GraphicsScene::getBoxSize(const QPointF &startpoint, const QPointF &endpoint)
{
    float x1,y1,x2,y2;
    if (startpoint.x() < endpoint.x()) {
        x1 = startpoint.x();
        x2 = endpoint.x();
    } else {
        x2 = startpoint.x();
        x1 = endpoint.x();
    }
    if (startpoint.x() < endpoint.x()) {
        y1 = startpoint.y();
        y2 = endpoint.y();
    } else {
        y2 = startpoint.y();
        y1 = endpoint.y();
    }

    //qDebug(QString("Box: %1 %2 %3 %4").arg(x1).arg(y1).arg(x2).arg(y2).toAscii());
    return QRectF(QPointF(x1,y1),QPointF(x2,y2));
}

QRectF GraphicsScene::getBoxRatioSize(const QRectF box)
{
    QPointF startP = box.topLeft();
    QPointF endP = box.bottomRight();
    double width = endP.x()-startP.x();
    double height = endP.y()-startP.y();

    int iw = (int)((width) / 1.92 + 0.5);
    int ih = (int)(height / 1.08 + 0.5);
    int maxwh = iw > ih ? iw : ih;

    float cwitdh = 1.92*maxwh;
    float cheight = 1.08*maxwh;
    QRectF bbox = box;
    bbox.setWidth(cwitdh);
    bbox.setHeight(cheight);
    qDebug(QString("Ratio: %1 %2 %3 %4 => %5 %6").arg(bbox.x()).arg(bbox.y()).arg(bbox.x()+bbox.width()).arg(bbox.y()+bbox.height()).arg(1.92/1.08).arg(bbox.width()/bbox.height()).toAscii());
    return bbox;
}
