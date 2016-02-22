#ifndef MARKER_API
#define MARKER_API

/* Handle to a MRK FILE */
DECLARE_HANDLE(MMARKER);

extern long int samplestart[24];
extern long int sampleend[24];
extern wchar_t soundnames[24][20];
extern LPCWSTR lpszRomPathName;

/* Function prototypes */
//MMARKER	WINAPI	ReadMarkerFile(CFile& file);
void ReadMarkerFile(CStdioFile& file);
#endif