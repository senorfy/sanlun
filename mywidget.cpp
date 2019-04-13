#include "mywidget.h"
#include "ui_mywidget.h"
#include <QFileDialog>
MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    b=new QPushButton("fyoomm",this);
    //b->show();
    b->move(100,100);
    btn=new MyButton(this);
    //b->resize(50,50);
    btn->setText("chen");
    btn->move(50,50);
    this->setWindowTitle("凤英小可爱");
    this->resize(500,500);
    //connect(b,&QPushButton::clicked,btn,&MyButton::hide);
    connect(b,&QPushButton::clicked,this,[=]{
         btn->setText("凤英我爱你");
    });
    connect(btn,&MyButton::clicked,this,&MyWidget::soltForText1);
    b1=new QPushButton(this);
    b1->setText("弹出德宁框");
    b1->move(200,200);
    b1->setWindowTitle("小德宁");
    connect(b1,&QPushButton::clicked,this,&MyWidget::slotTurn);
    void (subWidget::*Mysignl)()=&subWidget::mysignl;
    connect(&sub,Mysignl,this,&MyWidget::showSlot);
    void (subWidget::*Mysignl1)(int,QString)=&subWidget::mysignl;
    connect(&sub,Mysignl1,this,&MyWidget::showSlot1);
    connect(ui->pushButton,&QPushButton::clicked,this,[=]()
    {
        QString name = QFileDialog::getOpenFileName(this,"凤英","E:\\");
        qDebug()<<name.toUtf8().data();
    });

}
void MyWidget::slotTurn()
{
    this->hide();
    sub.show();
}
void  MyWidget::showSlot()
{
    this->show();
    sub.hide();
}
void MyWidget::showSlot1(int num, QString str)
{
    qDebug()<<num<<"  "<<str.toUtf8().data()<<endl;
}

void MyWidget::soltForText()
{
    btn->setText("凤英我爱你");
}
void MyWidget::soltForText1()
{
    b->setText("凤英我也爱你");
}
MyWidget::~MyWidget()
{
    delete ui;
}
