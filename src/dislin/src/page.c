#include <malloc.h>
#include <string.h>
#include "page.h"

struct DISLIN_PAGE {
  char *norm;
  int width;
  int height;
  int hasBorder;
  DislinHeader * header;
};

#define TRUE 1
#define FALSE 0

static
char * copyStr( char * str)
{
  char *res;

  if( str == NULL) {
    res = (char *)malloc( sizeof( char));
    strcpy( res, "");
  } else {
    res = (char*) malloc( sizeof( char) * (strlen( str) + 1));
    strcpy( res, str);
  }
  return( res);
}

DislinPage *allocPage( )
{
  DislinPage *ptr;

  ptr = (DislinPage *)malloc( sizeof( DislinPage));

  ptr->norm = NULL;
  ptr->width = 0;
  ptr->height = 0;
  ptr->hasBorder = FALSE;
  ptr->header = NULL;

  return( ptr);
}

DislinPage *copyPage( DislinPage *ptr)
{
  DislinPage *res;

  res = allocPage();
  res->norm = copyStr( ptr->norm);
  res->width = ptr->width;
  res->height = ptr->height;
  res->hasBorder = ptr->hasBorder;
  if( ptr->header != NULL) {
    res->header = copyHeader( ptr->header);
  } else {
    res->header = NULL;
  }
}

void freePage( DislinPage *ptr)
{
  if( ptr->norm != NULL) {
    free( ptr->norm);
  }
  if( ptr->header != NULL) {
    freeHeader( ptr->header);
  }
  free( ptr);
}


/**
 * inspecting the data structure:
 */

int sizeNormed( DislinPage *ptr)
{
  return( ptr->norm != NULL);
}

char * getNorm( DislinPage *ptr)
{
  return( copyStr( ptr->norm));
}

int getSize( int * h, DislinPage *ptr)
{
  *h = ptr->height;
  return( ptr->width);
}

int hasBorder( DislinPage *ptr)
{
  return( ptr->hasBorder);
}

int hasHeader( DislinPage *ptr)
{
  return( ptr->header != NULL);
}

DislinHeader *getHeader( DislinPage *ptr)
{
  return( copyHeader( ptr->header));
}


/**
 * modifying the data structure:
 */

void setNorm( DislinPage *ptr, char * norm)
{
  ptr->norm = copyStr( norm);
  ptr->width = 0;
  ptr->height = 0;
}

void setSize( DislinPage *ptr, int w, int h)
{
  ptr->norm = NULL;
  ptr->width = w;
  ptr->height = h;
}

void setBorder( DislinPage *ptr)
{
  ptr->hasBorder = TRUE;
}

void unsetBorder( DislinPage *ptr)
{
  ptr->hasBorder = FALSE;
}

void setHeader( DislinPage *ptr, DislinHeader *h)
{
  ptr->header = copyHeader( h);
}

