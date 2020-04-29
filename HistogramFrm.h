//---------------------------------------------------------------------------

#ifndef HistogramFrmH
#define HistogramFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "histogrambox.hpp"
//---------------------------------------------------------------------------
class THistogramForm : public TForm
{
__published:	// IDE-managed Components
    THistogramBox *HistogramBox;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *PixelsAt0RLabel;
    TLabel *PixelsAt0GLabel;
    TLabel *PixelsAt0BLabel;
    TLabel *PixelsAt255RLabel;
    TLabel *PixelsAt255GLabel;
    TLabel *PixelsAt255BLabel;
    TLabel *Label3;
    TLabel *PixelsMinRLabel;
    TLabel *PixelsMinGLabel;
    TLabel *PixelsMinBLabel;
    TLabel *Label4;
    TLabel *PixelsMaxRLabel;
    TLabel *PixelsMaxGLabel;
    TLabel *PixelsMaxBLabel;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label7;
    TLabel *Label8;
    TLabel *Label9;
    TLabel *Label10;
    TLabel *Label11;
    TLabel *Label12;
    TLabel *Label13;
    TLabel *Label14;
    TLabel *Label15;
    TLabel *Label16;
    void __fastcall HistogramBoxClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall FormResize(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall THistogramForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE THistogramForm *HistogramForm;
//---------------------------------------------------------------------------
#endif
