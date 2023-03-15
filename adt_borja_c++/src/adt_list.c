// adt_list.c
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"
#include "adt_list.h"

#include "ABGS_MemoryManager\abgs_memory_manager.h"


static s16 LIST_initWithoutCheck(List* list);

static s16 LIST_destroy(List* list);
static s16 LIST_reset(List* list);
static s16 LIST_resize(List* list, u16 new_size);

static u16 LIST_capacity(List* list);
static u16 LIST_length(List* list);
static bool LIST_isEmpty(List* list);
static bool LIST_isFull(List* list);

static void* LIST_first(List* list);
static void* LIST_last(List* list);
static void* LIST_at(List* list, u16 position);

static s16 LIST_insertFirst(List* list, void* data, u16 bytes);
static s16 LIST_insertLast(List* list, void* data, u16 bytes);
static s16 LIST_insertAt(List* list, void* data, u16 bytes, u16 position);

static void* LIST_extractFirst(List* list);
static void* LIST_extractLast(List* list);
static void* LIST_extractAt(List* list, u16 position);

static s16 LIST_concat(List* list, List* list_src);

static s16 LIST_traverse(List* list, void(*callback) (MemoryNode*));
static void LIST_print(List* list);

struct list_ops_s list_ops =
{
	.destroy = LIST_destroy,
	.reset = LIST_reset,
	.resize = LIST_resize,

	.capacity = LIST_capacity,
	.length = LIST_length,
	.isEmpty = LIST_isEmpty,
	.isFull = LIST_isFull,

	.first = LIST_first,
	.last = LIST_last,
	.at = LIST_at,

	.insertFirst = LIST_insertFirst,
	.insertLast = LIST_insertLast,
	.insertAt = LIST_insertAt,

	.extractFirst = LIST_extractFirst,
	.extractLast = LIST_extractLast,
	.extractAt = LIST_extractAt,

	.concat = LIST_concat,
	.print = LIST_print
};

// List Definitions
List* LIST_create(u16 capacity) {
	if (0 == capacity) { return NULL; }

	List* list = MM->malloc(sizeof(List));

	if (NULL == list) return NULL;

	list->capacity_ = capacity;

	LIST_initWithoutCheck(list);
	return list;
}

s16 LIST_initWithoutCheck(List* list)
{
	list->first_ = NULL;
	list->last_ = NULL;
	list->length_ = 0;
	
	list->ops_ = &list_ops;

	return kErrorCode_Ok;
}

s16 LIST_destroy(List* list)
{
	if (kErrorCode_LIST_NULL == LIST_reset(list))return kErrorCode_LIST_NULL;

	list->capacity_ = 0;
	MM->free(list);
	return kErrorCode_Ok;
}

s16 LIST_reset(List* list)
{
	if (NULL == list)return kErrorCode_LIST_NULL;

	if (NULL == list->first_) return kErrorCode_LIST_FIRST_NULL;

	if (NULL == list->last_) return kErrorCode_LIST_LAST_NULL;

	if (LIST_isEmpty(list))return kErrorCode_Ok;

	MemoryNode* tmp_actual;
	MemoryNode* tmp_next;
	tmp_actual = list->first_;
	if (NULL == tmp_actual)
	{
		return kErrorCode_LIST_FIRST_NULL;
	}
	tmp_next = list->first_->ops_->getNext(list->first_);
	if (NULL == tmp_next)
	{
		return kErrorCode_LIST_NULL;
	}
	for (u16 i = 0; i < list->length_; ++i) {
		tmp_next = tmp_actual->ops_->getNext(tmp_actual);
		tmp_actual->ops_->free(tmp_actual);
		tmp_actual = tmp_next;
	}
	list->first_ = NULL;
	list->last_ = NULL;
	list->length_ = 0;
	return kErrorCode_Ok;
}

