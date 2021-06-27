#include "static_hash.h"

unsigned int hash_string(const char *str) {
    unsigned int hash = 0, i;

    for (i = 0; str[i]; ++i) {
        hash = 65599 * hash + str[i];
    }
    return hash ^ (hash >> 16);
}
