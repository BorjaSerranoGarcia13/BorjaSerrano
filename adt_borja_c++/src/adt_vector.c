// adt_vector.c
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"
#include "adt_vector.h"

#include "ABGS_MemoryManager/abgs_memory_manager.h"


static s16 VECTOR_destroy(Vector *vector);	
static s16 VECTOR_reset(Vector *vector);		
static s16 VECTOR_softReset(Vector *vector);  
static u16 VECTOR_resize(Vector *vector, u16 new_size); 

// State queries
static u16 VECTOR_capacity(Vector *vector);		
static u16 VECTOR_length(Vector *vector);			
static bool VECTOR_isEmpty(Vector *vector);
static bool VECTOR_isFull(Vector *vector);

// Data queries
static void* VECTOR_first(Vector *vector); 
static void* VECTOR_last(Vector *vector); 
static void* VECTOR_at(Vector *vector, u16 position); 

// Insertion
static s16 VECTOR_insertFirst(Vector *vector, void *data, u16 bytes); 
static s16 VECTOR_insertLast(Vector *vector, void *data, u16 bytes); 
static s16 VECTOR_insertAt(Vector *vector, u16 position, void *data, u16 bytes); 

// Extraction
static void* VECTOR_extractFirst(Vector *vector); 
// For debugging:
#if DEBUG
	//void*(*extractFirst) (Vector *vector, u16 *size);
#endif // DEBUG
	//void*(*extractFirst) (Vector *vector, u16 *size);
#if DEBUG

#endif // DEBUG
static void* VECTOR_extractLast(Vector *vector); 
static void* VECTOR_extractAt(Vector *vector, u16 position); 

// Miscellaneous
static s16 VECTOR_concat(Vector *vector, Vector *vector_src); 
static s16 VECTOR_traverse(Vector *vector, void(*callback) (MemoryNode *)); 
static void VECTOR_print(Vector *vector); 


struct vector_ops_s vector_ops =
{
  .destroy = VECTOR_destroy,
  .reset = VECTOR_reset,
  .softReset = VECTOR_softReset,
	.resize = VECTOR_resize,

	.capacity = VECTOR_capacity,
	.length = VECTOR_length,
	.isEmpty = VECTOR_isEmpty,
	.isFull = VECTOR_isFull,

	.first = VECTOR_first,
	.last = VECTOR_last,
	.at = VECTOR_at,

	.insertFirst = VECTOR_insertFirst,
	.insertLast = VECTOR_insertLast,
	.insertAt = VECTOR_insertAt,

	.extractFirst = VECTOR_extractFirst,
	.extractLast = VECTOR_extractLast,
	.extractAt = VECTOR_extractAt,

	.concat = VECTOR_concat,
	.print = VECTOR_print,
	.traverse = VECTOR_traverse

};


s16 VECTOR_initWithoutCheck(Vector *vector, u16 capacity) {
	vector->head_ = 0;
	vector->tail_ = 0;
	vector->capacity_ = capacity;
	vector->ops_ = &vector_ops;

	VECTOR_traverse(vector, MEMNODE_createLite);

	return kErrorCode_Ok;
}

Vector* VECTOR_create(u16 capacity) {
	if (0 == capacity) {
		return NULL;
	}
	Vector* v = MM->malloc(sizeof(Vector));
	if (NULL == v) return NULL;
	v->storage_ = MM->malloc(capacity * sizeof(MemoryNode));
	if (NULL == v->storage_) {
		MM->free(v);
		return NULL;
	}
	v->capacity_ = capacity;
	VECTOR_initWithoutCheck(v, capacity);
	return v;
}

s16 VECTOR_destroy(Vector *vector)	
{
	if (NULL == vector)
	{
		return kErrorCode_Vector_NULL;
	}

	for (u16 i = vector->head_; i < vector->tail_; i++)
	{
		vector->storage_->ops_->reset(&vector->storage_[i]);
		// &vector->storage_[i]
	}
	if (NULL != vector->storage_)
	{
		MM->free(vector->storage_);
		vector->storage_ = NULL;
	}
	vector->head_ = 0;
	vector->tail_ = 0;
	vector->capacity_ = 0;
	if (NULL != vector)
	{
		MM->free(vector);
	}

	return kErrorCode_Ok;
}

