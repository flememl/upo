#include "test.hpp"

TestCase::TestCase()
{
  this->_sql_obj = upo::db::SQLObject::sql();
}

TestCase::~TestCase()
{
  delete this->_sql_obj;
}

void TestCase::init(database_init* db_init)
{
  this->_db = db_init;
}

upo::db::SQLObject* TestCase::sql_obj()
{
  return this->_sql_obj;
}

database_init* TestCase::database()
{
  return this->_db;
}

bool test_db_connect(TestCase* tc)
{
  std::string host = tc->database()->server + ":" + tc->database()->port;

  tc->sql_obj()->connect(host, tc->database()->user, tc->database()->pwd, tc->database()->name);
  return true;
}

bool test_db_close(TestCase* tc)
{
  tc->sql_obj()->close();
  return true;
}

/*
** DB Table tests
*/

bool test_db_create_table(TestCase* tc)
{
  // XXX "City" will later be an entity
  tc->sql_obj()->create_table("City");
  tc->sql_obj()->commit();
  return true;
}

bool test_db_delete_table(TestCase* tc)
{
  // XXX "City" will later be an entity
  tc->sql_obj()->delete_table("City");
  tc->sql_obj()->commit();
  return true;
}

/*
** DB Column tests
*/

bool test_db_create_column(TestCase* tc)
{
  tc->sql_obj()->create_column("City", "name", "VARCHAR", 256);
  tc->sql_obj()->create_column("City", "zipcode", "INT", 5);
  tc->sql_obj()->create_column("City", "country", "VARCHAR", 3);
  tc->sql_obj()->commit();
  return true;
}

bool test_db_delete_column(TestCase* tc)
{
  tc->sql_obj()->delete_column("City", "country");
  tc->sql_obj()->delete_column("City", "zipcode");
  tc->sql_obj()->delete_column("City", "name");
  tc->sql_obj()->commit();
  return true;
}

/*
** DB Entity tests
*/

bool test_db_create_entity(TestCase* tc)
{
  // XXX INSERT will later be replaced by create_entity
  tc->sql_obj()->execute("INSERT INTO `City` (`name`, `zipcode`, `country`) VALUES ('test', 15000, 'FRA');");
  tc->sql_obj()->commit();
  return true;
}

bool test_db_delete_entity(TestCase* tc)
{
  // XXX DELETE will later be replaced by delete_entity
  tc->sql_obj()->execute("DELETE FROM `City` WHERE `name` = 'test';");
  tc->sql_obj()->commit();
  return true;
}
