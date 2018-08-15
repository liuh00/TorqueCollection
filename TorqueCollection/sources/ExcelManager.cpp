#include "ExcelManager.h"
#include <QAxObject>
#include <QFile>
#include <QDir>
#include <QMessageBox>


ExcelManager::ExcelManager(QObject* parent)
	: QObject(parent)
{
}

ExcelManager::~ExcelManager()
{
}

QString ExcelManager::getProduct() const
{
	return product;
}

void ExcelManager::setProduct(const QString& q_char)
{
	product = q_char;
}

QString ExcelManager::getNo() const
{
	return no;
}

void ExcelManager::setNo(const QString& q_char)
{
	no = q_char;
}

QString ExcelManager::getEnGname() const
{
	return ENGname;
}

void ExcelManager::setEnGname(const QString& en_gname)
{
	ENGname = en_gname;
}

QString ExcelManager::getMouth() const
{
	return mouth;
}

void ExcelManager::setMouth(const QString& q_char)
{
	mouth = q_char;
}

QString ExcelManager::getParameterDir() const
{
	return parameterDir;
}

void ExcelManager::setParameterDir(const QString& parameter_dir)
{
	parameterDir = parameter_dir;
}

void ExcelManager::printTable()
{
	QString dirName = parameterDir + "/" + product;
	QDir dir(dirName);

	if (!dir.exists())
	{
		QMessageBox::warning(Q_NULLPTR, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("目录不存在"));
		return;
	}

	QString fileName = dirName + "/" + product + ".xls";
	QFile file(fileName);

	if (!file.exists())
	{
		QMessageBox::warning(Q_NULLPTR, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("文件不存在"));
		return;
	}

	QAxObject* obj = new QAxObject("Excel.Application", this);

	if (obj == Q_NULLPTR)
	{
		QMessageBox::warning(Q_NULLPTR, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("Excel.Application调用错误。"));
		return;
	}

	obj->setProperty("Visible", false);
	obj->setProperty("DisplayAlerts", false);//不显示任何警告信息。


	QAxObject* workbooks = obj->querySubObject("Workbooks");

	if (workbooks == Q_NULLPTR)
	{
		QMessageBox::warning(Q_NULLPTR, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("workbooks获取错误。"));
		obj->dynamicCall("Quit(void)");
		delete obj;
		return;
	}

	QAxObject* workbook = workbooks->querySubObject("Open(QString)", QDir::toNativeSeparators(fileName));

	if (workbook == Q_NULLPTR)
	{
		QMessageBox::warning(Q_NULLPTR, QString::fromLocal8Bit("错误"), product + ".xls" + QString::fromLocal8Bit("文件打开获取错误."));
		workbooks->dynamicCall("Close(bool)", true);
		obj->dynamicCall("Quit(void)");
		delete workbooks;
		delete obj;
		return;
	}

	QAxObject* sheets = workbook->querySubObject("Sheets");
	QAxObject* workSheet = sheets->querySubObject("Item(QString)", "List");


	if (workSheet == Q_NULLPTR)
	{
		QMessageBox::warning(Q_NULLPTR, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("List表获取错误."));
		workbooks->dynamicCall("Close(bool)", true);
		obj->dynamicCall("Quit(void)");
		delete sheets;
		delete workbooks;
		delete obj;
		return;
	}
	//获取标题
	QVariant var;
	QList<QList<QVariant>> res;
	QVariant titleVar;
	QVariant titleVarList;
	QAxObject* qcosTabletitleRange = workSheet->querySubObject("Rows(int)", 2);

	if (qcosTabletitleRange != Q_NULLPTR)
	{
		//获取QCOSTable数据
		titleVar = qcosTabletitleRange->dynamicCall("Value");
		titleVarList = titleVar.toList();

		QAxObject* qcosTableRange = workSheet->querySubObject("Range(QString)", "QCOSTable");
		if (qcosTableRange != Q_NULLPTR)
		{
			var = qcosTableRange->dynamicCall("Value");
			variantTovariantList(var, res);
			delete qcosTableRange;
		}
		delete qcosTabletitleRange;


	}


	workbooks->dynamicCall("Close(bool)", true);
	obj->dynamicCall("Quit(void)");


	delete workSheet;
	delete sheets;
	delete workbooks;
	delete obj;
}

void ExcelManager::variantTovariantList(const QVariant& var, QList<QList<QVariant>>& res)
{
	QVariantList varRows = var.toList();
	if (varRows.isEmpty())
	{
		return;
	}
	const int rowCount = varRows.size();
	QVariantList rowData;
	for (int i = 0; i < rowCount; ++i)
	{
		rowData = varRows[i].toList();
		res.push_back(rowData);
	}
}
