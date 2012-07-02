#ifndef __UTILS__
# define __UTILS__

# include <iostream>
# include <string>
# include <vector>

# define COLOR_TEXT(X) "\033["X"m"
# define ERROR_TEXT COLOR_TEXT("31") // red
# define WARNING_TEXT COLOR_TEXT("33") // yellow
# define INFO_TEXT COLOR_TEXT("36") // blue (or try 34)
# define DEPRECATION_TEXT COLOR_TEXT("35") // magenta
# define DEBUG_TEXT COLOR_TEXT("32") // green
# define RESET_COLOR COLOR_TEXT("0")

namespace upo
{
  void print_error(std::string msg);
  void print_warning(std::string msg);
  void print_info(std::string msg);
  void print_deprecated(std::string msg);
  void print_debug(std::string msg);

  template<class T>
  T join(std::vector<T> strs, T separator)
  {
    T str;
    typename std::vector<T>::iterator it;

    for (it = strs.begin() ; it != strs.end() ; ++it)
      {
	if (!str.empty())
	  str.append(separator);
	str.append(*it);
      }
    return str;
  }
} // namespace upo

#endif // __UTILS__
