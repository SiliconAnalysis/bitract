//---------------------------------------------------------------------------

#ifndef ROMBitSettingsFrmH
#define ROMBitSettingsFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include "histogrambox.hpp"
#include "ievect.hpp"
#include "ieview.hpp"
#include "imageenview.hpp"
#include "imageenproc.hpp"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TROMBitSettingsForm : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label6;
    TLabel *Label7;
    TEdit *BitsPerColEdit;
    TEdit *BitsPerRowEdit;
    TEdit *BoxWidthEdit;
    TEdit *BoxHeightEdit;
    TEdit *Threshold0Edit;
    TEdit *Threshold1Edit;
    TPageControl *PageControl;
    TTabSheet *TabSheet1;
    TTabSheet *TabSheet2;
    THistogramBox *HistogramBox;
    TImageEnVect *BitView;
    TImageEnProc *BitViewProc;
    TCheckBox *BitHistRedCheckBox;
    TCheckBox *BitHistGreenCheckBox;
    TCheckBox *BitHistBlueCheckBox;
    TCheckBox *BitHistGrayCheckBox;
    TCheckBox *RedCheckBox;
    TCheckBox *GreenCheckBox;
    TCheckBox *BlueCheckBox;
    TLabel *Label10;
    TLabel *Label11;
    TLabel *Label12;
    TGroupBox *BitBoxInfoGroupBox;
    TLabel *Label13;
    TLabel *Label14;
    TLabel *BitBoxIdxLabel;
    TLabel *PixelSumLabel;
    TLabel *Label8;
    TEdit *MinBright1Edit;
    TLabel *Label9;
    TEdit *MaxBright0Edit;
    TRadioGroup *BitAnalysisMethodRadioGroup;
        TLabel *Label5;
        TLabel *PixelsAboveThresholdLabel;
        TLabel *Label16;
        TLabel *PixelsBelowThresholdLabel;
    TLabel *Label15;
    TEdit *RimWidthEdit;
    TLabel *Label17;
    TEdit *DotWidthEdit;
    TLabel *Label18;
    TEdit *Dot1ThresholdEdit;
    TLabel *Label19;
    TEdit *Dot0ThresholdEdit;
    TLabel *Label20;
    TLabel *Label21;
    TLabel *Label22;
    TLabel *DotLevelLabel;
    TLabel *Label24;
    TLabel *RimLevelLabel;
    TLabel *Label23;
    TEdit *XBoxesToAnalyzeEdit;
    TLabel *Label25;
    TEdit *YBoxesToAnalyzeEdit;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall TabSheet1Resize(TObject *Sender);
    void __fastcall BitHistRedCheckBoxClick(TObject *Sender);
    void __fastcall BitsPerColEditKeyPress(TObject *Sender, char &Key);
    void __fastcall YBoxesToAnalyzeEditKeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
    __fastcall TROMBitSettingsForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TROMBitSettingsForm *ROMBitSettingsForm;
//---------------------------------------------------------------------------
#endif
