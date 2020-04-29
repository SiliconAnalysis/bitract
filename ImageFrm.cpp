//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <Math.hpp>
#pragma hdrstop

#include "ImageFrm.h"
#include "HistogramFrm.h"
#include "LogFrm.h"
#include "ROMBitSettingsFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ieview"
#pragma link "imageenio"
#pragma link "imageenview"
#pragma link "imageenproc"
#pragma link "ievect"
#pragma resource "*.dfm"
TImageForm *ImageForm;
//---------------------------------------------------------------------------
__fastcall TImageForm::TImageForm(TComponent* Owner)
    : TForm(Owner)
{
    MultiplierR=NULL;
    MultiplierG=NULL;
    MultiplierB=NULL;

    ROMPolygon=-1;

    ROMBit=NULL;
    NumROMBits=0;

    OpenFilename="";
    WorkingDir="";
    PreviousFilename="";

    XBoxesPatternLen=0;
    XBoxesPattern=NULL;
    YBoxesPatternLen=0;
    YBoxesPattern=NULL;
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::Saveimageas1Click(TObject *Sender)
{
    if( WorkingDir.Length() && SaveImageDialog->InitialDir != WorkingDir )
    {
        SaveImageDialog->InitialDir = WorkingDir;
        SaveImageDialog->FileName = "";
    }
    if( SaveImageDialog->Execute() != mrOk )
        return;

    WorkingDir = SaveImageDialog->FileName.SubString(1, SaveImageDialog->FileName.LastDelimiter( ":\\" ) );
    
    ImageView->IO->SaveToFile( SaveImageDialog->FileName );
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::FormCreate(TObject *Sender)
{
// read .ini file to setup form (x/y position etc)
    TIniFile *PicturizatronIni;

    PicturizatronIni = new TIniFile( ChangeFileExt( Application->ExeName, ".ini" ) );
    Top     = PicturizatronIni->ReadInteger( "ImageForm", "Top", 0 );
    Left    = PicturizatronIni->ReadInteger( "ImageForm", "Left", LogForm->Left + LogForm->Width );
    Width   = PicturizatronIni->ReadInteger( "ImageForm", "Width", Width );
    Height  = PicturizatronIni->ReadInteger( "ImageForm", "Height", Height );

    WorkingDir = PicturizatronIni->ReadString( "Image", "WorkingDir", "" );

    LoadSettings( ChangeFileExt( Application->ExeName, ".ini" ) );

    delete PicturizatronIni;
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::FormDestroy(TObject *Sender)
{
    if(ROMBit)
        delete[] ROMBit;
    ROMBit=NULL;
    NumROMBits=0;

// write .ini file to save form setup (x/y position etc)
    TIniFile *PicturizatronIni;

    PicturizatronIni = new TIniFile( ChangeFileExt( Application->ExeName, ".ini" ) );
    PicturizatronIni->WriteInteger( "ImageForm", "Top", Top );          // save top/left of form
    PicturizatronIni->WriteInteger( "ImageForm", "Left", Left );
    PicturizatronIni->WriteInteger( "ImageForm", "Width", Width );      // save width/height of form
    PicturizatronIni->WriteInteger( "ImageForm", "Height", Height );

    PicturizatronIni->WriteString( "Image", "WorkingDir", WorkingDir );

    delete PicturizatronIni;

    SaveSettings( ChangeFileExt( Application->ExeName, ".ini" ) );

    XBoxesPatternLen=0;
    if( XBoxesPattern )
        delete[] XBoxesPattern;
    XBoxesPattern=NULL;
    YBoxesPatternLen=0;
    if( YBoxesPattern )
        delete[] YBoxesPattern;
    YBoxesPattern=NULL;
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::Zoom1001Click(TObject *Sender)
{
    ImageView->Zoom = 100.0;
    UpdateCaption();
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::ImageViewZoomIn(TObject *Sender,
      double &NewZoom)
{
    UpdateCaption();
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::ImageViewZoomOut(TObject *Sender,
      double &NewZoom)
{
    UpdateCaption();
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::UpdateCaption(void)
{
    Caption = (AnsiString)"Image "+ImageView->IEBitmap->Width+"x"+ImageView->IEBitmap->Height+" ["+RoundTo(ImageView->Zoom,0)+"\%]";
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::ImageViewImageChange(TObject *Sender)
{
    THistogram ImageHistogram;


    HistogramForm->HistogramBox->Update();

    ImageView->Proc->GetHistogram( &ImageHistogram );

    HistogramForm->PixelsAt0RLabel->Caption = ImageHistogram[0].R;
    HistogramForm->PixelsAt0GLabel->Caption = ImageHistogram[0].G;
    HistogramForm->PixelsAt0BLabel->Caption = ImageHistogram[0].B;

    HistogramForm->PixelsAt255RLabel->Caption = ImageHistogram[255].R;
    HistogramForm->PixelsAt255GLabel->Caption = ImageHistogram[255].G;
    HistogramForm->PixelsAt255BLabel->Caption = ImageHistogram[255].B;


    int MinR,MinG,MinB;
    int MaxR,MaxG,MaxB;

    for(MinR=0; !ImageHistogram[MinR].R; MinR++)
        ;
    for(MinG=0; !ImageHistogram[MinG].G; MinG++)
        ;
    for(MinB=0; !ImageHistogram[MinB].B; MinB++)
        ;

    for(MaxR=255; !ImageHistogram[MaxR].R; MaxR--)
        ;
    for(MaxG=255; !ImageHistogram[MaxG].G; MaxG--)
        ;
    for(MaxB=255; !ImageHistogram[MaxB].B; MaxB--)
        ;

    HistogramForm->PixelsMinRLabel->Caption = MinR;
    HistogramForm->PixelsMinGLabel->Caption = MinG;
    HistogramForm->PixelsMinBLabel->Caption = MinB;

    HistogramForm->PixelsMaxRLabel->Caption = MaxR;
    HistogramForm->PixelsMaxGLabel->Caption = MaxG;
    HistogramForm->PixelsMaxBLabel->Caption = MaxB;

    UpdateCaption();
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::Calcmultipliers1Click(TObject *Sender)
{
    THistogram RefHisto;
    TRGB RefMin, RefMax;
    int RowCounter,ColCounter;


    ImageView->Cursor = crHourGlass;
    ImageView->Update();

// get reference image histogram
    ImageView->Proc->GetHistogram( &RefHisto );

// calc RefMin.r
    for( RefMin.r=0; RefMin.r<255; RefMin.r++ )
        if( RefHisto[ RefMin.r ].R )
            break;

// calc RefMax.r
    for( RefMax.r=255; RefMax.r; RefMax.r-- )
        if( RefHisto[ RefMax.r ].R )
            break;

// calc RefMin.g
    for( RefMin.g=0; RefMin.g<255; RefMin.g++ )
        if( RefHisto[ RefMin.g ].G )
            break;

// calc RefMax.g
    for( RefMax.g=255; RefMax.g; RefMax.g-- )
        if( RefHisto[ RefMax.g ].G )
            break;

// calc RefMin.b
    for( RefMin.b=0; RefMin.b<255; RefMin.b++ )
        if( RefHisto[ RefMin.b ].B )
            break;

// calc RefMax.b
    for( RefMax.b=255; RefMax.b; RefMax.b-- )
        if( RefHisto[ RefMax.b ].B )
            break;


//    LogForm->LogMemo->Lines->Add( (AnsiString)"min: "+RefMin.r+" "+RefMin.g+" "+RefMin.b );
//    LogForm->LogMemo->Lines->Add( (AnsiString)"max: "+RefMax.r+" "+RefMax.g+" "+RefMax.b );


    if( MultiplierR )
        delete[] MultiplierR;
    if( MultiplierG )
        delete[] MultiplierG;
    if( MultiplierB )
        delete[] MultiplierB;

    MultiplierR = new double[ImageView->IEBitmap->Width * ImageView->IEBitmap->Height];
    MultiplierG = new double[ImageView->IEBitmap->Width * ImageView->IEBitmap->Height];
    MultiplierB = new double[ImageView->IEBitmap->Width * ImageView->IEBitmap->Height];


// loop to calculate Multiplier[] values
    for( RowCounter=0; RowCounter<ImageView->IEBitmap->Height; RowCounter++ )
    {
        for( ColCounter=0; ColCounter<ImageView->IEBitmap->Width; ColCounter++ )
        {
            MultiplierR[ (RowCounter*ImageView->IEBitmap->Width)+ColCounter ] = ( (double)RefMax.r / (double)ImageView->IEBitmap->Pixels_ie24RGB[ColCounter][RowCounter].r );
            MultiplierG[ (RowCounter*ImageView->IEBitmap->Width)+ColCounter ] = ( (double)RefMax.g / (double)ImageView->IEBitmap->Pixels_ie24RGB[ColCounter][RowCounter].g );
            MultiplierB[ (RowCounter*ImageView->IEBitmap->Width)+ColCounter ] = ( (double)RefMax.b / (double)ImageView->IEBitmap->Pixels_ie24RGB[ColCounter][RowCounter].b );
        }
    }


// done
    ImageView->Cursor = crDefault;
    ImageView->Update();
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::ApplyMultipliersButtonClick(TObject *Sender)
{
    int RowCounter,ColCounter;
    int NewPixelValue;
    int MaxR=0,MaxG=0,MaxB=0;
    int CutR=0,CutG=0,CutB=0;

    if( !MultiplierR || !MultiplierG || !MultiplierB )
        return;

    ImageView->Cursor = crHourGlass;
    ImageView->Update();


// loop to apply Multiplier[] values
    for( RowCounter=0; RowCounter<ImageView->IEBitmap->Height; RowCounter++ )
    {
//        if( !RowCounter%50 )
//            ImageView->Update();


        for( ColCounter=0; ColCounter<ImageView->IEBitmap->Width; ColCounter++ )
        {
            NewPixelValue = (double)ImageView->IEBitmap->Pixels_ie24RGB[ColCounter][RowCounter].r * MultiplierR[ (RowCounter*ImageView->IEBitmap->Width)+ColCounter ];
            if( NewPixelValue > 0xFF )
            {
                CutR++;
                if(NewPixelValue>MaxR)
                    MaxR=NewPixelValue;
                NewPixelValue = 0xFF;
            }
            (*ImageView->IEBitmap->PPixels_ie24RGB[ColCounter][RowCounter]).r = NewPixelValue;

            NewPixelValue = (double)ImageView->IEBitmap->Pixels_ie24RGB[ColCounter][RowCounter].g * MultiplierG[ (RowCounter*ImageView->IEBitmap->Width)+ColCounter ];
            if( NewPixelValue > 0xFF )
            {
                CutG++;
                if(NewPixelValue>MaxG)
                    MaxG=NewPixelValue;
                NewPixelValue = 0xFF;
            }
            (*ImageView->IEBitmap->PPixels_ie24RGB[ColCounter][RowCounter]).g = NewPixelValue;

            NewPixelValue = (double)ImageView->IEBitmap->Pixels_ie24RGB[ColCounter][RowCounter].b * MultiplierB[ (RowCounter*ImageView->IEBitmap->Width)+ColCounter ];
            if( NewPixelValue > 0xFF )
            {
                CutB++;
                if(NewPixelValue>MaxB)
                    MaxB=NewPixelValue;
                NewPixelValue = 0xFF;
            }
            (*ImageView->IEBitmap->PPixels_ie24RGB[ColCounter][RowCounter]).b = NewPixelValue;
        }
    }

// done
    ImageView->Cursor = crDefault;
    Update();

//    LogForm->LogMemo->Lines->Add( (AnsiString)CutR+" "+CutG+" "+CutB );
//    LogForm->LogMemo->Lines->Add( (AnsiString)MaxR+" "+MaxG+" "+MaxB );
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::OpenImageButtonClick(TObject *Sender)
{
    if( WorkingDir.Length() && OpenImageDialog->InitialDir != WorkingDir )
    {
        OpenImageDialog->InitialDir = WorkingDir;
        OpenImageDialog->FileName = "";
    }

    if( OpenImageDialog->Execute() != mrOk )
        return;

    WorkingDir = OpenImageDialog->FileName.SubString(1, OpenImageDialog->FileName.LastDelimiter( ":\\" ) );

    OpenFilename = OpenImageDialog->FileName;
    ImageView->IO->LoadFromFile( OpenFilename.c_str() );

    LogForm->LogMemo->Lines->Add("Image loaded - Select \"Area Of Interest -> Show Area Of Interest overlay\" to set the area of interest.");
    LogForm->LogMemo->Lines->Add("");
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::ShowROMBox1Click(TObject *Sender)
{
    int i;
    int minx,miny;


    if(ROMPolygon > -1)
    {       // ROMPolygon already exists  - delete objects before recreating it
        Clearallobjects1Click(Sender);
        ImageView->UnSelAllObjects();
        ImageView->OnVectorialChanged = NULL;
        ImageView->RemoveAllObjects();
        ROMPolygon = -1;
        ImageView->OnVectorialChanged = ImageViewVectorialChanged;
    }

    ROMPolygon = ImageView->AddNewObject();

    TPoint LinePoints[4];

    TIniFile *ini;
    ini = new TIniFile( ChangeFileExt( Application->ExeName, ".ini" ) );
    LinePoints[0].x = ini->ReadInteger( "ROMPolygon", "0x", 100 );
    LinePoints[0].y = ini->ReadInteger( "ROMPolygon", "0y", 100 );
    LinePoints[1].x = ini->ReadInteger( "ROMPolygon", "1x", 200 );
    LinePoints[1].y = ini->ReadInteger( "ROMPolygon", "1y", 100 );
    LinePoints[2].x = ini->ReadInteger( "ROMPolygon", "2x", 200 );
    LinePoints[2].y = ini->ReadInteger( "ROMPolygon", "2y", 200 );
    LinePoints[3].x = ini->ReadInteger( "ROMPolygon", "3x", 100 );
    LinePoints[3].y = ini->ReadInteger( "ROMPolygon", "3y", 200 );
    delete ini;

    if( ImageView->IEBitmap->Width > 10 )
    {
    // check if LinePoints[0..3] fit within image boundaries
        for( i=0; i<4; i++ )
        {
            if( LinePoints[i].x >= ImageView->IEBitmap->Width || LinePoints[i].y >= ImageView->IEBitmap->Height )
                break;
        }
        if( i<4 )   // at least one point is outside of image boundary
        {
            minx=LinePoints[0].x;
            miny=LinePoints[0].y;
            for( i=1; i<4; i++ )
            {
                if( LinePoints[i].x < minx )
                    minx = LinePoints[i].x;
                if( LinePoints[i].y < miny )
                    miny = LinePoints[i].y;
            }
            for( i=0; i<4; i++ )
            {
                LinePoints[i].x -= (minx-10);       // adjust ROMBox so it will fit within a small image
                LinePoints[i].y -= (miny-10);
            }

            LogForm->LogMemo->Lines->Add("WARNING: The Area Of Interest overlay was outside image boundaries.");
            LogForm->LogMemo->Lines->Add("The position of the AOI has been adjusted to be visible within the current image.");
        }
    }

    ImageView->ObjKind[ROMPolygon] = iekPOLYLINE;
    ImageView->ObjPenWidth[ROMPolygon] = 1;
    ImageView->ObjPenColor[ROMPolygon] = clBlue;
    ImageView->ObjStyle[ROMPolygon] = TIEVStyle()<<ievsSelectable<<ievsMoveable<<ievsSizeable<<ievsVisible;
    ImageView->ObjName[ROMPolygon] = "ROMPolygon";
    ImageView->SetObjPolylinePoints(ROMPolygon,LinePoints,3);
    ImageView->ObjPolylineClosed[ROMPolygon] = true;


    ImageView->MouseInteractVt=TIEMouseInteractVt()<<miObjectSelect;
    ImageView->SelAllObjects();

    ImageView->OnVectorialChanged = ImageViewVectorialChanged;


    LogForm->LogMemo->Lines->Add("Move or resize the area of interest so the box exactly lines up with the bits you want to extract.");
    LogForm->LogMemo->Lines->Add("Select \"Cursor -> Adjust box corners\" to drag box corners to adjust for rotation.");
    LogForm->LogMemo->Lines->Add("Ensure \"Bits across AOI\" and \"Bits up and down AOI\" are correct, then select \"Area Of Interest -> Analyze bits within AOI\".");
    LogForm->LogMemo->Lines->Add("");
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::EditPolyline1Click(TObject *Sender)
{
    if( EditPolyline1->Checked )
        ImageView->MouseInteractVt=TIEMouseInteractVt()<<miObjectSelect;
    else
        ImageView->MouseInteractVt=TIEMouseInteractVt()<<miEditPolyline;

    EditPolyline1->Checked = !EditPolyline1->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::FillROMBox1Click(TObject *Sender)
{
    TPoint TL,TR,BL,BR;
    bool UseRed,UseGreen,UseBlue;
    int BitsPerCol;
    int BitsPerRow;

    int BoxWidth;
    int BoxHeight;

    int Threshold0;
    int Threshold1;

    int MinBright1,MaxBright0;
    int BitAnalysisMethod;

    int Dot1Threshold;
    int Dot0Threshold;
    int RimWidth;
    int DotWidth;

    int PixelSumR;
    int PixelSumG;
    int PixelSumB;

    int AboveThresholdR;
    int AboveThresholdG;
    int AboveThresholdB;
    int BelowThresholdR;
    int BelowThresholdG;
    int BelowThresholdB;

    int PixelSumGray;
    int NumChannels;
    int NumRimPixels;
    int NumDotPixels;


    int FullColCount;   // total # of cols including gap between bits
    int FullRowCount;
    int i,n;

    int NumInvalidBits;


    if( ImageView->IEBitmap->Width<1 || ImageView->IEBitmap->Height<1 )
    {
        LogForm->LogMemo->Lines->Add("Cannot analyze bits without an image loaded.");
        LogForm->LogMemo->Lines->Add("");
        return;
    }
    if( ROMPolygon < 0 )
    {
        LogForm->LogMemo->Lines->Add("Cannot analyze bits when Area Of Interest overlay is not shown.");
        LogForm->LogMemo->Lines->Add("");
        return;
    }


    LogForm->LogMemo->Lines->Add("Analyzing bits within Area of Interest ....");


    BitsPerCol = ROMBitSettingsForm->BitsPerColEdit->Text.ToIntDef(64);
    BitsPerRow = ROMBitSettingsForm->BitsPerRowEdit->Text.ToIntDef(8);
    BoxWidth = ROMBitSettingsForm->BoxWidthEdit->Text.ToIntDef(5);
    BoxHeight = ROMBitSettingsForm->BoxHeightEdit->Text.ToIntDef(5);

    Threshold0 = ROMBitSettingsForm->Threshold0Edit->Text.ToIntDef(1500);
    Threshold1 = ROMBitSettingsForm->Threshold1Edit->Text.ToIntDef(1700);

    Dot1Threshold = ROMBitSettingsForm->Dot1ThresholdEdit->Text.ToIntDef(0);
    Dot0Threshold = ROMBitSettingsForm->Dot0ThresholdEdit->Text.ToIntDef(0);
    RimWidth = ROMBitSettingsForm->RimWidthEdit->Text.ToIntDef(1);
    DotWidth = ROMBitSettingsForm->DotWidthEdit->Text.ToIntDef(1);


//    BitRowOfs = ROMBitSettingsForm->BitRowOfsEdit->Text.ToIntDef(0);

/*
//settings for st19
    FullColCount = (Ceil(BitsPerCol/64.0)- 1 )*3 + BitsPerCol;
    if(FullColCount<BitsPerCol)
        FullColCount=BitsPerCol;
    FullRowCount = (Ceil(BitsPerRow/8.0)- (BitRowOfs?0:1) )*2 + BitsPerRow;
    if(FullRowCount<BitsPerRow)
        FullRowCount=BitsPerRow;
*/
//    FullColCount = (Ceil(BitsPerCol/32.0)- 1 )*3 + BitsPerCol;
    FullColCount = BitsPerCol;
    if(FullColCount<BitsPerCol)
        FullColCount=BitsPerCol;
    FullRowCount = BitsPerRow;

    UseRed = ROMBitSettingsForm->RedCheckBox->Checked;
    UseGreen = ROMBitSettingsForm->GreenCheckBox->Checked;
    UseBlue = ROMBitSettingsForm->BlueCheckBox->Checked;

    MinBright1 = ROMBitSettingsForm->MinBright1Edit->Text.ToIntDef(0);
    MaxBright0 = ROMBitSettingsForm->MaxBright0Edit->Text.ToIntDef(0);
    BitAnalysisMethod = ROMBitSettingsForm->BitAnalysisMethodRadioGroup->ItemIndex;

    XBoxesPatternLen=0;
    if( XBoxesPattern )
        delete[] XBoxesPattern;
    XBoxesPattern=NULL;
    YBoxesPatternLen=0;
    if( YBoxesPattern )
        delete[] YBoxesPattern;
    YBoxesPattern=NULL;

    XBoxesPatternLen = ROMBitSettingsForm->XBoxesToAnalyzeEdit->Text.Length();
    if( XBoxesPatternLen > 0 )
    {
        XBoxesPattern = new int[XBoxesPatternLen];
        if( !XBoxesPattern )
        {
            Application->MessageBoxA("Memory allocation error! aborting FillROMBox.","ERROR",MB_OK);
            return;
        }

        n = 0;
        for( i=0; i<XBoxesPatternLen; i++ )
        {
            switch( ROMBitSettingsForm->XBoxesToAnalyzeEdit->Text[1+i] )
            {
                case '1':
                    XBoxesPattern[n++] = 1;
                    break;

                case '0':
                    XBoxesPattern[n++] = 0;
                    break;
            }
        }
        XBoxesPatternLen = n;
    }
    YBoxesPatternLen = ROMBitSettingsForm->YBoxesToAnalyzeEdit->Text.Length();
    if( YBoxesPatternLen > 0 )
    {
        YBoxesPattern = new int[YBoxesPatternLen];
        if( !YBoxesPattern )
        {
            Application->MessageBoxA("Memory allocation error! aborting FillROMBox.","ERROR",MB_OK);
            return;
        }

        n = 0;
        for( i=0; i<YBoxesPatternLen; i++ )
        {
            switch( ROMBitSettingsForm->YBoxesToAnalyzeEdit->Text[1+i] )
            {
                case '1':
                    YBoxesPattern[n++] = 1;
                    break;

                case '0':
                    YBoxesPattern[n++] = 0;
                    break;
            }
        }
        YBoxesPatternLen = n;
    }


    TL = ImageView->ObjPolylinePoints[ROMPolygon][0];
    TR = ImageView->ObjPolylinePoints[ROMPolygon][1];
    BR = ImageView->ObjPolylinePoints[ROMPolygon][2];
    BL = ImageView->ObjPolylinePoints[ROMPolygon][3];


    NumROMBits = BitsPerRow * BitsPerCol;
    if(ROMBit)
    {
        delete[] ROMBit;
        ROMBit=NULL;
    }
    ROMBit = new struct _ROMBit[NumROMBits];


    for( int i=ImageView->ObjectsCount-1; i; i-- )
    {
        if( ImageView->ObjKind[i] != iekPOLYLINE )
            ImageView->RemoveObject(i);
    }

    for( int RowCounter=0,RowCounterOfs=0; RowCounter<BitsPerRow; RowCounter++,RowCounterOfs++ )
    {
        for( int ColCounter=0, ColCounterOfs=0; ColCounter<BitsPerCol; ColCounter++, ColCounterOfs++ )
        {
            int ROMBitIdx = RowCounter*BitsPerCol+ColCounter;

            // check if this ROMBit is active

            ROMBit[ROMBitIdx].Active = 1;

            if( XBoxesPatternLen && !XBoxesPattern[ ColCounter % XBoxesPatternLen ] )
                ROMBit[ROMBitIdx].Active = 0;
            if( YBoxesPatternLen && !YBoxesPattern[ RowCounter % YBoxesPatternLen ] )
                ROMBit[ROMBitIdx].Active = 0;

            if( !ROMBit[ROMBitIdx].Active )
                continue;

            TPoint BitPos;

            double xOfs = (double)RowCounterOfs * (((double)BL.x-TL.x)/(double)FullRowCount);        // offset to compensate for rotation
            BitPos.x = TL.x + (double)(ColCounterOfs)* (((double)TR.x-TL.x)/(double)(FullColCount-1)) + RoundTo(xOfs,0);

            double yOfs = (double)ColCounterOfs * (((double)TR.y-TL.y)/(double)FullColCount);        // offset to compensate for rotation
            BitPos.y = TL.y + (double)(RowCounterOfs)* (((double)BL.y-TL.y)/(double)(FullRowCount-1)) + RoundTo(yOfs,0);

            ImageView->ObjKind[-1] = iekBOX;
            ImageView->ObjLeft[-1] = BitPos.x-BoxWidth/2;
            ImageView->ObjTop[-1] = BitPos.y-BoxHeight/2;
            ImageView->ObjHeight[-1] = BoxHeight;
            ImageView->ObjWidth[-1] = BoxWidth;
            ImageView->ObjPenColor[-1]  = clRed;
            ImageView->ObjStyle[-1] = TIEVStyle()<<ievsVisible;

            ImageView->ObjTransparency[-1] = 128;      // set transparency to 50%

// fill in this ROMBit[]
//            int ROMBitIdx = BitRowCounter*BitsPerCol+BitColCounter;
            ROMBit[ROMBitIdx].Box=ImageView->AddNewObject();
            ROMBit[ROMBitIdx].Value=-1;
            ROMBit[ROMBitIdx].PixelSumG=0;
            ROMBit[ROMBitIdx].PixelSum.r=0;
            ROMBit[ROMBitIdx].PixelSum.g=0;
            ROMBit[ROMBitIdx].PixelSum.b=0;
            ROMBit[ROMBitIdx].Pos.x=ColCounter;
            ROMBit[ROMBitIdx].Pos.y=RowCounter;



// calc pixelsums
            PixelSumR=0;
            PixelSumG=0;
            PixelSumB=0;

            AboveThresholdR=0;
            AboveThresholdG=0;
            AboveThresholdB=0;
            BelowThresholdR=0;
            BelowThresholdG=0;
            BelowThresholdB=0;

            for( int BoxRow=0; BoxRow<BoxHeight; BoxRow++ )
            {
                for( int BoxCol=0; BoxCol<BoxWidth; BoxCol++ )
                {
                    if( UseRed )
                        PixelSumR += ImageView->IEBitmap->Pixels[ImageView->ObjLeft[-2]+BoxCol][ImageView->ObjTop[-2]+BoxRow].r;
                    if( UseGreen )
                        PixelSumG += ImageView->IEBitmap->Pixels[ImageView->ObjLeft[-2]+BoxCol][ImageView->ObjTop[-2]+BoxRow].g;
                    if( UseBlue )
                        PixelSumB += ImageView->IEBitmap->Pixels[ImageView->ObjLeft[-2]+BoxCol][ImageView->ObjTop[-2]+BoxRow].b;
                }
            }

            if( UseRed )
                ROMBit[ROMBitIdx].PixelSum.r = PixelSumR / (BoxHeight*BoxWidth);
            if( UseGreen )
                ROMBit[ROMBitIdx].PixelSum.g = PixelSumG / (BoxHeight*BoxWidth);
            if( UseBlue )
                ROMBit[ROMBitIdx].PixelSum.b = PixelSumB / (BoxHeight*BoxWidth);

            PixelSumGray=0;
            NumChannels=0;
            ROMBit[ROMBitIdx].PixelsAboveThreshold=0;
            ROMBit[ROMBitIdx].PixelsBelowThreshold=0;

            if( UseRed )
            {
                PixelSumGray += ROMBit[ROMBitIdx].PixelSum.r;
                NumChannels++;
            }
            if( UseGreen )
            {
                PixelSumGray += ROMBit[ROMBitIdx].PixelSum.g;
                NumChannels++;
            }
            if( UseBlue )
            {
                PixelSumGray += ROMBit[ROMBitIdx].PixelSum.b;
                NumChannels++;
            }

            if( NumChannels )
            {
                ROMBit[ROMBitIdx].PixelSumG = PixelSumGray / NumChannels;
            }
            else
                ROMBit[ROMBitIdx].PixelSumG = PixelSumGray;


            switch( BitAnalysisMethod )
            {
                case 2:     // dot finder

            ROMBit[ROMBitIdx].RimLevel = 0;
            ROMBit[ROMBitIdx].DotLevel = 0;
            NumRimPixels=0;
            NumDotPixels=0;
            for( int BoxRow=0; BoxRow<BoxHeight; BoxRow++ )
            {
                for( int BoxCol=0; BoxCol<BoxWidth; BoxCol++ )
                {
                    if( BoxRow < RimWidth || BoxHeight - BoxRow <= RimWidth || BoxCol < RimWidth || BoxWidth - BoxCol <= RimWidth )
                    {
                        if( UseRed )
                            ROMBit[ROMBitIdx].RimLevel +=  ImageView->IEBitmap->Pixels[ImageView->ObjLeft[-2]+BoxCol][ImageView->ObjTop[-2]+BoxRow].r;
                        if( UseGreen )
                            ROMBit[ROMBitIdx].RimLevel +=  ImageView->IEBitmap->Pixels[ImageView->ObjLeft[-2]+BoxCol][ImageView->ObjTop[-2]+BoxRow].g;
                        if( UseBlue )
                            ROMBit[ROMBitIdx].RimLevel +=  ImageView->IEBitmap->Pixels[ImageView->ObjLeft[-2]+BoxCol][ImageView->ObjTop[-2]+BoxRow].b;
                        NumRimPixels++;
                    }

                    if( BoxRow >= ((BoxHeight/2.0) - (DotWidth/2.0) + 0.5) && BoxRow <= ((BoxHeight/2.0) + (DotWidth/2.0) + 0.5) && BoxCol >= ((BoxWidth/2.0) - (DotWidth/2.0) + 0.5) && BoxCol <= ((BoxWidth/2.0) + (DotWidth/2.0) + 0.5) )
                    {
                        if( UseRed )
                            ROMBit[ROMBitIdx].DotLevel +=  ImageView->IEBitmap->Pixels[ImageView->ObjLeft[-2]+BoxCol][ImageView->ObjTop[-2]+BoxRow].r;
                        if( UseGreen )
                            ROMBit[ROMBitIdx].DotLevel +=  ImageView->IEBitmap->Pixels[ImageView->ObjLeft[-2]+BoxCol][ImageView->ObjTop[-2]+BoxRow].g;
                        if( UseBlue )
                            ROMBit[ROMBitIdx].DotLevel +=  ImageView->IEBitmap->Pixels[ImageView->ObjLeft[-2]+BoxCol][ImageView->ObjTop[-2]+BoxRow].b;
                        NumDotPixels++;
                    }
                }
            }

            NumChannels=0;

            if( UseRed )
                NumChannels++;
            if( UseGreen )
                NumChannels++;
            if( UseBlue )
                NumChannels++;

            if( NumChannels )
            {
                ROMBit[ROMBitIdx].RimLevel /= NumChannels;
                ROMBit[ROMBitIdx].DotLevel /= NumChannels;
            }
            if( NumRimPixels )
                ROMBit[ROMBitIdx].RimLevel /= NumRimPixels;
            if( NumDotPixels )
                ROMBit[ROMBitIdx].DotLevel /= NumDotPixels;

                    if( ROMBit[ROMBitIdx].DotLevel - ROMBit[ROMBitIdx].RimLevel <= Dot0Threshold )
                    {
                        ROMBit[ROMBitIdx].Value = 0;
                        ImageView->ObjPenColor[ROMBit[ROMBitIdx].Box]  = clBlue;
                    }
                    else if( ROMBit[ROMBitIdx].DotLevel - ROMBit[ROMBitIdx].RimLevel >= Dot1Threshold )
                    {
                        ROMBit[ROMBitIdx].Value = 1;
                        ImageView->ObjPenColor[ROMBit[ROMBitIdx].Box] = clYellow;
                    }
                    break;


                case 1:     // # of bright pixels within bit-box
// calc pixelsums
            PixelSumR=0;
            PixelSumG=0;
            PixelSumB=0;

            AboveThresholdR=0;
            AboveThresholdG=0;
            AboveThresholdB=0;
            BelowThresholdR=0;
            BelowThresholdG=0;
            BelowThresholdB=0;

            for( int BoxRow=0; BoxRow<BoxHeight; BoxRow++ )
            {
                for( int BoxCol=0; BoxCol<BoxWidth; BoxCol++ )
                {
                    if( UseRed && ImageView->IEBitmap->Pixels[ImageView->ObjLeft[-2]+BoxCol][ImageView->ObjTop[-2]+BoxRow].r >= Threshold1 )
                        AboveThresholdR++;
                    if( UseGreen && ImageView->IEBitmap->Pixels[ImageView->ObjLeft[-2]+BoxCol][ImageView->ObjTop[-2]+BoxRow].g >= Threshold1 )
                        AboveThresholdG++;
                    if( UseBlue && ImageView->IEBitmap->Pixels[ImageView->ObjLeft[-2]+BoxCol][ImageView->ObjTop[-2]+BoxRow].b >= Threshold1 )
                        AboveThresholdB++;
                    if( UseRed && ImageView->IEBitmap->Pixels[ImageView->ObjLeft[-2]+BoxCol][ImageView->ObjTop[-2]+BoxRow].r <= Threshold0 )
                        BelowThresholdR++;
                    if( UseGreen && ImageView->IEBitmap->Pixels[ImageView->ObjLeft[-2]+BoxCol][ImageView->ObjTop[-2]+BoxRow].g <= Threshold0 )
                        BelowThresholdG++;
                    if( UseBlue && ImageView->IEBitmap->Pixels[ImageView->ObjLeft[-2]+BoxCol][ImageView->ObjTop[-2]+BoxRow].b <= Threshold0 )
                        BelowThresholdB++;
                }
            }

            NumChannels=0;
            ROMBit[ROMBitIdx].PixelsAboveThreshold=0;
            ROMBit[ROMBitIdx].PixelsBelowThreshold=0;

            if( UseRed )
            {
                ROMBit[ROMBitIdx].PixelsAboveThreshold += AboveThresholdR;
                ROMBit[ROMBitIdx].PixelsBelowThreshold += BelowThresholdR;
                NumChannels++;
            }
            if( UseGreen )
            {
                ROMBit[ROMBitIdx].PixelsAboveThreshold += AboveThresholdG;
                ROMBit[ROMBitIdx].PixelsBelowThreshold += BelowThresholdG;
                NumChannels++;
            }
            if( UseBlue )
            {
                ROMBit[ROMBitIdx].PixelsAboveThreshold += AboveThresholdB;
                ROMBit[ROMBitIdx].PixelsBelowThreshold += BelowThresholdB;
                NumChannels++;
            }

            if( NumChannels )
            {
                ROMBit[ROMBitIdx].PixelsAboveThreshold /= NumChannels;
                ROMBit[ROMBitIdx].PixelsBelowThreshold /= NumChannels;
            }


                    if( ROMBit[ROMBitIdx].PixelsAboveThreshold <= MaxBright0 )
                    {
                        ROMBit[ROMBitIdx].Value = 0;
                        ImageView->ObjPenColor[ROMBit[ROMBitIdx].Box]  = clBlue;
                    }
                    else if( ROMBit[ROMBitIdx].PixelsAboveThreshold >= MinBright1 )
                    {
                        ROMBit[ROMBitIdx].Value = 1;
                        ImageView->ObjPenColor[ROMBit[ROMBitIdx].Box] = clYellow;
                    }
                    break;


                case 0: // avg. brightness within bit-box
                default:
/*
// calc pixelsums
            PixelSumR=0;
            PixelSumG=0;
            PixelSumB=0;

            AboveThresholdR=0;
            AboveThresholdG=0;
            AboveThresholdB=0;
            BelowThresholdR=0;
            BelowThresholdG=0;
            BelowThresholdB=0;

            for( int BoxRow=0; BoxRow<BoxHeight; BoxRow++ )
            {
                for( int BoxCol=0; BoxCol<BoxWidth; BoxCol++ )
                {
                    if( UseRed )
                        PixelSumR += ImageView->IEBitmap->Pixels[ImageView->ObjLeft[-2]+BoxCol][ImageView->ObjTop[-2]+BoxRow].r;
                    if( UseGreen )
                        PixelSumG += ImageView->IEBitmap->Pixels[ImageView->ObjLeft[-2]+BoxCol][ImageView->ObjTop[-2]+BoxRow].g;
                    if( UseBlue )
                        PixelSumB += ImageView->IEBitmap->Pixels[ImageView->ObjLeft[-2]+BoxCol][ImageView->ObjTop[-2]+BoxRow].b;
                }
            }

            if( UseRed )
                ROMBit[ROMBitIdx].PixelSum.r = PixelSumR / (BoxHeight*BoxWidth);
            if( UseGreen )
                ROMBit[ROMBitIdx].PixelSum.g = PixelSumG / (BoxHeight*BoxWidth);
            if( UseBlue )
                ROMBit[ROMBitIdx].PixelSum.b = PixelSumB / (BoxHeight*BoxWidth);

            PixelSumGray=0;
            NumChannels=0;
            ROMBit[ROMBitIdx].PixelsAboveThreshold=0;
            ROMBit[ROMBitIdx].PixelsBelowThreshold=0;

            if( UseRed )
            {
                PixelSumGray += ROMBit[ROMBitIdx].PixelSum.r;
                NumChannels++;
            }
            if( UseGreen )
            {
                PixelSumGray += ROMBit[ROMBitIdx].PixelSum.g;
                NumChannels++;
            }
            if( UseBlue )
            {
                PixelSumGray += ROMBit[ROMBitIdx].PixelSum.b;
                NumChannels++;
            }

            if( NumChannels )
            {
                ROMBit[ROMBitIdx].PixelSumG = PixelSumGray / NumChannels;
            }
            else
                ROMBit[ROMBitIdx].PixelSumG = PixelSumGray;
*/


                    if( ROMBit[ROMBitIdx].PixelSumG <= Threshold0 )
                    {
                        ROMBit[ROMBitIdx].Value = 0;
                        ImageView->ObjPenColor[ROMBit[ROMBitIdx].Box]  = clBlue;
                    }
                    else if( ROMBit[ROMBitIdx].PixelSumG >= Threshold1 )
                    {
                        ROMBit[ROMBitIdx].Value = 1;
                        ImageView->ObjPenColor[ROMBit[ROMBitIdx].Box] = clYellow;
                    }
                    break;
            }
        }
    }


    FillBitView();


    // scan through bits and check for any ? -- ask user if they want to save file as-is or if they will correct errors
    NumInvalidBits=0;
    for( i=0; i<ImageForm->NumROMBits; i++ )
    {
        if( ROMBit[i].Active == 0 )
            continue;
        if( ROMBit[i].Value < 0 || ImageForm->ROMBit[i].Value > 1 )
            NumInvalidBits++;
    }

    LogForm->LogMemo->Lines->Add("Area of Interest has been analyzed for bits.");
    LogForm->LogMemo->Lines->Add("'1' bits are yellow, '0' bits are blue, undetermined bits are red.");
    LogForm->LogMemo->Lines->Add("Click within the image area to give the image focus, then press '1' or '0' while mouse is hovering over bits to adjust them.");
    LogForm->LogMemo->Lines->Add("Use \"File -> Export bits to file...\" to save the bit pattern to disk.");
    if( NumInvalidBits )
    {
        AnsiString TempStr;

        TempStr.sprintf( "WARNING - UNRECOGNIZED BITS!  %d bits have not been identified as 1 or 0 - they are marked red.", NumInvalidBits);
        LogForm->LogMemo->Lines->Add( TempStr );
    }
    LogForm->LogMemo->Lines->Add("");

}
//---------------------------------------------------------------------------
void __fastcall TImageForm::Clearallobjects1Click(TObject *Sender)
{
    ImageView->UnSelAllObjects();

    NumROMBits = 0;
    if(ROMBit)
    {
        delete[] ROMBit;
        ROMBit=NULL;
    }

    for( int i=ImageView->ObjectsCount-1; i; i-- )
    {
        if( ImageView->ObjKind[i] != iekPOLYLINE )
            ImageView->RemoveObject(i);
    }

    if( ROMPolygon > -1 )
        ImageView->AddSelObject(ROMPolygon);
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::Transparency1Click(TObject *Sender)
{
//    if(ROMPolygon>-1)
//        ImageView->ObjTransparency[ROMPolygon] = 255;
    for( int counter=0; counter< NumROMBits; counter++)
    {
        if( !ROMBit[counter].Active )
            continue;

        ImageView->ObjTransparency[ROMBit[counter].Box] = 255;
    }
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::Transparency501Click(TObject *Sender)
{
//    if(ROMPolygon>-1)
//        ImageView->ObjTransparency[ROMPolygon] = 128;
    for( int counter=0; counter< NumROMBits; counter++)
    {
        if( !ROMBit[counter].Active )
            continue;

        ImageView->ObjTransparency[ROMBit[counter].Box] = 128;
    }
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::Transparency801Click(TObject *Sender)
{
//    if(ROMPolygon>-1)
//        ImageView->ObjTransparency[ROMPolygon] = 255.0*0.20;
    for( int counter=0; counter< NumROMBits; counter++)
    {
        if( !ROMBit[counter].Active )
            continue;

        ImageView->ObjTransparency[ROMBit[counter].Box] = 255.0*0.20;
    }
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::ImageViewMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
    double ObjectDistance;
    int FoundObject;
    int FoundBitBox;

    FoundObject = ImageView->FindObjectAt(X, Y, ObjectDistance);

    if( ObjectDistance < 5 )
    {
//        ImageView->ObjPenColor[FoundObject] = clGreen;

        for( FoundBitBox=0; FoundBitBox<NumROMBits; FoundBitBox++ )
        {
            if( ROMBit[FoundBitBox].Box == FoundObject )
                break;
        }
        if( FoundBitBox < NumROMBits )
        {   //  FoundBitBox is index of ROMBitBox for box near cursor
            ROMBitSettingsForm->BitBoxIdxLabel->Caption = FoundBitBox;
            ROMBitSettingsForm->PixelSumLabel->Caption = ROMBit[FoundBitBox].PixelSumG;
            ROMBitSettingsForm->PixelsAboveThresholdLabel->Caption = ROMBit[FoundBitBox].PixelsAboveThreshold;
            ROMBitSettingsForm->PixelsBelowThresholdLabel->Caption = ROMBit[FoundBitBox].PixelsBelowThreshold;
            ROMBitSettingsForm->DotLevelLabel->Caption = ROMBit[FoundBitBox].DotLevel;
            ROMBitSettingsForm->RimLevelLabel->Caption = ROMBit[FoundBitBox].RimLevel;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::Processing1Click(TObject *Sender)
{
    ImageView->Proc->DoPreviews();
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::Undo1Click(TObject *Sender)
{
    ImageView->Proc->Undo(true);
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::Redo1Click(TObject *Sender)
{
    ImageView->Proc->Redo();
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::FillBitView(void)
{
    int BitsPerCol;
    int BitsPerRow;
    int ActiveBitsPerCol;
    int ActiveBitsPerRow;

    BitsPerCol = ROMBitSettingsForm->BitsPerColEdit->Text.ToIntDef(64);
    BitsPerRow = ROMBitSettingsForm->BitsPerRowEdit->Text.ToIntDef(8);


    bool UseRed,UseGreen,UseBlue;

    UseRed = ROMBitSettingsForm->RedCheckBox->Checked;
    UseGreen = ROMBitSettingsForm->GreenCheckBox->Checked;
    UseBlue = ROMBitSettingsForm->BlueCheckBox->Checked;



    ActiveBitsPerCol=0;
    for( int BitBoxCounter=0; BitBoxCounter< BitsPerCol; BitBoxCounter++ )
    {
        if( XBoxesPatternLen && !XBoxesPattern[ BitBoxCounter % XBoxesPatternLen ] )
            continue;

        ActiveBitsPerCol++;
    }

    ActiveBitsPerRow=0;
    for( int BitBoxCounter=0; BitBoxCounter< BitsPerRow; BitBoxCounter++ )
    {
        if( YBoxesPatternLen && !YBoxesPattern[ BitBoxCounter % YBoxesPatternLen ] )
            continue;

        ActiveBitsPerRow++;
    }


    ROMBitSettingsForm->BitView->IEBitmap->Allocate(ActiveBitsPerCol,ActiveBitsPerRow,ie24RGB);
    ROMBitSettingsForm->BitView->IEBitmap->Fill(clBlack);


    for( int RowCounter=0, ActiveBitsPerRow=0; RowCounter<BitsPerRow; RowCounter++ )
    {
        if( YBoxesPatternLen && !YBoxesPattern[ RowCounter % YBoxesPatternLen ] )
            continue;

        for( int ColCounter=0, ActiveBitsPerCol=0; ColCounter<BitsPerCol; ColCounter++ )
        {
            int ROMBitIdx = RowCounter*BitsPerCol+ColCounter;

            if( XBoxesPatternLen && !XBoxesPattern[ ColCounter % XBoxesPatternLen ] )
                continue;

            if(UseRed)
                ROMBitSettingsForm->BitView->IEBitmap->PPixels_ie24RGB[ActiveBitsPerCol][ActiveBitsPerRow]->r = ROMBit[ROMBitIdx].PixelSum.r;
            else
                ROMBitSettingsForm->BitView->IEBitmap->PPixels_ie24RGB[ActiveBitsPerCol][ActiveBitsPerRow]->r = ROMBit[ROMBitIdx].PixelSumG;

            if(UseGreen)
                ROMBitSettingsForm->BitView->IEBitmap->PPixels_ie24RGB[ActiveBitsPerCol][ActiveBitsPerRow]->g = ROMBit[ROMBitIdx].PixelSum.g;
            else
                ROMBitSettingsForm->BitView->IEBitmap->PPixels_ie24RGB[ActiveBitsPerCol][ActiveBitsPerRow]->g = ROMBit[ROMBitIdx].PixelSumG;

            if(UseBlue)
                ROMBitSettingsForm->BitView->IEBitmap->PPixels_ie24RGB[ActiveBitsPerCol][ActiveBitsPerRow]->b = ROMBit[ROMBitIdx].PixelSum.b;
            else
                ROMBitSettingsForm->BitView->IEBitmap->PPixels_ie24RGB[ActiveBitsPerCol][ActiveBitsPerRow]->b = ROMBit[ROMBitIdx].PixelSumG;

            ActiveBitsPerCol++;
        }
        ActiveBitsPerRow++;
    }

/*
    int RowCounter=0; //( BitBoxCounter / BitsPerCol);
    int ColCounter=0; //(BitBoxCounter % BitsPerCol );
    int NewRow=0;
    for( int BitBoxCounter=0; BitBoxCounter< NumROMBits; BitBoxCounter++ )
    {
        if(BitBoxCounter && !(BitBoxCounter%BitsPerCol))
            NewRow = 1;

        if( !ROMBit[BitBoxCounter].Active )
            continue;

        ColCounter++;

        if(NewRow)
        {
            ColCounter=0;
            RowCounter++;
            NewRow=0;
        }

        if(UseRed)
            ROMBitSettingsForm->BitView->IEBitmap->PPixels_ie24RGB[ColCounter][RowCounter]->r = ROMBit[BitBoxCounter].PixelSum.r;
        else
            ROMBitSettingsForm->BitView->IEBitmap->PPixels_ie24RGB[ColCounter][RowCounter]->r = ROMBit[BitBoxCounter].PixelSumG;

        if(UseGreen)
            ROMBitSettingsForm->BitView->IEBitmap->PPixels_ie24RGB[ColCounter][RowCounter]->g = ROMBit[BitBoxCounter].PixelSum.g;
        else
            ROMBitSettingsForm->BitView->IEBitmap->PPixels_ie24RGB[ColCounter][RowCounter]->g = ROMBit[BitBoxCounter].PixelSumG;

        if(UseBlue)
            ROMBitSettingsForm->BitView->IEBitmap->PPixels_ie24RGB[ColCounter][RowCounter]->b = ROMBit[BitBoxCounter].PixelSum.b;
        else
            ROMBitSettingsForm->BitView->IEBitmap->PPixels_ie24RGB[ColCounter][RowCounter]->b = ROMBit[BitBoxCounter].PixelSumG;
    }
*/
    ROMBitSettingsForm->BitView->Update();
    ROMBitSettingsForm->HistogramBox->Update();
    ROMBitSettingsForm->Update();
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::ImageViewDblClick(TObject *Sender)
{
    TPoint CursorPos;

    CursorPos = Mouse->CursorPos;

    CursorPos = ImageView->ScreenToClient( CursorPos );

    double ObjectDistance;
    int FoundObject;
    int FoundBitBox;

    FoundObject = ImageView->FindObjectAt(CursorPos.x, CursorPos.y, ObjectDistance);

    if( ObjectDistance < 5 )
    {
//        ImageView->ObjPenColor[FoundObject] = clGreen;

        for( FoundBitBox=0; FoundBitBox<NumROMBits; FoundBitBox++ )
        {
            if( ROMBit[FoundBitBox].Box == FoundObject )
                break;
        }
        if( FoundBitBox < NumROMBits )
        {   //  FoundBitBox is index of ROMBitBox for box near cursor
//            ROMBitSettingsForm->BitBoxIdxLabel->Caption = FoundBitBox;
//            ROMBitSettingsForm->PixelSumLabel->Caption = ROMBit[FoundBitBox].PixelSumG;
            ROMBit[FoundBitBox].Value++;
            if(ROMBit[FoundBitBox].Value>1)
                ROMBit[FoundBitBox].Value=-1;
            switch( ROMBit[FoundBitBox].Value )
            {
                case 0:
                    ImageView->ObjPenColor[ROMBit[FoundBitBox].Box] = clBlue;
                    break;

                case 1:
                    ImageView->ObjPenColor[ROMBit[FoundBitBox].Box] = clYellow;
                    break;

                case -1:
                    ImageView->ObjPenColor[ROMBit[FoundBitBox].Box] = clRed;
                    break;
            }
            ImageView->Update();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::ImageViewKeyPress(TObject *Sender, char &Key)
{
    TPoint CursorPos;

    CursorPos = Mouse->CursorPos;

    CursorPos = ImageView->ScreenToClient( CursorPos );

    double ObjectDistance;
    int FoundObject;
    int FoundBitBox;

    FoundObject = ImageView->FindObjectAt(CursorPos.x, CursorPos.y, ObjectDistance);

    if( ObjectDistance < 5 )
    {
//        ImageView->ObjPenColor[FoundObject] = clGreen;

        for( FoundBitBox=0; FoundBitBox<NumROMBits; FoundBitBox++ )
        {
            if( ROMBit[FoundBitBox].Box == FoundObject )
                break;
        }
        if( FoundBitBox < NumROMBits )
        {   //  FoundBitBox is index of ROMBitBox for box near cursor
            switch( Key )
            {
                case '0':
                    ROMBit[FoundBitBox].Value=0;
                    ImageView->ObjPenColor[ROMBit[FoundBitBox].Box] = clBlue;
                    break;

                case '1':
                    ROMBit[FoundBitBox].Value=1;
                    ImageView->ObjPenColor[ROMBit[FoundBitBox].Box] = clYellow;
                    break;

                case '.':
                    ROMBit[FoundBitBox].Value=-1;
                    ImageView->ObjPenColor[ROMBit[FoundBitBox].Box] = clRed;
                    break;
            }
            ImageView->Update();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::ImageViewVectorialChanged(TObject *Sender)
{
    if( ROMPolygon < 0 )
        return;
    if( ImageView->ObjPolylinePointsCount[ROMPolygon] > 0 && ImageView->ObjPolylinePointsCount[ROMPolygon] != 4 )
    {
        TPoint LinePoints[4];
        int i;

// ideally we would remove the point that is closest to another point - that is probably the new one accidentally added?
// really most likely candidate is the one that is in line between two others - but need to calculate line path & distance from it to find that 
        for( i=0; i<4; i++ )
        {
            LinePoints[i].x = ImageView->ObjPolylinePoints[ROMPolygon][i].x;
            LinePoints[i].y = ImageView->ObjPolylinePoints[ROMPolygon][i].y;
        }
/*
        TIniFile *ini;
        ini = new TIniFile( ChangeFileExt( Application->ExeName, ".ini" ) );
        LinePoints[0].x = ini->ReadInteger( "ROMPolygon", "0x", 100 );
        LinePoints[0].y = ini->ReadInteger( "ROMPolygon", "0y", 100 );
        LinePoints[1].x = ini->ReadInteger( "ROMPolygon", "1x", 200 );
        LinePoints[1].y = ini->ReadInteger( "ROMPolygon", "1y", 100 );
        LinePoints[2].x = ini->ReadInteger( "ROMPolygon", "2x", 200 );
        LinePoints[2].y = ini->ReadInteger( "ROMPolygon", "2y", 200 );
        LinePoints[3].x = ini->ReadInteger( "ROMPolygon", "3x", 100 );
        LinePoints[3].y = ini->ReadInteger( "ROMPolygon", "3y", 200 );
        delete ini;
*/
        ImageView->ObjKind[ROMPolygon] = iekPOLYLINE;
        ImageView->ObjPenWidth[ROMPolygon] = 1;
        ImageView->ObjPenColor[ROMPolygon] = clBlue;
        ImageView->ObjStyle[ROMPolygon] = TIEVStyle()<<ievsSelectable<<ievsMoveable<<ievsSizeable<<ievsVisible;
        ImageView->ObjName[ROMPolygon] = "ROMPolygon";
        ImageView->SetObjPolylinePoints(ROMPolygon,LinePoints,3);
        ImageView->ObjPolylineClosed[ROMPolygon] = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::Fittowindow1Click(TObject *Sender)
{
    ImageView->Fit();
    UpdateCaption();
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::ZoomIn1Click(TObject *Sender)
{
    ImageView->Zoom *= 1.05;
    UpdateCaption();
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::ZoomOut1Click(TObject *Sender)
{
    ImageView->Zoom /= 1.05;
    UpdateCaption();
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::ResetROMBox1Click(TObject *Sender)
{
    NumROMBits = 0;
    if(ROMBit)
    {
        delete[] ROMBit;
        ROMBit=NULL;
    }

    ImageView->OnVectorialChanged = NULL;
    ImageView->UnSelAllObjects();
    ImageView->RemoveAllObjects();

    ROMPolygon = ImageView->AddNewObject();

    TPoint LinePoints[4];
    LinePoints[0].x = 100;
    LinePoints[0].y = 100;
    LinePoints[1].x = 200;
    LinePoints[1].y = 100;
    LinePoints[2].x = 200;
    LinePoints[2].y = 200;
    LinePoints[3].x = 100;
    LinePoints[3].y = 200;

    ImageView->ObjKind[ROMPolygon] = iekPOLYLINE;
    ImageView->ObjPenWidth[ROMPolygon] = 1;
    ImageView->ObjPenColor[ROMPolygon] = clBlue;
    ImageView->ObjStyle[ROMPolygon] = TIEVStyle()<<ievsSelectable<<ievsMoveable<<ievsSizeable<<ievsVisible;
    ImageView->ObjName[ROMPolygon] = "ROMPolygon";
    ImageView->SetObjPolylinePoints(ROMPolygon,LinePoints,3);
    ImageView->ObjPolylineClosed[ROMPolygon] = true;

    ImageView->MouseInteractVt=TIEMouseInteractVt()<<miObjectSelect;
    ImageView->SelAllObjects();

    ImageView->OnVectorialChanged = ImageViewVectorialChanged;
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::Exportbits1Click(TObject *Sender)
{
    FILE *BitTxtFile;
    int BitCounter;

    if( ImageForm->NumROMBits < 1 )
    {
        Application->MessageBoxA("You must first define the Area Of Interest and then Analyze bits within AOI before you can export the bits.", "No bits to export", MB_OK );
        return;     // nothing to save
    }

    // scan through bits and check for any ? -- ask user if they want to save file as-is or if they will correct errors
    for( BitCounter=0; BitCounter<ImageForm->NumROMBits; BitCounter++ )
    {
        if( ImageForm->ROMBit[BitCounter].Active == 0 )
            continue;
        if( ImageForm->ROMBit[BitCounter].Value < 0 || ImageForm->ROMBit[BitCounter].Value > 1 )
            break;
    }
    if( BitCounter<ImageForm->NumROMBits )
    {
         if( Application->MessageBoxA( "Some bits have not been identified as 1 or 0.\nThey will appear as '?' in the output file.\n\nDo you want to export the bits anyway?", "WARNING - Some bits not recognized!", MB_YESNO ) != IDYES )
            return;
    }


    if( WorkingDir.Length() && ROMBitSaveDialog->InitialDir != WorkingDir )
    {
        ROMBitSaveDialog->InitialDir = WorkingDir;
        ROMBitSaveDialog->FileName = "";
    }

    if( ROMBitSaveDialog->Execute() != mrOk )
        return;

    WorkingDir = ROMBitSaveDialog->FileName.SubString(1, ROMBitSaveDialog->FileName.LastDelimiter( ":\\" ) );

// open ROMBitSaveDialog->FileName
    BitTxtFile = fopen( ROMBitSaveDialog->FileName.c_str(), "wt" );
    if( !BitTxtFile )
    {
        Application->MessageBox("Error opening file for output.","Error",MB_OK);
        return;
    }

    int BitsPerCol=64;
//    int BitsPerRow=8;

    BitsPerCol = ROMBitSettingsForm->BitsPerColEdit->Text.ToIntDef(64);
//    BitsPerRow = ROMBitSettingsForm->BitsPerRowEdit->Text.ToIntDef(8);

    for( BitCounter=0; BitCounter<ImageForm->NumROMBits; BitCounter++ )
    {
        int RowCounter= ( BitCounter / BitsPerCol);
        int ColCounter=  (BitCounter % BitsPerCol );

        if( (!ColCounter) && RowCounter )
            fprintf( BitTxtFile, "\n" );        // newline

        //output " " between columns
        if( !ROMBit[BitCounter].Active )
        {
            fprintf( BitTxtFile, " " );
            continue;
        }

//        if( ColCounter==32 )
//            fprintf( BitTxtFile, " " );     // separator between columns every 32 bits

//output bit
        switch( ImageForm->ROMBit[BitCounter].Value )
        {
            case 0:
                fputc( '0', BitTxtFile );
                break;

            case 1:
                fputc( '1', BitTxtFile );
                break;

            case -1:
            default:
                fputc( '?', BitTxtFile );
                break;
        }
    }

    fprintf( BitTxtFile, "\n" );

    fclose( BitTxtFile );
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::ImageViewObjectClick(TObject *Sender, int hobj)
{
    if( ROMPolygon >= 0 )
    {
        if( ImageView->SelObjectsCount != 1 || ImageView->SelObjects[0] != ROMPolygon )
        {
            ImageView->UnSelAllObjects();
            ImageView->AddSelObject(ROMPolygon);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::Loadsettings1Click(TObject *Sender)
{
    TIniFile *SettingsIni;


    if( WorkingDir.Length() && OpenSettingsDialog->InitialDir != WorkingDir )
    {
        OpenSettingsDialog->InitialDir = WorkingDir;
        OpenSettingsDialog->FileName = "";
    }

    if( OpenSettingsDialog->Execute() != mrOk )
        return;

    WorkingDir = OpenSettingsDialog->FileName.SubString(1, OpenSettingsDialog->FileName.LastDelimiter( ":\\" ) );

    LoadSettings( OpenSettingsDialog->FileName );
    SaveSettings( ChangeFileExt( Application->ExeName, ".ini" ) );

    if( PreviousFilename.Length() )
        LogForm->LogMemo->Lines->Add( "Loaded bit extraction settings for "+PreviousFilename );
    else
        LogForm->LogMemo->Lines->Add( "Loaded bit extraction settings from file." );
    LogForm->LogMemo->Lines->Add( "" );

    ShowROMBox1Click(NULL);

    return;
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::LoadSettings( AnsiString IniFilename )
{
    TPoint LinePoints[4];
    TIniFile *SettingsIni;


    SettingsIni = new TIniFile( IniFilename );
    LinePoints[0].x = SettingsIni->ReadInteger( "ROMPolygon", "0x", 100 );
    LinePoints[0].y = SettingsIni->ReadInteger( "ROMPolygon", "0y", 100 );
    LinePoints[1].x = SettingsIni->ReadInteger( "ROMPolygon", "1x", 200 );
    LinePoints[1].y = SettingsIni->ReadInteger( "ROMPolygon", "1y", 100 );
    LinePoints[2].x = SettingsIni->ReadInteger( "ROMPolygon", "2x", 200 );
    LinePoints[2].y = SettingsIni->ReadInteger( "ROMPolygon", "2y", 200 );
    LinePoints[3].x = SettingsIni->ReadInteger( "ROMPolygon", "3x", 100 );
    LinePoints[3].y = SettingsIni->ReadInteger( "ROMPolygon", "3y", 200 );

    ROMBitSettingsForm->BitsPerColEdit->Text = SettingsIni->ReadInteger( "BitSettings", "BitColumns", 16 );
    ROMBitSettingsForm->BitsPerRowEdit->Text = SettingsIni->ReadInteger( "BitSettings", "BitRows", 16 );
    ROMBitSettingsForm->BoxWidthEdit->Text = SettingsIni->ReadInteger( "BitSettings", "BoxWidth", 5 );
    ROMBitSettingsForm->BoxHeightEdit->Text = SettingsIni->ReadInteger( "BitSettings", "BoxHeight", 5 );
    ROMBitSettingsForm->Threshold0Edit->Text = SettingsIni->ReadInteger( "BitSettings", "Threshold0", 64 );
    ROMBitSettingsForm->Threshold1Edit->Text = SettingsIni->ReadInteger( "BitSettings", "Threshold1", 96 );
    ROMBitSettingsForm->MinBright1Edit->Text = SettingsIni->ReadInteger( "BitSettings", "MinBright1", 20 );
    ROMBitSettingsForm->MaxBright0Edit->Text = SettingsIni->ReadInteger( "BitSettings", "MaxBright0", 5 );
    ROMBitSettingsForm->BitAnalysisMethodRadioGroup->ItemIndex = SettingsIni->ReadInteger( "BitSettings", "BitAnalysisMethod", 0 );
    ROMBitSettingsForm->RedCheckBox->Checked = SettingsIni->ReadInteger( "BitSettings", "UseR", 1 );
    ROMBitSettingsForm->GreenCheckBox->Checked = SettingsIni->ReadInteger( "BitSettings", "UseG", 1 );
    ROMBitSettingsForm->BlueCheckBox->Checked = SettingsIni->ReadInteger( "BitSettings", "UseB", 1 );
    ROMBitSettingsForm->Dot1ThresholdEdit->Text = SettingsIni->ReadInteger( "BitSettings", "Dot1Threshold", 0 );
    ROMBitSettingsForm->Dot0ThresholdEdit->Text = SettingsIni->ReadInteger( "BitSettings", "Dot0Threshold", 0 );
    ROMBitSettingsForm->RimWidthEdit->Text = SettingsIni->ReadInteger( "BitSettings", "RimWidth", 1 );
    ROMBitSettingsForm->DotWidthEdit->Text = SettingsIni->ReadInteger( "BitSettings", "DotWidth", 1 );
    ROMBitSettingsForm->XBoxesToAnalyzeEdit->Text = SettingsIni->ReadString( "BitSettings", "XBoxesToAnalyze", "" );
    ROMBitSettingsForm->YBoxesToAnalyzeEdit->Text = SettingsIni->ReadString( "BitSettings", "YBoxesToAnalyze", "" );

    PreviousFilename = SettingsIni->ReadString( "Image", "Filename", "" );

    delete SettingsIni;

    SettingsIni = new TIniFile( ChangeFileExt( Application->ExeName, ".ini" ) );
    SettingsIni->WriteInteger( "ROMPolygon", "0x", LinePoints[0].x );
    SettingsIni->WriteInteger( "ROMPolygon", "0y", LinePoints[0].y );
    SettingsIni->WriteInteger( "ROMPolygon", "1x", LinePoints[1].x );
    SettingsIni->WriteInteger( "ROMPolygon", "1y", LinePoints[1].y );
    SettingsIni->WriteInteger( "ROMPolygon", "2x", LinePoints[2].x );
    SettingsIni->WriteInteger( "ROMPolygon", "2y", LinePoints[2].y );
    SettingsIni->WriteInteger( "ROMPolygon", "3x", LinePoints[3].x );
    SettingsIni->WriteInteger( "ROMPolygon", "3y", LinePoints[3].y );
    delete SettingsIni;
    

    return;
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::Savesettings1Click(TObject *Sender)
{
    if( WorkingDir.Length() && SaveSettingsDialog->InitialDir != WorkingDir )
    {
        SaveSettingsDialog->InitialDir = WorkingDir;
        SaveSettingsDialog->FileName = "";
    }

    if( SaveSettingsDialog->Execute() != mrOk )
        return;

    WorkingDir = SaveSettingsDialog->FileName.SubString(1, SaveSettingsDialog->FileName.LastDelimiter( ":\\" ) );

    SaveSettings(SaveSettingsDialog->FileName);

    return;
}
//---------------------------------------------------------------------------
void __fastcall TImageForm::SaveSettings(AnsiString IniFilename)
{
    TIniFile *SettingsIni;
    TPoint LinePoints[4];
    int BitsPerCol;
    int BitsPerRow;
    int BoxWidth;
    int BoxHeight;
    int Threshold0;
    int Threshold1;


    if( ROMPolygon > -1 )
    {
        LinePoints[0].x = ImageView->ObjPolylinePoints[ROMPolygon][0].x;
        LinePoints[0].y = ImageView->ObjPolylinePoints[ROMPolygon][0].y;
        LinePoints[1].x = ImageView->ObjPolylinePoints[ROMPolygon][1].x;
        LinePoints[1].y = ImageView->ObjPolylinePoints[ROMPolygon][1].y;
        LinePoints[2].x = ImageView->ObjPolylinePoints[ROMPolygon][2].x;
        LinePoints[2].y = ImageView->ObjPolylinePoints[ROMPolygon][2].y;
        LinePoints[3].x = ImageView->ObjPolylinePoints[ROMPolygon][3].x;
        LinePoints[3].y = ImageView->ObjPolylinePoints[ROMPolygon][3].y;
    }
    else
    {
        SettingsIni = new TIniFile( ChangeFileExt( Application->ExeName, ".ini" ) );
        LinePoints[0].x = SettingsIni->ReadInteger( "ROMPolygon", "0x", 100 );
        LinePoints[0].y = SettingsIni->ReadInteger( "ROMPolygon", "0y", 100 );
        LinePoints[1].x = SettingsIni->ReadInteger( "ROMPolygon", "1x", 200 );
        LinePoints[1].y = SettingsIni->ReadInteger( "ROMPolygon", "1y", 100 );
        LinePoints[2].x = SettingsIni->ReadInteger( "ROMPolygon", "2x", 200 );
        LinePoints[2].y = SettingsIni->ReadInteger( "ROMPolygon", "2y", 200 );
        LinePoints[3].x = SettingsIni->ReadInteger( "ROMPolygon", "3x", 100 );
        LinePoints[3].y = SettingsIni->ReadInteger( "ROMPolygon", "3y", 200 );
        delete SettingsIni;
    }

    SettingsIni = new TIniFile( IniFilename );
    SettingsIni->WriteInteger( "ROMPolygon", "0x", LinePoints[0].x );
    SettingsIni->WriteInteger( "ROMPolygon", "0y", LinePoints[0].y );
    SettingsIni->WriteInteger( "ROMPolygon", "1x", LinePoints[1].x );
    SettingsIni->WriteInteger( "ROMPolygon", "1y", LinePoints[1].y );
    SettingsIni->WriteInteger( "ROMPolygon", "2x", LinePoints[2].x );
    SettingsIni->WriteInteger( "ROMPolygon", "2y", LinePoints[2].y );
    SettingsIni->WriteInteger( "ROMPolygon", "3x", LinePoints[3].x );
    SettingsIni->WriteInteger( "ROMPolygon", "3y", LinePoints[3].y );


    BitsPerCol = ROMBitSettingsForm->BitsPerColEdit->Text.ToIntDef(64);
    BitsPerRow = ROMBitSettingsForm->BitsPerRowEdit->Text.ToIntDef(8);
    BoxWidth = ROMBitSettingsForm->BoxWidthEdit->Text.ToIntDef(5);
    BoxHeight = ROMBitSettingsForm->BoxHeightEdit->Text.ToIntDef(5);
    Threshold0 = ROMBitSettingsForm->Threshold0Edit->Text.ToIntDef(64);
    Threshold1 = ROMBitSettingsForm->Threshold1Edit->Text.ToIntDef(96);

    SettingsIni->WriteInteger( "BitSettings", "BitColumns", BitsPerCol );
    SettingsIni->WriteInteger( "BitSettings", "BitRows", BitsPerRow );
    SettingsIni->WriteInteger( "BitSettings", "BoxWidth", BoxWidth );
    SettingsIni->WriteInteger( "BitSettings", "BoxHeight", BoxHeight );
    SettingsIni->WriteInteger( "BitSettings", "Threshold0", Threshold0 );
    SettingsIni->WriteInteger( "BitSettings", "Threshold1", Threshold1 );
    SettingsIni->WriteInteger( "BitSettings", "MinBright1", ROMBitSettingsForm->MinBright1Edit->Text.ToIntDef(20) );
    SettingsIni->WriteInteger( "BitSettings", "MaxBright0", ROMBitSettingsForm->MaxBright0Edit->Text.ToIntDef(5) );
    SettingsIni->WriteInteger( "BitSettings", "BitAnalysisMethod", ROMBitSettingsForm->BitAnalysisMethodRadioGroup->ItemIndex );
    SettingsIni->WriteInteger( "BitSettings", "UseR", ROMBitSettingsForm->RedCheckBox->Checked );
    SettingsIni->WriteInteger( "BitSettings", "UseG", ROMBitSettingsForm->GreenCheckBox->Checked );
    SettingsIni->WriteInteger( "BitSettings", "UseB", ROMBitSettingsForm->BlueCheckBox->Checked );
    SettingsIni->WriteInteger( "BitSettings", "Dot1Threshold", ROMBitSettingsForm->Dot1ThresholdEdit->Text.ToIntDef(0) );
    SettingsIni->WriteInteger( "BitSettings", "Dot0Threshold", ROMBitSettingsForm->Dot0ThresholdEdit->Text.ToIntDef(0) );
    SettingsIni->WriteInteger( "BitSettings", "RimWidth", ROMBitSettingsForm->RimWidthEdit->Text.ToIntDef(1) );
    SettingsIni->WriteInteger( "BitSettings", "DotWidth", ROMBitSettingsForm->DotWidthEdit->Text.ToIntDef(1) );
    SettingsIni->WriteString( "BitSettings", "XBoxesToAnalyze", ROMBitSettingsForm->XBoxesToAnalyzeEdit->Text );
    SettingsIni->WriteString( "BitSettings", "YBoxesToAnalyze", ROMBitSettingsForm->YBoxesToAnalyzeEdit->Text );

    SettingsIni->WriteString( "Image", "Filename", OpenFilename );

    delete SettingsIni;

    if( OpenFilename.Length() )
        LogForm->LogMemo->Lines->Add( "Saved settings for "+OpenFilename );
    else
        LogForm->LogMemo->Lines->Add( "Saved settings to file." );
    LogForm->LogMemo->Lines->Add( "" );
}
//---------------------------------------------------------------------------
