//---------------------------------------------------------------------------

#ifndef LogFrmH
#define LogFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <SyncObjs.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TLogForm : public TForm
{
__published:	// IDE-managed Components
    TMemo *LogMemo;
    TMainMenu *MainMenu;
    TMenuItem *File1;
    TMenuItem *Exit1;
    TMenuItem *Window1;
    TMenuItem *Image1;
    TMenuItem *Histogram1;
    TMenuItem *ROMBitSettings1;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall Exit1Click(TObject *Sender);
    void __fastcall Image1Click(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall Histogram1Click(TObject *Sender);
    void __fastcall ROMBitSettings1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TLogForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TCriticalSection *StageCmd;       // TCriticalSection for accessing CmdToExec/X/Y/StepSize
//---------------------------------------------------------------------------
extern PACKAGE TLogForm *LogForm;
//---------------------------------------------------------------------------
#endif
