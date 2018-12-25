/*
Syn's AyyWare Framework 2015
*/

#include "Menu.h"
#include "Controls.h"
#include "Hooks.h" // for the unload meme
#include "Interfaces.h"
#include "CRC32.h"

#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 470

AyyWareWindow Menu::Window;

void SaveLegitCallbk()
{
	switch (Menu::Window.MiscTab.lstPlayers.GetIndex())
	{
	case 0:GUI.SaveWindowState(&Menu::Window, "1.cfg"); break;
	case 1:GUI.SaveWindowState(&Menu::Window, "2.cfg"); break;
	case 2:GUI.SaveWindowState(&Menu::Window, "3.cfg"); break;
	case 3:GUI.SaveWindowState(&Menu::Window, "4.cfg"); break;
	case 4:GUI.SaveWindowState(&Menu::Window, "5.cfg"); break;
	case 5:GUI.SaveWindowState(&Menu::Window, "6.cfg"); break;
	}
}

void LoadLegitCallbk()
{
	static ConVar* Meme = Interfaces::CVar->FindVar("cl_fullupdate");
	Interfaces::Engine->ClientCmd_Unrestricted("cl_fullupdate");
	switch (Menu::Window.MiscTab.lstPlayers.GetIndex())
	{
	case 0:GUI.LoadWindowState(&Menu::Window, "1.cfg"); break;
	case 1:GUI.LoadWindowState(&Menu::Window, "2.cfg"); break;
	case 2:GUI.LoadWindowState(&Menu::Window, "3.cfg"); break;
	case 3:GUI.LoadWindowState(&Menu::Window, "4.cfg"); break;
	case 4:GUI.LoadWindowState(&Menu::Window, "5.cfg"); break;
	case 5:GUI.LoadWindowState(&Menu::Window, "6.cfg"); break;
	}
}

void UnLoadCallbk()
{
	DoUnload = true;
}

void KnifeApplyCallbk()
{
	static ConVar* Meme = Interfaces::CVar->FindVar("cl_fullupdate");
	Meme->nFlags &= ~FCVAR_CHEAT;
	Interfaces::Engine->ClientCmd_Unrestricted("cl_fullupdate");
}

void AyyWareWindow::Setup()
{
	SetPosition(50, 50);
	SetSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	SetTitle("killamonjaro");

	RegisterTab(&RageBotTab);
	RegisterTab(&LegitBotTab);
	RegisterTab(&VisualsTab);
	RegisterTab(&MiscTab);

	RECT Client = GetClientArea();
	Client.bottom -= 29;

	RageBotTab.Setup();
	LegitBotTab.Setup();
	VisualsTab.Setup();
	MiscTab.Setup();

}

