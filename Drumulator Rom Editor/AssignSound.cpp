// AssignSound.cpp : implementation file
//

#include "stdafx.h"
#include <string.h>
#include "Drumulator Rom Editor.h"
#include "AssignSound.h"
#include "marker_api.h"
#include "wavesamples.h"
#include "DrumulatorRom.h"

wchar_t outputs[8][14]={
	{_T("Lo Tom")},
	{_T("Mid/Hi Tom")},
	{_T("Clave/Cowbell")},
	{_T("Claps")},
	{_T("Ride (NF)")},
	{_T("Hats (NF)")},
	{_T("Snare/Rim")},
	{_T("Bass")}};

// CAssignSound dialog

IMPLEMENT_DYNAMIC(CAssignSound, CDialog)

CAssignSound::CAssignSound(CWnd* pParent /*=NULL*/)
	: CDialog(CAssignSound::IDD, pParent)
{

}

CAssignSound::~CAssignSound()
{
}

void CAssignSound::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SOUND_COMBO_1, mComboSound1);
	DDX_Control(pDX, IDC_OUTPUT_COMBO_1, mOutputCombo1);
	DDX_Control(pDX, IDC_PLAY_1, mPlayButton1);
	DDX_Control(pDX, IDC_SOUND_COMBO_2, mComboSound2);
	DDX_Control(pDX, IDC_OUTPUT_COMBO_2, mOutputCombo2);
	DDX_Control(pDX, IDC_PLAY_2, mPlayButton2);
	DDX_Control(pDX, IDC_SOUND_COMBO_3, mComboSound3);
	DDX_Control(pDX, IDC_OUTPUT_COMBO_3, mOutputCombo3);
	DDX_Control(pDX, IDC_PLAY_3, mPlayButton3);
	DDX_Control(pDX, IDC_SOUND_COMBO_4, mComboSound4);
	DDX_Control(pDX, IDC_OUTPUT_COMBO_4, mOutputCombo4);
	DDX_Control(pDX, IDC_PLAY_4, mPlayButton4);
	DDX_Control(pDX, IDC_SOUND_COMBO_5, mComboSound5);
	DDX_Control(pDX, IDC_OUTPUT_COMBO_5, mOutputCombo5);
	DDX_Control(pDX, IDC_PLAY_5, mPlayButton5);
	DDX_Control(pDX, IDC_SOUND_COMBO_6, mComboSound6);
	DDX_Control(pDX, IDC_OUTPUT_COMBO_6, mOutputCombo6);
	DDX_Control(pDX, IDC_PLAY_6, mPlayButton6);
	DDX_Control(pDX, IDC_SOUND_COMBO_7, mComboSound7);
	DDX_Control(pDX, IDC_OUTPUT_COMBO_7, mOutputCombo7);
	DDX_Control(pDX, IDC_PLAY_7, mPlayButton7);
	DDX_Control(pDX, IDC_SOUND_COMBO_8, mComboSound8);
	DDX_Control(pDX, IDC_OUTPUT_COMBO_8, mOutputCombo8);
	DDX_Control(pDX, IDC_PLAY_8, mPlayButton8);
	DDX_Control(pDX, IDC_SOUND_COMBO_9, mComboSound9);
	DDX_Control(pDX, IDC_OUTPUT_COMBO_9, mOutputCombo9);
	DDX_Control(pDX, IDC_PLAY_9, mPlayButton9);
	DDX_Control(pDX, IDC_SOUND_COMBO_10, mComboSound10);
	DDX_Control(pDX, IDC_OUTPUT_COMBO_10, mOutputCombo10);
	DDX_Control(pDX, IDC_PLAY_10, mPlayButton10);
	DDX_Control(pDX, IDC_SOUND_COMBO_11, mComboSound11);
	DDX_Control(pDX, IDC_OUTPUT_COMBO_11, mOutputCombo11);
	DDX_Control(pDX, IDC_PLAY_11, mPlayButton11);
	DDX_Control(pDX, IDC_SOUND_COMBO_12, mComboSound12);
	DDX_Control(pDX, IDC_OUTPUT_COMBO_12, mOutputCombo12);
	DDX_Control(pDX, IDC_PLAY_12, mPlayButton12);
}


