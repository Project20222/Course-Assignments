#ifndef CBUFFER_H
#define CBUFFER_H

#include <cstddef>

template <typename T, size_t SIZE>
class CBuffer
{
private:
    T buffer[SIZE]{};
    size_t elem_num{0};
    size_t head{0}, tail{0};

public:
    CBuffer(const CBuffer &) = delete;
    CBuffer &operator=(const CBuffer &) = delete;
    CBuffer() { static_assert(SIZE > 1, "SIZE shall be greater than 1"); };

    T peek(void)
    {
        return buffer[head];
    }

    T read(void)
    {
        T data = buffer[head];
        if (elem_num > 0) // If the buffer is not empty
        {
            elem_num--;
            head = (head + 1) % SIZE;
        }
        return data;
    }

    void clear(void)
    {
        head = 0;
        tail = 0;
        elem_num = 0;
    }

    bool isfull(void)
    {
        return (elem_num == SIZE);
    }

    void write(const T &value)
    {
        buffer[tail] = value;
        tail = (tail + 1U) % SIZE;

        if (elem_num == SIZE) // If the buffer is full, the oldest element is overwritten.
        {
            head = (head + 1U) % SIZE; // We need to move head
        }
        else
        {
            elem_num++;
        }
    }

    size_t available(void)
    {
        return elem_num;
    }
};

#endif /* CBUFFER_H */
