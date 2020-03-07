#include "Main.h"
namespace  MainSpace
{
	IMenu* MainMenu = nullptr;
	IMenuElement* QColor = nullptr;
	std::shared_ptr<ISpell> Q;
	float lastQ = 0.f;
	
	void Main::LoadMain()
	{
		InitializeSpells();
		InitializeMenu();
		InitializeEvents();
		g_Common->ChatPrint("<font color='#2CC04F' size='30'>... successfully loaded. </font>");
	}

	void Main::UnLoadMain()
	{
		//You have to unload your plugins.
		EventHandler<Events::GameUpdate>::RemoveEventHandler(OnUpdate);
		EventHandler<Events::OnHudDraw>::RemoveEventHandler(OnDraw);
		MainMenu->Remove();
		g_Log->Print("Unloaded");
	}

	void InitializeSpells()
	{
		Q = g_Common->AddSpell(SpellSlot::Q, 1000.f);
		Q->SetSkillshot(0.25f, 50.f, 2000.f, kCollidesWithMinions, kSkillshotLine);
	}

	void InitializeMenu()
	{
		//Create Menu
		MainMenu = g_Menu->CreateMenu("Main Menu", "Main Menu");
		//Add menu item to main menu
		QColor = MainMenu->AddColorPicker("Q Color", "QColor", 255, 0, 0, 255);
	}

	void InitializeEvents()
	{
		//Add event handlers
		EventHandler<Events::GameUpdate>::AddEventHandler(OnUpdate);
		EventHandler<Events::OnHudDraw>::AddEventHandler(OnDraw);
	}

	void OnUpdate()
	{
		//Check Active Orbwalker mode  
		if(g_Orbwalker->IsModeActive(eOrbwalkingMode::kModeCombo))
		{
			Combo();
		}
		//Check Active Orbwalker mode  
		if (g_Orbwalker->IsModeActive(eOrbwalkingMode::kModeLaneClear))
		{
			LaneClear();
		}
	}

	void OnDraw()
	{
		//Draw a circle with radius of Q range.
		g_Drawing->AddCircle(g_LocalPlayer->Position(), Q->Range(), QColor->GetColor(), 1.75f);
	}

	void Combo()
	{
		//Get target from Target Selector
		auto target = g_Common->GetTarget(Q->Range(), DamageType::Physical);
		//Check target is null or not. Check target is dead or not. If target is not valid return
		if(target == nullptr || target->IsDead() || target->IsInvulnerable()) return;
		//Check Q is ready for casting
		if(Q->IsReady() && lastQ + 0.5f < g_Common->Time()/*For Anti DC*/)
		{
			//Q is ready so cast Q. If Q is skillshot you have to specify Hitchance. Don't forget!
			Q->Cast(target, HitChance::High);
			lastQ = g_Common->Time();/*For Anti DC*/
		}
	}
	void LaneClear()
	{
		/*I recommend to you use cpplinq library for linq expressions. You can install it via nuget and you can ask for its syntax to me*/
		//Get Lane Minions
		for (auto x : g_ObjectManager->GetMinionsEnemy())
		{
			//check minion is valid in Q range
			if(x->IsValidTarget(Q->Range()) && lastQ + 0.5f < g_Common->Time()/*For Anti DC*/)
			{
				Q->Cast(x, HitChance::High);
				lastQ = g_Common->Time(); /*For Anti DC*/
			}
		}
	}
}
