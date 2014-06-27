#ifndef __ICC__
#define __ICC__

#include <stdint.h>

#ifndef _FILE_DEFINED
typedef uint32_t IccFile;
#else
typedef FILE* IccFile;
#endif

#pragma pack(push, 1)

typedef struct {
	uint16_t year;
	uint16_t month;
	uint16_t days;
	uint16_t hours;
	uint16_t minutes;
	uint16_t seconds;
} DateTimeNumber;

typedef int32_t  s15Fixed16Number;
typedef uint32_t u16Fixed16Number;
typedef uint16_t u8Fixed8Number;

typedef uint8_t  uInt8Number;
typedef uint16_t uInt16Number;
typedef uint32_t uInt32Number;
typedef uint64_t uInt64Number;

typedef uint8_t Reserved;
typedef uint8_t Signature4[4];

typedef struct {
	s15Fixed16Number x;
	s15Fixed16Number y;
	s15Fixed16Number z;
} XyzNumber;

typedef struct {
	uInt8Number major;
	uInt8Number minor;
	Reserved reserved[2];
} ProfileVersion;

typedef union {
	uInt32Number value;
	Signature4 string;
} SignaturePack4;

typedef       void* IccVoidP;
typedef const char* IccString;

/*
	Profile File

	-------------------------
	| signature | encoding  |
	-------------------------
	| 'acsp'    | 61637370h |
	-------------------------
*/

typedef SignaturePack4 ProfileFile;

#define ICC_PROFILE_ACSP 0x61637370

static const ProfileFile IccProfileAcsp = { ICC_PROFILE_ACSP };

/*
	Device Class

	------------------------------------------------------------------------
	| signature | encoding  | description                                  |
	------------------------------------------------------------------------
	| 'scnr'    | 73636E72h | input devices - scanners and digital cameras |
	| 'mntr'    | 6D6E7472h | display devices - CRTs and LCDs              |
	| 'prtr'    | 70727472h | output devices - printers                    |
	| 'link'    | 6C696E6Bh | device link profiles                         |
	| 'spac'    | 73706163h | color space conversion profiles              |
	| 'abst'    | 61627374h | abstract profiles                            |
	| 'nmcl'    | 6E6D636Ch | named color profiles                         |
	------------------------------------------------------------------------
*/

typedef SignaturePack4 DeviceClass;

#define ICC_DC_SCNR 0x73636E72
#define ICC_DC_MNTR 0x6D6E7472
#define ICC_DC_PRTR 0x70727472
#define ICC_DC_LINK 0x6C696E6B
#define ICC_DC_SPAC 0x73706163
#define ICC_DC_ABST 0x61627374
#define ICC_DC_NMCL 0x6E6D636C

static const DeviceClass IccDeviceClassScnr = { ICC_DC_SCNR };
static const DeviceClass IccDeviceClassMntr = { ICC_DC_MNTR };
static const DeviceClass IccDeviceClassPrtr = { ICC_DC_LINK };
static const DeviceClass IccDeviceClassLink = { ICC_DC_SPAC };
static const DeviceClass IccDeviceClassSpac = { ICC_DC_ABST };
static const DeviceClass IccDeviceClassNmcl = { ICC_DC_NMCL };

/*
	Color Space

	---------------------------------------
	| Color Space | Signature | encoding  |
	---------------------------------------
	| XYZData     | 'XYZ '    | 58595A20h |
	| labData     | 'Lab '    | 4C616220h |
	| luvData     | 'Luv '    | 4C757620h |
	| YCbCrData   | 'YCbr'    | 59436272h |
	| YxyData     | 'Yxy '    | 59787920h |
	| rgbData     | 'RGB '    | 52474220h |
	| grayData    | 'GRAY'    | 47524159h |
	| hsvData     | 'HSV '    | 48535620h |
	| hlsData     | 'HLS '    | 484C5320h |
	| cmykData    | 'CMYK'    | 434D594Bh |
	| cmyData     | 'CMY '    | 434D5920h |
	---------------------------------------
*/

