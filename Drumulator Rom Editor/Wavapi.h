// $Id: Wavapi.h,v 1.8 2008/01/30 22:50:43 root Exp $

#ifndef _INC_WAVAPI
#define _INC_WAVAPI
/* Handle to a WAV */
DECLARE_HANDLE(MWAV);


/* Function prototypes */
BOOL	WINAPI	SaveWAV(MWAV hWav, CFile& file);
MWAV	WINAPI	ReadWAVFile(LPCWSTR lpszWaveName);
BOOL SplitWaveRom(CFile& waveromfile, LPCWSTR lpszWaveRomPathName);

#endif //!_INC_WAVAPI

