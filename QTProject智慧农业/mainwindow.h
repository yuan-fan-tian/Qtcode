#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <QMainWindow>
#include<QTimer>
#include <QTimer>
#include <QDateTime>
#include <QSqlDatabase> //数据驱动
#include <QSqlQuery> //数据库执行语句
#include <QMessageBox>//消息盒子
#include <QDebug>
void sqlite_Init();
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
    void time_update(void);

    
private:
    Ui::MainWindow *ui;
    QTimer *readTimer;

private slots:
    void readData();
    void on_pushButton_clicked();
    void on_BTN_temp_clicked();
    void on_BTN_hum_clicked();
    void on_BTN_hun_back_clicked();
    void on_BTN_temp_back_clicked();
    void on_pushButton_2_clicked();
    void on_signup_clicked();
};


#endif // MAINWINDOW_H




