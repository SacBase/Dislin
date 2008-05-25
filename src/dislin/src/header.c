#include <malloc.h>
#include "header.h"

struct DISLIN_HEADER {
  char *pre;
  char *post;
  int pos;
  int dir;
};

DislinHeader *createHeader( char *pre, char *post, int pos, int dir)
{
  DislinHeader *ptr;

  ptr = (DislinHeader *)malloc( sizeof( DislinHeader));

  ptr->pre = pre;
  ptr->post = post;
  ptr->pos = pos;
  ptr->dir = dir;

  return( ptr);
}

DislinHeader *copyHeader( DislinHeader *ptr)
{
  return( createHeader( ptr->pre, ptr->post, ptr->pos, ptr->dir));
}

void freeHeader( DislinHeader *ptr)
{
  free( ptr);
}

