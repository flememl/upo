#ifdef UPO_MYSQL

# include "sqlfactory_mysql.hpp"
# include "utils.hpp"

using namespace std;
using namespace upo::db;

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
  sql::ResultSet* result = NULL;

  upo::print_debug(query);
  try
    {
      result = statement->executeQuery(query);
    }
  catch (sql::SQLException &e)
    {
      this->error(e, __FILE__, __LINE__, __func__, query);
    }
  return result;
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

void MySQL::error(sql::SQLException e, string file, int line, string func, string query)
{
  if (e.getErrorCode() == 0)
    return ;
  ostringstream msg;
  msg << "ERROR: SQLException in " << file;
  msg << " (" << func << ") on line " << line << endl;
  msg << "ERROR: " << e.what();
  msg << " (MySQL error code: " << e.getErrorCode();
  msg << ", SQLState: " << e.getSQLState() << ")" << endl;
  msg << "ERROR: Query: " << query;
  upo::print_error(msg.str());
}

void MySQL::warning(sql::SQLException e, string file, int line, string func, string query)
{
  if (e.getErrorCode() == 0)
    return ;
  ostringstream msg;
  msg << "WARNING: SQLException in " << file;
  msg << " (" << func << ") on line " << line << endl;
  msg << "WARNING: " << e.what();
  msg << " (MySQL error code: " << e.getErrorCode();
  msg << ", SQLState: " << e.getSQLState() << ")" << endl;
  msg << "WARNING: Query: " << query;
  upo::print_warning(msg.str());
}

bool MySQL::create_table(string table_name, bool safe/*=true*/)
{
  cout << "MySQL create_table" << endl;
  ostringstream query;
  bool result = false;

  query << "CREATE TABLE ";
  if (safe)
    query << "IF NOT EXISTS ";
  query << SSTR(table_name) << " (`id` INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY)" << ENDQ;
  try
    {
      this->execute(query.str());
      result = true;
    }
  catch (sql::SQLException &e)
    {
      if (e.getErrorCode() == 0)
	result = true;
      this->warning(e, __FILE__, __LINE__, __func__, query.str());
    }
  return result;
}

bool MySQL::create_column(string table_name, string column_name, string type, int length/*=0*/)
{
  cout << "MySQL create_column" << endl;
  ostringstream query;
  bool result = false;

  query << "ALTER TABLE " << SSTR(table_name) << " ADD COLUMN ( " << SSTR(column_name) << " " << type;
  if (length > 0)
    query << "(" << length << ")";
  query << " )" << ENDQ;
  try
    {
      this->execute(query.str());
      result = true;
    }
  catch (sql::SQLException &e)
    {
      if (e.getErrorCode() == 0)
	result = true;
      this->warning(e, __FILE__, __LINE__, __func__, query.str());
    }
  return result;
}

bool MySQL::delete_table(string table_name, bool safe/*=true*/)
{
  cout << "MySQL delete_table" << endl;
  ostringstream query;
  bool result = false;

  query << "DROP TABLE ";
  if (safe)
    query << "IF EXISTS ";
  query << SSTR(table_name) << ENDQ;
  try
    {
      this->execute(query.str());
      result = true;
    }
  catch (sql::SQLException &e)
    {
      if (e.getErrorCode() == 0)
	result = true;
      this->error(e, __FILE__, __LINE__, __func__, query.str());
    }
  return result;
}

bool MySQL::delete_column(string table_name, string column_name)
{
  cout << "MySQL delete_column" << endl;
  ostringstream query;
  bool result = false;

  query << "ALTER TABLE " << SSTR(table_name) << " DROP COLUMN " << SSTR(column_name) << ENDQ;
  try
    {
      this->execute(query.str());
      result = true;
    }
  catch (sql::SQLException &e)
    {
      if (e.getErrorCode() == 0)
	result = true;
      this->warning(e, __FILE__, __LINE__, __func__, query.str());
    }
  return result;
}

#endif // UPO_MYSQL
