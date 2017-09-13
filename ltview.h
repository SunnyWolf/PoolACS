#ifndef LTVIEW_H
#define LTVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QWidget>
#include <QBrush>

class LTView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit LTView(QWidget *parent = nullptr);
    ~LTView();

    void setLH(double level);
    void setLL(double level);
    void setTH(double level);
    void setTL(double level);
    void setCursor(double t, double l);

signals:

public slots:
    void updateView();

private:
    double mLL, mLH, mTL, mTH, mLevel, mTemp;

    QGraphicsScene *scene;
    QPen penBlack;
    QPen penRed;
    QBrush brushRed;
};

#endif // LTWIEV_H
