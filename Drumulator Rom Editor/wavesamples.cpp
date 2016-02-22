/* $Id: wavesamples.cpp,v 1.17 2008/02/23 23:58:51 root Exp $ */
#include "stdafx.h"
#include <windows.h>
#include <mmsystem.h>
#include <MMReg.h>
#include <math.h>
#include <afxwin.h>
#include <afx.h>

#include "marker_api.h"
#include "DrumulatorRom.h"
#include "wavesamples.h"

struct _WaveSample_ WaveSample;

void PlayWaveData(struct _WaveSample_ WaveData, long int samplestart, long int samplelength)
{
	HANDLE		hData  = NULL;  // handle of waveform data memory 
	HPSTR		lpData = NULL;  // pointer to waveform data memory 
	HWAVEOUT	hWaveOut; 
	HGLOBAL		hWaveHdr; 
	LPWAVEHDR	lpWaveHdr; 
	UINT		wResult; 
	WAVEFORMAT	*pFormat; 
	DWORD		dwDataSize; 

	dwDataSize = (DWORD) (samplelength - samplestart);

	pFormat = (WAVEFORMAT *)&WaveData.waveFormat.fmtFORMAT;
	lpData = (HPSTR)&WaveData.SampleData[samplestart * WaveData.waveFormat.fmtFORMAT.nBlockAlign];

	// Open a waveform device for output using window callback. 

	if (waveOutOpen((LPHWAVEOUT)&hWaveOut, WAVE_MAPPER, 
					(LPWAVEFORMATEX)pFormat,
					0L, 0L, CALLBACK_NULL))
	{ 
		MessageBox(NULL, 
					_T("Failed to open waveform output device."), 
					NULL, MB_OK | MB_ICONEXCLAMATION); 
		return; 
	} 
 
	// Allocate and lock memory for the header. 

	hWaveHdr = GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE, 
		(DWORD) sizeof(WAVEHDR)); 
	if (hWaveHdr == NULL) 
	{ 
		MessageBox(NULL, _T("Not enough memory for header."), 
					NULL, MB_OK | MB_ICONEXCLAMATION); 
		return; 
	} 
 
	lpWaveHdr = (LPWAVEHDR) GlobalLock(hWaveHdr); 
	if (lpWaveHdr == NULL) 
	{ 
		GlobalUnlock(hData); 
		GlobalFree(hData); 
		MessageBox(NULL, 
			_T("Failed to lock memory for header."), 
			NULL, MB_OK | MB_ICONEXCLAMATION); 
		return; 
	} 
 
	// After allocation, set up and prepare header. 
 
	lpWaveHdr->lpData = lpData; 
	lpWaveHdr->dwBufferLength = dwDataSize; 
	lpWaveHdr->dwFlags = 0L; 
	lpWaveHdr->dwLoops = 0L; 
	waveOutPrepareHeader(hWaveOut, lpWaveHdr, sizeof(WAVEHDR)); 
 
	// Now the data block can be sent to the output device. The 
	// waveOutWrite function returns immediately and waveform 
	// data is sent to the output device in the background. 
 
	wResult = waveOutWrite(hWaveOut, lpWaveHdr, sizeof(WAVEHDR)); 
	if (wResult != 0) 
	{ 
		waveOutUnprepareHeader(hWaveOut, lpWaveHdr, 
								sizeof(WAVEHDR)); 
		GlobalUnlock( hData); 
		GlobalFree(hData); 
		MessageBox(NULL, _T("Failed to write block to device"), 
					NULL, MB_OK | MB_ICONEXCLAMATION); 
		return; 
	}
	GlobalUnlock( hData); 
	GlobalFree(hData); 
}

void DrumSampleParams(int lsbaddress, unsigned char selection)
{
	unsigned char start_lsb, start_msb, end_lsb, end_msb;

	start_lsb = (unsigned char)(samplestart[selection] & 0xFF);
	start_msb = (unsigned char)((samplestart[selection] & 0xFF00) / 256);
	end_lsb = (unsigned char)((65535 - (sampleend[selection] - samplestart[selection])) & 0xFF);
	end_msb = (unsigned char)(((65535 - (sampleend[selection] - samplestart[selection])) & 0xFF00) /256);
	DrumulatorRom[lsbaddress] = start_lsb;
	DrumulatorRom[lsbaddress+1] = start_msb;
	DrumulatorRom[lsbaddress+2] = end_lsb;
	DrumulatorRom[lsbaddress+3] = end_msb;
}

unsigned char GetSampleFromRom(unsigned short address, CFile& RomFile)
{
	unsigned short rom_soundstart;
	unsigned char counter;
	unsigned char lsb_byte;
	unsigned char msb_byte;
	RomFile.Seek(address,CFile::begin );
	RomFile.Read(&lsb_byte,1);
	RomFile.Read(&msb_byte,1);
	rom_soundstart = lsb_byte + (256* msb_byte);

	for (counter = 0 ; counter < 12; counter++)
	{
		if (samplestart[counter] == rom_soundstart)
			return counter;
	}
	return 255;
}