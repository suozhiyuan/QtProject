#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent), ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->imgLabel->setScaledContents(true);                                                      //填充设置
    this->resize(ui->imgLabel->width(),ui->imgLabel->height());
    this->setFixedSize(width() ,height());                              //获取宽和高对窗口进行初始化固定
    this->setWindowTitle("标头");
    this->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);       //普通对话框风格, 不要帮助问号按钮
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginBtn_clicked()
{
    /*
    QMessageBox::information(this, "提示", "槽方法调用");
    正则验证邮箱地址 用户名@域名
    ^ 开始 $ 结束
    +表示匹配次数 ≥1 次
    *表示匹配任意次数(可以是0次)
    {n.m}表示匹配次数至少n次,至多m次
     \\.   \\- 为转义，代表的就是 . -
    */
    QRegExp rx("^[A-Za-z0-9]+([_\\.][A-Za-z0-9]+)*@([A-Za-z0-9\\-]+\\.)+[A-Za-z]{2,6}$");
    bool res = rx.exactMatch(ui -> accountEdit -> text());                  // exactMatch 准确匹配控件中的文本信息 == ui 模块 accountEdit 的 text 文本信息

    if(!res)
    {
        QMessageBox::information(this, "提示", "邮箱格式错误, 请重新输入!!!");        //当前窗口作为副窗口，提示框标题，提示框内容
        ui->accountEdit->clear();       //清除账号框
        ui->codeEdit->clear();
        ui->accountEdit->setFocus();    //将焦点转移至输入框
        return;
    }
    else
    {
        //QMessageBox::information(this, "提示", "欢迎登陆!!!");
        QString filename;                          //账号密码数据文件的路径
        QString strAccInput;                       //用来保存 输入的账号信息
        QString strCode;                           //用来保存 输入的密码信息
        QString strLine;                           //用来保存每行读取的字符串
        QStringList strList;                       //字符串链表

        filename = "../account.txt";
        strAccInput = ui->accountEdit->text();     //获取控件中的账号信息
        strCode = ui->codeEdit->text();            //获取控件中的密码信息

        QFile file(filename);                      //用来保存文件的类，并用filename进行初始化
        QTextStream stream(&file);                 //读取文件流，保存到 stream

        if(file.open(QIODevice::ReadOnly | QIODevice::Text))  //打开文件，并且指定要对文件进行哪些操作， ReadOnly 只读， Text 纯文本
        {
            bool isWin = false;     //登录成功
            while (!stream.atEnd())
            {
                strLine = stream.readLine();           //从文件流 stream 中读取一行
                strList = strLine.split(",");          //以某种符号分割字符串
                if(strAccInput == strList.at(0))       // QStringList 类型的字符串链表， at 访问元素
                {
                    if(strCode == strList.at(1))
                    {
                        QMessageBox::information(this,"提示","密码输入正确！");
                        isWin = true;
                        file.close();                   //关闭文件
                        done(Accepted);                //关闭当前窗体，并且以指定的方式返回，Accepted 接受， Rejected 不接受
                        return;
                    }
                }
            }
            if(!isWin)
            {
                QMessageBox::information(this,"提示", "账号或密码错误！重新输入");
                ui->accountEdit->clear();       //清除账号输入框
                ui->codeEdit->clear();          //清除密码输入框
                ui->accountEdit->setFocus();    //将焦点转移至输入框
                file.close();
            }
        }
        else
        {
            QMessageBox::information(this, "提示", "读取账号文件数据失败!");
            return;
        }

    }

}

void LoginDialog::on_cancelBtn_clicked()
{
    done(Rejected);              //关闭当前窗体，并且以指定的方式返回，Accepted 接受, Rejected 不接受
}
