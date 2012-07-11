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

Examples
--------

First, declare the relations of your new entity :
```c++
class ParentOf : public OneToMany<Person,Person> { };

class ChildOf : public ManyToOne<Person,Person>
{
  // LMANDATORY specifies that a Person has to be the child of someone
  static const Cardinality __cardinality__ = OneToMany<Person,Person>::__cardinality__ | LMANDATORY;
};
```

Next, declare the ``Person`` entity :
```c++
class Person : public Entity
{
public:
  StrAttribute name;
  ParentOf     parent_of;
  ChildOf      child_of;
};
```

And make some calls :
```c++
Person bob = Person(42); // Get the Person with id 42
Person kevin = Person(); // Create a new entity Person
kevin.name = "Kevin";
kevin.child_of = bob;
kevin.commit();
bob.parent_of += kevin;
bob.commit()
```