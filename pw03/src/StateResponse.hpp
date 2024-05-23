#pragma once

#include <iostream>
#include <optional>
#include <string>

/**
 * @brief Represents the response of a state validation.
 */
class StateResponse {
public:
    /**
     * @return whether the state is valid
     */
    bool valid() const;

    /**
     * @return the reason if the state is invalid
     * @throw std::logic_error if the state is valid
     */
    std::string_view reason() const;

    /**
     * Formats the response to a stream
     * @param os stream where the response will be formatted
     * @return the stream where the response has been formatted
     */
    virtual std::ostream& formatToStream(std::ostream& os) const;

    /**
     * Merges two state responses
     * @param other the other state response
     * @return the other state response if the current one is valid,
     *         the current one otherwise
     */
    StateResponse merge(const StateResponse& other) const;

    /**
     * @return construct a valid state response
     */
    static StateResponse ok();

    /**
     * @param reason the reason why the state is invalid
     * @return construct an invalid state response
     */
    static StateResponse nok(std::string reason);

private:
    explicit StateResponse(bool valid, std::optional<std::string> reason = std::nullopt);

    bool _valid;
    std::optional<std::string> _reason;
};

/**
 * Displays the response in a given stream
 * @param os stream where the response will be displayed
 * @param response response to display
 * @return the stream where the response has been displayed
 */
std::ostream& operator<<(std::ostream& os, const StateResponse& response);
