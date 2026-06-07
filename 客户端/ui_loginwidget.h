/********************************************************************************
** Form generated from reading UI file 'loginwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWIDGET_H
#define UI_LOGINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWidget
{
public:
    QLabel *label_4;
    QLineEdit *pwd_lineEdit;
    QComboBox *comboBox;
    QLineEdit *account_lineEdit;
    QPushButton *code_pushButton;
    QLineEdit *code_lineEdit;
    QPushButton *register_pushButton;
    QLabel *label_3;
    QLabel *label_5;
    QPushButton *login_pushButton;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *LoginWidget)
    {
        if (LoginWidget->objectName().isEmpty())
            LoginWidget->setObjectName(QStringLiteral("LoginWidget"));
        LoginWidget->resize(922, 703);
        label_4 = new QLabel(LoginWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(130, 340, 111, 51));
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        font.setWeight(75);
        label_4->setFont(font);
        pwd_lineEdit = new QLineEdit(LoginWidget);
        pwd_lineEdit->setObjectName(QStringLiteral("pwd_lineEdit"));
        pwd_lineEdit->setGeometry(QRect(230, 270, 431, 51));
        comboBox = new QComboBox(LoginWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(240, 350, 121, 31));
        account_lineEdit = new QLineEdit(LoginWidget);
        account_lineEdit->setObjectName(QStringLiteral("account_lineEdit"));
        account_lineEdit->setGeometry(QRect(230, 200, 431, 51));
        code_pushButton = new QPushButton(LoginWidget);
        code_pushButton->setObjectName(QStringLiteral("code_pushButton"));
        code_pushButton->setGeometry(QRect(380, 420, 141, 41));
        code_lineEdit = new QLineEdit(LoginWidget);
        code_lineEdit->setObjectName(QStringLiteral("code_lineEdit"));
        code_lineEdit->setGeometry(QRect(230, 420, 131, 41));
        register_pushButton = new QPushButton(LoginWidget);
        register_pushButton->setObjectName(QStringLiteral("register_pushButton"));
        register_pushButton->setGeometry(QRect(430, 480, 191, 71));
        label_3 = new QLabel(LoginWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(130, 270, 111, 51));
        label_3->setFont(font);
        label_5 = new QLabel(LoginWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(130, 410, 111, 51));
        label_5->setFont(font);
        login_pushButton = new QPushButton(LoginWidget);
        login_pushButton->setObjectName(QStringLiteral("login_pushButton"));
        login_pushButton->setGeometry(QRect(130, 480, 191, 71));
        label = new QLabel(LoginWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(230, 70, 521, 81));
        QFont font1;
        font1.setPointSize(38);
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);
        label_2 = new QLabel(LoginWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(130, 200, 111, 51));
        label_2->setFont(font);

        retranslateUi(LoginWidget);

        QMetaObject::connectSlotsByName(LoginWidget);
    } // setupUi

    void retranslateUi(QWidget *LoginWidget)
    {
        LoginWidget->setWindowTitle(QApplication::translate("LoginWidget", "Form", Q_NULLPTR));
        label_4->setText(QApplication::translate("LoginWidget", "\350\272\253\344\273\275", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("LoginWidget", "\350\200\201\344\272\272", Q_NULLPTR)
         << QApplication::translate("LoginWidget", "\346\212\244\345\267\245", Q_NULLPTR)
         << QApplication::translate("LoginWidget", "\345\256\266\345\261\236", Q_NULLPTR)
        );
        code_pushButton->setText(QApplication::translate("LoginWidget", "\350\216\267\345\217\226\351\252\214\350\257\201\347\240\201", Q_NULLPTR));
        register_pushButton->setText(QApplication::translate("LoginWidget", "\346\263\250\345\206\214", Q_NULLPTR));
        label_3->setText(QApplication::translate("LoginWidget", "\345\257\206\347\240\201", Q_NULLPTR));
        label_5->setText(QApplication::translate("LoginWidget", "\351\252\214\350\257\201\347\240\201", Q_NULLPTR));
        login_pushButton->setText(QApplication::translate("LoginWidget", "\347\231\273\345\275\225 ", Q_NULLPTR));
        label->setText(QApplication::translate("LoginWidget", "\345\261\205\345\256\266\345\205\273\350\200\201\346\231\272\350\203\275\347\233\221\346\212\244\347\263\273\347\273\237", Q_NULLPTR));
        label_2->setText(QApplication::translate("LoginWidget", "\350\264\246\345\217\267", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LoginWidget: public Ui_LoginWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWIDGET_H
