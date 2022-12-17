#ifndef FTD_DATA_OPTION_HPP
#define FTD_DATA_OPTION_HPP

#include <cstdint>
#include <type_traits>
#include <utility>

namespace ftd{

template <typename Contained>
struct Option{
private:
    uint8_t data[sizeof (Contained)] = {0};
    bool initialized{false};

    [[nodiscard]] constexpr Contained&
    get_data() noexcept {
        return *reinterpret_cast<Contained*>(data);
    }

    [[nodiscard]] constexpr const Contained&
    get_data() const noexcept {
        return *reinterpret_cast<const Contained*>(data);
    }

public:
    constexpr Option() noexcept = default;

    constexpr Option& operator=(const Option& other) noexcept requires(std::is_copy_assignable_v<Contained>) {
        if (!other.initialized)
            return *this;

        if (initialized && !std::is_trivially_destructible_v<Contained>) {
            initialized = false;
            get_data().~Contained();
        }

        new(data) Contained(other.get_data());
        initialized = true;
        return *this;
    }

    constexpr Option& operator=(Option&& other) noexcept requires(std::is_move_assignable_v<Contained>) {
        if (!other.initialized)
            return *this;

        other.initialized = false;

        if (initialized && !std::is_trivially_destructible_v<Contained>) {
            initialized = false;
            get_data().~Contained();
        }

        new(data) Contained(std::move(other.get_data()));
        initialized = true;
        return *this;
    }

    constexpr Option(const Contained& contained) noexcept requires(std::is_copy_constructible_v<Contained>) {
        if (initialized && !std::is_trivially_destructible_v<Contained>) {
            initialized = false;
            get_data().~Contained();
        }

        new(data) Contained(contained);
        initialized = true;
    }

    constexpr Option(Contained&& contained) noexcept requires(std::is_move_constructible_v<Contained>) {
        if (initialized && !std::is_trivially_destructible_v<Contained>) {
            initialized = false;
            get_data().~Contained();
        }

        new(data) Contained(std::move(contained));
        initialized = true;
    }

    constexpr Option& operator=(const Contained& contained) noexcept requires(std::is_copy_assignable_v<Contained>) {
        if (initialized && !std::is_trivially_destructible_v<Contained>) {
            initialized = false;
            get_data().~Contained();
        }

        new(data) Contained(contained);
        initialized = true;
        return *this;
    }

    constexpr Option& operator=(Contained&& contained) noexcept requires(std::is_move_assignable_v<Contained>) {
        if (initialized && !std::is_trivially_destructible_v<Contained>) {
            initialized = false;
            get_data().~Contained();
        }

        new(data) Contained(std::move(contained));
        initialized = true;
        return *this;
    }

    [[nodiscard("Result of is_initialized should be used")]] constexpr bool
    is_initialized() const noexcept {
        return initialized;
    }

    [[nodiscard("Result of is_initialized should be used")]] constexpr
    operator bool() const noexcept {
        return initialized;
    }

    [[nodiscard("Cannot discard Option's value")]] constexpr const Contained&
    value() const noexcept {
        if (!initialized) {
            // Creating a segfault instead of throwing an exception
            // to encourage correct usage of the API
            int *ptr = nullptr;
            *ptr = 1;
        }

        return get_data();
    }

    [[nodiscard("Cannot discard Option's value")]] constexpr Contained&
    value() noexcept {
        if (!initialized) {
            // Creating a segfault instead of throwing an exception
            // to encourage correct usage of the API
            int *ptr = nullptr;
            *ptr = 1;
        }

        return get_data();
    }

    [[nodiscard("Cannot discard Option's value")]] constexpr const Contained&
    operator*() const noexcept {
        return value();
    }

    [[nodiscard("Cannot discard Option's value")]] constexpr Contained&
    operator*() noexcept {
        return value();
    }

    [[nodiscard("Option does not hold value anymore")]] constexpr Contained
    unwrap() noexcept {
        initialized = false;
        return std::move(get_data());
    }

    [[nodiscard("Option does not hold value anymore")]] constexpr Contained
    unwrap_or(Contained&& def) noexcept {
        if (!initialized)
            return std::forward(def);

        initialized = false;
        return std::move(get_data());
    }

    constexpr ~Option() noexcept requires(!std::is_trivially_destructible_v<Contained>) {
        if (initialized) {
            get_data().~Contained();
        }
    }

    constexpr ~Option() noexcept requires(std::is_trivially_destructible_v<Contained>) = default;

};

template<typename Contained>
[[nodiscard]] constexpr Option<Contained>
make_option(std::nullptr_t) noexcept {
    return Option<Contained>{};
}

template <typename Contained>
[[nodiscard]] constexpr Option<std::remove_cvref_t<Contained>>
make_option(Contained&& c) noexcept {
    return Option{std::forward<Contained>(c)};
}

template <typename Contained, typename ...Args>
[[nodiscard]] constexpr Option<Contained>
make_option(Args&& ...args) noexcept requires (std::is_constructible_v<Contained, Args...>) {
    return Option(Contained{std::forward<Args>(args)...});
}
}
#endif
