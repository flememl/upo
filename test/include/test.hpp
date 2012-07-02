#ifndef __TEST_HPP__
# define __TEST_HPP__

# include <string>
# include "sqlfactory.hpp"

class TestCase
{
public:
  TestCase();
  ~TestCase();
  void init(upo::db::database_init* db_init);
  upo::db::SQLObject* sql_obj();
  upo::db::database_init* database();
private:
  upo::db::database_init* _db;
  upo::db::SQLObject* _sql_obj;
};

class DBTestCase : public TestCase
{
public:
  bool test_db_connect();
  bool test_db_close();
  bool test_db_create_table();
  bool test_db_delete_table();
  bool test_db_create_column();
  bool test_db_delete_column();
  bool test_db_create_entity();
  bool test_db_delete_entity();
};

#endif // __TEST_HPP__
