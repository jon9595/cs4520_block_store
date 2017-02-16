#include "block_store.h"
#include "bitmap.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_STORE_NUM_BLOCKS 256
#define BLOCK_STORE_BITMAP_LOC 255
#define BLOCK_TOTAL_NUM_BYTES 256

typedef struct block_store {
    void* block; //creating a place to store information
} block_store_t;

block_store_t *block_store_create() {

    block_store_t* bs = malloc(sizeof(block_store_t) * BLOCK_STORE_NUM_BLOCKS); //allocing out the blocks

    if(bs == NULL) { //check to see if the allocation worked
        return NULL;
    }

    bitmap_t* block_map = bitmap_create(BLOCK_STORE_NUM_BLOCKS); //using the bitmap create from the bitmap library to create a new bitmap

    if(block_map == NULL) { //checking to make sure the bitmap creation worked
        return NULL;
    }

    bs[BLOCK_STORE_BITMAP_LOC].block = block_map; //adding the bitmap to the end of the block storage device

    bitmap_set(bs[BLOCK_STORE_BITMAP_LOC].block, BLOCK_STORE_BITMAP_LOC); //setting the bitmap at the last byte to indicate the bitmap is present at the last block

    int i;
    for(i = 0; i < BLOCK_STORE_NUM_BLOCKS - 1; i++) {
        bs[i].block = malloc(BLOCK_TOTAL_NUM_BYTES); //mallocing out each void pointer in the block storage device to hold individual blocks of memory (excluding the last spot, which is the location of the block storage device
    }

    return bs; //returning the newly created block storage device
}

void block_store_destroy(block_store_t *const bs) {

    if(bs == NULL) { //if the device is already null, there is nothing to do
        return;
    }

    bitmap_destroy(bs[BLOCK_STORE_BITMAP_LOC].block); //destroying the bitmap at the end of the device

    int i;
    for(i = 0; i < BLOCK_STORE_NUM_BLOCKS - 1; i++) { //iterating through the device and freeing each individual block
        free(bs[i].block);
    }

    free(bs); //freeing the entire device

    return;
}

size_t block_store_allocate(block_store_t *const bs) {

    if(bs == NULL) { //checking for a null device
        return SIZE_MAX;
    }

    size_t free_block = bitmap_ffz(bs[BLOCK_STORE_BITMAP_LOC].block); //using the find first zero function from the bitmap library to find the first free block

    if(free_block != SIZE_MAX) { //if free block is size_max, then no memory is available, so we won't set the bitmap.
        bitmap_set(bs[BLOCK_STORE_BITMAP_LOC].block, free_block); //setting the bitmap at the first available block
    }


    return free_block; //returning either the set block (if we found a free space), or SIZE_MAX if the device is full
}

bool block_store_request(block_store_t *const bs, const size_t block_id) {

    if(bs == NULL || block_id > BLOCK_STORE_BITMAP_LOC) { //checking for a null device as well as if the block_id is out of bounds for the current amount of storage allowed.
        return false;
    }

    if(!bitmap_test(bs[BLOCK_STORE_BITMAP_LOC].block, block_id)){ //checking to see if the block is currently in use. if it isn't we use bitmap set to set the block as active
        bitmap_set(bs[BLOCK_STORE_BITMAP_LOC].block, block_id);
    }
    else{ //block was in use
        return false;
    }

    return true;
}

void block_store_release(block_store_t *const bs, const size_t block_id) {

    if(bs == NULL) { //checking for a null device
        return;
    }

    if(bitmap_test(bs[BLOCK_STORE_BITMAP_LOC].block, block_id)) { //testing to check if the bit is already not set
        bitmap_reset(bs[BLOCK_STORE_BITMAP_LOC].block, block_id); //clearing the set bit if it was already set
    }

    return;
}

size_t block_store_get_used_blocks(const block_store_t *const bs) {

    if(bs == NULL) { //checking for a null device
        return SIZE_MAX;
    }

    size_t result = bitmap_total_set(bs[BLOCK_STORE_BITMAP_LOC].block); //this will give the total number of set blocks in the bitmap in the device

    return result - 1; //returning the total number of set bytes - 1 to accout for the bitmap at the end of the device
}

size_t block_store_get_free_blocks(const block_store_t *const bs) {

    if(bs == NULL) { //checking for a null device
        return SIZE_MAX;
    }

    size_t result = bitmap_total_set(bs[BLOCK_STORE_BITMAP_LOC].block); //gettign the total number of set blocks in the device

    result = BLOCK_STORE_NUM_BLOCKS - result; //taking the toatl number of block in the device and subtracting the set bits

    return result;
}

size_t block_store_get_total_blocks() {
    return BLOCK_STORE_NUM_BLOCKS - 1; //giving usable blocks (total - bitmap)
}

size_t block_store_read(const block_store_t *const bs, const size_t block_id, void *buffer) {

    if(bs == NULL || buffer == NULL) { //checking for a null device or a null input buffer
        return 0;
    }

    if(block_id > BLOCK_STORE_BITMAP_LOC) { //making sure the id to read from is not out of bounds
        return 0;
    }

    memcpy(buffer, bs[block_id].block, BLOCK_TOTAL_NUM_BYTES); //copying data from the block to the buffer

    return BLOCK_TOTAL_NUM_BYTES; //returning the size of a block
}

size_t block_store_write(block_store_t *const bs, const size_t block_id, const void *buffer) {

    if(bs == NULL || buffer == NULL) { //checking for a null device or a null input buffer
        return 0;
    }

    if(block_id > BLOCK_STORE_BITMAP_LOC) { //checking that the requested block is in the current range of the device
        return 0;
    }

    memcpy(bs[block_id].block, buffer, BLOCK_TOTAL_NUM_BYTES); //copying memory from the buffer into the device

    return BLOCK_TOTAL_NUM_BYTES; //returning the size of a block
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
