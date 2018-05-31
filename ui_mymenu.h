/********************************************************************************
** Form generated from reading UI file 'mymenu.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYMENU_H
#define UI_MYMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_mymenu
{
public:

    void setupUi(QDialog *mymenu)
    {
        if (mymenu->objectName().isEmpty())
            mymenu->setObjectName(QStringLiteral("mymenu"));
        mymenu->resize(400, 300);

        retranslateUi(mymenu);

        QMetaObject::connectSlotsByName(mymenu);
    } // setupUi

    void retranslateUi(QDialog *mymenu)
    {
        mymenu->setWindowTitle(QApplication::translate("mymenu", "mymenu", 0));
    } // retranslateUi

};

namespace Ui {
    class mymenu: public Ui_mymenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYMENU_H
