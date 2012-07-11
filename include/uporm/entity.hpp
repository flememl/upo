#ifndef __UPORM_ENTITY__
# define __UPORM_ENTITY__

# include <string>
# include <map>
//# include "uporm/attribute.hpp"

namespace upo
{
  namespace orm
  {
# define REGISTER_RELATION(X,Y,N,C,R) X = new Y(this, R, C);	\
    this->name_table.insert(std::pair<std::string,void*>(N, X))

    class Entity
    {
    public:
      Entity();
      Entity(int id);
      virtual ~Entity();
      virtual bool commit();
      virtual bool drop();
      virtual void* call(std::string name);

      // static methods
      static Entity* get();

      // attributes
      //UIntAttribute id;

    protected:
      std::map<std::string,void*> name_table;
    };
  }
}

#endif // __UPORM_ENTITY__