BEGIN_MESSAGE_MAP(CAssignSound, CDialog)
	ON_BN_CLICKED(IDC_PLAY_1, &CAssignSound::OnBnClickedPlay1)
	ON_BN_CLICKED(IDC_PLAY_2, &CAssignSound::OnBnClickedPlay2)
	ON_BN_CLICKED(IDC_PLAY_3, &CAssignSound::OnBnClickedPlay3)
	ON_BN_CLICKED(IDC_PLAY_4, &CAssignSound::OnBnClickedPlay4)
	ON_BN_CLICKED(IDC_PLAY_5, &CAssignSound::OnBnClickedPlay5)
	ON_BN_CLICKED(IDC_PLAY_6, &CAssignSound::OnBnClickedPlay6)
	ON_BN_CLICKED(IDC_PLAY_7, &CAssignSound::OnBnClickedPlay7)
	ON_BN_CLICKED(IDC_PLAY_8, &CAssignSound::OnBnClickedPlay8)
	ON_BN_CLICKED(IDC_PLAY_9, &CAssignSound::OnBnClickedPlay9)
	ON_BN_CLICKED(IDC_PLAY_10, &CAssignSound::OnBnClickedPlay10)
	ON_BN_CLICKED(IDC_PLAY_11, &CAssignSound::OnBnClickedPlay11)
	ON_BN_CLICKED(IDC_PLAY_12, &CAssignSound::OnBnClickedPlay12)
	ON_BN_CLICKED(IDC_OK_BUTTON, &CAssignSound::OnBnClickedOkButton)
	ON_BN_CLICKED(IDC_CANCEL, &CAssignSound::OnBnClickedCancel)
END_MESSAGE_MAP()


