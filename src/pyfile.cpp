#include <Python.h>

#include <db_runtime.hpp>
#include <db_runtime/cpython.hpp>

db_runtime::pyfile::pyfile(PyObject *p) noexcept: f(p)
{}


static PyObject *read_from_pyo(PyObject *f, Py_ssize_t n)
{
    PyObject *writer_func;
    PyObject *bytes;

    writer_func = PyObject_GetAttrString(f, "read");
    if (writer_func == nullptr)
    {
        return nullptr;
    }
    bytes = PyObject_CallFunction(writer_func, "n", n);
    Py_DECREF(writer_func);
    if (bytes == nullptr)
    {
        return nullptr;
    }
    if (!(PyBytes_Check(bytes)))
    {
        Py_DECREF(bytes);
        PyErr_Format(
                PyExc_TypeError,
                ".read method returned not bytes"
        );
        return nullptr;
    }
    if (PyBytes_GET_SIZE(bytes) > n)
    {
        Py_DECREF(bytes);
        PyErr_Format(
                PyExc_ValueError,
                ".read method returned to many bytes"
        );
        return nullptr;
    }
    return bytes;
}

bool db_runtime::pyfile::getc(uint_fast8_t *dst) noexcept
{
    PyObject *bytes;

    bytes = read_from_pyo(this->f, 1);
    if (bytes == nullptr)
    {
        this->was_error = false;
        return true;
    }
    *dst = PyBytes_AS_STRING(bytes)[0];
    Py_DECREF(bytes);
    return false;
}

bool db_runtime::pyfile::write(const void *, size_t) noexcept
{
    return false;
}
