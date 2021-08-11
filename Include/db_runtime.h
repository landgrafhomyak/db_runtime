#include <stddef.h>

#ifndef DB_RUNTIME_H
#define DB_RUNTIME_H

#ifdef __cplusplus
extern "C" {
#endif


void *dump_int_be(void *encoded, void *decoded, size_t size, size_t type_size);

void *parse_int_be(void *decoded, void *encoded, size_t size, size_t type_size);

void *dump_int_le(void *encoded, void *decoded, size_t size, size_t type_size);

void *parse_int_le(void *decoded, void *encoded, size_t size, size_t type_size);

#ifdef __cplusplus
};
#endif

#endif /* DB_RUNTIME_H */
