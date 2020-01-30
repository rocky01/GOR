#include "gtest/gtest.h"

#include "gor.hpp"

#if __cplusplus > 201402L // Needed to omit compilation errors as std::optional from c++17 was used

std::unique_ptr<int> getVal(bool isProperValue)
{
    if (isProperValue)
        return std::make_unique<int>(10);
    return nullptr;
}

std::optional<int> doSomething(bool isProperValue)
{
    // MAIN FUNCTIONALITY (TRY macro)
    std::unique_ptr<int> x = TRY(getVal(isProperValue)); // try to get proper value if possible if not print message
                                                 // and return std::nullopt

    *x = *x + 10; // do some operation on "x" we can be sure that "x" have some value (is not nullptr)
    return *x;
}


TEST(Test, SimpleTest_ExceptionHandledByTRY)
{
    bool isProperValueReturnedByGetFunction = false;
    std::optional<int> result = doSomething(isProperValueReturnedByGetFunction);

    ASSERT_TRUE(result == std::nullopt);
}

TEST(Test, SimpleTest_NoException)
{
    bool isProperValueReturnedByGetFunction = true;
    std::optional<int> result = doSomething(isProperValueReturnedByGetFunction);

    ASSERT_TRUE(result != std::nullopt);
    ASSERT_TRUE(*result == 20);
}

#endif
