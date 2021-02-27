#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginDialog; }     //和类 LoginDialog 不是一个东西,Ui_LoginDialog的子类,用于描述登录窗口界面信息
QT_END_NAMESPACE

class LoginDialog : public QDialog
{
    Q_OBJECT        //信号与槽 继承自 QObject 的类才能够支持信号与槽机制

public:
    LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void on_loginBtn_clicked();

private:
    Ui::LoginDialog *ui;
};
#endif // LOGINDIALOG_H
