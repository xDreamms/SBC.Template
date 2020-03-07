#include "Header.h"
#include "Main.h"

//Plugin Definitions
PLUGIN_API const char PLUGIN_PRINT_NAME[32] = "Template";
PLUGIN_API const char PLUGIN_PRINT_AUTHOR[32] = "xDreamms";
PLUGIN_API ChampionId PLUGIN_TARGET_CHAMP = ChampionId::Unknown; // Change these according to your champion


bool Loaded = false;
PLUGIN_API bool OnLoadSDK(IPluginsSDK* plugin_sdk)
{
	DECLARE_GLOBALS(plugin_sdk);
	//if you are writing for a particular champion use this
	// if(g_LocalPlayer->ChampionId() == ChampionId::Aatrox)
	// {
	// 	
	// }
	//Main Entry, Main Load
	MainSpace::Main::LoadMain();
	Loaded = true;
	return true;
}
PLUGIN_API void OnUnloadSDK()
{
	if (Loaded)
	{
		//Unload if its loaded.
		MainSpace::Main::UnLoadMain();
	}
}
