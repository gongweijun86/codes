#include <iostream>
#include <occi.h>
using namespace std;
using namespace oracle::occi;

Environment *env;
StatelessConnectionPool *connPool;
  
void initDB()
{
	const string username = "scott";
	const string password = "bupt";
	const string connectString = "//192.168.10.183/APM";
	unsigned int maxConn = 5;
	unsigned int minConn = 2;
	unsigned int incrConn = 1;

	try
	{
		env = Environment::createEnvironment(Environment::DEFAULT);
		cout << "11" << endl;
		connPool = env->createStatelessConnectionPool(username, password, connectString, maxConn, minConn, incrConn, StatelessConnectionPool::HOMOGENEOUS);
	}
	catch (SQLException &sqlExcp)
	{
		cerr << sqlExcp.getErrorCode() << ":" << sqlExcp.getMessage() << endl;
	}
	catch (exception &excp)
	{
		cerr << excp.what() << endl;
	}
}

void doit()
{
	Connection *conn = connPool->getAnyTaggedConnection();
	Statement  *stmt = conn->createStatement();
	string mySQL="select * from SSP";
	ResultSet *rs = stmt->executeQuery(mySQL);
	
	while(rs->next())
	{
		string Next_server_add=rs->getString(1);
		string mysopgroup=rs->getString(2);
		int mytotalbw = rs->getInt(3);
		int mycost = rs->getInt(5);
		int myavailablebw = rs->getInt(4);
		int myValid = rs->getInt(6);
		int myoutputport = rs->getInt(9);
		string myoutputadd = rs->getString(7);
			
		cout << "NextServerAdd:" << Next_server_add << endl;
		cout << "MySopGroup:" << mysopgroup << endl;
		cout << "MyTotalBW:" << mytotalbw << endl;
		cout << "MyCost:" << mycost << endl;
		cout << "MyAvailableBW:" << myavailablebw << endl;
		cout << "MyValid:" << myValid << endl;
		cout << "MyOutputPort:" << myoutputport << endl;
		cout << "MyOutputAdd:" << myoutputadd << endl;
	}
	cout << "done" << endl;
	
	conn->terminateStatement(stmt);
	connPool->releaseConnection(conn);
}

void createTable()
{
	Connection *conn = connPool->getAnyTaggedConnection();
	Statement  *stmt = conn->createStatement();
	string mySQL = "CREATE TABLE author (author_id NUMBER, author_name VARCHAR2(25))";
	stmt->executeUpdate(mySQL);
	conn->terminateStatement(stmt);
	connPool->releaseConnection(conn);	
}

void terminateDataBase()
{
	try
	{
		env->terminateStatelessConnectionPool(connPool);
		Environment::terminateEnvironment(env);

		}
	
	catch (SQLException &sqlExcp)
	{
		cerr <<sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage() << endl;
	}
	catch (exception &excp)
	{
		cerr << excp.what() << endl;
	}
}

int main()
{
	initDB();
	//doit();
	createTable();
	return 0;
}
