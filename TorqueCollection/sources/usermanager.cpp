#include "usermanager.h"
#include <QCoreApplication>
#include <QDir>
#include <QSqlQuery>
#include <QVariant>
#include <OpenSSL/ssl.h>
#include <QSqlError>

void UserManager::login(QString userName, QString password)
{
	setLogUser(userName);
	setActUserName("");
	setActUserGroup("");
	setActUserLevel(0);
	setLogged(false);
		
	
	QSqlDatabase sql = getDatabase();
	if (sql.open())
	{
		QSqlQuery query(sql);

		query.prepare("SELECT * FROM userManager WHERE id =:id");
		query.bindValue(":id", shaEncrypt(userName));
		query.exec();

		if (query.isActive() && query.next())
		{
			QString cipher_user = query.value("userName").toString();
			QString cipher_password = query.value("password").toString();
			QString cipher_group = query.value("userGroup").toString();
			QString cipher_level = query.value("userLevel").toString();
			query.clear();
			QString user = decrypt(cipher_user);
			QString pwd = decrypt(cipher_password);

			if (pwd == password && user == userName)
			{
				QString group = decrypt(cipher_group);
				QString level = decrypt(cipher_level);
				group.resize(group.size() - user.size());
				level.resize(level.size() - user.size());
				
				setActUserName(user);
				setActUserGroup(group);
				setActUserLevel(level.toInt());
				setLogged(true);
			}
		}
		query.clear();
	}
	sql.close();
}

void UserManager::logout()
{
	setActUserName("");
	setActUserGroup("");
	setActUserLevel(0);
	setLogged(false);
}

UserManager::UserManager(QObject* parent)
	: QObject(parent)
{
	setActUserName("");
	setActUserGroup("");
	setActUserLevel(0);
	setLogged(false);
	init();
}

UserManager::~UserManager()
{
	QSqlDatabase::removeDatabase("UserManager");
}

bool UserManager::init()
{
	if (!initDatabase())
	{
		return false;
	}
	return true;
}

bool UserManager::initDatabase()
{
	QString pathName = QCoreApplication::applicationDirPath() + "/Configuration";

	QDir dir(pathName);

	if (!dir.exists())
	{
		dir.mkpath(pathName);
	}

	if (QSqlDatabase::contains("UserManager"))
	{
		QSqlDatabase::removeDatabase("UserManager");
	}


	QSqlDatabase sql = getDatabase();


	if (sql.open())
	{
		QSqlQuery query(sql);

		QString commandText = "SELECT count(*) as count  FROM sqlite_master WHERE name='userManager'";
		query.exec(commandText);
		int count = 0;

		if (query.next() && query.isActive())
		{
			count = query.value("count").toInt();
			//不存在数据库
			if (count == 0)
			{
				commandText = " CREATE TABLE 'userManager' ('id' TEXT, 'userName'  TEXT, 'password'  TEXT, 'userGroup'  TEXT,'userLevel' TEXT)";
				query.exec(commandText);
				if (!query.isActive())
				{
					sql.close();
					return false;
				}
			}
		}
		else
		{
			sql.close();
			return false;
		}

		commandText = QString("DELETE FROM userManager WHERE id='%1'").arg(shaEncrypt("System"));
		query.exec(commandText);
		
		
		QString par1 = shaEncrypt("System");
		QString par2 = encrypt("System");
		QString par3 = encrypt("system.admin");
		QString par4 = encrypt("SYSTEMSystem");
		QString par5 = encrypt("999System");
		
		query.prepare("INSERT INTO userManager (id,userName,password,userGroup,userLevel) VALUES (?,?,?,?,?)");
		query.bindValue(0, par1);
		query.bindValue(1, par2);
		query.bindValue(2, par3);
		query.bindValue(3, par4);
		query.bindValue(4, par5);
		query.exec();

		QString str = query.lastError().text();
		query.clear();
	}
	else
	{
		return false;
	}


	sql.close();
	return true;
}


QSqlDatabase& UserManager::getDatabase()
{
	QString pathName = QCoreApplication::applicationDirPath() + "/Configuration";
	QString fileName = pathName + "/UserManager";

	QSqlDatabase sql;
	if (!QSqlDatabase::contains("QSQLITE"))
	{
		sql = QSqlDatabase::addDatabase("QSQLITE", "UserManager");
		sql.setDatabaseName(fileName);
		sql.setUserName("UserManager.");
		sql.setPassword("UserManager.");
		return sql;
	}
	sql = QSqlDatabase::database("UserManager");
	return sql;
}

