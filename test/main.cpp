#include "test.hpp"

int main(int, char**)
{
  DBTestCase tc;
  upo::db::database_init db;

  db.server = "localhost";
  db.port = "3307";
  db.user = "root";
  db.pwd = "root";
  db.name = "test";
  tc.init(&db);
  // tests routine
  tc.test_db_connect();
  tc.test_db_create_table();
  tc.test_db_create_column();
  tc.test_db_create_entity();
  tc.test_db_delete_entity();
  tc.test_db_delete_column();
  tc.test_db_delete_table();
  tc.test_db_close();
  // end tests routine

  return EXIT_SUCCESS;
}
