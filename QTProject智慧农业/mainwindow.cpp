#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signup.h"
#include "QMessageBox"
#include <QTimer>
#include <QDateTime>
#include <QGraphicsDropShadowEffect>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    //tupian
    QPixmap *pix = new QPixmap(":/image/background.jpg");
        QSize sz = ui->label_image->size();
        ui->label_image->setPixmap(pix->scaled(sz));
        //xiaoguo
            QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
            shadow->setOffset(-3, 0);
            shadow->setColor(QColor("#888888"));
            shadow->setBlurRadius(30);
            ui->label_image->setGraphicsEffect(shadow);
    //显示当前日期时间
        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), SLOT(time_update()));
        timer->start(5000); //1s执行一次,定时器
    readData();
    readTimer = new QTimer(this); //建立一个定时器

    /*开启定时器，并且每5000ms后询问一次串口。定时的时间一到，马上产生timeout（）信号，继续执行自定义槽函数readData() */

    readTimer->start(5000);

    connect(readTimer,SIGNAL(timeout()),this,SLOT(readData()));//定时读取串口数
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::time_update() //显示系统时间的功能
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd");
    ui->LE_ti->setText(str);
    ui->LE_ti_2->setText(str);
}


void MainWindow::readData() //读取串口数据并显示出来

{

/*C语言文件读写*/

int fd,n;
int y,m,d;

   char buf[100];

   if((fd=open("/home/my/yuanjianxin/day02/data.txt",O_RDONLY))<0)

       printf("open failure!\n");

   if(n=read(fd,buf,sizeof(buf))>0)

       printf("%s\n",buf);

   else if(n==-1)

       printf("read failure!\n");

   if(::close(fd)==-1)

       printf("close failure!\n");

/*使用QString对读取到的数据字符串进行处理，显示*/

   QString str = QString((const char*)buf);//将char转为QString,文件模拟串口发送数据

   QString temp=str.section("/",0,0); //temp:26/Hum:21/time:0000000000, 按照“/”切分，取位置编号开始为0到结束为0的字符串

   temp = temp.section(":",1,1); //存储温度数据

   QString hum =str.section("/",1,1);

   hum = hum.section(":",1,1);//存储湿度度数据
  // int minute,hour;
 //  qint8 time=str.section("/",2,2);
  // time=time.section(":",1,1);
  // minute=time%3600/60;
  // hour=(time%86400/3600+8)%24;
   QTime current_time = QTime::currentTime();

   int hour = current_time.hour();        //当前的小时
   int minute = current_time.minute();    //当前的分
   int miao = current_time.second();    //当前的秒
   //int msec = current_time.msec();        //当前的毫秒
   //QString h=int.toString("");

   ui->LE_Temp->setText(temp);
   ui->LE_Hum->setText(hum);
   // ui->LE_Minute->setText(minute);
   // ui->LE_Hour->setText(hour);
    //ui->LE_Miao->setText(miao);
   if(temp.toInt()>30){
       ui->label_temp_alter->setStyleSheet("border-image: url(:/image/temp_hot.jpg);");
   }else if(temp.toInt()<20){
       ui->label_temp_alter->setStyleSheet("border-image: url(:/image/temp_cool.jpg);");
   }else{
       ui->label_temp_alter->setStyleSheet("border-image: url(:/image/temp_good.jpg);");
   }
}

void MainWindow::on_pushButton_clicked()
{
        sqlite_Init();
        QString username = ui->LE_Name->text();
        QString password = ui->LE_Password->text();
        QString sql=QString("select * from user where username='%1' and password='%2'")
                .arg(username).arg(password);
        //创建执行语句对象
        QSqlQuery query(sql);
        //判断执行结果
        if(!query.next())
        {
            qDebug()<<"Login error";
            QMessageBox::information(this,"登录认证","登录失败,账户或者密码错误");
        }
        else
        {
            qDebug()<<"Login success";
            QMessageBox::information(this,"登录认证","登录成功");
            ui->stackedWidget->setCurrentIndex(1);
            //登录成功后可以跳转到其他页面
            //QWidget *w = new QWidget;
            //w->show();
            //this->close();
        }

    /*QString name,password;
    name=ui->LE_Name->text();
    password=ui->LE_Password->text();
    if(name=="my"&&password=="123456"){
        ui->stackedWidget->setCurrentIndex(1);
    }
    else{
        QMessageBox::warning(this,tr("Warning"),("用户名或密码错误！"),QMessageBox::Yes);
        ui->LE_Name->clear();                      //清除用户名

        ui->LE_Password->clear();                 //清除密码

        ui->LE_Name->setFocus();              //鼠标回到用户名栏
    }*/
    /*QString username = ui->LE_Name->text();
        //qDebug()<<username; //测试
        //获取输入的密码
        QString userpwd = ui->LE_Password->text();

        if(ui->LE_Name->text()=="")//名字判断
        {
            //弹窗(是否指定窗口，标题，内容)
            QMessageBox::critical(NULL,"错误","用户名为空，请输入用户名");
            userEdit->clear();
            pwdEdit->clear();
            //光标定位回用户名处
            userEdit->setFocus();
        }
        else if(ui->LE_Password->text()=="")//密码判断
        {
            QMessageBox::critical(NULL,"错误","密码为空，请输入密码");
            userEdit->clear();
            pwdEdit->clear();
            //光标定位回用户名处
            userEdit->setFocus();
        }
        else
            {
                int i=0;//判断次数
                for(i=0;i<usersdata::userlist.size();i++)
                {
                    if(userEdit->text()==usersdata::userlist.at(i)->getUsername()&&
                            pwdEdit->text()==usersdata::userlist.at(i)->getUserpwd())//用户密码存在相等
                    {
                        QMessageBox::information(NULL,"成功","登录成功");
                        IndexWin *p = new IndexWin;
                        p->show();
                        this->hide();
                        break;
                    }
                }
                if(i>=usersdata::userlist.size())//没有找到用户密码存在相等
                {
                    QMessageBox::critical(NULL,"错误","用户或密码错误请重新输入");
                    userEdit->clear();
                    pwdEdit->clear();
                    //光标定位回用户名处
                    userEdit->setFocus();
                }
            }*/
}



void sqlite_Init()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("user.db");
    if(!db.open())
    {
        qDebug()<<"open error";
    }
    //create excle
    QString createsql=QString("create table if not exists user(id integer primary key autoincrement,"
                        "username ntext unique not NULL,"
                        "password ntext not NULL)");
    QSqlQuery query;
    if(!query.exec(createsql)){
        qDebug()<<"table create error";
    }
    else{
        qDebug()<<"table create success";
    }
}


void MainWindow::on_BTN_temp_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_BTN_hum_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_BTN_hun_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_BTN_temp_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_signup_clicked()
{
    this->close();
    Signup *s = new Signup;
    s->show();
}
