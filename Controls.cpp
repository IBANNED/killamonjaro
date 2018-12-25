/*
Syn's AyyWare Framework 2015
*/

#include "Controls.h"
#include "RenderManager.h"

#pragma region Base Control
void CControl::SetPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}

void CControl::SetSize(int w, int h)
{
	m_iWidth = w;
	m_iHeight = h;
}

void CControl::GetSize(int &w, int &h)
{
	w = m_iWidth;
	h = m_iHeight;
}

bool CControl::Flag(int f)
{
	if (m_Flags & f)
		return true;
	else
		return false;
}

POINT CControl::GetAbsolutePos()
{
	POINT p;
	RECT client = parent->GetClientArea();
	if (parent)
	{
		p.x = m_x + client.left;
		p.y = m_y + client.top + 29;
	}

	return p;
}

void CControl::SetFileId(std::string fid)
{
	FileIdentifier = fid;
}
#pragma endregion Implementations of the Base control functions

#pragma region CSeperate
CSeperate::CSeperate()
{
	m_Flags = UIFlags::UI_Drawable;

	FileControlType = UIControlTypes::UIC_Seperate;
}

void CSeperate::Draw(bool hover) {}

void CSeperate::OnUpdate() {}

void CSeperate::OnClick() {}

#pragma endregion Implementations of the CSeperate

#pragma region ButtonLoad
CButtonLoad::CButtonLoad()
{
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_Clickable;
	FileControlType == UIControlTypes::UIC_Button;
	Text = "Load";
	m_iHeight = 25;
	CallBack = nullptr;
	FileIdentifier = "Default";
}

void CButtonLoad::Draw(bool hover)
{
	POINT a = GetAbsolutePos();
	if (hover)
		Render::GradientV(a.x, a.y, m_iWidth, m_iHeight, Color(55, 55, 55, 255), Color(55, 55, 55, 255));
	else
		Render::GradientV(a.x, a.y, m_iWidth, m_iHeight, Color(45, 45, 45, 255), Color(45, 45, 45, 255));

	Render::Outline(a.x, a.y, m_iWidth, m_iHeight, Color(2, 2, 2, 255));

	RECT TextSize = Render::GetTextSize(Render::Fonts::Menu, Text.c_str());
	int TextX = a.x + (m_iWidth / 2) - (TextSize.right / 2);
	int TextY = a.y + (m_iHeight / 2) - (TextSize.bottom / 2);

	Render::Text2(TextX, TextY, Text.c_str(), Render::Fonts::Menu, Color(180, 180, 180, 200));
}

void CButtonLoad::SetText(std::string text)
{
	Text = text;
}

void CButtonLoad::SetCallback(CButtonLoad::ButtonCallback_t callback)
{
	CallBack = callback;
}

void CButtonLoad::OnUpdate()
{
	m_iHeight = 25;
}

void CButtonLoad::OnClick()
{
	if (CallBack)
		CallBack();
}
#pragma endregion Implementations of the Button functions


#pragma region ButtonSave
CButtonSave::CButtonSave()
{
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_Clickable;
	FileControlType == UIControlTypes::UIC_Button;
	Text = "Save";
	m_iHeight = 25;
	CallBack = nullptr;
	FileIdentifier = "Default";
}

void CButtonSave::Draw(bool hover)
{
	POINT a = GetAbsolutePos();
	if (hover)
		Render::GradientV(a.x, a.y, m_iWidth, m_iHeight, Color(55, 55, 55, 255), Color(55, 55, 55, 255));
	else
		Render::GradientV(a.x, a.y, m_iWidth, m_iHeight, Color(45, 45, 45, 255), Color(45, 45, 45, 255));

	Render::Outline(a.x, a.y, m_iWidth, m_iHeight, Color(2, 2, 2, 255));

	RECT TextSize = Render::GetTextSize(Render::Fonts::Menu, Text.c_str());
	int TextX = a.x + (m_iWidth / 2) - (TextSize.right / 2);
	int TextY = a.y + (m_iHeight / 2) - (TextSize.bottom / 2);

	Render::Text2(TextX, TextY, Text.c_str(), Render::Fonts::Menu, Color(180, 180, 180, 200));
}

void CButtonSave::SetText(std::string text)
{
	Text = text;
}

void CButtonSave::SetCallback(CButtonSave::ButtonCallback_t callback)
{
	CallBack = callback;
}

void CButtonSave::OnUpdate()
{
	m_iHeight = 25;
}

