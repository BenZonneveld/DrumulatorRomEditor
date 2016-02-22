// $Id: Wavapi.cpp,v 1.19 2008/02/23 23:58:51 root Exp $
#include "stdafx.h"
#include "windows.h"
#include <math.h>


#include "wavesamples.h"
#include "resource.h"
#include "Wavapi.h"


MWAV WINAPI ReadWAVFile(LPCWSTR lpszWaveName)
{
	HMMIO		hmmio;				// file handle for open file 
	MMCKINFO	mmckinfoParent;		// parent chunk information 
	MMCKINFO	mmckinfoSubchunk;	// subchunk information structure 
	DWORD		dwFmtSize;			// size of "FMT" chunk
	DWORD		dwDataSize;			// size of "DATA" chunk
	const unsigned char	*lpDataIn;			// Pointer to memory for file to be loaded
	DWORD		dwRiffSize;			// size of "RIFF" chunk?
	MWAV		hWAV;
	LPSTR		pWAV;
//	struct	_WaveSample_ WaveSample;	// The Wavesample structure for the Mirage

	// Open the file for reading with buffered I/O 
    // by using the default internal buffer 

//	swprintf_s(szFileName,sizeof(szFileName),_T("%s"),file.GetFilePath());
	if(!(hmmio = mmioOpen((LPWSTR)lpszWaveName, NULL, 
		MMIO_READ | MMIO_ALLOCBUF))) 
	{ 
		MessageBox(NULL,_T("Failed to open file."),NULL,MB_ICONERROR | MB_OK); 
		return NULL; 
	}

	// Locate a "RIFF" chunk with a "WAVE" form type to make 
	// sure the file is a waveform-audio file. 
	mmckinfoParent.fccType = mmioFOURCC('W', 'A', 'V', 'E'); 
	if (mmioDescend(hmmio, (LPMMCKINFO) &mmckinfoParent, NULL, 
		MMIO_FINDRIFF)) 
	{ 
		MessageBox(NULL,_T("This is not a waveform-audio file."),NULL,MB_ICONERROR | MB_OK); 
		mmioClose(hmmio, 0); 
		return NULL; 
	}
	dwRiffSize = mmckinfoParent.cksize + 8;

	memcpy((unsigned char *)&WaveSample.riff_header,(unsigned char *)&mmckinfoParent,sizeof(WaveSample.riff_header));
	if ( dwRiffSize > sizeof(WaveSample) )
	{
		hWAV = (MWAV) ::GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, (DWORD)dwRiffSize);
	} else {
		hWAV = (MWAV) ::GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, (DWORD)sizeof(WaveSample));
	}

	if (hWAV == NULL)
	{
		MessageBox(NULL,_T("Unable to allocate memory for file loading."),NULL,MB_ICONERROR | MB_OK); 
		mmioClose(hmmio, 0); 
		return NULL;
	}
	pWAV = (LPSTR) ::GlobalLock((HGLOBAL) hWAV);

	// Find the "FMT" chunk (form type "FMT"); it must be 
	// a subchunk of the "RIFF" chunk. 
	mmckinfoSubchunk.ckid = mmioFOURCC('f', 'm', 't', ' '); 
	if (mmioDescend(hmmio, &mmckinfoSubchunk, &mmckinfoParent, 
		MMIO_FINDCHUNK) != MMSYSERR_NOERROR ) 
	{ 
		MessageBox(NULL, _T("Waveform-audio file has no \"FMT\" chunk."), NULL, MB_ICONERROR | MB_OK); 
		mmioClose(hmmio, 0); 
		::GlobalUnlock((HGLOBAL) hWAV);
		::GlobalFree((HGLOBAL) hWAV);
		return NULL; 
	} 
 
	// Get the size of the "FMT" chunk.
	dwFmtSize = mmckinfoSubchunk.cksize;
	// Read the "FMT" chunk. 
	if (mmioRead(hmmio, (HPSTR) &WaveSample.waveFormat.fmtFORMAT, dwFmtSize) != dwFmtSize){ 
        MessageBox(NULL,_T("Failed to read format chunk."), NULL, MB_ICONERROR | MB_OK); 
        mmioClose(hmmio, 0);
		::GlobalUnlock((HGLOBAL) hWAV);
		::GlobalFree((HGLOBAL) hWAV);
        return NULL; 
    }
	// Put the size in the WaveSample and the fmtID
	memcpy(WaveSample.waveFormat.fmtID,"fmt ",4);
	WaveSample.waveFormat.fmtSIZE = dwFmtSize;

	// Ascend out of the "FMT" subchunk. 
	mmioAscend(hmmio, &mmckinfoSubchunk, 0);

	// Find the data subchunk. The current file position should be at 
	// the beginning of the data chunk; however, you should not make 
	// this assumption. Use mmioDescend to locate the data chunk.
	mmckinfoSubchunk.ckid = mmioFOURCC('d','a','t','a');
	if (mmioDescend(hmmio, &mmckinfoSubchunk, &mmckinfoParent, 
		MMIO_FINDCHUNK) != MMSYSERR_NOERROR ) 
	{ 
		MessageBox(NULL,_T("Waveform-audio file has no data chunk."), NULL, MB_ICONERROR | MB_OK); 
		mmioClose(hmmio, 0); 
		::GlobalUnlock((HGLOBAL) hWAV);
		::GlobalFree((HGLOBAL) hWAV);
		return NULL; 
	} 
 
	// Get the size of the data subchunk. 
	dwDataSize = mmckinfoSubchunk.cksize;
	if (dwDataSize == 0L){ 
        MessageBox(NULL,_T("The data chunk contains no data."), NULL, MB_ICONERROR | MB_OK);  
		mmioClose(hmmio, 0); 
		::GlobalUnlock((HGLOBAL) hWAV);
		::GlobalFree((HGLOBAL) hWAV);
		return NULL; 
	}

	// Allocate memory for input data
	lpDataIn = (const unsigned char *) ::GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, (DWORD)dwDataSize);
	 
	// Read the waveform-audio data subchunk. 
	if(mmioRead(hmmio, (HPSTR) lpDataIn, dwDataSize) != dwDataSize){ 
		MessageBox(NULL, _T("Failed to read data chunk."), NULL, MB_ICONERROR | MB_OK); 
		mmioClose(hmmio, 0);
		::GlobalUnlock((HGLOBAL) hWAV);
		::GlobalFree((HGLOBAL) hWAV);
		::GlobalFree((HGLOBAL) lpDataIn);
		return NULL; 
	}

	// Check if the sample is a mono sample
	if ( WaveSample.waveFormat.fmtFORMAT.nChannels > 2 )
	{	
		CString strMsg;
		// We only handle stereo samples:
		if ( WaveSample.waveFormat.fmtFORMAT.nChannels > 2 )
		{
			MessageBox(NULL, _T("Sample has more than 2 channels."), NULL, MB_ICONERROR | MB_OK);
			mmioClose(hmmio, 0);
			::GlobalUnlock((HGLOBAL) hWAV);
			::GlobalFree((HGLOBAL) hWAV);
			::GlobalFree((HGLOBAL) lpDataIn);
			return NULL;
		}
	}
			
	memcpy((unsigned char *)&WaveSample.SampleData,lpDataIn,dwDataSize);
	::GlobalFree((HGLOBAL) lpDataIn); 

	memcpy(WaveSample.data_header.dataID,"data",4);
	WaveSample.data_header.dataSIZE = dwDataSize;
	mmioClose(hmmio, 0);

	if ( dwRiffSize > sizeof(WaveSample) )
	{
		memcpy(pWAV,(unsigned char*)&WaveSample, sizeof(WaveSample));
	} else {
		memcpy(pWAV,(unsigned char*)&WaveSample, dwRiffSize);
	}

	::GlobalUnlock((HGLOBAL) hWAV);
	return hWAV;
}


