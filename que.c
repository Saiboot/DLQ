#include "que.h"
#include <stdio.h>

typedef struct {
  char *comp;
  char *error;
} wet;

/*  Double linked Queue
 *  - push new elements to the back.
 *  - pop existing elements from the front.
 */

LQue *LQue_init(size_t data_sz, void (*flush_func)(void *data)) {
  LQue *q = malloc(sizeof(LQue));
  q->_pBack = 0x0;
  q->_pFront = 0x0;
  q->flush = flush_func;
  q->size = 0;
  q->data_sz = data_sz;
  return q;
}

void LQue_flush(LQue *q) {
  while(q->size > 0)
    LQue_popFront(q);
  free(q);
}

void LQue_pushBack(LQue *q, void *data) {
 
  Link *pB = 0x0;

  /* Handle populated queue */
  if (q->size >= 1) 
    pB = q->_pBack;             // Save: _pBack 

  /* Create next link */
  Link *newLink = malloc(sizeof(Link));   // Allocate new link.
  newLink->data = malloc(q->data_sz);     // Allocate memory for data inside the link.
  memcpy(newLink->data, data, q->data_sz);    // Insert data into the new link.
  newLink->_pBackward = 0x0;                  // _pBackward-> nullptr
  newLink->_pForward = 0x0;                   // _pForward-> nullptr

  if (pB) newLink->_pForward = pB;    // _pForward-> Previous pBack

  /* Push new link */
  q->_pBack = newLink;                // Place it at the back of the queue.                           
  if(pB) pB->_pBackward = newLink;    // ...

  /* Handle empty queue */
  if (q->size == 0) 
    q->_pFront = newLink;   // Add the front link.

  q->size++;
}

void *LQue_popFront(LQue *q) {

  if(!q->size)
    return 0x0;
  //assert(q->size > 0);  // Make sure the queue isn't empty!

  wet *d = q->_pFront->data;
  printf("sda>> %s\n", d->error);

  /* Allocate new memory & store the data to pop fron queue */
  size_t data_sz = sizeof(q->_pFront->data);
  void *front_data = malloc(data_sz);
  memcpy(front_data, d, data_sz);

  wet *w = front_data;

  printf("size: %d\n", data_sz);
  printf("data>>%s\n", w->error);

  q->flush(q->_pFront->data);  // flush the generic data type.

  if (q->size == 1) {

    free(q->_pFront);       // free the last element.

    /* Clean up the que */
    q->_pBack = 0x0;
    q->_pFront = 0x0;
    q->size = 0;
    return front_data;
  }

  Link *pN = q->_pFront->_pBackward;
  pN->_pForward = 0x0;

  free(q->_pFront);

  q->_pFront = pN;
  q->size--;
  return front_data;
}
