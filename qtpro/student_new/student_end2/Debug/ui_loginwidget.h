/********************************************************************************
** Form generated from reading UI file 'loginwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWIDGET_H
#define UI_LOGINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWidget
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *Logolabel;
    QSpacerItem *horizontalSpacer;
    QLCDNumber *TimeLcdNumber;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_11;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *EnterpushButton;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *LeftpushButton;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_10;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *RightpushButton;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_12;
    QHBoxLayout *horizontalLayout_5;
    QLabel *Informationlabel;
    QSpacerItem *horizontalSpacer_30;
    QSpacerItem *horizontalSpacer_16;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *ServerManpushButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *InformationpushButton;
    QSpacerItem *horizontalSpacer_13;
    QPushButton *SetpushButton;
    QSpacerItem *horizontalSpacer_14;
    QPushButton *ShutdownpushButton;
    QSpacerItem *horizontalSpacer_15;

    void setupUi(QWidget *LoginWidget)
    {
        if (LoginWidget->objectName().isEmpty())
            LoginWidget->setObjectName(QStringLiteral("LoginWidget"));
        LoginWidget->resize(864, 599);
        gridLayout = new QGridLayout(LoginWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        Logolabel = new QLabel(LoginWidget);
        Logolabel->setObjectName(QStringLiteral("Logolabel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Logolabel->sizePolicy().hasHeightForWidth());
        Logolabel->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(Logolabel);

        horizontalSpacer = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        TimeLcdNumber = new QLCDNumber(LoginWidget);
        TimeLcdNumber->setObjectName(QStringLiteral("TimeLcdNumber"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(TimeLcdNumber->sizePolicy().hasHeightForWidth());
        TimeLcdNumber->setSizePolicy(sizePolicy1);
        TimeLcdNumber->setFrameShape(QFrame::NoFrame);

        horizontalLayout->addWidget(TimeLcdNumber);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        groupBox = new QGroupBox(LoginWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_11, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        EnterpushButton = new QPushButton(groupBox);
        EnterpushButton->setObjectName(QStringLiteral("EnterpushButton"));

        horizontalLayout_3->addWidget(EnterpushButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        gridLayout_2->addLayout(horizontalLayout_3, 3, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        LeftpushButton = new QPushButton(groupBox);
        LeftpushButton->setObjectName(QStringLiteral("LeftpushButton"));

        horizontalLayout_2->addWidget(LeftpushButton);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_7);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_9);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_10);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_8);

        RightpushButton = new QPushButton(groupBox);
        RightpushButton->setObjectName(QStringLiteral("RightpushButton"));

        horizontalLayout_2->addWidget(RightpushButton);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);


        gridLayout_2->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_12, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox, 1, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        Informationlabel = new QLabel(LoginWidget);
        Informationlabel->setObjectName(QStringLiteral("Informationlabel"));

        horizontalLayout_5->addWidget(Informationlabel);

        horizontalSpacer_30 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_30);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_16);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        ServerManpushButton = new QPushButton(LoginWidget);
        ServerManpushButton->setObjectName(QStringLiteral("ServerManpushButton"));

        horizontalLayout_4->addWidget(ServerManpushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        InformationpushButton = new QPushButton(LoginWidget);
        InformationpushButton->setObjectName(QStringLiteral("InformationpushButton"));

        horizontalLayout_4->addWidget(InformationpushButton);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_13);

        SetpushButton = new QPushButton(LoginWidget);
        SetpushButton->setObjectName(QStringLiteral("SetpushButton"));

        horizontalLayout_4->addWidget(SetpushButton);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_14);

        ShutdownpushButton = new QPushButton(LoginWidget);
        ShutdownpushButton->setObjectName(QStringLiteral("ShutdownpushButton"));

        horizontalLayout_4->addWidget(ShutdownpushButton);

        horizontalSpacer_15 = new QSpacerItem(37, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_15);


        horizontalLayout_5->addLayout(horizontalLayout_4);


        gridLayout->addLayout(horizontalLayout_5, 2, 0, 1, 1);

        groupBox->raise();

        retranslateUi(LoginWidget);

        QMetaObject::connectSlotsByName(LoginWidget);
    } // setupUi

    void retranslateUi(QWidget *LoginWidget)
    {
        LoginWidget->setWindowTitle(QApplication::translate("LoginWidget", "LoginWidget", Q_NULLPTR));
        Logolabel->setText(QApplication::translate("LoginWidget", "LOGO", Q_NULLPTR));
        groupBox->setTitle(QString());
        EnterpushButton->setText(QString());
        LeftpushButton->setText(QString());
        label->setText(QApplication::translate("LoginWidget", "TextLabel", Q_NULLPTR));
        label_2->setText(QApplication::translate("LoginWidget", "TextLabel", Q_NULLPTR));
        label_3->setText(QApplication::translate("LoginWidget", "TextLabel", Q_NULLPTR));
        RightpushButton->setText(QString());
        Informationlabel->setText(QApplication::translate("LoginWidget", "\345\205\254\345\217\270\344\277\241\346\201\257\357\274\214\350\275\257\344\273\266\344\277\241\346\201\257", Q_NULLPTR));
        ServerManpushButton->setText(QString());
        InformationpushButton->setText(QString());
        SetpushButton->setText(QString());
        ShutdownpushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LoginWidget: public Ui_LoginWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWIDGET_H
