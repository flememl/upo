#include "sqlfactory.hpp"
#ifdef UPO_MYSQL
# include "sqlfactory_mysql.hpp"
#endif // UPO_MYSQL

using namespace std;
using namespace upo::db;

SQLObject* SQLObject::sql()
{
  return new SQL_ENGINE();
}
