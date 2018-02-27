#ifndef _QUEUE_LINKED_H
#define _QUEUE_LINKED_H

#include <string.h>
#include <stdlib.h>

#include <assert.h>


/* 	Link/Node:
 *	- A Link containing data.
 *	- Linked together with either zero, one or two other Links.
 */
typedef struct Link Link; 
struct Link {
  void *data;
  Link *_pForward;
  Link *_pBackward;
};

/*	LQue:
 *	- a queue linked together with Links containing data.
 *	- queue Access:
 *		- Front Link in queue.
 *		- Back Link in queue.
 *	- size: amount of elements contained within the queue.
 *	- data_sz: the data-type size of the data within the Links connected to the queue.
 *	- flush: function to deallocate data within the Links.
 */
typedef struct LQue LQue;
struct LQue {
  Link *_pFront;
  Link *_pBack;
  int size;
  size_t data_sz;
  void (*flush)(void *data);
};


/*	LQue_init():
 *	- initialize/allocate -a new queue.
 *	- flush_data_func():
 *		- generic data deallocator
 */
LQue *LQue_init(size_t data_sz, void (*flush_func)(void *data));

/*	LQue_flush():
 *	- flush/deallocate -the queue.
 */
void LQue_flush(LQue *q);

/*	LQue_pushBack():
 *	- Push back/insert -a new link in the queue.
 */
void LQue_pushBack(LQue *q, void *data);

/*	LQue_popFront():
 *	- Pop out/remove -the first link in the queue.
 *	- return: data stored in the popped link.
 */
void *LQue_popFront(LQue *q);

/*	LQue_size():
 *	- return: size of the queue.
 */
//inline int LQue_size(LQue *q) { return q->size; }

#endif //!_QUEUE_LINKED_H