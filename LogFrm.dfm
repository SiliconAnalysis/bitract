object LogForm: TLogForm
  Left = 184
  Top = 121
  Width = 632
  Height = 232
  Caption = 'Bitract: The ROM Bit Extraction System'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu
  OldCreateOrder = False
  Visible = True
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object LogMemo: TMemo
    Left = 0
    Top = 0
    Width = 616
    Height = 174
    Align = alClient
    Lines.Strings = (
      'Welcome to Bitract: The ROM Bit Extraction System'
      ''
      
        'To start the bit extraction process, open an Image using "File -' +
        '>Open image..."'
      '')
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object MainMenu: TMainMenu
    object File1: TMenuItem
      Caption = '&File'
      object Exit1: TMenuItem
        Caption = 'E&xit'
        OnClick = Exit1Click
      end
    end
    object Window1: TMenuItem
      Caption = '&Window'
      object Image1: TMenuItem
        Caption = 'Image'
        OnClick = Image1Click
      end
      object Histogram1: TMenuItem
        Caption = 'Image &Histogram'
        OnClick = Histogram1Click
      end
      object ROMBitSettings1: TMenuItem
        Caption = 'Bit Settings'
        OnClick = ROMBitSettings1Click
      end
    end
  end
end
