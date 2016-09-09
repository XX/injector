#include "catch.hpp"
#include "noogen/injector/injector.hpp"
#include "noogen/injector/TestInterface.hpp"
#include "noogen/injector/TestImplementation.hpp"
#include "noogen/injector/TestImplementationProxy.hpp"

using namespace noogen::injector;

/**
 * Injector definitions
 */

#define DECLARE_test_reactor_common_injector_DECLARE_Interface_1(var) INNER_DECLARE(TestImplementation, var)

#define INJECT_test_reactor_common_injector_INJECT_Interface_1(var, ...) INNER_INJECT_STATIC(TestImplementation, var, __VA_ARGS__)
#define INJECT_test_reactor_common_injector_INJECT_Interface_2(var, ...) INNER_INJECT_DYNAMIC_PROXY(TestImplementationProxy, TestImplementation, var, __VA_ARGS__)

#define INJECT_PTR_test_reactor_common_injector_INJECT_PTR_Interface(ptrType, ptr, ...) INNER_INJECT_PTR_DYNAMIC_SHARED(ptrType, TestImplementation, ptr, __VA_ARGS__)
#define INJECT_PTR_STATIC_test_reactor_common_injector_INJECT_PTR_Interface(ptrType, ptr, ...) INNER_INJECT_PTR_STATIC(ptrType, TestImplementation, ptr, __VA_ARGS__)
#define INJECT_PTR_DYNAMIC_test_reactor_common_injector_INJECT_PTR_Interface(ptrType, ptr, ...) INNER_INJECT_PTR_DYNAMIC(ptrType, TestImplementation, ptr, __VA_ARGS__)

#define CREATE_test_reactor_common_injector_CREATE_Interface_1(var, ...) INNER_CREATE_STATIC(TestImplementation, var, __VA_ARGS__)
#define CREATE_test_reactor_common_injector_CREATE_Interface_2(var, ...) INNER_CREATE_DYNAMIC_PROXY(TestImplementationProxy, TestImplementation, var, __VA_ARGS__)

#define CREATE_PTR_test_reactor_common_injector_CREATE_PTR_Interface(ptrType, ptr, ...) INNER_CREATE_PTR_DYNAMIC_SHARED(ptrType, TestImplementation, ptr, __VA_ARGS__)
#define CREATE_PTR_STATIC_test_reactor_common_injector_CREATE_PTR_Interface(ptrType, ptr, ...) INNER_CREATE_PTR_STATIC(ptrType, TestImplementation, ptr, __VA_ARGS__)
#define CREATE_PTR_DYNAMIC_test_reactor_common_injector_CREATE_PTR_Interface(ptrType, ptr, ...) INNER_CREATE_PTR_DYNAMIC(ptrType, TestImplementation, ptr, __VA_ARGS__)

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
    DECLARE(test_reactor_common_injector_DECLARE_Interface_1, test);
    test.init(1);
    REQUIRE( test.getValue() == 1 );
}

TEST_CASE("injector INJECT macros is correct", "[injector.INJECT]") {
    DECLARE(test_reactor_common_injector_DECLARE_Interface_1, test1);
    INJECT(test_reactor_common_injector_INJECT_Interface_1, test1);
    test1.init(1);
    REQUIRE( test1.getValue() == 1 );
}

TEST_CASE("injector CREATE macros is correct", "[injector.CREATE]") {
    CREATE(test_reactor_common_injector_CREATE_Interface_1, test1);
    test1.init(1);
    REQUIRE( test1.getValue() == 1 );

    CREATE(test_reactor_common_injector_CREATE_Interface_2, test2);
    test2.init(2);
    REQUIRE( test2.getValue() == 2 );

    CREATE(test_reactor_common_injector_CREATE_Interface_1, test3, 3);
    REQUIRE( test3.getValue() == 3 );
}

TEST_CASE("injector CREATE_PTR macroses is correct", "[injector.CREATE_PTR]") {
    CREATE_PTR(test_reactor_common_injector_CREATE_PTR_Interface, TestInterface *, test1);
    test1->init(1);
    REQUIRE( test1->getValue() == 1 );

    CREATE_PTR_STATIC(test_reactor_common_injector_CREATE_PTR_Interface, TestInterface *, test2);
    test2->init(2);
    REQUIRE( test2->getValue() == 2 );

    CREATE_PTR_DYNAMIC(test_reactor_common_injector_CREATE_PTR_Interface, TestInterface *, test3, 3);
    REQUIRE( test3->getValue() == 3 );
}