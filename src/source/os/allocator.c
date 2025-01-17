/*
 * Copyright 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include <stdlib.h>
#include <zephyr/kernel.h>

/* Public headers */
#include "kvs/pool_allocator.h"

/* Internal headers */
#include "allocator.h"

// static void *k_realloc(void *ptr, size_t new_size) {
//     if (ptr == NULL) {
//         return k_malloc(new_size);
//     }

//     if (new_size == 0) {
//         k_free(ptr);
//         return NULL;
//     }

//     void *new_ptr = k_malloc(new_size);
//     if (new_ptr == NULL) {
//         return NULL;
//     }

//     // Copy the old data to the new block of memory
//     memcpy(new_ptr, ptr, new_size);
//     k_free(ptr);

//     return new_ptr;
// }

void *kvsMalloc(size_t bytes)
{
    return k_malloc(bytes);
}

void *kvsRealloc(void *ptr, size_t bytes)
{
    return k_realloc(ptr, bytes);
}

void *kvsCalloc(size_t num, size_t bytes)
{
    return k_calloc(num, bytes);
}

void kvsFree(void *ptr)
{
    k_free(ptr);
}

/**
 * Wrapper of KVS malloc that use pool allocator malloc.
 *
 * @param[in] bytes Memory size
 * @return New allocated address on success, NULL otherwise
 */
void *__wrap_kvsMalloc(size_t bytes)
{
    return poolAllocatorMalloc(bytes);
}

/**
 * Wrapper of KVS realloc that use pool allocator realloc.
 *
 * @param[in] ptr Pointer to be re-allocated
 * @param[in] bytes New memory size
 * @return New allocated address on success, NULL otherwise
 */
void *__wrap_kvsRealloc(void *ptr, size_t bytes)
{
    return poolAllocatorRealloc(ptr, bytes);
}

/**
 * Wrapper of KVS calloc that use pool allocator calloc.
 *
 * @param[in] num Number of elements
 * @param[in] bytes Element size
 * @return Newly allocated address on success, NULL otherwise
 */
void *__wrap_kvsCalloc(size_t num, size_t bytes)
{
    return poolAllocatorCalloc(num, bytes);
}

/**
 * Wrapper of KVS free that use pool allocator free.
 *
 * @param[in] ptr Memory pointer to be freed
 */
void __wrap_kvsFree(void *ptr)
{
    poolAllocatorFree(ptr);
}
