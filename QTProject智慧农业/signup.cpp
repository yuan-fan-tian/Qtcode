#include "signup.h"
#include "ui_signup.h"
#include "mainwindow.h"
Signup::Signup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Signup)
{
    ui->setupUi(this);
    //设置图片
        QPixmap *pix = new QPixmap(":/image/regeist.jpg");
        QSize sz = ui->label_4->size();
        ui->label_4->setPixmap(pix->scaled(sz));
}

Signup::~Signup()
{
    delete ui;
}

void Signup::on_fanhui_clicked()
{


        MainWindow *w = new MainWindow;
        w->show();
        this->close();

}

void Signup::on_zhuce_clicked()
{


        sqlite_Init();
        QString username = ui->zhuce_username->text();
        QString password = ui->zhuce_password1->text();
        QString surepass = ui->zhuce_password2->text();
        //判断密码是否一致
        if(password == surepass  && password!="")
        {
            QString sql=QString("insert into user(username,password) values('%1','%2');")
                    .arg(username).arg(password);
            //创建执行语句对象
            QSqlQuery query;
            //判断执行结果
            if(!query.exec(sql))
            {
                qDebug()<<"insert into error";
                QMessageBox::information(this,"注册认证","插入失败！");
            }
            else
            {
                qDebug()<<"insert into success";
                QMessageBox::information(this,"注册认证","插入成功！");
                MainWindow *w = new MainWindow;
                w->show();
                this->close();
            }

        }else if(password=="" || username==""||surepass==""){
            QMessageBox::information(this,"注册认证","输入不能为空");
        }
        else {
            QMessageBox::information(this,"注册认证","两次密码输入不一致");
        }

}
