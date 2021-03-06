#include "examdialog.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QApplication>

ExamDialog::ExamDialog(QWidget* parent):QDialog(parent)
{
    setWindowTitle("考试已用时：0分0秒");
    resize(800, 900);           //设置宽高
    initTimer();                //初始化计时器
    initLayout();               //初始化控件间距与窗体间距

    if(initTextEdit())          //文本编辑器初始化
    {
        //QMessageBox::information(this, "提示" ,"初始化题库数据文件失败！");
        //QTimer::singleShot(0, qApp, SLOT(QUIT()));      //间隔时间发送信号到槽，间隔多久 响应的槽（qapp为当前应用程序） 发送什么信号
    }

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
    QStringList strList;                //保存读取到的答案行, QStringList 类提供了一个字符串列表。
    QString fileName("../exam.txt");
    QFile file(fileName);               //操作文件，参数为文件路径 文件名, QFile 类提供了读取和写入文件的接口
    QTextStream stream(&file);          //文本文件流, QTextStream 类为读写文本提供了一个方便的接口
    stream.setCodec("UTF-8");

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        m_textEdit = new QTextEdit(this);       //将图库文本显示进行初始化， QTextEdit 类提供了一个用于编辑和显示纯文本和富文本的小部件。
        QString strText;                        //用于保存显示到文本编辑器的数据， 题目 & 选项
        int nLines = 0;

        while (!stream.atEnd())
        {
            if(nLines == 0)
            {
                stream.readLine();       //从流中读取一行文本，并将其作为 QString 返回
                nLines++;
                continue;
            }
            if((nLines >= 6 && nLines <= 9 * 6 && (nLines % 6 == 0)) || (nLines == 6 * 9 + 4))
            {
                strLine = stream.readLine();
                strList = strLine.split(" ");               //按照字符串中的空格分隔字符串
                m_answerList.append(strList.at(1));         // append 在列表的末尾插入值。
                strLine += "\n";
                nLines++;
                continue;
            }

            strText += stream.readLine();
            strText += "\n";
            nLines++;
        }
        m_textEdit->setText(strText);         //将文本显示到控件中去
        m_layout->addWidget(m_textEdit, 0, 0, 1, 10);
        file.close();
        return true;
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



