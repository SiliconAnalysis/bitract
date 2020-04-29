object ImageForm: TImageForm
  Left = 928
  Top = 116
  Width = 726
  Height = 639
  Caption = 'Image'
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
  object ImageView: TImageEnVect
    Left = 0
    Top = 0
    Width = 710
    Height = 581
    ParentCtl3D = False
    LegacyBitmap = False
    OnImageChange = ImageViewImageChange
    OnZoomIn = ImageViewZoomIn
    OnZoomOut = ImageViewZoomOut
    ImageEnVersion = '3.0.2'
    EnableInteractionHints = True
    Align = alClient
    TabOrder = 0
    OnDblClick = ImageViewDblClick
    OnMouseMove = ImageViewMouseMove
    OnKeyPress = ImageViewKeyPress
    OnVectorialChanged = ImageViewVectorialChanged
  end
  object MainMenu: TMainMenu
    Top = 8
    object File1: TMenuItem
      Caption = '&File'
      object OpenImageButton: TMenuItem
        Caption = '&Open image...'
        OnClick = OpenImageButtonClick
      end
      object Saveimageas1: TMenuItem
        Caption = '&Save image as...'
        OnClick = Saveimageas1Click
      end
      object Loadsettings1: TMenuItem
        Caption = '&Load settings...'
        OnClick = Loadsettings1Click
      end
      object Savesettings1: TMenuItem
        Caption = 'Save se&ttings...'
        OnClick = Savesettings1Click
      end
      object Exportbits1: TMenuItem
        Caption = '&Export bits to file...'
        OnClick = Exportbits1Click
      end
    end
    object Edit1: TMenuItem
      Caption = '&Edit'
      object Undo1: TMenuItem
        Caption = '&Undo image processing'
        ShortCut = 16474
        OnClick = Undo1Click
      end
      object Redo1: TMenuItem
        Caption = '&Redo image processing'
        ShortCut = 24666
        OnClick = Redo1Click
      end
    end
    object View1: TMenuItem
      Caption = '&View'
      object Fittowindow1: TMenuItem
        Caption = '&Fit to window'
        OnClick = Fittowindow1Click
      end
      object ZoomIn1: TMenuItem
        Caption = 'Zoom &In'
        OnClick = ZoomIn1Click
      end
      object ZoomOut1: TMenuItem
        Caption = 'Zoom &Out'
        OnClick = ZoomOut1Click
      end
      object Zoom1001: TMenuItem
        Caption = 'Zoom &100%'
        OnClick = Zoom1001Click
      end
      object Transparency1: TMenuItem
        Caption = 'Overlay transparency 0%'
        OnClick = Transparency1Click
      end
      object Transparency501: TMenuItem
        Caption = 'Overlay transparency 50%'
        OnClick = Transparency501Click
      end
      object Transparency801: TMenuItem
        Caption = 'Overlay transparency 80%'
        OnClick = Transparency801Click
      end
    end
    object Processing2: TMenuItem
      Caption = ' &Processing'
      object Processing1: TMenuItem
        Caption = 'Image &processing...'
        OnClick = Processing1Click
      end
      object Calcmultipliers1: TMenuItem
        Caption = '&Calc. flatfield multipliers'
        OnClick = Calcmultipliers1Click
      end
      object ApplyMultipliersButton: TMenuItem
        Caption = 'App&ly flatfield multipliers'
        OnClick = ApplyMultipliersButtonClick
      end
    end
    object Cursor1: TMenuItem
      Caption = '&Cursor'
      object EditPolyline1: TMenuItem
        Caption = 'Adjust box corners'
        OnClick = EditPolyline1Click
      end
    end
    object Objects1: TMenuItem
      Caption = '&Area Of Interest'
      object ShowROMBox1: TMenuItem
        Caption = 'Show Area Of Interest overlay'
        OnClick = ShowROMBox1Click
      end
      object ResetROMBox1: TMenuItem
        Caption = 'Reset AOI overlay'
        OnClick = ResetROMBox1Click
      end
      object Clearallobjects1: TMenuItem
        Caption = '&Clear bit-boxes'
        OnClick = Clearallobjects1Click
      end
      object FillROMBox1: TMenuItem
        Caption = 'Analyze bits within AOI'
        OnClick = FillROMBox1Click
      end
    end
  end
  object SaveImageDialog: TSaveDialog
    DefaultExt = '.jpg'
    FileName = 'capture'
    Filter = 
      'JPEG image (*.jpg)|*.jpg|TIFF image (*.tif)|*.tif|PNG image (*.p' +
      'ng)|*.png|GIF image (*.gif)|*.gif|BMP image (*.bmp)|*.bmp'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofPathMustExist, ofEnableSizing]
    Title = 'Select filename for saved image'
    Left = 32
  end
  object ImageProc: TImageEnProc
    AttachedImageEn = ImageView
    Background = clBtnFace
    PreviewsParams = [prppShowResetButton, prppHardReset]
    PreviewFont.Charset = DEFAULT_CHARSET
    PreviewFont.Color = clWindowText
    PreviewFont.Height = -11
    PreviewFont.Name = 'MS Sans Serif'
    PreviewFont.Style = []
    Left = 80
    Top = 16
  end
  object OpenImageDialog: TOpenDialog
    Filter = 
      'Image files (*.tif;*.jpg;*.png;*.bmp)|*.tif;*.jpg;*.png;*.bmp|TI' +
      'FF files (*.tif)|*.tif|JPEG files (*.jpg)|*.jpg|PNG files (*.png' +
      ')|*.png|BMP files (*.bmp)|*.bmp'
    Options = [ofHideReadOnly, ofPathMustExist, ofFileMustExist, ofEnableSizing]
    Left = 40
    Top = 72
  end
  object ROMBitSaveDialog: TSaveDialog
    DefaultExt = '.txt'
    Filter = 'Text files|*.txt'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofPathMustExist, ofEnableSizing]
    Left = 8
    Top = 32
  end
  object OpenSettingsDialog: TOpenDialog
    DefaultExt = '.ini'
    Filter = 'Settings files (*.ini)|*.ini'
    Options = [ofHideReadOnly, ofPathMustExist, ofFileMustExist, ofEnableSizing]
    Title = 'Load bitract settings file...'
    Left = 72
    Top = 72
  end
  object SaveSettingsDialog: TSaveDialog
    DefaultExt = '.ini'
    FileName = 'bitsettings'
    Filter = 'Settings files (*.ini)|*.ini'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofPathMustExist, ofEnableSizing]
    Title = 'Save settings...'
    Left = 72
    Top = 96
  end
end
