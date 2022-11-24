
// adt_dllist.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//
#ifndef __ADT_DLLIST_H__
#define __ADT_DLLIST_H__ 1

#include "adt_memory_node.h"


typedef struct adt_dllist_s
{
	u16 length_;/**< number of active node*/
	u16 capacity_;/**< number of total capacity*/
	MemoryNode* first_;/**< pointer to  first node*/
	MemoryNode* last_;/**< pointer to  last node*/
	struct dllist_ops_s* ops_;/**< pointer to struct dllist to use the functions */
} DLList;

struct dllist_ops_s
{
	/** @brief Destroys the dllist and its data
   *
   * @param *dllist pointer to the dllist
   *
   * @return kErrorCode_DLLIST_NULL When dllist is NULL
   * @return kErrorCode_Ok When function has done his job
   */
	s16(*destroy) (DLList* dllist);

	/** @brief Resets dllist's data.
  *
  * @param *dllist pointer to the dllist.
  *
  * @return kErrorCode_DLLIST_NULL When dllist is NULL.
  * @return kErrorCode_Ok When function has done his job.
  */
	s16(*reset) (DLList* dllist);

	/** @brief Resizes the capacity of the dllist.
	*
	*  @param *dllist Pointer to the dllist.
	*  @param new_size Pew size for the dllist.
	*
	* @return kErrorCode_Ok When function has done his job.
	* @return kErrorCode_DLLIST_NULL When dllist is NULL.
	* @return kErrorCode_DLLIST_FIRST_NULL When dllist first is NULL.
	* @return kErrorCode_DLLIST_LAST_NULL When dllist last is NULL.
   */
	s16(*resize)(DLList* dllist, u16 new_size);
	
	/** @brief Returns the maximum number of elemets to store.
	*
	*  @param *dllist pointer to the dllist.
	*
	*  @return capacity of dllist.
	*  @return 0 When dllist is NULL.
	*/
	u16(*capacity)(DLList* dllist);
	
	/** @brief Returns the maximum number of elemets to store.
	*
	*  @param *dllist pointer to the dllist.
	*
	*  @return lenght of dllist.
	*  @return 0 When dllist is NULL.
	*/
	u16(*length)(DLList* dllist);

	/** @brief Returns if the dllist is empty.
	*
	*  @param *dllist Pointer to the dllist.
	*
	*  @return True When dllist is empty.
	*  @return False When dllist is not empty or NULL.
	*/
	bool (*isEmpty) (DLList* dllist); 
	
	/** @brief returns a reference to the first element of the list.
	*
	*  @param *list pointer to the list.
	*
	*   @return True When dllist is full.
	*  @return False When dllist is capacity 0, not full.
	*/
	bool (*isFull) (DLList* dllist); 
	
	/** @brief Inserts an element in the first position of the dllist.
   *
   * @param *dllist Pointer to the dllist.
   * @param *void data Pointer to the data.
   * @param bytes Bytes to insert.
   *
   * @return kErrorCode_DLLIST_NULL When dllist is NULL.
   * @return kErrorCode_DLLIST_DATA_NULL When data is NULL.
   * @return kErrorCode_DLLIST_BYTES_0 When bytes = 0.
   * @return kErrorCode_DLLIST_FULL When dllist is full.
   * @return kErrorCode_Memory When cant reserve memory.
   * @return kErrorCode_Ok When function has done his job.
   */
	s16(*insertFirst) (DLList* dllist, void* data, u16 bytes);
	
	/** @brief Inserts an element in the last position of the dllist
	*
	* @param *dllist Pointer to the dllist.
	* @param *void data Pointer to the data.
	* @param bytes Bytes to insert.
	*
	* @return kErrorCode_DLLIST_NULL When dllist is NULL.
   * @return kErrorCode_DLLIST_DATA_NULL When data is NULL.
   * @return kErrorCode_DLLIST_BYTES_0 When bytes = 0.
   * @return kErrorCode_DLLIST_FULL When dllist is full.
   * @return kErrorCode_Memory When cant reserve memory.
   * @return dllist inserted first.
   * @return kErrorCode_DLLIST_LAST_NULL When dllist last is NULL.
   * @return kErrorCode_Ok When function has done his job.
	*/
	s16(*insertLast) (DLList* dllist, void* data, u16 bytes);
	
