#include <cstdio>
#include <cstdint>

#include <db_runtime.hpp>

db_runtime::cfile::error::error(int v) noexcept: value(v)
{}

db_runtime::cfile::cfile(FILE *p) noexcept: f(p)
{}

uint_fast8_t db_runtime::cfile::getc() const
{
    int c;
    c = fgetc(this->f);
    if (c == EOF)
    {
        throw db_runtime::eof_exception();
    }
    if (ferror(this->f))
    {
        throw db_runtime::cfile::error(ferror(this->f));
    }
    return (uint_fast8_t) c;
}

void db_runtime::cfile::putc(uint_fast8_t c) const
{
    fputc(c, this->f);
    if (ferror(this->f))
    {
        throw db_runtime::cfile::error(ferror(this->f));
    }
}

void db_runtime::cfile::seek(long offset, int origin) const
{
    if (fseek(this->f, offset, origin) != 0)
    {
        throw db_runtime::cfile::error(ferror(this->f));
    }
}

void db_runtime::cfile::write(const void *data, size_t s) const
{
    if (fwrite(data, 1, s, this->f) != s)
    {
        throw db_runtime::cfile::error(ferror(this->f));
    }
}

void db_runtime::cfile::read(void *data, size_t s) const
{
    if (fread(data, 1, s, this->f) != s)
    {
        if (feof(this->f))
        {
            throw db_runtime::eof_exception();
        }
        else
        {
            throw db_runtime::cfile::error(ferror(this->f));
        }
    }
}

void db_runtime::cfile::close() const
{
    if (fclose(this->f) == EOF)
    {
        throw db_runtime::cfile::error(ferror(this->f));
    }
}
