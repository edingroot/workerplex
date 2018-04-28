#ifndef WORKERPLEX_EXCEPTIONS_HPP
#define WORKERPLEX_EXCEPTIONS_HPP

#include <stdexcept>

class command_not_found : public std::runtime_error {
public:
    command_not_found(const std::string &what);

    ~command_not_found() throw() = default;
};


#endif //WORKERPLEX_EXCEPTIONS_HPP