void CButtonSave::OnClick()
{
	if (CallBack)
		CallBack();
}
#pragma endregion Implementations of the Button functions


#pragma region CheckBox
CCheckBox::CCheckBox()
{
	Checked = false;
	bIsSub = false;

	m_Flags = UIFlags::UI_Clickable | UIFlags::UI_Drawable | UIFlags::UI_SaveFile;
	m_iHeight = 9;

	FileControlType = UIControlTypes::UIC_CheckBox;
}


void CCheckBox::SetState(bool s)
{
	Checked = s;
}

bool CCheckBox::GetState()
{
	return Checked;
}

void CCheckBox::Draw(bool hover)
{
	POINT a = GetAbsolutePos();
	Render::GradientV(a.x, a.y, 14, 14, Color(55, 55, 55, 255), Color(30, 30, 30, 255));
	Render::Outline(a.x, a.y, 14, 14, Color(2, 2, 2, 255));

	if (hover)
	{
		Render::Text(a.x + 1, a.y - 1, Color(120, 120, 120, 120), Render::Fonts::MenuSymbols, L"✔");
		Render::Outline(a.x, a.y, 14, 14, Color(120, 120, 120, 255));
	}
	if (Checked)
	{
		Render::Text(a.x + 1, a.y - 1, Color(255, 255, 255, 255), Render::Fonts::MenuSymbols, L"✔");
		Render::Outline(a.x, a.y, 14, 14, Color(2, 2, 2, 255));
	}
}

void CCheckBox::OnUpdate() { m_iHeight = 9; }

void CCheckBox::OnClick()
{

	Checked = !Checked;
}
#pragma endregion Implementations of the Check Box functions

#pragma region Label
CLabel::CLabel()
{
	m_Flags = UIFlags::UI_Drawable;
	Text = "Default";
	FileIdentifier = "Default";
}

void CLabel::Draw(bool hover)
{
	POINT a = GetAbsolutePos();
	Render::Text(a.x, a.y, Color(190, 190, 190, 220), Render::Fonts::Slider, Text.c_str());
}

void CLabel::SetText(std::string text)
{
	Text = text;
}

void CLabel::OnUpdate() {}
void CLabel::OnClick() {}
#pragma endregion Implementations of the Label functions

#pragma region GroupBox
CGroupBox::CGroupBox()
{
	Items = 1;
	iYAdd = 0;
	ItemSpacing = 17;
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_RenderFirst;
	Text = "Default";
	FileIdentifier = "Default";
}

void CGroupBox::Draw(bool hover)
{
	POINT a = GetAbsolutePos();
	RECT txtSize = Render::GetTextSize(Render::Fonts::Slider, Text.c_str());
	Render::Clear(a.x + 2, a.y + 2, m_iWidth - 4, m_iHeight - 4, Color(8, 8, 8, 10)); // menu mini box color
	Render::Text(a.x + 15, a.y - (txtSize.bottom / 2), Color(255, 255, 255, 255), Render::Fonts::Slider, Text.c_str());

	Render::Line(a.x, a.y, a.x + 12, a.y, Color(129, 129, 129, 255));
	Render::Line(a.x + 15 + txtSize.right + 5, a.y, a.x + m_iWidth, a.y, Color(129, 129, 129, 255));
	Render::Line(a.x, a.y, a.x, a.y + m_iHeight, Color(129, 129, 129, 255));
	Render::Line(a.x, a.y + m_iHeight, a.x + m_iWidth, a.y + m_iHeight, Color(129, 129, 129, 255));
	Render::Line(a.x + m_iWidth, a.y, a.x + m_iWidth, a.y + m_iHeight, Color(129, 129, 129, 255));
}

void CGroupBox::SetText(std::string text)
{
	Text = text;
}

void CGroupBox::SetSpacing(int Spacing)
{
	ItemSpacing = Spacing;
}

