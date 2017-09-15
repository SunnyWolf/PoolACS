#include "model.h"

Model::Model(QObject *parent) :
    QObject(parent),
    mLifeTimer(new QTimer),
    mPumpTimer(new QTimer)
{
    mLifeTimerTimeout = 300;
    mLifeTimer->setInterval(mLifeTimerTimeout);
    connect(mLifeTimer, SIGNAL(timeout()), this, SLOT(lifeTimerWork()));

    mPumpTimer->setInterval(1000);
    connect(mPumpTimer, SIGNAL(timeout()), this, SLOT(pumpTimerWork()));
}

void Model::start(){
    mLifeTimer->start();
    mPumpTimer->start();
    emit pumpTimerWork();
}

void Model::stop(){
    mLifeTimer->stop();
    mPumpTimer->stop();
}

void Model::lifeTimerWork(){
    calcTemp();
    emit update();
}

void Model::pumpTimerWork(){
    detectZone();
    selectU1U2();
}

void Model::detectZone(){
    if (mTemp < mTL){
        if (mLevel < mLL){
            zone = 1;
        } else if (mLevel < mLH){
            zone = 2;
        } else {
            zone = 3;
        }
    } else if (mTemp < mTH){
        if (mLevel < mLL){
            zone = 8;
        } else if (mLevel < mLH){
            zone = 9;
        } else {
            zone = 4;
        }
    } else {
        if (mLevel < mLL){
            zone = 7;
        } else if (mLevel < mLH){
            zone = 6;
        } else {
            zone = 5;
        }
    }
}

void Model::selectU1U2(){
    switch (zone) {
    case 1:
        u1 = 1;
        u2 = 0;
        break;
    case 2:
        u1 = 1;
        u2 = 1;
        break;
    case 3:
    case 4:
    case 5:
        u1 = 0;
        u2 = 1;
        break;
    case 6:
        u1 = 0;
        u2 = 0;
        break;
    case 7:
    case 8:
        u1 = 1;
        u2 = 0;
        break;
    case 9:
    default:
        u1 = 0;
        u2 = 0;
        break;
    }
}

void Model::calcTemp(){
    double t = (double)(mLifeTimerTimeout) / 1000;
    double a = mK * mS / mC * -1.0;
    double tau = mTout + pow(2.71, a * t) * (mTemp - mTout);

    if (u1 > 0){
        mTemp = (tau * mLevel * mS + u1 * mTin * mQ * t) / (mLevel * mS + u1 * mQ * t);
    } else {
        mTemp = tau;
    }

    mLevel = mLevel + (mQ * t * (u1 - u2)) / mS;
    if (mLevel < 0){
        mLevel = 0;
    }
}

void Model::setLH(double level)   { mLH = level;     }
void Model::setLL(double level)   { mLL = level;     }
void Model::setLevel(double level){ mLevel = level;  }
void Model::setTH(double t)       { mTH = t;         }
void Model::setTL(double t)       { mTL = t;         }
void Model::setTin(double t)      { mTin = t;        }
void Model::setTout(double t)     { mTout = t;       }
void Model::setTemp(double t)     { mTemp = t;       }
void Model::setC(double c)        { mC = c;          }
void Model::setS(double s)        { mS = s;          }
void Model::setR(double r)        { mR = r;          }
void Model::setQ(double q)        { mQ = q;          }
void Model::setK(double k)        { mK = k;          }

double Model::getLevel(){ return mLevel; }
double Model::getTemp(){  return mTemp;  }
bool Model::getU1(){      return (bool)(u1); }
bool Model::getU2(){      return (bool)(u2); }
