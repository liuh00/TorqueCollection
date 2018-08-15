#pragma once

#include <QObject>

class ExcelManager : public QObject
{
	Q_OBJECT

public:
	ExcelManager(QObject *parent=Q_NULLPTR);
	~ExcelManager();

private:
	QString product;	//����
	QString no;			//λ�ú�
	QString ENGname;	//����ʦ����
	QString mouth;		//����
	QString parameterDir;	//����Ŀ¼


public:
	QString getProduct() const;
	void setProduct(const QString& q_char);
	QString getNo() const;
	void setNo(const QString& q_char);
	QString getEnGname() const;
	void setEnGname(const QString& en_gname);
	QString getMouth() const;
	void setMouth(const QString& q_char);

	QString getParameterDir() const;
	void setParameterDir(const QString& parameter_dir);
	void printTable();


private:
	static void variantTovariantList(const QVariant &var, QList<QList<QVariant> > &res);
};
