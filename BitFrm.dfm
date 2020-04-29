object BitForm: TBitForm
  Left = 233
  Top = 107
  Width = 264
  Height = 269
  Caption = 'BitForm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Visible = True
  DesignSize = (
    240
    242)
  PixelsPerInch = 96
  TextHeight = 13
  object BitView: TImageEnVect
    Left = 0
    Top = 0
    Width = 240
    Height = 81
    ParentCtl3D = False
    LegacyBitmap = False
    ImageEnVersion = '3.0.2'
    Anchors = [akLeft, akTop, akRight]
    EnableInteractionHints = True
    TabOrder = 0
  end
  object HistogramBox: THistogramBox
    Left = 0
    Top = 81
    Width = 240
    Height = 162
    AttachedImageEnProc = BitProc
    HistogramKind = [hkBlue]
    Align = alBottom
  end
  object BitProc: TImageEnProc
    AttachedImageEn = BitView
    Background = clBtnFace
    PreviewsParams = [prppShowResetButton, prppHardReset]
    PreviewFont.Charset = DEFAULT_CHARSET
    PreviewFont.Color = clWindowText
    PreviewFont.Height = -11
    PreviewFont.Name = 'MS Sans Serif'
    PreviewFont.Style = []
    Left = 8
    Top = 8
  end
end
