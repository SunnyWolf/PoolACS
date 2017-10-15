#include "model.h"

Model::Model(QObject *parent) :
    QObject(parent),
    mLifeTimer(new QTimer),
    mPumpTimer(new QTimer)
{
    mLifeTimerTimeout = 3;
    mPumpTimerTimeout = 1;

    isManualU = false;

    connect(mLifeTimer, SIGNAL(timeout()), this, SLOT(lifeTimerWork()));
    connect(mPumpTimer, SIGNAL(timeout()), this, SLOT(pumpTimerWork()));
}

void Model::start(){
    mLifeTimer->setInterval(mLifeTimerTimeout);
    mPumpTimer->setInterval(mPumpTimerTimeout);
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
    if (!isManualU){
        detectZone();
        selectU1U2();
    }
}

void Model::detectZone(){
    double temp = getTempFromSensor();
    double level = getLevelFromSensor();

    if (temp < mTL){
        if (level < mLL){
            zone = 1;
        } else if (mLevel < mLH){
            zone = 2;
        } else {
            zone = 3;
        }
    } else if (temp < mTH){
        if (level < mLL){
            zone = 8;
        } else if (level < mLH){
            zone = 9;
        } else {
            zone = 4;
        }
    } else {
        if (level < mLL){
            zone = 7;
        } else if (level < mLH){
            zone = 6;
        } else {
            zone = 5;
        }
    }
}

void Model::selectU1U2(){
    switch (zone) {
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
    case 1:
    case 7:
    case 8:
        u1 = 1;
        u2 = 0;
        break;
    case 9:
        // Если вошли в зону при u1=1, u2=0 или наоборот
        if (u1 != u2){
            if (mLevel > (mLH - msL)){
                u1 = 0;
                u2 = 1;
            } else if (mLevel < (mLL + msL)){
                u1 = 1;
                u2 = 0;
            } else {
                u1 = 0;
                u2 = 0;
            }
        }
        // Алгоритм регулировки температуры
        if ((u1 & u2) && (mTemp > (mTH - msT)) ){
            u1 = 0;
            u2 = 0;
        }
        if (!(u1 & u2) && (mTemp < (mTL + msT))){
            u1 = 1;
            u2 = 1;
        }
        break;
    case 6:
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

void Model::applySettings(QMap<QString, double> &params){
    if (params.isEmpty()) return;

    mLH = params.value("LH");
    mLL = params.value("LL");
    mLevel = params.value("Level");
    mTH = params.value("TH");
    mTL = params.value("TL");
    mTin = params.value("Tin");
    mTout = params.value("Tout");
    mTemp = params.value("Temp");
    mC = params.value("C");
    mS = params.value("S");
    mR = params.value("R");
    mQ = params.value("Q");
    mK = params.value("K");
    mdT = params.value("dT", 1);
    mdL = params.value("dL", 1);
    msT = params.value("sT", 0);
    msL = params.value("sL", 0);
    mLifeTimerTimeout = params.value("tMod", mLifeTimerTimeout) * 1000;
    mPumpTimerTimeout = params.value("tReg", mPumpTimerTimeout) * 1000;
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

double Model::getLevelFromSensor(){
    return round(mLevel / mdL) * mdL;
}
double Model::getTempFromSensor(){
    return round(mTemp / mdT) * mdT;
}
double Model::getLevel(){ return mLevel;     }
double Model::getTemp(){  return mTemp;      }
bool Model::getU1(){      return (bool)(u1); }
bool Model::getU2(){      return (bool)(u2); }

void Model::setU1(bool state){ u1 = state == true ? 1 : 0; }
void Model::setU2(bool state){ u2 = state == true ? 1 : 0; }

void Model::setManualU(bool state){ isManualU = state; }