typedef SignaturePack4 ColorSpace;

#define ICC_CS_XYZ  0x58595A20
#define ICC_CS_LAB  0x4C616220
#define ICC_CS_LUV  0x4C757620
#define ICC_CS_YCBR 0x59436272
#define ICC_CS_YZY  0x59787920
#define ICC_CS_RGB  0x52474220
#define ICC_CS_GRAY 0x47524159
#define ICC_CS_HSV  0x48535620
#define ICC_CS_HLS  0x484C5320
#define ICC_CS_CMYK 0x434D594B
#define ICC_CS_CMY  0x434D5920

static const ColorSpace IccColorSpaceXyz = { ICC_CS_XYZ };
static const ColorSpace IccColorSpaceLab = { ICC_CS_LAB };
static const ColorSpace IccColorSpaceLuv = { ICC_CS_LUV };
static const ColorSpace IccColorSpaceYcbr = { ICC_CS_YCBR };
static const ColorSpace IccColorSpaceYzy = { ICC_CS_YZY };
static const ColorSpace IccColorSpaceRgb = { ICC_CS_RGB };
static const ColorSpace IccColorSpaceGray = { ICC_CS_GRAY };
static const ColorSpace IccColorSpaceHsv = { ICC_CS_HSV };
static const ColorSpace IccColorSpaceHls = { ICC_CS_HLS };
static const ColorSpace IccColorSpaceCmyk = { ICC_CS_CMYK };
static const ColorSpace IccColorSpaceCmy = { ICC_CS_CMY };

/*
	Profile Connection Color Space

	-----------------------------------
	| PCCS    | Signature | encoding  |
	-----------------------------------
	| XYZData | 'XYZ '    | 58595A20h |
	| labData | 'Lab '    | 4C616220h |
	-----------------------------------
*/

typedef SignaturePack4 ProfileConnection;

#define ICC_PCCS_XYZ 0x58595A20
#define ICC_PCCS_LAB 0x4C616220

static const ProfileConnection IccProfileConnectionColorSpaceXyz = { ICC_PCCS_XYZ };
static const ProfileConnection IccProfileConnectionCoolrSpaceLab = { ICC_PCCS_LAB };

/*
	Primary Platform Target

	--------------------------------------------------
	| Primary Platform       | Signature | encoding  |
	--------------------------------------------------
	| Apple Computer, Inc.   | 'APPL'    | 4150504Ch |
	| Microsoft Corporation  | 'MSFT'    | 4D534654h |
	| Silicon Graphics, Inc. | 'SGI '    | 53474920h |
	| Sun Microsystems, Inc. | 'SUNW'    | 53554E57h |
	| Taligent, Inc.         | 'TGNT'    | 54474E54h |
	--------------------------------------------------
*/

typedef SignaturePack4 PlatformTarget;

#define ICC_PPT_APPLE     0x4150504C
#define ICC_PPT_MICROSOFT 0x4D534654
#define ICC_PPT_SILICON   0x53474920
#define ICC_PPT_SUN       0x53554E57
#define ICC_PPT_TALIGENT  0x54474E54

static const PlatformTarget IccPrimaryPlatformTargetApple = { ICC_PPT_APPLE };
static const PlatformTarget IccPrimaryPlatformTargetMicrosoft = { ICC_PPT_MICROSOFT };
static const PlatformTarget IccPrimaryPlatformTargetSilicon = { ICC_PPT_SILICON };
static const PlatformTarget IccPrimaryPlatformTargetSun = { ICC_PPT_SUN };
static const PlatformTarget IccPrimaryPlatformTargetTaligent = { ICC_PPT_TALIGENT };

/*
	Profile Flags

	-------------------------------------------------------
	| Flags                                | Bit Position |
	-------------------------------------------------------
	| Embedded Profile (0 if not embedded, | 0            |
	| 1 if embeddedin file)                |              |
	-------------------------------------------------------
	| Profile cannot be used independently |              |
	| from the embedded color              | 1            |
	| data (set to 1 if true, 0 if false)  |              |
	-------------------------------------------------------
*/