QString UserManager::encrypt(QString src)
{
	QByteArray puk;
	puk.append("-----BEGIN PUBLIC KEY-----\n");
	puk.append("MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAvUfXBVha5REvxVtKUxnc");
	puk.append("wUcXBEl9rWHL0zxgRrXY7A67AOqlyXg4KUxjXEO0KrUiuc4Dh7mdCdDpSGU9aZBS");
	puk.append("uS7cnRCx2UqfE9SC79M5iF55/eW4EPjuhqeeIFoRJWqOPvugOAb9b1pKPWM1dUmP");
	puk.append("N39q0GE/GYxepqaPKUqOzCAhKe+M8ut+fOkgXClFQ18gWmOB/w54qFjm3lJ9RTQE");
	puk.append("PBEIkzR9d8axOhFkvIUBoUzey/4x+eSnoriA/zXmO0wphcwP4iLXGlkuaX6iaT4o");
	puk.append("2QBQGPMC6UIQd8HdJQxOyGppnvfXLM8ZiAu2HpKDzTNVO2wB6WKXB+D7XVxmZ/wp");
	puk.append("mwIDAQAB");
	puk.append("\n-----END PUBLIC KEY-----\n");


	int len = src.size() * 2;
	unsigned char* srcChar = (unsigned char *)malloc(len);
	memcpy(srcChar, src.toLatin1().data(), len);
	char encrypted[256] = {0};

	BIO* keybio;
	keybio = BIO_new_mem_buf(puk.data(), -1);
	RSA* rsa;
	rsa = PEM_read_bio_RSA_PUBKEY(keybio, nullptr, nullptr, nullptr);
	RSA_public_encrypt(len, srcChar, (unsigned char *)encrypted, rsa, RSA_PKCS1_OAEP_PADDING);
	QByteArray date(encrypted, 256);

	delete[] srcChar;
	RSA_free(rsa);
	BIO_free(keybio);


	return date.toBase64(QByteArray::Base64Encoding);;
}

