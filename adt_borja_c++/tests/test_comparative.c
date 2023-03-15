// comparative.c
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//
// File for comparative of ADTs

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ABGS_MemoryManager/abgs_memory_manager.h"
#include "ABGS_MemoryManager/abgs_platform_types.h"
#include "common_def.h"
#include "adt_vector.h"
#include "adt_list.h"
#include "adt_dllist.h"


u32 repetitions = 500;
void *ptr[10000];

void VectorComparative()
{
	LARGE_INTEGER frequency;				// ticks per second
	LARGE_INTEGER  time_start, time_end;    // ticks in interval
	double elapsed_time = 0.0f;
	repetitions = 500;

	Vector *v;
	v = VECTOR_create(repetitions);
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&time_start);
	// execute function to meassure 'repetitions' times
	for (u32 i = 0; i < repetitions; ++i)
	{
		v->ops_->insertFirst(v, ptr[i], 10);
	}
	
	QueryPerformanceCounter(&time_end);
	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;
	
	printf("-- VECTOR COMPARATIVE --\n\n");
	printf("Insert First: %2f\n", elapsed_time);

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&time_start);
	// execute function to meassure 'repetitions' times
	for (u32 i = 0; i < repetitions; ++i)
	{
		v->ops_->insertLast(v, ptr[i], 10);
	}

	QueryPerformanceCounter(&time_end);
	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;


	printf("Insert Last: %2f\n", elapsed_time);
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&time_start);
	// execute function to meassure 'repetitions' times
	for (u32 i = 0; i < repetitions; ++i)
	{
		v->ops_->insertAt(v, 5, ptr[i], 10);
	}

	QueryPerformanceCounter(&time_end);
	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;


	printf("Insert At: %2f\n", elapsed_time);
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&time_start);
	// execute function to meassure 'repetitions' times
	for (u32 i = 0; i < repetitions; ++i)
	{
		ptr[i] = v->ops_->extractFirst(v);
	}

	QueryPerformanceCounter(&time_end);
	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;


	printf("Extract First: %2f\n", elapsed_time);
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&time_start);
	// execute function to meassure 'repetitions' times
	for (u32 i = 0; i < repetitions; ++i)
	{
		ptr[i] = v->ops_->extractLast(v);
	}

	QueryPerformanceCounter(&time_end);
	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;


	printf("Extract Last: %2f\n", elapsed_time);
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&time_start);
	// execute function to meassure 'ietitions' times
	for (u32 i = 0; i < repetitions; ++i)
	{
		ptr[i] = v->ops_->extractAt(v, 5, ptr[i], 10);
	}

	QueryPerformanceCounter(&time_end);
	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;

	printf("Extract At: %2f\n", elapsed_time);

	v->ops_->destroy(v);

	// ----- CONCAT ------
	
	Vector* v1;
	Vector* v2;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&time_start);
	v1 = VECTOR_create(1);
	v2 = VECTOR_create(repetitions);

	v1->ops_->insertFirst(v, ptr[0], 10);

	for (u32 i = 1; i < repetitions ; ++i)
	{	
		v2->ops_->insertFirst(v2, ptr[i], 10);
	}


	// execute function to meassure 'repetitions' times
	v->ops_->concat(v1, v2);

	QueryPerformanceCounter(&time_end);
	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;


	printf("Concat: %2f\n", elapsed_time);
	
	v->ops_->destroy(v1);
	v->ops_->destroy(v2);
	
}

void TESTBASE_generateDataForComparative()
{
	for (u32 i = 0; i < repetitions; i++)
	{
		//ptr[i] = MM->malloc(10);
	}
	//*ptr = MM->malloc(10000);
}

