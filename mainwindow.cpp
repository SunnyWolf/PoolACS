#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model(new Model),
    ltView(new LTView)
{
    ui->setupUi(this);

    ui->bStop->setEnabled(false);

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

void MainWindow::bStartHandler(){
    ui->bStart->setEnabled(false);
    ui->bStop->setEnabled(true);

    uploadDataToModel();

    emit startSimulation();
}
void MainWindow::bStopHandler(){
    ui->bStart->setEnabled(true);
    ui->bStop->setEnabled(false);

    emit stopSimulation();
}

void MainWindow::uploadDataToModel(){
    double temp;
    temp = ui->teLH->text().toDouble();
    model->setLH(temp);
    ltView->setLH(temp);
    temp = ui->teLL->text().toDouble();
    model->setLL(temp);
    ltView->setLL(temp);
    temp = ui->teLevel->text().toDouble();
    model->setLevel(temp);
    temp = ui->teTH->text().toDouble();
    model->setTH(temp);
    ltView->setTH(temp);
    temp = ui->teTL->text().toDouble();
    model->setTL(temp);
    ltView->setTL(temp);
    temp = ui->teTemp->text().toDouble();
    model->setTemp(temp);
    temp = ui->teTin->text().toDouble();
    model->setTin(temp);
    temp = ui->teTout->text().toDouble();
    model->setTout(temp);
    temp = ui->teTout->text().toDouble();
    model->setTH(temp);
    temp = ui->teC->text().toDouble();
    model->setC(temp);
    temp = ui->teS->text().toDouble();
    model->setS(temp);
    temp = ui->teQ->text().toDouble();
    model->setQ(temp);
    temp = ui->teK->text().toDouble();
    model->setK(temp);

    ltView->updateView();
}

void MainWindow::updateDataOnUI(){
    double temp, level, lh;
    bool state;

    level = model->getLevel();
    lh = ui->teLH->text().toDouble();
    ui->teLevel->setText(QString::number(level));
    ui->pbPool->setValue(level / lh * 100);

    temp = model->getTemp();
    ui->teTemp->setText(QString::number(temp));

    ltView->setCursor(temp, level);
    ltView->updateView();

    state = model->getU1();
    ui->cbPump1->setChecked(state);
    state = model->getU2();
    ui->cbPump2->setChecked(state);
}

void MainWindow::initLTView(){
    double temp;
}