void CRageBotTab::Setup()
{
	SetTitle("rage");
	SetTitle2("C");

	AimbotGroup.SetPosition(5, 13);
	AimbotGroup.SetText("aimbot");
	AimbotGroup.SetSize(340, 180);
	RegisterControl(&AimbotGroup);

	AimbotEnable.SetFileId("aim_enable");
	AimbotGroup.PlaceLabledControl("enable", this, &AimbotEnable);

	AimbotAutoFire.SetFileId("aim_autofire");
	AimbotGroup.PlaceLabledControl("auto fire", this, &AimbotAutoFire);

	aimbotfov2.SetFileId("");
	AimbotGroup.PlaceLabledControl("field of view", this, &aimbotfov2);

	AimbotFov.SetFileId("aim_fov");
	AimbotFov.SetBoundaries(0.f, 180.f);
	AimbotFov.SetValue(39.f);
	AimbotGroup.PlaceLabledControl("", this, &AimbotFov);

	AimbotSilentAim.SetFileId("aim_silent");
	AimbotGroup.PlaceLabledControl("silent aim", this, &AimbotSilentAim);

	AimbotAutoPistol.SetFileId("aim_autopistol");
	AimbotGroup.PlaceLabledControl("auto pistol", this, &AimbotAutoPistol);

#pragma endregion Aimbot Controls Get Setup in here

#pragma region Target
	TargetGroup.SetPosition(5, 205);
	TargetGroup.SetText("target");
	TargetGroup.SetSize(340, 195);
	RegisterControl(&TargetGroup);

	targetselection2.SetFileId("");
	TargetGroup.PlaceLabledControl("selection", this, &targetselection2);

	TargetSelection.SetFileId("tgt_selection");
	TargetSelection.AddItem("closest to crosshair");
	TargetSelection.AddItem("distance");
	TargetSelection.AddItem("lowest health");
	TargetGroup.PlaceLabledControl("", this, &TargetSelection);

	TargetFriendlyFire.SetFileId("tgt_friendlyfire");
	TargetGroup.PlaceLabledControl("friendly fire", this, &TargetFriendlyFire);

	targethitbox2.SetFileId("");
	TargetGroup.PlaceLabledControl("hitbox", this, &targethitbox2);

	TargetHitbox.SetFileId("tgt_hitbox");
	TargetHitbox.AddItem("head");
	TargetHitbox.AddItem("neck");
	TargetHitbox.AddItem("chest");
	TargetHitbox.AddItem("stomach");
	TargetHitbox.AddItem("shins");
	TargetGroup.PlaceLabledControl("", this, &TargetHitbox);

	targethitscan2.SetFileId("");
	TargetGroup.PlaceLabledControl("hitscan", this, &targethitscan2);

	TargetHitscan.SetFileId("tgt_hitscan");
	TargetHitscan.AddItem("off"); //0
	TargetHitscan.AddItem("low"); // 1
	TargetHitscan.AddItem("medium"); // 2
	TargetHitscan.AddItem("high"); // 3
	TargetHitscan.AddItem("extreme"); // 4
	TargetGroup.PlaceLabledControl("", this, &TargetHitscan);

	TargetMultipoint.SetFileId("tgt_multipoint");
	TargetGroup.PlaceLabledControl("multipoint", this, &TargetMultipoint);

	TargetPointscale.SetFileId("tgt_pointscale");
	TargetPointscale.SetBoundaries(0.f, 10.f);
	TargetPointscale.SetValue(5.f);
	TargetGroup.PlaceLabledControl("", this, &TargetPointscale);
#pragma endregion Targetting controls 

#pragma region Accuracy
	AccuracyGroup.SetPosition(360, 13);
	AccuracyGroup.SetText("accuracy");
	AccuracyGroup.SetSize(340, 210); //280
	RegisterControl(&AccuracyGroup);

	AccuracyRecoil.SetFileId("acc_norecoil");
	AccuracyGroup.PlaceLabledControl("anti recoil", this, &AccuracyRecoil);

	AccuracyAutoWall.SetFileId("acc_awall");
	AccuracyGroup.PlaceLabledControl("auto wall", this, &AccuracyAutoWall);

	accuracyminimumdamage2.SetFileId("");
	AccuracyGroup.PlaceLabledControl("autowall damage", this, &accuracyminimumdamage2);

	AccuracyMinimumDamage.SetFileId("acc_mindmg");
	AccuracyMinimumDamage.SetBoundaries(1.f, 99.f);
	AccuracyMinimumDamage.SetValue(1.f);
	AccuracyGroup.PlaceLabledControl("", this, &AccuracyMinimumDamage);

	AccuracyAutoScope.SetFileId("acc_scope");
	AccuracyGroup.PlaceLabledControl("auto scope", this, &AccuracyAutoScope);

	accuracyhitchance2.SetFileId("");
	AccuracyGroup.PlaceLabledControl("hit chance", this, &accuracyhitchance2);

	AccuracyHitchance.SetFileId("acc_chance");
	AccuracyHitchance.SetBoundaries(0, 100);
	AccuracyHitchance.SetValue(0);
	AccuracyGroup.PlaceLabledControl("", this, &AccuracyHitchance);

	accuracyresolver2.SetFileId("");
	AccuracyGroup.PlaceLabledControl("anti aim resolver", this, &accuracyresolver2);
	
	AccuracyResolver.SetFileId("acc_aaa");
	AccuracyResolver.AddItem("off");
	AccuracyResolver.AddItem("auto yaw resolve");
	AccuracyResolver.AddItem("auto yaw + pitch");
	AccuracyGroup.PlaceLabledControl("", this, &AccuracyResolver);

	accuracysmart2.SetFileId("");
	AccuracyGroup.PlaceLabledControl("smart aim", this, &accuracysmart2);

	AccuracySmart.SetFileId("acc_smart");
	AccuracySmart.SetBoundaries(0, 20);
	AccuracySmart.SetValue(1);
	AccuracyGroup.PlaceLabledControl("", this, &AccuracySmart);
#pragma endregion  Accuracy controls get Setup in here

#pragma region AntiAim
	AntiAimGroup.SetPosition(360, 235); //344
	AntiAimGroup.SetText("anti aim");
	AntiAimGroup.SetSize(340, 165);
	RegisterControl(&AntiAimGroup);

	antiaimpitch3.SetFileId("");
	AntiAimGroup.PlaceLabledControl("pitch", this, &antiaimpitch3);

	AntiAimPitch.SetFileId("aa_x");
	AntiAimPitch.AddItem("none");
	AntiAimPitch.AddItem("down");
	AntiAimGroup.PlaceLabledControl("", this, &AntiAimPitch);

	antiaimyaw2.SetFileId("");
	AntiAimGroup.PlaceLabledControl("yaw", this, &antiaimyaw2);

	AntiAimYaw.SetFileId("aa_y");
	AntiAimYaw.AddItem("none");
	AntiAimYaw.AddItem("backwards");
	AntiAimYaw.AddItem("fake jitter");
	AntiAimGroup.PlaceLabledControl("", this, &AntiAimYaw);

	antiaimoffset2.SetFileId("");
	AntiAimGroup.PlaceLabledControl("yaw offset", this, &antiaimoffset2);

	AntiAimOffset.SetFileId("aa_offset");
	AntiAimOffset.SetBoundaries(0, 360);
	AntiAimOffset.SetValue(0);
	AntiAimGroup.PlaceLabledControl("", this, &AntiAimOffset);

	AntiAimKnife.SetFileId("aa_knife");
	AntiAimGroup.PlaceLabledControl("anti aim on knife", this, &AntiAimKnife);

	AntiAimTarget.SetFileId("aa_target");
	AntiAimGroup.PlaceLabledControl("anti aim at target", this, &AntiAimTarget);
#pragma endregion  AntiAim controls get setup in here
}

