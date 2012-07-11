#ifndef __UPORM_RELATION__
# define __UPORM_RELATION__

# include <string>
# include "uporm/operand.hpp"

namespace upo
{
  namespace orm
  {
    enum Cardinality {
      NONE = 0,
      LMANDATORY = 1, // Left  operand is mandatory
      RMANDATORY = 2, // Right operand is mandatory
      LUNIQUE    = 4, // Left  operand is unique (*ToOneRelation)
      RUNIQUE    = 8  // Right operand is unique (OneTo*Relation)
    };

    enum Position {
      LEFT  = 1,
      RIGHT = 2
    };

    // XXX use a composite enum

    template<class L, class R, class A, class B>
    class Relation
    {
    public:
      Relation()
      {
	// XXX use this->__cardinality__
      }

      virtual ~Relation()
      {
      }

    protected:
      static const Cardinality __cardinality__ = NONE;
      std::string _reverse;
      L _from; // XXX replace by Operand
      R _to; // XXX replace by Operand
    };

    template<class L, class R, class A, class B>
    class ExternRelation : public Relation<L,R,A,B>
    {
    public:
      ExternRelation(A* from, std::string reverse, Position)
      {
	this->_from.set(from);
	this->_reverse = reverse;
      }

      ExternRelation(B* to, std::string reverse, Position)
      {
	this->_to.set(to);
	this->_reverse = reverse;
      }

      A* set(B* entity, bool set_reverse=true)
      {
	this->_to.add(entity);
	if (set_reverse == true && !this->_reverse.empty())
	  ((ExternRelation<R,L,B,A>*)entity->call(this->_reverse))->set(this->_from.get(), false);
	return this->_from.get();
      }

      B* get()
      {
	return this->_to.get();
      }
    };

    template<class L, class A>
    class SelfRelation : public Relation<L,L,A,A>
    {
    public:
      SelfRelation(A* entity, std::string reverse, Position position) : _position(position)
      {
	if (this->_position & LEFT)
	  this->_from.set(entity);
	else if (this->_position & RIGHT)
	  this->_to.set(entity);
	this->_reverse = reverse;
      }

      A* set(A* entity, bool set_reverse=true)
      {
	A* main;
	if (this->_position & LEFT)
	  {
	    main = this->_from.get();
	    this->_to.add(entity);
	  }
	else if (this->_position & RIGHT)
	  {
	    main = this->_to.get();
	    this->_from.add(entity);
	  }
	if (set_reverse == true && !this->_reverse.empty())
	  ((SelfRelation<L,A>*)entity->call(this->_reverse))->set(main, false);
	return main;
      }

      A* get()
      {
	if (this->_position & LEFT)
	  return this->_to.get();
	else if (this->_position & RIGHT)
	  return this->_from.get();
      }

    protected:
      Position _position;
    };

    template<class A, class B>
    struct Extern
    {
      typedef ExternRelation<ONE(A),ONE(B),A,B> OneToOne;
      typedef ExternRelation<ONE(A),MANY(B),A,B> OneToMany;
      typedef ExternRelation<MANY(A),ONE(B),A,B> ManyToOne;
      typedef ExternRelation<MANY(A),MANY(B),A,B> ManyToMany;
    };

    template<class A>
    struct Self
    {
      typedef SelfRelation<ONE(A),A> OneToOne;
      typedef ExternRelation<ONE(A),MANY(A),A,A> OneToMany;
      typedef ExternRelation<MANY(A),ONE(A),A,A> ManyToOne;
      typedef SelfRelation<MANY(A),A> ManyToMany;
    };
  }
}

#endif // __UPORM_RELATION__
