#ifdef _MSC_VER
#  define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#include "icc.h"

#include <stdlib.h>
#include <string.h>

static uint8_t _iccSignatureBuffer[5];

static IccString iccGetSignatureString(IccString signature) {

	memcpy(_iccSignatureBuffer, signature, 4);

	if (_iccSignatureBuffer[3] == ' ') {
		_iccSignatureBuffer[3] = '\0';
	}
	else {
		_iccSignatureBuffer[4] = '\0';
	}

	return _iccSignatureBuffer;
}

static uInt8Number iccInvertValue8(uInt8Number value) {

	uInt8Number result = 0;

	for (uInt32Number i = 0; i < sizeof(value); i++) {
		((char*)&result)[i] = ((char*)&value)[sizeof(value) - i - 1];
	}

	return result;
}

static uInt16Number iccInvertValue16(uInt16Number value) {

	uInt16Number result = 0;

	for (uInt32Number i = 0; i < sizeof(value); i++) {
		((char*)&result)[i] = ((char*)&value)[sizeof(value) - i - 1];
	}

	return result;
}

static uInt32Number iccInvertValue32(uInt32Number value) {

	uInt32Number result = 0;

	for (uInt32Number i = 0; i < sizeof(value); i++) {
		((char*)&result)[i] = ((char*)&value)[sizeof(value) - i - 1];
	}

	return result;
}

static uInt64Number iccInvertValue64(uInt64Number value) {

	uInt64Number result = 0;

	for (uInt32Number i = 0; i < sizeof(value); i++) {
		((char*)&result)[i] = ((char*)&value)[sizeof(value) - i - 1];
	}

	return result;
}

static void _iccInternalRead(IccP icc, IccVoidP buffer, uInt32Number length) {

	if (icc->file.handle != NULL) {
		fread(buffer, length, 1, icc->file.handle);
	}
}

static void _iccInternalNumber(IccP icc, IccVoidP buffer, uInt32Number length) {

	if (icc->file.handle != NULL) {

		// read number
		fread(buffer, length, 1, icc->file.handle);

		switch (length)
		{
			// invert data with 1/2/4/8 bytes
			case 1: *(uint8_t *)buffer = iccInvertValue8 (*(uint8_t*)buffer); break;
			case 2: *(uint16_t*)buffer = iccInvertValue16(*(uint32_t*)buffer); break;
			case 4: *(uint32_t*)buffer = iccInvertValue32(*(uint32_t*)buffer); break;
			case 8: *(uint64_t*)buffer = iccInvertValue64(*(uint64_t*)buffer); break;
			// ignore others
			default:
				break;
		}
	}
}

static void _iccInternalWrite(IccP icc, IccVoidP buffer, uInt32Number length) {

	if (icc->file.handle != NULL) {
		fwrite(buffer, length, 1, icc->file.handle);
	}
}

static void _iccInternalMove(IccP icc, uInt32Number position) {

	fpos_t filePosition = position;

	if (icc->file.handle != NULL) {
		fsetpos(icc->file.handle, &filePosition);
	}
}

static IccVoidP _iccInternalReadTagData(IccP icc, uInt32Number length, uInt32Number position) {

	IccVoidP buffer;

	if (icc->file.handle == NULL) {
		return NULL;
	}

	buffer = malloc(length);

	fsetpos(icc->file.handle, (fpos_t*) &position);
	fread(buffer, length, 1, icc->file.handle);

	return buffer;
}

void iccOpenFile(IccP icc, IccString file) {

	// open handle and save it's name
	icc->file.handle = fopen(file, "rb");
	icc->file.name = file;

	// set methods for icc object
	icc->read = _iccInternalRead;
	icc->write = _iccInternalWrite;
	icc->move = _iccInternalMove;
	icc->load = _iccInternalReadTagData;
}

void iccCloseFile(IccP icc) {

	// close handle
	fclose(icc->file.handle);

	// reset handle
	icc->file.handle = NULL;
}

void iccReadHeader(IccP icc) {

	// read header from file
	fread(&icc->header, sizeof(IccHeader), 1, icc->file.handle);

	// invert numbers to little-endian
	icc->header.profileSize = iccInvertValue32(icc->header.profileSize);
	icc->header.renderingIntent = iccInvertValue32(icc->header.renderingIntent);

	icc->header.creationTime.year = iccInvertValue16(icc->header.creationTime.year);
	icc->header.creationTime.month = iccInvertValue16(icc->header.creationTime.month);
	icc->header.creationTime.days = iccInvertValue16(icc->header.creationTime.days);
	icc->header.creationTime.hours = iccInvertValue16(icc->header.creationTime.hours);
	icc->header.creationTime.minutes = iccInvertValue16(icc->header.creationTime.minutes);
	icc->header.creationTime.seconds = iccInvertValue16(icc->header.creationTime.seconds);

	icc->header.xyzProfileIlluminant.x = iccInvertValue16(icc->header.xyzProfileIlluminant.x);
	icc->header.xyzProfileIlluminant.y = iccInvertValue16(icc->header.xyzProfileIlluminant.y);
	icc->header.xyzProfileIlluminant.z = iccInvertValue16(icc->header.xyzProfileIlluminant.z);
}

