#include "stdafx.h"
#include "windows.h"
#include "marker_api.h"

long int samplestart[24];
long int sampleend[24];
wchar_t soundnames[24][20];
LPCWSTR lpszRomPathName;

void ReadMarkerFile(CStdioFile& file)
{
	// Marker Type 11 is region start
	// Marker Type 12 is region end
	// Marker Type 0 is generic Marker

	CString buf[1024];
	wchar_t *stopstring;
	long	counter = 0;
	wchar_t *markerline = new wchar_t[512];
	for ( counter = 0 ; counter < 12 ; counter++)
	{
		samplestart[counter] = -1;
		sampleend[counter] = -1;
		wsprintf(soundnames[counter],_T(""));
	}
	counter = 0;

	while (file.ReadString(buf[counter]))
	{
		if ( wcsrchr(buf[counter], _T('\t')) != NULL )
			buf[counter] = wcsrchr(buf[counter], _T('\t')) + 1;
		if (wcsstr(buf[counter],_T("Name=")) != NULL )
		{
			buf[counter] = wcsrchr(buf[counter], _T('=')) +1;
			if (wcsstr(buf[counter],_T("*")) == NULL)
				wcscpy(soundnames[counter],buf[counter]);
		}
		if ( wcsstr(buf[counter],_T("Pos=")) != NULL )
		{
			file.ReadString(buf[counter+1]);
			if ( wcsstr(buf[counter+1],_T("Type=11")) != NULL )
			{
				buf[counter] = wcsrchr(buf[counter], _T('=')) +1;
				if ( samplestart[counter] == -1 )
				{
					samplestart[counter] = wcstoul( buf[counter] , &stopstring, 10);
				
					if ( counter > 0 )
					{
						if ( sampleend[counter - 1] == -1 )
						{
							sampleend[counter - 1] = samplestart[counter] - 1;
						}
					}
					counter++;
				}
			}
			if ( wcsstr(buf[counter+1],_T("Type=12")) != NULL )
			{
				buf[counter] = wcsrchr(buf[counter], _T('=')) +1;
				sampleend[counter-1] = wcstoul( buf[counter] , &stopstring, 10);
			}
//			if (samplestart[counter] != -1 && sampleend[counter] != -1 )
//				counter++;
		}
	}

	if ( sampleend[11] == -1 )
		sampleend[11] = 65535;
}