#ifndef DISLIN_PAGE_H
#define DISLIN_PAGE_H

#include "header.h"

typedef struct DISLIN_PAGE DislinPage;


extern DislinPage *allocPage( );
extern DislinPage *copyPage( DislinPage *ptr);
extern void freePage( DislinPage *ptr);

extern int sizeNormed( DislinPage *ptr);
extern char * getNorm( DislinPage *ptr);
extern int getSize( int * h, DislinPage *ptr);
extern int hasBorder( DislinPage *ptr);
extern int hasHeader( DislinPage *ptr);
extern DislinHeader *getHeader( DislinPage *ptr);

extern void setNorm( DislinPage *ptr, char * norm);
extern void setSize( DislinPage *ptr, int w, int h);
extern void setBorder( DislinPage *ptr);
extern void unsetBorder( DislinPage *ptr);
extern void setHeader( DislinPage *ptr, DislinHeader *h);

#endif /* DISLIN_PAGE_H */
