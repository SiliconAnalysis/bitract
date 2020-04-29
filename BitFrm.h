//---------------------------------------------------------------------------

#ifndef BitFrmH
#define BitFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ievect.hpp"
#include "ieview.hpp"
#include "imageenview.hpp"
#include "histogrambox.hpp"
#include "imageenproc.hpp"
//---------------------------------------------------------------------------
class TBitForm : public TForm
{
__published:	// IDE-managed Components
    TImageEnVect *BitView;
    THistogramBox *HistogramBox;
    TImageEnProc *BitProc;
private:	// User declarations
public:		// User declarations
    __fastcall TBitForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TBitForm *BitForm;
//---------------------------------------------------------------------------
#endif
