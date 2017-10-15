#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QTimer>
#include <QMap>
#include <qmath.h>

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);

    void applySettings(QMap<QString, double> &params);

    void setLH(double level);
    void setLL(double level);
    void setLevel(double level);
    void setTH(double t);
    void setTL(double t);
    void setTin(double t);
    void setTout(double t);
    void setTemp(double t);
    void setC(double c);
    void setS(double s);
    void setR(double r);
    void setQ(double q);
    void setK(double k);
    double getLevel();
    double getLevelFromSensor();
    double getTemp();
    double getTempFromSensor();
    bool getU1();
    bool getU2();
    void setU1(bool state);
    void setU2(bool state);
    void setManualU(bool state);


private:
    void detectZone();
    void selectU1U2();
    void calcTemp();

    /* Уровни бассейна */
    double mLH, mLL, mLevel, mdL, msL;
    /* Температура жидкости в бассейне */
    double mTH, mTL, mTemp, mdT, msT;
    /* Тепрература входящей жидкости и температура внешней среды */
    double mTin, mTout;
    /* Коэфициенты */
    double mC, mS, mQ, mK, mR;
    /* Управление */
    int u1, u2;
    int u1old, u2old;
    int zone;


    QTimer *mLifeTimer;
    QTimer *mPumpTimer;
    int mLifeTimerTimeout;
    int mPumpTimerTimeout;

    bool isManualU = false;

signals:
    void update();

public slots:
    void start();
    void stop();

private slots:
    void lifeTimerWork();
    void pumpTimerWork();

};

#endif // MODEL_H
