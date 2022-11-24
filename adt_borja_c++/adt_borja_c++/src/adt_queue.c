// adt_queue.c
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//
#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"
#include "adt_queue.h"

#include "ABGS_MemoryManager\abgs_memory_manager.h"

static s16 QUEUE_destroy(Queue *queue);	// Destroys the vector and its data
static s16 QUEUE_reset(Queue *queue);		// Resets vector's data
static u16 QUEUE_resize(Queue *queue, u16 new_size); // Resizes the capacity of the vector. Some elements can be lost

// State queries
static u16 QUEUE_capacity(Queue *queue);		// returns the maximum number of elemets to store
static u16 QUEUE_length(Queue *queue);			// current number of elements (<= capacity)
static bool QUEUE_isEmpty(Queue *queue);
static bool QUEUE_isFull(Queue *queue);

// Data queries
static void* QUEUE_front(Queue *queue); // Returns a reference to the last element of the vector
static void* QUEUE_back(Queue *queue); // Returns a reference to the last element of the vector

// Insertion
static s16 QUEUE_enqueue(Queue *queue, void *data, u16 bytes); // Inserts an element in the first position of the vector


// Extraction
static void* QUEUE_dequeue(Queue *queue); // Extracts the first element of the vector


// Miscellaneous
static s16 QUEUE_concat(Queue *queue, Queue *queue_src); // Concatenates two vectors
static void* QUEUE_print(Queue *queue); // Prints the features and content of the vector


struct queue_ops_s queue_ops =
{
	.destroy = QUEUE_destroy,
	.destroy = QUEUE_destroy,
	.reset = QUEUE_reset,
	.resize = QUEUE_resize,

	.capacity = QUEUE_capacity,
	.length = QUEUE_length,
	.isEmpty = QUEUE_isEmpty,
	.isFull = QUEUE_isFull,

	.front = QUEUE_front ,
	.back = QUEUE_back ,
	.enqueue = QUEUE_enqueue ,
	.dequeue = QUEUE_dequeue ,

	.concat = QUEUE_concat,
	.print = QUEUE_print

};

s16 QUEUE_initWithoutCheck(Queue *queue, u16 capacity) {

	queue->ops_ = &queue_ops;
	return kErrorCode_Ok;
}
Queue* QUEUE_create(u16 capacity) {
	if (0 == capacity) {
		return NULL;
	}
	Queue* q = (Queue*)MM->malloc(sizeof(Queue));
	if (NULL == q) return NULL;
	q->storage_ = LIST_create(capacity);
	if (NULL == q->storage_) {
		MM->free(q);
		return NULL;
	}
	QUEUE_initWithoutCheck(q, capacity);
	return q;
}
s16 QUEUE_destroy(Queue* queue) {
	if (NULL == queue)return kErrorCode_Ok;

	queue->storage_->ops_->destroy(queue->storage_);

	MM->free(queue);
	return kErrorCode_Ok;
}
s16 QUEUE_reset(Queue *queue) {
	if (NULL == queue)return kErrorCode_QUEUE_NULL;
	if (NULL == queue->storage_)return kErrorCode_QUEUE_STORAGE_NULL;
	queue->storage_->ops_->reset(queue->storage_);
	return kErrorCode_Ok;
}

s16 QUEUE_resize(Queue *queue, u16 new_size) {
	if (NULL == queue)return kErrorCode_QUEUE_NULL;
	if (new_size == 0)return kErrorCode_LIST_BYTES_0;
	if (new_size == queue->storage_->capacity_) return kErrorCode_Ok;

	return queue->storage_->ops_->resize(queue->storage_, new_size);
}
u16 QUEUE_capacity(Queue *queue) {
	if (NULL == queue)return 0;
	return queue->storage_->ops_->capacity(queue->storage_);
}
bool QUEUE_isEmpty(Queue *queue) {
	if (NULL == queue)return true;
	if (NULL == queue->storage_)return true;
	return queue->storage_->ops_->isEmpty(queue->storage_);
}
bool QUEUE_isFull(Queue *queue) {
	if (NULL == queue)return false;
	if (NULL == queue->storage_)return false;
	return queue->storage_->ops_->isFull(queue->storage_);
}
u16 QUEUE_length(Queue *queue) {
	if (NULL == queue)return 0;
	if (NULL == queue->storage_) return 0;
	return queue->storage_->ops_->length(queue->storage_);
}

void* QUEUE_front(Queue *queue) {
	if (NULL == queue)return NULL;
	if (NULL == queue->storage_) return NULL;
	return queue->storage_->ops_->first(queue->storage_);
}

s16 QUEUE_enqueue(Queue *queue, void *data, u16 bytes) {
	if (NULL == queue)return kErrorCode_QUEUE_NULL;
	if (NULL == data)return kErrorCode_QUEUE__DATA_NULL;
	if (bytes == 0)return kErrorCode_LIST_BYTES_0;

	return queue->storage_->ops_->insertLast(queue->storage_, data, bytes);
}

void* QUEUE_back(Queue *queue) {
	if (NULL == queue)return NULL;


	return queue->storage_->ops_->last(queue->storage_);
}

s16 QUEUE_concat(Queue *queue, Queue *queue_src) {
	if (NULL == queue)return kErrorCode_QUEUE_NULL;
	if (NULL == queue_src)return kErrorCode_QUEUE_NULL;


	return queue->storage_->ops_->concat(queue->storage_, queue_src->storage_);

}
void* QUEUE_dequeue(Queue *queue) {
	if (NULL == queue)return kErrorCode_QUEUE_NULL;

	return queue->storage_->ops_->extractFirst(queue->storage_);

}

void* QUEUE_print(Queue *queue)
{
	return NULL;
}
