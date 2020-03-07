#pragma once
#include "Header.h"

namespace  MainSpace
{
	class Main
	{
	public:
		static void LoadMain();
		static void UnLoadMain();
	};
	void InitializeSpells();
	void InitializeMenu();
	void InitializeEvents();
	void OnUpdate();
	void OnDraw();
	void Combo();
	void LaneClear();
}


