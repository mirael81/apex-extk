#include <mutex>
#include <unordered_map>

#include "../utils/includes.h"
#include "../utils/offsets.hpp"
#include "../utils/Vector.hpp"



class SDK {
public:

    class Game {
    public: class Get {
    public: std::uint64_t getAddress();
    private: std::uintptr_t Address;
    };
          class Script : public Get {
          public: std::string GetName(int i);
                std::string getModelName();
             
              std::string getSignifierName();

          };
          class WorldToScreen : public Script {
          public: Vector3 W2S(Vector3 Position);
          };
    };
    class Glow : public Game::Get {
    public:/* void SetGlow(int GlowEnabled, int GlowThroughWall, int HighlightID);
          void DisableGlow();*/
    };
    class Loot {
    public:
        int GetIndex();
        Vector3 GetPosition();
    };
    class Entity : public SDK::Game::WorldToScreen {
    public:
        //Variables
        int Health;
        int Shield;
        int Max_Shield;
        int Shield_Type;
        int Level;
        bool Is_Alive;
        bool IsPlayer;
        bool IsLocalPlayer;
        float Distance;
        float Width;
        float Height;
        std::string Name;
        std::string Operator;
        Vector3 Feet_Position;
        Vector3 Head_Position;
        std::vector < Entity* > List;

        //Accessor functions
        Entity* LocalPlayer();
        Glow* GetGlow();
    public: class Collision : public SDK::Game::Get {
    public: Vector3 Get_VecMin();
          Vector3 Get_VecMax();
          Vector3 Get_vecSpecifiedSurroundingMins();
          Vector3 Get_vecSpecifiedSurroundingMaxs();

          int Get_SolidFlags();
          int Get_SolidType();
          int Get_triggerBloat();
          int Get_collisionDetailLevel();
          int Get_SurroundType();
         
       /*   void Set_VecMin(Vector3 Min);
          void Set_VecMax(Vector3 Max);
          void Set_vecSpecifiedSurroundingMins(Vector3 Min);
          void Set_vecSpecifiedSurroundingMaxs(Vector3 Max);

          void Set_SolidFlags(int Flag);
          void Set_SolidType(int Type);
          void Set_triggerBloat(int Trigger);
          void Set_collisionDetailLevel(int Level);
          void Set_SurroundType(int Type);*/

    };
        /*  class ViewModel : public SDK::Game::Get {
          public: void Set_ViewOffset(int Value);
                void Set_StabilizePlayerEyes(int Value);
          };
          class AnimationData : public SDK::Game::Get {
          public: void StabilizePlayerEyes(int value);
                void DrawLocalPlayer(int value);
                void ThirdPersonCamera(int value);
          };
          class Camera : public SDK::Game::Get {
          public: void Set_Fov(float FOV);
                void Set_Fog(bool value);
          };*/
          bool Update();
          int Get_Current_shield();
          int Get_Max_shield();
          int Get_shield_type();
          int Get_Network_Flags();
        /*  void Set_Network_Flags(int Network_Flag);
          void ignoreParentRotation(int Rotation);*/
          int Get_TeamNum();
          int Get_Squad();
          //void Set_PassthroughThickness(int thickness);
          bool Get_Alive();
          bool Get_IsLocalPlayer();
          float Get_Height();
          float Get_Width();
          Vector3 Get_Position();
          Vector3 getBonePos(int ID);
          Vector3 GetBonePositionByHitBox(int ID);
          Vector3 ViewAngles();
          void SetViewAngles(Vector2 Angles);
          float GetDistance();
          bool Get_IsPlayer();
          float LastKillTime();
          int Current_Health();
          int Get_Level();
          std::string GetOperator();
          int GetWeaponIndex();
      
         /* ViewModel* Get_ViewModel();
          AnimationData* Get_AnimationData();
          Camera* Get_Camera();*/
          Collision* Get_Collision();

    };

