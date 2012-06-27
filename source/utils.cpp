#include "utils.hpp"

using namespace std;

void upo::print_error(string msg)
{
  cout << ERROR_TEXT;
  cout << msg;
  cout << RESET_COLOR;
  cout << endl;
}

void upo::print_warning(string msg)
{
  cout << WARNING_TEXT;
  cout << msg;
  cout << RESET_COLOR;
  cout << endl;
}

void upo::print_info(string msg)
{
  cout << INFO_TEXT;
  cout << msg;
  cout << RESET_COLOR;
  cout << endl;
}

void upo::print_deprecated(string msg)
{
  cout << DEPRECATION_TEXT;
  cout << msg;
  cout << RESET_COLOR;
  cout << endl;
}

void upo::print_debug(string msg)
{
  cout << DEBUG_TEXT;
  cout << msg;
  cout << RESET_COLOR;
  cout << endl;
}
