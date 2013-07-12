#ifndef DETECFLIPNEW_H
#define DETECTFLIPNEW_H

#include "allheaders.h"
#include <stdio.h>
#include <math.h>

int isRightsideUp(PIX *pixs, l_float32*, l_int32, l_int32);

/* Sels for pixOrientDetect() */
static const char *textsel1 = "x  oo "
                              "x oOo "
                              "x  o  "
                              "x     "
                              "xxxxxx";

static const char *textsel2 = " oo  x"
                              " oOo x"
                              "  o  x"
                              "     x"
                              "xxxxxx";

static const char *textsel3 = "xxxxxx"
                              "x     "
                              "x  o  "
                              "x oOo "
                              "x  oo ";
                          
static const char *textsel4 = "xxxxxx"
                              "     x"
                              "  o  x"
                              " oOo x"
                              " oo  x";

/* Parameters for determining orientation */
static const l_int32  DEFAULT_MIN_UP_DOWN_COUNT = 70;
static const l_float32  DEFAULT_MIN_UP_DOWN_CONF = 7.0;
#endif
