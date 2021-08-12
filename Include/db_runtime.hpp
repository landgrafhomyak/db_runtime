#include <cstdio>
#include <cstdint>

#include <exception>

#ifndef DB_RUNTIME_HPP
#define DB_RUNTIME_HPP

namespace db_runtime
{
    class eof_exception : std::exception
    {
    };

    template<class type, std::size_t size, class file_wrapper>
    void dump_uint_be(file_wrapper f, type decoded);

    template<class type, std::size_t size, class file_wrapper>
    void dump_uint_le(file_wrapper f, type decoded);

    template<class type, std::size_t size, class file_wrapper>
    type parse_uint_be(file_wrapper f);

    template<class type, std::size_t size, class file_wrapper>
    type parse_uint_le(file_wrapper f);

    class cfile
    {
    public:
        class error : std::exception
        {
        public:
            const int value;

            explicit error(int) noexcept;
        };

        FILE *f = nullptr;

        explicit cfile(FILE *) noexcept;


        uint_fast8_t getc() const;

        void putc(uint_fast8_t) const;

        void seek(long, int) const;

        void write(const void *, size_t) const;

        void read(void *, size_t) const;

        void close() const;
    };
}

#endif /* DB_RUNTIME_HPP */