typedef uint32_t ProfileFlags;

#define ICC_PF_EMBEDDED    0x0000
#define ICC_PF_INDEPENDENT 0x0001

/*
	Device Flags

	--------------------------------------------------------
	| Attribute                             | bit position |
	--------------------------------------------------------
	| Reflective (off) or Transparency (on) | 0            |
	| Glossy (off) or Matte (on)            | 1            |
	--------------------------------------------------------
*/

typedef uint64_t DeviceFlags;

#define ICC_DF_TRANSPARENCY 0x0000
#define ICC_DF_MATTE        0x0001

static uint8_t isDeviceFlagTransparency(DeviceFlags deviceFlags) {
	return (deviceFlags & ICC_DF_TRANSPARENCY) != 0;
}
static uint8_t isDeviceFlagReflective(DeviceFlags deviceFlags) {
	return (deviceFlags & ICC_DF_TRANSPARENCY) == 0;
}
static uint8_t isDeviceFlagMatte(DeviceFlags deviceFlags) {
	return (deviceFlags & ICC_DF_MATTE) != 0;
}
static uint8_t isDeviceFlagGlossy(DeviceFlags deviceFlags) {
	return (deviceFlags & ICC_DF_MATTE) == 0;
}

/*
	Rendering Intent

	---------------------------------
	| Rendering Intent      | value |
	---------------------------------
	| Perceptual            | 0     |
	| Relative Colorimetric | 1     |
	| Saturation            | 2     |
	| Absolute Colorimetric | 3     |
	----------------------------------
*/

typedef uint32_t RenderingIntent;

#define ICC_RI_REPCEPTUAL            0x0000
#define ICC_RI_RELATIVE_COLORIMETRIC 0x0001
#define ICC_RI_SATURATION            0x0002
#define ICC_RI_ABSOLUTE_COLORIMETRIC 0x0003

/*
	ICC Header:

	The profile header provides the necessary information to allow a receiving
	system to properly search and sort ICC profiles. Table 8 gives the byte position,
	content and encoding of the profile header.

	This header provides a set of parameters at the beginning of the profile
	format. For color transformation profiles, the device profile dependent fields are
	set to zero if irrelevant. Having a fixed length header allows for performance
	enhancements in the profile searching and sorting operations.
*/

typedef struct {

	/*	The total size of the profile in bytes. */
	uInt32Number profileSize;

	/*	Identifies the preferred CMM to be used.
		The signatures must be registered in order to
		avoid conflicts. The Technical Secretary
		of the International Color Consortium is
		responsible for the registering of new signatures. */
	Signature4 cmmType;

	/*	Profile version number where the first 8 bits
		are the major version number and the next 8 bits
		are for the minor version number. The major and
		minor version numbers are set by the International
		Color Consortium and will match up with the
		profile format revisions. The current version
		number is 02h with a minor version number of 00h. */
	ProfileVersion profileVersionNumber;

	/*	Profile/Device class: There are three basic
		classifications (classes) of device profiles: input,
		display and output profiles. */
	DeviceClass deviceClass;

	/*	Color space of data (possibly a derived space) */
	ColorSpace colorDataSpace;

	/*	Profile connection space */
	ProfileConnection profileConnection;

	/*	Date and time this profile was first created */
	DateTimeNumber creationTime;

	/*	‘acsp’ (61637370h) profile file signature */
	Signature4 acspSignature;

	/*	Signature to indicate the primary
		platform/operating system framework
		for which the profile was created. */
	PlatformTarget platformTarget;

	/*	Flags to indicate various hints for the
		CMM such as distributed processing and
		caching options. The first 16 bits (low
		word in big-endian notation) are reserved
		for the Profile Consortium. */
	ProfileFlags profileFlags;

	/*	The signatures for various manufacturers and models
		are listed in a separate document (ICC Signatures).
		New signatures must be registered with the ICC, see
		clause 0.7 'Registration Authority' */
	Signature4 deviceManufacturer;
	Signature4 deviceModel;

	/*	Attributes unique to the particular device setup
		such as media type. The first 32 bits (lower two
		words in big-endian notation) of this 64 bit value
		are reserved for the ICC. */
	DeviceFlags deviceAttributes;

	/*	Perceptual, relative colorimetric, saturation and
		absolute colorimetric are the four intents required
		to be supported. The first 16 bits (low word in big-endian
		notation) worth of numbers are reserved for the ICC. */
	RenderingIntent renderingIntent;

	/*	The XYZ values of the illuminant of the pro- ﬁle connection
		space. This must correspond to D50. It is explained in more
		detail in Annex A.1 'Proﬁle Connection Spaces' */
	XyzNumber xyzProfileIlluminant;

	/*	Identifies the creator of the profile. The signatures
		are from the group of signatures used for the device
		manufacturer field. */
	Signature4 profileCreator;

	/*	Reserved */
	Reserved reserved[44];

} IccHeader;

