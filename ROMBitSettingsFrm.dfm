object ROMBitSettingsForm: TROMBitSettingsForm
  Left = 645
  Top = 112
  Width = 632
  Height = 370
  Caption = 'Bit analysis settings'
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
  DesignSize = (
    616
    332)
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 47
    Top = 4
    Width = 75
    Height = 13
    Caption = 'Bits across AOI:'
  end
  object Label2: TLabel
    Left = 16
    Top = 44
    Width = 106
    Height = 13
    Caption = 'Bits up and down AOI:'
  end
  object Label3: TLabel
    Left = 250
    Top = 12
    Width = 63
    Height = 13
    Caption = 'Bit-box width:'
  end
  object Label4: TLabel
    Left = 246
    Top = 36
    Width = 67
    Height = 13
    Caption = 'Bit-box height:'
  end
  object Label6: TLabel
    Left = 209
    Top = 92
    Width = 104
    Height = 13
    Caption = 'Max. '#39'0'#39' bit brightness:'
  end
  object Label7: TLabel
    Left = 212
    Top = 68
    Width = 101
    Height = 13
    Caption = 'Min. '#39'1'#39' bit brightness:'
  end
  object Label10: TLabel
    Left = 196
    Top = 290
    Width = 98
    Height = 13
    Caption = 'Channels to analyze:'
  end
  object Label11: TLabel
    Left = 4
    Top = 20
    Width = 115
    Height = 13
    Caption = '(# of horizontal columns)'
  end
  object Label12: TLabel
    Left = 32
    Top = 60
    Width = 87
    Height = 13
    Caption = '(# of vertical rows)'
  end
  object Label8: TLabel
    Left = 196
    Top = 124
    Width = 119
    Height = 13
    Caption = 'Min. # bright pixels for '#39'1'#39':'
  end
  object Label9: TLabel
    Left = 193
    Top = 148
    Width = 122
    Height = 13
    Caption = 'Max. # bright pixels for '#39'0'#39':'
  end
  object Label15: TLabel
    Left = 266
    Top = 188
    Width = 49
    Height = 13
    Caption = 'Rim width:'
  end
  object Label17: TLabel
    Left = 267
    Top = 212
    Width = 48
    Height = 13
    Caption = 'Dot width:'
  end
  object Label18: TLabel
    Left = 134
    Top = 188
    Width = 75
    Height = 13
    Caption = 'Dot 1 threshold:'
  end
  object Label19: TLabel
    Left = 134
    Top = 212
    Width = 75
    Height = 13
    Caption = 'Dot 0 threshold:'
  end
  object Label20: TLabel
    Left = 12
    Top = 252
    Width = 58
    Height = 13
    BiDiMode = bdLeftToRight
    Caption = '# pixels dim:'
    ParentBiDiMode = False
  end
  object Label21: TLabel
    Left = 73
    Top = 252
    Width = 40
    Height = 13
    AutoSize = False
    Caption = '-1'
  end
  object Label23: TLabel
    Left = 142
    Top = 244
    Width = 92
    Height = 13
    Caption = 'X boxes to analyze:'
  end
  object Label25: TLabel
    Left = 142
    Top = 268
    Width = 92
    Height = 13
    Caption = 'Y boxes to analyze:'
  end
  object BitsPerColEdit: TEdit
    Left = 128
    Top = 8
    Width = 49
    Height = 21
    TabOrder = 0
    Text = '32'
    OnKeyPress = BitsPerColEditKeyPress
  end
  object BitsPerRowEdit: TEdit
    Left = 128
    Top = 48
    Width = 49
    Height = 21
    TabOrder = 1
    Text = '32'
    OnKeyPress = BitsPerColEditKeyPress
  end
  object BoxWidthEdit: TEdit
    Left = 320
    Top = 8
    Width = 41
    Height = 21
    TabOrder = 4
    Text = '10'
    OnKeyPress = BitsPerColEditKeyPress
  end
  object BoxHeightEdit: TEdit
    Left = 320
    Top = 32
    Width = 41
    Height = 21
    TabOrder = 5
    Text = '10'
    OnKeyPress = BitsPerColEditKeyPress
  end
  object Threshold0Edit: TEdit
    Left = 320
    Top = 88
    Width = 41
    Height = 21
    TabOrder = 7
    Text = '58'
    OnKeyPress = BitsPerColEditKeyPress
  end
  object Threshold1Edit: TEdit
    Left = 320
    Top = 64
    Width = 41
    Height = 21
    TabOrder = 6
    Text = '72'
    OnKeyPress = BitsPerColEditKeyPress
  end
  object PageControl: TPageControl
    Left = 376
    Top = 0
    Width = 264
    Height = 343
    ActivePage = TabSheet2
    Anchors = [akLeft, akTop, akRight, akBottom]
    TabIndex = 1
    TabOrder = 13
    object TabSheet1: TTabSheet
      Caption = 'Bits Histogram'
      OnResize = TabSheet1Resize
      DesignSize = (
        256
        315)
      object HistogramBox: THistogramBox
        Left = 5
        Top = -1
        Width = 224
        Height = 162
        AttachedImageEnProc = BitViewProc
        HistogramKind = [hkRed, hkGreen, hkBlue]
      end
      object BitHistRedCheckBox: TCheckBox
        Left = 8
        Top = 281
        Width = 49
        Height = 17
        Anchors = [akLeft, akBottom]
        Caption = 'Red'
        Checked = True
        State = cbChecked
        TabOrder = 1
        OnClick = BitHistRedCheckBoxClick
      end
      object BitHistGreenCheckBox: TCheckBox
        Left = 64
        Top = 281
        Width = 57
        Height = 17
        Anchors = [akLeft, akBottom]
        Caption = 'Green'
        Checked = True
        State = cbChecked
        TabOrder = 2
        OnClick = BitHistRedCheckBoxClick
      end
      object BitHistBlueCheckBox: TCheckBox
        Left = 128
        Top = 281
        Width = 57
        Height = 17
        Anchors = [akLeft, akBottom]
        Caption = 'Blue'
        Checked = True
        State = cbChecked
        TabOrder = 3
        OnClick = BitHistRedCheckBoxClick
      end
      object BitHistGrayCheckBox: TCheckBox
        Left = 182
        Top = 281
        Width = 46
        Height = 17
        Anchors = [akLeft, akBottom]
        Caption = 'Gray'
        TabOrder = 4
        OnClick = BitHistRedCheckBoxClick
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Bits-only Image'
      ImageIndex = 1
      DesignSize = (
        256
        315)
      object BitView: TImageEnVect
        Left = 0
        Top = 0
        Width = 234
        Height = 306
        ParentCtl3D = False
        ImageEnVersion = '3.0.2'
        Anchors = [akLeft, akTop, akRight, akBottom]
        EnableInteractionHints = True
        TabOrder = 0
      end
    end
  end
  object RedCheckBox: TCheckBox
    Left = 168
    Top = 304
    Width = 49
    Height = 17
    Caption = 'Red'
    Checked = True
    State = cbChecked
    TabOrder = 10
  end
  object GreenCheckBox: TCheckBox
    Left = 224
    Top = 304
    Width = 57
    Height = 17
    Caption = 'Green'
    Checked = True
    State = cbChecked
    TabOrder = 11
  end
  object BlueCheckBox: TCheckBox
    Left = 288
    Top = 304
    Width = 57
    Height = 17
    Caption = 'Blue'
    Checked = True
    State = cbChecked
    TabOrder = 12
  end
  object BitBoxInfoGroupBox: TGroupBox
    Left = 8
    Top = 172
    Width = 117
    Height = 117
    Caption = 'Bit-box under mouse'
    TabOrder = 3
    object Label13: TLabel
      Left = 19
      Top = 20
      Width = 51
      Height = 13
      Caption = 'Bit-box idx:'
    end
    object Label14: TLabel
      Left = 5
      Top = 36
      Width = 65
      Height = 13
      BiDiMode = bdLeftToRight
      Caption = 'Sum of pixels:'
      ParentBiDiMode = False
    end
    object BitBoxIdxLabel: TLabel
      Left = 73
      Top = 20
      Width = 40
      Height = 13
      AutoSize = False
      Caption = '-1'
    end
    object PixelSumLabel: TLabel
      Left = 73
      Top = 36
      Width = 40
      Height = 13
      AutoSize = False
      Caption = '-1'
    end
    object Label5: TLabel
      Left = 2
      Top = 52
      Width = 68
      Height = 13
      BiDiMode = bdLeftToRight
      Caption = '# pixels bright:'
      ParentBiDiMode = False
    end
    object PixelsAboveThresholdLabel: TLabel
      Left = 73
      Top = 52
      Width = 40
      Height = 13
      AutoSize = False
      Caption = '-1'
    end
    object Label16: TLabel
      Left = 12
      Top = 68
      Width = 58
      Height = 13
      BiDiMode = bdLeftToRight
      Caption = '# pixels dim:'
      ParentBiDiMode = False
    end
    object PixelsBelowThresholdLabel: TLabel
      Left = 73
      Top = 68
      Width = 40
      Height = 13
      AutoSize = False
      Caption = '-1'
    end
    object Label22: TLabel
      Left = 25
      Top = 84
      Width = 45
      Height = 13
      BiDiMode = bdLeftToRight
      Caption = 'Dot level:'
      ParentBiDiMode = False
    end
    object DotLevelLabel: TLabel
      Left = 73
      Top = 84
      Width = 40
      Height = 13
      AutoSize = False
      Caption = '-1'
    end
    object Label24: TLabel
      Left = 24
      Top = 100
      Width = 46
      Height = 13
      BiDiMode = bdLeftToRight
      Caption = 'Rim level:'
      ParentBiDiMode = False
    end
    object RimLevelLabel: TLabel
      Left = 73
      Top = 100
      Width = 40
      Height = 13
      AutoSize = False
      Caption = '-1'
    end
  end
  object MinBright1Edit: TEdit
    Left = 320
    Top = 120
    Width = 41
    Height = 21
    TabOrder = 8
    Text = '20'
    OnKeyPress = BitsPerColEditKeyPress
  end
  object MaxBright0Edit: TEdit
    Left = 320
    Top = 144
    Width = 41
    Height = 21
    TabOrder = 9
    Text = '5'
    OnKeyPress = BitsPerColEditKeyPress
  end
  object BitAnalysisMethodRadioGroup: TRadioGroup
    Left = 8
    Top = 88
    Width = 177
    Height = 73
    Caption = 'Bit analysis method'
    ItemIndex = 0
    Items.Strings = (
      'Avg. brightness within bit-box'
      '# of bright pixels within bit-box'
      'Dot finder')
    TabOrder = 2
  end
  object RimWidthEdit: TEdit
    Left = 320
    Top = 184
    Width = 41
    Height = 21
    TabOrder = 14
    Text = '2'
    OnKeyPress = BitsPerColEditKeyPress
  end
  object DotWidthEdit: TEdit
    Left = 320
    Top = 208
    Width = 41
    Height = 21
    TabOrder = 15
    Text = '2'
    OnKeyPress = BitsPerColEditKeyPress
  end
  object Dot1ThresholdEdit: TEdit
    Left = 216
    Top = 184
    Width = 41
    Height = 21
    TabOrder = 16
    Text = '20'
    OnKeyPress = BitsPerColEditKeyPress
  end
  object Dot0ThresholdEdit: TEdit
    Left = 216
    Top = 208
    Width = 41
    Height = 21
    TabOrder = 17
    Text = '10'
    OnKeyPress = BitsPerColEditKeyPress
  end
  object XBoxesToAnalyzeEdit: TEdit
    Left = 240
    Top = 240
    Width = 121
    Height = 21
    TabOrder = 18
    Text = '1'
    OnKeyPress = YBoxesToAnalyzeEditKeyPress
  end
  object YBoxesToAnalyzeEdit: TEdit
    Left = 240
    Top = 264
    Width = 121
    Height = 21
    TabOrder = 19
    Text = '1'
    OnKeyPress = YBoxesToAnalyzeEditKeyPress
  end
  object BitViewProc: TImageEnProc
    AttachedImageEn = BitView
    Background = clBtnFace
    PreviewsParams = [prppShowResetButton, prppHardReset]
    PreviewFont.Charset = DEFAULT_CHARSET
    PreviewFont.Color = clWindowText
    PreviewFont.Height = -11
    PreviewFont.Name = 'MS Sans Serif'
    PreviewFont.Style = []
    Left = 200
  end
end
