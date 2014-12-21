#ifndef PICTURE_SIMPLE_H
#define PICTURE_SIMPLE_H

#include <QDialog>
#include <QString>
#include <QPixmap>
#include <QRect>
#include <QRectF>
#include <QColor>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsSceneMouseEvent>

namespace Ui {
class PictureSimple;
}

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphicsScene(QObject *parent = 0) { mClicked = false; mRectItem = NULL;}
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * mouseEvent);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent);
signals:
    void boxActive(QRectF);
public slots:

protected:
    QRectF getBoxSize(const QPointF & startPoint, const QPointF & endpoint);
    QRectF getBoxRatioSize(const QRectF box);
private:
    QPointF mStartPoint;
    QPointF mEndPoint;
    bool mClicked;
    QGraphicsRectItem * mRectItem;
};

QSize getImgSize(int width);

class PictureSimple : public QDialog
{
    Q_OBJECT

public:
    explicit PictureSimple(const QString fileName, QWidget *parent = 0);
    ~PictureSimple();

public slots:
    void boxActive(QRectF);
protected:
    void drawPixmap(const QRect & box);
private slots:
    void on_pbOk_clicked();

    void on_pbCancel_clicked();

    void on_pbBackground_clicked();

private:
    Ui::PictureSimple *ui;
    QPixmap mImage;
    QRect mActBox;
    QColor mColor;
    GraphicsScene mScene;
    QGraphicsPixmapItem * mImageSceneItem;
    QGraphicsRectItem * mImagerect;
    QSize mShowview;

};

#endif // PICTURE_SIMPLE_H
