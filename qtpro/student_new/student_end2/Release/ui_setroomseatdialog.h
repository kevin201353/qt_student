/********************************************************************************
** Form generated from reading UI file 'setroomseatdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETROOMSEATDIALOG_H
#define UI_SETROOMSEATDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SetRoomSeatDialog
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *RoomNumlabel;
    QLineEdit *RoomNumlineEdit;
    QHBoxLayout *horizontalLayout;
    QLabel *SeatNumlabel;
    QLineEdit *SeatNumlineEdit;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *OKpushButton;
    QPushButton *CancelpushButton;

    void setupUi(QDialog *SetRoomSeatDialog)
    {
        if (SetRoomSeatDialog->objectName().isEmpty())
            SetRoomSeatDialog->setObjectName(QStringLiteral("SetRoomSeatDialog"));
        SetRoomSeatDialog->resize(375, 222);
        gridLayout = new QGridLayout(SetRoomSeatDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        RoomNumlabel = new QLabel(SetRoomSeatDialog);
        RoomNumlabel->setObjectName(QStringLiteral("RoomNumlabel"));

        horizontalLayout_2->addWidget(RoomNumlabel);

        RoomNumlineEdit = new QLineEdit(SetRoomSeatDialog);
        RoomNumlineEdit->setObjectName(QStringLiteral("RoomNumlineEdit"));

        horizontalLayout_2->addWidget(RoomNumlineEdit);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        SeatNumlabel = new QLabel(SetRoomSeatDialog);
        SeatNumlabel->setObjectName(QStringLiteral("SeatNumlabel"));

        horizontalLayout->addWidget(SeatNumlabel);

        SeatNumlineEdit = new QLineEdit(SetRoomSeatDialog);
        SeatNumlineEdit->setObjectName(QStringLiteral("SeatNumlineEdit"));

        horizontalLayout->addWidget(SeatNumlineEdit);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        OKpushButton = new QPushButton(SetRoomSeatDialog);
        OKpushButton->setObjectName(QStringLiteral("OKpushButton"));

        horizontalLayout_3->addWidget(OKpushButton);

        CancelpushButton = new QPushButton(SetRoomSeatDialog);
        CancelpushButton->setObjectName(QStringLiteral("CancelpushButton"));

        horizontalLayout_3->addWidget(CancelpushButton);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);


        retranslateUi(SetRoomSeatDialog);

        QMetaObject::connectSlotsByName(SetRoomSeatDialog);
    } // setupUi

    void retranslateUi(QDialog *SetRoomSeatDialog)
    {
        SetRoomSeatDialog->setWindowTitle(QApplication::translate("SetRoomSeatDialog", "Dialog", Q_NULLPTR));
        RoomNumlabel->setText(QApplication::translate("SetRoomSeatDialog", "TextLabel", Q_NULLPTR));
        SeatNumlabel->setText(QApplication::translate("SetRoomSeatDialog", "TextLabel", Q_NULLPTR));
        OKpushButton->setText(QApplication::translate("SetRoomSeatDialog", "PushButton", Q_NULLPTR));
        CancelpushButton->setText(QApplication::translate("SetRoomSeatDialog", "PushButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SetRoomSeatDialog: public Ui_SetRoomSeatDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETROOMSEATDIALOG_H
