#ifndef __UPORM_ENTITY__
# define __UPORM_ENTITY__

# include "uporm/attribute.hpp"

namespace upo
{
  namespace orm
  {
    class Entity
    {
    public:
      virtual Entity();
      virtual Entity(int id);
      virtual ~Entity();
      virtual bool commit();
      virtual bool delete();

      // static methods
      static virtual Entity* get();

      // attributes
      UIntAttribute id;
    };
  }
}

#endif // __UPORM_ENTITY__
