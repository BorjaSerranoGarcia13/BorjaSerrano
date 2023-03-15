// adt_stack.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//
#ifndef __ADT_STACK_H__
#define __ADT_STACK_H__ 1

#include "adt_vector.h"

typedef struct adt_stack_s
{
	Vector *storage_;
	struct stack_ops_s *ops_;
} Stack;

struct stack_ops_s
{
	/** @brief Destroys the stack and its data.
   *
   * @param *stack pointer to the stack.
   *
   * @return kErrorCode_STACK_NULL When stack is NULL.
   * @return kErrorCode_Ok When function has done his job.
   */
	s16(*destroy) (Stack *stack);

	/** @brief Resets stack's data.
  *
  * @param *stack pointer to the stack.
  *
  * @return kErrorCode_STACK_NULL When stack is NULL.
  * @return kErrorCode_STACK_STORAGE_NULL When stack->storage is NULL.
  * @return kErrorCode_Ok When function has done his job.
  */
	s16(*reset) (Stack *stack);		

	/** @brief Resizes the capacity of the stack.
  *
  *  @param *stack Pointer to the stack.
  *  @param new_size Pew size for the stack.
  *
  * @return 0 When stack is NULL, new size = 0; out range
  * @return stack resized.
  */
	u16(*resize)(Stack *stack, u16 new_size); 

	// State queries
	/** @brief Returns the maximum number of elemets to store.
	*
	*  @param *stack pointer to the stack.
	*
	*  @return capacity of stack.
	*  @return 0 When stack is NULL.
	*/
	u16(*capacity)(Stack *stack);		

	/** @brief Returns the maximum number of elemets to store.
	*
	*  @param *stack pointer to the stack.
	*
	*  @return lenght of stack.
	*  @return 0 When stack is NULL.
	*/
	u16(*length)(Stack *stack);			
	
	/** @brief Returns if the stack is empty.
	*
	*  @param *stack Pointer to the stack.
	*
	*  @return True When stack is empty or NULL.
	*  @return False When stack is not empty.
	*/
	bool(*isEmpty) (Stack *stack);
	
	/** @brief returns if the stack is full.
	*
	*  @param *stack pointer to the stack.
	*
	*  @return True When stack is full.
	*  @return False When stack is full or NULL.
	*/
	bool(*isFull) (Stack *stack);

	// Data queries
	
	// Data queries
	/** @brief returns a reference to the top of stack.
	*
	*  @param *stack pointer to the stack.
	*
	*  @return NULL When stack is NULL, empty .
	*  @return reference of last element of stack.
	*/
	void* (*top)(Stack *stack); 

	// Insertion
	
	/** @brief Inserts an element in the last position of the stack.
   *
   * @param *stack Pointer to the stack.
   * @param *void data Pointer to the data.
   * @param bytes Bytes to insert.
   *
   * @return kErrorCode_STACK_NULL When stack is NULL.
   * @return kErrorCode_STACK__DATA_NULL When data is NULL.
   * @return kErrorCode_STACK_BYTES_0 When bytes = 0.
   * @return kErrorCode_STACK_FULL When stack is full.
   * @return the stack inserted last.
   */
	s16(*push) (Stack *stack, void *data, u16 bytes); 

	// Extraction
	
	/** @brief Extracts the first element of the stack
   *
   * @param *stack pointer to the stack.
   *
   * @return NULL When stack is NULL, empty.
   * @return New stack with the extract done.
   */
	void*(*pop) (Stack *stack); 

	// Miscellaneous
	/** @brief Calls to a function from all elements of the stack
   *
   * @param *stack pointer to the stack.
   * @param *void position stack to extract.
   *
   * @return kErrorCode_STACK_NULL When stack is NULL.
   * @return kErrorCode_STACK_SRC_NULL When stack src is NULL.
   * @return the stack concatenaed
   */
	s16(*concat) (Stack *stack, Stack *stack_src); 

	/** @brief Prints the features and content of the stack
   *
   * @param *stack pointer to the stack.
   * @param *void position stack to extract.
   */
	void(*print)(Stack *stack); 
};

/** @brief Creates a new stack
   *
   * @param *capacity The capacity of stack.
   *
   * @return Null When capacity = 0, new stack is Null, storage new stack is NULL.
   * @return stack The new created stack.
   */
Stack* STACK_create(u16 capacity); // Creates a new stack
#endif //__ADT_STACK_H__

