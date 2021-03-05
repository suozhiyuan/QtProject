#include "logindialog.h"
#include <QApplication>
#include "examdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    LoginDialog w;
//    w.show();
    ExamDialog w;
    w.show();

    return a.exec();
}