void ListComparative()
{
	LARGE_INTEGER frequency;				// ticks per second
	LARGE_INTEGER  time_start, time_end;    // ticks in interval
	double elapsed_time = 0.0f;
	repetitions = 500;

	List *l;
	l = LIST_create(repetitions);

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&time_start);

	// execute function to meassure 'repetitions' times
	for (u32 i = 0; i < repetitions; ++i)
	{
		l->ops_->insertFirst(l, ptr[i], 10);
	}

	QueryPerformanceCounter(&time_end);
	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;

	printf("\n\n-- LIST COMPARATIVE --\n\n");
	printf("Insert First: %2f\n", elapsed_time);
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&time_start);
	// execute function to meassure 'repetitions' times
	for (u32 i = 0; i < repetitions; ++i)
	{
		l->ops_->insertLast(l, ptr[i], 10);
	}

	QueryPerformanceCounter(&time_end);
	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;


	printf("Insert Last: %2f\n", elapsed_time);
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&time_start);
	
	// execute function to meassure 'repetitions' times
	for (u32 i = 0; i < repetitions; ++i)
	{
		l->ops_->insertAt(l, 5, ptr[i], 10);
	}

	QueryPerformanceCounter(&time_end);
	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;


	printf("Insert At: %2f\n", elapsed_time);
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&time_start);
	// execute function to meassure 'repetitions' times
	for (u32 i = 0; i < repetitions; ++i)
	{
		ptr[i] = l->ops_->extractFirst(l);
	}

	QueryPerformanceCounter(&time_end);
	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;


	printf("Extract First: %2f\n", elapsed_time);
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&time_start);

	// execute function to meassure 'repetitions' times
	for (u32 i = 0; i < repetitions; ++i)
	{
		ptr[i] = l->ops_->extractLast(l);
	}

	QueryPerformanceCounter(&time_end);
	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;


	printf("Extract Last: %2f\n", elapsed_time);
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&time_start);
	// execute function to meassure 'repetitions' times
	for (u32 i = 0; i < repetitions; ++i)
	{
		ptr[i] = l->ops_->extractAt(l, 10);
	}

	QueryPerformanceCounter(&time_end);
	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;


	printf("Extract At: %2f\n", elapsed_time);

	// --- Concat
	List* v1;
	List* v2;
	v1 = LIST_create(1);
	v2 = LIST_create(repetitions);
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&time_start);
	v1->ops_->insertFirst(v1, ptr[0], 1000);
	for (u32 i = 1; i < repetitions ; ++i)
	{
		v2->ops_->insertFirst(v2, ptr[i], 10);
	}

	// execute function to meassure 'repetitions' times
	v1->ops_->concat(v1, v2);

	QueryPerformanceCounter(&time_end);
	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;


	printf("Concat: %2f\n", elapsed_time);
	v1->ops_->destroy(v1);
	v2->ops_->destroy(v2);

	l->ops_->destroy(l);
}


void DLListComparative()
{
	LARGE_INTEGER frequency;				// ticks per second
	LARGE_INTEGER  time_start, time_end;    // ticks in interval
	double elapsed_time = 0.0f;
	repetitions = 500;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&time_start);

	DLList *l;
	l = DLLIST_create(repetitions);

	// execute function to meassure 'repetitions' times
	for (u32 i = 0; i < repetitions; ++i)
	{
		l->ops_->insertFirst(l, ptr[i], 10);
	}

	QueryPerformanceCounter(&time_end);
	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;

	printf("\n\n-- DLLIST COMPARATIVE --\n\n");
	printf("Insert First: %2f\n", elapsed_time);
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&time_start);
	// execute function to meassure 'repetitions' times
	for (u32 i = 0; i < repetitions; ++i)
	{
		l->ops_->insertLast(l, ptr[i], 10);
	}

	QueryPerformanceCounter(&time_end);
	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;


	printf("Insert Last: %2f\n", elapsed_time);
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&time_start);
	// execute function to meassure 'repetitions' times
	for (u32 i = 0; i < repetitions; ++i)
	{
		l->ops_->insertAt(l, 5, ptr[i], 10);
	}

	QueryPerformanceCounter(&time_end);
	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;


	printf("Insert At: %2f\n", elapsed_time);
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&time_start);
	// execute function to meassure 'repetitions' times
	for (u32 i = 0; i < repetitions; ++i)
	{
		ptr[i] = l->ops_->extractFirst(l);
	}

	QueryPerformanceCounter(&time_end);
	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;


	printf("Extract First: %2f\n", elapsed_time);
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&time_start);
	// execute function to meassure 'repetitions' times
	for (u32 i = 0; i < repetitions; ++i)
	{
		ptr[i] = l->ops_->extractLast(l);
	}

	QueryPerformanceCounter(&time_end);
	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;


	printf("Extract Last: %2f\n", elapsed_time);
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&time_start);
	// execute function to meassure 'repetitions' times
	for (u32 i = 0; i < repetitions; ++i)
	{
		ptr[i] = l->ops_->extractAt(l, 2);
	}

	QueryPerformanceCounter(&time_end);
	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;


	printf("Extract At: %2f\n", elapsed_time);
	l->ops_->destroy(l);

	// -----
	DLList* v;
	DLList* v2;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&time_start);

	v = DLLIST_create(1);
	v2 = DLLIST_create(repetitions);
	

	v->ops_->insertFirst(v, ptr[0], 10);
	for (u32 i = 0; i < repetitions; ++i)
	{
		v2->ops_->insertFirst(v2, ptr[i], 10);
	}


	// execute function to meassure 'repetitions' times
	v->ops_->concat(v, v2);

	QueryPerformanceCounter(&time_end);
	elapsed_time = (time_end.QuadPart - time_start.QuadPart) * 1000000.0f / frequency.QuadPart;
	elapsed_time /= repetitions;


	printf("Concat: %2f\n", elapsed_time);
	v->ops_->destroy(v);
	v2->ops_->destroy(v2);
}


int main()
{
	TESTBASE_generateDataForComparative();
	
	VectorComparative();
	ListComparative();
	DLListComparative();

	printf("\n\nVector bytes %d\n", sizeof(struct adt_vector_s));
	printf("\n\List bytes %d\n", sizeof(struct adt_list_s));
	printf("\n\DLlist bytes %d\n", sizeof(struct adt_dllist_s));

	MM->status();
	MM->destroy();
	printf("Press ENTER to continue\n");
	//getchar();
	return 0;
}
