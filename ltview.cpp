#include "ltview.h"

LTView::LTView(QWidget *parent) : QGraphicsView(parent),
    group1(new QGraphicsItemGroup),
    group2(new QGraphicsItemGroup),
    scene(new QGraphicsScene),
    penBlack(Qt::black),
    penRed(Qt::red),
    brushRed(Qt::red, Qt::SolidPattern)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setAlignment(Qt::AlignCenter);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->setMinimumHeight(100);
    this->setMinimumWidth(100);

    this->setScene(scene);

    penRed.setWidth(1);

    scene->addItem(group1);
    scene->addItem(group2);
}

LTView::~LTView(){

}

void LTView::updateView(){

    int width = this->width();
    int height = this->height();
    scene->setSceneRect(0, 0, width, height);

    double maxH = mLH + 1;
    double maxW = mTH + 10;
    double ratioL = ((double)(height)) / maxH;
    double ratioT = ((double)(width)) / maxW;

    int topL = ratioL * (maxH - mLH);
    int botL = ratioL * (maxH - mLL);
    int topT = ratioT * (mTH);
    int botT = ratioT * (mTL);

    scene->addLine(0, botL, width, botL, penBlack);
    scene->addLine(0, topL, width, topL, penBlack);
    scene->addLine(botT, 0, botT, height, penBlack);
    scene->addLine(topT, 0, topT, height, penBlack);

    int pointS = 8;
    int pointX = ratioT * mTemp;
    int pointY = ratioL * (maxH - mLevel);
    int pointXold = ratioT * mTempOld;
    int pointYold = ratioL * (maxH - mLevelOld);

    QGraphicsEllipseItem* ellipse = scene->addEllipse(0, 0, pointS, pointS, penBlack, brushRed);
    ellipse->setPos(pointX-pointS/2, pointY-pointS/2);

    deleteItemsFromGroup(group1);
    group1->addToGroup(ellipse);

    if (pointX != pointXold || pointY != pointYold){
        QGraphicsLineItem *line = scene->addLine(pointXold, pointYold, pointX, pointY, penRed);
        group2->addToGroup(line);

        mTempOld = mTemp;
        mLevelOld = mLevel;
    }
}

void LTView::deleteItemsFromGroup(QGraphicsItemGroup *group){
    foreach (QGraphicsItem *item, scene->items(group->boundingRect())) {
        if (item->group() == group){
            delete item;
        }
    }
}

void LTView::applySettings(QMap<QString, double> &params){
    if (params.isEmpty()) return;

    mLH = params.value("LH");
    mLL = params.value("LL");
    mLevel = params.value("Level");
    mLevelOld = mLevel;
    mTH = params.value("TH");
    mTL = params.value("TL");
    mTemp = params.value("Temp");
    mTempOld = mTemp;
}

void LTView::setLH(double level){ mLH = level; }
void LTView::setLL(double level){ mLL = level; }
void LTView::setTH(double level){ mTH = level; }
void LTView::setTL(double level){ mTL = level; }
void LTView::setCursor(double t, double l){
    mTemp = t;
    mLevel = l;
}
