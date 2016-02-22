/* $Id: wavesamples.h,v 1.15 2008/01/23 22:42:31 root Exp $ */

#include "stdafx.h"
#include <mmsystem.h>

#ifndef WAVESAMPLES
#define WAVESAMPLES
#endif

struct _riff_
{
  _TCHAR riffID[4];		//contains identifier "RIFF"
  DWORD riffSIZE;		//File size minus 8 bytes
  _TCHAR riffFORMAT[4];	//contains identifier "WAVE"
};

struct WAVEFORM
{
  WORD wFormatTag;		//format of digital sound (1 for uncompressed)
  WORD nChannels;		//Number of channels (1 for mono and 2 for stereo)
  DWORD nSamplesPerSec;	//Number of samples per second
  DWORD nAvgBytesPerSec;//Average number bytes of data per second
  WORD nBlockAlign;		//Minimal data size for playing
  WORD wBitsPerSample;	//Bits per sample (8 or 16)
};

struct _fmt_
{
  _TCHAR fmtID[4];		//contains identifier: "fmt " (with space)
  DWORD fmtSIZE;		//contains the size of this block (for WAVE PCM 16)
  WAVEFORM fmtFORMAT;	//structure WAVEFORMATEX but without cbSize field
};

struct _data_
{
  _TCHAR dataID[4];	//contains identifier: "data"
  DWORD dataSIZE;	//data size
};

#pragma pack (1)
struct _WaveSample_
{
	struct _riff_			riff_header;
	struct _fmt_			waveFormat;
	struct _data_			data_header;
	unsigned char		SampleData[65535 * 4];	// The actual waveform data
};

typedef short	AudioWord;
typedef unsigned char	AudioByte;

extern struct _WaveSample_ WaveSample;

void PlayWaveData(struct _WaveSample_ WaveData, long int samplestart, long int samplelength);

void DrumSampleParams(int lsbaddress, unsigned char selection);

unsigned char GetSampleFromRom(unsigned short address, CFile& RomFile);
