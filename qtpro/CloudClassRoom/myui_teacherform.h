/********************************************************************************
** Form generated from reading UI file 'teacherform.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEACHERFORM_H
#define UI_TEACHERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "classmould.h"

QT_BEGIN_NAMESPACE

class Ui_TeacherForm
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *Logolabel;
    QSpacerItem *horizontalSpacer_18;
    QLabel *TeacherVMStatuslabel;
    QSpacerItem *horizontalSpacer_19;
    QScrollArea *TeacherscrollArea;
    QWidget *Teacher_scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout_2;
    QLabel *RoomNumberlabel;
    QLCDNumber *TimelcdNumber;
    QSpacerItem *horizontalSpacer_22;
    QSpacerItem *horizontalSpacer_25;
    QSpacerItem *horizontalSpacer_26;
    QSpacerItem *horizontalSpacer_30;
    QSpacerItem *horizontalSpacer_33;
    QSpacerItem *horizontalSpacer_28;
    QSpacerItem *horizontalSpacer_31;
    QSpacerItem *horizontalSpacer_32;
    QSpacerItem *horizontalSpacer_23;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QLabel *TeacherNameLogolabel;
    QLabel *TeacherNamelabel;
    QSpacerItem *horizontalSpacer_21;
    QPushButton *BackpushButton;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QLabel *ClassNamelTitletabel;
    QLabel *ClassNameLogolabel;
    QLabel *ClassNamelabel;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *horizontalSpacer_20;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *StartSelfpushButton;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *ClassOverpushButton;
    QSpacerItem *horizontalSpacer_24;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_9;
    QLabel *SetClassNamelabel;
    QComboBox *ClsaaNamecomboBox;
    QTabWidget *ClasstabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_16;
    QPushButton *LeftpushButton;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_7;
    ClassMould *ClassNamelabel_1;
    QSpacerItem *horizontalSpacer_34;
    QSpacerItem *horizontalSpacer_27;
    ClassMould *ClassNamelabel_2;
    QSpacerItem *horizontalSpacer_35;
    QSpacerItem *horizontalSpacer_29;
    ClassMould *ClassNamelabel_3;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_13;
    QPushButton *ClassBeginpushButton;
    QSpacerItem *horizontalSpacer_14;
    QSpacerItem *verticalSpacer_3;
    QPushButton *RightpushButton;
    QSpacerItem *horizontalSpacer_15;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *horizontalSpacer_11;
    QSpacerItem *horizontalSpacer_17;
    QSpacerItem *horizontalSpacer_12;
    QSpacerItem *verticalSpacer_7;
    QSpacerItem *verticalSpacer_8;
    QWidget *tab_2;
    QGridLayout *gridLayout_3;
    QScrollArea *TerminalscrollArea;
    QWidget *Student_scrollAreaWidgetContents;
    QPushButton *TeacherVMFlush;

    void setupUi(QWidget *TeacherForm)
    {
        if (TeacherForm->objectName().isEmpty())
            TeacherForm->setObjectName(QStringLiteral("TeacherForm"));
        TeacherForm->resize(1920, 1080);
        gridLayout = new QGridLayout(TeacherForm);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        Logolabel = new QLabel(TeacherForm);
        Logolabel->setObjectName(QStringLiteral("Logolabel"));

        verticalLayout->addWidget(Logolabel);

        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer_18);

        TeacherVMStatuslabel = new QLabel(TeacherForm);
        TeacherVMStatuslabel->setObjectName(QStringLiteral("TeacherVMStatuslabel"));
//        TeacherVMFlush = new QPushButton(TeacherForm);
//        TeacherVMFlush->setObjectName(QStringLiteral("TeacherVMFlush"));

        verticalLayout->addWidget(TeacherVMStatuslabel);

        horizontalSpacer_19 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer_19);

        TeacherscrollArea = new QScrollArea(TeacherForm);
        TeacherscrollArea->setObjectName(QStringLiteral("TeacherscrollArea"));
        TeacherscrollArea->setWidgetResizable(true);
        Teacher_scrollAreaWidgetContents = new QWidget();
        Teacher_scrollAreaWidgetContents->setObjectName(QStringLiteral("Teacher_scrollAreaWidgetContents"));
        Teacher_scrollAreaWidgetContents->setGeometry(QRect(0, 0, 68, 572));
        TeacherscrollArea->setWidget(Teacher_scrollAreaWidgetContents);

        verticalLayout->addWidget(TeacherscrollArea);


        gridLayout->addLayout(verticalLayout, 0, 0, 5, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        RoomNumberlabel = new QLabel(TeacherForm);
        RoomNumberlabel->setObjectName(QStringLiteral("RoomNumberlabel"));

        horizontalLayout_2->addWidget(RoomNumberlabel);

        TimelcdNumber = new QLCDNumber(TeacherForm);
        TimelcdNumber->setObjectName(QStringLiteral("TimelcdNumber"));

        horizontalLayout_2->addWidget(TimelcdNumber);

        horizontalSpacer_22 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_22);

        horizontalSpacer_25 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_25);

        horizontalSpacer_26 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_26);

        horizontalSpacer_30 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_30);

        horizontalSpacer_33 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_33);

        horizontalSpacer_28 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_28);

        horizontalSpacer_31 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_31);

        horizontalSpacer_32 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_32);

        horizontalSpacer_23 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_23);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        TeacherNameLogolabel = new QLabel(TeacherForm);
        TeacherNameLogolabel->setObjectName(QStringLiteral("TeacherNameLogolabel"));

        horizontalLayout->addWidget(TeacherNameLogolabel);

        TeacherNamelabel = new QLabel(TeacherForm);
        TeacherNamelabel->setObjectName(QStringLiteral("TeacherNamelabel"));

        horizontalLayout->addWidget(TeacherNamelabel);


        horizontalLayout_2->addLayout(horizontalLayout);

        horizontalSpacer_21 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_21);

        BackpushButton = new QPushButton(TeacherForm);
        BackpushButton->setObjectName(QStringLiteral("BackpushButton"));

        horizontalLayout_2->addWidget(BackpushButton);


        gridLayout->addLayout(horizontalLayout_2, 1, 1, 1, 3);

        horizontalSpacer = new QSpacerItem(789, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 1, 1, 3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        ClassNamelTitletabel = new QLabel(TeacherForm);
        ClassNamelTitletabel->setObjectName(QStringLiteral("ClassNamelTitletabel"));

        horizontalLayout_3->addWidget(ClassNamelTitletabel);

        ClassNameLogolabel = new QLabel(TeacherForm);
        ClassNameLogolabel->setObjectName(QStringLiteral("ClassNameLogolabel"));

        horizontalLayout_3->addWidget(ClassNameLogolabel);

        ClassNamelabel = new QLabel(TeacherForm);
        ClassNamelabel->setObjectName(QStringLiteral("ClassNamelabel"));

        horizontalLayout_3->addWidget(ClassNamelabel);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        gridLayout->addLayout(horizontalLayout_3, 3, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 3, 2, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_8);

        horizontalSpacer_20 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_20);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        StartSelfpushButton = new QPushButton(TeacherForm);
        StartSelfpushButton->setObjectName(QStringLiteral("StartSelfpushButton"));

        horizontalLayout_4->addWidget(StartSelfpushButton);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        ClassOverpushButton = new QPushButton(TeacherForm);
        ClassOverpushButton->setObjectName(QStringLiteral("ClassOverpushButton"));

        horizontalLayout_4->addWidget(ClassOverpushButton);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalSpacer_24 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_3->addItem(horizontalSpacer_24);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_9);

        SetClassNamelabel = new QLabel(TeacherForm);
        SetClassNamelabel->setObjectName(QStringLiteral("SetClassNamelabel"));

        horizontalLayout_5->addWidget(SetClassNamelabel);

        ClsaaNamecomboBox = new QComboBox(TeacherForm);
        ClsaaNamecomboBox->setObjectName(QStringLiteral("ClsaaNamecomboBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ClsaaNamecomboBox->sizePolicy().hasHeightForWidth());
        ClsaaNamecomboBox->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(ClsaaNamecomboBox);


        verticalLayout_3->addLayout(horizontalLayout_5);


        gridLayout->addLayout(verticalLayout_3, 3, 3, 1, 1);

        ClasstabWidget = new QTabWidget(TeacherForm);
        ClasstabWidget->setObjectName(QStringLiteral("ClasstabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_16, 1, 3, 1, 1);

        LeftpushButton = new QPushButton(tab);
        LeftpushButton->setObjectName(QStringLiteral("LeftpushButton"));

        gridLayout_2->addWidget(LeftpushButton, 1, 1, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_6);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        ClassNamelabel_1 = new ClassMould(tab,"NULL");
        ClassNamelabel_1->setObjectName(QStringLiteral("ClassNamelabel_1"));

        horizontalLayout_7->addWidget(ClassNamelabel_1);

        horizontalSpacer_34 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_34);

        horizontalSpacer_27 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_27);

        ClassNamelabel_2 = new ClassMould(tab,"NULL");
        ClassNamelabel_2->setObjectName(QStringLiteral("ClassNamelabel_2"));

        horizontalLayout_7->addWidget(ClassNamelabel_2);

        horizontalSpacer_35 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_35);

        horizontalSpacer_29 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_29);

        ClassNamelabel_3 = new ClassMould(tab,"NULL");
        ClassNamelabel_3->setObjectName(QStringLiteral("ClassNamelabel_3"));

        horizontalLayout_7->addWidget(ClassNamelabel_3);


        verticalLayout_4->addLayout(horizontalLayout_7);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_4);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_13);

        ClassBeginpushButton = new QPushButton(tab);
        ClassBeginpushButton->setObjectName(QStringLiteral("ClassBeginpushButton"));

        horizontalLayout_8->addWidget(ClassBeginpushButton);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_14);


        verticalLayout_4->addLayout(horizontalLayout_8);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_3);


        gridLayout_2->addLayout(verticalLayout_4, 1, 4, 1, 1);

        RightpushButton = new QPushButton(tab);
        RightpushButton->setObjectName(QStringLiteral("RightpushButton"));

        gridLayout_2->addWidget(RightpushButton, 1, 7, 1, 1);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_15, 1, 5, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_10, 1, 2, 1, 1);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_11, 1, 6, 1, 1);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_17, 1, 8, 1, 1);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_12, 1, 0, 1, 1);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_7, 2, 4, 1, 1);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_8, 0, 4, 1, 1);

        ClasstabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_3 = new QGridLayout(tab_2);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        TerminalscrollArea = new QScrollArea(tab_2);
        TerminalscrollArea->setObjectName(QStringLiteral("TerminalscrollArea"));
        TerminalscrollArea->setWidgetResizable(true);
        Student_scrollAreaWidgetContents = new QWidget();
        Student_scrollAreaWidgetContents->setObjectName(QStringLiteral("Student_scrollAreaWidgetContents"));
        Student_scrollAreaWidgetContents->setGeometry(QRect(0, 0, 810, 462));
        TerminalscrollArea->setWidget(Student_scrollAreaWidgetContents);

        gridLayout_3->addWidget(TerminalscrollArea, 0, 0, 1, 1);

        ClasstabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(ClasstabWidget, 4, 1, 1, 3);


        retranslateUi(TeacherForm);

        ClasstabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(TeacherForm);
    } // setupUi

    void retranslateUi(QWidget *TeacherForm)
    {
        TeacherForm->setWindowTitle(QApplication::translate("TeacherForm", "Form", 0));
        Logolabel->setText(QApplication::translate("TeacherForm", "Logo", 0));
        TeacherVMStatuslabel->setText(QApplication::translate("TeacherForm", "as", 0));
        RoomNumberlabel->setText(QApplication::translate("TeacherForm", "RoomNumberlabel", 0));
        TeacherNameLogolabel->setText(QApplication::translate("TeacherForm", "TeacherNameLogolabel", 0));
        TeacherNamelabel->setText(QApplication::translate("TeacherForm", "TeacherNamelabel", 0));
        BackpushButton->setText(QString());
        ClassNamelTitletabel->setText(QApplication::translate("TeacherForm", "ClassNamelabel", 0));
        ClassNameLogolabel->setText(QApplication::translate("TeacherForm", "TextLabel", 0));
        ClassNamelabel->setText(QApplication::translate("TeacherForm", "TextLabel", 0));
        SetClassNamelabel->setText(QApplication::translate("TeacherForm", "\347\217\255\347\272\247\345\220\215\347\247\260", 0));
        LeftpushButton->setText(QString());
        ClassBeginpushButton->setText(QString());
        RightpushButton->setText(QString());
        ClasstabWidget->setTabText(ClasstabWidget->indexOf(tab), QApplication::translate("TeacherForm", "Tab 1", 0));
        ClasstabWidget->setTabText(ClasstabWidget->indexOf(tab_2), QApplication::translate("TeacherForm", "Tab 2", 0));
    } // retranslateUi

};

namespace Ui {
    class TeacherForm: public Ui_TeacherForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEACHERFORM_H
