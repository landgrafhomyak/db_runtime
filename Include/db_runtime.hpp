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
