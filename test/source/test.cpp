#include "test.hpp"

TestCase::TestCase()
{
  this->_sql_obj = upo::db::SQLObject::sql();
}

TestCase::~TestCase()
{
  delete this->_sql_obj;
}

void TestCase::init(upo::db::database_init* db_init)
{
  this->_db = db_init;
}

upo::db::SQLObject* TestCase::sql_obj()
{
  return this->_sql_obj;
}

upo::db::database_init* TestCase::database()
{
  return this->_db;
}

bool DBTestCase::test_db_connect()
{
  this->sql_obj()->connect(*(this->database()));
  return true;
}

bool DBTestCase::test_db_close()
{
  this->sql_obj()->close();
  return true;
}

/*
** DB Table tests
*/

bool DBTestCase::test_db_create_table()
{
  // XXX "City" will later be an entity
  this->sql_obj()->create_table("City");
  this->sql_obj()->commit();
  return true;
}

bool DBTestCase::test_db_delete_table()
{
  // XXX "City" will later be an entity
  this->sql_obj()->delete_table("City");
  this->sql_obj()->commit();
  return true;
}

/*
** DB Column tests
*/

bool DBTestCase::test_db_create_column()
{
  this->sql_obj()->create_column("City", "name", "VARCHAR", 256);
  this->sql_obj()->create_column("City", "zipcode", "INT", 5);
  this->sql_obj()->create_column("City", "country", "VARCHAR", 3);
  this->sql_obj()->commit();
  return true;
}

bool DBTestCase::test_db_delete_column()
{
  this->sql_obj()->delete_column("City", "country");
  this->sql_obj()->delete_column("City", "zipcode");
  this->sql_obj()->delete_column("City", "name");
  this->sql_obj()->commit();
  return true;
}

/*
** DB Entity tests
*/

bool DBTestCase::test_db_create_entity()
{
  std::map<std::string,std::string> values;

  values.insert(std::pair<std::string,std::string>("name", "test"));
  values.insert(std::pair<std::string,std::string>("zipcode", "15000"));
  values.insert(std::pair<std::string,std::string>("country", "FRA"));
  // XXX INSERT will later be replaced by create_entity
  this->sql_obj()->create_row("City", values);
  this->sql_obj()->commit();
  return true;
}

bool DBTestCase::test_db_delete_entity()
{
  std::map<std::string,std::string> values;

  values.insert(std::pair<std::string,std::string>("name", "test"));
  values.insert(std::pair<std::string,std::string>("country", "FRA"));
  // XXX DELETE will later be replaced by delete_entity
  this->sql_obj()->delete_row("City", values);
  this->sql_obj()->commit();
  return true;
}
