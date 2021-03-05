#ifndef EXAMDIALOG_H
#define EXAMDIALOG_H
#include <QDialog>
#include <QTimer>

class ExamDialog : public QDialog
{
    Q_OBJECT        //需要用到信号与槽机制， 加入 Q_OBJECT 宏声明
public:
    ExamDialog(QWidget* PARENT = 0);
    void initTimer();       //初始化计时器

private:
    QTimer* m_timer;        //计时器
    int m_timeGo;           //已用时

/*
public slots：在这个区内声明的槽意味着任何对象都可将信号与之相连接。这对于组件编程非常有用，你可以创建彼此互不了解的对象，将它们的信号与槽进行连接以便信息能够正确的传递。
protected slots：在这个区内声明的槽意味着当前类及其子类可以将信号与之相连接。这适用于那些槽，它们是类实现的一部分，但是其界面接口却面向外部。
private slots：在这个区内声明的槽意味着只有类自己可以将信号与之相连接。这适用于联系非常紧密的类。
*/
private slots:
    void freshTime();       //私有 响应的槽方法

};

#endif // EXAMDIALOG_H
