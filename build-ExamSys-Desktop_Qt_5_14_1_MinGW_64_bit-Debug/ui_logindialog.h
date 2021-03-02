/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *accountEdit;
    QLineEdit *codeEdit;
    QPushButton *loginBtn;
    QPushButton *cancelBtn;
    QLabel *imgLabel;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QString::fromUtf8("LoginDialog"));
        LoginDialog->resize(563, 381);
        label = new QLabel(LoginDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(120, 71, 24, 16));
        label_2 = new QLabel(LoginDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(120, 110, 24, 12));
        accountEdit = new QLineEdit(LoginDialog);
        accountEdit->setObjectName(QString::fromUtf8("accountEdit"));
        accountEdit->setGeometry(QRect(160, 70, 131, 20));
        codeEdit = new QLineEdit(LoginDialog);
        codeEdit->setObjectName(QString::fromUtf8("codeEdit"));
        codeEdit->setGeometry(QRect(160, 110, 131, 20));
        loginBtn = new QPushButton(LoginDialog);
        loginBtn->setObjectName(QString::fromUtf8("loginBtn"));
        loginBtn->setGeometry(QRect(110, 160, 75, 23));
        cancelBtn = new QPushButton(LoginDialog);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));
        cancelBtn->setGeometry(QRect(240, 160, 75, 23));
        imgLabel = new QLabel(LoginDialog);
        imgLabel->setObjectName(QString::fromUtf8("imgLabel"));
        imgLabel->setGeometry(QRect(0, 0, 431, 261));
        imgLabel->setPixmap(QPixmap(QString::fromUtf8(":/login.jpg")));
        imgLabel->raise();
        label->raise();
        label_2->raise();
        accountEdit->raise();
        codeEdit->raise();
        loginBtn->raise();
        cancelBtn->raise();

        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "LoginDialog", nullptr));
        label->setText(QCoreApplication::translate("LoginDialog", "\350\264\246\345\217\267", nullptr));
        label_2->setText(QCoreApplication::translate("LoginDialog", "\345\257\206\347\240\201", nullptr));
        loginBtn->setText(QCoreApplication::translate("LoginDialog", "\347\231\273 \345\275\225", nullptr));
        cancelBtn->setText(QCoreApplication::translate("LoginDialog", "\345\217\226 \346\266\210", nullptr));
        imgLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
