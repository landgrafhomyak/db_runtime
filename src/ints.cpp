#include <cstdint>
#include <cstdio>
#include <db_runtime.hpp>

template<class type, std::size_t size, class file_wrapper>
void dump_uint_be(file_wrapper f, type decoded)
{
    type buffer;
    std::uint8_t *pos = &buffer + size;
    std::size_t S = size;

    while (decoded != 0 && S-- > 0)
    {
        *(--pos) = decoded & 0xFF;
        decoded >>= 8;
    }
    while (S-- > 0)
    {
        *(--pos) = 0;
    }
    f.write(&buffer, size);
}


template<class type, std::size_t size, class file_wrapper>
void dump_uint_le(file_wrapper f, type decoded)
{
    std::size_t S = size;
    while (decoded != 0 && S-- > 0)
    {
        f.putc(decoded & 0xFF);
        decoded >>= 8;
    }
    while (S-- > 0)
    {
        f.putc(0);
    }
}


template<class type, std::size_t size, class file_wrapper>
type parse_uint_be(file_wrapper f)
{
    type o = 0;
    std::size_t S = size;

    while (S-- > 0)
    {
        o <<= 8;
        o |= f.getc();
    }
    return o;
}

template<class type, std::size_t size, class file_wrapper>
type parse_uint_le(file_wrapper f)
{
    type o = 0;
    type buf;
    std::size_t S = size;
    uint8_t *pos = &buf + size;

    f.read(&buf, size);

    while (S-- > 0 && --pos >= &buf)
    {
        o = (o << 8) | *pos;
    }
}