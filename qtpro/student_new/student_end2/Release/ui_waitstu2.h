/********************************************************************************
** Form generated from reading UI file 'waitstu2.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WAITSTU2_H
#define UI_WAITSTU2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_waitstu2
{
public:

    void setupUi(QWidget *waitstu2)
    {
        if (waitstu2->objectName().isEmpty())
            waitstu2->setObjectName(QStringLiteral("waitstu2"));
        waitstu2->resize(400, 300);
        waitstu2->setAutoFillBackground(true);

        retranslateUi(waitstu2);

        QMetaObject::connectSlotsByName(waitstu2);
    } // setupUi

    void retranslateUi(QWidget *waitstu2)
    {
        waitstu2->setWindowTitle(QApplication::translate("waitstu2", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class waitstu2: public Ui_waitstu2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WAITSTU2_H
