#include <QAxObject>
#include <QVector>
#include "qt_windows.h"
#include "ado.h"
#include "ntaccessmanager.h"
#include<qdebug.h>
NtAccessManager::NtAccessManager()
{

}

void NtAccessManager::getAccessTableList(QString mdbPath, QStringList &tableList)
{
	HRESULT r = OleInitialize(0);
	if (r != S_OK && r != S_FALSE) {
		qWarning("Qt: Could not initialize OLE (error %x)", (unsigned int)r);
		
	}
	
	QAxObject *connection = new QAxObject;
	connection->setControl("ADODB.Connection");/*创建ADODB.Connection对象*/
	connection->setProperty("ConnectionTimeout", 300);/*设置超时时间确保连接成功*/
	QString connectString = QString("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%1;").arg(mdbPath);
	//打开连接
	HRESULT hr =
		connection->dynamicCall("Open(QString,QString,QString,int)", connectString, "", "", adConnectUnspecified).toInt(); /*连接到数据库*/
	//qDebug() << mdbPath;
	if (SUCCEEDED(hr))
	{
		
		//查询有关数据源的schema信息
		QAxObject *recordSet = connection->querySubObject("OpenSchema(SchemaEnum)", adSchemaTables);
		
		if (recordSet)
		{
			
			while (!recordSet->property("EOF").toBool())
			{
				QAxObject * adoFields = recordSet->querySubObject("Fields");
				if (adoFields)
				{
					int count = adoFields->property("Count").toInt();
					QString tableName = "";
					QString tableType = "";
					//从字段列表中获取表名和表类型
					for (int i = 0; i < count; i++)
					{
						QAxObject * adoField = adoFields->querySubObject("Item(int)", i);
						if (adoField)
						{
							QString name = adoField->property("Name").toString();
							QVariant value = adoField->property("Value");
							if (name == "TABLE_NAME")
							{
								tableName = value.toString();
							}
							else if (name == "TABLE_TYPE")
							{
								tableType = value.toString();
							}
							ADO_DELETE(adoField);
						}
					}
					//判断表类型为TABLE时，该表为用户添加的表，将该表名插入到表列表中
					if (tableType == "TABLE")
						tableList.append(tableName);
					ADO_DELETE(adoFields);
				}
				//移动至下一条记录
				recordSet->dynamicCall("MoveNext");
			}
			ADO_DELETE(recordSet);
		}
		//关闭连接
		connection->dynamicCall("Close");
		delete connection;
		connection = NULL;
		OleUninitialize();
	}
}

void NtAccessManager::getAccessFieldList(QString mdbPath, QString targetTable, QStringList &filedList)
{
	HRESULT r = OleInitialize(0);
	if (r != S_OK && r != S_FALSE) {
		qWarning("Qt: Could not initialize OLE (error %x)", (unsigned int)r);
	}

	QAxObject *connection = new QAxObject;
	connection->setControl("ADODB.Connection");/*创建ADODB.Connection对象*/
	connection->setProperty("ConnectionTimeout", 300);/*设置超时时间确保连接成功*/
	QString connectString = QString("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%1;")
		.arg(mdbPath);
	HRESULT hr =
		connection->dynamicCall("Open(QString,QString,QString,int)", connectString, "", "", adConnectUnspecified).toInt(); /*连接到数据库*/
	if (SUCCEEDED(hr))
	{
		QString sqlStr = QString("select * from %1").arg(targetTable);
		QAxObject *recordSet = connection->querySubObject("Execute(QString, QVariant&, int)", sqlStr);
		if (recordSet && !recordSet->property("EOF").toBool())
		{
			QAxObject * adoFields = recordSet->querySubObject("Fields");
			if (adoFields)
			{
				int count = adoFields->property("Count").toInt();
				for (int i = 0; i < count; i++)
				{
					QAxObject * adoField = adoFields->querySubObject("Item(int)", i);
					if (adoField)
					{
						QString name = adoField->property("Name").toString();
						filedList.append(name);
						ADO_DELETE(adoField);
					}
				}
				ADO_DELETE(adoFields);
			}

			ADO_DELETE(recordSet);
		}

		connection->dynamicCall("Close");
		delete connection;
		connection = NULL;
		OleUninitialize();
	}
}

