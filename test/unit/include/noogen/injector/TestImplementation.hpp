#ifndef NOOGEN_INJECTOR_TESTIMPLEMENTATION_HPP
#define NOOGEN_INJECTOR_TESTIMPLEMENTATION_HPP

#include "noogen/injector/TestInterface.hpp"

namespace noogen { namespace injector {

/**
 * Example implementation
 */
class TestImplementation : public TestInterface {
public:
    TestImplementation() {}
    TestImplementation(int value) { this->value = value; }

    void init(int value) { this->value = value; }
    int getValue() { return value; }

private:
    int value;
};

}} // namespace noogen::injector

#endif // NOOGEN_INJECTOR_TESTIMPLEMENTATION_HPP
