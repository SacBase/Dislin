#include <malloc.h>
#include "header.h"
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

DislinPage *createPage()
{
  DislinPage *ptr;

  ptr = (DislinPage *)malloc( sizeof( DislinPage));

  ptr->norm = "da4l";
  ptr->hasBorder = FALSE;
  ptr->header = NULL;

  return( ptr);
}

int hasNorm( DislinPage *ptr)
{
  return( ptr->norm != NULL);
}

char * getNorm( DislinPage *ptr)
{
  return( ptr->norm);
}

int getWidth( DislinPage *ptr)
{
  return( ptr->width);
}

int getHeight( DislinPage *ptr)
{
  return( ptr->height);
}

int getHasBorder( DislinPage *ptr)
{
  return( ptr->hasBorder);
}

int hasHeader( DislinPage *ptr)
{
  return( ptr->header != NULL);
}

DislinHeader *getHeader( DislinPage *ptr)
{
  return( ptr->header);
}


void setNorm( DislinPage *ptr, char * norm)
{
  ptr->norm = norm;
}

void setWidthHeight( DislinPage *ptr, int w, int h)
{
  ptr->width = w;
  ptr->height = h;
}

void setHasBorder( DislinPage *ptr, int b)
{
  ptr->hasBorder = b;
}

void setHeader( DislinPage *ptr, DislinHeader *h)
{
  ptr->header = h;
}

