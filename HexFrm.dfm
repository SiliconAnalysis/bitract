object HexForm: THexForm
  Left = 554
  Top = 113
  Width = 625
  Height = 407
  Caption = 'Byte view'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object HexMemo: TRichEdit
    Left = 0
    Top = 0
    Width = 609
    Height = 369
    Align = alClient
    Color = clBlack
    Font.Charset = ANSI_CHARSET
    Font.Color = clSilver
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    PopupMenu = PopupMenu1
    ScrollBars = ssVertical
    TabOrder = 0
    WordWrap = False
    OnKeyPress = HexMemoKeyPress
  end
  object PopupMenu1: TPopupMenu
    Left = 192
    Top = 48
    object Updatebyteview1: TMenuItem
      Caption = '&Redraw byte view'
      OnClick = Updatebyteview1Click
    end
    object Copy1: TMenuItem
      Caption = '&Copy selection'
      OnClick = Copy1Click
    end
    object Savebinfile1: TMenuItem
      Caption = '&Save .bin file...'
      OnClick = Savebinfile1Click
    end
  end
end
