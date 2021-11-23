#ifndef NTACCESSMANAGER_H
#define NTACCESSMANAGER_H

#include <QString>
#include<qstringlist.h>
class NtAccessManager
{
public:
	NtAccessManager();

	/**
	* @brief 获取Access数据库中所有的表
	* @param mdbPath 数据库文件路径
	* @param tableList 输出参数 表列表
	*/
	void getAccessTableList(QString mdbPath, QStringList &tableList);

	/**
	* @brief 获取Access数据库中某个表所有的字段
	* @param mdbPath 数据库文件路径
	* @param targetTable 目标表名称
	* @param filedList 输出参数 字段列表
	*/
	void getAccessFieldList(QString mdbPath, QString targetTable, QStringList &filedList);


	/**
	* @brief 获取Access数据库中某个表中的所有数据
	* @param mdbPath 数据库文件路径
	* @param targetTable 目标表名称
	* @param data 输出参数 key：字段名称  value：该字段下所有的值
	*/
	void getAccessData(QString mdbPath, QString targetTable, QMap<QString, QVector<QString> > &data, QString sortField = QString(), bool asc = true);


	/**
	* @brief delTabelDataByID : 从指定表格删除指定编号的电路
	* @param mdbPath : mdb文件所在的路径
	* @param targetTable ： 目标表名
	* @param id : 电路ID
	*/
	void delTabelDataByID(QString mdbPath, QString targetTable, QString condition);


private:
	QStringList filedList;

};

#endif // NTACCESSMANAGER_H