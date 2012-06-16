#ifndef __SQL_FACTORY__
# define __SQL_FACTORY__

# include <iostream>
# include <string>
# include <cstdlib>

# ifdef UPO_MYSQL
#  include "cppconn/connection.h"
#  include "cppconn/driver.h"
#  include "cppconn/exception.h"
#  include "cppconn/resultset.h"
#  include "cppconn/statement.h"
# endif // UPO_MYSQL

class SQLObject;
class MySQL;

class SQLObject
{
public:
  static SQLObject* sql();
  virtual ~SQLObject() {};
  virtual void connect(std::string url, std::string user, std::string pwd, std::string db) = 0;
  virtual sql::ResultSet* execute(std::string query) = 0;
  virtual void close() = 0;
  virtual void commit() = 0;
  virtual void error(sql::SQLException e, std::string file, int line, std::string func) = 0;
};

# ifdef UPO_MYSQL

class MySQL: public SQLObject
{
public:
  MySQL();
  ~MySQL();
  virtual void connect(std::string url, std::string user, std::string pwd, std::string db);
  virtual sql::ResultSet* execute(std::string query);
  virtual void close();
  virtual void commit();
  virtual void error(sql::SQLException e, std::string file, int line, std::string func);
private:
  sql::Driver* _driver;
  sql::Connection* _connection;
};

# endif // UPO_MYSQL

#endif // __SQL_FACTORY__