s16 LIST_resize(List* list, u16 new_capacity) {
	if (NULL == list) return kErrorCode_LIST_NULL;



	if (new_capacity == list->capacity_) return kErrorCode_Ok;

	if (0 == new_capacity) return kErrorCode_LIST_CAPACITY_0;


	if (LIST_isEmpty(list)) {
		list->capacity_ = new_capacity;
		return kErrorCode_Ok;
	}

	if (NULL == list->first_) return kErrorCode_LIST_FIRST_NULL;

	if (list->length_ > new_capacity) {
		MemoryNode* tmp_actual;
		
		MemoryNode* tmp_aux;
		tmp_actual = list->first_;
		if (NULL == tmp_actual)
		{
			return kErrorCode_LIST_FIRST_NULL;
		}
		for (u16 i = 0; i < new_capacity; ++i) {
			tmp_actual = tmp_actual->ops_->getNext(tmp_actual);
		}
		tmp_aux = tmp_actual->ops_->getNext(tmp_actual);
		if (NULL == tmp_actual)
		{
			return kErrorCode_LIST_NULL;
		}
		for (u16 i = new_capacity; i < list->length_; ++i) {
			tmp_aux = tmp_actual->ops_->getNext(tmp_actual);
			tmp_actual->ops_->free(tmp_actual);
			tmp_actual = tmp_aux;
		}
		list->length_ = new_capacity;
	}

	list->capacity_ = new_capacity;
	return kErrorCode_Ok;
}

u16 LIST_capacity(List* list) {
	if (NULL == list) 	return 0;

	return list->capacity_;
}

u16 LIST_length(List* list) {
	if (NULL == list) 	return 0;

	return list->length_;
}

bool LIST_isEmpty(List* list) {
	if (NULL == list) return false;

	if (0 == list->length_) return true;

	return false;
}

bool LIST_isFull(List* list) {
	if (NULL == list) return false;

	if (0 == list->capacity_)return false;

	if (list->length_ == list->capacity_) return true;

	return false;
}

void* LIST_first(List* list) {
	if (NULL == list) {
		return NULL;
	}

	if (list->ops_->isEmpty(list)) 
	{
		return NULL;
	}

	if (NULL == list->first_) return NULL;

	if (NULL == list->first_->ops_->data(list->first_))
	{
		return NULL;
	}

	return list->first_->ops_->data(list->first_);
}

void* LIST_last(List* list) {
	if (NULL == list) {
		return NULL;
	}

	if (list->ops_->isEmpty(list)) {
		return NULL;
	}

	if (NULL == list->last_) return NULL;

	if (NULL == list->last_->ops_->data(list->last_)) {
		return NULL;
	}

	return list->last_->ops_->data(list->last_);
}

void* LIST_at(List* list, u16 position) {
	if (NULL == list) return NULL;

	if (list->ops_->isEmpty(list)) return NULL;

	if (position >= list->length_)return NULL;

	MemoryNode* list_actual;

	if (NULL == list->first_) return NULL;
	list_actual = list->first_;
	if (NULL == list_actual)
	{
		return kErrorCode_Memory;
	}


	for (u16 i = 0; i < position; ++i) {
		list_actual = list_actual->next_;
	}

	if (NULL == list_actual->ops_->data(list_actual)) return NULL;

	return list_actual->ops_->data(list_actual);
}

s16 LIST_insertFirst(List* list, void* data, u16 bytes) {

	if (NULL == list)return kErrorCode_LIST_NULL;

	if (NULL == data) return kErrorCode_LIST_DATA_NULL;

	if (0 == bytes) return kErrorCode_LIST_BYTES_0;

	if (list->ops_->isFull(list)) return kErrorCode_LIST_FULL;

	
	MemoryNode* mn = MEMNODE_create();
	if (NULL == mn) return kErrorCode_Memory;

	if (list->ops_->isEmpty(list)) {
		mn->ops_->setNext(mn, NULL);
		mn->ops_->setData(mn, data, bytes);
		list->first_ = mn;
		list->last_ = mn;
	}
	else {
		mn->ops_->setNext(mn, list->first_);
		mn->ops_->setData(mn, data, bytes);
		list->first_ = mn;
	}

	if (NULL == list->first_) return kErrorCode_LIST_FIRST_NULL;

	if (NULL == list->last_) return kErrorCode_LIST_LAST_NULL;



	list->length_++;
	return kErrorCode_Ok;
}

