/********************************************************************************
** Form generated from reading UI file 'loginwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
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
#include "classmould.h"
QT_BEGIN_NAMESPACE

class Ui_LoginWidget
{
public:
    QGridLayout *gridLayout;
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
    ClassMould *label_1;
    QSpacerItem *horizontalSpacer_9;
    ClassMould *label_2;
    QSpacerItem *horizontalSpacer_10;
    ClassMould *label_3;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *RightpushButton;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_12;
    QHBoxLayout *horizontalLayout;
    QLabel *Logolabel;
    QSpacerItem *horizontalSpacer;
    QLCDNumber *TimeLcdNumber;
    QHBoxLayout *horizontalLayout_4;
    QLabel *Informationlabel;
    QSpacerItem *horizontalSpacer_30;
    QSpacerItem *horizontalSpacer_34;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_29;
    QSpacerItem *horizontalSpacer_42;
    QSpacerItem *horizontalSpacer_48;
    QSpacerItem *horizontalSpacer_37;
    QSpacerItem *horizontalSpacer_36;
    QSpacerItem *horizontalSpacer_40;
    QSpacerItem *horizontalSpacer_43;
    QSpacerItem *horizontalSpacer_47;
    QSpacerItem *horizontalSpacer_38;
    QSpacerItem *horizontalSpacer_44;
    QSpacerItem *horizontalSpacer_31;
    QSpacerItem *horizontalSpacer_58;
    QSpacerItem *horizontalSpacer_27;
    QSpacerItem *horizontalSpacer_51;
    QSpacerItem *horizontalSpacer_59;
    QSpacerItem *horizontalSpacer_49;
    QSpacerItem *horizontalSpacer_39;
    QSpacerItem *horizontalSpacer_57;
    QSpacerItem *horizontalSpacer_52;
    QSpacerItem *horizontalSpacer_33;
    QSpacerItem *horizontalSpacer_45;
    QSpacerItem *horizontalSpacer_41;
    QSpacerItem *horizontalSpacer_28;
    QSpacerItem *horizontalSpacer_46;
    QSpacerItem *horizontalSpacer_50;
    QSpacerItem *horizontalSpacer_35;
    QSpacerItem *horizontalSpacer_26;
    QSpacerItem *horizontalSpacer_32;
    QSpacerItem *horizontalSpacer_25;
    QSpacerItem *horizontalSpacer_24;
    QPushButton *ServerManpushButton;
    QSpacerItem *horizontalSpacer_21;
    QPushButton *SetpushButton;
    QSpacerItem *horizontalSpacer_22;
    QPushButton *InformationpushButton;
    QSpacerItem *horizontalSpacer_23;
    QPushButton *ShutdownpushButton;

    void setupUi(QWidget *LoginWidget)
    {
        if (LoginWidget->objectName().isEmpty())
            LoginWidget->setObjectName(QStringLiteral("LoginWidget"));
        LoginWidget->resize(864, 599);
        gridLayout = new QGridLayout(LoginWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
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

        label_1 = new ClassMould(groupBox,"NULL");
        label_1->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label_1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_9);

        label_2 = new ClassMould(groupBox,"NULL");
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_10);

        label_3 = new ClassMould(groupBox,"NULL");
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


        gridLayout->addWidget(groupBox, 1, 0, 3, 2);

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


        gridLayout->addLayout(horizontalLayout, 0, 1, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        Informationlabel = new QLabel(LoginWidget);
        Informationlabel->setObjectName(QStringLiteral("Informationlabel"));

        horizontalLayout_4->addWidget(Informationlabel);

        horizontalSpacer_30 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_30);

        horizontalSpacer_34 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_34);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        horizontalSpacer_29 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_29);

        horizontalSpacer_42 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_42);

        horizontalSpacer_48 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_48);

        horizontalSpacer_37 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_37);

        horizontalSpacer_36 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_36);

        horizontalSpacer_40 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_40);

        horizontalSpacer_43 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_43);

        horizontalSpacer_47 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_47);

        horizontalSpacer_38 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_38);

        horizontalSpacer_44 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_44);

        horizontalSpacer_31 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_31);

        horizontalSpacer_58 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_58);

        horizontalSpacer_27 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_27);

        horizontalSpacer_51 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_51);

        horizontalSpacer_59 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_59);

        horizontalSpacer_49 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_49);

        horizontalSpacer_39 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_39);

        horizontalSpacer_57 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_57);

        horizontalSpacer_52 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_52);

        horizontalSpacer_33 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_33);

        horizontalSpacer_45 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_45);

        horizontalSpacer_41 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_41);

        horizontalSpacer_28 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_28);

        horizontalSpacer_46 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_46);

        horizontalSpacer_50 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_50);

        horizontalSpacer_35 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_35);

        horizontalSpacer_26 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_26);

        horizontalSpacer_32 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_32);

        horizontalSpacer_25 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_25);

        horizontalSpacer_24 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_24);

        ServerManpushButton = new QPushButton(LoginWidget);
        ServerManpushButton->setObjectName(QStringLiteral("ServerManpushButton"));

        horizontalLayout_4->addWidget(ServerManpushButton);

        horizontalSpacer_21 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_21);

        SetpushButton = new QPushButton(LoginWidget);
        SetpushButton->setObjectName(QStringLiteral("SetpushButton"));

        horizontalLayout_4->addWidget(SetpushButton);

        horizontalSpacer_22 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_22);

        InformationpushButton = new QPushButton(LoginWidget);
        InformationpushButton->setObjectName(QStringLiteral("InformationpushButton"));

        horizontalLayout_4->addWidget(InformationpushButton);

        horizontalSpacer_23 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_23);

        ShutdownpushButton = new QPushButton(LoginWidget);
        ShutdownpushButton->setObjectName(QStringLiteral("ShutdownpushButton"));

        horizontalLayout_4->addWidget(ShutdownpushButton);


        gridLayout->addLayout(horizontalLayout_4, 4, 1, 1, 1);


        retranslateUi(LoginWidget);

        QMetaObject::connectSlotsByName(LoginWidget);
    } // setupUi

    void retranslateUi(QWidget *LoginWidget)
    {
        LoginWidget->setWindowTitle(QApplication::translate("LoginWidget", "LoginWidget", 0));
        groupBox->setTitle(QString());
        EnterpushButton->setText(QString());
        LeftpushButton->setText(QString());
        RightpushButton->setText(QString());
        Informationlabel->setText(QApplication::translate("LoginWidget", "\345\205\254\345\217\270\344\277\241\346\201\257\357\274\214\350\275\257\344\273\266\344\277\241\346\201\257", 0));
        ServerManpushButton->setText(QString());
        SetpushButton->setText(QString());
        InformationpushButton->setText(QString());
        ShutdownpushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LoginWidget: public Ui_LoginWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWIDGET_H
