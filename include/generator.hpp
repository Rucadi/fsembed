#include <coroutine>
#include <optional>

template<typename T>
struct generator {
    // Inner class for coroutine promise type
    struct promise_type {
        std::optional<T> current_value;

        generator<T> get_return_object() {
            return generator{ std::coroutine_handle<promise_type>::from_promise(*this) };
        }

        std::suspend_always initial_suspend() const noexcept {
            return {};
        }

        std::suspend_always final_suspend() const noexcept {
            return {};
        }

        std::suspend_always yield_value(T value) noexcept {
            current_value = std::move(value);
            return {};
        }

        void return_void() noexcept {}

        void unhandled_exception() {
            std::terminate();  // Handle exceptions by terminating the program
        }
    };

    using handle_type = std::coroutine_handle<promise_type>;

    explicit generator(handle_type h) : coro(h) {}
    generator(generator const&) = delete;
    generator(generator&& other) noexcept : coro(other.coro) {
        other.coro = nullptr;
    }

    ~generator() {
        if (coro) coro.destroy();
    }

    // Iterator class for the generator
    struct iterator {
        handle_type coro;

        iterator() noexcept : coro(nullptr) {}
        iterator(handle_type coro) : coro(coro) {}

        iterator& operator++() {
            coro.resume();
            if (coro.done()) coro = nullptr;
            return *this;
        }

        bool operator==(const iterator& other) const {
            return coro == other.coro;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

        const T& operator*() const {
            return coro.promise().current_value.value();
        }

        const T* operator->() const {
            return &(operator*());
        }
    };

    iterator begin() {
        if (coro) {
            coro.resume();
            if (!coro.done()) {
                return iterator{ coro };
            }
        }
        return iterator{ nullptr };
    }

    iterator end() {
        return iterator{ nullptr };
    }

private:
    handle_type coro;
};
