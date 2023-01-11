#define _CRT_SECURE_NO_WARNINGS
#include "icons.h"
#include "menu.h"
#include "fontss.hpp"
#include "auth.hpp"
#include "driver.h"
#include <iostream>
#include <windows.h>
#include "protect\protectmain.h"
#include "Loader.h"

#define BaseGameMode 56911872 //"Signature": "System_Collections_Generic_List_BaseGameMode__c*"
#define TodSkyy 56931512 // "Signature": "TOD_Sky_c*"
#define ConVar_Client_c 56914152 // ConVar_Client_c*
#define ConVar_Admin_c 56908960 // ConVar_Admin_c*
#define oFovConVarGraphics 56922160 // "Signature": "ConVar_Graphics_c*"
#define OclusionCulling 56920712 // "Signature": "OcclusionCulling_c*"
#define oConVar_Culling 56920656 // "Signature": "ConVar_Culling_c*"
#define oPlayerMovement 0x4F8 // 0x4E8 // public BaseMovement movement;
#define oActiveUID 0x5D8 // private uint clActiveItem;
#define oPlayerInventory 0x6A0 // public PlayerInventory inventory;
#define oContainerBelt 0x28 // public ItemContainer containerBelt
#define oBeltContentList 0x38 // public List<Item> contents   or   public List<int> availableSlots;
#define oHeld 0xA0 // private EntityRef heldEntity
#define oRecoilProperties 0x2E0 // public RecoilProperties recoil;
#define oRecoilYawMin 0x18  // public float recoilYawMin;
#define oRecoilYawMax 0x1C  // public float recoilYawMax;
#define oRecoilPitchMin 0x20 // public float recoilPitchMin;
#define oRecoilPitchMax 0x24 // public float recoilPitchMax;
#define oAimconeCurveScale 0x60 // public float aimconeCurveScale;
#define oStancePenalty 0x348 //private float stancePenalty;
#define oAimCone 0x2F0 //public float aimCone;
#define oHipAimCone 0x2F4 //public float hipAimCone;
#define oAimconePenaltyPerShot 0x2F8 //public float aimconePenaltyPerShot;
#define oAutomatic 0x290 // public bool automatic;
#define oFastCompoundBow 0x3B8    // public float stringHoldDurationMax; // 0x378
#define capsuleHeight 0x68 // public float capsuleHeight
#define capsuleCenter 0x6C // public float capsuleCenter
#define groundAngle 0xC4 // groundAngle
#define groundAngleNew 0xC8 // groundAngleNew
#define oGravityMultiplier 0x84 // public float gravityMultiplier;
#define oAttackRadius 0x29C // public float attackRadius;
#define oisAutomatic 0x2A0// public bool isAutomatic;
#define omaxDistance 0x298 // public float maxDistance;
#define oBlockSprintOnAttack 0x2A1 // public bool blockSprintOnAttack;
#define oonlyThrowAsProjectile 0x282 // public bool onlyThrowAsProjectile;
#define othrowReady 0x2D8 // private bool throwReady;

float content_animation = 0.0f;
float dpi_scale = 1.5f;

bool birkez = true;

bool supermeele = false;
bool ESP = false;
bool CHAMS = false;
bool chamstamiri = false;
bool AdminFlag = false;
bool nighttmode = false;
bool Spiderman = false;
bool Flyhack = false;
int FlyHackButon;
bool Climb = false;
int climbbutton;
bool TimeChanger = false;
int TimeValue = 12;
bool GraphicFov = false;
bool SuperEoka = false;
bool NoSway = false;
int FovValue = 90;
bool NoRecoil = false;
int NoRecoilValue = 1;

float originalx1;
float originalx2;
float originaly1;
float originaly2;
char* origValues[6];

bool FatBullet = false;
bool NoSpread = false;
bool Automatic = false;
int old_tab = 0;

using namespace std;
#define INFO_BUFFER_SIZE 32767
TCHAR  infoBuf[INFO_BUFFER_SIZE];
DWORD  bufCharCount = INFO_BUFFER_SIZE;
std::string PCNAME = infoBuf;


#include <Iphlpapi.h>
#include <Assert.h>
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib,"advapi32.lib")


