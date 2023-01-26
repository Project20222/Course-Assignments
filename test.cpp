#include <unity.h>
#include "cbuffer.h"

#define CBUFFER_SIZE 8

void setUp()
{
}

void tearDown()
{
}

void test_cbuffer_clear(void)
{
    CBuffer<int, CBUFFER_SIZE> buffer;

    buffer.write(100U);
    TEST_ASSERT_EQUAL_UINT8(1U, buffer.available());
    TEST_ASSERT_FALSE(buffer.isfull());

    buffer.write(110U);
    TEST_ASSERT_EQUAL_UINT8(2U, buffer.available());
    TEST_ASSERT_FALSE(buffer.isfull());

    TEST_ASSERT_EQUAL_UINT8(100U, buffer.read());
    TEST_ASSERT_EQUAL_UINT8(1U, buffer.available());
    TEST_ASSERT_FALSE(buffer.isfull());

    buffer.clear();

    TEST_ASSERT_FALSE(buffer.isfull());
    TEST_ASSERT_EQUAL_UINT8(0U, buffer.available());
}

void test_read_write_buffer(void)
{
    CBuffer<int, CBUFFER_SIZE> buffer;

    for (uint8_t i = 0U; i < CBUFFER_SIZE - 3U; i++)
    {
        buffer.write(i + 1);
        TEST_ASSERT_EQUAL_UINT8(i + 1, buffer.available());
        TEST_ASSERT_FALSE(buffer.isfull());
    }

    TEST_ASSERT_EQUAL_UINT8(1U, buffer.peek());
    TEST_ASSERT_EQUAL_UINT8(CBUFFER_SIZE - 3U, buffer.available());
    TEST_ASSERT_FALSE(buffer.isfull());

    TEST_ASSERT_EQUAL_UINT8(1U, buffer.read());
    TEST_ASSERT_EQUAL_UINT8(CBUFFER_SIZE - 4U, buffer.available());
    TEST_ASSERT_FALSE(buffer.isfull());

    TEST_ASSERT_EQUAL_UINT8(2U, buffer.read());
    TEST_ASSERT_EQUAL_UINT8(CBUFFER_SIZE - 5U, buffer.available());
    TEST_ASSERT_FALSE(buffer.isfull());

    TEST_ASSERT_EQUAL_UINT8(3U, buffer.read());
    TEST_ASSERT_EQUAL_UINT8(CBUFFER_SIZE - 6U, buffer.available());
    TEST_ASSERT_FALSE(buffer.isfull());

    for (uint8_t i = 0U; i < 4U; i++)
    {
        buffer.write(i + 1U);
        TEST_ASSERT_EQUAL_UINT8(CBUFFER_SIZE - 5U + i, buffer.available());
        TEST_ASSERT_FALSE(buffer.isfull());
    }

    TEST_ASSERT_EQUAL_UINT8(4U, buffer.read());
    TEST_ASSERT_EQUAL_UINT8(CBUFFER_SIZE - 3U, buffer.available());
    TEST_ASSERT_FALSE(buffer.isfull());
}

void test_read_empty_buffer(void)
{
    CBuffer<int, CBUFFER_SIZE> buffer;

    buffer.read();
    TEST_ASSERT_FALSE(buffer.isfull());
    TEST_ASSERT_EQUAL_UINT8(0U, buffer.available());

    buffer.write(100U);
    TEST_ASSERT_EQUAL_UINT8(1U, buffer.available());
    TEST_ASSERT_FALSE(buffer.isfull());

    buffer.write(110U);
    TEST_ASSERT_EQUAL_UINT8(2U, buffer.available());
    TEST_ASSERT_FALSE(buffer.isfull());

    TEST_ASSERT_EQUAL_UINT8(100U, buffer.read());
    TEST_ASSERT_EQUAL_UINT8(1U, buffer.available());
    TEST_ASSERT_FALSE(buffer.isfull());

    TEST_ASSERT_EQUAL_UINT8(110U, buffer.read());
    TEST_ASSERT_EQUAL_UINT8(0U, buffer.available());
    TEST_ASSERT_FALSE(buffer.isfull());

    buffer.read();
    TEST_ASSERT_FALSE(buffer.isfull());
    TEST_ASSERT_EQUAL_UINT8(0U, buffer.available());

    buffer.write(100U);
    TEST_ASSERT_EQUAL_UINT8(100U, buffer.read());
    TEST_ASSERT_EQUAL_UINT8(0U, buffer.available());
    TEST_ASSERT_FALSE(buffer.isfull());
}

