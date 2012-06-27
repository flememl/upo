#ifndef __UTILS__
# define __UTILS__

# include <iostream>
# include <string>

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
} // namespace upo

#endif // __UTILS__
