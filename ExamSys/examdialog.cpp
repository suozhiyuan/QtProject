#include "examdialog.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QApplication>
#include <QPushButton>


ExamDialog::ExamDialog(QWidget* parent):QDialog(parent)
{
    //设置字体大小
    QFont font;                 //QFont 类指定了用于绘制文本的字体的查询。
    font.setPointSize(12);      //设置字体大小
    setFont(font);

    //设置窗体背景颜色
    setPalette(QPalette(QColor(209,215,255)));


    setWindowTitle("考试已用时：0分0秒");
    setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
    resize(800, 900);           //设置宽高
    initTimer();                //初始化计时器
    initLayout();               //初始化控件间距与窗体间距
    if(!initTextEdit())          //文本编辑器初始化
    {
        QMessageBox::information(this, "提示" ,"初始化题库数据文件失败！");
        QTimer::singleShot(0, qApp, SLOT(QUIT()));      //间隔时间发送信号到槽，间隔多久 响应的槽（qapp为当前应用程序） 发送什么信号
    }

    //初始化答题区
    initButtons();
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
        m_textEdit->setReadOnly(true);          //设置只读
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
                //strLine += "\n";
                strText += "\n";
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

void ExamDialog::initButtons()
{
    QStringList strList = {"A","B","C","D"};
    for(int i = 0; i < 10; i++)
    {
        //题目标签
        m_titleLabels[i] = new QLabel(this);        //QLabel小部件提供文本或图像显示。
        m_titleLabels[i] -> setText("第" + QString::number(i + 1) + "题");
        m_layout->addWidget(m_titleLabels[i] ,1 ,i);       //addWidget 将小部件添加到这个框布局的末尾，具有拉伸因子拉伸和对齐对齐。参数2 第几行 参数3 第几列

        //对按钮进行分组
        if(i < 8)
        {
            m_btnGroups[i] = new QButtonGroup(this);
        }

        //选择题
        for(int j = 0; j <4; j++)
        {

            if(i == 8)
            {
                //多选
                m_checkBtns[j] = new QCheckBox(this);
                m_checkBtns[j]->setText(strList.at(j));
                m_layout->addWidget(m_checkBtns[j], 2+j, 8);
            }
            else if (i == 9)
            {
                 //判断题
                m_radioA = new QRadioButton(this);          //QRadioButton 小部件提供了一个带有文本标签的单选按钮。
                m_radioB = new QRadioButton(this);
                m_radioA->setText("正确");
                m_radioB->setText("错误");

                m_layout->addWidget(m_radioA, 2, 9);        //添加到布局
                m_layout->addWidget(m_radioB, 3, 9);

                m_btnGroups[8] = new QButtonGroup(this);    //对按钮进行分组
                m_btnGroups[8]->addButton(m_radioA);
                m_btnGroups[8]->addButton(m_radioB);
                break;
            }
            else
            {
                //单选
                m_radioBtns[4 * i + j] = new QRadioButton(this);
                m_radioBtns[4 * i + j]->setText(strList.at(j));
                m_layout->addWidget(m_radioBtns[4 * i + j], 2+j, i);

                m_btnGroups[i]->addButton(m_radioBtns[4 * i + j]);    //对按钮进行分组
            }
        }
    }

    QPushButton *submitBtn = new QPushButton(this);
    submitBtn->setText("提交");
    submitBtn->setFixedSize(100, 35);
    //connect 参数1 谁发信号  参数2 发什信号宏clicked(点击信号)  参数3 谁响应  参数4 响应干嘛宏(提交)
    connect(submitBtn, SIGNAL(clicked(bool)), this, SLOT(getScore()));
    m_layout->addWidget(submitBtn,6,9);

}

bool ExamDialog::hasNoSelect()
{
    int radioSelects = 0;
    for (int i = 0; i < 8; i++)
    {
        if(m_btnGroups[i]->checkedButton())       //checkedButton 返回按钮组的选中按钮，如果没有选中按钮，则返回nullptr
        {
            radioSelects++;
        }
    }
    if(radioSelects != 8)
    {
        return  true;
    }

    int checkSelects = 0;
    for (int i = 0; i < 4; i++)
    {
        if(m_checkBtns[i]->isChecked())            //isChecked 检查按钮是否被选中
        {
            checkSelects++;
        }
    }

    if(checkSelects <= 1)
    {
        return true;
    }

    if(!m_radioA->isChecked() && !m_radioB->isChecked())
    {
        return true;
    }

    return false;
}

//刷新考试用时操作
void ExamDialog::freshTime()
{
    m_timeGo++;
    QString min = QString::number(m_timeGo / 60);       //QString::number 方法可以将数据转换字符串
    QString sec = QString::number(m_timeGo % 60);
    setWindowTitle("考试已用时：" + min + "分" + sec + "秒");
}

void ExamDialog::getScore()
{
    if(hasNoSelect())
    {
        QMessageBox::information(this, "提示", "有未完成的题目！", "是");
        return;
    }

    int scores = 0;
    for (int i = 0; i < 10; i++)
    {
        if(i < 8)
        {
            if(m_btnGroups[i]->checkedButton()->text() == m_answerList.at(i))     //获取按钮组中选中内容的文本  与 m_answerList的第 i 个进行对比
            {
                scores += 10;
            }
        }

        //多项选择题计分
        if(i == 8)
        {
            QString answer = m_answerList.at(i);        //提取答案字符串中的第 i 个内容
            bool hasA = false;
            bool hasB = false;
            bool hasC = false;
            bool hasD = false;

            if(answer.contains("A")) hasA = true;          // 如果该字符串包含了str类型的字符串 A ，则返回true;否则返回false。
            if(answer.contains("B")) hasB = true;
            if(answer.contains("C")) hasC = true;
            if(answer.contains("D")) hasD = true;

            bool checkA = m_checkBtns[0]->checkState();     //返回复选框的选中状态。选中返回 true
            bool checkB = m_checkBtns[1]->checkState();
            bool checkC = m_checkBtns[2]->checkState();
            bool checkD = m_checkBtns[3]->checkState();

            if(hasA != checkA) continue;
            if(hasB != checkB) continue;
            if(hasC != checkC) continue;
            if(hasD != checkD) continue;

            scores += 10;
        }

        //判断题计分
        if(i == 9)
        {
            if(m_btnGroups[8]->checkedButton()->text() == m_answerList.at(i))
            {
                scores += 10;
            }
        }
    }
    QString str =  "您的分数是：" + QString::number(scores) + "分。是否重新考试？";
    int res = QMessageBox::information(this, "提示", str, QMessageBox::Yes | QMessageBox::No);
    if(res == QMessageBox::Yes)
        return;
    else
        close();
}



