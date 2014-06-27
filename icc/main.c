#include <icc/icc.h>

#include <stdlib.h>

int main(int argc, char** argv) {

	Icc icc;

	iccOpenFile(&icc, "WebCoatedSWOP2006Grade5.icc");
	iccReadHeader(&icc);
	iccPrintHeader(&icc);
	iccReadTable(&icc);
	iccPrintTable(&icc);
	iccCloseFile(&icc);

#ifdef _WIN32
	system("pause");
#endif

	return 0;
}