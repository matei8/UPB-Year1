#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "allocator.h"

static Allocator allocator;

static inline MemClass get_class(size_t size) {
	if (!allocator)
		return NULL;
	for (size_t i = 0; i < allocator->num_classes; i++) {
		if (allocator->classes[i]->size >= size && allocator->classes[i]->free_list != NULL)
			return allocator->classes[i];
	}
	return NULL;
}

static inline MemClass find_class(void *ptr) {
	if (!allocator)
		return NULL;
	void *end, *start = &allocator->buffer[0];
	for (size_t i = 0; i < allocator->num_classes; i++) {
		end = start + allocator->classes[i]->capacity * allocator->classes[i]->size;
		if (ptr >= start && ptr < end) {
			return allocator->classes[i];
		}
		start += allocator->classes[i]->capacity * allocator->classes[i]->size;
	}
	return NULL;
}

void allocator_init(Pair *pairs, size_t length) {
	// TODO 1 -- alocare memorie și inițializare alocator
	allocator = malloc(sizeof(Allocator));
	allocator->num_classes = (int)length;
	allocator->buf_len = 0;
	allocator->classes = malloc(length * sizeof(MemClass));

	for (int i = 0; i < allocator->num_classes; i++) {
		allocator->classes[i] = malloc(sizeof(MemClass));
		allocator->classes[i]->size = pairs[i].size;
		allocator->classes[i]->capacity = pairs[i].capacity;
		allocator->classes[i]->free_list = NULL;
		allocator->buf_len = allocator->buf_len + allocator->classes[i]->size * allocator->classes[i]->capacity;
	}
	allocator->buffer = malloc(allocator->buf_len * sizeof(unsigned char));

	// Free-List construction and buffer mapping (point 5 of the requirement)
	void *start = allocator->buffer;
	for (size_t i = 0; i < length; i++) {
		allocator->classes[i]->start = start;
		for (size_t j = 0; j < pairs[i].capacity; j++) {
			void *ptr = start;
			MemBlock block = (MemBlock) ptr;
			block->next = allocator->classes[i]->free_list;
			allocator->classes[i]->free_list = block;
			start += pairs[i].size;
		}
	}
}

void *allocator_alloc(size_t size) {
	MemClass class = get_class(size);

	if (class->free_list == NULL) {
		MemBlock aux = (MemBlock)malloc(size);
		class->free_list = aux;
		allocator->stats.alloc_times++;
	} else {
		class->free_list = class->free_list->next;
		allocator->stats.alloc_times++;
	}

	return class->free_list;
}

void allocator_free(void *ptr) {
	MemClass class = find_class(ptr);

	MemBlock aux = ptr;
	aux->next =class->free_list;
	class->free_list = aux;

	allocator->stats.free_times++;
}

void allocator_stats(Stats *s) {
	*s = allocator->stats;
}

void allocator_destroy() {
	for (int i = 0; i < allocator->num_classes; i++) {
		free(allocator->classes[i]);
	}

	free(allocator->classes);
	free(allocator->buffer);
	free(allocator);
}
