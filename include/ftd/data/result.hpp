#ifndef FTD_DATA_RESULT_HPP
#define FTD_DATA_RESULT_HPP

#include <algorithm>
#include <cstdint>
#include <type_traits>
#include <variant>

namespace ftd {

template <typename Ok, typename Err> requires(!std::is_same_v<Ok, Err>)
struct Result {
private:
    std::variant<std::monostate, Ok, Err> data;

public:
    constexpr Result() = delete;
    constexpr Result(const Result& other) = delete;
    constexpr Result& operator=(const Result& other) = delete;

    constexpr Result(Result&& other) = default;
    constexpr Result& operator=(Result&& other) = default;

    constexpr Result(Ok&& ok)
        : data(std::forward<Ok>(ok)) {}
    constexpr Result(Err&& err)
        : data(std::forward<Err>(err)) {}

    [[nodiscard]] constexpr bool
    is_ok() const noexcept {
        return data.index() == 1;
    }

    [[nodiscard]] constexpr bool
    is_err() const noexcept {
        return data.index() == 2;
    }

    [[nodiscard]] constexpr Ok
    unwrap() {
        return std::move(std::get<Ok>(data));
    }

    [[nodiscard]] constexpr Err
    unwrap_err() {
        return std::move(std::get<Err>(data));
    }
};

}

#endif
