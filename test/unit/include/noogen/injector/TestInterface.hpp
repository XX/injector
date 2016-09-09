#ifndef NOOGEN_INJECTOR_TESTINTERFACE_HPP
#define NOOGEN_INJECTOR_TESTINTERFACE_HPP

namespace noogen { namespace injector {

/**
 * Example interface
 */
class TestInterface {
public:
    virtual void init(int value) = 0;
    virtual int getValue() = 0;
};

}} // namespace noogen::injector

#endif // NOOGEN_INJECTOR_TESTINTERFACE_HPP