using namespace KeyAuth;
std::string namee = _xor_(" ); // application name. right above the blurred text aka the secret on the licenses tab among other tabs
std::string ownerid = _xor_(" "); // ownerid, found in account settings. click your profile picture on top right of dashboard and then account settings.
std::string secret = _xor_(" "); // app secret, the blurred text on licenses tab and other tabs
std::string version = _xor_(" "); // leave alone unless you've changed version on website
std::string url = _xor_("https://keyauth.win/api/1.2/"); // change if you're self-hosting
api KeyAuthApp(namee, ownerid, secret, version, url);

bool rememberme;
char UserName[350];
char PassWord[350];
char License[350];
static float progress = 0.0f, progress_dir = 1.0f;
static bool animate = false;
ImFont* Gay;
ImFont* NotGay;
ImFont* BigGay;
ImFont* BigBigGay;
ImFont* BigBigbGay;

ImFont* Font;
ImFont* Font2;
static int tabs = 1;

ImVec2 GetWindowSize() {
    return { (float)GetSystemMetrics(SM_CXSCREEN), (float)GetSystemMetrics(SM_CYSCREEN) };
}

void MouseCur(int Deger)
{
    const char* mouse_cursors_names[] = { "Arrow", "TextInput", "ResizeAll", "ResizeNS", "ResizeEW", "ResizeNESW", "ResizeNWSE", "Hand", "NotAllowed" };
    IM_ASSERT(IM_ARRAYSIZE(mouse_cursors_names) == ImGuiMouseCursor_COUNT);
    if (ImGui::IsItemHovered())
        ImGui::SetMouseCursor(Deger);
}

std::string HollUsername = (_xor_("C:\\Windows\\System\\ArbitUsername.txt"));
std::string HollPassword = (_xor_("C:\\Windows\\System\\ArbitPassword.txt"));
std::string HollReg = (_xor_("C:\\Windows\\System\\ArbitReg.txt"));


bool SetClipboard(const std::string& data) {

    auto size = data.size() + 1;
    auto pGlobal = GlobalAlloc(GMEM_MOVEABLE, size);

    if (!pGlobal) {

        return false;
    }

    OpenClipboard(0);
    EmptyClipboard();

    auto pLock = GlobalLock(pGlobal);

    if (!pLock) {
        CloseClipboard();
        return false;
    }

    CopyMemory(pLock, data.c_str(), size);

    GlobalUnlock(pGlobal);

    SetClipboardData(CF_TEXT, pGlobal);

    CloseClipboard();

    GlobalFree(pGlobal);

    return true;
}

UINT64 GetHeldItem(UINT64 LocalPlayer)
{
    const auto base_player = LocalPlayer;
    const auto active_item_id = read<UINT64>(base_player + oActiveUID);
    const auto player_inventory = read<UINT64>(base_player + oPlayerInventory);
    const auto inventory_belt = read<UINT64>(player_inventory + oContainerBelt);
    const auto belt_contents_list = read<UINT64>(inventory_belt + oBeltContentList);
    const auto belt_contents_sz = read<uint32_t>(belt_contents_list + 0x14);
    const auto belt_contents = read<UINT64>(belt_contents_list + 0x10);
    for (auto i = 0u; i <= 6; i++)
    {
        if (belt_contents != 0)
        {
            const auto current_item = read<UINT64>(belt_contents + (0x20 + (i * 8)));
            if (!current_item) continue;
            if (active_item_id == read<uint32_t>(current_item + 0x28)) return current_item;
        }
    }
}
std::wstring get_item_name(uintptr_t item)
{
    auto unk = read<UINT64>(item + 0x20);
    unk = read<UINT64>(unk + 0x20);
    return read_wstring(unk + 0x14, 14);
}
bool is_weapon(uintptr_t helditem)
{
    auto ItemName = get_item_name(helditem);
    if (ItemName.find(L"rifle") != std::string::npos) return true;
    if (ItemName.find(L"pistol") != std::string::npos) return true;
    if (ItemName.find(L"bow.hunting") != std::string::npos) return true;
    if (ItemName.find(L"bow") != std::string::npos) return true;
    if (ItemName.find(L"lmg") != std::string::npos) return true;
    if (ItemName.find(L"shotgun") != std::string::npos) return true;
    if (ItemName.find(L"smg") != std::string::npos) return true;
    else return false;
}
bool is_meele(uintptr_t helditem)
{
    auto ItemName = get_item_name(helditem);
    if (ItemName.find(L"rock") != std::string::npos) return true;
    if (ItemName.find(L"hatchet") != std::string::npos) return true;
    if (ItemName.find(L"stone.pickaxe") != std::string::npos) return true;
    if (ItemName.find(L"stonehatchet") != std::string::npos) return true;
    if (ItemName.find(L"pickaxe") != std::string::npos) return true;
    if (ItemName.find(L"hammer.salvage") != std::string::npos) return true;
    if (ItemName.find(L"icepick.salvag") != std::string::npos) return true;
    if (ItemName.find(L"axe.salvaged") != std::string::npos) return true;
    if (ItemName.find(L"pitchfork") != std::string::npos) return true;
    if (ItemName.find(L"mace") != std::string::npos) return true;
    if (ItemName.find(L"spear.stone") != std::string::npos) return true;
    if (ItemName.find(L"spear.wooden") != std::string::npos) return true;
    if (ItemName.find(L"machete") != std::string::npos) return true;
    if (ItemName.find(L"bone.club") != std::string::npos) return true;
    if (ItemName.find(L"paddle") != std::string::npos) return true;
    if (ItemName.find(L"salvaged.sword") != std::string::npos) return true;
    if (ItemName.find(L"salvaged.cleav") != std::string::npos) return true;
    if (ItemName.find(L"knife.combat") != std::string::npos) return true;
    if (ItemName.find(L"knife.butcher") != std::string::npos) return true;
    if (ItemName.find(L"jackhammer") != std::string::npos) return true;
    if (ItemName.find(L"chainsaw") != std::string::npos) return true;
    if (ItemName.find(L"knife.bone") != std::string::npos) return true;
    if (ItemName.find(L"torch") != std::string::npos) return true;
    if (ItemName.find(L"hammer") != std::string::npos) return true;
    if (ItemName.find(L"sickle") != std::string::npos) return true;
    else return false;
}

void hile()
{
    while (true)
    {
        if (animate)
        {
            auto main_offsets = read<uintptr_t>(assemblybase + BaseGameMode);
            Local_Player = read_chain<uintptr_t>(main_offsets, { 0xb8, 0x20, 0x10, 0x28, 0x18, 0x20 });

            auto Movement = read<uintptr_t>(Local_Player + oPlayerMovement);
            auto OcclusionCulling = read<uintptr_t>(assemblybase + OclusionCulling);
            auto CullingDebugOnOff = read<uintptr_t>(OcclusionCulling + 0xB8);
            auto OcclusionCullingEditted = read_chain<uintptr_t>(OcclusionCulling, { 0xB8, 128, 0x18 });
            auto ConvarCulling = read<uintptr_t>(assemblybase + oConVar_Culling);
            auto ConvarCulling2 = read<uintptr_t>(ConvarCulling + 0xB8);
            auto klass = read<uintptr_t>(assemblybase + ConVar_Client_c);
            auto static_fields = read<uintptr_t>(klass + 0xB8);
            auto klass2 = read<uintptr_t>(assemblybase + ConVar_Admin_c); // convar_admin_c*
            auto static_fields2 = read<uintptr_t>(klass2 + 0xb8);
            if (ESP)
            {
                if (read<float>(ConvarCulling2 + 0x0) != 1000.f) {
                    write<float>(ConvarCulling2 + 0x0, 1000.f); // culling.entityupdaterate 1000 komutu
                }
                if (read<uintptr_t>(OcclusionCullingEditted + 0x20) != 131072) {
                    write<uintptr_t>(OcclusionCullingEditted + 0x20, 131072);
                }
                if (read<uintptr_t>(CullingDebugOnOff + 0x94) != 1) {
                    write<uintptr_t>(CullingDebugOnOff + 0x94, 1); // culling.debug 1 komutu
                }
            }
            else
            {
                if (read<float>(CullingDebugOnOff + 0x94) != 0) {
                    write<uintptr_t>(CullingDebugOnOff + 0x94, 0);// culling.debug 0 komutu
                }
            }
            if (nighttmode)
            {
                write<float>(static_fields2 + 0xC, 2); // public static float adminambientmultiplier;
            }
            else
            {
               write<float>(static_fields2 + 0xC, -1);  // public static float adminambientmultiplier;
            }
            if (AdminFlag)
            {
                auto player_flags = read<uintptr_t>(Local_Player + 0x690);
                if (!player_flags) {

                    return;
                }
                player_flags |= 4;
                write(Local_Player + 0x690, player_flags);


                write<float>(static_fields + 0x30, 1.f);
                write<float>(static_fields + 0x3C, 1.f);
                write<bool>(Movement + 0x18, false); // noclipi oto kapatýyor
            }
            if (TimeChanger)
            {
                if (read<float>(static_fields2 + 0x0) != TimeValue) {
                    write<float>(static_fields2 + 0x0, TimeValue); // public static float admintime;
                }
            }
            if (GraphicFov)
            {
                uint64_t fov = read<UINT64>(assemblybase + oFovConVarGraphics); // "Signature": "ConVar_Graphics_c"
                uint64_t instance = read<UINT64>(fov + 0xB8);
                write<float>(instance + 0X18, FovValue);
            }
            if (Spiderman)
            {
                write<float>(Movement + 0xC4, 0.f);
                write<float>(Movement + 0xC8, 0.f);
            }
            if (Flyhack)
            {
                if (GetAsyncKeyState(FlyHackButon))
                {

                    write<float>(Movement + groundAngle, 0);//groundAngle
                    write<float>(Movement + groundAngleNew, 0);//groundAngleNew
                    write<float>(Movement + oGravityMultiplier, 0);//gravityMultiplier

                }
                else
                {
                    if (read<float>(Movement + oGravityMultiplier) != 2.5f) {
                        write<float>(Movement + oGravityMultiplier, 2.5f);//gravityMultiplier
                    }
                }
            }
            if (Climb)
            {
                if (GetAsyncKeyState(climbbutton))
                {

                    write<float>(Movement + capsuleHeight, -100);
                    write<float>(Movement + capsuleCenter, -100);
                }
                else
                {
                    if (read<float>(Movement + capsuleHeight) != 1.79f) {
                        write<float>(Movement + capsuleHeight, 1.79f);
                        write<float>(Movement + capsuleCenter, 0.899f);
                    }
                }
            }

            const auto current_item = GetHeldItem(Local_Player);
            auto base_projectile = read<uintptr_t>(current_item + oHeld);
            auto recoil_prop = read<uintptr_t>(base_projectile + oRecoilProperties);
            auto newRecoilOverride = read<uintptr_t>(recoil_prop + 0x78);



            if (is_meele(current_item)) {
                if (supermeele)
                {
                    if (read<float>(base_projectile + omaxDistance) != 3.0f) {
                        write<float>(base_projectile + omaxDistance, 3.0f);
                    }
                    if (read<float>(base_projectile + oAttackRadius) != 1.0f) {
                        write<float>(base_projectile + oAttackRadius, 1.0f);
                    }

                    if (read<bool>(base_projectile + oBlockSprintOnAttack) != false) {
                        write<bool>(base_projectile + oBlockSprintOnAttack, false);
                        write<bool>(base_projectile + oonlyThrowAsProjectile, false);
                        write<bool>(base_projectile + othrowReady, true);
                    }
                }
            }

            if (is_weapon(current_item)) {
                if (NoRecoil) {
                    if (newRecoilOverride) {
                        write<int>(newRecoilOverride + oRecoilYawMin, originalx1 * (NoRecoilValue / 100));
                        write<int>(newRecoilOverride + oRecoilYawMax, originalx2 * (NoRecoilValue / 100));
                        write<int>(newRecoilOverride + oRecoilPitchMin, originaly1 * (NoRecoilValue / 100));
                        write<int>(newRecoilOverride + oRecoilPitchMax, originaly2 * (NoRecoilValue / 100));
                    }
                    if (!newRecoilOverride) {
                        write<int>(recoil_prop + oRecoilYawMin, originalx1 * (NoRecoilValue / 100));
                        write<int>(recoil_prop + oRecoilYawMax, originalx2 * (NoRecoilValue / 100));
                        write<int>(recoil_prop + oRecoilPitchMin, originaly1 * (NoRecoilValue / 100));
                        write<int>(recoil_prop + oRecoilPitchMax, originaly2 * (NoRecoilValue / 100));
                    }
                }
                if (FatBullet)
                {

                    auto List = read<uintptr_t>(base_projectile + 0x370); //private List<Projectile> createdProjectiles;
                    int size = read<uintptr_t>(List + 0x18);
                    List = read<uintptr_t>(List + 0x10);
                    for (int i = 0; i < size; ++i)
                    {
                        auto Item = read<uintptr_t>(List + 0x20 + (i * 0x8));
                        if (read<float>(Item + 0x2C) != 0.7f) {
                            write<float>(Item + 0x2C, 0.7f);
                        }
                    }
                }
                if (NoSpread)
                {

                    if (newRecoilOverride)
                    {
                        if (read<int>(newRecoilOverride + oAimconeCurveScale) != -1) {
                            write<int>(newRecoilOverride + oAimconeCurveScale, -1);
                            write<int>(newRecoilOverride + oStancePenalty, -1);
                            write<int>(newRecoilOverride + oAimCone, -1);
                            write<int>(newRecoilOverride + oHipAimCone, -1);
                            write<int>(newRecoilOverride + oAimconePenaltyPerShot, -1);
                        }
                    }
                    if (!newRecoilOverride)
                    {
                        if (read<int>(recoil_prop + oAimconeCurveScale) != -1) {
                            write<int>(recoil_prop + oAimconeCurveScale, -1);
                            write<int>(recoil_prop + oStancePenalty, -1);
                            write<int>(recoil_prop + oAimCone, -1);
                            write<int>(recoil_prop + oHipAimCone, -1);
                            write<int>(recoil_prop + oAimconePenaltyPerShot, -1);
                        }
                    }
                }
                if (Automatic)
                {
                    if (read<bool>(base_projectile + oAutomatic) != Automatic) {
                        write<bool>(base_projectile + oAutomatic, Automatic);
                    }
                }
                if (NoSway)
                {
                    write<float>(base_projectile + 0x2D8, 0.f);// public float aimSway;
                    write<float>(base_projectile + 0x2DC, 0.f);// public float aimSwaySpeed;
                }
                if (SuperEoka)
                {
                    if (read<float>(base_projectile + 0x378) != 100.f) {
                        write<float>(base_projectile + 0x378, 100.f); // successFraction
                    }
                    if (read<bool>(base_projectile + 0x388) != true) {
                        write<bool>(base_projectile + 0x388, true); // didSparkThisFrame
                    }
                }
            }



            if (CHAMS)
            {
                if (!chamstamiri)
                {
                    uintptr_t BaseGameModee = read<uintptr_t>(assemblybase + BaseGameMode);
                    uintptr_t h1 = read<uintptr_t>(BaseGameModee + 0xB8);
                    uintptr_t h2 = read<uintptr_t>(h1 + 0x20);
                    uintptr_t h3 = read<uintptr_t>(h2 + 0x10);
                    uintptr_t h4 = read<uintptr_t>(h3 + 0x28);
                    auto objectList = read<uintptr_t>(h4 + 0x18);

                    for (int i = 0; i < 10; i++) {
                        auto Entity = read<uintptr_t>(objectList + 0x20 + (i * 0x8)); if (Entity <= 10) continue;

                        uintptr_t player_model = read<uintptr_t>(Entity + 0x4D0); // public PlayerModel playerModel;

                        auto SKY_C = read<uintptr_t>(assemblybase + TodSkyy); // "Signature": "TOD_Sky_c*"
                        auto SKYINSTANCE = read<uintptr_t>(SKY_C + 0xB8);
                        auto SKYINSTANCELIST = read<uintptr_t>(SKYINSTANCE + 0x0);
                        auto INSTANCES = read<uintptr_t>(SKYINSTANCELIST + 0x10);
                        auto Dome = read<uintptr_t>(INSTANCES + 0x20);

                        auto components = read<uintptr_t>(Dome + 0xA8);
                        auto scattering = read<uintptr_t>(components + 0x1A0);
                        auto material = read<uintptr_t>(scattering + 0x78);

                        //Cinsiyet 1
                        auto player_skin_component = read<uintptr_t>(player_model + 0x1A0); // public SkinSetCollection MaleSkin; // 0x1A0
                        auto skins = read<uintptr_t>(player_skin_component + 0x18);
                        auto skins_sz = read<int32_t>(skins + 0x18);
                        for (int i = NULL; i <= (int)skins_sz; i++)
                        {
                            auto current_skin = read<uintptr_t>(skins + 0x20 + (i * 0x8));

                            write<uintptr_t>(current_skin + 0x68, material);
                            write<uintptr_t>(current_skin + 0x70, material);
                            write<uintptr_t>(current_skin + 0x78, material);
                        }
                        //Cinsiyet 2
                        auto player_skin_component2 = read<uintptr_t>(player_model + 0x1A8); // public SkinSetCollection MaleSkin; // 0x1A0
                        auto skins2 = read<uintptr_t>(player_skin_component2 + 0x18);
                        auto skins_sz2 = read<int32_t>(skins2 + 0x18);
                        for (int i = NULL; i <= (int)skins_sz2; i++)
                        {
                            auto current_skin2 = read<uintptr_t>(skins2 + 0x20 + (i * 0x8));

                            write<uintptr_t>(current_skin2 + 0x68, material);
                            write<uintptr_t>(current_skin2 + 0x70, material);
                            write<uintptr_t>(current_skin2 + 0x78, material);
                        }
                        chamstamiri = true;
                    }
                }
            }
            else
            {
                chamstamiri = false;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
#pragma comment (lib, "urlmon.lib")
#include <urlmon.h>
#include <filesystem>

std::string mapperwin11 = (_xor_("https://cdn.discordapp.com/attachments/1034435554080722964/1046171317575106640/kdmapper.exe"));
std::string mapperkonumwin11 = (_xor_("C:\\Windows\\System\\9305dsi643jw11.exe"));

std::string driver = (_xor_("https://cdn.discordapp.com/attachments/1034435554080722964/1046166593299824640/driver.sys"));
std::string driverkonum = (_xor_("C:\\Windows\\System\\9305dsi643j.sys"));

void LoadDriver()
{
    DeleteFileA(mapperkonumwin11.c_str());
    DeleteFileA(driverkonum.c_str());
    Sleep(1000);
    URLDownloadToFileA(NULL, mapperwin11.c_str(), mapperkonumwin11.c_str(), 0, NULL);
    URLDownloadToFileA(NULL, driver.c_str(), driverkonum.c_str(), 0, NULL);
    Sleep(1000);
    system(skCrypt("C:\\Windows\\System\\9305dsi643jw11.exe C:\\Windows\\System\\9305dsi643j.sys >nul 2>&1"));
    Sleep(900);
    DeleteFileA(skCrypt("C:\\Windows\\System\\9305dsi643jw11.exe"));
    DeleteFileA(skCrypt("C:\\Windows\\System\\9305dsi643j.sys"));
    Sleep(500);
}

void DriverINNIT()
{
r8:
    initdrv();
    Sleep(1);
    r_socket = connect();
    if (r_socket == INVALID_SOCKET)
    {
        if (process_id(_xor_("RustClient.exe")))
        {
            system(skCrypt("CLS"));
            std::cout << skCrypt("CLOSE RUST") << std::endl;
            goto r8;
        }
        else
        {
            printf(skCrypt("driver not found\n"));
            LoadDriver();
            goto r8;
        }
    }
    else
    {
        r_pid = process_id(_xor_("RustClient.exe"));
        assemblybase = dll_oku(r_socket, r_pid, 0);
        unitybase = dll_oku(r_socket, r_pid, 1);
        if (Menu::tab != 2) old_tab = Menu::tab;
        Menu::tab == 2 ? Menu::tab = old_tab, content_animation = 0.0f : Menu::tab = 2, content_animation = 0.0f;
        Menu::tab = 2; Beep(150, 100);
    }
}
IDirect3DTexture9* Logo;
int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandleA(0), 0,0,0, 0, _xor_("Arbit Cheat").c_str(), 0 };
    RegisterClassEx(&wc);
    Window = CreateWindow(wc.lpszClassName, _xor_("Arbit Cheat").c_str(), WS_POPUP, 0, 0, 5, 5, 0, 0, wc.hInstance, 0);

    if (!CreateDeviceD3D(Window)) 
    {
        CleanupDeviceD3D();
        UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    ShowWindow(Window, SW_HIDE);
    UpdateWindow(Window);

    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.LogFilename = nullptr;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; 
   
    static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
    ImFontConfig icons_config;

    io.IniFilename = nullptr;
    io.LogFilename = nullptr;

    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.OversampleH = 3;
    icons_config.OversampleV = 3;

    ImFontConfig CustomFont;
    CustomFont.FontDataOwnedByAtlas = false;
    Gay = io.Fonts->AddFontFromMemoryCompressedTTF(Font_compressed_data, Font_compressed_size, 12.5f, NULL, io.Fonts->GetGlyphRangesJapanese());
    NotGay = io.Fonts->AddFontFromMemoryCompressedTTF(Font_compressed_data, Font_compressed_size, 13.5f, NULL, io.Fonts->GetGlyphRangesJapanese());
    BigGay = io.Fonts->AddFontFromMemoryCompressedTTF(Font_compressed_data, Font_compressed_size, 15.5f, NULL, io.Fonts->GetGlyphRangesJapanese());
    BigBigGay = io.Fonts->AddFontFromMemoryCompressedTTF(Font_compressed_data, Font_compressed_size, 70.5f, NULL, io.Fonts->GetGlyphRangesJapanese());
    BigBigbGay = io.Fonts->AddFontFromMemoryCompressedTTF(Font_compressed_data, Font_compressed_size, 25.5f, NULL, io.Fonts->GetGlyphRangesJapanese());

    //main_font3 = io.Fonts->AddFontFromMemoryCompressedTTF(Font_compressed_data, Font_compressed_size, 13.f, NULL, io.Fonts->GetGlyphRangesJapanese());

    Font = io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 35.5f, &icons_config, icons_ranges);
    Font2 = io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 1.0f, &icons_config, icons_ranges);
    io.Fonts->AddFontDefault();

    D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, logooooooooo, sizeof(logooooooooo), 100, 100, D3DX_DEFAULT, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &Logo);

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplWin32_Init(Window);
    ImGui_ImplDX9_Init(g_pd3dDevice);
    MSG msg;

    memset(&msg, 0, sizeof(msg));

    RECT rc = { 0 };
    GetWindowRect(GetDesktopWindow(), &rc);
    auto x = float(rc.right - WINDOW_WIDTH) / 2.f;
    auto y = float(rc.bottom - WINDOW_HEIGHT) / 2.f;
    auto s = ImVec2{}, p = ImVec2{}, gs = ImVec2{ WINDOW_WIDTH, WINDOW_HEIGHT };
        


    FILE* Dosya;
    if (Dosya = fopen((HollUsername.c_str()), ("r"))) {
        std::ifstream DosyaOku(HollUsername.c_str());
        std::string Anahtar;
        std::getline(DosyaOku, Anahtar);
        DosyaOku.close();
        fclose(Dosya);

        int i;
        for (i = 0; i < 50; i++) {
            UserName[i] = Anahtar[i];
        }
    }
    FILE* Dosya2;
    if (Dosya2 = fopen((HollPassword.c_str()), ("r"))) {
        std::ifstream DosyaOku2(HollPassword.c_str());
        std::string Anahtar2;
        std::getline(DosyaOku2, Anahtar2);
        DosyaOku2.close();
        fclose(Dosya2);

        int i;
        for (i = 0; i < 50; i++) {
            PassWord[i] = Anahtar2[i];
        }
    }

    std::string Anahtar3 = "";
    int index;
    for (index = 0; index < 50; index++) {
        Anahtar3[index] = PassWord[index];
    }
    if (Anahtar3 == "") { rememberme = false; }
    else { rememberme = true; }

    static bool update_on_f5 = true;

    KeyAuthApp.init();
    std::string LastLogin;
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_Once);

      

        time_t currtime;
        struct tm* tminfo;
        time(&currtime);
        tminfo = localtime(&currtime);
        std::time_t x = std::mktime(tminfo);
        std::time_t y = string_to_timet(KeyAuthApp.data.expiry);
        double difference;
        if (x != (std::time_t)(-1) && y != (std::time_t)(-1))
        {
            difference = std::difftime(y, x) / (60 * 60 * 24);
        }
        std::string LisansinKalanZamani = std::to_string((int)difference);

        std::string LISANS = "Expiry: " + LisansinKalanZamani + " Days";


        if (Menu::tab == 1)
        {
            Menu::Theme();
            {
                ImGui::Begin(skCrypt("Arbit Cheat"), &Enabled, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
                {
                    auto draw = ImGui::GetWindowDrawList();
                    ImVec2 pos = ImGui::GetWindowPos();
                    ImVec2 size = ImGui::GetWindowSize();

                    if (update_on_f5) { if (GetAsyncKeyState(VK_F5)) content_animation = 0.0f; } // lol
                    content_animation = ImLerp(content_animation, content_animation < 1.0f ? 1.0f : 0.0f, 0.08f * (0.8f - ImGui::GetIO().DeltaTime));

                   
                   
                    draw->AddLine(ImVec2(pos.x, pos.y + 5), ImVec2(pos.x + size.x, pos.y + 5), ImColor(46, 46, 46)); // upper line
                    draw->AddRectFilledMultiColor(ImVec2(pos.x, pos.y + 6), ImVec2(pos.x + size.x, pos.y + WINDOW_HEIGHT * 1), ImColor(0, 0, 50), ImColor(0, 0, 10), ImColor(0, 0, 50, 0), ImColor(0, 0, 0, 0));

                    ImVec2 CursorPos = ImGui::GetWindowPos();
                    ImGui::SetWindowSize(ImVec2(540, 520));
                    //ImGui::GetWindowDrawList()->AddTriangleFilled(ImVec2(CursorPos.x, CursorPos.y + 200), ImVec2(CursorPos.x + 450, CursorPos.y + 800), ImVec2(CursorPos.x + 0, CursorPos.y + 800), ImColor(8, 8, 8, 255));

                    //dot_draw();

                    ImGui::SetCursorPos(ImVec2(500, 6));
                    ImGui::PushFont(Font);
                    if (ImGui::ButtonNew("X", ImVec2(30, 30)))
                    {
                        exit(-1);
                    }
                    ImGui::PopFont();

                    ImGui::SetCursorPos(ImVec2(75, 30 * content_animation));
                    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
                    ImGui::PushFont(BigBigGay);
                    ImGui::TextColored(ImColor(255, 255, 255, 255), skCrypt("Arbit"));

                    ImGui::SetCursorPos(ImVec2(225, 25 * content_animation));
                    ImGui::Image(Logo, ImVec2(70, 70));

                    ImGui::SetCursorPos(ImVec2(292, 30 * content_animation));
                    ImGui::TextColored(ImColor(255, 255, 255, 255), skCrypt("Cheat"));

                    ImGui::PopFont();
                    ImGui::PopStyleColor();


                    ImGui::SetCursorPos(ImVec2(155, 120 * content_animation));
                    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 120));
                    ImGui::PushFont(Gay);
                    ImGui::Text(skCrypt("Thanks for for choosing our products !"));
                    ImGui::PopFont();
                    ImGui::PopStyleColor();

                 /*   ImGui::SetCursorPos(ImVec2(120, 140 * content_animation));
                    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
                    ImGui::PushFont(BigGay);
                    ImGui::Text(skCrypt("New discord adress: Discord.gg/3sAEE8fxjX"));
                    if (ImGui::IsItemHovered())
                    {   
                        ImGui::BeginTooltip();
                        ImGui::PushTextWrapPos(450.0f);
                        ImGui::TextUnformatted(skCrypt("Click and copy: Discord.gg/3sAEE8fxjX"));
                        ImGui::PopTextWrapPos();
                        ImGui::EndTooltip();
                        MouseCur(7);
                        if (ImGui::IsItemClicked())
                        {
                            SetClipboard("Discord.gg/3sAEE8fxjX");
                        }
                    }
                    ImGui::PopStyleColor();
                    ImGui::PopFont();*/




                    if (Menu::logreg == 1)
                    {

                        ImGui::SetCursorPos(ImVec2(100, 220 * content_animation));
                        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(240, 240, 240, 255));
                        ImGui::PushFont(NotGay);
                        ImGui::Text(skCrypt("Username :"));
                        ImGui::PopStyleColor();
                        ImGui::PopFont();

                        ImGui::SetCursorPos(ImVec2(100, 290 * content_animation));
                        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(240, 240, 240, 255));
                        ImGui::PushFont(NotGay);
                        ImGui::Text(skCrypt("Password :"));
                        ImGui::PopStyleColor();
                        ImGui::PopFont();



                        ImGui::PushFont(NotGay);
                        ImGui::SetCursorPos(ImVec2(100, 240 * content_animation));
                        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(240, 240, 240, 255));
                        ImGui::InputTextNew(skCrypt("##RenderUsername"), UserName, sizeof(UserName), ImVec2(350, 35));
                        ImGui::SetCursorPos(ImVec2(100, 310 * content_animation));
                        ImGui::InputTextNew(skCrypt("##RenderPassword"), PassWord, sizeof(PassWord), ImVec2(350, 35), ImGuiInputTextFlags_Password);

                        ImGui::SetCursorPos(ImVec2(100, 350 * content_animation));
                        ImGui::Checkbox(skCrypt("Remember me"), &rememberme);

                        ImGui::SetCursorPos(ImVec2(100, 380 * content_animation));
                        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));

                        if (ImGui::Button(skCrypt("Login Now"), ImVec2(350, 42)))
                        {
                            KeyAuthApp.login(UserName, PassWord);
                            if (KeyAuthApp.data.success)
                            {
                                if (rememberme)
                                {
                                    std::ofstream key; key.open(HollUsername.c_str());
                                    key << UserName;
                                    key.close();
                                    std::ofstream key2; key2.open(HollPassword.c_str());
                                    key2 << PassWord;
                                    key2.close();
                                }
                                else
                                {
                                    remove(HollUsername.c_str());
                                    remove(HollPassword.c_str());
                                }
                             
                                animate = true;
                            }
                            else
                            {
                                Beep(70, 400);
                            }
                        }
                        if (!animate)
                        {
                            ImGui::SetCursorPos(ImVec2(210, 430 * content_animation));
                            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 120));
                            ImGui::PushFont(Gay);
                            ImGui::Text(skCrypt("Create an account."));
                            if (ImGui::IsItemHovered())
                            {
                                MouseCur(7);
                                if (ImGui::IsItemClicked())
                                {
                                    Sleep(60);
                                    if (Menu::logreg != 2) old_tab = Menu::logreg;
                                    Menu::logreg == 2 ? Menu::logreg = old_tab, content_animation = 0.0f : Menu::logreg = 2, content_animation = 0.0f; 
                                    Menu::logreg = 2;
                                }
                            }
                            ImGui::PopFont();
                            ImGui::PopStyleColor();
                        }
                        if (animate == true)
                        {
                            ImGui::SetCursorPos(ImVec2(225, 445 * content_animation));
                            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 180));
                            ImGui::PushFont(Gay);
                            ImGui::Text(skCrypt("Driver loading."));
                            ImGui::PopFont();
                            ImGui::PopStyleColor();
                            ImGui::PushFont(Gay);
                            ImGui::SetCursorPos(ImVec2(100, 460 * content_animation));
                            ImGui::ProgressBar(progress, ImVec2(350.f, 10.0f));
                            ImGui::PopFont();
                            progress += progress_dir * 0.5f * ImGui::GetIO().DeltaTime;
                            if (progress >= +1.1f) {
                                progress = +1.1f;

                                DriverINNIT();
                                LastLogin = tm_to_readable_time(timet_to_tm(string_to_timet(KeyAuthApp.data.lastlogin)));
                                if (birkez)
                                {
                                    birkez = false;
                                }
                            }
                        }
                        ImGui::PopStyleColor();
                        ImGui::PopFont();
                        ImGui::PopStyleColor();
                    }
                    if (Menu::logreg == 2)
                    {


                        ImGui::SetCursorPos(ImVec2(100, 190 * content_animation));
                        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(240, 240, 240, 255));
                        ImGui::PushFont(NotGay);
                        ImGui::Text(skCrypt("Username :"));
                        ImGui::PopStyleColor();
                        ImGui::PopFont();

                        ImGui::SetCursorPos(ImVec2(100, 250 * content_animation));
                        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(240, 240, 240, 255));
                        ImGui::PushFont(NotGay);
                        ImGui::Text(skCrypt("Password :"));
                        ImGui::PopStyleColor();
                        ImGui::PopFont();

                        ImGui::SetCursorPos(ImVec2(100, 310 * content_animation));
                        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(240, 240, 240, 255));
                        ImGui::PushFont(NotGay);
                        ImGui::Text(skCrypt("License :"));
                        ImGui::PopStyleColor();
                        ImGui::PopFont();



                        ImGui::PushFont(NotGay);
                        ImGui::SetCursorPos(ImVec2(100, 210 * content_animation));
                        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(240, 240, 240, 255));
                        ImGui::InputTextNew(skCrypt("##RenderUsername"), UserName, sizeof(UserName), ImVec2(350, 35));
                        ImGui::SetCursorPos(ImVec2(100, 270 * content_animation));
                        ImGui::InputTextNew(skCrypt("##RenderPassword"), PassWord, sizeof(PassWord), ImVec2(350, 35), ImGuiInputTextFlags_Password);
                        ImGui::SetCursorPos(ImVec2(100, 330 * content_animation));
                        ImGui::InputTextNew(skCrypt("##RenderLicense"), License, sizeof(License), ImVec2(350, 35), ImGuiInputTextFlags_Password);
                        ImGui::SetCursorPos(ImVec2(100, 370 * content_animation));
                        ImGui::Checkbox(skCrypt("Remember me"), &rememberme);
                    
                        ImGui::SetCursorPos(ImVec2(100, 395 * content_animation));
                        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));

                        if (ImGui::Button(skCrypt("Register Now"), ImVec2(350, 42)))
                        {
                            KeyAuthApp.regstr(UserName, PassWord, License);
                            if (KeyAuthApp.data.success)
                            {
                                if (rememberme)
                                {
                                    std::ofstream key; key.open(HollUsername.c_str());
                                    key << UserName;
                                    key.close();
                                    std::ofstream key2; key2.open(HollPassword.c_str());
                                    key2 << PassWord;
                                    key2.close();
                                }
                                else
                                {
                                    remove(HollUsername.c_str());
                                    remove(HollPassword.c_str());
                                }
                   
                                animate = true;
                            }
                            else
                            {
                                Beep(70, 400);
                            }
                        }

                        if (!animate)
                        {
                            ImGui::SetCursorPos(ImVec2(190, 445 * content_animation));
                            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 120));
                            ImGui::PushFont(Gay);
                            ImGui::Text(skCrypt("I already have an account."));
                            if (ImGui::IsItemHovered())
                            {
                                MouseCur(7);
                                if (ImGui::IsItemClicked())
                                {
                                    Sleep(60);
                                    if (Menu::logreg != 1) old_tab = Menu::logreg;
                                    Menu::logreg == 1 ? Menu::logreg = old_tab, content_animation = 0.0f : Menu::logreg = 1, content_animation = 0.0f; 
                                    Menu::logreg = 1;
                                }
                            }
                            ImGui::PopFont();
                            ImGui::PopStyleColor();
                        }
                        if (animate == true)
                        {
                            ImGui::SetCursorPos(ImVec2(225, 445 * content_animation));
                            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 180));
                            ImGui::PushFont(Gay);
                            ImGui::Text(skCrypt("Driver loading."));
                            ImGui::PopFont();
                            ImGui::PopStyleColor();

                            ImGui::PushFont(Gay);
                            ImGui::SetCursorPos(ImVec2(100, 460 * content_animation));
                            ImGui::ProgressBar(progress, ImVec2(350.f, 10.0f));
                            ImGui::PopFont();
                            progress += progress_dir * 0.5f * ImGui::GetIO().DeltaTime;
                            if (progress >= +1.1f) {
                                progress = +1.1f;

                                DriverINNIT();
                                LastLogin = tm_to_readable_time(timet_to_tm(string_to_timet(KeyAuthApp.data.lastlogin)));
                                if (birkez)
                                {
                                    birkez = false;
                                }
                            }
                        }

                        ImGui::PopStyleColor();
                        ImGui::PopFont();
                        ImGui::PopStyleColor();
                    }

                   

                    

                    
                     //ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(CursorPos.x , CursorPos.y + 450), ImVec2(CursorPos.x + 120, CursorPos.y + 800), ImColor(0, 0, 0, 255));

                }
                ImGui::End();
            }
        }
        if (Menu::tab == 2)
        {
            Menu::Theme2();
            {
                ImGui::Begin(skCrypt("Holl Cheat"), &Enabled, ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
                {
                    auto draw = ImGui::GetWindowDrawList();
                    ImVec2 pos = ImGui::GetWindowPos();
                    ImVec2 size = ImGui::GetWindowSize();

                    draw->AddLine(ImVec2(pos.x, pos.y + 5), ImVec2(pos.x + size.x, pos.y + 5), ImColor(46, 46, 46)); // upper line
                    draw->AddRectFilledMultiColor(ImVec2(pos.x, pos.y + 6), ImVec2(pos.x + size.x, pos.y + 480 * 1), ImColor(0, 0, 50), ImColor(0, 0, 10), ImColor(0, 0, 50, 0), ImColor(0, 0, 0, 0));

                    if (update_on_f5) { if (GetAsyncKeyState(VK_F5)) content_animation = 0.0f; } // lol
                    content_animation = ImLerp(content_animation, content_animation < 1.0f ? 1.0f : 0.0f, 0.1f * (1.0f - ImGui::GetIO().DeltaTime));

                    ImVec2 CursorPos = ImGui::GetWindowPos();
                    ImGui::SetWindowSize(ImVec2(580, 480));
                    ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(5, 5, 5, 255));
                    ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(9, 9, 9, 255));

                    //dot_draw();

                    // ImGui::GetWindowDrawList()->AddTriangleFilled(ImVec2(CursorPos.x, CursorPos.y + 200), ImVec2(CursorPos.x + 450, CursorPos.y + 800), ImVec2(CursorPos.x + 0, CursorPos.y + 800), ImColor(8, 8, 8, 255));


                    ImGui::PopStyleColor(2);
                    //ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(CursorPos.x, CursorPos.y + 45), ImVec2(CursorPos.x + 150, CursorPos.y + 800), ImColor(8, 8, 8, 255));
                    ImGui::GetWindowDrawList()->AddLine(ImVec2(CursorPos.x + 150, CursorPos.y), ImVec2(CursorPos.x + 150, CursorPos.y + 800), ImColor(255, 255, 255, 10));

                    draw->AddRectFilledMultiColor(ImVec2(CursorPos.x, CursorPos.y + 45), ImVec2(CursorPos.x + 150, CursorPos.y + 800), ImColor(0, 0, 50), ImColor(0, 0, 10), ImColor(0, 0, 50, 0), ImColor(0, 0, 0, 0));


                    ImGui::SetCursorPos(ImVec2(540, 6));
                    ImGui::PushFont(Font);
                    if (ImGui::ButtonNew("X", ImVec2(30, 30)))
                    {
                        exit(-1);
                    }
                    ImGui::PopFont();

                  /*  ImGui::SetCursorPos(ImVec2(510, 10));
                    ImGui::PushFont(Font2);
                    if (ImGui::ButtonNew(skCrypt(ICON_FA_SIGN_OUT), ImVec2(30, 30)))
                    {
                        if (Menu::tab != 1) old_tab = Menu::tab;
                        Menu::tab == 1 ? Menu::tab = old_tab, content_animation = 0.0f : Menu::tab = 1, content_animation = 0.0f;
                        animate = false;
                        progress = 0.f;
                        Menu::tab = 1;

                    }
                    ImGui::PopFont();*/

                    ImGui::SetCursorPos(ImVec2(40, 7));
                    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
                    ImGui::PushFont(BigBigbGay);
                    ImGui::TextColored(ImColor(0, 0, 120, 255), skCrypt("Arbit"));
                    ImGui::Separator();
                    ImGui::PopFont();
                    ImGui::PushFont(NotGay);

                    ImGui::SetCursorPos(ImVec2(15, 460));
                    ImGui::TextColored(ImColor(255, 255, 255, 255), LISANS.c_str());

                    std::string YUSIRNEYM = "Username: " + KeyAuthApp.data.username;
                    ImGui::SetCursorPos(ImVec2(160, 20));
                    ImGui::TextColored(ImColor(255, 255, 255, 150), YUSIRNEYM.c_str());
                    ImGui::PopFont();
                    ImGui::PopStyleColor();

                    ImGui::SetCursorPos(ImVec2(50, 70 * content_animation));
                    ImGui::PushFont(Font);
                    if (ImGui::ButtonNew(skCrypt(ICON_FA_GAMEPAD), ImVec2(50, 50)))
                    {
                        if (tabs != 1) old_tab = tabs;
                        tabs == 1 ? tabs = old_tab, content_animation = 0.0f : tabs = 1, content_animation = 0.0f;
                        tabs = 1;

                    }
                    ImGui::SetCursorPos(ImVec2(50, 130 * content_animation));
                    ImGui::PushFont(Font);
                    if (ImGui::ButtonNew(skCrypt(ICON_FA_BARS), ImVec2(50, 50)))
                    {
                        if (tabs != 2) old_tab = tabs;
                        tabs == 2 ? tabs = old_tab, content_animation = 0.0f : tabs = 2, content_animation = 0.0f;
                        tabs = 2;
                    }
                    ImGui::PopFont();

                    ImGui::SetCursorPos(ImVec2(50, 180 * content_animation));
                    ImGui::PushFont(Font);
                    if (ImGui::ButtonNew(skCrypt(ICON_FA_USER), ImVec2(50, 50)))

                    {
                        if (tabs != 3) old_tab = tabs;
                        tabs == 3 ? tabs = old_tab, content_animation = 0.0f : tabs = 3, content_animation = 0.0f;
                        tabs = 3;
                    }
                    ImGui::PopFont();

                   

              
                
                    if (tabs == 1)
                    {
                        ImGui::BeginGroup();
                        ImGui::SetCursorPos(ImVec2(160, 50 * content_animation));
                        ImGui::PushFont(BigGay);
                        ImGui::MenuChild(skCrypt("Main"), ImVec2(410, 420), false, ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);
                        {

                            ImGui::SetCursorPos({ 0,35 * content_animation });
                            ImGui::Checkbox2(skCrypt(" Esp"), &ESP);
                            ImGui::SetCursorPos({ 0,60 * content_animation });
                            ImGui::Checkbox2(skCrypt(" Chams"), &CHAMS);
                            ImGui::SetCursorPos({ 130,87 * content_animation }); ImGui::PushItemWidth(200); ImGui::SliderInt(skCrypt("Time Value"), &TimeValue, 1, 24, "% .1f"); ImGui::SetCursorPos({ 0,85 * content_animation });
                            ImGui::Checkbox2(skCrypt(" TimeChanger"), &TimeChanger);
                            ImGui::SetCursorPos({ 130,112 * content_animation }); ImGui::PushItemWidth(200); ImGui::SliderInt(skCrypt("Fov Value"), &FovValue, 90, 150, "% .2f"); ImGui::SetCursorPos({ 0,110 * content_animation });
                            ImGui::Checkbox2(skCrypt(" GraphicFov"), &GraphicFov);

                            ImGui::SetCursorPos({ 0,145 * content_animation });
                            ImGui::Separator();

                            ImGui::SetCursorPos({ 0,160 * content_animation });
                            ImGui::Checkbox2(skCrypt(" Spiderman"), &Spiderman);
                            ImGui::SetCursorPos({ 130,187 * content_animation }); ImGui::KeyBind(skCrypt("FlyHack Key"), FlyHackButon, ImVec2(100, 0)); ImGui::SetCursorPos({ 0,185 * content_animation });
                            ImGui::Checkbox2(skCrypt(" Flyhack"), &Flyhack);
                            ImGui::SetCursorPos({ 130,212 * content_animation }); ImGui::KeyBind(skCrypt("Climb Key"), climbbutton, ImVec2(100, 0)); ImGui::SetCursorPos({ 0,210 * content_animation });
                            ImGui::Checkbox2(skCrypt(" Climb"), &Climb);
                            ImGui::SetCursorPos({ 0,235 * content_animation });
                            ImGui::Checkbox2(skCrypt(" AdminFlag"), &AdminFlag);
                            ImGui::SetCursorPos({ 0,260 * content_animation });
                            ImGui::Checkbox2(skCrypt(" Brightness"), &nighttmode);

                        }    
                        ImGui::PopFont();
                        ImGui::EndChild();
                        ImGui::EndGroup();
                    }
                    if (tabs == 2)
                    {
                        ImGui::BeginGroup();
                        ImGui::SetCursorPos(ImVec2(160, 50 * content_animation));
                        ImGui::PushFont(BigGay);
                        ImGui::MenuChild(skCrypt("Misc"), ImVec2(410, 420), false, ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);
                        {
                            ImGui::SetCursorPos({ 0,35 * content_animation });
                            ImGui::Checkbox2(skCrypt(" No Recoil"), &NoRecoil);
                            ImGui::SetCursorPos({ 0,60 * content_animation });
                            ImGui::Checkbox2(skCrypt(" Thick Bullet"), &FatBullet);
                            ImGui::SetCursorPos({ 0,85 * content_animation });
                            ImGui::Checkbox2(skCrypt(" No Spread"), &NoSpread);
                            ImGui::SetCursorPos({ 0,110 * content_animation });
                            ImGui::Checkbox2(skCrypt(" Automatic"), &Automatic);
                            ImGui::SetCursorPos({ 0,135 * content_animation });
                            ImGui::Checkbox2(skCrypt(" No Sway"), &NoSway);
                            ImGui::SetCursorPos({ 0,160 * content_animation });
                            ImGui::Checkbox2(skCrypt(" Super Eoka"), &SuperEoka);
                            ImGui::SetCursorPos({ 0,185 * content_animation });
                            ImGui::Checkbox2(skCrypt(" Super Meele"), &supermeele);

                        }       
                        ImGui::PopFont();
                        ImGui::EndChild();
                        ImGui::EndGroup();
                    }
                    if (tabs == 3)
                    {
                        ImGui::BeginGroup();
                        ImGui::SetCursorPos(ImVec2(160, 50 * content_animation));
                        ImGui::PushFont(BigGay);
                        ImGui::MenuChild(skCrypt("User data"), ImVec2(410, 420), false, ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);
                        {
                            ImGui::Text(skCrypt("\n Username: %s"), KeyAuthApp.data.username);
                            ImGui::Text(skCrypt("\n IP address: %s"), KeyAuthApp.data.ip);
                            std::string Hwid = "\n Hardware-Id: " + KeyAuthApp.data.hwid;
                            ImGui::Text((Hwid.c_str()));
                            std::string LLogin = "\n Last login: " + LastLogin;
                            ImGui::Text(LLogin.c_str());
                            ImGui::Text(skCrypt("\n Number of users: %s"), KeyAuthApp.data.numUsers);
                            ImGui::Text(skCrypt("\n Version: %s"), KeyAuthApp.data.version);
                            std::string LisansZMN = "\n Subs expiry: " + LisansinKalanZamani + " Days";
                            ImGui::Text(LisansZMN.c_str());
                        }           
                        ImGui::PopFont();
                        ImGui::EndChild();
                        ImGui::EndGroup();
                    }


                }
                ImGui::End();
            }
        }
       
        ImGui::EndFrame();

        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
            ResetDevice();
        }
        if (!Enabled) {
            msg.message = WM_QUIT;
        }
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    DestroyWindow(Window);
    UnregisterClass(wc.lpszClassName, wc.hInstance);

    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {

            ResetDevice();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}



int main()
{
   ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
   mainprotect();
   std::thread(hile).detach();
   WinMain(0, 0, 0, 0);
}

#include <iostream>
#include<fstream>
#include<winuser.h>
#include<windows.h>