s16 VECTOR_reset(Vector *vector)		
{
	if (NULL == vector)
	{
		return kErrorCode_Vector_NULL;
	}
	if (NULL == vector->storage_)
	{
		return kErrorCode_VectorStorage_NULL;
	}
	for (u16 i = vector->head_; i < vector->tail_; i++)
	{
		vector->storage_->ops_->reset(&vector->storage_[i]);
	}
	vector->head_ = 0;
	vector->tail_ = 0;

	return kErrorCode_Ok;
}

s16 VECTOR_softReset(Vector *vector)	
{
  if (NULL == vector)
  {
    return kErrorCode_Vector_NULL;
  }
  if (NULL == vector->storage_)
  {
    return kErrorCode_VectorStorage_NULL;
  }
  for (u16 i = vector->head_; i < vector->tail_; i++)
  {
    vector->storage_->ops_->softReset(&vector->storage_[i]);
  }
  vector->head_ = 0;
  vector->tail_ = 0;

  return kErrorCode_Ok;
}

u16 VECTOR_resize(Vector *vector, u16 new_size) 
{
	if (NULL == vector)
	{
		return 0;
	}
	if (new_size == 0)
	{
		return 0;
	}
	if (new_size == vector->capacity_)
	{
		return kErrorCode_Ok;
	}
	MemoryNode* newStorage = MM->malloc(sizeof(MemoryNode) * new_size);
	if (NULL == newStorage)
	{
		return 0;
	}
	if (new_size > vector->capacity_)
	{
		memcpy(newStorage, vector->storage_, sizeof(MemoryNode) * vector->capacity_);
		for (u16 i = vector->capacity_; i < new_size; i++)
		{
			MEMNODE_createLite(&newStorage[i]);
		}
	}
	else
	{
		memcpy(newStorage, vector->storage_, sizeof(MemoryNode) * new_size);
		for (u16 i = new_size; i < vector->capacity_; i++)
		{
      vector->storage_->ops_->reset(&vector->storage_[i]);
		}
	}

	memset(vector->storage_, 0, sizeof(MemoryNode) * vector->capacity_);
	if (NULL != vector->storage_)
	{
		MM->free(vector->storage_);
	}
	vector->storage_ = newStorage;
	vector->capacity_ = new_size;
	if (vector->tail_ > new_size)
	{
		vector->tail_ = new_size;
	}

	return kErrorCode_Ok;
}

// State queries
u16 VECTOR_capacity(Vector *vector)	{	
	if (NULL == vector)
	{
		return 0;
	}
	return vector->capacity_;
}

u16 VECTOR_length(Vector *vector)			
{
	if (NULL == vector)
	{
		return kErrorCode_Vector_NULL;
	}

	return vector->tail_ - vector->head_;
}

bool VECTOR_isEmpty(Vector *vector)
{
	if (NULL == vector)
	{
		return true;
	}

	if (vector->head_ == vector->tail_)
	{
		return true;
	}

	return false;
}

bool VECTOR_isFull(Vector *vector)
{
	if (NULL == vector)
	{
		return false;
	}

	if (vector->capacity_ == vector->tail_)
	{
		return true;
	}

	return false;
}

// Data queries
void* VECTOR_first(Vector *vector) 
{
	if (NULL == vector)
	{
		return NULL;
	}
	if (VECTOR_isEmpty(vector)) { return NULL; }
	if (NULL == vector->storage_->ops_->data(&vector->storage_[vector->head_]))
	{
		return NULL;
	}
	return vector->storage_->ops_->data(&vector->storage_[vector->head_]);
}

void* VECTOR_last(Vector *vector) {
	if (NULL == vector)
	{
		return NULL;
	}
	if (VECTOR_isEmpty(vector)) { return NULL; }
	if (NULL == vector->storage_->ops_->data(&vector->storage_[vector->tail_ - 1]))
	{
		return NULL;
	}
	return vector->storage_->ops_->data(&vector->storage_[vector->tail_ - 1]);
}

void* VECTOR_at(Vector *vector, u16 position) 
{
	if (NULL == vector)
	{
		return NULL;
	}
	if (VECTOR_isEmpty(vector)) { return NULL; }
	if (position > vector->tail_ - 1) { return NULL; }
	if (NULL == vector->storage_->ops_->data(&vector->storage_[position]))
	{
		return NULL;
	}
	return vector->storage_->ops_->data(&vector->storage_[position]);
}