s16 LIST_insertLast(List* list, void* data, u16 bytes) {

	if (NULL == list) return kErrorCode_LIST_NULL;

	if (NULL == data) return kErrorCode_LIST_DATA_NULL;

	if (0 == bytes) return kErrorCode_LIST_BYTES_0;

	if (list->ops_->isFull(list)) return kErrorCode_LIST_FULL;

	if (list->ops_->isEmpty(list)) return LIST_insertFirst(list, data, bytes);

	if (NULL == list->last_) return kErrorCode_LIST_LAST_NULL;

	MemoryNode* mn = MEMNODE_create();
	if (NULL == mn)
	{
		return kErrorCode_Memory;
	}

	list->last_->ops_->setNext(list->last_, mn);
	mn->ops_->setData(mn, data, bytes);
	mn->ops_->setNext(mn, NULL);
	list->last_ = mn;

	list->length_++;

	return kErrorCode_Ok;
}

s16 LIST_insertAt(List* list, void* data, u16 bytes, u16 position) {
	if (NULL == list)
	{
		return kErrorCode_LIST_NULL;
	}

	if (NULL == data)
	{
		return kErrorCode_LIST_DATA_NULL;
	}

	if (0 == bytes) {
		return kErrorCode_LIST_BYTES_0;
	}

	if (list->ops_->isFull(list)) 	return kErrorCode_LIST_FULL;

	if (position >= list->capacity_) return kErrorCode_LIST_OUT_RANGE;

	if (position >= list->length_) return LIST_insertLast(list, data, bytes);

	if (0 == position)
	{
		return list->ops_->insertFirst(list, data, bytes);
	}

	if (list->ops_->isEmpty(list))
	{
		return LIST_insertFirst(list, data, bytes);
	}

	if (NULL == list->first_) return kErrorCode_LIST_FIRST_NULL;

	MemoryNode* mn;
	
	mn = list->first_;
	if (NULL == mn)
	{
		return kErrorCode_Memory;
	}
	for (u16 i = 0; i < position - 1; ++i) {
		mn = mn->ops_->getNext(mn);
	}

	MemoryNode* mn2 = MEMNODE_create();
	if (NULL == mn2) return kErrorCode_Memory;


	mn2->ops_->setData(mn2, data, bytes);
	mn2->ops_->setNext(mn2, mn->ops_->getNext(mn));
	mn->ops_->setNext(mn, mn2);

	list->length_++;

	return kErrorCode_Ok;
}

void* LIST_extractFirst(List* list) {
	if (NULL == list)
	{
		return NULL;
	}

	if (NULL == list->first_)
	{
		return NULL;
	}

	if (list->ops_->isEmpty(list))
	{
		return NULL;
	}

	void* first_data = list->first_->ops_->data(list->first_);
	if (NULL == first_data)
	{
		return NULL;
	}

	MemoryNode* mn;
	mn = list->first_->ops_->getNext(list->first_);

	list->first_->ops_->softFree(list->first_);
	list->first_ = mn;
	list->length_--;

	return first_data;
}

void* LIST_extractLast(List* list) {

	if (NULL == list) return NULL;

	if (NULL == list->first_) return NULL;
	if (NULL == list->last_) return NULL;

	if (list->ops_->isEmpty(list)) return NULL;

	void* last_data = list->last_->ops_->data(list->last_);
	if (NULL == last_data)
	{
		return NULL;
	}

	MemoryNode* mn;
	mn = list->first_;
	if (NULL == mn)
	{
		return NULL;
	}

	for (u16 i = 0; i < list->length_ - 2; ++i) {
		mn = mn->ops_->getNext(mn);
	}

	list->last_->ops_->softFree(list->last_);
	mn->ops_->setNext(mn, NULL);
	list->last_ = mn;
	list->length_--;

	return last_data;
}