/*
	Device Technology Information
*/

#define ICC_DTI_FSCN 0x6673636E
#define ICC_DTI_DCAM 0x6463616D
#define ICC_DTI_RSCN 0x7273636E
#define ICC_DTI_IJET 0x696A6574
#define ICC_DTI_TWAX 0x74776178
#define ICC_DTI_EPHO 0x6570686F
#define ICC_DTI_ESTA 0x65737461
#define ICC_DTI_DSUB 0x64737562
#define ICC_DTI_RPHO 0x7270686F
#define ICC_DTI_RPRN 0x6670726E
#define ICC_DTI_VIDM 0x7669646D
#define ICC_DTI_VIDC 0x76696463
#define ICC_DTI_PJTV 0x706A7476
#define ICC_DTI_CRT  0x43525420
#define ICC_DTI_PMD  0x504D4420
#define ICC_DTI_AMD  0x414D4420
#define ICC_DTI_KPCD 0x4B504344
#define ICC_DTI_IMGS 0x696D6773
#define ICC_DTI_GRAV 0x67726176
#define ICC_DTI_OFFS 0x6F666673
#define ICC_DTI_SILK 0x73696C6B
#define ICC_DTI_FLEX 0x666C6578

/*
	Individual Tag Structures Within Tag Table
*/

typedef struct {
	SignaturePack4 signature;
	uInt32Number dataOffset;
	uInt32Number elementSize;
} IccTag, *IccTagP;

typedef struct {
	IccTag tag;
	IccVoidP data;
} IccTagNode, *IccTagNodeP;

/*
	The tag table acts as a table of contents for the tags
	and tag element data in the profiles. The tags within
	the table are not required to be in any particular order.
*/

typedef struct {
	uInt32Number tagCount;
} IccTable;

typedef struct {
	IccFile handle;
	IccString name;
} IccFileInfo;

typedef struct Icc* IccP;

typedef void(*IccReadMethod)(IccP icc,
	IccVoidP buffer,
	uInt32Number length);

typedef void(*IccNumberMethod)(IccP icc,
	IccVoidP buffer,
	uInt32Number length);

typedef void(*IccWriteMethod)(IccP icc,
	IccVoidP buffer,
	uInt32Number length);

typedef void(*IccMoveMethod)(IccP icc,
	uInt32Number position);

typedef IccVoidP(*IccReadAtMethod)(IccP icc,
	uInt32Number length,
	uInt32Number position);

typedef struct Icc {

	/* File header */
	IccHeader header;
	/* File table */
	IccTable table;
	/* File info */
	IccFileInfo file;
	/* Array with tags */
	IccTagNodeP list;
	/* Read number from file */
	IccNumberMethod number;
	/* Read buffer from file */
	IccReadMethod read;
	/* Write buffer to file */
	IccWriteMethod write;
	/* Move file to another position */
	IccMoveMethod move;
	/* Load block from file */
	IccReadAtMethod load;

} Icc;

/*
	Tag Descriptions

	This clause specifies the individual tags used to create
	all possible portable profiles in the ICC Profile Format.
	The appropriate tag typing is indicated with each individual
	tag description. Note that the signature indicates only
	the type of data and does not imply anything about the use
	or purpose for which the data is intended.
*/

