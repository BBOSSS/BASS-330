#ifndef __MYSQL_INTERFACE_H__  
#define __MYSQL_INTERFACE_H__  
 
#include <string>  
#include <vector>  
 
#include <winsock.h> 
#include "mysql.h"

#pragma comment(lib, "ws2_32.lib")  

 
#define		ERROR_QUERY_FAIL	-1
#define		PORT				3306
#define		SERVER				"localhost"
#define		USER				"root"
#define		PASSWORD			"12123"
#define		DATABASE			"bass-330"

typedef struct
{
	char* server;
	char* user;
	char* password;
	char* database;
	int port;
}MySQLConInfo;
 
class MySQLInterface
{
public:
	MySQLInterface();
	virtual ~MySQLInterface();
 
	void SetMySQLConInfo(char* server, char* username, char* password, char* database, int port);
	bool Open(); 
	void Close(); 
 
	bool Select(const std::string& Querystr, std::vector<std::vector<std::string> >& data);	    
	bool Query(const std::string& Querystr);   
	int GetInsertID(const std::string& Querystr);
	void ErrorIntoMySQL();		
 
public:
	int ErrorNum;				
	const char* ErrorInfo;      
 
private:
	MySQLConInfo MysqlConInfo;	
	MYSQL MysqlInstance;		 
	MYSQL_RES *Result;			
};

#endif