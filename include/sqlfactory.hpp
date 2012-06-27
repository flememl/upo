#ifndef __SQL_FACTORY__
# define __SQL_FACTORY__

# include <iostream>
# include <string>
# include <sstream>
# include <cstdlib>

// to safely specify table names or column names, not to be confounded with SQL keywords
# define SSTR(s) "`" + s + "`"
# define ENDQ    ";"

# ifdef UPO_MYSQL
#  include "cppconn/connection.h"
#  include "cppconn/driver.h"
#  include "cppconn/exception.h"
#  include "cppconn/resultset.h"
#  include "cppconn/statement.h"
#  include "cppconn/prepared_statement.h"
# endif // UPO_MYSQL

namespace upo
{
  namespace db
  {
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
      virtual void warning(sql::SQLException e, std::string file, int line, std::string func) = 0;

      virtual bool create_table(std::string table_name, bool safe=true) = 0;
      // virtual bool create_column() = 0;
      // virtual bool alter_table() = 0;
      // virtual bool alter_column() = 0;
      virtual bool delete_table(std::string table_name, bool safe=true) = 0;
      // virtual bool delete_column() = 0;
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
      virtual void warning(sql::SQLException e, std::string file, int line, std::string func);

      virtual bool create_table(std::string table_name, bool safe=true);
      // virtual bool create_column();
      // virtual bool alter_table();
      // virtual bool alter_column();
      virtual bool delete_table(std::string table_name, bool safe=true);
      // virtual bool delete_column();
    private:
      sql::Driver* _driver;
      sql::Connection* _connection;
    };
# endif // UPO_MYSQL

  } // namespace db
} // namespace upo

#endif // __SQL_FACTORY__
