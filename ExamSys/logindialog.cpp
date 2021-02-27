#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent), ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->imgLabel->setScaledContents(true);      //填充设置
    this->resize(ui->imgLabel->width(),ui->imgLabel->height());
    this->setWindowTitle("标头");
    this->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);       //普通对话框风格, 不要帮助问号按钮
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginBtn_clicked()
{
    //QMessageBox::information(this, "提示", "槽方法调用");
    //正则验证邮箱地址 用户名@域名
    //^ 开始 $ 结束
    //+表示匹配次数 ≥1 次
    //*表示匹配任意次数(可以是0次)
    //{n.m}表示匹配次数至少n次,至多m次
    QRegExp rx("^[A-Za-z0-9]+([_\\.][A-Za-z0-9]+)*@([A-Za-z0-9\\-]+\\.)+[A-Za-z]{2,6}$");

    //exactMatch 准确匹配 ui 模块 accountEdit 的 text 文本信息
    bool res = rx.exactMatch(ui -> accountEdit -> text());
    if(!res)
    {
        QMessageBox::information(this, "提示", "没有匹配的邮箱账号, 请重新输入!!!");
        ui->accountEdit->clear();       //清除输入框
        ui->accountEdit->setFocus();    //将焦点转移至输入框

    }else{
        QMessageBox::information(this, "提示", "欢迎登陆!!!");
    }

}
