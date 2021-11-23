#ifndef NTACCESSMANAGER_H
#define NTACCESSMANAGER_H

#include <QString>
#include<qstringlist.h>
class NtAccessManager
{
public:
	NtAccessManager();

	/**
	* @brief ��ȡAccess���ݿ������еı�
	* @param mdbPath ���ݿ��ļ�·��
	* @param tableList ������� ���б�
	*/
	void getAccessTableList(QString mdbPath, QStringList &tableList);

	/**
	* @brief ��ȡAccess���ݿ���ĳ�������е��ֶ�
	* @param mdbPath ���ݿ��ļ�·��
	* @param targetTable Ŀ�������
	* @param filedList ������� �ֶ��б�
	*/
	void getAccessFieldList(QString mdbPath, QString targetTable, QStringList &filedList);


	/**
	* @brief ��ȡAccess���ݿ���ĳ�����е���������
	* @param mdbPath ���ݿ��ļ�·��
	* @param targetTable Ŀ�������
	* @param data ������� key���ֶ�����  value�����ֶ������е�ֵ
	*/
	void getAccessData(QString mdbPath, QString targetTable, QMap<QString, QVector<QString> > &data, QString sortField = QString(), bool asc = true);


	/**
	* @brief delTabelDataByID : ��ָ�����ɾ��ָ����ŵĵ�·
	* @param mdbPath : mdb�ļ����ڵ�·��
	* @param targetTable �� Ŀ�����
	* @param id : ��·ID
	*/
	void delTabelDataByID(QString mdbPath, QString targetTable, QString condition);


private:
	QStringList filedList;

};

#endif // NTACCESSMANAGER_H