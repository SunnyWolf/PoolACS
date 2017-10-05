#ifndef LTVIEW_H
#define LTVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsItemGroup>
#include <QWidget>
#include <QBrush>

class LTView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit LTView(QWidget *parent = nullptr);
    ~LTView();

    void applySettings(QMap<QString, double> &params);
    void setLH(double level);
    void setLL(double level);
    void setTH(double level);
    void setTL(double level);
    void setCursor(double t, double l);

signals:

public slots:
    void updateView();

private:
    void drawHistory();
    void deleteItemsFromGroup(QGraphicsItemGroup *group);

    double mLL, mLH, mTL, mTH;
    double mLevel, mTemp, mLevelOld, mTempOld;

    QGraphicsScene *scene;
    QGraphicsItemGroup *group1;
    QGraphicsItemGroup *group2;

    QPen penBlack;
    QPen penRed;
    QBrush brushRed;
};

#endif // LTWIEV_H