void NtAccessManager::getAccessData(QString mdbPath, QString targetTable, QMap<QString, QVector<QString> > &data, QString sortField, bool asc)
{
	HRESULT r = OleInitialize(0);
	if (r != S_OK && r != S_FALSE) {
		qWarning("Qt: Could not initialize OLE (error %x)", (unsigned int)r);
	}
	QAxObject *connection = new QAxObject;
	connection->setControl("ADODB.Connection");/*创建ADODB.Connection对象*/
	connection->setProperty("ConnectionTimeout", 300);/*设置超时时间确保连接成功*/
	QString connectString = QString("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%1;")
		.arg(mdbPath);
	HRESULT hr =
		connection->dynamicCall("Open(QString,QString,QString,int)", connectString, "", "", adConnectUnspecified).toInt(); /*连接到数据库*/
	if (SUCCEEDED(hr))
	{
		QString orderStr = "";
		if (sortField.length() != 0)
			orderStr = QString(" order by %1 %2").arg(sortField).arg(asc ? "asc" : "desc");
		QString sqlStr = QString("select * from %1 %2").arg(targetTable).arg(orderStr);
		QAxObject *recordSet = connection->querySubObject("Execute(QString, QVariant&, int)", sqlStr);
		if (recordSet)
		{
			while (!recordSet->property("EOF").toBool())
			{
				QAxObject * adoFields = recordSet->querySubObject("Fields");
				if (adoFields)
				{
					int count = adoFields->property("Count").toInt();
					for (int i = 0; i < count; i++)
					{
						QAxObject * adoField = adoFields->querySubObject("Item(int)", i);
						if (adoField)
						{
							QString fieldName = adoField->property("Name").toString();
							QVariant fieldValueVar = adoField->property("Value");
							QString fieldValue = fieldValueVar.isValid() ? fieldValueVar.toString() : "";
							QVector<QString> values;
							if (data.contains(fieldName))
								values = data.value(fieldName);
							values.append(fieldValue);
							data.insert(fieldName, values);
							ADO_DELETE(adoField);
						}
					}
					ADO_DELETE(adoFields);
				}

				//移动至下一条记录
				recordSet->dynamicCall("MoveNext");
			}
			ADO_DELETE(recordSet);
		}
		connection->dynamicCall("Close");
		delete connection;
		connection = NULL;
		OleUninitialize();
	}
}

void NtAccessManager::delTabelDataByID(QString mdbPath, QString targetTable, QString condition)
{
	HRESULT r = OleInitialize(0);
	if (r != S_OK && r != S_FALSE) {
		qWarning("Qt: Could not initialize OLE (error %x)", (unsigned int)r);
	}

	QAxObject *connection = new QAxObject;
	connection->setControl("ADODB.Connection");/*创建ADODB.Connection对象*/
	connection->setProperty("ConnectionTimeout", 300);/*设置超时时间确保连接成功*/
	QString connectString = QString("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%1;")
		.arg(mdbPath);
	HRESULT hr =
		connection->dynamicCall("Open(QString,QString,QString,int)", connectString, "", "", adConnectUnspecified).toInt(); /*连接到数据库*/
	if (SUCCEEDED(hr))
	{
		//QString sqlStr = QString("select * from %1").arg(targetTable);
		QString sqlStr = QString("DELETE FROM %1 where 样品编号 in (%2)").arg(targetTable).arg(condition);
		QAxObject *recordSet = connection->querySubObject("Execute(QString, QVariant&, int)", sqlStr);
		if (recordSet && !recordSet->property("EOF").toBool())
		{
			ADO_DELETE(recordSet);
		}

		connection->dynamicCall("Close");
		delete connection;
		connection = NULL;
		OleUninitialize();
	}
}