void iccReadTag(IccP icc, IccTagNodeP node) {

	fpos_t position = 0;
	fpos_t dataOffset = 0;

	IccTagInfoP tagInfo;

	// read tag info
	fread(&node->tag, sizeof(IccTag), 1, icc->file.handle);

	// invert tag elements to little-endian
	node->tag.signature.value = iccInvertValue32(node->tag.signature.value);
	node->tag.dataOffset = iccInvertValue32(node->tag.dataOffset);
	node->tag.elementSize = iccInvertValue32(node->tag.elementSize);

	// save data offset and allocate memory for data array
	dataOffset = node->tag.dataOffset;
	node->data = malloc(node->tag.elementSize);

	// save current position, set new and
	// get tag's data from file
	fgetpos(icc->file.handle, &position);
	fsetpos(icc->file.handle, &dataOffset);

	// now we can invoke reader for current tag
	if ((tagInfo = IccFindTagInfo(node->tag.signature.value)) != NULL) {
		tagInfo->reader(icc, tagInfo, node);
	}

	// restore saved position
	fsetpos(icc->file.handle, &position);
}

void iccReadTable(IccP icc) {

	IccTagNode iccTagNode;

	// read table information (4 bytes with tag amount)
	fread(&icc->table, sizeof(IccTable), 1, icc->file.handle);

	// invert value to little-endian
	icc->table.tagCount = iccInvertValue32(icc->table.tagCount);
	icc->list = calloc(icc->table.tagCount, sizeof(IccTagNode));

	// read all tags and save in array
	for (uInt32Number i = 0; i < icc->table.tagCount; i++) {

		// read tag from file
		iccReadTag(icc, &iccTagNode);

		// copy tag to array
		memcpy(&icc->list[i], &iccTagNode, sizeof(iccTagNode));
	}
}

void iccPrintHeader(IccP icc) {

	printf("ICC File\n");
	printf(" - File Name : %s\n", icc->file.name);

	printf("ICC Header\n");
	printf(" - Profile Size : %d\n", icc->header.profileSize);
	printf(" - CMM Type : %s\n", iccGetSignatureString(icc->header.cmmType));
	printf(" - Profile Version Number : %d\n", icc->header.profileVersionNumber);
	printf(" - Device Class : %s\n", iccGetSignatureString(icc->header.deviceClass.string));
	printf(" - Color Space : %s\n", iccGetSignatureString(icc->header.colorDataSpace.string));
	printf(" - Profile Connection : %s\n", iccGetSignatureString(icc->header.profileConnection.string));
	printf(" - Creation Time : %d.%d.%d-%d:%d:%d\n",
		icc->header.creationTime.days,
		icc->header.creationTime.month,
		icc->header.creationTime.year,
		icc->header.creationTime.hours,
		icc->header.creationTime.minutes,
		icc->header.creationTime.seconds);
	printf(" - ACSP Signature : %s\n", iccGetSignatureString(icc->header.acspSignature));
	printf(" - Platform Target : %s\n", iccGetSignatureString(icc->header.platformTarget.string));
	printf(" - Profile Flags : %d\n", icc->header.profileFlags);
	printf(" - Device Manufacturer : \"%s\"\n", iccGetSignatureString(icc->header.deviceManufacturer));
	printf(" - Device Model : %p\n", icc->header.deviceModel);
	printf(" - Device Attributes : %d\n", icc->header.deviceAttributes);
	printf(" - Rendering Intent : %d\n", icc->header.renderingIntent);

	printf(" - XYZ Profile Illuminant\n");
	printf(" - - X : %d\n", icc->header.xyzProfileIlluminant.x);
	printf(" - - Y : %d\n", icc->header.xyzProfileIlluminant.y);
	printf(" - - Z : %d\n", icc->header.xyzProfileIlluminant.z);
	
	printf(" - Profile Creator : \"%s\"\n\n", iccGetSignatureString(icc->header.profileCreator));
}

void iccPrintTable(IccP icc) {

	for (uInt32Number i = 0; i < icc->table.tagCount; i++) {

		IccTagNodeP tagNode = &icc->list[i];

		printf("(%s) - %d:%d\n",
			iccGetSignatureString(tagNode->tag.signature.string),
			                      tagNode->tag.dataOffset,
			                      tagNode->tag.elementSize,
								  tagNode->data);
	}
	printf("\n");
}