// CAssignSound message handlers
BOOL CAssignSound::OnInitDialog()
{
	CDialog::OnInitDialog();

	CFile RomFile;
	CFileException fe;

	CButton *Button1 = &mPlayButton1;
	CComboBox	*Sound1 = &mComboSound1;
	CComboBox	*Output1 = &mOutputCombo1;

	CButton *Button2 = &mPlayButton2;
	CComboBox	*Sound2 = &mComboSound2;
	CComboBox	*Output2 = &mOutputCombo2;

	CButton *Button3 = &mPlayButton3;
	CComboBox	*Sound3 = &mComboSound3;
	CComboBox	*Output3 = &mOutputCombo3;

	CButton *Button4 = &mPlayButton4;
	CComboBox	*Sound4 = &mComboSound4;
	CComboBox	*Output4 = &mOutputCombo4;

	CButton *Button5 = &mPlayButton5;
	CComboBox	*Sound5 = &mComboSound5;
	CComboBox	*Output5 = &mOutputCombo5;

	CButton *Button6 = &mPlayButton6;
	CComboBox	*Sound6 = &mComboSound6;
	CComboBox	*Output6 = &mOutputCombo6;

	CButton *Button7 = &mPlayButton7;
	CComboBox	*Sound7 = &mComboSound7;
	CComboBox	*Output7 = &mOutputCombo7;

	CButton *Button8 = &mPlayButton8;
	CComboBox	*Sound8 = &mComboSound8;
	CComboBox	*Output8 = &mOutputCombo8;

	CButton *Button9 = &mPlayButton9;
	CComboBox	*Sound9 = &mComboSound9;
	CComboBox	*Output9 = &mOutputCombo9;

	CButton *Button10 = &mPlayButton10;
	CComboBox	*Sound10 = &mComboSound10;
	CComboBox	*Output10 = &mOutputCombo10;

	CButton *Button11 = &mPlayButton11;
	CComboBox	*Sound11 = &mComboSound11;
	CComboBox	*Output11 = &mOutputCombo11;
	
	CButton *Button12 = &mPlayButton12;
	CComboBox	*Sound12 = &mComboSound12;
	CComboBox	*Output12 = &mOutputCombo12;
	
	char output_counter,sound_counter;
	wchar_t soundname[20];

	unsigned char rom_output;
	for (output_counter = 0 ; output_counter < 8 ; output_counter++)
	{
		Output1->AddString((LPCTSTR)outputs[output_counter]);
		Output2->AddString((LPCTSTR)outputs[output_counter]);
		Output3->AddString((LPCTSTR)outputs[output_counter]);
		Output4->AddString((LPCTSTR)outputs[output_counter]);
		Output5->AddString((LPCTSTR)outputs[output_counter]);
		Output6->AddString((LPCTSTR)outputs[output_counter]);
		Output7->AddString((LPCTSTR)outputs[output_counter]);
		Output8->AddString((LPCTSTR)outputs[output_counter]);
		Output9->AddString((LPCTSTR)outputs[output_counter]);
		Output10->AddString((LPCTSTR)outputs[output_counter]);
		Output11->AddString((LPCTSTR)outputs[output_counter]);
		Output12->AddString((LPCTSTR)outputs[output_counter]);
	}

	for (sound_counter = 0 ; sound_counter < 12 ; sound_counter++)
	{
		if (sampleend[sound_counter] != 0)
		{
			if ( wcslen(soundnames[sound_counter]) > 0 )
			{
				swprintf(soundname,sizeof(soundname),_T("%s"), soundnames[sound_counter]);
			} else {
				swprintf(soundname,sizeof(soundname),_T("Sound %i"),sound_counter+1);
			}
			Sound1->AddString((LPCTSTR)soundname);
			Sound2->AddString((LPCTSTR)soundname);
			Sound3->AddString((LPCTSTR)soundname);
			Sound4->AddString((LPCTSTR)soundname);
			Sound5->AddString((LPCTSTR)soundname);
			Sound6->AddString((LPCTSTR)soundname);
			Sound7->AddString((LPCTSTR)soundname);
			Sound8->AddString((LPCTSTR)soundname);
			Sound9->AddString((LPCTSTR)soundname);
			Sound10->AddString((LPCTSTR)soundname);
			Sound11->AddString((LPCTSTR)soundname);
			Sound12->AddString((LPCTSTR)soundname);
		}
	}

	if (RomFile.Open(lpszRomPathName, CFile::modeRead | CFile::shareDenyWrite, &fe))
	{
		RomFile.Seek(0x1EBC, CFile::begin );
		RomFile.Read(&rom_output,1);
		Output1->SetCurSel(rom_output/2);
		RomFile.Read(&rom_output,1);
		Output2->SetCurSel(rom_output/2);
		RomFile.Read(&rom_output,1);
		Output3->SetCurSel(rom_output/2);
		RomFile.Read(&rom_output,1);
		Output4->SetCurSel(rom_output/2);
		RomFile.Read(&rom_output,1);
		Output5->SetCurSel(rom_output/2);
		RomFile.Read(&rom_output,1);
		Output6->SetCurSel(rom_output/2);
		RomFile.Read(&rom_output,1);
		Output7->SetCurSel(rom_output/2);
		RomFile.Read(&rom_output,1);
		Output8->SetCurSel(rom_output/2);
		RomFile.Read(&rom_output,1);
		Output9->SetCurSel(rom_output/2);
		RomFile.Read(&rom_output,1);
		Output10->SetCurSel(rom_output/2);
		RomFile.Read(&rom_output,1);
		Output11->SetCurSel(rom_output/2);
		RomFile.Read(&rom_output,1);
		Output12->SetCurSel(rom_output/2);

		/* Now Search for the sounds in the existing rom image */
		rom_output = GetSampleFromRom(0x1EC8,RomFile);
		Sound1->SetCurSel(GetSampleFromRom(0x1EC8,RomFile));
		Sound2->SetCurSel(GetSampleFromRom(0x1ECC,RomFile));
		Sound3->SetCurSel(GetSampleFromRom(0x1ED0,RomFile));
		Sound4->SetCurSel(GetSampleFromRom(0x1ED4,RomFile));
		Sound5->SetCurSel(GetSampleFromRom(0x1ED8,RomFile));
		Sound6->SetCurSel(GetSampleFromRom(0x1EDC,RomFile));
		Sound7->SetCurSel(GetSampleFromRom(0x1EE0,RomFile));
		Sound8->SetCurSel(GetSampleFromRom(0x1EE4,RomFile));
		Sound9->SetCurSel(GetSampleFromRom(0x1EE8,RomFile));
		Sound10->SetCurSel(GetSampleFromRom(0x1EEC,RomFile));
		Sound11->SetCurSel(GetSampleFromRom(0x1EF0,RomFile));
		Sound12->SetCurSel(GetSampleFromRom(0x1EF4,RomFile));
	} else {
		Output1->SetCurSel(2);
		Output2->SetCurSel(2);
		Output3->SetCurSel(3);
		Output4->SetCurSel(5);
		Output5->SetCurSel(5);
		Output6->SetCurSel(4);
		Output7->SetCurSel(7);
		Output8->SetCurSel(6);
		Output9->SetCurSel(6);
		Output10->SetCurSel(1);
		Output11->SetCurSel(1);
		Output12->SetCurSel(0);

		Sound1->SetCurSel(0);
		Sound2->SetCurSel(1);
		Sound3->SetCurSel(2);
		Sound4->SetCurSel(3);
		Sound5->SetCurSel(4);
		Sound6->SetCurSel(5);
		Sound7->SetCurSel(6);
		Sound8->SetCurSel(7);
		Sound9->SetCurSel(8);
		Sound10->SetCurSel(9);
		Sound11->SetCurSel(10);
		Sound12->SetCurSel(11);
	}
	return true;
}

