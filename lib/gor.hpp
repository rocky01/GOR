#ifndef GOR_HPP_
#define GOR_HPP_

#include <cstring>
#include <iostream>
#include <memory>

#if __cplusplus > 201402L
#include <optional>
#endif


namespace gor //  get or return
{
namespace internal
{

struct CastableToReturnType
{
    template <typename T>
    operator T*() const
    {
        return nullptr;
    }

    template <typename T>
    operator std::unique_ptr<T>() const
    {
        return nullptr;
    }

    template <typename T>
    operator std::shared_ptr<T>() const
    {
        return nullptr;
    }

#if __cplusplus > 201402L
    template <typename T>
    operator std::optional<T>() const
    {
        return std::nullopt;
    }
#endif
};

template<bool>
constexpr auto returnVal();

template<>
inline constexpr auto returnVal<true>()
{
    return void();
}

template<>
inline constexpr auto returnVal<false>()
{
    return CastableToReturnType{};
}

}  // namespace internal
}  // namespace gor

#define TRY(expression)                                                                                               \
    __extension__({                                                                                                   \
        auto result = expression;                                                                                     \
        if (!result)                                                                                                  \
        {                                                                                                             \
            std::cerr << __FILE__ << ":" << __LINE__ << " TRY: " << #expression << " return null." << std::endl;      \
            constexpr bool is_void = memcmp(__PRETTY_FUNCTION__, "void ", 5) == 0;                                    \
            return gor::internal::returnVal<is_void>();                                                               \
        }                                                                                                             \
        std::move(result);                                                                                            \
    })

#endif  // GOR_HPP_
