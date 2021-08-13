#include <cstdio>
#include <cstdint>

#include <exception>

#ifndef DB_RUNTIME_HPP
#define DB_RUNTIME_HPP

namespace db_runtime
{
    template<class type, std::size_t size, class file_wrapper>
    static bool dump_uint_be(file_wrapper f, type decoded)
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
        return f.write(&buffer, size);
    }

    template<class type, std::size_t size, class file_wrapper>
    static bool dump_uint_le(file_wrapper f, type decoded)
    {
        std::size_t S = size;
        while (decoded != 0 && S-- > 0)
        {
            if (f.putc(decoded & 0xFF))
            {
                return true;
            }
            decoded >>= 8;
        }
        while (S-- > 0)
        {
            if (f.putc(0))
            {
                return true;
            }
        }
        return false;
    }

    template<class type, std::size_t size, class file_wrapper>
    bool parse_uint_be(file_wrapper f, type *dst)
    {
        uint_fast8_t c;
        std::size_t S = size;
        *dst = 0;

        while (S-- > 0)
        {
            if (f.getc(&c))
            {
                return true;
            }
            *dst = (*dst << 8) | c;
        }
        return false;
    }

    template<class type, std::size_t size, class file_wrapper>
    bool parse_uint_le(file_wrapper f, type *dst)
    {
        type buf;
        std::size_t S = size;
        uint8_t *pos = &buf + size;
        *dst = 0;

        if (f.read(&buf, size))
        {
            return true;
        }

        while (S-- > 0 && --pos >= &buf)
        {
            *dst = (*dst << 8) | *pos;
        }
        return false;
    }


    class cfile
    {
    private:
        errno_t err = 0;
    public:
        FILE *const f = nullptr;

        explicit cfile(FILE *) noexcept;

        bool getc(uint_fast8_t *dst) noexcept;

        bool putc(uint_fast8_t) noexcept;

        bool seek(long, int) noexcept;

        bool write(const void *, size_t) noexcept;

        bool read(void *, size_t) noexcept;

        bool close() noexcept;

        bool eof() const noexcept;

        bool error() const noexcept;

        errno_t get_errno() const noexcept;

        void clear_err() noexcept;
    };
}

#endif /* DB_RUNTIME_HPP */