void CLegitBotTab::Setup()
{
	SetTitle("legit");
	SetTitle2("D");

#pragma region Aimbot
	AimbotGroup.SetPosition(5, 13);
	AimbotGroup.SetText("aimbot");
	AimbotGroup.SetSize(256, 180);
	RegisterControl(&AimbotGroup);

	AimbotEnable.SetFileId("aim_enable");
	AimbotGroup.PlaceLabledControl("enable", this, &AimbotEnable);

	AimbotAutoFire.SetFileId("aim_autofire");
	AimbotGroup.PlaceLabledControl("auto fire", this, &AimbotAutoFire);

	AimbotFriendlyFire.SetFileId("aim_friendfire");
	AimbotGroup.PlaceLabledControl("friendly fire", this, &AimbotFriendlyFire);

	AimbotKeyPress.SetFileId("aim_usekey");
	AimbotGroup.PlaceLabledControl("on key press", this, &AimbotKeyPress);

	AimbotKeyBind.SetFileId("aim_key");
	AimbotGroup.PlaceLabledControl("key bind", this, &AimbotKeyBind);
	
	AimbotAutoPistol.SetFileId("aim_apistol");
	AimbotGroup.PlaceLabledControl("auto pistol", this, &AimbotAutoPistol);

#pragma endregion Aimbot shit

#pragma region Main Weapon
	WeaponMainGroup.SetPosition(5, 205);
	WeaponMainGroup.SetText("rifles");
	WeaponMainGroup.SetSize(256, 195);
	RegisterControl(&WeaponMainGroup);

	smoothseperete4.SetFileId("");
	WeaponMainGroup.PlaceLabledControl("smooth", this, &smoothseperete4);

	WeaponMainSpeed.SetFileId("main_speed");
	WeaponMainSpeed.SetBoundaries(0.1f, 100.f); 
	WeaponMainSpeed.SetValue(1.0f);
	WeaponMainGroup.PlaceLabledControl("", this, &WeaponMainSpeed);

	fovseperete4.SetFileId("");
	WeaponMainGroup.PlaceLabledControl("field of view", this, &fovseperete4);

	WeaponMainFoV.SetFileId("main_fov");
	WeaponMainFoV.SetBoundaries(0.1f, 30.f);
	WeaponMainFoV.SetValue(5.f);
	WeaponMainGroup.PlaceLabledControl("", this, &WeaponMainFoV);

	WeaponMainRecoil.SetFileId("main_recoil");
	WeaponMainGroup.PlaceLabledControl("recoil", this, &WeaponMainRecoil);

	hitboxseperate4.SetFileId("");
	WeaponMainGroup.PlaceLabledControl("hitbox", this, &hitboxseperate4);

	WeaponMainHitbox.SetFileId("main_hitbox");
	WeaponMainHitbox.AddItem("head");
	WeaponMainHitbox.AddItem("neck");
	WeaponMainHitbox.AddItem("chest");
	WeaponMainHitbox.AddItem("stomach");
	WeaponMainGroup.PlaceLabledControl("hitbox", this, &WeaponMainHitbox);
#pragma endregion

#pragma region Pistols
	WeaponPistGroup.SetPosition(440, 205);
	WeaponPistGroup.SetText("pistols");
	WeaponPistGroup.SetSize(256, 195);
	RegisterControl(&WeaponPistGroup);

	smoothseperete3.SetFileId("");
	WeaponPistGroup.PlaceLabledControl("smooth", this, &smoothseperete3);

	WeaponPistSpeed.SetFileId("pist_speed");
	WeaponPistSpeed.SetBoundaries(0.1f, 100.f);
	WeaponPistSpeed.SetValue(1.0f);
	WeaponPistGroup.PlaceLabledControl("", this, &WeaponPistSpeed);

	fovseperete3.SetFileId("");
	WeaponPistGroup.PlaceLabledControl("field of view", this, &fovseperete3);

	WeaponPistFoV.SetFileId("pist_fov");
	WeaponPistFoV.SetBoundaries(0.1f, 30.f);
	WeaponPistFoV.SetValue(5.f);
	WeaponPistGroup.PlaceLabledControl("", this, &WeaponPistFoV);

	WeaponPistRecoil.SetFileId("pist_recoil");
	WeaponPistGroup.PlaceLabledControl("recoil", this, &WeaponPistRecoil);

	hitboxseperate3.SetFileId("");
	WeaponPistGroup.PlaceLabledControl("hitbox", this, &hitboxseperate3);

	WeaponPistHitbox.SetFileId("pist_hitbox");
	WeaponPistHitbox.AddItem("head");
	WeaponPistHitbox.AddItem("neck");
	WeaponPistHitbox.AddItem("chest");
	WeaponPistHitbox.AddItem("stomach");
	WeaponPistGroup.PlaceLabledControl("hitbox", this, &WeaponPistHitbox);
#pragma endregion

#pragma region Snipers
	WeaponSnipGroup.SetPosition(440, 13);
	WeaponSnipGroup.SetText("snipers");
	WeaponSnipGroup.SetSize(256, 180);
	RegisterControl(&WeaponSnipGroup);

	smoothseperete2.SetFileId("");
	WeaponSnipGroup.PlaceLabledControl("smooth", this, &smoothseperete2);

	WeaponSnipSpeed.SetFileId("snip_speed");
	WeaponSnipSpeed.SetBoundaries(0.1f, 100.f);
	WeaponSnipSpeed.SetValue(1.0f);
	WeaponSnipGroup.PlaceLabledControl("", this, &WeaponSnipSpeed);

	fovseperete2.SetFileId("");
	WeaponPistGroup.PlaceLabledControl("field of view", this, &fovseperete2);

	WeaponSnipFoV.SetFileId("snip_fov");
	WeaponSnipFoV.SetBoundaries(0.1f, 30.f);
	WeaponSnipFoV.SetValue(5.f);
	WeaponSnipGroup.PlaceLabledControl("", this, &WeaponSnipFoV);

	WeaponSnipRecoil.SetFileId("snip_recoil");
	WeaponSnipGroup.PlaceLabledControl("recoil", this, &WeaponSnipRecoil);

	hitboxseperate2.SetFileId("");
	WeaponSnipGroup.PlaceLabledControl("hitbox", this, &hitboxseperate2);

	WeaponSnipHitbox.SetFileId("snip_hitbox");
	WeaponSnipHitbox.AddItem("head");
	WeaponSnipHitbox.AddItem("neck");
	WeaponSnipHitbox.AddItem("chest");
	WeaponSnipHitbox.AddItem("stomach");
	WeaponSnipGroup.PlaceLabledControl("", this, &WeaponSnipHitbox);
#pragma endregion
}

