#include "sqlfactory.hpp"

using namespace std;
using namespace upo::db;

SQLObject* SQLObject::sql()
{
  return new SQL_ENGINE();
}

#ifdef UPO_MYSQL
MySQL::MySQL()
{
  cout << "MySQL constructor" << endl;
  this->_driver = get_driver_instance();
}

MySQL::~MySQL()
{
  cout << "MySQL destructor" << endl;
  this->close();
  delete this->_connection;
}

void MySQL::connect(string url, string user, string pwd, string db)
{
  cout << "MySQL connect" << endl;
  this->_connection = this->_driver->connect(url, user, pwd);
  this->_connection->setAutoCommit(0);
  this->_connection->setSchema(db);
}

sql::ResultSet* MySQL::execute(string query)
{
  cout << "MySQL execute" << endl;
  try
    {
      sql::Statement* statement = this->_connection->createStatement();
      return statement->executeQuery(query);
    }
  catch (sql::SQLException &e)
    {
      this->error(e, __FILE__, __LINE__, __func__);
    }
  return NULL;
}

void MySQL::close()
{
  if (!this->_connection->isClosed())
    {
      cout << "MySQL close" << endl;
      this->_connection->close();
    }
}

void MySQL::commit()
{
  cout << "MySQL commit" << endl;
  this->_connection->commit();
}

void MySQL::error(sql::SQLException e, string file, int line, string func)
{
      cout << "ERROR: SQLException in " << file;
      cout << " (" << func << ") on line " << line << endl;
      cout << "ERROR: " << e.what();
      cout << " (MySQL error code: " << e.getErrorCode();
      cout << ", SQLState: " << e.getSQLState() << ")" << endl;
}
#endif // UPO_MYSQL
