#ifndef __UPORM_OPERAND__
# define __UPORM_OPERAND__

# include <list>

namespace upo
{
  namespace orm
  {
# define ONE(x) UOperand<x>
# define MANY(x) MOperand<x>

    template<class A>
    class IOperand
    {
    public:
      virtual void set(A* value) = 0;
      virtual A* get(int i=0) = 0;
      virtual void add(A* value) = 0;
      virtual bool empty() = 0;
      virtual void clear() = 0;
    };

    template<class A>
    class UOperand : public IOperand<A>
    {
    public:
      virtual void set(A* value)
      {
	this->_value = value;
      }

      virtual A* get(int i=0)
      {
	return this->_value;
      }

      virtual void add(A* value)
      {
	this->_value = value;
      }

      virtual bool empty()
      {
	return this->_value == NULL;
      }

      virtual void clear()
      {
	this->_value = NULL;
      }

    private:
      A* _value;
    };

    template<class A>
    class MOperand : public IOperand<A>
    {
    public:
      virtual void set(A* value)
      {
	this->clear();
	this->add(value);
      }

      virtual A* get(int i=0)
      {
	return this->_value[i];
      }

      virtual void add(A* value)
      {
	this->_value.push_back(value);
      }

      virtual bool empty()
      {
	return this->_value.empty();
      }

      virtual void clear()
      {
	this->_value.empty();
      }

    private:
      std::list<A*> _value;
    };
  }
}

#endif // __UPORM_OPERAND__
