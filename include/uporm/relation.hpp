#ifndef __UPORM_RELATION__
# define __UPORM_RELATION__

# include <list>

namespace upo
{
  namespace orm
  {
# define HAS_ONE(X) X&
# define HAS_MANY(X) std::list<X*>

    enum Cardinality {
      NONE = 0,
      RMANDATORY = 1, // Right operand is mandatory
      LMANDATORY = 2, // Left  operand is mandatory
      RUNIQUE    = 4, // Right operand is unique (OneTo*Relation)
      LUNIQUE    = 8  // Left  operand is unique (*ToOneRelation)
    };

    template<class A, class B>
    class Relation
    {
    public:
      virtual Relation()
      {
	// use this->__cardinality__
      }
      virtual ~Relation()
      {
      }

    protected:
      static const __cardinality__ = NONE;
    };

    template<class A, class B>
    class OneToOne : public Relation<A,B>
    {
    protected:
      static const __cardinality__ = Relation<A,B>::__cardinality__ | RUNIQUE | LUNIQUE;
      HAS_ONE(A) _from;
      HAS_ONE(B) _to;
    };

    template<class A, class B>
    class OneToMany : public Relation<A,B>
    {
    protected:
      static const __cardinality__ = Relation<A,B>::__cardinality__ | RUNIQUE;
      HAS_ONE(A) _from;
      HAS_MANY(B) _to;
    };

    template<class A, class B>
    class ManyToOne : public Relation<A,B>
    {
    protected:
      static const __cardinality__ = Relation<A,B>::__cardinality__ | LUNIQUE;
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
