/********************************************************************************
** Form generated from reading UI file 'loadingframe.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADINGFRAME_H
#define UI_LOADINGFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_LoadingFrame
{
public:
    QGridLayout *gridLayout;
    QLabel *GIFlabel;
    QLabel *label;
    QSpacerItem *horizontalSpacer;

    void setupUi(QFrame *LoadingFrame)
    {
        if (LoadingFrame->objectName().isEmpty())
            LoadingFrame->setObjectName(QStringLiteral("LoadingFrame"));
        LoadingFrame->resize(269, 154);
        LoadingFrame->setFrameShape(QFrame::StyledPanel);
        LoadingFrame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(LoadingFrame);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        GIFlabel = new QLabel(LoadingFrame);
        GIFlabel->setObjectName(QStringLiteral("GIFlabel"));

        gridLayout->addWidget(GIFlabel, 1, 0, 1, 1);

        label = new QLabel(LoadingFrame);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 2, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);


        retranslateUi(LoadingFrame);

        QMetaObject::connectSlotsByName(LoadingFrame);
    } // setupUi

    void retranslateUi(QFrame *LoadingFrame)
    {
        LoadingFrame->setWindowTitle(QApplication::translate("LoadingFrame", "Frame", Q_NULLPTR));
        GIFlabel->setText(QApplication::translate("LoadingFrame", "GIF", Q_NULLPTR));
        label->setText(QApplication::translate("LoadingFrame", "\350\257\267\347\250\215\344\276\257", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LoadingFrame: public Ui_LoadingFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADINGFRAME_H