void CGroupBox::PlaceLabledControl(std::string Label, CTab *Tab, CControl* control)
{
	if (control->FileControlType == UIControlTypes::UIC_CheckBox)
	{
		int x = m_x + 34;
		int y = m_y + Items * ItemSpacing + iYAdd;

		CLabel* label = new CLabel;
		label->SetPosition(x, y);
		label->SetText(Label);
		Tab->RegisterControl(label);

		x = m_x + 12;

		int cw, ch;
		control->SetPosition(x, y);
		control->GetSize(cw, ch);
		control->SetSize((m_iWidth / 2) - 32, ch);
		Tab->RegisterControl(control);
	}
	else if (control->FileControlType == UIControlTypes::UIC_Seperate)
	{
		int x = m_x + 34;
		int y = m_y + Items * ItemSpacing + iYAdd;

		CLabel* label = new CLabel;
		label->SetPosition(x, y);
		label->SetText(Label);
		Tab->RegisterControl(label);

		x = m_x + 16;

		int cw, ch;
		control->SetPosition(x, y);
		control->GetSize(cw, ch);
		control->SetSize((m_iWidth / 1.5), ch);
		Tab->RegisterControl(control);

		iYAdd -= 4;
	}
	else if (control->FileControlType == UIControlTypes::UIC_ComboBox)
	{
		int x = m_x + 34;
		int y = m_y + Items * ItemSpacing + iYAdd;

		x += (m_iWidth / 2) + 42;

		RECT txtSize = Render::GetTextSize(Render::Fonts::supremacy, Label.c_str());
		y = y + 10 - (txtSize.bottom / 2);

		CLabel* label = new CLabel;
		label->SetPosition(x, y);
		label->SetText(Label);
		Tab->RegisterControl(label);

		x = m_x + 34;
		y = m_y + Items * ItemSpacing + iYAdd;

		int cw, ch;
		control->SetPosition(x, y);
		control->GetSize(cw, ch);
		control->SetSize((m_iWidth / 1.5), ch);
		Tab->RegisterControl(control);

		iYAdd += 8;
	}
	else if (control->FileControlType == UIControlTypes::UIC_Slider)
	{
		int x = m_x + 34;
		int y = m_y + Items * ItemSpacing + iYAdd - 1;

		x += m_iWidth / 2;

		CLabel* label = new CLabel;
		label->SetPosition(x, y);
		label->SetText(Label);
		Tab->RegisterControl(label);

		x = m_x + 34;
		y += 1;

		int cw, ch;
		control->SetPosition(x, y);
		control->GetSize(cw, ch);
		control->SetSize((m_iWidth / 1.5), ch);
		Tab->RegisterControl(control);

		iYAdd -= 4;
	}
	else if (control->FileControlType == UIControlTypes::UIC_Slider2)
	{
		int x = m_x + 34;
		int y = m_y + Items * ItemSpacing + iYAdd - 1;

		x += m_iWidth / 2;

		CLabel* label = new CLabel;
		label->SetPosition(x, y);
		label->SetText(Label);
		Tab->RegisterControl(label);

		x = m_x + 34;
		y += 1;

		int cw, ch;
		control->SetPosition(x, y);
		control->GetSize(cw, ch);
		control->SetSize((m_iWidth / 1.5), ch);
		Tab->RegisterControl(control);
	}
	else if (control->FileControlType == UIControlTypes::UIC_Slider3)
	{
		int x = m_x + 34;
		int y = m_y + Items * ItemSpacing + iYAdd - 1;

		x += m_iWidth / 2;

		CLabel* label = new CLabel;
		label->SetPosition(x, y);
		label->SetText(Label);
		Tab->RegisterControl(label);

		x = m_x + 34;
		y += 1;

		int cw, ch;
		control->SetPosition(x, y);
		control->GetSize(cw, ch);
		control->SetSize((m_iWidth / 1.5), ch);
		Tab->RegisterControl(control);
	}
	else if (control->FileControlType == UIControlTypes::UIC_Slider4)
	{
		int x = m_x + 34;
		int y = m_y + Items * ItemSpacing + iYAdd - 1;

		x += m_iWidth / 2;

		CLabel* label = new CLabel;
		label->SetPosition(x, y);
		label->SetText(Label);
		Tab->RegisterControl(label);

		x = m_x + 34;
		y += 1;

		int cw, ch;
		control->SetPosition(x, y);
		control->GetSize(cw, ch);
		control->SetSize((m_iWidth / 1.5), ch);
		Tab->RegisterControl(control);
	}
	else if (control->FileControlType == UIControlTypes::UIC_Button)
	{
		int x = m_x + 34;
		int y = m_y + Items * ItemSpacing + iYAdd;

		x += m_iWidth / 2;

		CLabel* label = new CLabel;
		label->SetPosition(x, y);
		label->SetText(Label);
		Tab->RegisterControl(label);

		x = m_x + 34;

		int cw, ch;
		control->SetPosition(x, y);
		control->GetSize(cw, ch);
		control->SetSize(m_iWidth, 24);
		Tab->RegisterControl(control);

	}
	else
	{
		int x = m_x + 34;
		int y = m_y + Items * ItemSpacing + iYAdd - 1;

		x += m_iWidth / 2;

		CLabel* label = new CLabel;
		label->SetPosition(x, y);
		label->SetText(Label);
		Tab->RegisterControl(label);

		x = m_x + 34;

		int cw, ch;
		control->SetPosition(x, y);
		control->GetSize(cw, ch);
		control->SetSize((m_iWidth / 1.5), ch);
		Tab->RegisterControl(control);
	}
	Items++;
}


