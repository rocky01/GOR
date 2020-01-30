#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "gor.hpp"

namespace
{

// unique ptr

std::unique_ptr<int> getVal(std::unique_ptr<int> val)
{
    return val;
}

std::unique_ptr<int> doSomething(
    std::unique_ptr<int> valueToGet,
    std::unique_ptr<int> valueToReturn)
{
    std::unique_ptr<int> x = TRY(getVal(std::move(valueToGet))); // main functionality

    return valueToReturn;
}

// shared ptr

std::shared_ptr<int> getVal(std::shared_ptr<int> val)
{
    return val;
}

std::shared_ptr<int> doSomething(
    std::shared_ptr<int> valueToGet,
    std::shared_ptr<int> valueToReturn)
{
    std::shared_ptr<int> x = TRY(getVal(valueToGet)); // main functionality

    return valueToReturn;
}

// row ptr

const char* getVal(const char* val)
{
    return val;
}

const int* doSomething(
    const char* valueToGet,
    const int* valueToReturn)
{
    const char* x = TRY(getVal(valueToGet)); // main functionality

    return valueToReturn;
}

#if __cplusplus > 201402L
// std optional

std::optional<char> getVal(std::optional<char> val)
{
    return val;
}

std::optional<int> doSomething(
    std::optional<char> valueToGet,
    std::optional<int> valueToReturn)
{
    std::optional<char> x = TRY(getVal(valueToGet)); // main functionality

    return valueToReturn;
}
#endif
// row ptr and bool

bool getVal(bool val)
{
    return val;
}

const char* doSomething(
    bool valueToGet,
    const char* valueToReturn)
{
    bool x = TRY(getVal(valueToGet)); // main functionality

    return valueToReturn;
}

//void

void tryGetValEarlyReturn(bool valueToGet, std::string& modifiedValue)
{
    modifiedValue = "there was exception handled by TRY";
    bool x = TRY(getVal(valueToGet)); // main functionality
    modifiedValue = "no exception, normal leave";
}

void tryGetValLateReturn(bool valueToGet, std::string& modifiedValue)
{
    modifiedValue = "there was exception handled by TRY";
    bool x = TRY(getVal(valueToGet)); // main functionality
    modifiedValue = "no exception, normal leave";
}

} // namespace


// UniquePtr

TEST(Test, UniquePtrNull)
{
    std::unique_ptr<int> valueToGet = nullptr;
    std::unique_ptr<int> valueToReturn = std::make_unique<int>(5);

    auto result = doSomething(std::move(valueToGet), std::move(valueToReturn));

    ASSERT_TRUE(result == nullptr);
}

TEST(Test, UniquePtrNotNull)
{
    std::unique_ptr<int> valueToGet = std::make_unique<int>(10);
    std::unique_ptr<int> valueToReturn = std::make_unique<int>(5);

    auto result = doSomething(std::move(valueToGet), std::move(valueToReturn));

    ASSERT_TRUE(*result == 5);
}

// shared ptr

TEST(Test, SharedPtrNull)
{
    std::shared_ptr<int> valueToGet = nullptr;
    std::shared_ptr<int> valueToReturn = std::make_shared<int>(52);

    auto result = doSomething(valueToGet, valueToReturn);

    ASSERT_TRUE(result == nullptr);
}

TEST(Test, SharedPtrNotNull)
{
    std::shared_ptr<int> valueToGet = std::make_shared<int>(101);
    std::shared_ptr<int> valueToReturn = std::make_shared<int>(52);

    auto result = doSomething(valueToGet, valueToReturn);

    ASSERT_TRUE(*result == 52);
}

// Row Ptr

TEST(Test, GetRowPointerNull)
{
    const char* valueToGet = nullptr;
    const int* valueToReturn = new int(1234);

    auto result = doSomething(valueToGet, valueToReturn);

    ASSERT_TRUE(result == nullptr);
}

TEST(Test, GetRowPointerNotNull)
{
    const char* valueToGet = new char('w');
    const int* valueToReturn = new int(1234);

    auto result = doSomething(valueToGet, valueToReturn);

    ASSERT_TRUE(*result == 1234);
}

#if __cplusplus > 201402L
// optional

TEST(Test, GetOptionalNull)
{
    std::optional<char> valueToGet = std::nullopt;
    std::optional<int> valueToReturn = 4321;

    auto result = doSomething(valueToGet, valueToReturn);

    ASSERT_TRUE(result == std::nullopt);
}

TEST(Test, GetOptionalNotNull)
{
    std::optional<char> valueToGet = 'e';
    std::optional<int> valueToReturn = 4321;

    auto result = doSomething(valueToGet, valueToReturn);

    ASSERT_TRUE(result == 4321);
}
#endif

// bool and row ptr

TEST(Test, GetRowPtrNull_Bool)
{
    bool valueToGet = false;
    const char* valueToReturn = new char('S');

    auto result = doSomething(valueToGet, valueToReturn);

    ASSERT_TRUE(result == nullptr);
}

TEST(Test, GetRowPtrNotNull_Bool)
{
    bool valueToGet = true;
    const char* valueToReturn = new char('S');

    auto result = doSomething(valueToGet, valueToReturn);

    ASSERT_TRUE(*result == 'S');
}

// void as return value

TEST(Test, GetVoidNull_Bool)
{
    bool valueToGet = false;
    std::string modifiedValue;

    tryGetValEarlyReturn(valueToGet, modifiedValue);
    ASSERT_TRUE(modifiedValue == "there was exception handled by TRY");
}

TEST(Test, GetVoidNotNull_Bool)
{
    bool valueToGet = true;
    std::string modifiedValue;

    tryGetValLateReturn(valueToGet, modifiedValue);
    ASSERT_TRUE(modifiedValue == "no exception, normal leave");
}
