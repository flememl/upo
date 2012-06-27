#include "sqlfactory.hpp"
#include "utils.hpp"

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
  sql::Statement* statement = this->_connection->createStatement();

  return statement->executeQuery(query);
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
  if (e.getErrorCode() == 0)
    return ;
  ostringstream msg;
  msg << "ERROR: SQLException in " << file;
  msg << " (" << func << ") on line " << line << endl;
  msg << "ERROR: " << e.what();
  msg << " (MySQL error code: " << e.getErrorCode();
  msg << ", SQLState: " << e.getSQLState() + ")";
  upo::print_error(msg.str());
}

void MySQL::warning(sql::SQLException e, string file, int line, string func)
{
  if (e.getErrorCode() == 0)
    return ;
  ostringstream msg;
  msg << "WARNING: SQLException in " << file;
  msg << " (" << func << ") on line " << line << endl;
  msg << "WARNING: " << e.what();
  msg << " (MySQL error code: " << e.getErrorCode();
  msg << ", SQLState: " << e.getSQLState() + ")";
  upo::print_warning(msg.str());
}

bool MySQL::create_table(string table_name, bool safe/*=true*/)
{
  cout << "MySQL create_table" << endl;
  string query = "CREATE TABLE ";
  bool result = false;

  if (safe)
    query.append("IF NOT EXISTS ");
  query.append( SSTR(table_name) );
  query.append(" (`id` INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY);");
  try
    {
      this->execute(query);
      result = true;
    }
  catch (sql::SQLException &e)
    {
      if (e.getErrorCode() == 0)
	result = true;
      this->warning(e, __FILE__, __LINE__, __func__);
    }
  return result;
}

bool MySQL::delete_table(string table_name, bool safe/*=true*/)
{
  cout << "MySQL delete_table" << endl;
  string query = "DROP TABLE ";
  bool result = false;

  if (safe)
    query.append(" IF EXISTS ");
  query.append( SSTR(table_name) );
  try
    {
      this->execute(query);
      result = true;
    }
  catch (sql::SQLException &e)
    {
      if (e.getErrorCode() == 0)
	result = true;
      this->error(e, __FILE__, __LINE__, __func__);
    }
  return result;
}
#endif // UPO_MYSQL
