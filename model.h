#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QTimer>
#include <qmath.h>

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);

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
    double getTemp();
    bool getU1();
    bool getU2();


private:
    void detectZone();
    void selectU1U2();
    void calcTemp();

    /* Уровни бассейна */
    double mLH, mLL;
    double mLevel;
    /* Температура жидкости в бассейне */
    double mTH, mTL;
    double mTemp;
    /* Тепрература входящей жидкости и температура внешней среды */
    double mTin, mTout;
    /* Коэфициенты */
    double mC, mS, mQ, mK, mR;
    /* Управление */
    int u1, u2;
    int zone;


    QTimer *mLifeTimer;
    QTimer *mPumpTimer;
    int mLifeTimerTimeout;

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
