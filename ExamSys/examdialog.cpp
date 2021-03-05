#include "examdialog.h"

ExamDialog::ExamDialog(QWidget* parent):QDialog(parent)
{

}

void ExamDialog::initTimer()
{
    m_timeGo = 0;                        //已用时
    m_timer = new QTimer(this);          //new一个计时器
    m_timer->setInterval(1000);          //指定多久1次，单位毫秒
    m_timer->start();                    //计时器的启动操作

    //QObject 的 connect 方法，可以将信号与槽联系起来
    //参数一 发送信号对象
    //参数二 发送什么样的信号
    //参数三 谁响应
    //参数四 执行操作
    connect(m_timer, SIGNAL(timeout()), this, SLOT(freshTime()));
}

void ExamDialog::freshTime()
{

}
