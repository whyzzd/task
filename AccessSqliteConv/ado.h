/*File: ado.h 关于ADO的一些定义*/
#ifndef ADO_H
#define ADO_H

#include <QAxObject>
#include <QFile>
#include <QTextStream>

#define adConnectUnspecified -1

#define adStateClosed 0

#define adOpenStatic  3
#define adOpenDynamic 2

#define adLockOptimistic 3

#define adCmdText 1

#define adSchemaTables 20

typedef long HRESULT;

#define SUCCEEDED(hr) ((HRESULT)(hr) >= 0)
#define FAILED(hr)    ((HRESULT)(hr) < 0)

#define ADO_DELETE(p) do{if(p) delete (p); (p)=0;}while(0)

class ADO {

public:
	static void outPutDocument(QString doc, QString fileName)
	{

		QFile outFile(fileName);

		outFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
		QTextStream ts(&outFile);

		ts << doc << endl;
		outFile.close();
	}
};

#endif // ADO