void CGroupBox::OnUpdate() {}
void CGroupBox::OnClick() {}
#pragma endregion Implementations of the Group Box functions

#pragma region Sliders
CSlider::CSlider()
{
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_Clickable | UIFlags::UI_SaveFile;
	m_iHeight = 10;
	FileControlType = UIControlTypes::UIC_Slider;
}

void CSlider::Draw(bool hover)
{
	POINT a = GetAbsolutePos();
	RECT Region = { a.x, a.y, m_iWidth, 7 };
	Render::GradientV(a.x, a.y, m_iWidth, 7, Color(32, 32, 32, 255), Color(48, 48, 48, 245));

	float Ratio = (Value - Min) / (Max - Min);
	float Location = Ratio * m_iWidth;



	Render::GradientV(a.x, a.y, Location, 7, Color(255, 255, 255, 255), Color(20, 20, 20, 245));

	Render::Outline(a.x, a.y, m_iWidth, 7, Color(2, 2, 2, 255));

	if (GUI.IsMouseInRegion(Region))
	{
		Render::Outline(a.x, a.y, m_iWidth, 7, Color(120, 120, 120, 255));
	}

	char buffer[24];
	sprintf_s(buffer, "%.f", Value);
	RECT txtSize = Render::GetTextSize(Render::Fonts::Slider, buffer);
	Render::Text(a.x + Location - txtSize.right / 2, a.y + 5, Color(200, 200, 200, 255), Render::Fonts::Slider, buffer);
}
void CSlider::OnUpdate() {
	POINT a = GetAbsolutePos();
	m_iHeight = 15;

	if (DoDrag)
	{
		if (GUI.GetKeyState(VK_LBUTTON))
		{
			POINT m = GUI.GetMouse();
			float NewX;
			float Ratio;
			NewX = m.x - a.x;//-1
			if (NewX < 0)
				NewX = 0;
			if (NewX > m_iWidth)
				NewX = m_iWidth;
			Ratio = NewX / float(m_iWidth);
			Value = Min + (Max - Min)*Ratio;
		}
		else
		{
			DoDrag = false;
		}
	}
}

void CSlider::OnClick() {
	POINT a = GetAbsolutePos();
	RECT SliderRegion = { a.x, a.y, m_iWidth, 11 };
	if (GUI.IsMouseInRegion(SliderRegion))
	{
		DoDrag = true;
	}
}

float CSlider::GetValue()
{
	return Value;
}

void CSlider::SetValue(float v)
{
	Value = v;
}

void CSlider::SetBoundaries(float min, float max)
{
	Min = min; Max = max;
}

#pragma endregion Implementations of the Slider functions
#pragma region KeyBinders

char* KeyStrings[254] = { nullptr, "Left Mouse", "Right Mouse", "Control+Break", "Middle Mouse", "Mouse 4", "Mouse 5",
nullptr, "Backspace", "TAB", nullptr, nullptr, nullptr, "ENTER", nullptr, nullptr, "SHIFT", "CTRL", "ALT", "PAUSE",
"CAPS LOCK", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "ESC", nullptr, nullptr, nullptr, nullptr, "SPACEBAR",
"PG UP", "PG DOWN", "END", "HOME", "Left", "Up", "Right", "Down", nullptr, "Print", nullptr, "Print Screen", "Insert",
"Delete", nullptr, "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X",
"Y", "Z", "Left Windows", "Right Windows", nullptr, nullptr, nullptr, "NUM 0", "NUM 1", "NUM 2", "NUM 3", "NUM 4", "NUM 5", "NUM 6",
"NUM 7", "NUM 8", "NUM 9", "*", "+", "_", "-", ".", "/", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
"F13", "F14", "F15", "F16", "F17", "F18", "F19", "F20", "F21", "F22", "F23", "F24", nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, "NUM LOCK", "SCROLL LOCK", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, "LSHIFT", "RSHIFT", "LCONTROL", "RCONTROL", "LMENU", "RMENU", nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "Next Track", "Previous Track", "Stop", "Play/Pause", nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, ";", "+", ",", "-", ".", "/?", "~", nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "[{", "\\|", "}]", "'\"", nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };

