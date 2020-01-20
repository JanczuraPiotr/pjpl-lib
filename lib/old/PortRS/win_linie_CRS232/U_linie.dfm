object F_Linie: TF_Linie
  Left = 472
  Top = 385
  Width = 315
  Height = 208
  BorderIcons = [biSystemMenu]
  Caption = 'Linie RS232'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object CKB_DTR: TCheckBox
    Left = 24
    Top = 44
    Width = 97
    Height = 17
    Caption = 'DTR'
    Enabled = False
    TabOrder = 0
    OnClick = CKB_DTRClick
  end
  object CKB_RTS: TCheckBox
    Left = 24
    Top = 68
    Width = 97
    Height = 17
    Caption = 'RTS'
    Enabled = False
    TabOrder = 1
    OnClick = CKB_RTSClick
  end
  object RB_StanDSR: TRadioButton
    Left = 176
    Top = 44
    Width = 113
    Height = 17
    Caption = 'DSR'
    Enabled = False
    TabOrder = 2
  end
  object RB_StanCTS: TRadioButton
    Left = 176
    Top = 68
    Width = 113
    Height = 17
    Caption = 'CTS'
    Enabled = False
    TabOrder = 3
  end
  object RB_StanRI: TRadioButton
    Left = 176
    Top = 92
    Width = 113
    Height = 17
    Caption = 'RI'
    Enabled = False
    TabOrder = 4
  end
  object RB_StanDCD: TRadioButton
    Left = 176
    Top = 116
    Width = 113
    Height = 17
    Caption = 'DCD'
    Enabled = False
    TabOrder = 5
  end
  object CKB_PrzelaczajDTR: TCheckBox
    Left = 24
    Top = 92
    Width = 97
    Height = 17
    Caption = 'Prze'#322#261'czaj DTR'
    Checked = True
    Enabled = False
    State = cbChecked
    TabOrder = 6
    OnClick = CKB_PrzelaczajDTRClick
  end
  object CKB_PrzelaczajRTS: TCheckBox
    Left = 24
    Top = 116
    Width = 97
    Height = 17
    Caption = 'Prze'#322#261'czaj RTS'
    Checked = True
    Enabled = False
    State = cbChecked
    TabOrder = 7
    OnClick = CKB_PrzelaczajRTSClick
  end
  object EDT_Port: TEdit
    Left = 24
    Top = 10
    Width = 99
    Height = 21
    TabOrder = 8
    Text = 'COM1'
  end
  object BTN_OtworzPort: TButton
    Left = 134
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Otworz Port'
    TabOrder = 9
    OnClick = BTN_OtworzPortClick
  end
  object BTN_ZamknijPort: TButton
    Left = 212
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Zamknij Port'
    Enabled = False
    TabOrder = 10
    OnClick = BTN_ZamknijPortClick
  end
  object TMR_PrzelaczajRTS: TTimer
    Enabled = False
    Interval = 500
    OnTimer = TMR_PrzelaczajRTSTimer
    Left = 58
    Top = 144
  end
  object TMR_PrzelaczajDTR: TTimer
    Enabled = False
    Interval = 500
    OnTimer = TMR_PrzelaczajDTRTimer
    Left = 22
    Top = 144
  end
  object TMR_SprawdzajLinie: TTimer
    Enabled = False
    Interval = 100
    OnTimer = TMR_SprawdzajLinieTimer
    Left = 178
    Top = 142
  end
end