void* LIST_extractAt(List* list, u16 position) {
	if (NULL == list) return NULL;

	if (list->ops_->isEmpty(list)) return NULL;

	if (NULL == list->first_) return NULL;

	if (position >= list->capacity_ && list->capacity_ != 0) return NULL;

	if (position >= list->length_) return NULL;

	if (0 == position) list->ops_->extractFirst(list);

	if ((list->length_ - 1) == position) list->ops_->extractLast(list);


	MemoryNode* mn;
	MemoryNode* mnOut;
	void* data;

	mn = list->first_;
	if (NULL == mn)
	{
		return NULL;
	}
	for (u16 i = 0; i < position - 1; ++i) {
		mn = mn->ops_->getNext(mn);
	}

	mnOut = mn->ops_->getNext(mn);
	if (NULL == mnOut)
	{
		return NULL;
	}
	data = mnOut->ops_->data(mnOut);
	if (NULL == data)
	{
		return NULL;
	}
	mn->ops_->setNext(mn, mnOut->ops_->getNext(mnOut));
	mnOut->ops_->softFree(mnOut);

	if (NULL == list->last_) return kErrorCode_LIST_LAST_NULL;
	if (NULL == mn->ops_->getNext(mn)) list->last_ = mn;

	list->length_--;
	return data;
}

s16 LIST_concat(List* list, List* list_src) {
	if (NULL == list) return kErrorCode_LIST_NULL;

	if (NULL == list_src) return kErrorCode_LIST_SRC_NULL;

	if (list->ops_->isEmpty(list_src)) return kErrorCode_Ok;

	u16 new_lenght = list->length_ + list_src->length_;
	u16 new_capacity = list->capacity_ + list_src->capacity_;
	if (list->capacity_ != 0) {
		list->capacity_ = new_capacity;
	}

	if (NULL == list->first_) return kErrorCode_LIST_FIRST_NULL;

	MemoryNode* mn;
	mn = list_src->first_;
	if (NULL == mn) return kErrorCode_Memory;
	for (u16 i = 0; i < list_src->length_; ++i) {
		void* data = MM->malloc(mn->size_);
		memcpy(data, mn->data_, mn->size_);

		list->ops_->insertLast(list, data, mn->size_);
		mn = mn->ops_->getNext(mn);
	}
	list->length_ = new_lenght;
	return kErrorCode_Ok;

}

s16 LIST_traverse(List* list, void(*callback) (MemoryNode*)) {

	if (NULL == list) return kErrorCode_LIST_NULL;

	if (NULL == callback) return kErrorCode_LIST_CALLBACK;

	if (NULL == list->first_) return kErrorCode_LIST_FIRST_NULL;

	MemoryNode* mn;
	mn = list->first_;
	if (NULL == mn) return kErrorCode_Memory;
	for (u16 i = 0; i < list->length_; ++i) {
		callback(mn);
		mn = mn->ops_->getNext(mn);
	}
	return kErrorCode_Ok;
}

void LIST_print(List* list) {

	printf("List :\n");
	if (NULL == list)
	{
		printf("NULL LIST \n");
		return;
	}

	if (NULL == list->first_) return kErrorCode_LIST_FIRST_NULL;
	if (NULL == list->last_) return kErrorCode_LIST_LAST_NULL;

	printf("List address-> %p\n", list);
	printf("Lenght-> %d\n", list->length_);
	printf("Capacity-> %d\n", list->capacity_);
	if (NULL == list->first_)printf("First address-> %p\n", list->first_);
	if (NULL == list->first_)printf("Last address-> %p\n", list->last_);

	MemoryNode* mn;
	mn = list->first_;
	printf("List Node:");
	for (u16 i = 0; i < list->length_; ++i) {
		printf("\nNode number->  %d \n", i);
		mn->ops_->print(mn);
		mn = mn->ops_->getNext(mn);
	}
}