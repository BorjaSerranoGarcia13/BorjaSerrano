// adt_dllist.c
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"
#include "adt_dllist.h"

#include "ABGS_MemoryManager\abgs_memory_manager.h"


static s16 DLLIST_initWithoutCheck(DLList* dllist);

static s16 DLLIST_destroy(DLList* dllist);
static s16 DLLIST_reset(DLList* dllist);
static s16 DLLIST_resize(DLList* dllist, u16 new_size);

static u16 DLLIST_capacity(DLList* dllist);
static u16 DLLIST_length(DLList* dllist);
static bool DLLIST_isEmpty(DLList* dllist);
static bool DLLIST_isFull(DLList* dllist);

static void* DLLIST_first(DLList* dllist);
static void* DLLIST_last(DLList* dllist);
static void* DLLIST_at(DLList* dllist, u16 position);

static s16 DLLIST_insertFirst(DLList* dllist, void* data, u16 bytes);
static s16 DLLIST_insertLast(DLList* dllist, void* data, u16 bytes);
static s16 DLLIST_insertAt(DLList* dllist, void* data, u16 bytes, u16 position);

static void* DLLIST_extractFirst(DLList* dllist);
static void* DLLIST_extractLast(DLList* dllist);
static void* DLLIST_extractAt(DLList* dllist, u16 position);

static s16 DLLIST_concat(DLList* dllist, DLList* dllist_src);

static s16 DLLIST_traverse(DLList* dllist, void(*callback) (MemoryNode*));
static void DLLIST_print(DLList* dllist);


struct dllist_ops_s dllist_ops =
{
	.destroy = DLLIST_destroy,
	.reset = DLLIST_reset,
	.resize = DLLIST_resize,

	.capacity = DLLIST_capacity,
	.length = DLLIST_length,
	.isEmpty = DLLIST_isEmpty,
	.isFull = DLLIST_isFull,

	.first = DLLIST_first,
	.last = DLLIST_last,
	.at = DLLIST_at,

	.insertFirst = DLLIST_insertFirst,
	.insertLast = DLLIST_insertLast,
	.insertAt = DLLIST_insertAt,

	.extractFirst = DLLIST_extractFirst,
	.extractLast = DLLIST_extractLast,
	.extractAt = DLLIST_extractAt,

	.concat = DLLIST_concat,
	.print = DLLIST_print
};


DLList* DLLIST_create(u16 capacity) {

	if (0 == capacity) return NULL;

	DLList* dllist = MM->malloc(sizeof(DLList));

	if (NULL == dllist) return NULL;


	dllist->capacity_ = capacity;
	DLLIST_initWithoutCheck(dllist);
	return dllist;
}

s16 DLLIST_initWithoutCheck(DLList* dllist)
{
	dllist->length_ = 0;
	dllist->first_ = NULL;
	dllist->last_ = NULL;
	dllist->ops_ = &dllist_ops;

	return kErrorCode_Ok;
}

s16 DLLIST_destroy(DLList* dllist)
{
	if (kErrorCode_DLLIST_NULL == DLLIST_reset(dllist)) return kErrorCode_DLLIST_NULL;
	dllist->capacity_ = 0;
	MM->free(dllist);
	return kErrorCode_Ok;
}

s16 DLLIST_reset(DLList* dllist)
{
	if (NULL == dllist) return kErrorCode_DLLIST_NULL;

	if (DLLIST_isEmpty(dllist)) return kErrorCode_Ok;


	if (NULL == dllist->first_->ops_->getNext(dllist->first_)) {
		dllist->first_->ops_->free(dllist->first_);
		dllist->length_ = 0;
		dllist->first_ = NULL;
		dllist->last_ = NULL;
		return kErrorCode_Ok;
	}

	MemoryNode* tmp_actual;
	MemoryNode* tmp_next;
	tmp_actual = dllist->first_;
	if (NULL == tmp_actual) return kErrorCode_Memory;

	tmp_next = dllist->first_->ops_->getNext(dllist->first_);
	if (NULL == tmp_next) return kErrorCode_Memory;

	for (u16 i = 0; i < dllist->length_; ++i) {
		tmp_next = tmp_actual->ops_->getNext(tmp_actual);
		tmp_actual->ops_->free(tmp_actual);
		tmp_actual = tmp_next;
	}
	dllist->first_ = NULL;
	dllist->last_ = NULL;
	dllist->length_ = 0;
	return kErrorCode_Ok;
}