void test_read_full_buffer(void)
{
    CBuffer<int, CBUFFER_SIZE> buffer;

    for (uint8_t i = 0U; i < CBUFFER_SIZE; i++)
    {
        buffer.write(i + 1);
        TEST_ASSERT_EQUAL_UINT8(i + 1, buffer.available());
    }
    TEST_ASSERT_TRUE(buffer.isfull());
    TEST_ASSERT_EQUAL_UINT8(CBUFFER_SIZE, buffer.available());

    TEST_ASSERT_EQUAL_UINT8(1U, buffer.peek());
    TEST_ASSERT_EQUAL_UINT8(CBUFFER_SIZE, buffer.available());
    TEST_ASSERT_TRUE(buffer.isfull());

    TEST_ASSERT_EQUAL_UINT8(1U, buffer.read());
    TEST_ASSERT_EQUAL_UINT8(CBUFFER_SIZE - 1U, buffer.available());
    TEST_ASSERT_FALSE(buffer.isfull());
}

void test_write_empty_buffer(void)
{
    CBuffer<int, CBUFFER_SIZE> buffer;

    buffer.write(1U);
    TEST_ASSERT_EQUAL_UINT8(1U, buffer.available());
    TEST_ASSERT_FALSE(buffer.isfull());

    TEST_ASSERT_EQUAL_UINT8(1U, buffer.read());
    TEST_ASSERT_EQUAL_UINT8(0U, buffer.available());
    TEST_ASSERT_FALSE(buffer.isfull());

    buffer.write(1U);
    TEST_ASSERT_EQUAL_UINT8(1U, buffer.available());
    TEST_ASSERT_FALSE(buffer.isfull());

    TEST_ASSERT_EQUAL_UINT8(1U, buffer.read());
    TEST_ASSERT_EQUAL_UINT8(0U, buffer.available());
    TEST_ASSERT_FALSE(buffer.isfull());
}

void test_write_full_buffer(void)
{
    CBuffer<int, CBUFFER_SIZE> buffer;

    for (uint8_t i = 0U; i < CBUFFER_SIZE; i++)
    {
        buffer.write(i + 1U);
        TEST_ASSERT_EQUAL_UINT8(i + 1U, buffer.available());
    }
    TEST_ASSERT_TRUE(buffer.isfull());
    TEST_ASSERT_EQUAL_UINT8(CBUFFER_SIZE, buffer.available());

    buffer.write(0U);
    TEST_ASSERT_TRUE(buffer.isfull());
    TEST_ASSERT_EQUAL_UINT8(CBUFFER_SIZE, buffer.available());

    TEST_ASSERT_EQUAL_UINT8(2U, buffer.peek());
    TEST_ASSERT_EQUAL_UINT8(CBUFFER_SIZE, buffer.available());
    TEST_ASSERT_TRUE(buffer.isfull());

    TEST_ASSERT_EQUAL_UINT8(2U, buffer.read());
    TEST_ASSERT_EQUAL_UINT8(CBUFFER_SIZE - 1U, buffer.available());
    TEST_ASSERT_FALSE(buffer.isfull());
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_cbuffer_clear);
    RUN_TEST(test_read_write_buffer);
    RUN_TEST(test_read_empty_buffer);
    RUN_TEST(test_read_full_buffer);
    RUN_TEST(test_write_empty_buffer);
    RUN_TEST(test_write_full_buffer);

    return UNITY_END();
}
