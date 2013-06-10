#ifndef __TTYREC_IO_H__
#define __TTYREC_IO_H__

#include "ttyrec.h"

int     read_header     (FILE *fp, Header *h);
int     write_header    (FILE *fp, Header *h);
FILE*   efopen          (const char *path, const char *mode);
int     edup            (int oldfd);
int     edup2           (int oldfd, int newfd);
FILE*   efdopen         (int fd, const char *mode);

/* The ttyrec2 format functions */
int     write_header2   (FILE* fp, Header *h, unsigned char channel);
int     read_header2    (FILE* fp, Header *h, unsigned char* channel);

#endif