    std::mutex PlayerUpdateMutex;
    std::uint64_t R5Apex = NULL;
    SDK::Entity* LocalPlayer = new SDK::Entity;
    Vector2 DisplaySize = {
      (float)GetSystemMetrics(0),
      (float)GetSystemMetrics(1)
    };
};
inline SDK sdk;
inline std::vector < SDK::Entity* > Entity_List;


inline Vector3 W2S(Vector3 Position) {
    std::uintptr_t render = Read < std::uintptr_t >(sdk.R5Apex + Offsets::Misc::m_ViewRender);
    if (!render) {
#ifdef DEBUG
        LOG_DEBUG(_(" Error std::uintptr_t render = Read<std::uintptr_t>(sdk.R5Apex + Offsets::Misc::m_ViewRender) ? NULL"));
#endif
        return {
          0,
          0,
          0
        };
    }

    std::uintptr_t Matrixa = Read < std::uintptr_t >(Offsets::Misc::m_ViewMatrix + render);
    if (!Matrixa) {
#ifdef DEBUG
        LOG_DEBUG(_(" Error std::uintptr_t  Matrixa = Read<std::uintptr_t>(Offsets::Misc::m_ViewMatrix + render) ? NULL"));
#endif
        return {
          0,
          0,
          0
        };
    }

    BaseMatrix Matrix = Read < BaseMatrix >(Matrixa);

    Vector3 out;
    float _x = Matrix.at[0] * Position.x + Matrix.at[1] * Position.y + Matrix.at[2] * Position.z + Matrix.at[3];
    float _y = Matrix.at[4] * Position.x + Matrix.at[5] * Position.y + Matrix.at[6] * Position.z + Matrix.at[7];
    out.z = Matrix.at[12] * Position.x + Matrix.at[13] * Position.y + Matrix.at[14] * Position.z + Matrix.at[15];

    if (out.z < 0.1f) return {
      0,
      0,
      0
    };

    _x *= 1.f / out.z;
    _y *= 1.f / out.z;

    out.x = sdk.DisplaySize.x * .5f;
    out.y = sdk.DisplaySize.y * .5f;

    out.x += 0.5f * _x * sdk.DisplaySize.x + 0.5f;
    out.y -= 0.5f * _y * sdk.DisplaySize.y + 0.5f;

    return out;
}

inline Vector3 GetBonePositionByHitBox(uint64_t Ent, int ID) {
    Vector3 origin = Read<Vector3>(Ent + Offsets::C_BaseEntity::m_m_vecAbsOrigin);
    //BoneByHitBox
    uint64_t Model = Read < uint64_t >(Ent + 0xff0);

    //get studio hdr
    uint64_t StudioHdr = Read < uint64_t >(Model + 0x8);

    //get hitbox array
    uint16_t HitboxCache = Read < uint16_t >(StudioHdr + 0x34);
    uint64_t HitBoxsArray = StudioHdr + ((uint16_t)(HitboxCache & 0xFFFE) << (4 * (HitboxCache & 1)));

    uint16_t IndexCache = Read < uint16_t >(HitBoxsArray + 0x4);
    int HitboxIndex = ((uint16_t)(IndexCache & 0xFFFE) << (4 * (IndexCache & 1)));

    uint16_t Bone = Read < uint16_t >(HitBoxsArray + HitboxIndex + (ID * 0x20));

    if (Bone < 0 || Bone > 255)
        return Vector3();

    //hitpos
    uint64_t BoneArray = Read < uint64_t >(Ent + Offsets::Misc::m_Bones);
    uintptr_t Add = BoneArray + Bone * sizeof(matrix3x4_t);
    matrix3x4_t Matrix = Read < matrix3x4_t >(Add);

    return Vector3(Matrix.m_flMatVal[0][3] + origin.x, Matrix.m_flMatVal[1][3] + origin.y, Matrix.m_flMatVal[2][3] + origin.z);
}


