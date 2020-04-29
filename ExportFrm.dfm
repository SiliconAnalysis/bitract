object ExportForm: TExportForm
  Left = 553
  Top = 122
  Width = 651
  Height = 190
  Caption = 'Export options'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object ROMLayoutRadioGroup: TRadioGroup
    Left = 8
    Top = 8
    Width = 225
    Height = 65
    Caption = 'ROM layout'
    ItemIndex = 0
    Items.Strings = (
      'Standard (1 bit per output column)'
      'Mirrored halves (1 bit per output column)')
    TabOrder = 0
    OnClick = ROMLayoutRadioGroupClick
  end
  object AdditionalOptionsGroupBox: TGroupBox
    Left = 248
    Top = 8
    Width = 372
    Height = 113
    Caption = 'Additional options'
    TabOrder = 1
    object OutputBitOrderLabel: TLabel
      Left = 8
      Top = 84
      Width = 76
      Height = 13
      Caption = 'Output bit order:'
    end
    object ReverseOutputsCheckbox: TCheckBox
      Left = 16
      Top = 24
      Width = 297
      Height = 17
      Caption = 'Reverse output bit order (bit 0 = rightmost output column)'
      TabOrder = 0
      OnClick = ReverseOutputsCheckboxClick
    end
    object ReverseWithinOutColCheckbox: TCheckBox
      Left = 16
      Top = 48
      Width = 349
      Height = 17
      Caption = 
        'Addresses run right-to-left (byte 0 = rightmost bit within outpu' +
        't column)'
      TabOrder = 1
      OnClick = ReverseWithinOutColCheckboxClick
    end
    object OutputBitOrderEdit: TEdit
      Left = 88
      Top = 80
      Width = 275
      Height = 21
      TabOrder = 2
      OnExit = OutputBitOrderEditExit
      OnKeyPress = OutputBitOrderEditKeyPress
    end
  end
  object EndianRadioGroup: TRadioGroup
    Left = 8
    Top = 96
    Width = 225
    Height = 49
    Caption = 'Endianness'
    ItemIndex = 1
    Items.Strings = (
      'Little endian (least significant byte first)'
      'Big endian (most significant byte first)')
    TabOrder = 2
    OnClick = EndianRadioGroupClick
  end
end