QString UserManager::decrypt(QString ciphertext)
{
	QByteArray prk;
	prk.append("-----BEGIN RSA PRIVATE KEY-----\n");
	prk.append("MIIEowIBAAKCAQEAvUfXBVha5REvxVtKUxncwUcXBEl9rWHL0zxgRrXY7A67AOql");
	prk.append("yXg4KUxjXEO0KrUiuc4Dh7mdCdDpSGU9aZBSuS7cnRCx2UqfE9SC79M5iF55/eW4");
	prk.append("EPjuhqeeIFoRJWqOPvugOAb9b1pKPWM1dUmPN39q0GE/GYxepqaPKUqOzCAhKe+M");
	prk.append("8ut+fOkgXClFQ18gWmOB/w54qFjm3lJ9RTQEPBEIkzR9d8axOhFkvIUBoUzey/4x");
	prk.append("+eSnoriA/zXmO0wphcwP4iLXGlkuaX6iaT4o2QBQGPMC6UIQd8HdJQxOyGppnvfX");
	prk.append("LM8ZiAu2HpKDzTNVO2wB6WKXB+D7XVxmZ/wpmwIDAQABAoIBAFoCWKjtDERT+PCT");
	prk.append("6fM8oDK1GKfsPrx9fgzUcEAP57jRhHH6I5578dEJx1Ivy/RnML1Ez37ycFAjrVvE");
	prk.append("8QBLJltzgmuabciT6LPoYd+kBX7o1oA7hl1j0yHrgZGG4xJ06nHe/KDICiqyuA0b");
	prk.append("KWe99EIC8ItpQzVl//ilyfxrvR4p81zMoCmWFe5U+8U06HsF/AQV+2xuZTNlHTkl");
	prk.append("tS5pr3U7YgsYGbVrvrLQDsGbNWyxxH1YZspntdZZZaWke0JbscVYYxODdCOXZvvt");
	prk.append("BGhLzi7Bmf3YcJ9sWsAYJSGRtOkYzPAHaqbbWpSe9vN0qet41cD4DijfdMTSiiBM");
	prk.append("7BFsjdECgYEA7A3DjulCejpMdw9DjMkUAtHbKQ7Hc/2KiJOOhXlB/zmt3VhZs5pR");
	prk.append("xqjGsYHPN1ArWdWZd/7rKeCuEstjv1TZfC2cp4Rz85gEP798ATdbQ1rgreZdHGNn");
	prk.append("sDB/s/oc2YL83KBgsH7fDBAk1NaNehG3yCY+n2IYy24ahMAkw5RbWwkCgYEAzUZL");
	prk.append("iz+vFTHa+5LcjlSaKWLUK3odlo5AH6nrx7mvnapUt7MP6Y09a1CIK+zpkKcsspWB");
	prk.append("lRVH76yKuNy9Vm4AXYJKZYQyI+z1LEb2MtlZslInaiXATqpZe8BrvW5FChV3fWWY");
	prk.append("azFqm2VfwfCuAx5ipLNYlULGjKsWqymf7By49IMCgYBHm7FMZDSXcaIKqCW8yq74");
	prk.append("YAMVBHe7Fxn0bpbYpL1BmJTGxeuIUXMnScHkzVU4GWjdOq/wt/NM4+zKpMqgmzPS");
	prk.append("uN+B7eti5SW81PDgSZO07hekiXKLjxhAWaYTyfcAgP0GTNyoDgTJ2wfhTSjj9AYF");
	prk.append("gJyUqySMad0/ki5U6meASQKBgCeCbivhGAvWSrW9MKJcekeY9AliOauuuXzesbkB");
	prk.append("bmHEVQX+ewOS4c1z9KGvuczTwHCnAgf1zqC87v5hzjeCeKOG3lbnuNbdVtss1Vo4");
	prk.append("J2GBGoD9vyPk+dAt2w7c2ID2XMdP9KQ9IK3EN0gW0Qdco9PbiSNBdQHCNFzBaDyD");
	prk.append("0r2NAoGBAIm5pZ94anuuX8gCdxHd3JsaEcnkeKYCqm1pc+j7YQnAbd9P60WsRvB6");
	prk.append("hfP+g0HmBfniAjUMk00u9rJU5ORFthKp8+AxvGm/VeTJOTDXVoulGpRaEnzoitdC");
	prk.append("CZFLqb9zjTbX4fzjRN6oFOYgZjnQzdRl+WjXI9owF+bR4dNVscuE");
	prk.append("\n-----END RSA PRIVATE KEY-----\n");


	QByteArray ciphertext_b = QByteArray::fromBase64(ciphertext.toLatin1(), QByteArray::Base64Encoding);
	unsigned char encrypted[256] = {0};
	memcpy(encrypted, ciphertext_b.data(), 256);
	unsigned char decrypted[256] = {0};
	RSA* rsa;
	BIO* keybio;
	keybio = BIO_new_mem_buf(prk.data(), -1);

	rsa = PEM_read_bio_RSAPrivateKey(keybio, nullptr, nullptr, nullptr);

	RSA_private_decrypt(ciphertext_b.length(), encrypted, decrypted, rsa, RSA_PKCS1_OAEP_PADDING);


	RSA_free(rsa);
	BIO_free(keybio);

	return QString::fromLatin1((char *)decrypted, -1);
}

QString UserManager::shaEncrypt(QString src)
{
	char buf[2];
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	QByteArray src_byte_array = src.toLatin1();
	SHA256_Update(&sha256, src_byte_array.data(), src_byte_array.length());
	SHA256_Final(hash, &sha256);
	QByteArray out((char *)hash, SHA256_DIGEST_LENGTH);

	return out.toBase64(QByteArray::Base64Encoding);
}

bool UserManager::logged() const
{
	return m_logged;
}

void UserManager::setLogged(const bool m_logged)
{
	this->m_logged = m_logged;
	emit loggedChanged();
}

QString UserManager::logUser() const
{
	return m_logUser;
}

void UserManager::setLogUser(const QString& m_log_user)
{
	m_logUser = m_log_user;
	emit logUserChanged();
}

QString UserManager::actUserName() const
{
	return m_actUserName;
}

void UserManager::setActUserName(const QString& m_actUserName)
{
	this->m_actUserName = m_actUserName;
	emit actUserNameChanged();
}

QString UserManager::actUserGroup() const
{
	return m_actUserGroup;
}

void UserManager::setActUserGroup(const QString& m_actUserGroup)
{
	this->m_actUserGroup = m_actUserGroup;
	emit actUserGroupChanged();
}

int UserManager::actUserLevel() const
{
	return m_actUserLevel;
}

void UserManager::setActUserLevel(const int m_actUserLevel)
{
	this->m_actUserLevel = m_actUserLevel;
	emit actUserLevelChanged();
}