inline std::string get_weapon_name(uint64_t playerEntity)
{
    uint64_t primary_weapons_latest = Read<uint64_t>(playerEntity + Offsets::Misc::m_PrimaryWeapon) & 0xFFFF;
    uint64_t primary_weapons_list = Read<uint64_t>(sdk.R5Apex + Offsets::Misc::m_EntityList + (primary_weapons_latest * 0x20));
    int weapon_index = Read<int>(primary_weapons_list + 0x1788); // weapon name0x1574 0x0769b4b8
    static const std::unordered_map<int, std::string> weapon_map = {
        {WeaponIDs::R301, _("R301")},                // 0
        {WeaponIDs::BOCEK, "Bocek"},              // 2
        {WeaponIDs::HAVOC, "Havoc"},              // 91 (previously 86)
        {WeaponIDs::DEVOTION, "Devotion"},        // 89 (previously 84)
        {WeaponIDs::LSTAR, "L-Star"},             // 99 (previously 94)
        {WeaponIDs::TRIPLE_TAKE, "Triple Take"},  // 114 (previously 108)
        {WeaponIDs::VOLT, "Volt"},                // 117 (previously 111)
        {WeaponIDs::NEMESIS, "Nemesis"},          // 120 (previously 114)
        {WeaponIDs::FLATLINE, "Flatline"},        // 94 (previously 89)
        {WeaponIDs::HEMLOCK, "Hemlock"},          // 96 (previously 91)
        {WeaponIDs::REPEATER_3030, "30-30 Repeater"}, // 118 (previously 112)
        {WeaponIDs::RAMPAGE, "Rampage"},          // 6  (previously 21)
        {WeaponIDs::CAR, "C.A.R"},                // 119 (previously 113)
        {WeaponIDs::P2020, "P2020"},              // 112 (previously 106)
        {WeaponIDs::RE45, "RE45"},                // 85 (previously 81)
        {WeaponIDs::ALTERNATOR, "Alternator"},    // 84 (previously 80)
        {WeaponIDs::R99, "R99"},                  // 111 (previously 105)
        {WeaponIDs::SPITFIRE, "Spitfire"},        // 113 (previously 107)
        {WeaponIDs::G7_SCOUT, "G7 Scout"},        // 95 (previously 90)
        {WeaponIDs::MOZAMBIQUE, "Mozambique"},    // 102 (previously 97)
        {WeaponIDs::EVA8, "EVA-8 Auto"},          // 92 (previously 88)
        {WeaponIDs::PEACEKEEPER, "Peacekeeper"},  // 109 (previously 104)
        {WeaponIDs::SENTINEL, "Sentinel"},        // 1  (same as before)
        {WeaponIDs::CHARGE_RIFLE, "Charge Rifle"}, // 87 (previously 83)
        {WeaponIDs::LONGBOW, "Longbow"},          // 90 (previously 85)
        {WeaponIDs::MASTIFF, "Mastiff"},          // 101 (previously 96)
        {WeaponIDs::PROWLER, "Prowler"},          // 107 (previously 102)
        {WeaponIDs::WINGMAN, "Wingman"},          // 115 (previously 110)
        {WeaponIDs::KRABER, "Kraber"},            // 98 (previously 93)
        {WeaponIDs::KNIFE, "Knife"}               // 176 (corrected from 166)
    };
    auto it = weapon_map.find(weapon_index);
    if (it != weapon_map.end()) {
        return it->second;
    }

    return "None";
}
inline int visentcount = 0;
inline uint64_t GameAssmebly = 0;

inline std::vector<SDK::Entity*> EntityList;
inline int Size = 20000;
namespace WebRadarHack {
    inline std::vector<std::string> PositionList;
}

inline int EntityCount = 0;
inline std::vector<SDK::Entity*> TempEntiyList;
inline std::vector<SDK::Entity*> BackupTempEntiyList;
inline std::vector<SDK::Loot*> LootList;
inline std::vector<SDK::Entity*> TempEntList;
inline std::mutex entity_mutex;
inline std::string LevelName;
