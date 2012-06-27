#include "sqlfactory.hpp"

int main(int argc, char** argv)
{
  upo::db::SQLObject* sql_obj = upo::db::SQLObject::sql();
  sql_obj->connect("localhost:3307", "root", "root", "test");
  // XXX "City" will later be an entity
  sql_obj->create_table("City");
  sql_obj->commit();
  //sql_obj->create_column("city", "name", "string", 256);
  //sql_obj->create_column("city", "zipcode", "int", 5);
  // XXX INSERT will later be replaced by create_entity
  //sql_obj->execute("INSERT INTO `city` (`name`, `zipcode`) VALUES ('test', '15000');");
  sql_obj->delete_table("City");
  sql_obj->commit();
  sql_obj->close();
  delete sql_obj;
  return EXIT_SUCCESS;
}
