// adt_queue.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
// 
#ifndef __ADT_QUEUE_H__
#define __ADT_QUEUE_H__ 1

#include "adt_list.h"

typedef struct adt_queue_s
{
	
	List *storage_;
	struct queue_ops_s *ops_;
} Queue;

struct queue_ops_s
{
	/**
	*	@brief Destroys the queue and its data
	*	@param  queue to do it
	*	@return CodeError
	*/
	s16(*destroy) (Queue *queue);	// Destroys the vector and its data

	/**
	*	@brief Resets queue's data
	*	@param  queue to do it
	*	@return CodeError
	*/
	s16(*reset) (Queue *queue);		// Resets vector's data

	/**
	*	@brief Resizes the capacity of the vector. Some elements can be lost
	*	@param  queue to do it and size
	*	@return CodeError
	*/
	u16(*resize)(Queue *queue, u16 new_size); // Resizes the capacity of the vector. Some elements can be lost

	// State queries
	// State queries
	/**
	*	@brief returns the maximum number of elemets to store
	*	@param  queue to do it
	*	@return capacity
	*/
	u16(*capacity)(Queue *queue);		// returns the maximum number of elemets to store

	/**
	*	@brief current number of elements (<= capacity)
	*	@param  queue to do it
	*	@return length
	*/
	u16(*length)(Queue *queue);			// current number of elements (<= capacity)
	
	/**
	*	@brief returns if empty queue
	*	@param  queue to do it
	*	@return true or false
	*/
	bool(*isEmpty) (Queue *queue);
	
	/**
	*	@brief returns if full queue
	*	@param  queue to do it
	*	@return true or false
	*/
	bool(*isFull) (Queue *queue);

	// Data queries
	/**
	*	@brief returns the front queue
	*	@param  queue to do it
	*	@return true or false
	*/
	void* (*front)(Queue *queue); // Returns a reference to the last element of the vector

	/**
	*	@brief returns the back queue
	*	@param  queue to do it
	*	@return true or false
	*/
	void* (*back)(Queue *queue);

	// Insertion
	/**
	*	@brief insert queue
	*	@param  queue to do it, the data and total bytes
	*	@return ErrorCode
	*/
	s16(*enqueue) (Queue *queue, void *data, u16 bytes); // Inserts an element in the last position of the vector

	// Extraction
	/**
	*	@brief extract queue
	*	@param  queue to do it
	*	@return ErrorCode
	*/
	void*(*dequeue) (Queue *queue); // Extracts the last element of the vector

	// Miscellaneous
	s16(*concat) (Queue *queue, Queue *queue_src); // Concatenates two vectors
	void(*print)(Queue *queue); // Prints the features and content of the queue
};

/**
	*	@brief create queue
	*	@param  capacity of queue
	*	@return ErrorCode
	*/
Queue* QUEUE_create(u16 capacity); // Creates a new queue
#endif //__ADT_QUEUE_H__

