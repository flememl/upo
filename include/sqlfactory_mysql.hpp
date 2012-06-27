#ifdef UPO_MYSQL
# ifndef __SQL_FACTORY__MYSQL__
#  define __SQL_FACTORY__MYSQL__

#  include "cppconn/connection.h"
#  include "cppconn/driver.h"
#  include "cppconn/exception.h"
#  include "cppconn/resultset.h"
#  include "cppconn/statement.h"

#  include "sqlfactory.hpp"

namespace upo
{
  namespace db
  {
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
  } // namespace db
} // namespace upo

# endif // __SQL_FACTORY__MYSQL__
#endif // UPO_MYSQL
