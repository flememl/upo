#ifndef __UPORM_ATTRIBUTE__
# define __UPORM_ATTRIBUTE__

# include <string>

namespace upo
{
  namespace orm
  {
    enum Definition {
      NONE = 0,
      REQUIRED = 1, // Column is NOT NULL
      UNIQUE   = 2  // Column is UNIQUE
    };

    template<typename T>
    class Attribute
    {
    public:
      virtual Attribute(T d_val, Definition def=NONE, int length=0, int decimals=0) :
	_value(d_val), _length(length), _decimals(decimals)
      {}
      virtual ~Attribute() {}
      virtual Attribute& operator=(const Attribute& right)
      {
	this->_value = right();
	return *this;
      }
      virtual Attribute& operator=(const T& right)
      {
	this->_value = right;
	return *this;
      }
      virtual T operator()()
      {
	return this->_value;
      }
      static const std::string type = NULL;
      static const std::string type_suffix = "";
    private:
      T _value;
      int _length;
      int _decimals;
    };

    class IntAttribute : Attribute<int>
    {
    public:
      static const std::string type = "INT";
    };

    class UIntAttribute : Attribute<unsigned int>
    {
    public:
      static const std::string type = "INT";
      static const std::string type_suffix = "UNSIGNED";
    };
  }
}

#endif // __UPORM_ATTRIBUTE__
