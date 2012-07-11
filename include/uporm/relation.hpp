#ifndef __UPORM_RELATION__
# define __UPORM_RELATION__

# include <list>
# include <string>

namespace upo
{
  namespace orm
  {
# define ONE(x) x*
# define MANY(x) std::list<x*>
# define HAS_ONE(x) ONE(x)
# define HAS_MANY(x) MANY(x)

    enum Cardinality {
      NONE = 0,
      LMANDATORY = 1, // Left  operand is mandatory
      RMANDATORY = 2, // Right operand is mandatory
      LUNIQUE    = 4, // Left  operand is unique (*ToOneRelation)
      RUNIQUE    = 8  // Right operand is unique (OneTo*Relation)
    };

    enum Position {
      NONE = 0,
      LEFT  = 1,
      RIGHT = 2
    };

    // XXX use a composite enum

    template<class A, class B>
    class Relation
    {
    public:
      virtual Relation()
      {
	// XXX use this->__cardinality__
      }

      virtual Relation(A* from, std::string reverse)
      {
	this->_from = from;
	this->_reverse = reverse;
      }

      virtual Relation(B* to, std::string reverse)
      {
	this->_to = to;
	this->_reverse = reverse;
      }

      virtual ~Relation()
      {
      }

      A& set(B* to, bool set_reverse=true)
      {
	this->_to = to;
	if (set_reverse == true && !this->_reverse.empty())
	  ((Relation<B,A>*)this->_to->call(this->_reverse))->set(this->_from, false);
	return *(this->_from);
      }

      B* get()
      {
	return this->_to;
      }

    protected:
      static const Cardinality __cardinality__ = NONE;
      std::string _reverse;
      A* _from; // XXX replace by Operand
      B* _to; // XXX replace by Operand
    };

    template<class A>
    class SelfRelation : public Relation<A,A>
    {
    public:
      SelfRelation(A* entity, std::string reverse, Position position) : _position(position)
      {
	if (this->_position & LEFT) {
	  this->_from = entity;
	}
	else if (this->_position & RIGHT) {
	  this->_to = entity;
	}
	this->_reverse = reverse;
      }

      A* set(A* entity, bool set_reverse=true)
      {
	A* main;
	if (this->_position & LEFT)
	  {
	    main = this->_from;
	    this->_to = entity;
	  }
	else if (this->_position & RIGHT)
	  {
	    main = this->_to;
	    this->_from = entity;
	  }
	if (set_reverse == true && !this->_reverse.empty())
	  ((Relation<Q,Q>*)entity->call(this->_reverse))->set(main, false);
	return main;
      }

      A* get()
      {
	if (this->_position & LEFT)
	  return this->_to;
	else if (this->_position & RIGHT)
	  return this->_from;
      }

    protected:
      Position _position;
    };

    template<class A, class B>
    class OneToOne : public Relation<A,B>
    {
    protected:
      static const Cardinality __cardinality__ = Relation<A,B>::__cardinality__ | RUNIQUE | LUNIQUE;
      HAS_ONE(A) _from;
      HAS_ONE(B) _to;
    };

    template<class A, class B>
    class OneToMany : public Relation<A,B>
    {
    protected:
      static const Cardinality __cardinality__ = Relation<A,B>::__cardinality__ | RUNIQUE;
      HAS_ONE(A) _from;
      HAS_MANY(B) _to;
    };

    template<class A, class B>
    class ManyToOne : public Relation<A,B>
    {
    protected:
      static const Cardinality __cardinality__ = Relation<A,B>::__cardinality__ | LUNIQUE;
      HAS_MANY(A) _from;
      HAS_ONE(B) _to;
    };

    template<class A, class B>
    class ManyToMany : public Relation<A,B>
    {
    protected:
      HAS_MANY(A) _from;
      HAS_MANY(B) _to;
    };
  }
}

#endif // __UPORM_RELATION__
