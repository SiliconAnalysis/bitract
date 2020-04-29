//---------------------------------------------------------------------------

#include <vcl.h>

#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("LogFrm.cpp", LogForm);
USEFORM("ImageFrm.cpp", ImageForm);
USEFORM("HistogramFrm.cpp", HistogramForm);
USEFORM("ROMBitSettingsFrm.cpp", ROMBitSettingsForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
         Application->Initialize();

         Application->Title = "Bitract: The ROM Bit Extraction System";
         Application->CreateForm(__classid(TLogForm), &LogForm);
         Application->CreateForm(__classid(TROMBitSettingsForm), &ROMBitSettingsForm);
         Application->CreateForm(__classid(TImageForm), &ImageForm);
         Application->CreateForm(__classid(THistogramForm), &HistogramForm);
         Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