// Insertion
s16 VECTOR_insertFirst(Vector *vector, void *data, u16 bytes) 
{
	if (NULL == vector)
	{
		return kErrorCode_Vector_NULL;
	}
	if (NULL == data)
	{
		return kErrorCode_VectorData_NULL;
	}
	if (0 == bytes)
	{
		return kErrorCode_Parameters_Zero; 
	}
	if (VECTOR_isFull(vector))
	{
		return kErrorCode_VectorCapacity_Zero; 
	}
	if (VECTOR_isEmpty(vector))
	{
		vector->storage_->ops_->setData(&vector->storage_[vector->head_], data, bytes);
		vector->tail_++;
		return  kErrorCode_Ok;
	}
	for (u16 i = vector->tail_; i > vector->head_; i--)
	{
		vector->storage_->ops_->setData(&vector->storage_[i],
			vector->storage_->ops_->data(&vector->storage_[i - 1]),
			vector->storage_->ops_->size(&vector->storage_[i - 1]));
		vector->storage_->ops_->softReset(&vector->storage_[i - 1]);
	}
	vector->storage_->ops_->softReset(&vector->storage_[vector->head_]);
	vector->storage_->ops_->setData(&vector->storage_[vector->head_], data, bytes);
	vector->tail_++;

	return  kErrorCode_Ok;
}

s16 VECTOR_insertLast(Vector *vector, void *data, u16 bytes) 
{
	if (NULL == vector)
	{
		return kErrorCode_Vector_NULL;
	}
	if (NULL == data)
	{
		return kErrorCode_VectorData_NULL;
	}
	if (0 == bytes)
	{
		return kErrorCode_Parameters_Zero;
	}
	if (VECTOR_isFull(vector))
	{
		return kErrorCode_VectorCapacity_Zero; 
	}

	vector->storage_->ops_->setData(&vector->storage_[vector->tail_], data, bytes);
	vector->tail_++;

	return  kErrorCode_Ok;
}

s16 VECTOR_insertAt(Vector *vector, void *data, u16 bytes, u16 position) 
{
	if (NULL == vector)
	{
		return kErrorCode_Vector_NULL;
	}
	if (NULL == data)
	{
		return kErrorCode_VectorData_NULL;
	}
	if (0 == bytes)
	{
		return kErrorCode_Parameters_Zero; 
	}
	if (VECTOR_isFull(vector))
	{
		return kErrorCode_VectorCapacity_Zero; 
	}

	if (position > vector->capacity_)
	{
		return kErrorCode_Vector_OUT_RANGE;
	}

	if (position >= vector->tail_)
	{
		return VECTOR_insertLast(vector, data, bytes);
	}

	if (VECTOR_isEmpty(vector))
	{
		return VECTOR_insertFirst(vector, data, bytes);
	}

	for (u16 i = vector->tail_; i > position; i--)
	{
		vector->storage_->ops_->setData(&vector->storage_[i],
			vector->storage_->ops_->data(&vector->storage_[i - 1]),
			vector->storage_->ops_->size(&vector->storage_[i - 1]));
		vector->storage_->ops_->softReset(&vector->storage_[i - 1]);
	}
	vector->storage_->ops_->setData(&vector->storage_[position], data, bytes);
	vector->tail_++;

	return  kErrorCode_Ok;
}

// Extraction
void* VECTOR_extractFirst(Vector* vector)
{
	if (NULL == vector)
	{
		return NULL;
	}
	if (VECTOR_isEmpty(vector))
	{
		return NULL;
	}

	if (NULL == vector->storage_)
	{
		return NULL;
	}
	void* nodeVector = vector->storage_->ops_->data(&vector->storage_[vector->head_]);
	
	vector->storage_->ops_->softReset(&vector->storage_[vector->head_]);
	for (u16 i = vector->head_; i < vector->tail_ - 1; i++)
	{
		vector->storage_->ops_->setData(&vector->storage_[i],
			vector->storage_->ops_->data(&vector->storage_[i + 1]),
			vector->storage_->ops_->size(&vector->storage_[i + 1]));
		vector->storage_->ops_->softReset(&vector->storage_[i + 1]);
	}
	vector->tail_--;
	return nodeVector;
}
// For debugging:
#if DEBUG
	//void*(*extractFirst) (Vector *vector, u16 *size);
#endif // DEBUG
	//void*(*extractFirst) (Vector *vector, u16 *size);
#if DEBUG

