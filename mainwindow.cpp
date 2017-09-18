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

    initLTView();
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
    temp = ui->tableWidget->item(0,0)->text().toDouble();
    model->setLH(temp);
    temp = ui->tableWidget->item(1,0)->text().toDouble();
    model->setLL(temp);
    temp = ui->tableWidget->item(2,0)->text().toDouble();
    model->setLevel(temp);
    temp = ui->tableWidget->item(3,0)->text().toDouble();
    model->setTH(temp);
    temp = ui->tableWidget->item(4,0)->text().toDouble();
    model->setTL(temp);
    temp = ui->tableWidget->item(5,0)->text().toDouble();
    model->setTin(temp);
    temp = ui->tableWidget->item(6,0)->text().toDouble();
    model->setTout(temp);
    temp = ui->tableWidget->item(7,0)->text().toDouble();
    model->setTemp(temp);
    temp = ui->tableWidget->item(8,0)->text().toDouble();
    model->setS(temp);
    temp = ui->tableWidget->item(9,0)->text().toDouble();
    model->setC(temp);
    temp = ui->tableWidget->item(10,0)->text().toDouble();
    model->setR(temp);
    temp = ui->tableWidget->item(11,0)->text().toDouble();
    model->setK(temp);
    temp = ui->tableWidget->item(12,0)->text().toDouble();
    model->setQ(temp);
}

/* Отображение данных модели на экране */
void MainWindow::updateDataOnUI(){
    double temp, level, lh;
    bool state;

    level = model->getLevel();
    temp = model->getTemp();

    lh = ui->tableWidget->item(0,0)->text().toDouble();
    ui->tableWidget->item(2,0)->setText(QString::number(level));
    ui->tableWidget->item(7,0)->setText(QString::number(temp));

    ui->pbPool->setValue(level / lh * 100);

    // Установка точки на графике
    ltView->setCursor(temp, level);
    // Перерисовка
    ltView->updateView();

    state = model->getU1();
    ui->cbPump1->setChecked(state);
    state = model->getU2();
    ui->cbPump2->setChecked(state);
}

/* Инициализания LTView */
void MainWindow::initLTView(){
    double temp;
    temp = ui->tableWidget->item(0,0)->text().toDouble();
    ltView->setLH(temp);
    temp = ui->tableWidget->item(1,0)->text().toDouble();
    ltView->setLL(temp);
    temp = ui->tableWidget->item(3,0)->text().toDouble();
    ltView->setTH(temp);
    temp = ui->tableWidget->item(4,0)->text().toDouble();
    ltView->setTL(temp);
}
