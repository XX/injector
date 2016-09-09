#ifndef NOOGEN_INJECTOR_TESTIMPLEMENTATION_PROXY_HPP
#define NOOGEN_INJECTOR_TESTIMPLEMENTATION_PROXY_HPP

#include "noogen/injector/TestInterface.hpp"

namespace noogen { namespace injector {

/**
 * Example proxy implementation
 */
class TestImplementationProxy : public TestInterface {
protected:
    TestInterface *implPtr;

public:
    TestImplementationProxy(TestInterface *ptr) { implPtr = ptr; }
    ~TestImplementationProxy() { delete implPtr; }

    void init(int value) { implPtr->init(value); }
    int getValue() { return implPtr->getValue(); };
};

}} // namespace noogen::injector

#endif // NOOGEN_INJECTOR_TESTIMPLEMENTATION_PROXY_HPP
