#include "StateResponse.hpp"

#include <stdexcept>

/// This constructor is kept private so that the only way to create a
/// StateResponse is through the static methods, and allows to make a static
/// instance for the valid state, which can be shared across the entire program.
StateResponse::StateResponse(bool valid, std::optional<std::string> reason)
    : _valid(valid), _reason(std::move(reason)) {}

bool StateResponse::valid() const {
    return _valid;
}

std::string_view StateResponse::reason() const {
    if (_valid || !_reason.has_value()) {
        throw std::logic_error("The state is valid");
    }

    return _reason.value();
}

StateResponse StateResponse::merge(const StateResponse& other) const {
    return valid() ? other : *this;
}

StateResponse StateResponse::ok() {
    return StateResponse(true);
}

StateResponse StateResponse::nok(std::string reason) {
    return StateResponse(false, std::move(reason));
}

std::ostream& StateResponse::formatToStream(std::ostream& os) const {
    if (valid()) {
        return os << "valid";
    }

    return os << "### " << reason();
}

std::ostream& operator<<(std::ostream& os, const StateResponse& response) {
    return response.formatToStream(os);
}
