#ifndef SPI_FI_H
#define SPI_FI_H

#ifdef __cplusplus
extern "C" {
#endif 

typedef struct PictureInfo {
	long left, top;			/* �����չ�_����λ�� */
	long width;					/* ����η�(pixel) */
	long height;				/* ����θߤ�(pixel) */
	WORD x_density;			/* ���ؤ�ˮƽ�����ܶ� */
	WORD y_density;			/* ���ؤδ�ֱ�����ܶ� */
	short colorDepth;		/* ���ص������bit�� */
	HLOCAL hInfo;				/* �����ڤΥƥ��������[���ӳ����Ȥ����] */
} PictureInfo;

/*-------------------------------------------------------------------------*/
/* ����`���`�� */
/*-------------------------------------------------------------------------*/
#define SPI_NO_FUNCTION				-1	/* ���ΙC�ܤϥ���ץ���Ȥ���Ƥ��ʤ� */
#define SPI_ALL_RIGHT					0	/* �����K�� */
#define SPI_ABORT							1	/* ���`��Хå��v������0�򷵤����Τ�չ�_����ֹ���� */
#define SPI_NOT_SUPPORT				2	/* δ֪�Υե��`�ޥå� */
#define SPI_OUT_OF_ORDER			3	/* �ǩ`��������Ƥ��� */
#define SPI_NO_MEMORY					4	/* ����`���_�������ʤ� */
#define SPI_MEMORY_ERROR			5	/* ����`����` */
#define SPI_FILE_READ_ERROR		6	/* �ե������`�ɥ���` */
#define	SPI_WINDOW_ERROR			7	/* �����_���ʤ� (�ǹ��_�Υ���`���`��) */
#define SPI_OTHER_ERROR				8	/* �ڲ�����` */
#define	SPI_FILE_WRITE_ERROR	9	/* �����z�ߥ���` (�ǹ��_�Υ���`���`��) */
#define	SPI_END_OF_FILE				10/* �ե�����K�� (�ǹ��_�Υ���`���`��) */

static const char *pluginfo[] = {
	"00IN",
	"FreeImage Susie Plugin by nyfair <nyfair2012@gmail.com>",
	"*.jpg;*.png;*.bmp;*.gif;*.jpeg;*.tga;*.tiff;*.webp;*.wdp;\
	*.psd;*.ico;*.hdr;*.jxr;*.tif;*.hdp",
	"View image with freeimage.dll",
};

const unsigned int infosize = sizeof(BITMAPINFOHEADER);
typedef int (CALLBACK *SPI_PROGRESS)(int, int, long);

/* Common Function */
int DLL_API WINAPI GetPluginInfo(int infono, LPSTR buf, int buflen);
int DLL_API WINAPI IsSupported(LPSTR filename, DWORD dw);

/* '00IN'���v�� */
int DLL_API WINAPI GetPictureInfo(LPSTR buf, long len, 
																	unsigned int flag, PictureInfo *lpInfo);
int DLL_API WINAPI GetPicture(LPSTR buf, long len, unsigned int flag,
															HANDLE *pHBInfo, HANDLE *pHBm,
															SPI_PROGRESS lpPrgressCallback, long lData);
int DLL_API WINAPI GetPreview(LPSTR buf, long len, unsigned int flag,
															HANDLE *pHBInfo, HANDLE *pHBm,
															SPI_PROGRESS lpPrgressCallback, long lData);

#ifdef __cplusplus
}
#endif 

#endif	/* SPI_FI_H */
