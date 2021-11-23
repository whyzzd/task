#include "accesssqliteconv.h"
#include"ntaccessmanager.h"
#include<qdebug.h>
AccessSqliteConv::AccessSqliteConv(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	NtAccessManager ntam;
	QStringList list;

	QString pathStr = QString("C:/Users/CHENSHUAISHUAI/Desktop/asd.mdb");
	ntam.getAccessTableList(pathStr, list);
	qDebug() << list;
}
