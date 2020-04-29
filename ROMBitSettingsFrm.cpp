//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "ROMBitSettingsFrm.h"
#include "ImageFrm.h"
#include "LogFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "histogrambox"
#pragma link "ievect"
#pragma link "ieview"
#pragma link "imageenview"
#pragma link "imageenproc"
#pragma resource "*.dfm"
TROMBitSettingsForm *ROMBitSettingsForm;
//---------------------------------------------------------------------------
__fastcall TROMBitSettingsForm::TROMBitSettingsForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TROMBitSettingsForm::FormCreate(TObject *Sender)
{
// read .ini file to setup form (x/y position etc)
    TIniFile *PicturizatronIni;

    PicturizatronIni = new TIniFile( ChangeFileExt( Application->ExeName, ".ini" ) );
    Top     = PicturizatronIni->ReadInteger( "ROMBitSettingsForm", "Top", LogForm->Top+LogForm->Height );
    Left    = PicturizatronIni->ReadInteger( "ROMBitSettingsForm", "Left", 0 );
    Width   = PicturizatronIni->ReadInteger( "ROMBitSettingsForm", "Width", Width );
    Height  = PicturizatronIni->ReadInteger( "ROMBitSettingsForm", "Height", Height );

    delete PicturizatronIni;
}
//---------------------------------------------------------------------------
void __fastcall TROMBitSettingsForm::FormDestroy(TObject *Sender)
{
// write .ini file to save form setup (x/y position etc)
    TIniFile *PicturizatronIni;

    PicturizatronIni = new TIniFile( ChangeFileExt( Application->ExeName, ".ini" ) );
    PicturizatronIni->WriteInteger( "ROMBitSettingsForm", "Top",  Top );          // save top/left of form
    PicturizatronIni->WriteInteger( "ROMBitSettingsForm", "Left", Left );
    PicturizatronIni->WriteInteger( "ROMBitSettingsForm", "Width", Width );      // save width/height of form
    PicturizatronIni->WriteInteger( "ROMBitSettingsForm", "Height", Height );

    delete PicturizatronIni;
}
//---------------------------------------------------------------------------
void __fastcall TROMBitSettingsForm::TabSheet1Resize(TObject *Sender)
{
    if( TabSheet1->Width > 50 )
        HistogramBox->Width = TabSheet1->Width-32;

    if( TabSheet1->Height > 60 )
        HistogramBox->Height = TabSheet1->Height-42;
}
//---------------------------------------------------------------------------
void __fastcall TROMBitSettingsForm::BitHistRedCheckBoxClick(
      TObject *Sender)
{
    THistogramKind TempHistogramKind;

    if( BitHistRedCheckBox->Checked )
        TempHistogramKind << hkRed;

    if( BitHistGreenCheckBox->Checked )
        TempHistogramKind << hkGreen;

    if( BitHistBlueCheckBox->Checked )
        TempHistogramKind << hkBlue;

    if( BitHistGrayCheckBox->Checked )
        TempHistogramKind << hkGray;

    HistogramBox->HistogramKind = TempHistogramKind;
}
//---------------------------------------------------------------------------
void __fastcall TROMBitSettingsForm::BitsPerColEditKeyPress(
      TObject *Sender, char &Key)
{
    if( Key=='\r' )
    {
        ImageForm->FillROMBox1Click(NULL);
        Key = 0;
    }
}
//---------------------------------------------------------------------------
void __fastcall TROMBitSettingsForm::YBoxesToAnalyzeEditKeyPress(
      TObject *Sender, char &Key)
{
    if( Key=='\r' )
    {
        ImageForm->FillROMBox1Click(NULL);
        Key = 0;
    }
    switch( Key )
    {
        case '\b':
        case '0':
        case '1':
            break;

        default:
            Key = 0;
            break;
    }
}
//---------------------------------------------------------------------------

