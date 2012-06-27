#ifndef __SQL_FACTORY__
# define __SQL_FACTORY__

# include <iostream>
# include <string>
# include <sstream>
# include <cstdlib>

// XXX TMP while there is no proper exceptions and resultsets
# ifdef UPO_MYSQL
#  include "cppconn/exception.h"
#  include "cppconn/resultset.h"
# endif UPO_MYSQL

// to safely specify table names or column names, not to be confounded with SQL keywords
# define SSTR(s) "`" + s + "`"
# define ENDQ    ";"

namespace upo
{
  namespace db
  {
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
  } // namespace db
} // namespace upo

#endif // __SQL_FACTORY__