	/** @brief Inserts an element in the given position of dllist.
   *
   * @param *dllist pointer to the dllist.
   * @param *void data Pointer to the data.
   * @param bytes Bytes to insert.
   * @param position The position to insert.
   *
   * @return kErrorCode_DLLIST_NULL When dllist is NULL.
   * @return kErrorCode_DLLIST_DATA_NULL When data is NULL.
   * @return kErrorCode_DLLIST_BYTES_0 When bytes = 0.
   * @return kErrorCode_DLLIST_FULL When dllist has capacity 0.
   * @return dllist inserted first.
   * @return dllist inserted last.
   * @return kErrorCode_Ok When function has done his job.
   */
	s16(*insertAt) (DLList* dllist, void* data, u16 bytes, u16 position);

	/** @brief returns a reference to the first element of the dllist.
	*
	*  @param *dllist pointer to the dllist.
	*
	*  @return NULL When dllist is not first, NULL, empty .
	*  @return reference of first element of dllist.
	*/
	void* (*first)(DLList* dllist);
	
	/** @brief returns a reference to the last element of the dllist.
	*
	*  @param *dllist pointer to the dllist.
	*
	*  @return NULL When dllist is not last, NULL, empty .
	*  @return reference of last element of dllist.
	*/
	void* (*last)(DLList* dllist);
	
	/** @brief Returns a reference to the element at a given position.
	*
	*  @param *dllist Pointer to the dllist.
	*
	*  @return NULL When dllist is NULL, empty or out of size.
	*  @return reference of position to the element at a given position.
	*/
	void* (*at)(DLList* dllist, u16 position);
	
	/** @brief Extracts the first element of the dllist
   *
   * @param *dllist pointer to the dllist.
   *
   * @return NULL When dllist is NULL, empty, first is NULL, last is NULL.
   * @return New dllist with the extract done.
   */
	void* (*extractFirst)(DLList* dllist);
	
	/** @brief Extracts the first element of the dllist
   *
   * @param *dllist pointer to the dllist.
   *
   * @return NULL When dllist is NULL, empty, first is NULL, last is NULL.
   * @return New dllist with the extract done.
   */
	void* (*extractLast) (DLList* dllist);
	
	/** @brief Extracts the first element of the dllist
   *
   * @param *dllist pointer to the dllist.
   * @param position position dllist to extract.
   *
   * @return NULL When dllist is NULL, empty, out of range, first is NULL, last is NULL.
   * @return New dllist When the extract is done.
   */
	void* (*extractAt) (DLList* dllist, u16 position);

	/** @brief Concatenates two dllist.
   *
   * @param *dllist pointer to the dllist.
   * @param *dllist pointer to vector_src.
   *
   * @return kErrorCode_DLLIST_NULL When dllist is NULL.
   * @return kErrorCode_DLLIST_SRC_NULL When list_src is NULL.
   * @return kErrorCode_DLLIST_FIRST_NULL When dllist first is NULL.
   * @return kErrorCode_Memory When cant reserve memory.
   * @return kErrorCode_Ok When function is done.
   */
	s16(*concat) (DLList* dllist, DLList* dllist_src);
	
	/** @brief Prints the features and content of the dllist
   *
   * @param *dllist pointer to the dllist.
   * @param *void position dllist to extract.
   */
	void(*print)(DLList* dllist);
};

/** @brief Creates a new dllist
   *
   * @param *capacity The capacity of dllist.
   *
   * @return Null When capacity = 0, new dllist is Null, storage new dllist is NULL.
   * @return dllist The new created dllist.
   */
DLList* DLLIST_create(u16 capacity);
#endif //__ADT_DLLIST_H__










