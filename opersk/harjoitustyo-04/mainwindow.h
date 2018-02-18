#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_actionLopeta_triggered();
    void on_actionAlkutila_triggered();
    void laske_bmi();
    void sp_paivita();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
