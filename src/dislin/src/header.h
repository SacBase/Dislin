#ifndef DISLIN_HEADER_H
#define DISLIN_HEADER_H

typedef struct DISLIN_HEADER DislinHeader;

extern DislinHeader *createHeader( char *pre, char *post, int pos, int dir);

extern DislinHeader *copyHeader( DislinHeader *ptr);
extern void freeHeader( DislinHeader *ptr);

#endif /* DISLIN_HEADER_H */