typedef struct IccTagInfo *IccTagInfoP;

typedef void(*IccTagReader)(
	IccP        icc,
	IccTagInfoP info,
	IccTagNodeP node);

typedef struct IccTagInfo {
	SignaturePack4 signature;
	IccTagReader reader;
} IccTagInfo;

#define ICC_TAG_A2B0 0x41324230
#define ICC_TAG_A2B1 0x41324231
#define ICC_TAG_A2B2 0x41324232
#define ICC_TAG_BXYZ 0x6258595A
#define ICC_TAG_BTRC 0x62545243
#define ICC_TAG_B2A0 0x42324130
#define ICC_TAG_B2A1 0x42324131
#define ICC_TAG_B2A2 0x42324132
#define ICC_TAG_CALT 0x63616C74
#define ICC_TAG_TARG 0x74617267
#define ICC_TAG_CPRT 0x63707274
#define ICC_TAG_DMND 0x646D6E64
#define ICC_TAG_DMDD 0x646D6464
#define ICC_TAG_GAMT 0x67616D74
#define ICC_TAG_KTRC 0x6B545243
#define ICC_TAG_GXYZ 0x6758595A
#define ICC_TAG_GTRC 0x67545243
#define ICC_TAG_LUMI 0x6C756D69
#define ICC_TAG_MEAS 0x6D656173
#define ICC_TAG_BKPT 0x626b7074
#define ICC_TAG_WTPT 0x77747074
#define ICC_TAG_NCOL 0x6E636F6C
#define ICC_TAG_NCL2 0x6E636C32
#define ICC_TAG_PRE0 0x70726530
#define ICC_TAG_PRE1 0x70726531
#define ICC_TAG_PRE2 0x70726532
#define ICC_TAG_DESC 0x64657363
#define ICC_TAG_PSEQ 0x70736571
#define ICC_TAG_PSD0 0x70736430
#define ICC_TAG_PSD1 0x70736431
#define ICC_TAG_PSD2 0x70736432
#define ICC_TAG_PSD3 0x70736433
#define ICC_TAG_PS2S 0x70733273
#define ICC_TAG_PS2I 0x70733269
#define ICC_TAG_RXYZ 0x7258595A
#define ICC_TAG_RTRC 0x72545243
#define ICC_TAG_SCRD 0x73637264
#define ICC_TAG_SCRN 0x7363726E
#define ICC_TAG_TECH 0x74656368
#define ICC_TAG_BFD  0x62666420
#define ICC_TAG_VUED 0x76756564
#define ICC_TAG_VIEW 0x76696577

