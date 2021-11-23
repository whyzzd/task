#include "accesssqliteconv.h"
#include<qsqldatabase.h>
#include<qsqlquery.h>
#include<qdebug.h>
#include<qsqlerror.h>
#include<qsqlrecord.h>
#include<qtextcodec.h>
AccessSqliteConv::AccessSqliteConv(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	init();
}

void AccessSqliteConv::init()
{
	
	QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");//
	//qDebug() << QSqlDatabase::drivers();
	qDebug()<< db.lastError();
	//QString dsn = QString("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access};DBQ=C:/Users/CHENSHUAISHUAI/Desktop/asd.mdb");
	QString dsn = QString("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access};DBQ=C:/Users/CHENSHUAISHUAI/Desktop/基础地理标准_500.mdb");
	db.setDatabaseName(dsn);
	if (db.open()) {
		//qDebug()<< "success!成功";
	
		mTables = db.tables();
		for (int i = 0; i < mTables.size(); i++)
		{
			//QString utf8Str = QString::fromLocal8Bit(mTables[i].toLatin1());
			//qDebug() << mTables[i].toUtf8().data();
		}

		/*QTextCodec *pcode = QTextCodec::codecForName("GBK");
		QTextCodec::setCodecForLocale(pcode);*/
		qDebug() << mTables;
		/*QSqlQuery query;
		
		query.exec("select * from [共用宗地]");
		qDebug()<<query.record().fieldName(1);*/
		
		for (int i = 0; i < 8/*mTables.size()*/; i++)
		{
			QSqlQuery query;
			query.exec("select * from " + QString("["+mTables[i]+"]"));

			QSqlRecord record = query.record();
			QStringList fieldNameList;//存放字段??
			int num = record.count();
			for (int j = 0; j < num; j++)
			{
				QString fieldName = record.fieldName(j);
				fieldNameList << fieldName;//遍历一次放一??

				//qDebug() << fieldName;
			}
			mTableData.insert(mTables[i], fieldNameList);
			/*qDebug() << "----------------";
			QSqlField  f = record.field(1);
			qDebug()<<f.value().toString();
			qDebug() << num++;*/

			
			QVector<QStringList> fieldValList(num);
			//qDebug() << num;
			while (query.next())
			{				
				for (int k = 0; k < num; k++)
				{
					//将字段值保??
					fieldValList[k] << query.value(k).toString();
					
				}
				//qDebug() << /*i*/ +": " << query.value(0).toString()
				//	<< query.value(1).toString()
				//	<< query.value(2).toString()
				//	<< query.value(3).toString()
				//	<< query.value(4).toString()
				//	<< query.value(5).toString();
			}
			//将字段名和字段值对??此循环结束即可完成一张表的存??
			for (int j = 0; j < num; j++)
			{
				mFieldData.insert(fieldNameList[j], fieldValList[j]);
			}			
		}		
		db.close();
		system("pause");
		return;				
	}
	else {
		qDebug()<< "false!";
	}
}

void toSqlite(const QHash<QString, QStringList>&fieldData)
{

}