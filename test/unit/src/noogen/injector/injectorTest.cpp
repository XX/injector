#include "catch.hpp"
#include "noogen/injector/injector.hpp"
#include "noogen/injector/TestInterface.hpp"
#include "noogen/injector/TestImplementation.hpp"
#include "noogen/injector/TestImplementationProxy.hpp"

using namespace noogen::injector;

/**
 * Injector definitions
 */

#define DECLARE_noogen_injector_TestInterface(var) INNER_DECLARE(TestImplementation, var)

#define INJECT_noogen_injector_TestInterface(var, ...) INNER_INJECT_STATIC(TestImplementation, var, __VA_ARGS__)
#define INJECT_noogen_injector_TestInterface_special(var, ...) INNER_INJECT_DYNAMIC_PROXY(TestImplementationProxy, TestImplementation, var, __VA_ARGS__)

#define INJECT_PTR_noogen_injector_TestInterface(ptrType, ptr, ...) INNER_INJECT_PTR_DYNAMIC_SHARED(ptrType, TestImplementation, ptr, __VA_ARGS__)
#define INJECT_PTR_STATIC_noogen_injector_TestInterface(ptrType, ptr, ...) INNER_INJECT_PTR_STATIC(ptrType, TestImplementation, ptr, __VA_ARGS__)
#define INJECT_PTR_DYNAMIC_noogen_injector_TestInterface(ptrType, ptr, ...) INNER_INJECT_PTR_DYNAMIC(ptrType, TestImplementation, ptr, __VA_ARGS__)

#define CREATE_noogen_injector_TestInterface(var, ...) INNER_CREATE_STATIC(TestImplementation, var, __VA_ARGS__)
#define CREATE_noogen_injector_TestInterface_special(var, ...) INNER_CREATE_DYNAMIC_PROXY(TestImplementationProxy, TestImplementation, var, __VA_ARGS__)

#define CREATE_PTR_noogen_injector_TestInterface(ptrType, ptr, ...) INNER_CREATE_PTR_DYNAMIC_SHARED(ptrType, TestImplementation, ptr, __VA_ARGS__)
#define CREATE_PTR_STATIC_noogen_injector_TestInterface(ptrType, ptr, ...) INNER_CREATE_PTR_STATIC(ptrType, TestImplementation, ptr, __VA_ARGS__)
#define CREATE_PTR_DYNAMIC_noogen_injector_TestInterface(ptrType, ptr, ...) INNER_CREATE_PTR_DYNAMIC(ptrType, TestImplementation, ptr, __VA_ARGS__)

/**
 * Test cases
 */

TestImplementation x = TestImplementation();
// CREATE(scope, x); +

// TestInterface xI = TestImplementation(); // -+
// DECLARE(scope, xI); INJECT(scope, xI); +
// TestInterface INJECT(scope, xI); -
// CREATE_TYPE(scope, TestInterface, xI); +

TestImplementation &xRI = x;
// DECLARE(scope, &xR) = x; +-
// DECLARE(scope, &xR = x); +-

TestInterface &xR = x;
// DECLARE(scope, &xR) = x; +-
// TestInterface &xR = x; +

TestInterface &&xRR = TestImplementation();
// TestInterface INJECT(scope, &&xRR); -
// CREATE_TYPE(scope, TestInterface, &&xRR); +

TestImplementation *xP = &x;
// DECLARE(scope, *xP); xP = &x; +
// DECLARE(scope, *xP) = &x; +-
// DECLARE(scope, *xP = &x); +-

TestInterface *xIP = &x;
// DECLARE(scope, *xPI); xPI = &x; +
// TestInterface *xIP = &x; +
// DECLARE(scope, *xIP) = &x; +-
// DECLARE(scope, *xIP = &x); +-

TestInterface *xIPN = new TestImplementation();
// CREATE_TYPE(scope, TestInterface, *xIPN);
// TestInterface *xIPN; INJECT_PTR(scope, xIPN); +

TestInterface **xIPP = &xIP;

const TestImplementation xC = TestImplementation();
const TestInterface *xPC = &x;
TestInterface * const xCP = &x;

TEST_CASE("injector DECLARE macros is correct", "[injector.DECLARE]") {
    DECLARE(noogen_injector_TestInterface, test);
    test.init(1);
    REQUIRE( test.getValue() == 1 );
}

TEST_CASE("injector INJECT macros is correct", "[injector.INJECT]") {
    DECLARE(noogen_injector_TestInterface, test1);
    INJECT(noogen_injector_TestInterface, test1);
    test1.init(1);
    REQUIRE( test1.getValue() == 1 );
}

TEST_CASE("injector CREATE macros is correct", "[injector.CREATE]") {
    CREATE(noogen_injector_TestInterface, test1);
    test1.init(1);
    REQUIRE( test1.getValue() == 1 );

    CREATE(noogen_injector_TestInterface_special, test2);
    test2.init(2);
    REQUIRE( test2.getValue() == 2 );

    CREATE(noogen_injector_TestInterface, test3, 3);
    REQUIRE( test3.getValue() == 3 );
}

TEST_CASE("injector CREATE_PTR macroses is correct", "[injector.CREATE_PTR]") {
    CREATE_PTR(noogen_injector_TestInterface, TestInterface *, test1);
    test1->init(1);
    REQUIRE( test1->getValue() == 1 );

    CREATE_PTR_STATIC(noogen_injector_TestInterface, TestInterface *, test2);
    test2->init(2);
    REQUIRE( test2->getValue() == 2 );

    CREATE_PTR_DYNAMIC(noogen_injector_TestInterface, TestInterface *, test3, 3);
    REQUIRE( test3->getValue() == 3 );
}