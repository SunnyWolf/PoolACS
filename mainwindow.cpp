#include "mainwindow.h"

#include "ui_mainwindow_v2.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model(new Model),
    ltView(new LTView)
{
    ui->setupUi(this);

    ui->bStop->setEnabled(false);

    /* Установка фонового изображения */
    QPixmap pmap ("background.png");
    ui->lBackground->setPixmap(pmap);
    ui->ltViewLayout->addWidget(ltView);

    connect(ui->bStart, SIGNAL(released()), this,  SLOT(bStartHandler()));
    connect(ui->bStop,  SIGNAL(released()), this,  SLOT(bStopHandler()));
    connect(this, SIGNAL(startSimulation()), model, SLOT(start()));
    connect(this, SIGNAL(stopSimulation()),  model, SLOT(stop()));
    connect(model, SIGNAL(update()), this, SLOT(updateDataOnUI()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* Обработчик нажатия кнопки Start */
void MainWindow::bStartHandler(){
    ui->bStart->setEnabled(false);
    ui->bStop->setEnabled(true);

    uploadDataToModel();

    emit startSimulation();
}
/* Обработчик нажатия кнопки Stop */
void MainWindow::bStopHandler(){
    ui->bStart->setEnabled(true);
    ui->bStop->setEnabled(false);

    emit stopSimulation();
}
/* Инициализация модели */
void MainWindow::uploadDataToModel(){
    double temp;
    QMap<QString, double> params;

    temp = ui->tableWidget->item(0,0)->text().toDouble();
    params.insert("LH", temp);
    temp = ui->tableWidget->item(1,0)->text().toDouble();
    params.insert("LL", temp);
    temp = ui->tableWidget->item(2,0)->text().toDouble();
    params.insert("Level", temp);
    temp = ui->tableWidget->item(3,0)->text().toDouble();
    params.insert("TH", temp);
    temp = ui->tableWidget->item(4,0)->text().toDouble();
    params.insert("TL", temp);
    temp = ui->tableWidget->item(5,0)->text().toDouble();
    params.insert("Tin", temp);
    temp = ui->tableWidget->item(6,0)->text().toDouble();
    params.insert("Tout", temp);
    temp = ui->tableWidget->item(7,0)->text().toDouble();
    params.insert("Temp", temp);
    temp = ui->tableWidget->item(8,0)->text().toDouble();
    params.insert("S", temp);
    temp = ui->tableWidget->item(9,0)->text().toDouble();
    params.insert("C", temp);
    temp = ui->tableWidget->item(10,0)->text().toDouble();
    params.insert("R", temp);
    temp = ui->tableWidget->item(11,0)->text().toDouble();
    params.insert("K", temp);
    temp = ui->tableWidget->item(12,0)->text().toDouble();
    params.insert("Q", temp);
    temp = ui->tableWidget->item(13,0)->text().toDouble();
    params.insert("dT", temp);
    temp = ui->tableWidget->item(14,0)->text().toDouble();
    params.insert("dTgist", temp);
    temp = ui->tableWidget->item(15,0)->text().toDouble();
    params.insert("dL", temp);
    temp = ui->tableWidget->item(16,0)->text().toDouble();
    params.insert("dLgist", temp);

    model->applySettings(params);
    ltView->applySettings(params);
}

/* Отображение данных модели на экране */
void MainWindow::updateDataOnUI(){
    double temp, level, slevel, stemp, lh;
    bool state;

    level = model->getLevel();
    temp = model->getTemp();
    slevel = model->getLevelFromSensor();
    stemp = model->getTempFromSensor();

    lh = ui->tableWidget->item(0,0)->text().toDouble();
    ui->tableWidget->item(2,0)->setText(QString::number(level));
    ui->tableWidget->item(7,0)->setText(QString::number(temp));

    ui->pbPool->setValue(level / lh * 100);

    // Установка точки на графике
    ltView->setCursor(stemp, slevel);
    // Перерисовка
    ltView->updateView();

    state = model->getU1();
    ui->cbPump1->setChecked(state);
    state = model->getU2();
    ui->cbPump2->setChecked(state);
}
