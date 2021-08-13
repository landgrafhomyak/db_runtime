#include <cstdio>
#include <cstdint>

#include <db_runtime.hpp>

db_runtime::cfile::cfile(FILE *p) noexcept: f(p)
{}

bool db_runtime::cfile::getc(uint_fast8_t *dst) noexcept
{
    int c;
    c = fgetc(this->f);
    if (c == EOF)
    {
        return false;
    }
    if (ferror(this->f))
    {
        this->err = errno;
        return true;
    }
    *dst = (uint_fast8_t) c;
    return false;
}

bool db_runtime::cfile::putc(uint_fast8_t c) noexcept
{
    fputc(c, this->f);
    if (ferror(this->f))
    {
        this->err = errno;
        return true;
    }
    return false;
}

bool db_runtime::cfile::seek(long offset, int origin) noexcept
{
    if (fseek(this->f, offset, origin) != 0)
    {
        this->err = errno;
        return true;
    }
    return false;
}

bool db_runtime::cfile::write(const void *data, size_t s) noexcept
{
    if (fwrite(data, 1, s, this->f) != s)
    {
        this->err = errno;
        return true;
    }
    return false;
}

bool db_runtime::cfile::read(void *data, size_t s) noexcept
{
    if (fread(data, 1, s, this->f) != s)
    {
        if (!ferror(this->f))
        {
            this->err = errno;
            return true;
        }
    }
    return false;
}

bool db_runtime::cfile::close() noexcept
{
    if (fclose(this->f) == EOF)
    {
        this->err = errno;
        return true;
    }
    return false;
}

bool db_runtime::cfile::eof() const noexcept
{
    return feof(this->f);
}

bool db_runtime::cfile::error() const noexcept
{
    return ferror(this->f);
}

errno_t db_runtime::cfile::get_errno() const noexcept
{
    return this->err;
}

void db_runtime::cfile::clear_err() noexcept
{
    this->err = 0;
    clearerr(this->f);
}
