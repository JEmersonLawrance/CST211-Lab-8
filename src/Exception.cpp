#include "Exception.h"

Exception::Exception(Exception &&copy) noexcept { m_msg = copy.m_msg; }

Exception &Exception::operator=(const Exception &copy) {
  m_msg = copy.m_msg;
  return *this;
}

Exception &Exception::operator=(Exception &&move) noexcept {
  m_msg = move.m_msg;
  move.m_msg = "";
  return *this;
}

ostream &operator<<(ostream &out, const Exception &except) {
  out << except.m_msg;
  return out;
}
