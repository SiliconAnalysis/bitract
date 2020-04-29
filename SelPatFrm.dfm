object SelPatForm: TSelPatForm
  Left = 718
  Top = 118
  Width = 439
  Height = 135
  Caption = 'Select pattern'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  DesignSize = (
    423
    97)
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 20
    Width = 145
    Height = 13
    Caption = 'Column selection pattern (hex):'
  end
  object OKBitBtn: TBitBtn
    Left = 122
    Top = 64
    Width = 75
    Height = 25
    Anchors = [akLeft, akBottom]
    TabOrder = 1
    Kind = bkOK
  end
  object CancelBitBtn: TBitBtn
    Left = 226
    Top = 64
    Width = 75
    Height = 25
    Anchors = [akLeft, akBottom]
    TabOrder = 2
    Kind = bkCancel
  end
  object PatEdit: TEdit
    Left = 160
    Top = 16
    Width = 257
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    TabOrder = 0
  end
end
