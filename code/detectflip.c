/*
 *    detectflip.c
 *
 *   Tests 180 degree orientation of text using
 *   functions in flipdetect.c.
 */

#include "allheaders.h"
#include <stdio.h>
#include <math.h>


l_int32 detectUpOrDown(PIX *pixs, l_float32*, l_int32, l_int32, l_int32);


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


int main(int argc, char** argv) {
    char *filein;
    l_int32 i, orient;
    l_float32 upconf1, conf1;
    PIX *pixs, *pixt1;

    if (argc != 2) {
        fprintf(stderr, "Input image missing.\n");
        exit(-1);
    }

    filein = argv[1];

    if ((pixt1 = pixRead(filein)) == NULL) {
        fprintf(stderr, "Unable to open image.\n");
        exit(-1);
    }

    //Top level conversion to 1 bpp
    pixs = pixConvertTo1(pixt1, 130);
    pixDestroy(&pixt1);

    //Safer version of up-down tests
    detectUpOrDown(pixs, &conf1, 0, 10, 1);
    pixDestroy(&pixs);
    return 0;
}


l_int32 detectUpOrDown(PIX *pixs, l_float32  *pconf, l_int32 mincount, l_int32 npixels, l_int32 debug) {
    l_int32 countup, countdown, nmax;
    l_float32 nup, ndown;
    PIX *pixt0, *pixt1, *pixt2, *pixt3, *pixm;
    SEL *sel1, *sel2, *sel3, *sel4;

    PROCNAME("pixUpDownDetectGeneral");

    if (!pconf) {
        fprintf(stderr, "&conf not defined.\n");
        exit(-1);
    }
    *pconf = 0.0;
    if (!pixs) {
        fprintf(stderr, "pixs not defined.\n");
        exit(-1);
    }
    if (mincount == 0) {
        mincount = DEFAULT_MIN_UP_DOWN_COUNT;
    }
    if (npixels < 0) {
        npixels = 0;
    }

    sel1 = selCreateFromString(textsel1, 5, 6, NULL);
    sel2 = selCreateFromString(textsel2, 5, 6, NULL);
    sel3 = selCreateFromString(textsel3, 5, 6, NULL);
    sel4 = selCreateFromString(textsel4, 5, 6, NULL);

    /* One of many reasonable pre-filtering sequences: (1, 8) and (30, 1).
     * This closes holes in x-height characters and joins them at
     * the x-height.  There is more noise in the descender detection
     * from this, but it works fairly well. */
    pixt0 = pixMorphCompSequence(pixs, "c1.8 + c30.1", 0);

    /* Optionally, make a mask of the word bounding boxes, shortening
     * each of them by a fixed amount at each end. */
    pixm = NULL;
    if (npixels > 0) {
        l_int32  i, nbox, x, y, w, h;
        BOX   *box;
        BOXA  *boxa;
        pixt1 = pixMorphSequence(pixt0, "o10.1", 0);
        boxa = pixConnComp(pixt1, NULL, 8);
        pixm = pixCreateTemplate(pixt1);
        pixDestroy(&pixt1);
        nbox = boxaGetCount(boxa);
        for (i = 0; i < nbox; i++) {
            box = boxaGetBox(boxa, i, L_CLONE);
            boxGetGeometry(box, &x, &y, &w, &h);
            if (w > 2 * npixels) {
                pixRasterop(pixm, x + npixels, y - 6, w - 2 * npixels, h + 13, PIX_SET, NULL, 0, 0);
            }
            boxDestroy(&box);
        }
        boxaDestroy(&boxa);
    }

    /* Find the ascenders and optionally filter with pixm.
     * For an explanation of the procedure used for counting the result
     * of the HMT, see comments at the beginning of this function. */
    pixt1 = pixHMT(NULL, pixt0, sel1);
    pixt2 = pixHMT(NULL, pixt0, sel2);
    pixOr(pixt1, pixt1, pixt2);
    if (pixm) {
        pixAnd(pixt1, pixt1, pixm);
    }
    pixt3 = pixReduceRankBinaryCascade(pixt1, 1, 1, 0, 0);
    pixCountPixels(pixt3, &countup, NULL);
    pixDestroy(&pixt1);
    pixDestroy(&pixt2);
    pixDestroy(&pixt3);

    /* Find the ascenders and optionally filter with pixm. */
    pixt1 = pixHMT(NULL, pixt0, sel3);
    pixt2 = pixHMT(NULL, pixt0, sel4);
    pixOr(pixt1, pixt1, pixt2);
    if (pixm) {
        pixAnd(pixt1, pixt1, pixm);
    }
    pixt3 = pixReduceRankBinaryCascade(pixt1, 1, 1, 0, 0);
    pixCountPixels(pixt3, &countdown, NULL);
    pixDestroy(&pixt1);
    pixDestroy(&pixt2);
    pixDestroy(&pixt3);

    /* Evaluate statistically, generating a confidence that is
     * related to the probability with a gaussian distribution. */
    nup = (l_float32)(countup);
    ndown = (l_float32)(countdown);
    nmax = L_MAX(countup, countdown);
    if (nmax > mincount) {
        *pconf = 2. * ((nup - ndown) / sqrt(nup + ndown));
    }

    if (debug) {
        if (*pconf > DEFAULT_MIN_UP_DOWN_CONF)
            fprintf(stderr, "rightside-up\n");
        if (*pconf < -DEFAULT_MIN_UP_DOWN_CONF)
            fprintf(stderr, "upside-down\n");
    }

    pixDestroy(&pixt0);
    pixDestroy(&pixm);
    selDestroy(&sel1);
    selDestroy(&sel2);
    selDestroy(&sel3);
    selDestroy(&sel4);
    return 0;
}
