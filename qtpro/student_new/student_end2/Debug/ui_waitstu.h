/********************************************************************************
** Form generated from reading UI file 'waitstu.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WAITSTU_H
#define UI_WAITSTU_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_waitstu
{
public:

    void setupUi(QFrame *waitstu)
    {
        if (waitstu->objectName().isEmpty())
            waitstu->setObjectName(QStringLiteral("waitstu"));
        waitstu->setWindowModality(Qt::NonModal);
        waitstu->resize(400, 300);
        waitstu->setAutoFillBackground(true);
        waitstu->setStyleSheet(QStringLiteral(""));
        waitstu->setFrameShape(QFrame::NoFrame);
        waitstu->setFrameShadow(QFrame::Raised);

        retranslateUi(waitstu);

        QMetaObject::connectSlotsByName(waitstu);
    } // setupUi

    void retranslateUi(QFrame *waitstu)
    {
        waitstu->setWindowTitle(QApplication::translate("waitstu", "Frame", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class waitstu: public Ui_waitstu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WAITSTU_H
