#include "sqlfactory.hpp"

int main(int argc, char** argv)
{
  SQLObject* sql_obj = SQLObject::sql();
  sql_obj->connect("localhost:3307", "root", "root", "test");
  sql_obj->execute("INSERT INTO `city` (`name`) VALUES ('test');");
  sql_obj->execute("DESCRIBE city;");
  sql_obj->close();
  delete sql_obj;
  return EXIT_SUCCESS;
}
