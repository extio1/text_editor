#include <iostream>
#include <ostream>
#include <vector>

/*
 * Template implementation of circular buffer
 */
template <typename T>
class CircularBuffer {
   public:
    explicit CircularBuffer(size_t capacity)
        : buffer(std::vector<std::shared_ptr<T>>(capacity)),
          max_capacity(capacity),
          capacity(capacity),
          next_index(capacity) {}

    bool empty() { return capacity == 0; }

    void push(std::shared_ptr<T>&& obj) {
        buffer[next_index++] = std::move(obj);
        ++capacity;
    }

    std::shared_ptr<T> get_next() {
        if (capacity == max_capacity)
            return nullptr;

        ++capacity;
        return buffer[next_index++];
    }

    std::shared_ptr<T> pop() {
        if (capacity == 0)
            return nullptr;

        auto v = buffer[--next_index];
        --capacity;
        return v;
    }

   private:
    class CircularValue {
       public:
        CircularValue(std::size_t curr_value, std::size_t max_value)
            : val(curr_value), max_value(max_value) {}
        CircularValue(std::size_t max_value) : CircularValue(0, max_value) {}

        std::size_t operator++() {
            val = (val + 1) % max_value;
            return val;
        }
        std::size_t operator++(int) {
            std::size_t v = val;
            val = (val + 1) % max_value;
            return v;
        }

        std::size_t operator--() {
            val = (val > 0) ? val - 1 : max_value - 1;
            return val;
        }
        std::size_t operator--(int) {
            std::size_t v = val;
            val = (val > 0) ? val - 1 : max_value - 1;
            return v;
        }

        bool operator==(const int o) { return val == o; }

        std::size_t get_value() { return val; }

       private:
        std::size_t val;
        std::size_t max_value;
    };

    class LimitedValue {
       public:
        LimitedValue(std::size_t curr_value, std::size_t max_value)
            : val(curr_value), max_value(max_value) {}
        LimitedValue(std::size_t max_value) : LimitedValue(0, max_value) {}

        std::size_t operator++() {
            val = (val + 1 > max_value) ? val : val + 1;
            return val;
        }
        std::size_t operator++(int) {
            auto v = val;
            val = (val + 1 > max_value) ? val : val + 1;
            return v;
        }

        std::size_t operator--() {
            val = (val > 0) ? val - 1 : 0;
            return val;
        }
        std::size_t operator--(int) {
            auto v = val;
            val = (val > 0) ? val - 1 : 0;
            return v;
        }

        bool operator==(const int o) { return val == o; }

        std::size_t get_value() { return val; }

       private:
        std::size_t val;
        std::size_t max_value;
    };

    std::vector<std::shared_ptr<T>> buffer;
    std::size_t max_capacity;
    std::size_t current_end;
    CircularValue next_index;  // Index there to push new element
    LimitedValue capacity;    // Current number of elements in circular buffer
};