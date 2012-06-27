#include "sqlfactory.hpp"

int main(int, char**)
{
  upo::db::SQLObject* sql_obj = upo::db::SQLObject::sql();
  sql_obj->connect("localhost:3307", "root", "root", "test");
  // XXX "City" will later be an entity
  sql_obj->create_table("City");
  sql_obj->commit();
  sql_obj->create_column("City", "name", "VARCHAR", 256);
  sql_obj->create_column("City", "zipcode", "INT", 5);
  sql_obj->create_column("City", "country", "VARCHAR", 3);
  sql_obj->commit();
  // XXX INSERT will later be replaced by create_entity
  sql_obj->execute("INSERT INTO `City` (`name`, `zipcode`, `country`) VALUES ('test', 15000, 'FRA');");
  sql_obj->commit();
  sql_obj->delete_column("City", "country");
  sql_obj->delete_table("City");
  sql_obj->commit();
  sql_obj->close();
  delete sql_obj;
  return EXIT_SUCCESS;
}
