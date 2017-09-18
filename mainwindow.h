#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QProgressBar>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QTableWidget>
#include "model.h"
#include "ltview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Model *model;
    LTView *ltView;

    void initLTView();
    void uploadDataToModel();

signals:
    void startSimulation();
    void stopSimulation();

private slots:
    void bStartHandler();
    void bStopHandler();

    void updateDataOnUI();

};

#endif // MAINWINDOW_H