s16 DLLIST_resize(DLList* dllist, u16 new_capacity) {
	if (NULL == dllist)
		return kErrorCode_DLLIST_NULL;
	if (new_capacity == dllist->capacity_) return kErrorCode_Ok;

	if (0 == new_capacity) return kErrorCode_DLLIST_NULL;

	if (dllist->ops_->isEmpty(dllist)) {
		dllist->capacity_ = new_capacity;
		return kErrorCode_Ok;
	}

	if (NULL == dllist->first_) return kErrorCode_DLLIST_FIRST_NULL;
	if (NULL == dllist->last_) return kErrorCode_DLLIST_LAST_NULL;

	if (dllist->length_ > new_capacity) {
		MemoryNode* tmp_actual;
		MemoryNode* tmp_aux;
		tmp_actual = dllist->first_;
		if (NULL == tmp_actual) return kErrorCode_Memory;

		for (u16 i = 0; i < new_capacity; ++i) {
			tmp_actual = tmp_actual->ops_->getNext(tmp_actual);
		}
		tmp_aux = tmp_actual->ops_->getNext(tmp_actual);
		if (NULL == tmp_aux) return kErrorCode_Memory;

		for (u16 i = new_capacity; i < dllist->length_; ++i) {
			tmp_aux = tmp_actual->ops_->getNext(tmp_actual);
			tmp_actual->ops_->free(tmp_actual);
			tmp_actual = tmp_aux;
		}
		dllist->length_ = new_capacity;
	}

	dllist->capacity_ = new_capacity;
	return kErrorCode_Ok;
}

u16 DLLIST_capacity(DLList* dllist) {
	if (NULL == dllist) return 0;
	return dllist->capacity_;
}

u16 DLLIST_length(DLList* dllist) {
	if (NULL == dllist) return 0;

	return dllist->length_;
}

bool DLLIST_isEmpty(DLList* dllist) {
	if (NULL == dllist) return false;

	if (0 == dllist->length_) return true;

	return false;
}

bool DLLIST_isFull(DLList* dllist) {
	if (NULL == dllist) return false;

	if (0 == dllist->capacity_) return false;


	if (dllist->length_ == dllist->capacity_)return true;

	return false;
}

void* DLLIST_first(DLList* dllist) {
	if (NULL == dllist) return NULL;

	if (dllist->ops_->isEmpty(dllist)) return NULL;

	if (NULL == dllist->first_) return NULL;

	if (NULL == dllist->first_->ops_->data(dllist->first_)) return NULL;

	return dllist->first_->ops_->data(dllist->first_);
}

void* DLLIST_last(DLList* dllist) {
	if (NULL == dllist) return NULL;

	if (dllist->ops_->isEmpty(dllist)) return NULL;

	if (NULL == dllist->last_) return NULL;

	if (NULL == dllist->last_->ops_->data(dllist->last_)) return NULL;

	return dllist->last_->ops_->data(dllist->last_);
}

void* DLLIST_at(DLList* dllist, u16 position) {
	if (NULL == dllist) return NULL;

	if (dllist->ops_->isEmpty(dllist)) return NULL;

	if (position >= dllist->length_) return NULL;


	MemoryNode* tmp_actual;

	if (NULL == dllist->first_) return NULL;
	tmp_actual = dllist->first_;
	if (NULL == tmp_actual) return NULL;

	for (u16 i = 0; i < position; ++i) {
		tmp_actual = tmp_actual->ops_->getNext(tmp_actual);
	}

	if (NULL == tmp_actual->ops_->data(tmp_actual)) return NULL;

	return tmp_actual->ops_->data(tmp_actual);
}

s16 DLLIST_insertFirst(DLList* dllist, void* data, u16 bytes) {

	if (NULL == dllist) return kErrorCode_DLLIST_NULL;

	if (NULL == data) return kErrorCode_DLLIST_DATA_NULL;

	if (0 == bytes) return kErrorCode_DLLIST_BYTES_0;

	if (dllist->ops_->isFull(dllist)) return kErrorCode_DLLIST_FULL;

	MemoryNode* new_node = MEMNODE_create();
	if (NULL == new_node) return kErrorCode_Memory;



	if (dllist->ops_->isEmpty(dllist)) {
		new_node->ops_->setNext(new_node, NULL);
		new_node->ops_->setData(new_node, data, bytes);
		dllist->first_ = new_node;
		dllist->last_ = new_node;
		new_node->ops_->setPrev(new_node, NULL);
	}
	else {
		new_node->next_ = dllist->first_;
		new_node->ops_->setData(new_node, data, bytes);
		dllist->first_->ops_->setPrev(dllist->first_, new_node);
		dllist->first_ = new_node;

	}

	dllist->length_++;
	return kErrorCode_Ok;
}

