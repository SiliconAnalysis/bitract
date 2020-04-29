//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BitFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ievect"
#pragma link "ieview"
#pragma link "imageenview"
#pragma link "histogrambox"
#pragma link "imageenproc"
#pragma resource "*.dfm"
TBitForm *BitForm;
//---------------------------------------------------------------------------
__fastcall TBitForm::TBitForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