#endif // DEBUG
void* VECTOR_extractLast(Vector *vector) 
{
	if (NULL == vector)
	{
		return NULL;
	}
	if (VECTOR_isEmpty(vector))
	{
		return NULL;
	}

	if (NULL == vector->storage_)
	{
		return NULL;
	}
	void* nodeVector = vector->storage_->ops_->data(&vector->storage_[vector->tail_ - 1]);
	
	vector->storage_->ops_->softReset(&vector->storage_[vector->tail_ - 1]);
	vector->tail_--;
	return nodeVector;
}

void* VECTOR_extractAt(Vector *vector, u16 position) 
{
	if (NULL == vector)
	{
		return NULL;
	}
	if (VECTOR_isEmpty(vector))
	{
		return NULL;
	}
	if (position >= vector->capacity_)
	{
		return NULL; 
	}
	if (position >= vector->tail_)
	{
		return NULL;
	}
	if (position == vector->tail_)
	{
		return VECTOR_extractLast(vector);
	}
	if (position == vector->head_)
	{
		return VECTOR_extractFirst(vector);
	}

	if (NULL == vector->storage_)
	{
		return NULL;
	}
	void* nodeVector = vector->storage_->ops_->data(&vector->storage_[position]);
	vector->storage_->ops_->softReset(&vector->storage_[position]);
	for (u16 i = position; i < vector->tail_; i++)
	{
		vector->storage_->ops_->setData(&vector->storage_[i],
			vector->storage_->ops_->data(&vector->storage_[i + 1]),
			vector->storage_->ops_->size(&vector->storage_[i + 1]));
		vector->storage_->ops_->softReset(&vector->storage_[i + 1]);
	}
	vector->tail_--;
	return nodeVector;
}

// Miscellaneous
s16 VECTOR_concat(Vector *vector, Vector *vector_src) 
{
	if (NULL == vector)return kErrorCode_Vector_NULL;
	if (NULL == vector_src)return kErrorCode_VectorSrc_NULL;

	MemoryNode* new_storage = MM->malloc(sizeof(MemoryNode) * (vector->capacity_ + vector_src->capacity_));
	if (NULL == new_storage) return kErrorCode_Memory;

	if (NULL == vector->storage_)
	{
		return kErrorCode_VectorStorage_NULL;
	}
	memcpy(new_storage, vector->storage_, sizeof(MemoryNode) * VECTOR_length(vector));

	for (u16 i = vector->tail_; i < (vector->ops_->length(vector) + vector_src->ops_->length(vector_src)); ++i) {
		MEMNODE_createLite(&new_storage[i]);
		vector_src->storage_->ops_->memCopy(&new_storage[i],
			vector_src->storage_->ops_->data(&vector_src->storage_[i - VECTOR_length(vector)]),
			vector_src->storage_->ops_->size(&vector_src->storage_[i - VECTOR_length(vector)]));
	}
	for (u16 i = (VECTOR_length(vector) + VECTOR_length(vector_src)); i < (vector->capacity_ + vector_src->capacity_); ++i) {
		MEMNODE_createLite(&new_storage[i]);
	}
	memset(vector->storage_, 0, sizeof(MemoryNode) * vector->capacity_);
	MM->free(vector->storage_);
	vector->storage_ = new_storage;

	vector->tail_ = VECTOR_length(vector) + VECTOR_length(vector_src);
	vector->capacity_ = vector->capacity_ + vector_src->capacity_;

	return kErrorCode_Ok;
}

s16 VECTOR_traverse(Vector *vector, void(*callback) (MemoryNode *)) 
{
	if (NULL == vector)
	{
		return kErrorCode_Vector_NULL;
	}
	if (NULL == vector->storage_)
	{
		return kErrorCode_VectorStorage_NULL;
	}
	for (u16 i = vector->head_; i < vector->capacity_; i++)
	{
		callback(&vector->storage_[i]);
	}
	return kErrorCode_Ok;
}

void VECTOR_print(Vector *vector) 
{
  if (NULL != vector)
  {
    printf("[Vector Info] Address : %p\n", vector);
    printf("[Vector Info] Head : %d\n", vector->head_);
    printf("[Vector Info] Tail : %d\n", vector->tail_);
    printf("[Vector Info] Capacity : %d\n", vector->capacity_);
    printf("[Vector Info] Data address: %p\n", vector->storage_);
    for (int i = 0; i < vector->tail_; i++) {
      printf("[Vector Info]  Storage #%d:\n", i);
      vector->storage_->ops_->print(&vector->storage_[i]);
    }
  }
}