s16 DLLIST_insertLast(DLList* dllist, void* data, u16 bytes) {

	if (NULL == dllist) return kErrorCode_DLLIST_NULL;

	if (NULL == data) return kErrorCode_DLLIST_DATA_NULL;

	if (0 == bytes) return kErrorCode_DLLIST_BYTES_0;

	if (dllist->ops_->isFull(dllist)) return kErrorCode_DLLIST_FULL;

	if (dllist->ops_->isEmpty(dllist)) return DLLIST_insertFirst(dllist, data, bytes);

	MemoryNode* new_node = MEMNODE_create();
	if (NULL == new_node) return kErrorCode_Memory;

	if (NULL == dllist->last_) return kErrorCode_DLLIST_LAST_NULL;

	dllist->last_->ops_->setNext(dllist->last_, new_node);
	new_node->ops_->setData(new_node, data, bytes);
	new_node->ops_->setNext(new_node, NULL);
	new_node->ops_->setPrev(new_node, dllist->last_);
	dllist->last_ = new_node;

	dllist->length_++;

	return kErrorCode_Ok;
}

s16 DLLIST_insertAt(DLList* dllist, void* data, u16 bytes, u16 position) {
	if (NULL == dllist) return kErrorCode_DLLIST_NULL;

	if (NULL == data) return kErrorCode_DLLIST_DATA_NULL;

	if (0 == bytes) return kErrorCode_DLLIST_BYTES_0;

	if (dllist->ops_->isFull(dllist)) return kErrorCode_DLLIST_FULL;

	if (position >= dllist->capacity_) return 14;

	if (position >= dllist->length_) return DLLIST_insertLast(dllist, data, bytes);

	if (0 == position) 	return DLLIST_insertFirst(dllist, data, bytes);

	if (dllist->ops_->isEmpty(dllist)) return DLLIST_insertFirst(dllist, data, bytes);


	MemoryNode* tmp_actual;
	tmp_actual = dllist->first_;
	if (NULL == tmp_actual) return NULL;

	for (u16 i = 0; i < position - 1; ++i) {
		tmp_actual = tmp_actual->ops_->getNext(tmp_actual);
	}

	MemoryNode* new_node = MEMNODE_create();
	if (NULL == new_node) {
		return kErrorCode_Memory;
	}
	MemoryNode* auxiliar = tmp_actual->ops_->getNext(tmp_actual);
	if (NULL == auxiliar) return NULL;

	new_node->ops_->setData(new_node, data, bytes);
	auxiliar->ops_->setPrev(auxiliar, new_node);

	new_node->ops_->setNext(new_node, tmp_actual->ops_->getNext(tmp_actual));
	tmp_actual->ops_->setNext(tmp_actual, new_node);
	tmp_actual->ops_->setPrev(new_node, tmp_actual);


	dllist->length_++;

	return kErrorCode_Ok;
}

void* DLLIST_extractFirst(DLList* dllist) {
	if (NULL == dllist) {
		return NULL;
	}
	if (NULL == dllist->first_) {
		return NULL;
	}
	if (NULL == dllist->last_) {
		return NULL;
	}
	if (dllist->ops_->isEmpty(dllist)) {
		return NULL;
	}

	void* first_data = dllist->first_->ops_->data(dllist->first_);
	if (NULL == first_data) return NULL;


	if (1 == dllist->length_) {
		dllist->first_->ops_->softFree(dllist->first_);
		dllist->first_ = NULL;
		dllist->last_ = NULL;
		dllist->length_--;
		return first_data;
	}

	MemoryNode* tmp_actual;
	tmp_actual = dllist->first_->ops_->getNext(dllist->first_);
	if (NULL == tmp_actual) return NULL;


	dllist->first_->ops_->softFree(dllist->first_);
	dllist->first_ = tmp_actual;
	dllist->first_->ops_->setPrev(dllist->first_, NULL);
	dllist->length_--;

	return first_data;
}

void* DLLIST_extractLast(DLList* dllist) {

	if (NULL == dllist) return NULL;

	if (NULL == dllist->first_) return NULL;
	if (NULL == dllist->last_) return NULL;

	if (dllist->ops_->isEmpty(dllist)) return NULL;


	void* last_data = dllist->last_->ops_->data(dllist->last_);
	if (NULL == last_data) return NULL;


	MemoryNode* tmp_actual;
	tmp_actual = dllist->first_;
	if (NULL == last_data) return NULL;

	for (u16 i = 0; i < dllist->length_ - 2; ++i) {
		tmp_actual = tmp_actual->ops_->getNext(tmp_actual);
	}

	dllist->last_->ops_->softFree(dllist->last_);
	tmp_actual->ops_->setNext(tmp_actual, NULL);
	dllist->last_ = tmp_actual;
	dllist->length_--;

	return last_data;
}

