/* interface file for all the algorithms */

#ifndef MIM_ALGORITHMS_H
#define MIM_ALGORITHMS_H

typedef int ADT;
/****************************************************************************
 * Sorting algorithms
 ****************************************************************************/
void bubbleSort(ADT *indata, int len);
void insertionSort(ADT *indata, int len);
void quickSort(ADT *indata, int len);

#endif //MIM_ALGORITHMS_H
