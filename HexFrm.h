//---------------------------------------------------------------------------

#ifndef HexFrmH
#define HexFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class THexForm : public TForm
{
__published:	// IDE-managed Components
    TRichEdit *HexMemo;
    TPopupMenu *PopupMenu1;
    TMenuItem *Updatebyteview1;
    TMenuItem *Copy1;
    TMenuItem *Savebinfile1;
    void __fastcall HexMemoKeyPress(TObject *Sender, char &Key);
    void __fastcall Updatebyteview1Click(TObject *Sender);
    void __fastcall Copy1Click(TObject *Sender);
    void __fastcall Savebinfile1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall THexForm(TComponent* Owner);

    void __fastcall UpdateBin( unsigned char *ByteData, int ByteDataLen );

    unsigned char *PrevByteData;
    int PrevByteDataLen;
};
//---------------------------------------------------------------------------
extern PACKAGE THexForm *HexForm;
//---------------------------------------------------------------------------
#endif
