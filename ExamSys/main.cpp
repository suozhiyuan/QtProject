#include "logindialog.h"
#include <QApplication>
#include "examdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);         //QApplication类管理GUI应用程序的控制流和主设置。
    LoginDialog logDialog;              //继承自QDialog，QDialog类是对话框窗口的基类。
    int res = logDialog.exec();         //.exec() 以模态窗口运行
    if(res == QDialog::Accepted)        //模式对话框返回的值。 0 和 1
    {
        ExamDialog *examDialog;
        examDialog = new ExamDialog;
        //examDialog->exec();
    }
    else
    {
        return  0;
    }
    return a.exec();
//    ExamDialog w;
//    w.show();
}
