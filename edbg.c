#include "edbg.h"

#include <stdlib.h>

void flush_data_func(void *data)
{
  Err_t *o = (Err_t *)(data);
  free(o->comp);
  free(o->error);
  free(o);
}

LQue *init_emsg()
{
  return LQue_init(sizeof(Err_t), &flush_data_func);
}

void cast_emsg(const int ETYPE, const char *msg)
{
  /* allocate error-type */
  Err_t *data = malloc(sizeof(Err_t));

  /* populate error-type with data */
  char *component = ALL_E_TYPES[ETYPE];     // -component
  size_t comp_len = strlen(component);
  data->comp = malloc(comp_len + 1);
  strncpy(data->comp, component, comp_len);
  data->comp[comp_len] = '\0';

  size_t msg_len = strlen(msg);            // -msg
  data->error = malloc(msg_len + 1);
  memset(data->error, 0, msg_len);
  strncpy(data->error, msg, msg_len);
  data->error[msg_len] = '\0';

  /* push the error-type onto the queue */
  LQue_pushBack(g_ErrCL, data);
}

int got_error()
{
  if(g_ErrCL->size > 0)
    return 1;
  return 0;
}

void free_emsg(Err_t *e)
{
  free(e->error);
  memset(e->comp, 0, COMP_LEN);
  free(e);
}

void print_emsg()
{
  if(!got_error())
    return; 

  printf("got a message!\n");

  Err_t *e = LQue_popFront(g_ErrCL);
  printf("%s::[!] %s\n", e->comp, e->error);

  free_emsg(e);
}

void flush_ErrCL()
{
  LQue_flush(g_ErrCL);
}