#include "Exceptions.hpp"


///////////////////////////////////////////////////////////////////////////
// command_not_found

command_not_found::command_not_found(const std::string &what) :
    std::runtime_error(what) {
}
