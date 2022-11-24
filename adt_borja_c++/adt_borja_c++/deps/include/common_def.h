// common_def.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

#ifndef __COMMON_DEF_H__
#define __COMMON_DEF_H__

#define VERBOSE_

typedef enum
{
	kErrorCode_Ok = 0,
	kErrorCode_Memory = -1,
	kErrorCode_MemoryAllocation = -2,
	kErrorCode_File = -3,
	kErrorCode_Node = -4,
	kErrorCode_Node_NULLNode = -5,
	kErrorCode_Node_NULLData = -6,
	kErrorCode_Parameters = -7,
	kErrorCode_Parameters_NULL = -8,
	kErrorCode_Parameters_Zero = -9,

	kErrorCode_VectorCapacity_Zero = -10,
	kErrorCode_Vector_NULL = -11,
	kErrorCode_VectorStorage_NULL = -12,
	kErrorCode_VectorData_NULL = -13,
	kErrorCode_VectorSrc_NULL = -14,
	kErrorCode_Vector_OUT_RANGE = -15,

	kErrorCode_LIST_NULL = -16,
	kErrorCode_LIST_CAPACITY_0 = -17,
	kErrorCode_LIST_DATA_NULL = -18,
	kErrorCode_LIST_BYTES_0 = -19,
	kErrorCode_LIST_SRC_NULL = -20,
	kErrorCode_LIST_FULL = -21,
	kErrorCode_LIST_EMPTY = -22,
	kErrorCode_LIST_OUT_RANGE = -23,
	kErrorCode_LIST_FIRST_NULL = -24,
	kErrorCode_LIST_LAST_NULL = -25,
	kErrorCode_LIST_CALLBACK = -26,

	kErrorCode_DLLIST_NULL = -27,
	kErrorCode_DLLIST_CAPACITY_0 = -28,
	kErrorCode_DLLIST_DATA_NULL = -29,
	kErrorCode_DLLIST_BYTES_0 = -30,
	kErrorCode_DLLIST_SRC_NULL = -31,
	kErrorCode_DLLIST_FULL = -32,
	kErrorCode_DLLIST_EMPTY = -33,
	kErrorCode_DLLIST_OUT_RANGE = -34,
	kErrorCode_DLLIST_CALLBACK = -35,
	kErrorCode_DLLIST_FIRST_NULL = -36,
	kErrorCode_DLLIST_LAST_NULL = -37,

	kErrorCode_QUEUE_NULL = -38,
	kErrorCode_QUEUE_STORAGE_NULL = -39,
	kErrorCode_QUEUE__DATA_NULL = -40,

	kErrorCode_STACK_NULL = -41,
	kErrorCode_STACK_STORAGE_NULL = -42,
	kErrorCode_STACK_SRC_NULL = -43,
	kErrorCode_STACK__DATA_NULL = -44,
	kErrorCode_STACK_FULL = -45,
	kErrorCode_STACK_BYTES_0 = -46
} ErrorCode;

static const char* kErrorMsg[47] = {
	"Ok",
	"Memory",
	"MemoryAllocation",
	"File",
	"Node",
	"NULLNode",
	"NULLData",
	"Parameters",
	"Parameters_NULL",
	"Parameters_Zero",

	"VectorCapacity_Zero",
	"Vector_NULL",
	"Vector_Storage_NULL",
	"Vector_Data_NULL",
	"VectorSrc_NULL",
	"Vector_OUT_RANGE",

	"LIST_NULL",
	"LIST_CAPACITY_0",
	"LIST_DATA_NULL",
	"LIST_BYTES_0",
	"LIST_SRC_NULL",
	"LIST_FULL",
	"LIST_EMPTY",
	"LIST_OUT_RANGE",
	"LIST_FIRST_NULL",
	"LIST_LAST_NULL",
	"LIST_CALLBACK",

	"DLLIST_NULL",
	"DLLIST_CAPACITY_0",
	"DLLIST_DATA_NULL",
	"DLLIST_BYTES_0",
	"DLLIST_SRC_NULL",
	"DLLIST_FULL",
	"DLLIST_EMPTY",
	"DLLIST_OUT_RANGE",
	"DLLIST_CALLBACK",
	"DLLIST_FIRST_NULL",
	"DLLIST_LAST_NULL",

	"QUEUE_NULL",
	"QUEUE_STORAGE_NULL",
	"QUEUE__DATA_NULL",

	"STACK_NULL",
	"STACK_STORAGE_NULL",
	"STACK_SRC_NULL",
	"STACK__DATA_NULL",
	"STACK_FULL"
	"STACK_BYTES_0"
};

#endif // __COMMON_DEF_H__
