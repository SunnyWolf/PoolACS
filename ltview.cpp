#include "ltview.h"

LTView::LTView(QWidget *parent) :
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
}

LTView::~LTView(){

}

void LTView::updateView(){
    scene->clear();

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
    int pointX = ratioT * mTemp - pointS / 2;
    int pointY = ratioL * (maxH - mLevel) - pointS / 2;

    QGraphicsEllipseItem* ellipse = scene->addEllipse(pointS, pointS, pointS, pointS, penBlack, brushRed);
    ellipse->setPos(pointX-pointS, pointY-pointS);
}

void LTView::setLH(double level){ mLH = level; }
void LTView::setLL(double level){ mLL = level; }
void LTView::setTH(double level){ mTH = level; }
void LTView::setTL(double level){ mTL = level; }
void LTView::setCursor(double t, double l){
    mTemp = t;
    mLevel = l;
}
