// adt_list.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//
#ifndef __ADT_LIST_H__
#define __ADT_LIST_H__

#include "adt_memory_node.h"

typedef struct adt_list_s
{
	u16 length_;/**< number of active node*/
	u16 capacity_;/**< number of total capacity*/
	MemoryNode *first_;/**< pointer to  first node*/
	MemoryNode *last_;/**< pointer to last node */
	struct list_ops_s *ops_;/**< pointer to struct list to use the functions */
} List;

struct list_ops_s
{
	/** @brief Destroys the list and its data
   *
   * @param *list pointer to the list
   *
   * @return kErrorCode_LIST_NULL When list is NULL
   * @return kErrorCode_Ok When function has done his job
   */
	s16(*destroy) (List *list);

	/** @brief Resets list's data.
  *
  * @param *list pointer to the list.
  *
  * @return kErrorCode_LIST_NULL When list is NULL.
  * @return kErrorCode_LIST_FIRST_NULL When list first is NULL.
  * @return kErrorCode_LIST_LAST_NULL When list last is NULL.
  * @return kErrorCode_Ok When function has done his job.
  */
	s16(*reset) (List *list);
	
	/** @brief Resizes the capacity of the list.
    *
    *  @param *list Pointer to the list.
    *  @param new_size Pew size for the list.
    *
	* @return kErrorCode_Ok When function has done his job.
	* @return kErrorCode_LIST_NULL When list is NULL.
	* @return kErrorCode_LIST_CAPACITY_0 When list capacity = 0.
	* @return kErrorCode_LIST_FIRST_NULL When list first is NULL.
   */
	s16(*resize)(List *list, u16 new_size);
	
	/** @brief Returns the maximum number of elemets to store.
	*
	*  @param *list pointer to the list.
	*
	*  @return capacity of list.
	*  @return 0 When list is NULL.
	*/
	u16(*capacity)(List *list);

	/** @brief Returns the maximum number of elemets to store.
	*
	*  @param *list pointer to the list.
	*
	*  @return lenght of list.
	*  @return 0 When list is NULL.
	*/
	u16(*length)(List *list);

	/** @brief Returns if the list is empty.
	*
	*  @param *list Pointer to the list.
	*
	*  @return True When list is empty.
	*  @return False When list is not empty or NULL.
	*/
	bool(*isEmpty) (List *list);

	/** @brief returns a reference to the first element of the list.
	*
	*  @param *list pointer to the list.
	*
	*  @return True When list is full.
	*  @return False When list is capacity 0, not full.
	*/
	bool(*isFull) (List *list);

	/** @brief Inserts an element in the first position of the list.
   *
   * @param *list Pointer to the list.
   * @param *void data Pointer to the data.
   * @param bytes Bytes to insert.
   *
   * @return kErrorCode_LIST_NULL When list is NULL.
   * @return kErrorCode_LIST_DATA_NULL When data is NULL.
   * @return kErrorCode_LIST_BYTES_0 When bytes = 0.
   * @return kErrorCode_LIST_FULL When list is full.
   * @return kErrorCode_Memory When cant reserve memory.
   * @return kErrorCode_LIST_FIRST_NULL When list first is NULL.
   * @return kErrorCode_LIST_LAST_NULL When list last is NULL.
   * @return kErrorCode_Ok When function has done his job.
   */
	s16(*insertFirst) (List *list, void *data, u16 bytes);

	/** @brief Inserts an element in the last position of the list
	*
	* @param *list Pointer to the list.
	* @param *void data Pointer to the data.
	* @param bytes Bytes to insert.
	*
	* @return kErrorCode_LIST_NULL When list is NULL.
   * @return kErrorCode_LIST_DATA_NULL When data is NULL.
   * @return kErrorCode_LIST_BYTES_0 When bytes = 0.
   * @return kErrorCode_LIST_FULL When list is full.
   * @return kErrorCode_Memory When cant reserve memory.
   * @return list inserted first.
   * @return kErrorCode_LIST_LAST_NULL When list last is NULL.
   * @return kErrorCode_Ok When function has done his job.
	*/
	s16(*insertLast) (List *list, void *data, u16 bytes);

	/** @brief Inserts an element in the given position of list.
   *
   * @param *list pointer to the list.
   * @param *void data Pointer to the data.
   * @param bytes Bytes to insert.
   * @param position The position to insert.
   *
   * @return kErrorCode_LIST_NULL When list is NULL.
   * @return kErrorCode_LIST_DATA_NULL When data is NULL.
   * @return kErrorCode_LIST_BYTES_0 When bytes = 0.
   * @return kErrorCode_LIST_FULL When list has capacity 0.
   * @return kErrorCode_LIST_OUT_RANGE When position is out of range.
   * @return list inserted first.
   * @return list inserted last.
   * @return kErrorCode_LIST_FIRST_NULL When list first is NULL.
   * @return kErrorCode_Ok When function has done his job.
   */
	s16(*insertAt) (List *list, void *data, u16 bytes, u16 position);

	/** @brief returns a reference to the first element of the list.
	*
	*  @param *list pointer to the list.
	*
	*  @return NULL When list is not first, NULL, empty .
	*  @return reference of first element of list.
	*/
	void* (*first)(List *list);

	/** @brief returns a reference to the last element of the list.
	*
	*  @param *list pointer to the list.
	*
	*  @return NULL When list is not last, NULL, empty .
	*  @return reference of last element of list.
	*/
	void* (*last)(List *list);

	/** @brief Returns a reference to the element at a given position.
	*
	*  @param *list Pointer to the list.
	*
	*  @return NULL When list is NULL, empty or out of size.
	*  @return reference of position to the element at a given position.
	*/
	void* (*at)(List *list, u16 position);

	/** @brief Extracts the first element of the list
   *
   * @param *list pointer to the list.
   *
   * @return NULL When list is NULL, empty, first is NULL.
   * @return New list with the extract done.
   */
	void*(*extractFirst)(List *list);

	/** @brief Extracts the first element of the list
   *
   * @param *list pointer to the list.
   *
   * @return NULL When list is NULL, empty, first is NULL.
   * @return New list with the extract done.
   */
	void*(*extractLast) (List *list);

	/** @brief Extracts the first element of the list
   *
   * @param *list pointer to the list.
   * @param position position list to extract.
   *
   * @return NULL When list is NULL, empty, out of range, first is NULL, last is NULL.
   * @return New list When the extract is done.
   */
	void*(*extractAt) (List *list, u16 position);

	/** @brief Concatenates two list.
   *
   * @param *list pointer to the list.
   * @param *list pointer to vector_src.
   *
   * @return kErrorCode_LIST_NULL When list is NULL.
   * @return kErrorCode_LIST_SRC_NULL When list_src is NULL.
   * @return kErrorCode_LIST_FIRST_NULL When list first is NULL.
   * @return kErrorCode_Memory When cant reserve memory.
   * @return kErrorCode_Ok When function is done.
   */
	s16(*concat) (List *list, List *list_src);

	/** @brief Prints the features and content of the list
   *
   * @param *list pointer to the list.
   * @param *void position list to extract.
   */
	void(*print)(List *list); 
};

/** @brief Creates a new list
   *
   * @param *capacity The capacity of list.
   *
   * @return Null When capacity = 0, new list is Null, storage new list is NULL.
   * @return list The new created list.
   */
List* LIST_create(u16 capacity); // Creates a new list
#endif //__ADT_list_H__


















