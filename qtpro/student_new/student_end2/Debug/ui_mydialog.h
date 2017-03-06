/********************************************************************************
** Form generated from reading UI file 'mydialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYDIALOG_H
#define UI_MYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyDialog
{
public:
    QFrame *title_bar;
    QPushButton *btnClose;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *OKpushButton;
    QPushButton *CancelpushButton;
    QSpacerItem *horizontalSpacer_2;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *Textlabel;

    void setupUi(QDialog *MyDialog)
    {
        if (MyDialog->objectName().isEmpty())
            MyDialog->setObjectName(QStringLiteral("MyDialog"));
        MyDialog->resize(469, 230);
        QFont font;
        font.setPointSize(14);
        MyDialog->setFont(font);
        title_bar = new QFrame(MyDialog);
        title_bar->setObjectName(QStringLiteral("title_bar"));
        title_bar->setGeometry(QRect(-8, -3, 481, 31));
        title_bar->setFrameShape(QFrame::StyledPanel);
        title_bar->setFrameShadow(QFrame::Raised);
        btnClose = new QPushButton(title_bar);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setGeometry(QRect(450, 10, 16, 13));
        btnClose->setStyleSheet(QStringLiteral("border-image: url(:/image1/x.png);"));
        horizontalLayoutWidget = new QWidget(MyDialog);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 150, 471, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        OKpushButton = new QPushButton(horizontalLayoutWidget);
        OKpushButton->setObjectName(QStringLiteral("OKpushButton"));

        horizontalLayout->addWidget(OKpushButton);

        CancelpushButton = new QPushButton(horizontalLayoutWidget);
        CancelpushButton->setObjectName(QStringLiteral("CancelpushButton"));

        horizontalLayout->addWidget(CancelpushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        horizontalLayoutWidget_2 = new QWidget(MyDialog);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(10, 30, 451, 111));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        Textlabel = new QLabel(horizontalLayoutWidget_2);
        Textlabel->setObjectName(QStringLiteral("Textlabel"));
        Textlabel->setFont(font);
        Textlabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(Textlabel);


        retranslateUi(MyDialog);

        QMetaObject::connectSlotsByName(MyDialog);
    } // setupUi

    void retranslateUi(QDialog *MyDialog)
    {
        MyDialog->setWindowTitle(QApplication::translate("MyDialog", "Dialog", Q_NULLPTR));
        btnClose->setText(QString());
        OKpushButton->setText(QString());
        CancelpushButton->setText(QString());
        Textlabel->setText(QApplication::translate("MyDialog", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MyDialog: public Ui_MyDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYDIALOG_H