void CAssignSound::OnBnClickedPlay1()
{
	CComboBox	*Sound1 = &mComboSound1;
	char selected_sound;
	selected_sound = Sound1->GetCurSel();
	PlayWaveData(WaveSample, samplestart[selected_sound], sampleend[selected_sound]);
}

void CAssignSound::OnBnClickedPlay2()
{
	CComboBox	*Sound2 = &mComboSound2;
	char selected_sound;
	selected_sound = Sound2->GetCurSel();
	PlayWaveData(WaveSample, samplestart[selected_sound], sampleend[selected_sound]);
}

void CAssignSound::OnBnClickedPlay3()
{
	CComboBox	*Sound3 = &mComboSound3;
	char selected_sound;
	selected_sound = Sound3->GetCurSel();
	PlayWaveData(WaveSample, samplestart[selected_sound], sampleend[selected_sound]);
}

void CAssignSound::OnBnClickedPlay4()
{
	CComboBox	*Sound4 = &mComboSound4;
	char selected_sound;
	selected_sound = Sound4->GetCurSel();
	PlayWaveData(WaveSample, samplestart[selected_sound], sampleend[selected_sound]);
}

void CAssignSound::OnBnClickedPlay5()
{
	CComboBox	*Sound5 = &mComboSound5;
	char selected_sound;
	selected_sound = Sound5->GetCurSel();
	PlayWaveData(WaveSample, samplestart[selected_sound], sampleend[selected_sound]);
}

void CAssignSound::OnBnClickedPlay6()
{
	CComboBox	*Sound6 = &mComboSound6;
	char selected_sound;
	selected_sound = Sound6->GetCurSel();
	PlayWaveData(WaveSample, samplestart[selected_sound], sampleend[selected_sound]);
}

void CAssignSound::OnBnClickedPlay7()
{
	CComboBox	*Sound7 = &mComboSound7;
	char selected_sound;
	selected_sound = Sound7->GetCurSel();
	PlayWaveData(WaveSample, samplestart[selected_sound], sampleend[selected_sound]);
}

void CAssignSound::OnBnClickedPlay8()
{
	CComboBox	*Sound8 = &mComboSound8;
	char selected_sound;
	selected_sound = Sound8->GetCurSel();
	PlayWaveData(WaveSample, samplestart[selected_sound], sampleend[selected_sound]);
}

void CAssignSound::OnBnClickedPlay9()
{
	CComboBox	*Sound9 = &mComboSound9;
	char selected_sound;
	selected_sound = Sound9->GetCurSel();
	PlayWaveData(WaveSample, samplestart[selected_sound], sampleend[selected_sound]);
}

void CAssignSound::OnBnClickedPlay10()
{
	CComboBox	*Sound10 = &mComboSound10;
	char selected_sound;
	selected_sound = Sound10->GetCurSel();
	PlayWaveData(WaveSample, samplestart[selected_sound], sampleend[selected_sound]);
}

void CAssignSound::OnBnClickedPlay11()
{
	CComboBox	*Sound11 = &mComboSound11;
	char selected_sound;
	selected_sound = Sound11->GetCurSel();
	PlayWaveData(WaveSample, samplestart[selected_sound], sampleend[selected_sound]);
}

void CAssignSound::OnBnClickedPlay12()
{
	CComboBox	*Sound12 = &mComboSound12;
	char selected_sound;
	selected_sound = Sound12->GetCurSel();
	PlayWaveData(WaveSample, samplestart[selected_sound], sampleend[selected_sound]);
}

