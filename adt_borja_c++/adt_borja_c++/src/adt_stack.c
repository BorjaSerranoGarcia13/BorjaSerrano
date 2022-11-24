// adt_stack.c
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//
#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"
#include "adt_stack.h"

#include "ABGS_MemoryManager\abgs_memory_manager.h"

static s16 STACK_initWithoutCheck(Stack *stack, u16 capacity);
static s16 STACK_destroy(Stack *stack);	
static s16 STACK_reset(Stack *stack);		
static u16 STACK_resize(Stack *stack, u16 new_size); 

// State queries
static u16 STACK_capacity(Stack *stack);		
static u16 STACK_length(Stack *stack);			
static bool STACK_isEmpty(Stack *stack);
static bool STACK_isFull(Stack *stack);

// Data queries
static void* STACK_top(Stack *stack); 

// Insertion
static s16 STACK_push(Stack *stack, void *data, u16 bytes); 


// Extraction
static void* STACK_pop(Stack *stack); 


// Miscellaneous
static s16 STACK_concat(Stack *stack, Stack *dllist_src); 
static s16 STACK_traverse(Stack *stack, void(*callback) (MemoryNode *)); 
static void STACK_print(Stack *stack); 


struct stack_ops_s stack_ops =
{
	.destroy = STACK_destroy,
	.destroy = STACK_destroy,
	.reset = STACK_reset,
	.resize = STACK_resize,

	.capacity = STACK_capacity,
	.length = STACK_length,
	.isEmpty = STACK_isEmpty,
	.isFull = STACK_isFull,

	.top = STACK_top,
	.pop = STACK_pop,
	.push = STACK_push,

	.concat = STACK_concat,
	.print = STACK_print,

};


s16 STACK_initWithoutCheck(Stack *stack, u16 capacity) {
	stack->ops_ = &stack_ops;
	return kErrorCode_Ok;
}

Stack* STACK_create(u16 capacity) {
	if (0 == capacity) {
		return NULL;
	}
	Stack *s = MM->malloc(sizeof(Stack));
	if (NULL == s) return NULL;
	s->storage_ = VECTOR_create(capacity);
	if (NULL == s->storage_) {
		MM->free(s);
		return NULL;
	}
	STACK_initWithoutCheck(s, capacity);
	return s;
}

s16 STACK_destroy(Stack *stack)	
{
	if (NULL == stack) return kErrorCode_STACK_NULL;
	if (NULL == stack->storage_) return kErrorCode_STACK_STORAGE_NULL;

	stack->storage_->ops_->destroy(stack->storage_);

	MM->free(stack);
	return kErrorCode_Ok;
}

s16 STACK_reset(Stack *stack)		
{
	if (NULL == stack) return kErrorCode_STACK_NULL;
	if (NULL == stack->storage_) return kErrorCode_STACK_STORAGE_NULL;

	return stack->storage_->ops_->reset(stack->storage_);
}

u16 STACK_resize(Stack *stack, u16 new_size) 
{
	if (NULL == stack) return kErrorCode_STACK_NULL;
	if (new_size == 0) return kErrorCode_STACK_BYTES_0;
	if (new_size == stack->storage_->capacity_) return kErrorCode_STACK_BYTES_0;

	return stack->storage_->ops_->resize(stack->storage_, new_size);
}

// State queries
u16 STACK_capacity(Stack *stack)		
{
	if (NULL == stack)
	{
		return 0;
	}

	return stack->storage_->ops_->capacity(stack->storage_);
}

u16 STACK_length(Stack *stack)			
{
	if (NULL == stack) {
		return 0;
	}

	return stack->storage_->ops_->length(stack->storage_);
}

bool STACK_isEmpty(Stack *stack)
{
	if (NULL == stack) return true;
	if (stack->storage_->ops_->isEmpty(stack->storage_)) return true;

	return false;
}

bool STACK_isFull(Stack *stack)
{
	if (NULL == stack) return false;
	if (stack->storage_->ops_->isFull(stack->storage_)) return true;

	return false;
}

// Data queries
void* STACK_top(Stack *stack) 
{
	if (NULL == stack) return NULL;
	if (STACK_isEmpty(stack)) return NULL;
	return stack->storage_->ops_->last(stack->storage_);
}

// Insertion
s16 STACK_push(Stack *stack, void *data, u16 bytes) 
{
	if (NULL == stack) return kErrorCode_STACK_NULL;
	if (NULL == data) return kErrorCode_STACK__DATA_NULL;
	if (0 == bytes) return kErrorCode_STACK_BYTES_0;
	if (STACK_isFull(stack)) return kErrorCode_STACK_FULL;

	return stack->storage_->ops_->insertLast(stack->storage_, data, bytes);
}


// Extraction
void* STACK_pop(Stack *stack) 
{
	if (NULL == stack) return NULL;
	if (STACK_isEmpty(stack)) return NULL;

	return stack->storage_->ops_->extractLast(stack->storage_);
}


// Miscellaneous
s16 STACK_concat(Stack *stack, Stack *stack_src) 
{
	if (NULL == stack) return kErrorCode_STACK_NULL;
	if (NULL == stack_src) return kErrorCode_STACK_SRC_NULL;
	if (NULL == stack->storage_) return kErrorCode_STACK_STORAGE_NULL;
	if (NULL == stack_src->storage_) return kErrorCode_STACK_STORAGE_NULL;

	return stack->storage_->ops_->concat(stack->storage_, stack_src->storage_);
}

s16 STACK_traverse(Stack *stack, void(*callback) (MemoryNode *)) 
{
	if (NULL == stack) return kErrorCode_STACK_NULL;
	if (NULL == stack->storage_) return kErrorCode_STACK_STORAGE_NULL;

	for (int i = 0; i < stack->storage_->capacity_; i++)
	{ 
		callback(&stack->storage_->storage_[i]);
	}
}

void STACK_print(Stack *stack) 
{
	printf("Stack :\n");
	if (NULL == stack)
	{
		printf("NULL STACK \n");
		return;
	}

	printf("Stack address-> %p\n", stack);


}
