#pragma once

#include <iostream>
#include <list>

class Person;
class StateResponse;

/**
 * @brief Container class, holds a list of people
 */
class Container {
protected:
    /**
     * @brief Constructor
     * @param name name of the container
     * @param people people to add to the container
     */
    explicit Container(std::string name,
                       std::initializer_list<const Person*> people = {});

public:
    /**
     * Virtual default destructor to allow for polymorphism
     */
    virtual ~Container() noexcept = default;

    /** @return the size of the container */
    size_t size() const;

    /**
     * Checks if the container contains a given person
     * @return whether the person is contained in the container
     */
    bool contains(const Person& person) const;

    /**
     * Adds a person to the container
     * @param person the person to add
     * @return whether the person has been added
     */
    bool add(const Person& person);

    /**
     * Removes a person from the container
     * @param person the person to remove
     * @return whether the person has been removed
     */
    bool remove(const Person& person);

    /**
     * Clears the container
     */
    void clear();

    /**
     * Validate the state
     * @return whether the state is valid
     */
    virtual StateResponse validatePeople() const;

    /**
     * @return the start iterator of the list of people
     */
    std::list<const Person*>::const_iterator begin() const;

    /**
     * @return the end iterator of the list of people
     */
    std::list<const Person*>::const_iterator end() const;

    /**
     * Formats the container to a stream
     * @param os stream where the container will be formatted
     * @return the stream where the container has been formatted
     */
    virtual std::ostream& formatToStream(std::ostream& os) const;

protected:
    /** @return a space-separated list of the people in the container */
    [[nodiscard]] std::string listPeople() const;

private:
    std::string _name;
    std::list<const Person*> _people;
};

/**
 * Displays the container in a given stream
 * @param os stream where the container will be displayed
 * @param container container to display
 * @return the stream where the container has been displayed
 */
std::ostream& operator<<(std::ostream& os, const Container& container);