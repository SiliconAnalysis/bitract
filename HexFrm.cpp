//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "HexFrm.h"
#include "MainFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
THexForm *HexForm;
//---------------------------------------------------------------------------
__fastcall THexForm::THexForm(TComponent* Owner)
    : TForm(Owner)
{
    PrevByteData=NULL;
    PrevByteDataLen=0;
}
//---------------------------------------------------------------------------
void __fastcall THexForm::UpdateBin( unsigned char *ByteData, int ByteDataLen )
{
    int i;
    int LineNum;
    AnsiString HexLine;
    AnsiString AsciiLine;
    int AddrDigits = AnsiString().sprintf("%X",ByteDataLen).Length();
    int CurSelStart,CurSelLength;


    if( AddrDigits < 4 )
        AddrDigits = 4;    
    CurSelStart = HexMemo->SelStart;
    CurSelLength = HexMemo->SelLength;
    HexMemo->Lines->BeginUpdate();
    HexMemo->Lines->Clear();
    for( i=0,LineNum=0; i<ByteDataLen; i++ )
    {
        if( !(i%0x10) )
        {
            if( i )
            {
                HexLine += "  ";
                HexLine += AsciiLine;

                if( HexMemo->Lines->Count <= LineNum )
                    HexMemo->Lines->Add(HexLine);
                else if( HexMemo->Lines->Strings[LineNum] != HexLine )
                    HexMemo->Lines->Strings[LineNum] = HexLine;
                LineNum++;
            }

            HexLine.sprintf( "%0*X:", AddrDigits, i );
            AsciiLine="";
        }

//TODO - add colouring to changed bytes/nibbles
//        if( i>=PrevByteDataLen || ByteData[i] != PrevByteData[i] )
//            HexLine.cat_sprintf("`%02X", ByteData[i] );
//        else
//            HexLine.cat_sprintf(" %02X", ByteData[i] );

        HexLine.cat_sprintf(" %02X", ByteData[i] );
        AsciiLine.cat_sprintf("%c", ByteData[i]>=0x20 && ByteData[i]<0x7F ? ByteData[i] : '.' );
    }

    for( ; i%0x10; i++ )
        HexLine.cat_sprintf("   ");

    HexLine += "  ";
    HexLine += AsciiLine;
    if( HexMemo->Lines->Count <= LineNum )
        HexMemo->Lines->Add(HexLine);
    else if( HexMemo->Lines->Strings[LineNum] != HexLine )
        HexMemo->Lines->Strings[LineNum] = HexLine;
    LineNum++;

    HexMemo->Lines->EndUpdate();
    HexMemo->SelStart = CurSelStart;
    HexMemo->SelLength = CurSelLength;
    HexMemo->Perform(EM_SCROLLCARET, 0, 0);

    HexMemo->Update();

    if( ByteDataLen != PrevByteDataLen )
    {
        PrevByteDataLen = ByteDataLen;
        PrevByteData = new unsigned char[ PrevByteDataLen ];
        memset( PrevByteData, 0, PrevByteDataLen );
    }
    memmove(PrevByteData,ByteData,ByteDataLen);
    PrevByteDataLen = ByteDataLen;
}
//---------------------------------------------------------------------------
void __fastcall THexForm::HexMemoKeyPress(TObject *Sender, char &Key)
{
    Key = 0;
}
//---------------------------------------------------------------------------
void __fastcall THexForm::Updatebyteview1Click(TObject *Sender)
{
    UpdateBin( PrevByteData, PrevByteDataLen );
}
//---------------------------------------------------------------------------
void __fastcall THexForm::Copy1Click(TObject *Sender)
{
    HexMemo->CopyToClipboard();
}
//---------------------------------------------------------------------------
void __fastcall THexForm::Savebinfile1Click(TObject *Sender)
{
    MainForm->SaveBinButtonClick(Sender);
}
//---------------------------------------------------------------------------
