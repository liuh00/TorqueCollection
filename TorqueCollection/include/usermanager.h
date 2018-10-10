#pragma once

#include <QObject>
#include <QSqlDatabase>

class UserManager : public QObject
{
	Q_OBJECT


	Q_PROPERTY(QString actUserName READ actUserName WRITE setActUserName NOTIFY actUserNameChanged)
	Q_PROPERTY(QString actUserGroup READ actUserGroup WRITE setActUserGroup NOTIFY actUserGroupChanged)
	Q_PROPERTY(int actUserLevel READ actUserLevel WRITE setActUserLevel NOTIFY actUserLevelChanged)
	Q_PROPERTY(QString logUser READ logUser WRITE setLogUser NOTIFY logUserChanged)
	Q_PROPERTY(bool logged READ logged WRITE setLogged NOTIFY loggedChanged)

	signals :
	void actUserNameChanged();
	void actUserGroupChanged();
	void actUserLevelChanged();
	void logUserChanged();
	void loggedChanged();
public slots:
	void login(QString userName, QString password);
	void logout();
public:
	UserManager(QObject* parent = Q_NULLPTR);
	~UserManager();


private:
	bool init();
	bool initDatabase();
	QSqlDatabase& getDatabase();
	QString encrypt(QString src);
	QString decrypt(QString ciphertext);
	QString shaEncrypt(QString src);

private:
	QString m_actUserName;
	QString m_actUserGroup;
	int m_actUserLevel;
	QString m_logUser;
	bool m_logged;

public:
	bool logged() const;
	void setLogged(const bool m_logged);
	QString logUser() const;
	void setLogUser(const QString& m_log_user);
	QString actUserName() const;
	void setActUserName(const QString& m_actUserName);
	QString actUserGroup() const;
	void setActUserGroup(const QString& m_actUserGroup);
	int actUserLevel() const;
	void setActUserLevel(const int m_actUserLevel);
};


