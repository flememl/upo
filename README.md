upo
===

Unidentified Programmed Object

Dependancies
------------

* MySql Connector/C++
  http://dev.mysql.com/downloads/connector/cpp/
  http://dev.mysql.com/tech-resources/articles/building-mysql-connector-cpp.html
* MySql compiling dependancies
  mysql-client
  mysql-server
  libmysqlclient-dev
* In order to compile the MySql connector, add
  ``#include <stdint.h>`` in ``cppconn/resultset.h``
  ``#include <stdint.h>`` in ``driver/nativeapi/native_connection_wrapper.h``
  ``#include <stdint.h>`` in ``driver/nativeapi/native_statement_wrapper.h``
  ``#include <stdint.h>`` in ``driver/nativeapi/native_resultset_wrapper.h``
