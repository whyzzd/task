/********************************************************************************
** Form generated from reading UI file 'accesssqliteconv.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACCESSSQLITECONV_H
#define UI_ACCESSSQLITECONV_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AccessSqliteConvClass
{
public:

    void setupUi(QWidget *AccessSqliteConvClass)
    {
        if (AccessSqliteConvClass->objectName().isEmpty())
            AccessSqliteConvClass->setObjectName(QStringLiteral("AccessSqliteConvClass"));
        AccessSqliteConvClass->resize(600, 400);

        retranslateUi(AccessSqliteConvClass);

        QMetaObject::connectSlotsByName(AccessSqliteConvClass);
    } // setupUi

    void retranslateUi(QWidget *AccessSqliteConvClass)
    {
        AccessSqliteConvClass->setWindowTitle(QApplication::translate("AccessSqliteConvClass", "AccessSqliteConv", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AccessSqliteConvClass: public Ui_AccessSqliteConvClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACCESSSQLITECONV_H
