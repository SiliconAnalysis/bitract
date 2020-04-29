//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "HistogramFrm.h"
#include "ImageFrm.h"
#include "ROMBitSettingsFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "histogrambox"
#pragma resource "*.dfm"
THistogramForm *HistogramForm;
//---------------------------------------------------------------------------
__fastcall THistogramForm::THistogramForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall THistogramForm::HistogramBoxClick(TObject *Sender)
{
    HistogramBox->Update();
}
//---------------------------------------------------------------------------
void __fastcall THistogramForm::FormCreate(TObject *Sender)
{
// read .ini file to setup form (x/y position etc)
    TIniFile *BitractIni;

    BitractIni = new TIniFile( ChangeFileExt( Application->ExeName, ".ini" ) );
    Top     = BitractIni->ReadInteger( "HistogramForm", "Top", ROMBitSettingsForm->Top+ROMBitSettingsForm->Height );     // HistogramForm goes below ObjectiveForm (on top of ImageForm)
    Left    = BitractIni->ReadInteger( "HistogramForm", "Left", 0 );
    Width   = BitractIni->ReadInteger( "HistogramForm", "Width", Width );
    Height  = BitractIni->ReadInteger( "HistogramForm", "Height", Height );

    delete BitractIni;
}
//---------------------------------------------------------------------------
void __fastcall THistogramForm::FormDestroy(TObject *Sender)
{
// write .ini file to save form setup (x/y position etc)
    TIniFile *BitractIni;

    BitractIni = new TIniFile( ChangeFileExt( Application->ExeName, ".ini" ) );
    BitractIni->WriteInteger( "HistogramForm", "Top", Top );          // save top/left of form
    BitractIni->WriteInteger( "HistogramForm", "Left", Left );
    BitractIni->WriteInteger( "HistogramForm", "Width", Width );      // save width/height of form
    BitractIni->WriteInteger( "HistogramForm", "Height", Height );

    delete BitractIni;
}
//---------------------------------------------------------------------------
void __fastcall THistogramForm::FormResize(TObject *Sender)
{
    if( Width > 320 )
        HistogramBox->Width = Width-315;
}
//---------------------------------------------------------------------------