void CAssignSound::OnBnClickedOkButton()
{
	OnOK();

	int counter;
	CFile RomFile;
	CFileException fe;

	CComboBox	*Sound1 = &mComboSound1;
	CComboBox	*Output1 = &mOutputCombo1;

	CComboBox	*Sound2 = &mComboSound2;
	CComboBox	*Output2 = &mOutputCombo2;

	CComboBox	*Sound3 = &mComboSound3;
	CComboBox	*Output3 = &mOutputCombo3;

	CComboBox	*Sound4 = &mComboSound4;
	CComboBox	*Output4 = &mOutputCombo4;

	CComboBox	*Sound5 = &mComboSound5;
	CComboBox	*Output5 = &mOutputCombo5;

	CComboBox	*Sound6 = &mComboSound6;
	CComboBox	*Output6 = &mOutputCombo6;

	CComboBox	*Sound7 = &mComboSound7;
	CComboBox	*Output7 = &mOutputCombo7;

	CComboBox	*Sound8 = &mComboSound8;
	CComboBox	*Output8 = &mOutputCombo8;

	CComboBox	*Sound9 = &mComboSound9;
	CComboBox	*Output9 = &mOutputCombo9;

	CComboBox	*Sound10 = &mComboSound10;
	CComboBox	*Output10 = &mOutputCombo10;

	CComboBox	*Sound11 = &mComboSound11;
	CComboBox	*Output11 = &mOutputCombo11;

	CComboBox	*Sound12 = &mComboSound12;
	CComboBox	*Output12 = &mOutputCombo12;

	DrumulatorRom[0x1EBC] = 2*(unsigned char)Output1->GetCurSel();
	DrumSampleParams(0x1EC8, (unsigned char)Sound1->GetCurSel());  

	DrumulatorRom[0x1EBD] = 2*(unsigned char)Output2->GetCurSel();
	DrumSampleParams(0x1ECC, (unsigned char)Sound2->GetCurSel());  

	DrumulatorRom[0x1EBE] = 2*(unsigned char)Output3->GetCurSel();
	DrumSampleParams(0x1ED0, (unsigned char)Sound3->GetCurSel());  

	DrumulatorRom[0x1EBF] = 2*(unsigned char)Output4->GetCurSel();
	DrumSampleParams(0x1ED4, (unsigned char)Sound4->GetCurSel());  

	DrumulatorRom[0x1EC0] = 2*(unsigned char)Output5->GetCurSel();
	DrumSampleParams(0x1ED8, (unsigned char)Sound5->GetCurSel());  

	DrumulatorRom[0x1EC1] = 2*(unsigned char)Output6->GetCurSel();
	DrumSampleParams(0x1EDC, (unsigned char)Sound6->GetCurSel());  

	DrumulatorRom[0x1EC2] = 2*(unsigned char)Output7->GetCurSel();
	DrumSampleParams(0x1EE0, (unsigned char)Sound7->GetCurSel());  

	DrumulatorRom[0x1EC3] = 2*(unsigned char)Output8->GetCurSel();
	DrumSampleParams(0x1EE4, (unsigned char)Sound8->GetCurSel());  

	DrumulatorRom[0x1EC4] = 2*(unsigned char)Output9->GetCurSel();
	DrumSampleParams(0x1EE8, (unsigned char)Sound9->GetCurSel());  

	DrumulatorRom[0x1EC5] = 2*(unsigned char)Output10->GetCurSel();
	DrumSampleParams(0x1EEC, (unsigned char)Sound10->GetCurSel());  

	DrumulatorRom[0x1EC6] = 2*(unsigned char)Output11->GetCurSel();
	DrumSampleParams(0x1EF0, (unsigned char)Sound11->GetCurSel());  

	DrumulatorRom[0x1EC7] = 2*(unsigned char)Output12->GetCurSel();
	DrumSampleParams(0x1EF4, (unsigned char)Sound12->GetCurSel());  

	if (!RomFile.Open(lpszRomPathName, CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive, &fe))
	{
		return;
	}

	for ( counter = 0 ; counter < 8192 ; counter++)
	{
		RomFile.Write((const void*)&DrumulatorRom[counter],1);
	}
	RomFile.Flush();
	RomFile.Close();
}

void CAssignSound::OnBnClickedCancel()
{
	OnCancel();
}
