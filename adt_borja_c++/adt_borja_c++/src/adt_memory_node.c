// adt_memory_node.c
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"
#include "adt_memory_node.h"

#include "ABGS_MemoryManager/abgs_memory_manager.h"


// Memory Node Declarations
static s16 MEMNODE_initWithoutCheck(MemoryNode *node);	
static void* MEMNODE_data(MemoryNode *node);	
static u16 MEMNODE_size(MemoryNode *node);		

static s16 MEMNODE_setData(MemoryNode *node, void *src, u16 bytes); 

static s16 MEMNODE_reset(MemoryNode *node);		
static s16 MEMNODE_softReset(MemoryNode *node);		
static s16 MEMNODE_free(MemoryNode *node);		
static s16 MEMNODE_softFree(MemoryNode *node);	

static s16 MEMNODE_memSet(MemoryNode *node, u8 value);
static s16 MEMNODE_memCopy(MemoryNode *node, void *src, u16 bytes); 
static s16 MEMNODE_memConcat(MemoryNode *node, void *src, u16 bytes); 
static s16 MEMNODE_memMask(MemoryNode *node, u8 mask); 

static void MEMNODE_print(MemoryNode *node);

static s16 MEMNODE_setNext(MemoryNode *node, MemoryNode *node2);
static MemoryNode* MEMNODE_getNext(MemoryNode *node);
static s16 MEMNODE_setPrev(MemoryNode *node, MemoryNode *node2);
static MemoryNode* MEMNODE_getPrev(MemoryNode *node);

// Memory Node's API Definitions
struct memory_node_ops_s memory_node_ops =
{
	.data = MEMNODE_data,
	.size = MEMNODE_size,
	.setData = MEMNODE_setData,
	.reset = MEMNODE_reset,
	.softReset = MEMNODE_softReset,
	.free = MEMNODE_free,
	.softFree = MEMNODE_softFree,
	.memSet = MEMNODE_memSet,
	.memCopy = MEMNODE_memCopy,
	.memConcat = MEMNODE_memConcat,
  .memMask = MEMNODE_memMask,
	.print = MEMNODE_print,
	.setNext = MEMNODE_setNext,
	.getNext = MEMNODE_getNext,
	.setPrev = MEMNODE_setPrev,
	.getPrev = MEMNODE_getPrev
};

// Memory Node Definitions
MemoryNode* MEMNODE_create() {
  MemoryNode *node = MM->malloc(sizeof(MemoryNode));
  if (NULL == node) {
#ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return NULL;
  }
  MEMNODE_initWithoutCheck(node);
  return node;
}

s16 MEMNODE_createLite(MemoryNode * node)
{
  if (NULL == node)
  {
    return kErrorCode_Node_NULLNode;
  }
  MEMNODE_initWithoutCheck(node);
  return kErrorCode_Ok;
}

s16 MEMNODE_createFromRef(MemoryNode **node) {
  if (NULL == node) {
    return kErrorCode_Node_NULLNode;
  }
  *node = MEMNODE_create();
  if (NULL == *node) {
#ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return kErrorCode_Memory;
  }
  return kErrorCode_Ok;
}


s16 MEMNODE_initWithoutCheck(MemoryNode *node)
{
	node->data_ = NULL;
	node->size_ = 0;
	node->ops_ = &memory_node_ops;
	return kErrorCode_Ok;
}

void* MEMNODE_data(MemoryNode *node) 
{
	if (NULL == node)
	{
		return NULL;
	}

	return node->data_;
}

u16	MEMNODE_size(MemoryNode *node) 
{
	if (node == NULL)
	{
		return 0;
	}

	return node->size_;
}

s16 MEMNODE_setData(MemoryNode *node, void *src, u16 bytes) 
{
	if (NULL == node)
	{
		return kErrorCode_Node_NULLNode;
	}
	if (src == NULL)
	{
		return kErrorCode_Parameters_NULL;
	}
	if (bytes == 0)
	{
		return kErrorCode_Parameters_NULL;
	}
	if (NULL != node->data_)
	{
		MM->free(node->data_);
		node->data_ = NULL;
		node->size_ = 0;
	}

	node->data_ = src;
	node->size_ = bytes;
	return kErrorCode_Ok;
}

s16 MEMNODE_reset(MemoryNode *node)		
{
	if (NULL == node)
	{
		return kErrorCode_Node_NULLNode;
	}
	if (NULL != node->data_)
	{
		MM->free(node->data_);
	}

	node->data_ = NULL;
	node->size_ = 0;
	return kErrorCode_Ok;
}