void CVisualTab::Setup()
{
	SetTitle("visuals");
	SetTitle2("E");

	OptionsGroup.SetText("options");
	OptionsGroup.SetPosition(5, 23);
	OptionsGroup.SetSize(225, 375);
	RegisterControl(&OptionsGroup);

	Active.SetFileId("opt_enable");
	OptionsGroup.PlaceLabledControl("enable", this, &Active);

	OptionsBox.SetFileId("opt_box");
	OptionsGroup.PlaceLabledControl("box", this, &OptionsBox);

	OptionsName.SetFileId("opt_name");
	OptionsGroup.PlaceLabledControl("name", this, &OptionsName);

	OptionsHealth.SetFileId("opt_hp");
	OptionsGroup.PlaceLabledControl("health", this, &OptionsHealth);

	OptionsWeapon.SetFileId("opt_weapon");
	OptionsGroup.PlaceLabledControl("weapon", this, &OptionsWeapon);

	OptionsInfo.SetFileId("opt_info");
	OptionsGroup.PlaceLabledControl("info", this, &OptionsInfo);

	chamsseperate.SetFileId("");
	OptionsGroup.PlaceLabledControl("chams", this, &chamsseperate);

	OptionsChams.SetFileId("opt_chams");
	OptionsChams.AddItem("off");
	OptionsChams.AddItem("normal");
	OptionsChams.AddItem("flat");
	OptionsGroup.PlaceLabledControl("", this, &OptionsChams);

	OptionsSkeleton.SetFileId("opt_bone");
	OptionsGroup.PlaceLabledControl("skeleton", this, &OptionsSkeleton);
	
	//OptionsCompRank.SetFileId("opt_comprank");
	//OptionsGroup.PlaceLabledControl("Player Ranks", this, &OptionsCompRank);

#pragma endregion Setting up the Options controls

#pragma region Filters
	FiltersGroup.SetText("filters");
	FiltersGroup.SetPosition(235, 23);
	FiltersGroup.SetSize(225, 375);
	RegisterControl(&FiltersGroup);

	FiltersAll.SetFileId("ftr_all");
	FiltersGroup.PlaceLabledControl("all", this, &FiltersAll);

	FiltersPlayers.SetFileId("ftr_players");
	FiltersGroup.PlaceLabledControl("players", this, &FiltersPlayers);

	FiltersEnemiesOnly.SetFileId("ftr_enemyonly");
	FiltersGroup.PlaceLabledControl("enemies only", this, &FiltersEnemiesOnly);

	FiltersWeapons.SetFileId("ftr_weaps");
	FiltersGroup.PlaceLabledControl("weapons", this, &FiltersWeapons);

	FiltersC4.SetFileId("ftr_c4");
	FiltersGroup.PlaceLabledControl("c4", this, &FiltersC4);

	FiltersThirdperson.SetFileId("aa_thirdpsr");
	FiltersGroup.PlaceLabledControl("thirdperson", this, &FiltersThirdperson);

#pragma endregion Setting up the Filters controls

#pragma region Other
	OtherGroup.SetText("other");
	OtherGroup.SetPosition(465, 23);
	OtherGroup.SetSize(235, 375);
	RegisterControl(&OtherGroup);

	OtherRadar.SetFileId("otr_radar");
	OtherGroup.PlaceLabledControl("radar", this, &OtherRadar);

	OtherNoVisualRecoil.SetFileId("otr_visrecoil");
	OtherGroup.PlaceLabledControl("no visual recoil", this, &OtherNoVisualRecoil);

	OtherNoFlash.SetFileId("otr_removeflash");
	OtherGroup.PlaceLabledControl("remove flash", this, &OtherNoFlash);

	OtherNoSmoke.SetFileId("otr_removesmoke");
	OtherGroup.PlaceLabledControl("remove smoke", this, &OtherNoSmoke);

	nohands2.SetFileId("");
	OtherGroup.PlaceLabledControl("hands", this, &nohands2);

	OtherNoHands.SetFileId("otr_hands");
	OtherNoHands.AddItem("off");
	OtherNoHands.AddItem("none");
	OtherNoHands.AddItem("transparent");
	OtherNoHands.AddItem("chams");
	OtherNoHands.AddItem("rainbow");
	OtherGroup.PlaceLabledControl("", this, &OtherNoHands);

	vieewmodelseperate.SetFileId("");
	OtherGroup.PlaceLabledControl("viewmodel fov changer", this, &vieewmodelseperate);

	OtherViewmodelFOV.SetFileId("otr_viewfov");
	OtherViewmodelFOV.SetBoundaries(0.f, 180.f);
	OtherViewmodelFOV.SetValue(0.f);
	OtherGroup.PlaceLabledControl("", this, &OtherViewmodelFOV);

	fovseperate.SetFileId("");
	OtherGroup.PlaceLabledControl("field of view changer", this, &fovseperate);

	OtherFOV.SetFileId("otr_fov");
	OtherFOV.SetBoundaries(0.f, 180.f);
	OtherFOV.SetValue(90.f);
	OtherGroup.PlaceLabledControl("", this, &OtherFOV);
#pragma endregion Setting up the Other controls
}