CKeyBind::CKeyBind()
{
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_Clickable | UIFlags::UI_SaveFile;
	FileControlType = UIControlTypes::UIC_KeyBind;
}

void CKeyBind::Draw(bool hover)
{
	POINT a = GetAbsolutePos();

	Render::Outline(a.x, a.y, m_iWidth, m_iHeight, Color(129, 129, 129, 255));
	if (hover)
		Render::Clear(a.x + 2, a.y + 2, m_iWidth - 4, m_iHeight - 4, Color(255, 255, 255, 80));
	bool GoodKeyName = false;
	char NameBuffer[128];
	char* KeyName = "not bound";

	if (IsGettingKey)
	{
		KeyName = "pree a key";
	}
	else
	{
		if (Key >= 0)
		{
			KeyName = KeyStrings[Key];
			if (KeyName)
			{
				GoodKeyName = true;
			}
			else
			{
				if (GetKeyNameText(Key << 16, NameBuffer, 127))
				{
					KeyName = NameBuffer;
					GoodKeyName = true;
				}
			}
		}

		if (!GoodKeyName)
		{
			KeyName = "no key...";
		}
	}


	Render::Text(a.x + 2, a.y + 2, Color(255, 255, 255, 255), Render::Fonts::Slider, KeyName);
}

void CKeyBind::OnUpdate() {
	m_iHeight = 16;
	POINT a = GetAbsolutePos();
	if (IsGettingKey)
	{
		for (int i = 0; i < 255; i++)
		{
			if (GUI.GetKeyPress(i))
			{
				if (i == VK_ESCAPE)
				{
					IsGettingKey = false;
					Key = -1;
					return;
				}

				Key = i;
				IsGettingKey = false;
				return;
			}
		}
	}
}

void CKeyBind::OnClick() {
	POINT a = GetAbsolutePos();
	if (!IsGettingKey)
	{
		IsGettingKey = true;
	}
}

int CKeyBind::GetKey()
{
	return Key;
}

void CKeyBind::SetKey(int key)
{
	Key = key;
}

#pragma endregion Implementations of the KeyBind Control functions

#pragma region Button
CButton::CButton()
{
	m_iWidth = 177;
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_Clickable;
	Text = "Default";
	CallBack = nullptr;
	FileIdentifier = "Default";
}

void CButton::Draw(bool hover)
{
	POINT a = GetAbsolutePos();
	Render::Outline(a.x, a.y, m_iWidth, m_iHeight, Color(129, 129, 129, 255));
	if (hover)
		Render::GradientV(a.x + 2, a.y + 2, m_iWidth - 4, m_iHeight - 4, Color(60, 60, 60, 255), Color(80, 80, 80, 255));
	else
		Render::GradientV(a.x + 2, a.y + 2, m_iWidth - 4, m_iHeight - 4, Color(8, 8, 8, 255), Color(8, 8, 8, 255));

	RECT TextSize = Render::GetTextSize(Render::Fonts::Slider, Text.c_str());
	int TextX = a.x + (m_iWidth / 2) - (TextSize.left / 2);
	int TextY = a.y + (m_iHeight / 2) - (TextSize.bottom / 2);

	Render::Text(TextX, TextY, Color(255, 255, 255, 255), Render::Fonts::Slider, Text.c_str());
}

void CButton::SetText(std::string text)
{
	Text = text;
}

void CButton::SetCallback(CButton::ButtonCallback_t callback)
{
	CallBack = callback;
}

void CButton::OnUpdate()
{
	m_iHeight = 26;
}

void CButton::OnClick()
{
	if (CallBack)
		CallBack();
}
#pragma endregion Implementations of the Button functions

#pragma region ccombobox
CComboBox::CComboBox()
{
	m_Flags = UIFlags::UI_Drawable | UIFlags::UI_Clickable | UIFlags::UI_Focusable | UIFlags::UI_SaveFile;
	m_iHeight = 20;
	FileControlType = UIControlTypes::UIC_ComboBox;
}


