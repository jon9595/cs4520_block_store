#include "block_store.h"
#include <stdint.h>

block_store_t *block_store_create() {

    return NULL;
}

void block_store_destroy(block_store_t *const bs) {

    if(bs == NULL) {
        return;
    }

    return;
}

size_t block_store_allocate(block_store_t *const bs) {

    if(bs == NULL) {
        return SIZE_MAX;
    }
    return 0;
}

bool block_store_request(block_store_t *const bs, const size_t block_id) {

    if(bs == NULL) {
        return false;
    }

    if(block_id == 0) {
        return false;
    }

    return true;
}

void block_store_release(block_store_t *const bs, const size_t block_id) {

    if(bs == NULL) {
        return;
    }

    if(block_id == 0) {
        return;
    }

    return;
}

size_t block_store_get_used_blocks(const block_store_t *const bs) {

    if(bs == NULL) {
        return SIZE_MAX;
    }

    return 0;
}

size_t block_store_get_free_blocks(const block_store_t *const bs) {

    if(bs == NULL) {
        return SIZE_MAX;
    }

    return 0;
}

size_t block_store_get_total_blocks() {
    return 0;
}

size_t block_store_read(const block_store_t *const bs, const size_t block_id, void *buffer) {

    if(bs == NULL || buffer == NULL) {
        return 0;
    }

    if(block_id == 0) {
        return 0;
    }

    return 0;
}

size_t block_store_write(block_store_t *const bs, const size_t block_id, const void *buffer) {

    if(bs == NULL || buffer == NULL) {
        return 0;
    }

    if(block_id == 0) {
        return 0;
    }

    return 0;
}

block_store_t *block_store_deseralize(const char *const filename) {

    if(filename == NULL) {
        return NULL;
    }

    return NULL;
}

size_t block_store_serialize(const block_store_t *const bs, const char *const filename) {

    if(bs == NULL || filename == NULL) {
        return 0;
    }

    return 0;
}
