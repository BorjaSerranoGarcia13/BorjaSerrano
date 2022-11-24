// adt_memory_node.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

#ifndef __ADT_MEMORY_NODE_H__
#define __ADT_MEMORY_NODE_H__

#include "ABGS_MemoryManager/abgs_platform_types.h"


// Memory Node type
typedef struct memory_node_s {
	void *data_; /**< data of node*/
	u16 size_;	/**< size of node*/
	void* next_;	/**< pointer to next node*/
	void* prev_;	/**< pointer to prev node*/
	struct memory_node_ops_s *ops_; /**< *pointer to struct memory node to use the functions */
} MemoryNode;

// Memory Node's API Declarations
struct memory_node_ops_s {
  void*(*data) (MemoryNode *node);
  s16(*setData) (MemoryNode *node, void *src, u16 bytes);
  u16(*size) (MemoryNode *node);

  /** 
  * @brief reset content of memory node
  * 
  * @param *node pointer to the node.
  *
  * @return kErrorCode_Node_NULLNode When node is NULL.
  * @return kErrorCode_Ok When function has done his job.
  */
  s16(*reset) (MemoryNode *node);		

  /** 
   * @brief reset content of memory node without freeing the data
   * 
   * @param *node pointer to the node.
   *
   * @return kErrorCode_Ok When function has done his job.
   */
  s16(*softReset) (MemoryNode *node);		

  /** 
   * @brief free memory, both data and node
   * 
   * @param *node pointer to the node.
   * 
   * @return kErrorCode_Ok When function has done his job.
   */  
  s16(*free) (MemoryNode *node);		

  /** 
   * @brief free only the node
   * 
   * @param *node pointer to the node.
   * 
   * @return kErrorCode_Ok When function has done his job.
   */    
  s16(*softFree) (MemoryNode *node);	

  /** 
   * @brief sets the data of a node
   * 
   * @param *node pointer to the node.
   * @param value The value to set.
   * 
   * @return kErrorCode_Node_NULLNode When node is NULL.
   * @return kErrorCode_Node_NULLData When node data is NULL.
   * @return kErrorCode_Ok When function has done his job.
   */    
  s16(*memSet) (MemoryNode *node, u8 value);

  /** 
   * @brief copys the data from a src
   * 
   * @param *node pointer to the node.
   * @param *void src pointer to Source to copy from.
   * @param bytes Size of the data.
   * 
   * @return kErrorCode_Node_NULLNode When node is NULL.
   * @return kErrorCode_Parameters_NULL When node src is NULL.
   * @return kErrorCode_Parameters_Zero When node src is 0.
   * @return kErrorCode_MemoryAllocation When cant reserve memory.
   * @return kErrorCode_Ok When function has done his job.
   */    
  s16(*memCopy) (MemoryNode *node, void *src, u16 bytes);

  /** 
   * @brief concats the data from a src
   * 
   * @param *node pointer to the node.
   * @param *void src pointer to the source to concat from.
   * @param bytes Size of the data.
   * 
   * @return kErrorCode_Node_NULLNode When node is NULL.
   * @return kErrorCode_Node_NULLData When node data is NULL.
   * @return kErrorCode_Parameters_NULL When node src is NULL.
   * @return kErrorCode_MemoryAllocation When cant reserve memory.
   * @return kErrorCode_Ok When function has done his job.
   */      
  s16(*memConcat) (MemoryNode *node, void *src, u16 bytes);

  /** 
   * @brief masks a node
   * 
   * @param *node pointer to the node.
   * @param mask The mask for the node.
   * 
   * @return kErrorCode_Node_NULLNode When node is NULL.
   * @return kErrorCode_Node_NULLData When node data is NULL.
   * @return kErrorCode_Ok When function has done his job.
   */      
  s16(*memMask) (MemoryNode *node, u8 mask);

  /** 
   * @brief Prints node information, such as the data the memory direction of the node (and the data), and the size
   * 
   * @param *node pointer to the node.
   * 
   */ 
  void(*print) (MemoryNode *node);

  /** 
   * @brief sets the data of a next node
   * 
   * @param *node pointer to the node.
   * @param value The value to set.
   *
   * @return kErrorCode_Node_NULLNode When node is NULL.
   * @return kErrorCode_Ok When function has done his job.
   */
  s16(*setNext)(MemoryNode *node, MemoryNode *node2);

  /**
   * @brief gets the data of a next node
   *
   * @param *node pointer to the node.
   * @param value The value to set.
   *
   * @return NULL When node is NULL, node next is NULL.
   * @return node next.
   */
  MemoryNode* (*getNext)(MemoryNode *node);

  /**
   * @brief sets the data of a prev node
   *
   * @param *node pointer to the node.
   * @param value The value to set.
   *
   * @return kErrorCode_Node_NULLNode When node is NULL.
   * @return kErrorCode_Ok When function has done his job.
   */
  s16(*setPrev)(MemoryNode *node, MemoryNode *node2);

  /**
   * @brief gets the data of a prev node
   *
   * @param *node pointer to the node.
   * @param value The value to set.
   *
   * @return NULL When node is NULL, node prev is NULL.
   * @return node prev.
   */
  MemoryNode* (*getPrev)(MemoryNode *node);
};

/** @brief Creates a new memory node
   *
   * @return Null When node is NULL.
   * @return node created.
   */
MemoryNode* MEMNODE_create(); // Creates a new memory node

/** @brief Creates a new memory node from ref
   *
   * @param *node pointer to the node.
   *
   * @return kErrorCode_Node_NULLNode When node is NULL.
   * @return kErrorCode_Memory When reserve memory fails.
   * @return kErrorCode_Ok When function has done his job.
   */
s16 MEMNODE_createFromRef(MemoryNode **node); 

/** @brief Creates a memory node without memory allocation
   *
   * @param *node pointer to the node.
   *
   * @@return kErrorCode_Node_NULLNode When node is NULL.
   * @return kErrorCode_Ok When function has done his job.
   */
s16 MEMNODE_createLite(MemoryNode *node); 

#endif // __ADT_MEMORY_NODE_H__