void CComboBox::Draw(bool hover)
{
	POINT a = GetAbsolutePos();
	RECT Region = { a.x, a.y, m_iWidth, 20 };
	Render::GradientV(a.x, a.y, m_iWidth, 20, Color(45, 45, 45, 255), Color(45, 45, 45, 255));
	if (GUI.IsMouseInRegion(Region)) Render::GradientV(a.x, a.y, m_iWidth, 20, Color(55, 55, 55, 255), Color(55, 55, 55, 255));
	Render::Outline(a.x, a.y, m_iWidth, 20, Color(2, 2, 2, 255));

	if (Items.size() > 0)
	{
		RECT txtSize = Render::GetTextSize(Render::Fonts::supremacy, GetItem().c_str());
		Render::Text2(a.x + 10, a.y + (Region.bottom / 2) - (txtSize.bottom / 2), GetItem().c_str(), Render::Fonts::supremacy, Color(180, 180, 180, 245));

		if (IsOpen)
		{
			Render::GradientV(a.x, a.y + 20, m_iWidth, Items.size() * 20, Color(45, 45, 45, 255), Color(45, 45, 45, 255));

			for (int i = 0; i < Items.size(); i++)
			{
				RECT ItemRegion = { a.x, a.y + 17 + i * 20, m_iWidth, 20 };

				if (GUI.IsMouseInRegion(ItemRegion))
				{
					Render::GradientV(a.x, a.y + 20 + i * 20, m_iWidth, 20, Color(35, 35, 35, 255), Color(35, 35, 35, 255));
				}

				RECT control_textsize = Render::GetTextSize(Render::Fonts::supremacy, Items[i].c_str());
				if (i == SelectedIndex)
					Render::Text2(a.x + 10, a.y + 20 + (i * 20) + 10 - (control_textsize.bottom / 2), Items[i].c_str(), Render::Fonts::supremacy, Color(159, 209, 20, 255));
				else
					Render::Text2(a.x + 10, a.y + 20 + (i * 20) + 10 - (control_textsize.bottom / 2), Items[i].c_str(), Render::Fonts::supremacy, Color(180, 180, 180, 245));
			}
			Render::Outline(a.x, a.y + 20, m_iWidth, Items.size() * 20, Color(2, 2, 2, 255));
		}
	}
	Vertex_t Verts2[3];
	Verts2[0].m_Position.x = a.x + m_iWidth - 10;
	Verts2[0].m_Position.y = a.y + 9;
	Verts2[1].m_Position.x = a.x + m_iWidth - 5;
	Verts2[1].m_Position.y = a.y + 9;
	Verts2[2].m_Position.x = a.x + m_iWidth - 7.5;
	Verts2[2].m_Position.y = a.y + 12;

	Render::Polygon(3, Verts2, Color(92, 92, 92, 255));
}

void CComboBox::AddItem(std::string text)
{
	Items.push_back(text);
	SelectedIndex = 0;
}

void CComboBox::OnUpdate()
{
	if (IsOpen)
	{
		m_iHeight = 20 + 20 * Items.size();

		if (parent->GetFocus() != this)
			IsOpen = false;
	}
	else
	{
		m_iHeight = 20;
	}

}

void CComboBox::OnClick()
{
	POINT a = GetAbsolutePos();
	RECT Region = { a.x, a.y, m_iWidth, 20 };

	if (IsOpen)
	{
		// If we clicked one of the items(Not in the top bar)
		if (!GUI.IsMouseInRegion(Region))
		{
			// Draw the items
			for (int i = 0; i < Items.size(); i++)
			{
				RECT ItemRegion = { a.x, a.y + 20 + i * 20, m_iWidth, 20 };

				// Hover
				if (GUI.IsMouseInRegion(ItemRegion))
				{
					SelectedIndex = i;
				}
			}
		}

		// Close the drop down
		IsOpen = false;
	}
	else
	{
		IsOpen = true;
	}

}

int CComboBox::GetIndex()
{
	return SelectedIndex;
}

void CComboBox::SetIndex(int index)
{
	SelectedIndex = index;
}

std::string CComboBox::GetItem()
{
	if (SelectedIndex >= 0 && SelectedIndex < Items.size())
	{
		return Items[SelectedIndex];
	}

	return "";
}

void CComboBox::SelectIndex(int idx)
{
	if (idx >= 0 && idx < Items.size())
	{
		SelectedIndex = idx;
	}
}
#pragma endregion ccombobox
