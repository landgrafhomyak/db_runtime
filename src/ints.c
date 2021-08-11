#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <db_runtime.h>

static uint_least16_t _is_le = 1;
#define IS_LE (*(uint8_t *)&_is_le)

static inline int is_le()
{}

static void reverse(void *dst, void *src, size_t size)
{
    uintptr_t src_p = (uintptr_t) src;
    uintptr_t dst_p = (uintptr_t) dst;
    dst_p += size;
    while (size-- > 0)
    {
        memcpy((void *) (--dst_p), (void *) (src_p++), 1);
    }
}

void *dump_int_be(void *encoded, void *decoded, size_t size, size_t type_size)
{
    if (IS_LE)
    {
        reverse(encoded, decoded, size);
    }
    else
    {
        memcpy(encoded, (void *) ((uintptr_t) decoded + type_size - size), size);
    }
    return encoded;
}

void *parse_int_be(void *decoded, void *encoded, size_t size, size_t type_size)
{
    if (IS_LE)
    {
        reverse(decoded, encoded, size);
        memset((void *) ((uintptr_t) decoded + size), 0, type_size - size);
    }
    else
    {
        memset(decoded, 0, type_size - size);
        memcpy((void *) ((uintptr_t) decoded + type_size - size), encoded, size);
    }
    return decoded;
}

void *dump_int_le(void *encoded, void *decoded, size_t size, size_t type_size)
{
    if (IS_LE)
    {
        memcpy(encoded, decoded, size);
    }
    else
    {
        reverse(encoded, (void *) ((uintptr_t) decoded + type_size - size), size);
    }
    return encoded;
}

void *parse_int_le(void *decoded, void *encoded, size_t size, size_t type_size)
{
    if (IS_LE)
    {
        memcpy(decoded, encoded, size);
        memset((void *) ((uintptr_t) decoded + size), 0, type_size - size);
    }
    else
    {
        memset(decoded, 0, type_size - size);
        reverse((void *) ((uintptr_t) decoded + type_size - size), encoded, size);
    }
    return decoded;
}