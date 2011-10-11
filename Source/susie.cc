#if defined(_MSC_VER)
#define	_export
#endif

#include <windows.h>
#include "FreeImage.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PictureInfo {
	long left,top;			/* �����չ�_����λ�� */
	long width;					/* ����η�(pixel) */
	long height;				/* ����θߤ�(pixel) */
	WORD x_density;			/* ���ؤ�ˮƽ�����ܶ� */
	WORD y_density;			/* ���ؤδ�ֱ�����ܶ� */
	short colorDepth;		/* ���ص������bit�� */
	HLOCAL hInfo;				/* �����ڤΥƥ��������[���ӳ����Ȥ����] */
} PictureInfo;

/* Common Function */
int _export PASCAL GetPluginInfo(int infono, LPSTR buf, int buflen);
int _export PASCAL IsSupported(LPSTR filename, DWORD dw);


/* '00IN'���v�� */
int _export PASCAL GetPictureInfo(LPSTR buf, long len, unsigned int flag, PictureInfo *lpInfo);
int _export PASCAL GetPicture(LPSTR buf, long len, unsigned int flag, HANDLE *pHBInfo, HANDLE *pHBm,
								FARPROC lpPrgressCallback, long lData);
int _export PASCAL GetPreview(LPSTR buf, long len,unsigned int flag, HANDLE *pHBInfo, HANDLE *pHBm,
								FARPROC lpPrgressCallback, long lData);

#ifdef __cplusplus
}
#endif