void* DLLIST_extractAt(DLList* dllist, u16 position) {
	if (NULL == dllist) return NULL;

	if (dllist->ops_->isEmpty(dllist)) return NULL;

	if (NULL == dllist->first_) return NULL;
	if (NULL == dllist->last_) return NULL;

	if (position >= dllist->capacity_ && dllist->capacity_ != 0) return NULL;

	if (position >= dllist->length_) return NULL;

	if (0 == position) DLLIST_extractFirst(dllist);

	if ((dllist->length_ - 1) == position) DLLIST_extractLast(dllist);

	MemoryNode* tmp_actual;
	MemoryNode* node_extract;
	void* data;

	tmp_actual = dllist->first_;
	if (NULL == tmp_actual) return NULL;


	for (u16 i = 0; i < position - 1; ++i) {
		tmp_actual = tmp_actual->ops_->getNext(tmp_actual);
	}
	MemoryNode* auxiliar;
	auxiliar = tmp_actual->ops_->getNext(tmp_actual);
	auxiliar = auxiliar->ops_->getNext(auxiliar);
	node_extract = tmp_actual->ops_->getNext(tmp_actual);
	if (NULL == node_extract) return NULL;


	data = node_extract->ops_->data(node_extract);
	if (NULL == data) return NULL;

	tmp_actual->ops_->setNext(tmp_actual, node_extract->ops_->getNext(node_extract));
	node_extract->ops_->softFree(node_extract);
	auxiliar->ops_->setPrev(auxiliar, tmp_actual);

	if (NULL == tmp_actual->ops_->getNext(tmp_actual)) dllist->last_ = tmp_actual;

	dllist->length_--;
	return data;
}

s16 DLLIST_concat(DLList* dllist, DLList* dllist_src) {
	if (NULL == dllist) return kErrorCode_DLLIST_NULL;

	if (NULL == dllist_src) return kErrorCode_DLLIST_SRC_NULL;

	if (dllist->ops_->isEmpty(dllist_src)) return kErrorCode_Ok;


	u16 new_lenght = dllist->length_ + dllist_src->length_;
	u16 new_capacity = dllist->capacity_ + dllist_src->capacity_;
	if (dllist->capacity_ != 0) {
		dllist->capacity_ = new_capacity;
	}

	MemoryNode* actual_src;
	if (NULL == dllist->first_) return kErrorCode_DLLIST_FIRST_NULL;
	actual_src = dllist_src->first_;
	if (NULL == actual_src) return kErrorCode_Memory;

	for (u16 i = 0; i < dllist_src->length_; ++i) {
		void* data = MM->malloc(actual_src->size_);
		memcpy(data, actual_src->data_, actual_src->size_);

		DLLIST_insertLast(dllist, data, actual_src->size_);
		actual_src = actual_src->ops_->getNext(actual_src);
	}
	dllist->length_ = new_lenght;
	return kErrorCode_Ok;
}

s16 DLLIST_traverse(DLList* dllist, void(*callback) (MemoryNode*)) {
	if (NULL == dllist) return kErrorCode_DLLIST_NULL;

	if (NULL == callback) return kErrorCode_LIST_CALLBACK;

	MemoryNode* tmp_actual;
	if (NULL == dllist->first_) return kErrorCode_DLLIST_FIRST_NULL;
	tmp_actual = dllist->first_;
	if (NULL == tmp_actual) return kErrorCode_Memory;

	for (u16 i = 0; i < dllist->length_; ++i) {
		callback(tmp_actual);
		tmp_actual = tmp_actual->ops_->getNext(tmp_actual);
	}

	return kErrorCode_Ok;
}

void DLLIST_print(DLList* dllist) {

	printf("dllist info:\n");
	if (NULL == dllist)
	{
		printf("dllist = NULL \n");
		return;
	}

	printf("dllist address : %p\n", dllist);
	if (NULL == dllist->first_) printf("First address : %p\n", dllist->first_);
	if (NULL == dllist->last_) printf("Last address : %p\n", dllist->last_);
	printf("Lenght : %d\n", dllist->length_);
	printf("Capacity : %d\n", dllist->capacity_);


	MemoryNode* tmp_actual;
	
	tmp_actual = dllist->first_;
	printf("dllist Node:");
	for (u16 i = 0; i < dllist->length_; ++i) {
		printf("\nNode number: %d \n", i);
		tmp_actual->ops_->print(tmp_actual);
		tmp_actual = tmp_actual->ops_->getNext(tmp_actual);
	}
	printf("\n");
}