BOOL SplitWaveRom(CFile& waveromfile, LPCWSTR lpszWaveRomPathName)
{
	CFile RomImageFile;
	CFileException fe;

	char buf[16384];
	int counter, rom;
	size_t stringsize;
	const wchar_t *pstring;

	/* Create the filename for the corresponding wavefile */
	stringsize = _tcslen(lpszWaveRomPathName);
	LPCWSTR lpszImageAPathName = new TCHAR[ stringsize + 1];
	LPCWSTR lpszImageBPathName = new TCHAR[ stringsize + 1];
	LPCWSTR lpszImageCPathName = new TCHAR[ stringsize + 1];
	LPCWSTR lpszImageDPathName = new TCHAR[ stringsize + 1];

	_tcscpy((wchar_t *)lpszImageAPathName, (wchar_t *)lpszWaveRomPathName);
	pstring = wcsrchr(lpszImageAPathName, _T('.'));
	_tcscpy((wchar_t *)pstring, _T(" A.bin"));

	_tcscpy((wchar_t *)lpszImageBPathName, (wchar_t *)lpszWaveRomPathName);
	pstring = wcsrchr(lpszImageBPathName, _T('.'));
	_tcscpy((wchar_t *)pstring, _T(" B.bin"));

	_tcscpy((wchar_t *)lpszImageCPathName, (wchar_t *)lpszWaveRomPathName);
	pstring = wcsrchr(lpszImageCPathName, _T('.'));
	_tcscpy((wchar_t *)pstring, _T(" C.bin"));

	_tcscpy((wchar_t *)lpszImageDPathName, (wchar_t *)lpszWaveRomPathName);
	pstring = wcsrchr(lpszImageDPathName, _T('.'));
	_tcscpy((wchar_t *)pstring, _T(" D.bin"));

	for(rom=0;rom < 4; rom++)
	{
		switch(rom)
		{
		case 0:
			if (!RomImageFile.Open(lpszImageAPathName, CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive, &fe))
			{
				return FALSE;
			}
			break;
		case 1:
			if (!RomImageFile.Open(lpszImageBPathName, CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive, &fe))
			{
				return FALSE;
			}
			break;
		case 2:
			if (!RomImageFile.Open(lpszImageCPathName, CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive, &fe))
			{
				return FALSE;
			}
			break;
		case 3:
			if (!RomImageFile.Open(lpszImageDPathName, CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive, &fe))
			{
				return FALSE;
			}
			break;
		}
		
		waveromfile.Read(buf,16384);
		RomImageFile.Write(buf,16384);
		RomImageFile.Flush();
		RomImageFile.Close();

	}
	return TRUE;
}