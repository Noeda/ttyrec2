/*
 * ttyrec2_to_ttyrec.c
 * Copyright (c) 2010 Mikko Juola (mikjuo@gmail.com)
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/file.h>
#include <sys/signal.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "io.h"

#define _(FOO) FOO

int main(int argc, char* argv[])
{
    char* input_file = (char*) 0;
    char* output_file = (char*) 0;

    while(1)
    {
        int ch = getopt(argc, argv, "i:o:");
        if (ch == EOF)
            break;
        switch(ch)
        {
            case 'i':
                if (optarg == NULL)
                {
                    perror("-i option requires an argument");
                    exit(EXIT_FAILURE);
                }
                input_file = strdup(optarg);
            break;
            case 'o':
                if (optarg == NULL)
                {
                    perror("-o option requires an argument");
                    exit(EXIT_FAILURE);
                }
                output_file = strdup(optarg);
            break;
            default:
                fprintf(stderr, _("usage: ttyrec2_to_ttyrec -i inputfile -o outputfile\n"));
                exit(EXIT_FAILURE);
        }
    }

    if (!input_file || !output_file)
    {
        fprintf(stderr, _("must use both -i and -o parameters\n"));
        exit(EXIT_FAILURE);
    }

    FILE* inpf = fopen(input_file, "rb");
    if (!inpf)
    {
        perror(input_file);
        exit(EXIT_FAILURE);
    }
    FILE* outf = fopen(output_file, "wb");
    if (!outf)
    {
        perror(output_file);
        exit(EXIT_FAILURE);
    }

    Header inph;
    unsigned char channel;
    char* buf = (char*) 0;
    int buf_len = 0;
    while (read_header2(inpf, &inph, &channel))
    {
        if (inph.len > buf_len)
        {
            buf = (char*) realloc(buf, inph.len);
            buf_len = inph.len;
        }

        if (!buf)
        {
            fprintf(stderr, _("realloc() failure"));
            exit(EXIT_FAILURE);
        }
        if (fread(buf, inph.len, 1, inpf) == 0)
        {
            if (ferror(inpf))
            {
                perror(input_file);
                exit(EXIT_FAILURE);
            }
            /* Assume end of file */
            fprintf(stderr, _("unexpected end of input file"));
            exit(EXIT_FAILURE);
        }
        if (channel != 0)
            continue;

        if (!write_header(outf, &inph))
        {
            perror(output_file);
            exit(EXIT_FAILURE);
        }
        if (fwrite(buf, inph.len, 1, outf) == 0)
        {
            perror(output_file);
            exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);
    return EXIT_SUCCESS;
}