void CMiscTab::Setup()
{
	SetTitle("Misc");
	SetTitle2("F");

#pragma region Knife
	KnifeGroup.SetPosition(5, 23);
	KnifeGroup.SetSize(225, 375);
	KnifeGroup.SetText("knife changer");
	RegisterControl(&KnifeGroup);

	KnifeEnable.SetFileId("knife_enable");
	KnifeGroup.PlaceLabledControl("enable", this, &KnifeEnable);

	KnifeModel.SetFileId("knife_model");
	KnifeModel.AddItem("karam");
	KnifeModel.AddItem("bayo");
	KnifeGroup.PlaceLabledControl("knife", this, &KnifeModel);

	KnifeSkin.SetFileId("knife_skin");
	KnifeSkin.AddItem("doppler sapphire");
	KnifeSkin.AddItem("doppler ruby");
	KnifeSkin.AddItem("tiger");
	KnifeSkin.AddItem("lore");
	KnifeGroup.PlaceLabledControl("skin", this, &KnifeSkin);

#pragma endregion

	MenuOptions.SetPosition(235, 23);
	MenuOptions.SetSize(235, 375);
	MenuOptions.SetText("options");
	RegisterControl(&MenuOptions);

	FakeLagEnable.SetFileId("otr_fakelagenable");
	MenuOptions.PlaceLabledControl("fakelag enable", this, &FakeLagEnable);

	FakeLagChoke.SetFileId("otr_fakelagchoke");
	FakeLagChoke.SetBoundaries(0.f, 14.f);
	FakeLagChoke.SetValue(0.f);
	MenuOptions.PlaceLabledControl("", this, &FakeLagChoke);

	SeperateFakelag.SetFileId("");
	MenuOptions.PlaceLabledControl("", this, &SeperateFakelag);

	lstPlayers.SetFileId("configs");
	lstPlayers.AddItem("1");
	lstPlayers.AddItem("2");
	lstPlayers.AddItem("3");
	lstPlayers.AddItem("4");
	lstPlayers.AddItem("5");
	lstPlayers.AddItem("6");
	MenuOptions.PlaceLabledControl("", this, &lstPlayers);

	SaveButton3.SetFileId("save");
	SaveButton3.SetCallback(SaveLegitCallbk);
	MenuOptions.PlaceLabledControl("", this, &SaveButton3);

	SeperateConfiguration.SetFileId("");
	MenuOptions.PlaceLabledControl("", this, &SeperateConfiguration);

	LoadButton3.SetFileId("load");
	LoadButton3.SetCallback(LoadLegitCallbk);
	MenuOptions.PlaceLabledControl("", this, &LoadButton3);

#pragma region Other
	OtherGroup.SetPosition(465, 23);
	OtherGroup.SetSize(235, 375);
	OtherGroup.SetText("other");
	RegisterControl(&OtherGroup);

	autobhops.SetFileId("otr_autobhops");
	OtherGroup.PlaceLabledControl("auto jump", this, &autobhops);

	OtherAutoJump.SetFileId("");
	OtherAutoJump.AddItem("off");
	OtherAutoJump.AddItem("normal");
	OtherGroup.PlaceLabledControl("", this, &OtherAutoJump);

	autostrafes.SetFileId("");
	OtherGroup.PlaceLabledControl("auto strafe", this, &autostrafes);

	OtherAutoStrafe.SetFileId("otr_strafe");
	OtherAutoStrafe.AddItem("off");
	OtherAutoStrafe.AddItem("legit");
	OtherAutoStrafe.AddItem("rage");
	OtherGroup.PlaceLabledControl("", this, &OtherAutoStrafe);

	OtherSafeMode.SetFileId("otr_safemode");
	OtherSafeMode.SetState(true);
	OtherGroup.PlaceLabledControl("anti untrusted", this, &OtherSafeMode);

	chatspams.SetFileId("");
	OtherGroup.PlaceLabledControl("chat spam", this, &chatspams);

	OtherChatSpam.SetFileId("otr_spam");
	OtherChatSpam.AddItem("off");
	OtherChatSpam.AddItem("namestealer");
	OtherChatSpam.AddItem("disperse name");
	OtherGroup.PlaceLabledControl("", this, &OtherChatSpam);

	clantagcustom.SetFileId("");
	OtherGroup.PlaceLabledControl("custom clantag", this, &clantagcustom);

	OtherClantag.SetFileId("otr_spam");
	OtherClantag.AddItem("off");
	OtherClantag.AddItem("valve");
	OtherGroup.PlaceLabledControl("", this, &OtherClantag);

	spamdelays.SetFileId("");
	OtherGroup.PlaceLabledControl("spam delay", this, &spamdelays);

	OtherChatDelay.SetFileId("otr_chatdelay");
	OtherChatDelay.SetBoundaries(0.1, 3.0);
	OtherChatDelay.SetValue(0.5);
	OtherGroup.PlaceLabledControl("", this, &OtherChatDelay);
#pragma endregion other random options
}

void Menu::SetupMenu()
{
	Window.Setup();

	GUI.RegisterWindow(&Window);
	GUI.BindWindow(VK_INSERT, &Window);
}

void Menu::DoUIFrame()
{
	if (Window.VisualsTab.FiltersAll.GetState())
	{
		Window.VisualsTab.FiltersC4.SetState(true);
		Window.VisualsTab.FiltersPlayers.SetState(true);
		Window.VisualsTab.FiltersWeapons.SetState(true);
	}
	GUI.Update();
	GUI.Draw();	
}


