#include "examdialog.h"
#include <QFile>
#include <QTextStream>

ExamDialog::ExamDialog(QWidget* parent):QDialog(parent)
{
    setWindowTitle("考试已用时：0分0秒");
    initTimer();        //初始化计时器
    initLayout();       //初始化控件间距与窗体间距
}

void ExamDialog::initTimer()
{
    m_timeGo = 0;                        //已用时
    m_timer = new QTimer(this);          //new一个计时器
    m_timer->setInterval(1000);          //指定多久1次，单位毫秒
    m_timer->start();                    //计时器的启动操作

    //QObject 的 connect 方法，可以将 信号 与 槽 联系起来
    //参数一 发送信号对象    //参数二 发送什么样的信号    //参数三 谁响应    //参数四 执行操作
    connect(m_timer, SIGNAL(timeout()), this, SLOT(freshTime()));
}

void ExamDialog::initLayout()
{
    m_layout = new QGridLayout(this);
    m_layout->setSpacing(10);           //设置控件间的间距
    m_layout->setMargin(10);            //设置窗体与控件之间的间距
}

bool ExamDialog::initTextEdit()
{
    QString strLine;                    //保存文件中读取到的一行数据
    QStringList strList;                //保存读取到的答案行
    QString fileName("../exam.txt");    //文件路径
    QFile file(fileName);               //操作文件，参数为文件路径 文件名
    QTextStream stream(&file);          //文本文件流

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        m_textEdit = new QTextEdit(this);
        QString strText;                //用于保存显示到文本编辑器的数据
    }
    else
    {
        return false;
    }
}

//刷新考试用时操作
void ExamDialog::freshTime()
{
    m_timeGo++;
    QString min = QString::number(m_timeGo / 60);       //QString::number 方法可以将数据转换字符串
    QString sec = QString::number(m_timeGo % 60);
    setWindowTitle("考试已用时：" + min + "分" + sec + "秒");
}



