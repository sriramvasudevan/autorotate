

/*
 * flipdetect_reg.c
 *
 *   Tests 90 degree orientation of text and whether the text is
 *   mirror reversed.  Compares the rasterop with dwa implementations
 *   for speed.  Shows the typical 'confidence' outputs from the
 *   functions in flipdetect.c.
 */

#include "allheaders.h"
#include <stdio.h>

static void printStarredMessage(const char *msg);

main(int    argc,
     char **argv)
{
char        *filein;
l_int32      i, orient;
l_float32    upconf1, upconf2, leftconf1, leftconf2, conf1, conf2;
PIX         *pixs, *pixt1, *pixt2;
static char  mainName[] = "flipdetect_reg";

    if (argc != 2)
	exit(ERROR_INT(" Syntax: flipdetect_reg filein", mainName, 1));

    filein = argv[1];

    if ((pixt1 = pixRead(filein)) == NULL)
	exit(ERROR_INT("pixt1 not made", mainName, 1));
    pixs = pixConvertTo1(pixt1, 130);
    pixDestroy(&pixt1);

    fprintf(stderr, "\nTest orientation detection\n");
    startTimer();
    pixOrientDetect(pixs, &upconf1, &leftconf1, 0, 0);
    fprintf(stderr, "Time for rop orient test: %7.3f sec\n", stopTimer());

    makeOrientDecision(upconf1, leftconf1, 0, 0, &orient, 1);

    startTimer();
    pixOrientDetectDwa(pixs, &upconf2, &leftconf2, 0, 0);
    fprintf(stderr, "Time for dwa orient test: %7.3f sec\n", stopTimer());

    if (upconf1 == upconf2 && leftconf1 == leftconf2) {
        printStarredMessage("Orient results identical");
        fprintf(stderr, "upconf = %7.3f, leftconf = %7.3f\n",
                upconf1, leftconf1);
    }
    else {
        printStarredMessage("Orient results differ");
        fprintf(stderr, "upconf1 = %7.3f, upconf2 = %7.3f\n", upconf1, upconf2);
        fprintf(stderr, "leftconf1 = %7.3f, leftconf2 = %7.3f\n",
                leftconf1, leftconf2);
    }

    pixt1 = pixCopy(NULL, pixs);
    fprintf(stderr, "\nTest orient detection for 4 orientations\n");
    for (i = 0; i < 4; i++) {
        pixOrientDetectDwa(pixt1, &upconf2, &leftconf2, 0, 0);
        makeOrientDecision(upconf2, leftconf2, 0, 0, &orient, 1);
        if (i == 3) break;
        pixt2 = pixRotate90(pixt1, 1);
        pixDestroy(&pixt1);
        pixt1 = pixt2;
    }
    pixDestroy(&pixt1);

    fprintf(stderr, "\nTest mirror reverse detection\n");
    startTimer();
    pixMirrorDetect(pixs, &conf1, 0, 1);
    fprintf(stderr, "Time for rop mirror flip test: %7.3f sec\n", stopTimer());

    startTimer();
    pixMirrorDetectDwa(pixs, &conf2, 0, 0);
    fprintf(stderr, "Time for dwa mirror flip test: %7.3f sec\n", stopTimer());

    if (conf1 == conf2) {
        printStarredMessage("Mirror results identical");
        fprintf(stderr, "conf = %7.3f\n", conf1);
    }
    else {
        printStarredMessage("Mirror results differ");
        fprintf(stderr, "conf1 = %7.3f, conf2 = %7.3f\n", conf1, conf2);
    }

    fprintf(stderr, "\nSafer version of up-down tests\n");
    pixUpDownDetectGeneral(pixs, &conf1, 0, 10, 1);
    pixUpDownDetectGeneralDwa(pixs, &conf2, 0, 10, 1);
    if (conf1 == conf2)
        fprintf(stderr, "Confidence results are identical\n");
        
    else
        fprintf(stderr, "Confidence results differ\n");

    pixDestroy(&pixs);
    return 0;
}


void
printStarredMessage(const char *msg)
{
    fprintf(stderr, "****************************************************\n");
    fprintf(stderr, "***********   %s   ***********\n", msg);
    fprintf(stderr, "****************************************************\n");
    return;
}

