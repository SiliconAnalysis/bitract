object HistogramForm: THistogramForm
  Left = 328
  Top = 117
  Width = 459
  Height = 146
  Caption = 'Image histogram'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Visible = True
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnResize = FormResize
  DesignSize = (
    443
    108)
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 174
    Top = 8
    Width = 64
    Height = 13
    Anchors = [akTop, akRight]
    Caption = 'Pixels at 0:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 160
    Top = 32
    Width = 78
    Height = 13
    Anchors = [akTop, akRight]
    Caption = 'Pixels at 255:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object PixelsAt0RLabel: TLabel
    Left = 256
    Top = 8
    Width = 35
    Height = 13
    Alignment = taRightJustify
    Anchors = [akTop, akRight]
    AutoSize = False
    Caption = '0'
  end
  object PixelsAt0GLabel: TLabel
    Left = 328
    Top = 8
    Width = 35
    Height = 13
    Alignment = taRightJustify
    Anchors = [akTop, akRight]
    AutoSize = False
    Caption = '0'
  end
  object PixelsAt0BLabel: TLabel
    Left = 394
    Top = 8
    Width = 35
    Height = 13
    Alignment = taRightJustify
    Anchors = [akTop, akRight]
    AutoSize = False
    Caption = '0'
  end
  object PixelsAt255RLabel: TLabel
    Left = 256
    Top = 32
    Width = 35
    Height = 13
    Alignment = taRightJustify
    Anchors = [akTop, akRight]
    AutoSize = False
    Caption = '0'
  end
  object PixelsAt255GLabel: TLabel
    Left = 328
    Top = 32
    Width = 35
    Height = 13
    Alignment = taRightJustify
    Anchors = [akTop, akRight]
    AutoSize = False
    Caption = '0'
  end
  object PixelsAt255BLabel: TLabel
    Left = 394
    Top = 32
    Width = 35
    Height = 13
    Alignment = taRightJustify
    Anchors = [akTop, akRight]
    AutoSize = False
    Caption = '0'
  end
  object Label3: TLabel
    Left = 177
    Top = 64
    Width = 61
    Height = 13
    Anchors = [akTop, akRight]
    Caption = 'Pixels min:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object PixelsMinRLabel: TLabel
    Left = 265
    Top = 64
    Width = 25
    Height = 13
    Alignment = taRightJustify
    Anchors = [akTop, akRight]
    AutoSize = False
    Caption = '0'
  end
  object PixelsMinGLabel: TLabel
    Left = 338
    Top = 64
    Width = 25
    Height = 13
    Alignment = taRightJustify
    Anchors = [akTop, akRight]
    AutoSize = False
    Caption = '0'
  end
  object PixelsMinBLabel: TLabel
    Left = 406
    Top = 64
    Width = 23
    Height = 13
    Alignment = taRightJustify
    Anchors = [akTop, akRight]
    AutoSize = False
    Caption = '0'
  end
  object Label4: TLabel
    Left = 174
    Top = 88
    Width = 64
    Height = 13
    Anchors = [akTop, akRight]
    Caption = 'Pixels max:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object PixelsMaxRLabel: TLabel
    Left = 265
    Top = 88
    Width = 25
    Height = 13
    Alignment = taRightJustify
    Anchors = [akTop, akRight]
    AutoSize = False
    Caption = '0'
  end
  object PixelsMaxGLabel: TLabel
    Left = 338
    Top = 88
    Width = 25
    Height = 13
    Alignment = taRightJustify
    Anchors = [akTop, akRight]
    AutoSize = False
    Caption = '0'
  end
  object PixelsMaxBLabel: TLabel
    Left = 406
    Top = 88
    Width = 23
    Height = 13
    Alignment = taRightJustify
    Anchors = [akTop, akRight]
    AutoSize = False
    Caption = '0'
  end
  object Label5: TLabel
    Left = 393
    Top = 64
    Width = 10
    Height = 13
    Anchors = [akTop, akRight]
    Caption = 'B:'
  end
  object Label6: TLabel
    Left = 384
    Top = 32
    Width = 10
    Height = 13
    Anchors = [akTop, akRight]
    Caption = 'B:'
  end
  object Label7: TLabel
    Left = 384
    Top = 8
    Width = 10
    Height = 13
    Anchors = [akTop, akRight]
    Caption = 'B:'
  end
  object Label8: TLabel
    Left = 393
    Top = 88
    Width = 10
    Height = 13
    Anchors = [akTop, akRight]
    Caption = 'B:'
  end
  object Label9: TLabel
    Left = 326
    Top = 88
    Width = 11
    Height = 13
    Anchors = [akTop, akRight]
    Caption = 'G:'
  end
  object Label10: TLabel
    Left = 326
    Top = 64
    Width = 11
    Height = 13
    Anchors = [akTop, akRight]
    Caption = 'G:'
  end
  object Label11: TLabel
    Left = 318
    Top = 32
    Width = 11
    Height = 13
    Anchors = [akTop, akRight]
    Caption = 'G:'
  end
  object Label12: TLabel
    Left = 318
    Top = 8
    Width = 11
    Height = 13
    Anchors = [akTop, akRight]
    Caption = 'G:'
  end
  object Label13: TLabel
    Left = 252
    Top = 88
    Width = 11
    Height = 13
    Anchors = [akTop, akRight]
    Caption = 'R:'
  end
  object Label14: TLabel
    Left = 252
    Top = 64
    Width = 11
    Height = 13
    Anchors = [akTop, akRight]
    Caption = 'R:'
  end
  object Label15: TLabel
    Left = 244
    Top = 32
    Width = 11
    Height = 13
    Anchors = [akTop, akRight]
    Caption = 'R:'
  end
  object Label16: TLabel
    Left = 244
    Top = 8
    Width = 11
    Height = 13
    Anchors = [akTop, akRight]
    Caption = 'R:'
  end
  object HistogramBox: THistogramBox
    Left = 0
    Top = 0
    Width = 145
    Height = 108
    AttachedImageEnProc = ImageForm.ImageProc
    HistogramKind = [hkRed, hkGreen, hkBlue]
    Align = alLeft
    OnClick = HistogramBoxClick
  end
end