s16 MEMNODE_softReset(MemoryNode* node) {
	if (NULL == node) {
		return kErrorCode_Node_NULLNode;
	}

  node->data_ = NULL;
  node->size_ = 0;
  return kErrorCode_Ok;
}

s16 MEMNODE_free(MemoryNode *node)		
{
	if (NULL == node)
	{
		return kErrorCode_Ok;
	}

	if (NULL != node->data_)
	{
		MM->free(node->data_);
	}
	node->size_ = 0;

	MM->free(node);
	return kErrorCode_Ok;
}

s16 MEMNODE_softFree(MemoryNode *node)	
{
	if (NULL == node)
	{
		return kErrorCode_Ok;
	}
	node->data_ = NULL;
	node->size_ = 0;
	MM->free(node);

	return kErrorCode_Ok;
}

s16 MEMNODE_memSet(MemoryNode *node, u8 value)
{
	if (NULL == node)
	{
		return kErrorCode_Node_NULLNode;
	}
	if (NULL == node->data_)
	{
		return kErrorCode_Node_NULLData;
	}
	memset(node->data_, value, node->size_);

	return kErrorCode_Ok;
}

s16 MEMNODE_memCopy(MemoryNode *node, void *src, u16 bytes)
{
	if (NULL == node)
	{
		return kErrorCode_Node_NULLNode;
	}
	if (NULL == src)
	{
		return kErrorCode_Parameters_NULL;
	}
	if (0 == bytes)
	{
		return kErrorCode_Parameters_Zero;
	}

	void *aux = MM->malloc(bytes);
	if (NULL == aux)
	{
		return kErrorCode_MemoryAllocation;
	}
	memcpy(aux, src, bytes);
	if (NULL != node->data_)
	{
		MM->free(node->data_);
		node->data_ = NULL;
		node->size_ = 0;
	}

	node->data_ = aux;
	node->size_ = bytes;

	return kErrorCode_Ok;
}

s16 MEMNODE_memConcat(MemoryNode *node, void *src, u16 bytes)
{
	if (NULL == node)
	{
		return kErrorCode_Node_NULLNode;
	}
	if (NULL == src)
	{
		return kErrorCode_Parameters_NULL;
	}
	if (NULL == node->data_)
	{
		return kErrorCode_Node_NULLData;
	}
	if (NULL == src && 0 == bytes)
	{
		return kErrorCode_Ok;
	}
	if (NULL == src || 0 == bytes)
	{
		 return kErrorCode_Ok; 
	}

	u16 new_size = node->size_ + bytes;
	void* new_data = MM->malloc(new_size);
	if (NULL == new_data)
	{
		kErrorCode_MemoryAllocation;
	}
	memcpy(new_data, node->data_, node->size_);
	memcpy(((u8*)new_data + node->size_), src, bytes);
	MM->free(node->data_);

	node->data_ = new_data;
	node->size_ = new_size;

	return kErrorCode_Ok;
}

s16 MEMNODE_memMask(MemoryNode *node, u8 mask)
{
	if (NULL == node)
	{
		return kErrorCode_Node_NULLNode;
	}
	if (NULL == node->data_)
	{
		return kErrorCode_Node_NULLData;
	}
	for (u16 i = 0; i < node->size_; i++)
	{
		*((u8*)node->data_ + i) &= mask;
	}

	return kErrorCode_Ok;
}

void MEMNODE_print(MemoryNode *node)
{
  if (NULL != node)
  {
    printf("[Node Info] Address : %p\n", node);
    printf("[Node Info] Size : %d\n", node->size_);
    printf("[Node Info] Data address: %p\n", node->data_);
    //printf("[Node Info] Data content : %s\n", node->data_);
  }
}


s16 MEMNODE_setNext(MemoryNode *node, MemoryNode *node2)
{
	if (NULL == node)
	{
		return kErrorCode_Node_NULLNode;
	}

	node->next_ = node2;
	return kErrorCode_Ok;
}

MemoryNode * MEMNODE_getNext(MemoryNode *node)
{
	if (NULL == node)
	{
		return NULL;
	}
	if (NULL == node->next_)
	{
		return NULL;
	}
	return node->next_;
}

s16 MEMNODE_setPrev(MemoryNode *node, MemoryNode *node2)
{
	if (NULL == node)
	{
		return kErrorCode_Node_NULLNode;
	}

	node->prev_ = node2;
	return kErrorCode_Ok;
}

MemoryNode * MEMNODE_getPrev(MemoryNode * node)
{
	if (NULL == node)
	{
		return NULL;
	}
	if (NULL == node->prev_)
	{
		return NULL;
	}
	return node->prev_;
}