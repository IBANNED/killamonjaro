/*
Syn's AyyWare Framework 2015
*/

#pragma once

#include "GUI.h"

#include "Interfaces.h"

void CWindow::SetPosition(int x, int y)
{
	m_x = x; m_y = y;
}

void CWindow::SetSize(int w, int h)
{
	m_iWidth = w;
	m_iHeight = h;
}

void CWindow::SetTitle(std::string title)
{
	Title = title;
}

void CWindow::RegisterTab(CTab* Tab)
{
	if (Tabs.size() == 0)
	{
		SelectedTab = Tab;
	}
	Tab->parent = this;
	Tabs.push_back(Tab);
}

RECT CWindow::GetClientArea()
{
	RECT client;
	client.left = m_x + 8;
	client.top = m_y + 1 + 27;
	client.right = m_iWidth - 4 - 12;
	client.bottom = m_iHeight - 2 - 8 - 26;
	return client;
}

RECT CWindow::GetTabArea()
{
	RECT client;
	client.left = m_x + 8;
	client.top = m_y + 1 + 27;
	client.right = m_iWidth - 4 - 12;
	client.bottom = 29;
	return client;
}

void CWindow::Open()
{
	m_bIsOpen = true;
}

void CWindow::Close()
{
	m_bIsOpen = false;
}

bool CWindow::isOpen()
{
	return m_bIsOpen;
}

void CWindow::Toggle()
{
	m_bIsOpen = !m_bIsOpen;
	static ConVar * cvar = Interfaces::CVar->FindVar("cl_mouseenable");
	if (m_bIsOpen)
	{
		cvar->SetValue(0);
	}
	else
	{
		cvar->SetValue(1);
	}
}

CControl* CWindow::GetFocus()
{
	return FocusedControl;
}

// TABS ---------------------------------------------------------------------------------------------------

void CTab::SetTitle(std::string name)
{
	Title = name;
}

void CTab::SetTitle2(std::string name2)
{
	Title2 = name2;
}

void CTab::SetTitle3(std::string name3)
{
	Title3 = name3;
}

void CTab::SetTitle4(std::string name4)
{
	Title4 = name4;
}

void CTab::SetTitle5(std::string name5)
{
	Title5 = name5;
}

void CTab::RegisterControl(CControl* control)
{
	control->parent = parent;
	Controls.push_back(control);
}