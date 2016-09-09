#ifndef NOOGEN_INJECTOR_INJECTOR_HPP
#define NOOGEN_INJECTOR_INJECTOR_HPP

#include <memory>


#define DECLARE(scope, var) DECLARE_##scope(var)

#define INJECT(scope, var, ...) INJECT_##scope(var, __VA_ARGS__)
#define INJECT_PTR(scope, ptr, ...) INJECT_PTR_##scope(ptr, __VA_ARGS__)
#define INJECT_PTR_STATIC(scope, ptrType, ptr, ...) INJECT_PTR_STATIC_##scope(ptrType, ptr, __VA_ARGS__)
#define INJECT_PTR_DYNAMIC(scope, ptrType, ptr, ...) INJECT_PTR_DYNAMIC_##scope(ptrType, ptr, __VA_ARGS__)

#define CREATE(scope, var, ...) CREATE_##scope(var, __VA_ARGS__)
#define CREATE_PTR(scope, ptrType, ptr, ...) CREATE_PTR_##scope(ptrType, ptr, __VA_ARGS__)
#define CREATE_PTR_STATIC(scope, ptrType, ptr, ...) CREATE_PTR_STATIC_##scope(ptrType, ptr, __VA_ARGS__)
#define CREATE_PTR_DYNAMIC(scope, ptrType, ptr, ...) CREATE_PTR_DYNAMIC_##scope(ptrType, ptr, __VA_ARGS__)


#define INNER_DECLARE(varType, var) varType var

#define INNER_INJECT_STATIC(varType, var, ...) var = varType{__VA_ARGS__}

#define INNER_INJECT_DYNAMIC_PROXY(proxyType, varType, var, ...) var = proxyType(new varType(__VA_ARGS__))

#define INNER_INJECT_PTR_STATIC(implType, ptr, ...) \
implType ptr##_imp_tmp_{__VA_ARGS__};\
ptr = &ptr##_imp_tmp_

#define INNER_INJECT_PTR_DYNAMIC(implType, ptr, ...) ptr = new implType(__VA_ARGS__)

#define INNER_INJECT_PTR_DYNAMIC_SHARED(ptrType, implType, ptr, ...) \
auto ptr##_tmp_ = std::make_shared<implType>(__VA_ARGS__);\
ptr = ptr##_tmp_.get()


#define INNER_CREATE_STATIC(varType, var, ...) varType var{__VA_ARGS__}

#define INNER_CREATE_DYNAMIC_PROXY(proxyType, varType, var, ...) proxyType INNER_INJECT_DYNAMIC_PROXY(proxyType, varType, var,__VA_ARGS__)

#define INNER_CREATE_PTR_STATIC(ptrType, implType, ptr, ...) \
INNER_DECLARE(ptrType, ptr);\
INNER_INJECT_PTR_STATIC(implType, ptr, __VA_ARGS__)

#define INNER_CREATE_PTR_DYNAMIC(ptrType, implType, ptr, ...) ptrType INNER_INJECT_PTR_DYNAMIC(implType, ptr, __VA_ARGS__)

#define INNER_CREATE_PTR_DYNAMIC_SHARED(ptrType, implType, ptr, ...) \
INNER_DECLARE(ptrType, ptr);\
INNER_INJECT_PTR_DYNAMIC_SHARED(ptrType, implType, ptr, __VA_ARGS__)\


#endif // NOOGEN_INJECTOR_INJECTOR_HPP
