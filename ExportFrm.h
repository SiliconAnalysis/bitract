//---------------------------------------------------------------------------

#ifndef ExportFrmH
#define ExportFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TExportForm : public TForm
{
__published:	// IDE-managed Components
    TRadioGroup *ROMLayoutRadioGroup;
    TGroupBox *AdditionalOptionsGroupBox;
    TLabel *OutputBitOrderLabel;
    TCheckBox *ReverseOutputsCheckbox;
    TCheckBox *ReverseWithinOutColCheckbox;
    TEdit *OutputBitOrderEdit;
    TRadioGroup *EndianRadioGroup;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall ReverseOutputsCheckboxClick(TObject *Sender);
    void __fastcall ReverseWithinOutColCheckboxClick(TObject *Sender);
    void __fastcall OutputBitOrderEditExit(TObject *Sender);
    void __fastcall OutputBitOrderEditKeyPress(TObject *Sender, char &Key);
    void __fastcall ROMLayoutRadioGroupClick(TObject *Sender);

    void __fastcall DisableAdditionalOptions(void);
    void __fastcall EnableAdditionalOptions(void);
    void __fastcall EndianRadioGroupClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TExportForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TExportForm *ExportForm;
//---------------------------------------------------------------------------
#endif
