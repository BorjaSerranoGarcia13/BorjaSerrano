// adt_vector.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

#ifndef __ADT_VECTOR_H__
#define __ADT_VECTOR_H__

#include "adt_memory_node.h"

typedef struct adt_vector_s {
	u16 head_; /**< head of vector*/
	u16 tail_; /**< tail of vector*/
	u16 capacity_;  /**< number of total capacity*/
	MemoryNode *storage_; /**< pointer to storage*/
	struct vector_ops_s *ops_; /**< *pointer to struct vector node to use the functions */
} Vector;

struct vector_ops_s {
	
  /** @brief Destroys the vector and its data.
   * 
   * @param *vector pointer to the vector.
   * 
   * @return kErrorCode_Vector_NULL When vector is NULL.
   * @return kErrorCode_Ok When function has done his job.
   */  
	s16 (*destroy)(Vector *vector);	

  /** @brief Soft resets vector's data.
   * 
   * @param *vector pointer to the vector.
   * 
   * @return kErrorCode_Vector_NULL When vector is NULL.
   * @return kErrorCode_VectorStorage_NULL When vector->storage is NULL.
   * @return kErrorCode_Ok When function has done his job.
   */  
  s16 (*softReset)(Vector *vector);	

  /** @brief Resets vector's data.
  * 
  * @param *vector pointer to the vector.
  * 
  * @return kErrorCode_Vector_NULL When vector is NULL.
  * @return kErrorCode_VectorStorage_NULL When vector->storage is NULL.
  * @return kErrorCode_Ok When function has done his job.
  */  	
  s16 (*reset)(Vector *vector);	

  /** @brief Resizes the capacity of the vector.
  * 
  *  @param *vector Pointer to the vector.
  *  @param new_size Pew size for the vector.
  * 
  * @return kErrorCode_Ok When function has done his job.
  * @return 0 When function has some element NULL or cant reserve memory.
  */ 	
	s16 (*resize)(Vector *vector, u16 new_size); 

	// State queries
	/** @brief Returns the maximum number of elemets to store.
    *
    *  @param *vector pointer to the vector.
    *
    *  @return capacity of vector.
    *  @return 0 When vector is NULL.
    */
	u16 (*capacity)(Vector *vector);

	/** @brief Returns the maximum number of elemets to store.
    *
    *  @param *vector pointer to the vector.
    *
    *  @return lenght of vector.
    *  @return 0 When vector is NULL.
    */
	u16 (*length)(Vector *vector);			
	
	/** @brief Returns if the vector is empty.
    *
    *  @param *vector Pointer to the vector.
    *
    *  @return True When vector is empty or NULL.
    *  @return False When vector is not empty.
    */
	bool (*isEmpty)(Vector *vector);		
	
	/** @brief returns if the vector is full.
	*
	*  @param *vector pointer to the vector.
	*
	*  @return True When vector is full.
	*  @return False When vector is full or NULL.
	*/
	bool (*isFull)(Vector *vector);			

	// Data queries
	/** @brief returns a reference to the first element of the vector.
	*
	*  @param *vector pointer to the vector.
	*
	*  @return NULL When vector is not first, NULL, empty .
	*  @return reference of first element of vector.
	*/
	void* (*first)(Vector *vector);

	/** @brief returns a reference to the last element of the vector.
	*
	*  @param *vector pointer to the vector.
	*
	*  @return NULL When vector is not last, NULL, empty .
	*  @return reference of last element of vector.
	*/
	void* (*last)(Vector *vector); 
	
	/** @brief Returns a reference to the element at a given position.
	*
	*  @param *vector Pointer to the vector.
	*
	*  @return NULL When vector is NULL, empty or out of size.
	*  @return reference of position to the element at a given position.
	*/
	void* (*at)(Vector *vector, u16 position);

	// Insertion
   /** @brief Inserts an element in the first position of the vector.
   * 
   * @param *vector Pointer to the vector.
   * @param *void data Pointer to the data.
   * @param bytes Bytes to insert.
   * 
   * @return kErrorCode_Vector_NULL When vector is NULL.
   * @return kErrorCode_VectorData_NULL When data is NULL.
   * @return kErrorCode_Parameters_Zero When bytes = 0.
   * @return kErrorCode_VectorCapacity_Zero When vector has capacity 0.
   * @return kErrorCode_Ok When function has done his job.
   */ 
	s16 (*insertFirst)(Vector *vector, void *data, u16 bytes); 

