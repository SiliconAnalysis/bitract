//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "LogFrm.h"
#include "ImageFrm.h"
#include "HistogramFrm.h"
#include "ROMBitSettingsFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TCriticalSection *StageCmd;      // TCriticalSection for accessing CmdToExec/X/Y/StepSize

TLogForm *LogForm;
//---------------------------------------------------------------------------
__fastcall TLogForm::TLogForm(TComponent* Owner)
    : TForm(Owner)
{
    StageCmd=new TCriticalSection;  // create StageCmd TCriticalSection
}
//---------------------------------------------------------------------------
void __fastcall TLogForm::FormCreate(TObject *Sender)
{
// read .ini file to setup form (x/y position etc)
    TIniFile *PicturizatronIni;

    PicturizatronIni = new TIniFile( ChangeFileExt( Application->ExeName, ".ini" ) );
    Top     = PicturizatronIni->ReadInteger( "LogForm", "Top", 0 );     // LogForm goes at top left of screen
    Left    = PicturizatronIni->ReadInteger( "LogForm", "Left", 0 );

    delete PicturizatronIni;
}
//---------------------------------------------------------------------------
void __fastcall TLogForm::Exit1Click(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TLogForm::Image1Click(TObject *Sender)
{
    ImageForm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TLogForm::FormDestroy(TObject *Sender)
{
// write .ini file to save form setup (x/y position etc)
    TIniFile *PicturizatronIni;

    PicturizatronIni = new TIniFile( ChangeFileExt( Application->ExeName, ".ini" ) );
    PicturizatronIni->WriteInteger( "LogForm", "Top", Top );          // save top/left of form
    PicturizatronIni->WriteInteger( "LogForm", "Left", Left );
    PicturizatronIni->WriteInteger( "LogForm", "Width", Width );      // save width/height of form
    PicturizatronIni->WriteInteger( "LogForm", "Height", Height );

    delete PicturizatronIni;
}
//---------------------------------------------------------------------------
void __fastcall TLogForm::Histogram1Click(TObject *Sender)
{
    HistogramForm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TLogForm::ROMBitSettings1Click(TObject *Sender)
{
    ROMBitSettingsForm->Show();
}
//---------------------------------------------------------------------------
