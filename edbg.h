#ifndef _ERR_DBG_H
#define _ERR_DBG_H

/*  TODO:
 *  - Component error handler
 *    -- Assert(0) --> Assert!   <assert.h>
 *    -- error string collector 
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "que.h"

#define COMP_LEN 10

#define ETYPES 3

#define ETYPE_CPU 0
#define ETYPE_MEM 1
#define ETYPE_IO  2

static char *ALL_E_TYPES[ETYPES] = {
  "[CPU]",
  "[Memory]",
  "[IO]"
};

/*  ErrCL_t :: Error Collection:
 *  - comp: component
 *  - error: msg
 */
typedef struct {
  char *comp;
  char *error;
} Err_t;

LQue *g_ErrCL;


/*  init_emsg:
 *  
 */
LQue *init_emsg();

/*  cast_emsg:
 *  - cast a new error message onto the queue.
 */
void cast_emsg(const int ETYPE, const char *msg);

/*  print_emsg:
 *  - print the error message in the front of the queue.
 */
void print_emsg();

/*  free_emsg:
 *  - deallocate a Err_t structure.
 */
void free_emsg();

/*  flush_ErrCL:
 *  - Flush the whole collection.
 */
void flush_ErrCL();

#endif  //!_ERR_DBG_H