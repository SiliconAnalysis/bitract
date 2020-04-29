//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ExportFrm.h"
#include "MainFrm.h"
#include "HexFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TExportForm *ExportForm;
//---------------------------------------------------------------------------
__fastcall TExportForm::TExportForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TExportForm::FormShow(TObject *Sender)
{
    char OutputStr[1024];


    ReverseOutputsCheckbox->Checked = MainForm->ReverseOutputs;
    ReverseWithinOutColCheckbox->Checked = MainForm->ReverseWithinOutCol;

    OutputBitOrderEdit->Text = MainForm->OutputBitOrderArrayToStr( OutputStr, sizeof(OutputStr) );

    ROMLayoutRadioGroup->ItemIndex = MainForm->ROM_Layout;
}
//---------------------------------------------------------------------------
void __fastcall TExportForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    MainForm->ReverseOutputs = ReverseOutputsCheckbox->Checked;
    MainForm->ReverseWithinOutCol = ReverseWithinOutColCheckbox->Checked;
    MainForm->ROM_Layout = (rom_layout_type)ROMLayoutRadioGroup->ItemIndex;
    MainForm->Endianness = ExportForm->EndianRadioGroup->ItemIndex;

    if( ROMLayoutRadioGroup->ItemIndex < 2 )
        EnableAdditionalOptions();
    else
        DisableAdditionalOptions();

    if( MainForm->ExportBin() > 0 )   // ByteData[] has been changed
        HexForm->UpdateBin( MainForm->ByteData, MainForm->ByteDataLen );
}
//---------------------------------------------------------------------------
void __fastcall TExportForm::FormCloseQuery(TObject *Sender,
      bool &CanClose)
{
    int i,n;
    char OutputStr[1024];


    CanClose = true;

    if( MainForm->OutputBitOrderStrToArray( OutputBitOrderEdit->Text.c_str() ) < 1 )
    {
        for( i=0; i<MainForm->NumOutputs; i++ )
            MainForm->OutputOrder[i] = i;

        OutputBitOrderEdit->Text = MainForm->OutputBitOrderArrayToStr( OutputStr, sizeof(OutputStr) );
        return;
    }

    // check if MainForm->OutputOrder[] is sane, if not popup dialog and offer to go back to edit it

    for( i=0; i<MainForm->NumOutputs; i++ )
    {
        if( MainForm->OutputOrder[i] >= MainForm->NumOutputs )
            break;
        for( n=0; n<MainForm->NumOutputs; n++ )
        {
            if( MainForm->OutputOrder[n] == i )
                break;
        }
        if( n >= MainForm->NumOutputs )
            break;
    }
    if( i < MainForm->NumOutputs )
    {
        if( Application->MessageBoxA( AnsiString(AnsiString("The Output bit order is not correct!\n\nThe Output bits include the range 0 .. ")+AnsiString( MainForm->NumOutputs-1 )+AnsiString("\n\nDo you want to continue even though the exported data will be invalid?") ).c_str(), "WARNING", MB_YESNO ) != IDYES )
            CanClose = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TExportForm::ReverseOutputsCheckboxClick(TObject *Sender)
{
    MainForm->ReverseOutputs = ReverseOutputsCheckbox->Checked;
    if( MainForm->ExportBin() > 0 )   // ByteData[] has been changed
        HexForm->UpdateBin( MainForm->ByteData, MainForm->ByteDataLen );
}
//---------------------------------------------------------------------------
void __fastcall TExportForm::ReverseWithinOutColCheckboxClick(
      TObject *Sender)
{
    MainForm->ReverseWithinOutCol = ReverseWithinOutColCheckbox->Checked;
    if( MainForm->ExportBin() > 0 )   // ByteData[] has been changed
        HexForm->UpdateBin( MainForm->ByteData, MainForm->ByteDataLen );
}
//---------------------------------------------------------------------------
void __fastcall TExportForm::OutputBitOrderEditExit(TObject *Sender)
{
    int i,n;

    
    MainForm->OutputBitOrderStrToArray( OutputBitOrderEdit->Text.c_str() );

    // check if MainForm->OutputOrder[] is sane

    for( i=0; i<MainForm->NumOutputs; i++ )
    {
        if( MainForm->OutputOrder[i] >= MainForm->NumOutputs )
            break;
        for( n=0; n<MainForm->NumOutputs; n++ )
        {
            if( MainForm->OutputOrder[n] == i )
                break;
        }
        if( n >= MainForm->NumOutputs )
            break;
    }
    if( i < MainForm->NumOutputs )
    {
        if( Application->MessageBoxA( AnsiString(AnsiString("The Output bit order is not correct!\n\nThe Output bits include the range 0 .. ")+AnsiString( MainForm->NumOutputs-1 )+AnsiString("\n\nDo you want to continue even though the exported data will be invalid?") ).c_str(), "WARNING", MB_YESNO ) != IDYES )
            return;
    }

    if( MainForm->ExportBin() > 0 )   // ByteData[] has been changed
        HexForm->UpdateBin( MainForm->ByteData, MainForm->ByteDataLen );
}
//---------------------------------------------------------------------------

void __fastcall TExportForm::OutputBitOrderEditKeyPress(TObject *Sender,
      char &Key)
{
    if( Key == '\r' )
    {
        OutputBitOrderEditExit(Sender);
    }
}
//---------------------------------------------------------------------------
void __fastcall TExportForm::ROMLayoutRadioGroupClick(TObject *Sender)
{
    MainForm->ROM_Layout = (rom_layout_type)ROMLayoutRadioGroup->ItemIndex;

    if( ROMLayoutRadioGroup->ItemIndex < 2 )
        EnableAdditionalOptions();
    else
        DisableAdditionalOptions();

    if( MainForm->ExportBin() > 0 )   // ByteData[] has been changed
        HexForm->UpdateBin( MainForm->ByteData, MainForm->ByteDataLen );
}
//---------------------------------------------------------------------------
void __fastcall TExportForm::DisableAdditionalOptions(void)
{
    ReverseOutputsCheckbox->Enabled = false;
    ReverseWithinOutColCheckbox->Enabled = false;
    OutputBitOrderEdit->Enabled = false;
    OutputBitOrderLabel->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TExportForm::EnableAdditionalOptions(void)
{
    ReverseOutputsCheckbox->Enabled = true;
    ReverseWithinOutColCheckbox->Enabled = true;
    OutputBitOrderEdit->Enabled = true;
    OutputBitOrderLabel->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TExportForm::EndianRadioGroupClick(TObject *Sender)
{
    MainForm->Endianness = ExportForm->EndianRadioGroup->ItemIndex;

    if( MainForm->ExportBin() > 0 )   // ByteData[] has been changed
        HexForm->UpdateBin( MainForm->ByteData, MainForm->ByteDataLen );
}
//---------------------------------------------------------------------------

