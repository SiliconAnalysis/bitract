//---------------------------------------------------------------------------

#ifndef ImageFrmH
#define ImageFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ieview.hpp"
#include "imageenio.hpp"
#include "imageenview.hpp"
#include <Dialogs.hpp>
#include <Menus.hpp>
#include <IniFiles.hpp>
#include "imageenproc.hpp"
#include "ievect.hpp"
//---------------------------------------------------------------------------
struct _ROMBit
{
    int Box;                    // hobj of the object for this box
    TRGB PixelSum;              // pixelsum for each of RGB
    int PixelSumG;              // gray pixelsum (selected channels mixed)
    int Value;                  // 0/1/-1
    TPoint Pos;                 // x,y position in grid of bits
    int PixelsAboveThreshold;
    int PixelsBelowThreshold;
    int RimLevel;
    int DotLevel;

    int Active;                 // 1 if this is a visible bit (analyze it), 0 if it is not a real bit
};
//---------------------------------------------------------------------------
class TImageForm : public TForm
{
__published:	// IDE-managed Components
    TMainMenu *MainMenu;
    TMenuItem *File1;
    TMenuItem *Saveimageas1;
    TSaveDialog *SaveImageDialog;
    TImageEnProc *ImageProc;
    TMenuItem *View1;
    TMenuItem *Zoom1001;
    TMenuItem *OpenImageButton;
    TMenuItem *Calcmultipliers1;
    TMenuItem *ApplyMultipliersButton;
    TOpenDialog *OpenImageDialog;
    TImageEnVect *ImageView;
    TMenuItem *ShowROMBox1;
    TMenuItem *Cursor1;
    TMenuItem *EditPolyline1;
    TMenuItem *FillROMBox1;
    TMenuItem *Objects1;
    TMenuItem *Clearallobjects1;
    TMenuItem *Transparency1;
    TMenuItem *Transparency501;
    TMenuItem *Transparency801;
    TMenuItem *Processing1;
    TMenuItem *Edit1;
    TMenuItem *Undo1;
    TMenuItem *Redo1;
    TMenuItem *Processing2;
    TMenuItem *Fittowindow1;
    TMenuItem *ZoomIn1;
    TMenuItem *ZoomOut1;
    TMenuItem *ResetROMBox1;
    TMenuItem *Exportbits1;
    TSaveDialog *ROMBitSaveDialog;
    TMenuItem *Loadsettings1;
    TMenuItem *Savesettings1;
    TOpenDialog *OpenSettingsDialog;
    TSaveDialog *SaveSettingsDialog;
    void __fastcall Saveimageas1Click(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall Zoom1001Click(TObject *Sender);
    void __fastcall ImageViewZoomIn(TObject *Sender, double &NewZoom);
    void __fastcall ImageViewZoomOut(TObject *Sender, double &NewZoom);
    void __fastcall ImageViewImageChange(TObject *Sender);
    void __fastcall Calcmultipliers1Click(TObject *Sender);
    void __fastcall ApplyMultipliersButtonClick(TObject *Sender);
    void __fastcall OpenImageButtonClick(TObject *Sender);
    void __fastcall ShowROMBox1Click(TObject *Sender);
    void __fastcall EditPolyline1Click(TObject *Sender);
    void __fastcall FillROMBox1Click(TObject *Sender);
    void __fastcall Clearallobjects1Click(TObject *Sender);
    void __fastcall Transparency1Click(TObject *Sender);
    void __fastcall Transparency501Click(TObject *Sender);
    void __fastcall Transparency801Click(TObject *Sender);
    void __fastcall ImageViewMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
    void __fastcall Processing1Click(TObject *Sender);
    void __fastcall Undo1Click(TObject *Sender);
    void __fastcall Redo1Click(TObject *Sender);
    void __fastcall ImageViewDblClick(TObject *Sender);
    void __fastcall ImageViewKeyPress(TObject *Sender, char &Key);
    void __fastcall ImageViewVectorialChanged(TObject *Sender);
    void __fastcall Fittowindow1Click(TObject *Sender);
    void __fastcall ZoomIn1Click(TObject *Sender);
    void __fastcall ZoomOut1Click(TObject *Sender);
    void __fastcall ResetROMBox1Click(TObject *Sender);
    void __fastcall FillBitView(void);
    void __fastcall Exportbits1Click(TObject *Sender);
    void __fastcall ImageViewObjectClick(TObject *Sender, int hobj);
    void __fastcall Loadsettings1Click(TObject *Sender);
    void __fastcall LoadSettings( AnsiString IniFilename );
    void __fastcall Savesettings1Click(TObject *Sender);
    void __fastcall SaveSettings(AnsiString IniFilename);

private:	// User declarations
public:		// User declarations
    __fastcall TImageForm(TComponent* Owner);

    void __fastcall UpdateCaption(void);

    double *MultiplierR;
    double *MultiplierG;
    double *MultiplierB;

    int ROMPolygon;
    int NumROMBits;
    struct _ROMBit *ROMBit;

    AnsiString OpenFilename;
    AnsiString WorkingDir;

    AnsiString PreviousFilename;        // filename loaded from settings file

    int XBoxesPatternLen;
    int *XBoxesPattern;
    int YBoxesPatternLen;
    int *YBoxesPattern;
};
//---------------------------------------------------------------------------
extern PACKAGE TImageForm *ImageForm;
//---------------------------------------------------------------------------
#endif