	/** @brief Inserts an element in the last position of the vector
    *
    * @param *vector Pointer to the vector.
    * @param *void data Pointer to the data.
    * @param bytes Bytes to insert.
    *
    * @return kErrorCode_Vector_NULL When vector is NULL.
    * @return kErrorCode_VectorData_NULL When data is NULL.
    * @return kErrorCode_Parameters_Zero When bytes = 0.
    * @return kErrorCode_VectorCapacity_Zero When vector has capacity 0.
    * @return kErrorCode_Ok When function has done his job.
    */
	s16 (*insertLast)(Vector *vector, void *data, u16 bytes); 

   /** @brief Inserts an element in the given position of vector.
   *
   * @param *vector pointer to the vector.
   * @param *void data Pointer to the data.
   * @param bytes Bytes to insert.
   * @param position The position to insert.
   *
   * @return kErrorCode_Vector_NULL When vector is NULL.
   * @return kErrorCode_VectorData_NULL When data is NULL.
   * @return kErrorCode_Parameters_Zero When bytes = 0.
   * @return kErrorCode_VectorCapacity_Zero When vector has capacity 0.
   * @return kErrorCode_Vector_OUT_RANGE When position is out of range.
   * @return kErrorCode_Ok When function has done his job.
   */
	s16 (*insertAt)(Vector *vector, void *data, u16 bytes, u16 position); 

	/** @brief Extracts the first element of the vector
   *
   * @param *vector pointer to the vector.
   *
   * @return NULL When vector is NULL, empty.
   * @return New vector with the extract done.
   */
	void* (*extractFirst)(Vector *vector); 
  /*
	// For debugging:
#if DEBUG
	void* (*extractFirst)(Vector *vector, u16 *size);
#endif // DEBUG
	void* (*extractFirst)(Vector *vector
#if DEBUG
	, u16 *size
#endif // DEBUG
		);

  /** @brief Extracts the last element of the vector
   *
   * @param *vector pointer to the vector.
   *
   * @return NULL When vector is NULL, empty.
   * @return New vector When the extract is done.
   */
	void* (*extractLast)(Vector *vector); 

  /** @brief Extracts the first element of the vector
   *
   * @param *vector pointer to the vector.
   * @param position position vector to extract.
   *
   * @return NULL When vector is NULL, empty, out of range, 
   * @return New vector When the extract is done.
   */
	void* (*extractAt)(Vector *vector, u16 position); 

	// Miscellaneous

	/** @brief Concatenates two vectors.
   *
   * @param *vector pointer to the vector.
   * @param *vector pointer to vector_src.
   *
   * @return kErrorCode_Vector_NULL When vector is NULL.
   * @return kErrorCode_VectorSrc_NULL When vector_src is NULL.
   * @return kErrorCode_Memory When cant reserve memory.
   * @return kErrorCode_Ok When function is done.
   */
	s16 (*concat)(Vector *vector, Vector *vector_src);

	/** @brief Calls to a function from all elements of the vector
   *
   * @param *vector pointer to the vector.
   * @param *void position vector to extract.
   *
   * @return kErrorCode_Vector_NULL When vector is NULL.
   * @return kErrorCode_VectorStorage_NULL When vector storage is NULL.
   * @return kErrorCode_Memory When cant reserve memory.
   * @return kErrorCode_Ok When function is done.
   */
	s16 (*traverse)(Vector *vector, void (*callback)(MemoryNode *)); 

	/** @brief Prints the features and content of the vector
   *
   * @param *vector pointer to the vector.
   * @param *void position vector to extract.
   */
	void (*print)(Vector *vector); 
};

/** @brief Creates a new vector
   *
   * @param *capacity The capacity of vector.
   * 
   * @return Null When capacity = 0, new vector is Null, storage new vector is NULL.
   * @return vector The new created vector.
   */
Vector* VECTOR_create(u16 capacity); // Creates a new vector
#endif //__ADT_VECTOR_H__
