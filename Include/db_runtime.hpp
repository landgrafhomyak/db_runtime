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
}

#endif /* DB_RUNTIME_HPP */
