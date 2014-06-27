#include "icc.h"

void IccReaderA2B0(IccP icc, IccTagInfoP info, IccTagNodeP node) {

	uInt32Number number;

	icc->read(icc, &number, sizeof(uInt32Number));

	printf("Number is %d\n", number);
}