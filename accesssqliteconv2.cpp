#include "accesssqliteconv2.h"
#include<qsqldatabase.h>
#include<qsqlquery.h>
#include<qdebug.h>
#include<qsqlerror.h>
#include<QTextCodec>
#include<qsqlrecord.h>
#include<qsqlfield.h>
#include<qstring.h>
AccessSqliteConv2::AccessSqliteConv2(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
	init();
}
void AccessSqliteConv2::init()
{
	qDebug() << QSqlDatabase::drivers();
	QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");//
	//QString dsn = QString("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access};DBQ=C:/Users/CHENSHUAISHUAI/Desktop/asd.mdb");
	QString dsn = QString("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access};DBQ=C:/Users/WYF/Desktop/基础地理标准_500.mdb");
	db.setDatabaseName(dsn);
	if (db.open()) {
		qDebug()<< "success!成功";
		QStringList tables = db.tables();
		int num = 0;
		for (int i = 8; i < 9; i++)
		{			
				QSqlQuery query;
				query.exec("select * from " + tables[i]);

				QSqlRecord record = query.record();
				for (int j = 0; j < record.count(); j++)
				{
					QString fieldName = record.fieldName(j);
					qDebug() << fieldName;
				}
				qDebug() << "----------------";
				QSqlField  f= record.field(1);
				
				//qDebug()<<f.value().toString();
					
				//qDebug() << num++;
				while (query.next())
				{
					
					qDebug() << /*i*/ +": " << query.value(0).toString()
						<< query.value(1).toString()
						<< query.value(2).toString()
						<< query.value(3).toString()
						<< query.value(4).toString()
						<< query.value(5).toString();			
				}			
		}
		//qDebug() << tables;0.
		db.close();
		system("pause");
	}
	else {
		qDebug() << "false!";
	}

}