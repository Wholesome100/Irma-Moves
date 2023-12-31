#include <stdio.h>
#include <stdlib.h>
#include "IrmaMoves.h"


void failwhale(void)
{
	printf("fail whale :(\n");
	exit(0);
}

int main(void)
{

    double hard,hours;
	Move irmaMove;

	// Create a map struct for this test case.
	char **finalBoardState = predictIrmaChange("h7 110 100 e5", &irmaMove);

	// Check wind speed/gusts of Irma when it reach to its destination
	if (irmaMove.irma.ws != 94 || irmaMove.irma.wg != 87)
		failwhale();
	printf("Hooray!\n");

	// Destroy the map board returned by predictIrmaChange().
	finalBoardState = destroyMapBoard(finalBoardState);

	return 0;
}
