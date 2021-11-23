#pragma once

#include <QtWidgets/QWidget>
#include "ui_accesssqliteconv.h"

class AccessSqliteConv : public QWidget
{
    Q_OBJECT

public:
    AccessSqliteConv(QWidget *parent = Q_NULLPTR);

private:
    Ui::AccessSqliteConvClass ui;
};
