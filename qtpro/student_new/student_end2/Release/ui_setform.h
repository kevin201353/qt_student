/********************************************************************************
** Form generated from reading UI file 'setform.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETFORM_H
#define UI_SETFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetForm
{
public:
    QGridLayout *gridLayout;
    QTabWidget *SetTabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QGroupBox *IPgroupBox;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QRadioButton *AutoSetIPradioButton;
    QRadioButton *ManualSetIPradioButton;
    QHBoxLayout *horizontalLayout_2;
    QLabel *IPlabel;
    QLineEdit *IPlineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *ChildIPlabel;
    QLineEdit *ChildIPlineEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *GetWaylabel;
    QLineEdit *GetWaylineEdit;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *DNSgroupBox;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *AutoSetDNSradioButton;
    QRadioButton *ManualSetDNSradioButton;
    QHBoxLayout *horizontalLayout_5;
    QLabel *DNS1label;
    QLineEdit *DNS1lineEdit;
    QHBoxLayout *horizontalLayout_6;
    QLabel *DNS2label;
    QLineEdit *DNS2lineEdit;
    QHBoxLayout *horizontalLayout_7;
    QLabel *DNS3label;
    QLineEdit *DNS3lineEdit;
    QSpacerItem *horizontalSpacer_5;
    QWidget *tab_2;
    QGridLayout *gridLayout_5;
    QLabel *ServerIPlabel;
    QLineEdit *ServerIPlineEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *SavepushButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *CancelpushButton;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *SetForm)
    {
        if (SetForm->objectName().isEmpty())
            SetForm->setObjectName(QStringLiteral("SetForm"));
        SetForm->resize(724, 516);
        gridLayout = new QGridLayout(SetForm);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        SetTabWidget = new QTabWidget(SetForm);
        SetTabWidget->setObjectName(QStringLiteral("SetTabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        IPgroupBox = new QGroupBox(tab);
        IPgroupBox->setObjectName(QStringLiteral("IPgroupBox"));
        gridLayout_2 = new QGridLayout(IPgroupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        AutoSetIPradioButton = new QRadioButton(IPgroupBox);
        AutoSetIPradioButton->setObjectName(QStringLiteral("AutoSetIPradioButton"));
        AutoSetIPradioButton->setEnabled(true);

        verticalLayout->addWidget(AutoSetIPradioButton);

        ManualSetIPradioButton = new QRadioButton(IPgroupBox);
        ManualSetIPradioButton->setObjectName(QStringLiteral("ManualSetIPradioButton"));

        verticalLayout->addWidget(ManualSetIPradioButton);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        IPlabel = new QLabel(IPgroupBox);
        IPlabel->setObjectName(QStringLiteral("IPlabel"));

        horizontalLayout_2->addWidget(IPlabel);

        IPlineEdit = new QLineEdit(IPgroupBox);
        IPlineEdit->setObjectName(QStringLiteral("IPlineEdit"));

        horizontalLayout_2->addWidget(IPlineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        ChildIPlabel = new QLabel(IPgroupBox);
        ChildIPlabel->setObjectName(QStringLiteral("ChildIPlabel"));

        horizontalLayout_3->addWidget(ChildIPlabel);

        ChildIPlineEdit = new QLineEdit(IPgroupBox);
        ChildIPlineEdit->setObjectName(QStringLiteral("ChildIPlineEdit"));

        horizontalLayout_3->addWidget(ChildIPlineEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        GetWaylabel = new QLabel(IPgroupBox);
        GetWaylabel->setObjectName(QStringLiteral("GetWaylabel"));

        horizontalLayout_4->addWidget(GetWaylabel);

        GetWaylineEdit = new QLineEdit(IPgroupBox);
        GetWaylineEdit->setObjectName(QStringLiteral("GetWaylineEdit"));

        horizontalLayout_4->addWidget(GetWaylineEdit);


        verticalLayout->addLayout(horizontalLayout_4);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 0, 1, 1, 1);


        gridLayout_3->addWidget(IPgroupBox, 0, 0, 1, 1);

        DNSgroupBox = new QGroupBox(tab);
        DNSgroupBox->setObjectName(QStringLiteral("DNSgroupBox"));
        gridLayout_4 = new QGridLayout(DNSgroupBox);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        AutoSetDNSradioButton = new QRadioButton(DNSgroupBox);
        AutoSetDNSradioButton->setObjectName(QStringLiteral("AutoSetDNSradioButton"));

        verticalLayout_2->addWidget(AutoSetDNSradioButton);

        ManualSetDNSradioButton = new QRadioButton(DNSgroupBox);
        ManualSetDNSradioButton->setObjectName(QStringLiteral("ManualSetDNSradioButton"));

        verticalLayout_2->addWidget(ManualSetDNSradioButton);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        DNS1label = new QLabel(DNSgroupBox);
        DNS1label->setObjectName(QStringLiteral("DNS1label"));

        horizontalLayout_5->addWidget(DNS1label);

        DNS1lineEdit = new QLineEdit(DNSgroupBox);
        DNS1lineEdit->setObjectName(QStringLiteral("DNS1lineEdit"));

        horizontalLayout_5->addWidget(DNS1lineEdit);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        DNS2label = new QLabel(DNSgroupBox);
        DNS2label->setObjectName(QStringLiteral("DNS2label"));

        horizontalLayout_6->addWidget(DNS2label);

        DNS2lineEdit = new QLineEdit(DNSgroupBox);
        DNS2lineEdit->setObjectName(QStringLiteral("DNS2lineEdit"));

        horizontalLayout_6->addWidget(DNS2lineEdit);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        DNS3label = new QLabel(DNSgroupBox);
        DNS3label->setObjectName(QStringLiteral("DNS3label"));

        horizontalLayout_7->addWidget(DNS3label);

        DNS3lineEdit = new QLineEdit(DNSgroupBox);
        DNS3lineEdit->setObjectName(QStringLiteral("DNS3lineEdit"));

        horizontalLayout_7->addWidget(DNS3lineEdit);


        verticalLayout_2->addLayout(horizontalLayout_7);


        gridLayout_4->addLayout(verticalLayout_2, 0, 0, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_5, 0, 1, 1, 1);


        gridLayout_3->addWidget(DNSgroupBox, 1, 0, 1, 1);

        SetTabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_5 = new QGridLayout(tab_2);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        ServerIPlabel = new QLabel(tab_2);
        ServerIPlabel->setObjectName(QStringLiteral("ServerIPlabel"));

        gridLayout_5->addWidget(ServerIPlabel, 0, 0, 1, 1);

        ServerIPlineEdit = new QLineEdit(tab_2);
        ServerIPlineEdit->setObjectName(QStringLiteral("ServerIPlineEdit"));

        gridLayout_5->addWidget(ServerIPlineEdit, 0, 1, 1, 1);

        SetTabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(SetTabWidget, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        SavepushButton = new QPushButton(SetForm);
        SavepushButton->setObjectName(QStringLiteral("SavepushButton"));

        horizontalLayout->addWidget(SavepushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        CancelpushButton = new QPushButton(SetForm);
        CancelpushButton->setObjectName(QStringLiteral("CancelpushButton"));

        horizontalLayout->addWidget(CancelpushButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(SetForm);

        SetTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SetForm);
    } // setupUi

    void retranslateUi(QWidget *SetForm)
    {
        SetForm->setWindowTitle(QApplication::translate("SetForm", "Form", Q_NULLPTR));
        IPgroupBox->setTitle(QApplication::translate("SetForm", "GroupBox", Q_NULLPTR));
        AutoSetIPradioButton->setText(QApplication::translate("SetForm", "DHCP", Q_NULLPTR));
        ManualSetIPradioButton->setText(QApplication::translate("SetForm", "Static", Q_NULLPTR));
        IPlabel->setText(QApplication::translate("SetForm", "\347\275\221\347\273\234\345\234\260\345\235\200", Q_NULLPTR));
        ChildIPlabel->setText(QApplication::translate("SetForm", "\345\255\220\347\275\221\346\216\251\347\240\201", Q_NULLPTR));
        GetWaylabel->setText(QApplication::translate("SetForm", "\347\275\221\345\205\263\345\234\260\345\235\200", Q_NULLPTR));
        DNSgroupBox->setTitle(QApplication::translate("SetForm", "GroupBox", Q_NULLPTR));
        AutoSetDNSradioButton->setText(QApplication::translate("SetForm", "DHCP", Q_NULLPTR));
        ManualSetDNSradioButton->setText(QApplication::translate("SetForm", "Static", Q_NULLPTR));
        DNS1label->setText(QApplication::translate("SetForm", "DNS1", Q_NULLPTR));
        DNS2label->setText(QApplication::translate("SetForm", "DNS2", Q_NULLPTR));
        DNS3label->setText(QApplication::translate("SetForm", "DNS3", Q_NULLPTR));
        SetTabWidget->setTabText(SetTabWidget->indexOf(tab), QApplication::translate("SetForm", "Tab 1", Q_NULLPTR));
        ServerIPlabel->setText(QApplication::translate("SetForm", "\346\234\215\345\212\241\345\231\250IP", Q_NULLPTR));
        SetTabWidget->setTabText(SetTabWidget->indexOf(tab_2), QApplication::translate("SetForm", "Tab 2", Q_NULLPTR));
        SavepushButton->setText(QApplication::translate("SetForm", "Save", Q_NULLPTR));
        CancelpushButton->setText(QApplication::translate("SetForm", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SetForm: public Ui_SetForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETFORM_H
