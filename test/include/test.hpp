#ifndef __TEST_HPP__
# define __TEST_HPP__

# include <string>
# include "sqlfactory.hpp"

struct database_init
{
  std::string server;
  std::string port;
  std::string user;
  std::string pwd;
  std::string name;
};

class TestCase
{
public:
  TestCase();
  ~TestCase();
  void init(database_init* db_init);
  upo::db::SQLObject* sql_obj();
  database_init* database();
private:
  database_init* _db;
  upo::db::SQLObject* _sql_obj;
};

bool test_db_connect(TestCase* tc);
bool test_db_close(TestCase* tc);
bool test_db_create_table(TestCase* tc);
bool test_db_delete_table(TestCase* tc);
bool test_db_create_column(TestCase* tc);
bool test_db_delete_column(TestCase* tc);
bool test_db_create_entity(TestCase* tc);
bool test_db_delete_entity(TestCase* tc);

#endif // __TEST_HPP__
