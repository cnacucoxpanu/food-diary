#include "../../header.h"

Command::Command() {}

Command::~Command() {}

std::ostream& operator<<(std::ostream& os, const Command& cmd) {
    os << cmd.getName() << ": " << cmd.getDescription();
    return os;
}