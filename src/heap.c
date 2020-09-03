/**
 * @file       heap.c
 * @author     Ondřej Ševčík
 * @date       6/2019
 * @brief      Implementing of functions for heap
 * **********************************************************************
 * @par       COPYRIGHT NOTICE (c) 2019 TBU in Zlin. All rights reserved.
 */

/* Private includes -------------------------------------------------------- */
#include "heap.h"

#include <stdlib.h>
#include <string.h>

bool Heap_Init(tHeap *heap) {
    if(heap == NULL){
        return false;
    }

    heap->array = myMalloc(MAX_ITEMS_START * sizeof(Data_t));
    if(!heap->array)
        return false;

    heap->count = 0;
    heap->maxItems = MAX_ITEMS_START;

    return true;
}

bool Heap_Insert(tHeap *heap, Data_t insertData) {
    if(!heap)
        return false;

    if(heap->count >= heap->maxItems){
        Data_t *ptr = myRealloc(heap->array, heap->maxItems * 2 * sizeof(Data_t));
        if(!ptr)
            return false;

        heap->array = ptr;
        heap->maxItems *= 2;
    }

    heap->array[heap->count] = insertData;
    heap->count++;

    unsigned int current_index = heap->count - 1;

    while(true) {
        unsigned int parent_index = current_index / 2;
        if(current_index == 0)
            break;

        if (Data_Cmp(heap->array + parent_index, heap->array + current_index) > 0)
            Heap_Swap(heap, current_index, parent_index);
        else break;

        current_index = parent_index;
    }

  return true;
}

void Heap_Destruct(tHeap *heap) {
    if(heap != NULL){
        myFree(heap->array);
        heap->array = NULL;
        heap->maxItems = 0;
    }
}

bool Heap_FindMin(tHeap heap, Data_t *value) {
    if(!value)
        return false;
    *value = heap.array[0];
    return true;
}

bool Heap_DeleteMin(tHeap *heap, Data_t *deleteValue) {
    if(!heap)
        return false;

    if(deleteValue)
        *deleteValue = heap->array[0];

    heap->count--;
    heap->array[0] = heap->array[heap->count];

    unsigned int currentIndex = 0;

    while(true){
        unsigned int leftChild = currentIndex * 2 + 1;
        unsigned int rightChild = currentIndex * 2 + 2;
        unsigned int smallestChild = 0;

        if(leftChild < heap->count){
            if(rightChild < heap->count){
                if(Data_Cmp(heap->array + leftChild, heap->array + rightChild) > 0){
                    smallestChild = rightChild;
                } else
                    smallestChild = leftChild;
            }
        } else
            break;
        if(Data_Cmp(heap->array + currentIndex, heap->array + smallestChild) > 0){
            Heap_Swap(heap, currentIndex, smallestChild);
        } else
            break;
    }
    return true;
}
void Heap_Print(tHeap heap) {
    if (!heap.count)
        return;

    for (unsigned i = 0; i < heap.count; i++) {
        printf("Index %d \t", i + 1);
        Data_Print(&heap.array[i]);
    }
}

bool Heap_Empty(tHeap heap) {
    if(!heap.count)
        return true;
    return false;
}

unsigned Heap_Count(tHeap heap) {
    return heap.count;
}

void Heap_Swap(tHeap *heap, unsigned index1, unsigned index2) {
    if(!heap)
        return;
    if(index2 < heap->count && index1 < heap->count){
        Data_t temporaryIndex = heap->array[index1];
        heap->array[index1] = heap->array[index2];
        heap->array[index2] = temporaryIndex;
    }
}
