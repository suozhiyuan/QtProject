#ifndef EXAMDIALOG_H
#define EXAMDIALOG_H
#include <QDialog>
#include <QTimer>
#include <QTextEdit>
#include <QLabel>
#include <QRadioButton>
#include <QCheckBox>
#include <QGridLayout>

class ExamDialog : public QDialog
{
    Q_OBJECT        //需要用到信号与槽机制， 加入 Q_OBJECT 宏声明
public:
    ExamDialog(QWidget* PARENT = 0);
    void initTimer();       //初始化计时器
    void initLayout();      //初始化布局管理器
    bool initTextEdit();    //初始化文本编辑器

private:
    QTimer* m_timer;                 //计时器， QTimer 类提供了重复的单次计时器
    int m_timeGo;                    //已用时
    QTextEdit* m_textEdit;           //题库显示， QTextEdit 类提供了一个用于编辑和显示纯文本和富文本的小部件。
    QLabel* m_titleLabels[10];       //题目标签， QLabel 小部件提供文本或图像显示。
    QRadioButton *m_raidoBtns[32];   //单选题按钮， QRadioButton 小部件提供了一个带有文本标签的单选按钮。
    QCheckBox *m_checkBtns[4];       //多选题按钮， QCheckBox 小部件提供了一个带有文本标签的复选框。
    QRadioButton *m_radioA;          //判断题A选项， QRadioButton 小部件提供了一个带有文本标签的单选按钮。
    QRadioButton *m_radioB;          //判断题B选项
    QGridLayout *m_layout;          //QT的布局管理器， QGridLayout 类在网格中布局小部件。
    QStringList m_answerList;       //答案列表

/*
public slots：在这个区内声明的槽意味着任何对象都可将信号与之相连接。这对于组件编程非常有用，你可以创建彼此互不了解的对象，将它们的信号与槽进行连接以便信息能够正确的传递。
protected slots：在这个区内声明的槽意味着当前类及其子类可以将信号与之相连接。这适用于那些槽，它们是类实现的一部分，但是其界面接口却面向外部。
private slots：在这个区内声明的槽意味着只有类自己可以将信号与之相连接。这适用于联系非常紧密的类。
*/
private slots:
    void freshTime();       //私有 响应的槽方法
};

#endif // EXAMDIALOG_H