extern void IccReaderA2B0(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderA2B1(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderA2B2(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderBXYZ(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderBTRC(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderB2A0(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderB2A1(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderB2A2(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderCALT(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderTARG(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderCPRT(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderDMND(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderDMDD(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderGAMT(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderKTRC(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderGXYZ(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderGTRC(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderLUMI(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderMEAS(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderBKPT(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderWTPT(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderNCOL(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderNCL2(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderPRE0(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderPRE1(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderPRE2(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderDESC(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderPSEQ(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderPSD0(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderPSD1(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderPSD2(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderPSD3(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderPS2S(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderPS2I(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderRXYZ(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderRTRC(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderSCRD(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderSCRN(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderTECH(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderBFD(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderVUED(IccP icc, IccTagInfoP info, IccTagNodeP node);
extern void IccReaderVIEW(IccP icc, IccTagInfoP info, IccTagNodeP node);

#define ICC_TAG_AMOUNT 44

static IccTagInfo IccTagInfoList[ICC_TAG_AMOUNT] = {
	{ ICC_TAG_A2B0, IccReaderA2B0 },
	{ ICC_TAG_A2B1, IccReaderA2B1 },
	{ ICC_TAG_A2B2, IccReaderA2B2 },
	{ ICC_TAG_BXYZ, IccReaderBXYZ },
	{ ICC_TAG_BTRC, IccReaderBTRC },
	{ ICC_TAG_B2A0, IccReaderB2A0 },
	{ ICC_TAG_B2A1, IccReaderB2A1 },
	{ ICC_TAG_B2A2, IccReaderB2A2 },
	{ ICC_TAG_CALT, IccReaderCALT },
	{ ICC_TAG_TARG, IccReaderTARG },
	{ ICC_TAG_CPRT, IccReaderCPRT },
	{ ICC_TAG_DMND, IccReaderDMND },
	{ ICC_TAG_DMDD, IccReaderDMDD },
	{ ICC_TAG_GAMT, IccReaderGAMT },
	{ ICC_TAG_KTRC, IccReaderKTRC },
	{ ICC_TAG_GXYZ, IccReaderGXYZ },
	{ ICC_TAG_GTRC, IccReaderGTRC },
	{ ICC_TAG_LUMI, IccReaderLUMI },
	{ ICC_TAG_MEAS, IccReaderMEAS },
	{ ICC_TAG_BKPT, IccReaderBKPT },
	{ ICC_TAG_WTPT, IccReaderWTPT },
	{ ICC_TAG_NCOL, IccReaderNCOL },
	{ ICC_TAG_NCL2, IccReaderNCL2 },
	{ ICC_TAG_PRE0, IccReaderPRE0 },
	{ ICC_TAG_PRE1, IccReaderPRE1 },
	{ ICC_TAG_PRE2, IccReaderPRE2 },
	{ ICC_TAG_DESC, IccReaderDESC },
	{ ICC_TAG_PSEQ, IccReaderPSEQ },
	{ ICC_TAG_PSD0, IccReaderPSD0 },
	{ ICC_TAG_PSD1, IccReaderPSD1 },
	{ ICC_TAG_PSD2, IccReaderPSD2 },
	{ ICC_TAG_PSD3, IccReaderPSD3 },
	{ ICC_TAG_PS2S, IccReaderPS2S },
	{ ICC_TAG_PS2I, IccReaderPS2I },
	{ ICC_TAG_RXYZ, IccReaderRXYZ },
	{ ICC_TAG_RTRC, IccReaderRTRC },
	{ ICC_TAG_SCRD, IccReaderSCRD },
	{ ICC_TAG_SCRN, IccReaderSCRN },
	{ ICC_TAG_TECH, IccReaderTECH },
	{ ICC_TAG_BFD,  IccReaderBFD  },
	{ ICC_TAG_VUED, IccReaderVUED },
	{ ICC_TAG_VIEW, IccReaderVIEW }
};

static IccTagInfoP IccFindTagInfo(uInt32Number value) {

	for (uInt32Number i = 0; i < ICC_TAG_AMOUNT; i++) {
		if (IccTagInfoList[i].signature.value == value) {
			return (IccTagInfoP)&IccTagInfoList[i];
		}
	}

	return 0;
}

static IccTagInfo IccTagInfoA2B0 = { ICC_TAG_A2B0, IccReaderA2B0 };
static IccTagInfo IccTagInfoA2B1 = { ICC_TAG_A2B1, IccReaderA2B1 };
static IccTagInfo IccTagInfoA2B2 = { ICC_TAG_A2B2, IccReaderA2B2 };
static IccTagInfo IccTagInfoBXYZ = { ICC_TAG_BXYZ, IccReaderBXYZ };
static IccTagInfo IccTagInfoBTRC = { ICC_TAG_BTRC, IccReaderBTRC };
static IccTagInfo IccTagInfoB2A0 = { ICC_TAG_B2A0, IccReaderB2A0 };
static IccTagInfo IccTagInfoB2A1 = { ICC_TAG_B2A1, IccReaderB2A1 };
static IccTagInfo IccTagInfoB2A2 = { ICC_TAG_B2A2, IccReaderB2A2 };
static IccTagInfo IccTagInfoCALT = { ICC_TAG_CALT, IccReaderCALT };
static IccTagInfo IccTagInfoTARG = { ICC_TAG_TARG, IccReaderTARG };
static IccTagInfo IccTagInfoCPRT = { ICC_TAG_CPRT, IccReaderCPRT };
static IccTagInfo IccTagInfoDMND = { ICC_TAG_DMND, IccReaderDMND };
static IccTagInfo IccTagInfoDMDD = { ICC_TAG_DMDD, IccReaderDMDD };
static IccTagInfo IccTagInfoGAMT = { ICC_TAG_GAMT, IccReaderGAMT };
static IccTagInfo IccTagInfoKTRC = { ICC_TAG_KTRC, IccReaderKTRC };
static IccTagInfo IccTagInfoGXYZ = { ICC_TAG_GXYZ, IccReaderGXYZ };
static IccTagInfo IccTagInfoGTRC = { ICC_TAG_GTRC, IccReaderGTRC };
static IccTagInfo IccTagInfoLUMI = { ICC_TAG_LUMI, IccReaderLUMI };
static IccTagInfo IccTagInfoMEAS = { ICC_TAG_MEAS, IccReaderMEAS };
static IccTagInfo IccTagInfoBKPT = { ICC_TAG_BKPT, IccReaderBKPT };
static IccTagInfo IccTagInfoWTPT = { ICC_TAG_WTPT, IccReaderWTPT };
static IccTagInfo IccTagInfoNCOL = { ICC_TAG_NCOL, IccReaderNCOL };
static IccTagInfo IccTagInfoNCL2 = { ICC_TAG_NCL2, IccReaderNCL2 };
static IccTagInfo IccTagInfoPRE0 = { ICC_TAG_PRE0, IccReaderPRE0 };
static IccTagInfo IccTagInfoPRE1 = { ICC_TAG_PRE1, IccReaderPRE1 };
static IccTagInfo IccTagInfoPRE2 = { ICC_TAG_PRE2, IccReaderPRE2 };
static IccTagInfo IccTagInfoDESC = { ICC_TAG_DESC, IccReaderDESC };
static IccTagInfo IccTagInfoPSEQ = { ICC_TAG_PSEQ, IccReaderPSEQ };
static IccTagInfo IccTagInfoPSD0 = { ICC_TAG_PSD0, IccReaderPSD0 };
static IccTagInfo IccTagInfoPSD1 = { ICC_TAG_PSD1, IccReaderPSD1 };
static IccTagInfo IccTagInfoPSD2 = { ICC_TAG_PSD2, IccReaderPSD2 };
static IccTagInfo IccTagInfoPSD3 = { ICC_TAG_PSD3, IccReaderPSD3 };
static IccTagInfo IccTagInfoPS2S = { ICC_TAG_PS2S, IccReaderPS2S };
static IccTagInfo IccTagInfoPS2I = { ICC_TAG_PS2I, IccReaderPS2I };
static IccTagInfo IccTagInfoRXYZ = { ICC_TAG_RXYZ, IccReaderRXYZ };
static IccTagInfo IccTagInfoRTRC = { ICC_TAG_RTRC, IccReaderRTRC };
static IccTagInfo IccTagInfoSCRD = { ICC_TAG_SCRD, IccReaderSCRD };
static IccTagInfo IccTagInfoSCRN = { ICC_TAG_SCRN, IccReaderSCRN };
static IccTagInfo IccTagInfoTECH = { ICC_TAG_TECH, IccReaderTECH };
static IccTagInfo IccTagInfoBFD  = { ICC_TAG_BFD,  IccReaderBFD  };
static IccTagInfo IccTagInfoVUED = { ICC_TAG_VUED, IccReaderVUED };
static IccTagInfo IccTagInfoVIEW = { ICC_TAG_VIEW, IccReaderVIEW };

void iccOpenFile(IccP icc, IccString file);
void iccCloseFile(IccP icc);
void iccReadHeader(IccP icc);
void iccReadTable(IccP icc);
void iccPrintHeader(IccP icc);
void iccPrintTable(IccP icc);

#pragma pack(pop)

#endif // ~__ICC__