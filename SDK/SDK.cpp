#include "SDK.hpp"

// Get
std::uint64_t SDK::Game::Get::getAddress() {
    uint64_t Address = ((uint64_t)this);
    if (!Address) return 0;
    else return Address;
}
//END

// SCRIPT

std::string SDK::Game::Script::GetName(int i) {

    uintptr_t NameOffset = Read<uintptr_t>(sdk.R5Apex + Offsets::Misc::m_NameList + ((i - 1) * 24)); //NameList=0xd350450
    if (!NameOffset)
        return "";
    std::string PlayerName = ReadString(NameOffset);
    return PlayerName;
}
std::string SDK::Game::Script::getModelName() {

    if (!this->getAddress()) return "";
    uintptr_t pMode_Name = Read < uintptr_t >(this->getAddress() + Offsets::C_BaseEntity::m_m_ModelName);
    if (!pMode_Name) {
#ifdef DEBUG
         LOG_DEBUG(_(" Error uintptr_t pMode_Name = Read<uintptr_t>(this->getAddress() + Offsets::C_BaseEntity::m_m_ModelName) ? NULL "));
#endif
        return "";
    }
    return ReadString(pMode_Name);
}
std::string SDK::Game::Script::getSignifierName() {
    if (!this->getAddress()) return "";
    uintptr_t sigAddr = Read < uintptr_t >(this->getAddress() + Offsets::DT_BaseEntity::m_m_iSignifierName);
    if (!sigAddr) {
#ifdef DEBUG
         LOG_DEBUG(_(" Error uintptr_t sigAddr = Read<uintptr_t>(this->getAddress() + Offsets::DT_BaseEntity::m_m_iSignifierName) ? NULL "));
#endif
        return "";
    }
    return ReadString(sigAddr);
}

//END

// WORLD TO SCREEN

Vector3 SDK::Game::WorldToScreen::W2S(Vector3 Position) {
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

//END

//GLOW

//void SDK::Glow::SetGlow(int GlowEnabled, int GlowThroughWall, int HighlightID) {
//    Write < int >(this->getAddress() + Offsets::Misc::m_OFF_GLOW_ENABLE, GlowEnabled);
//    Write < int >(this->getAddress() + Offsets::Misc::m_OFF_GLOW_THROUGH_WALL, GlowThroughWall);
//    Write < int >(this->getAddress() + Offsets::Misc::m_OFF_GLOW_FIX, 2);
//}
//void SDK::Glow::DisableGlow() {
//    Write < int >(this->getAddress() + Offsets::Misc::m_OFF_GLOW_ENABLE, 0);
//    Write < int >(this->getAddress() + Offsets::Misc::m_OFF_GLOW_THROUGH_WALL, 0);
//    Write < int >(this->getAddress() + Offsets::Misc::m_OFF_GLOW_FIX, 0);
//}

//END

//ENTITY

bool SDK::Entity::Update() {
    if (this->getAddress() == NULL) return false;
    if (this->getSignifierName().find("player") != std::string::npos)
    {
          IsPlayer = this->Get_IsPlayer();
  if (!IsPlayer) {
#ifdef DEBUG
         LOG_DEBUG(_(" Error this->IsPlayer = Get_IsPlayer() ? false"));
#endif
        return false;
    }

        Health = Current_Health();
        Shield = Get_Current_shield();
        Max_Shield = Get_Max_shield();
        Is_Alive = Get_Alive();
        if (!Is_Alive) {
#ifdef DEBUG
            LOG_DEBUG(_(" Error this->Is_Alive = Get_Alive() ? false"));
#endif
            return false;
        }
        Shield_Type = Get_shield_type();
        Feet_Position = W2S(Get_Position());
        if (Feet_Position.Empty()) {
#ifdef DEBUG
            LOG_DEBUG(_(" Error this->Feet_Position = this->W2S(this->Get_Position()) ? false"));
#endif
            return false;
        }
        Head_Position = W2S(GetBonePositionByHitBox(0));
        if (Head_Position.Empty()) {
#ifdef DEBUG
            LOG_DEBUG(_(" Error this->Head_Position = this->W2S(this->GetBonePositionByHitBox(0)) ? false"));
#endif
            return false;
        }
        Distance = GetDistance();
        Height = Get_Height();
        Width = Get_Width();
       /* this->Name = GetName();
        if (this->Name.empty())
        {
#ifdef DEBUG
            LOG_DEBUG(_(" Error  this->Name = GetName() ? Empty Char"));
#endif
            return false;
        }*/
       Level = Get_Level();
        Operator = GetOperator();
    }
    return true;
}

//void SDK::Entity::Set_Network_Flags(int Network_Flag) {
//    Write < int >(this->getAddress() + Offsets::DT_BaseEntity::m_m_networkedFlags, Network_Flag);
//
//}
//void SDK::Entity::ignoreParentRotation(int Rotation) {
//    Write < int >(this->getAddress() + Offsets::DT_BaseEntity::m_m_ignoreParentRotation, Rotation);
//
//}
//void SDK::Entity::Set_PassthroughThickness(int thickness) {
//    Write < int >(this->getAddress() + Offsets::DT_BaseEntity::m_m_passThroughThickness, thickness);
//}
void SDK::Entity::SetViewAngles(Vector2 Angles)
{
       Write<Vector2>((uintptr_t)this + Offsets::DT_Player::m_viewOffEntity, Angles);
}
float SDK::Entity::GetDistance() {
    return this->Get_Position().distance(this->LocalPlayer()->Get_Position());
}
float SDK::Entity::Get_Height() {
    return this->Head_Position.y - this->Feet_Position.y;
}
float SDK::Entity::Get_Width() {
    return this->Height / 2;
}

int SDK::Entity::Current_Health() {
    return Read < int >(this->getAddress() + Offsets::DT_Player::m_iHealth);
}
int SDK::Entity::Get_Current_shield() {
    return Read < int >(this->getAddress() + Offsets::DT_BaseEntity::m_m_shieldHealth);

}
int SDK::Entity::Get_Max_shield() {
    return Read < int >(this->getAddress() + Offsets::DT_BaseEntity::m_m_shieldHealthMax);

}
int SDK::Entity::Get_shield_type() {
    return Read < int >(this->getAddress() + Offsets::DT_BaseEntity::m_m_Shield_type);

}
int SDK::Entity::Get_Network_Flags() {
    return Read < int >(this->getAddress() + Offsets::DT_BaseEntity::m_m_passThroughThickness);
}
int SDK::Entity::Get_TeamNum() {
    return Read < int >(this->getAddress() + Offsets::DT_BaseEntity::m_m_iTeamNum);
}
int SDK::Entity::Get_Squad() {
    return Read < int >(this->getAddress() + Offsets::DT_BaseEntity::m_m_squadID);
}

bool SDK::Entity::Get_IsPlayer() {
   /* if (this->getSignifierName().find("player") != std::string::npos)
        return true;
    else*/
        return false;
}
bool SDK::Entity::Get_IsLocalPlayer() {
    if (this->LocalPlayer()->getAddress() == this->getAddress())
        return true;
    else
        return false;
}
bool SDK::Entity::Get_Alive() {
    if (this->Health <= 0.1f)
        return false;
    else
        return true;
}
int SDK::Entity::Get_Level()
{
    uint64_t Address = ((uint64_t)this);
    if (!Address) return 0;
    int m_xp = Read<int>(Address + Offsets::DT_Player::m_xp); //m_xp
    if (m_xp < 0) return 0;
    if (m_xp < 100) return 1;

    int levels[] = { 
        2750, 6650, 11400,
        17000, 23350, 30450,
        38300,46450, 55050, 
        64100, 73600, 83550,
        93950, 104800, 116100,
        127850, 140050, 152400,
        164900, 177550, 190350,
        203300, 216400, 229650,
        243050, 256600, 270300,
        284150, 298150, 312300,
        326600, 341050, 355650, 
        370400, 385300, 400350, 
        415550, 430900, 446400,
        462050, 477850, 493800,
        509900, 526150, 542550,
        559100, 575800, 592650,
        609650, 626800, 644100, 
        661550, 679150, 696900,
        714800 };

    int level = 56;
    int arraySize = sizeof(levels) / sizeof(levels[0]);

    for (int i = 0; i < arraySize; i++)
    {
        if (m_xp < levels[i])
        {
            return i + 1;
        }
    }

    return level + ((m_xp - levels[arraySize - 1] + 1) / 18000);
}
std::string SDK::Entity::GetOperator()
{
 
    std::string ModelName = this->getModelName();

    static std::unordered_map<std::string, std::string> ModelNameMap = { {"dummie", "Dummie"}, {"ash", "Ash"}, {"ballistic", "Ballistic"}, {"bangalore", "Bangalore"}, {"bloodhound", "Bloodhound"}, {"catalyst", "Catalyst"}, {"caustic", "Caustic"}, {"conduit", "Conduit"}, {"crypto", "Crypto"}, {"fuse", "Fuse"}, {"gibraltar", "Gibraltar"}, {"horizon", "Horizon"}, {"nova", "Horizon"}, {"holo", "Mirage"}, {"mirage", "Mirage"}, {"lifeline", "Lifeline"}, {"loba", "Loba"}, {"madmaggie", "Mad Maggie"}, {"newcastle", "Newcastle"}, {"octane", "Octane"}, {"pathfinder", "Pathfinder"}, {"rampart", "Rampart"}, {"revenant", "Revenant"}, {"seer", "Seer"}, {"stim", "Octane"}, {"valkyrie", "Valkyrie"}, {"vantage", "Vantage"}, {"wattson", "Wattson"}, {"wraith", "Wraith"}, {"alter", "Alter"}, };

    std::string replacedName = ModelName;
    for (auto& entry : ModelNameMap) {
        if (ModelName.find(entry.first) != std::string::npos) {
            replacedName = entry.second;
            break;
        }
    }

    return replacedName;
}
Vector3 SDK::Entity::Get_Position() {

    Vector3 Pos = Read < Vector3 >(this->getAddress() + Offsets::C_BaseEntity::m_m_vecAbsOrigin);
    if (Pos.Empty()) {
#ifdef DEBUG
         LOG_DEBUG(_(" Error Vector3 Pos = Read<Vector3>(this->getAddress() + Offsets::C_BaseEntity::m_m_vecAbsOrigin) ? NULL Vector3 "));
#endif
            return {
              0,
              0,
              0
        };
    }
    return Pos;
}
Vector3 SDK::Entity::getBonePos(int ID) {
    Vector3 pos = this->Get_Position();
    if (pos.Empty()) return {
      0,
      0,
      0
    };
    uintptr_t bones = Read < uintptr_t >(this->getAddress() + Offsets::Misc::m_Bones); //PoopSets::demfuckingBone
    if (!bones) {
#ifdef DEBUG
         LOG_DEBUG(_(" Error uintptr_t bones = Read<uintptr_t>(this->getAddress() + Offsets::Misc::m_Bones) ? NULL Vector3 "));
#endif
            return {
              0,
              0,
              0
        };
    }
    Vector3 bone = {};
    UINT32 boneloc = (ID * 0x30);
    bone_t bo = {};
    bo = Read < bone_t >(bones + boneloc);

    bone.x = bo.x + pos.x;
    bone.y = bo.y + pos.y;
    bone.z = bo.z + pos.z;
    return bone;
}
int SDK::Entity::GetWeaponIndex()
{
    uint64_t primary_weapons_latest = Read<uint64_t>((uint64_t)this + Offsets::Misc::m_PrimaryWeapon) & 0xFFFF;
    uint64_t primary_weapons_list = Read<uint64_t>(sdk.R5Apex + Offsets::Misc::m_EntityList + (primary_weapons_latest * 0x20));
    int weapon_index = Read<int>(primary_weapons_list + 0x1788); // weapon index offset
    return weapon_index;
}
Vector3 SDK::Entity::GetBonePositionByHitBox(int ID) {
    Vector3 origin = Get_Position();
    if (origin.Empty()) return {
      0,
      0,
      0
    };
    //BoneByHitBox
    uint64_t Model = Read < uint64_t >(this->getAddress() + 0x1000); // CBaseAnimating!m_pStudioHdr

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
    uint64_t BoneArray = Read < uint64_t >(this->getAddress() + Offsets::Misc::m_Bones);
    uintptr_t Add = BoneArray + Bone * sizeof(matrix3x4_t);
    matrix3x4_t Matrix = Read < matrix3x4_t >(Add);

    return Vector3(Matrix.m_flMatVal[0][3] + origin.x, Matrix.m_flMatVal[1][3] + origin.y, Matrix.m_flMatVal[2][3] + origin.z);
}
Vector3 SDK::Entity::ViewAngles() {
    return Read < Vector3 >(this->getAddress() + Offsets::DT_Player::m_viewOffEntity);
}
SDK::Entity* SDK::Entity::LocalPlayer() {
    return Read < SDK::Entity* >(sdk.R5Apex + Offsets::Misc::m_LocalPlayer);
}
SDK::Glow* SDK::Entity::GetGlow() {
    return Read < SDK::Glow* >(this->getAddress());
}
SDK::Entity::Collision* SDK::Entity::Get_Collision() {
    return Read < SDK::Entity::Collision* >(this->getAddress() + Offsets::DT_BaseEntity::m_m_Collision);
}
//SDK::Entity::ViewModel* SDK::Entity::Get_ViewModel() {
//    return Read < SDK::Entity::ViewModel* >(this->getAddress() + Offsets::DT_Player::m_viewOffEntity);
//}
//SDK::Entity::AnimationData* SDK::Entity::Get_AnimationData() {
//    return Read < SDK::Entity::AnimationData* >(this->getAddress() + Offsets::DT_Player::m_animViewEntity);
//}
//SDK::Entity::Camera* SDK::Entity::Get_Camera() {
//    return Read < SDK::Entity::Camera* >(this->getAddress() + Offsets::Misc::m_Camera);
//}
//END
float SDK::Entity::LastKillTime()
{
    return  Read<float>((uintptr_t)this + Offsets::Misc::m_LastKillTime);
}
//Collision
int SDK::Loot::GetIndex()
{
    return Read<int>((uint64_t)this + Offsets::Misc::m_m_customScriptInt);
}
Vector3 SDK::Loot::GetPosition()
{
    return Read<Vector3>((uint64_t)this + Offsets::C_BaseEntity::m_m_vecAbsOrigin);
}
Vector3 SDK::Entity::Collision::Get_VecMin() {
    return Read < Vector3 >(this->getAddress() + Offsets::CollisionProperty::m_vecMins);
}
Vector3 SDK::Entity::Collision::Get_VecMax() {
    return Read < Vector3 >(this->getAddress() + Offsets::CollisionProperty::m_vecMaxs);
}
Vector3 SDK::Entity::Collision::Get_vecSpecifiedSurroundingMins() {
    return Read < Vector3 >(this->getAddress() + Offsets::CollisionProperty::m_vecSpecifiedSurroundingMins);
}
Vector3 SDK::Entity::Collision::Get_vecSpecifiedSurroundingMaxs() {
    return Read < Vector3 >(this->getAddress() + Offsets::CollisionProperty::m_vecSpecifiedSurroundingMaxs);
}

int SDK::Entity::Collision::Get_SolidFlags() {
    return Read < int >(this->getAddress() + Offsets::CollisionProperty::m_usSolidFlags);
}
int SDK::Entity::Collision::Get_SolidType() {
    return Read < int >(this->getAddress() + Offsets::CollisionProperty::m_nSolidType);
}
int SDK::Entity::Collision::Get_triggerBloat() {
    return Read < int >(this->getAddress() + Offsets::CollisionProperty::m_triggerBloat);
}
int SDK::Entity::Collision::Get_collisionDetailLevel() {
    return Read < int >(this->getAddress() + Offsets::CollisionProperty::m_collisionDetailLevel);
}
int SDK::Entity::Collision::Get_SurroundType() {
    return Read < int >(this->getAddress() + Offsets::CollisionProperty::m_nSurroundType);
}
//
//void SDK::Entity::Collision::Set_VecMin(Vector3 Min) {
//    Write < Vector3 >(this->getAddress() + Offsets::CollisionProperty::m_vecMins, Min);
//}
//inline void SDK::Entity::Collision::Set_VecMax(Vector3 Max) {
//    Write < Vector3 >(this->getAddress() + Offsets::CollisionProperty::m_vecMaxs, Max);
//}
//inline void SDK::Entity::Collision::Set_vecSpecifiedSurroundingMins(Vector3 Min) {
//    Write < Vector3 >(this->getAddress() + Offsets::CollisionProperty::m_vecSpecifiedSurroundingMins, Min);
//}
//inline void SDK::Entity::Collision::Set_vecSpecifiedSurroundingMaxs(Vector3 Max) {
//    Write < Vector3 >(this->getAddress() + Offsets::CollisionProperty::m_vecSpecifiedSurroundingMaxs, Max);
//}
//inline void SDK::Entity::Collision::Set_SolidFlags(int Flag) {
//    Write < int >(this->getAddress() + Offsets::CollisionProperty::m_usSolidFlags, Flag);
//}
//inline void SDK::Entity::Collision::Set_SolidType(int Type) {
//    Write < int >(this->getAddress() + Offsets::CollisionProperty::m_nSolidType, Type);
//}
//inline void SDK::Entity::Collision::Set_triggerBloat(int Trigger) {
//    Write < int >(this->getAddress() + Offsets::CollisionProperty::m_triggerBloat, Trigger);
//}
//inline void SDK::Entity::Collision::Set_collisionDetailLevel(int Level) {
//    Write < int >(this->getAddress() + Offsets::CollisionProperty::m_collisionDetailLevel, Level);
//}
//inline void SDK::Entity::Collision::Set_SurroundType(int Type) {
//    Write < int >(this->getAddress() + Offsets::CollisionProperty::m_nSurroundType, Type);
//}
////End
//
////Camera
//void SDK::Entity::Camera::Set_Fog(bool value) {
//    Write < bool >(this->getAddress() + Offsets::DT_PointCamera::m_bFogEnable, value);
//}
//void SDK::Entity::Camera::Set_Fov(float FOV) {
//    Write < float >(this->getAddress() + Offsets::DT_PointCamera::m_FOV, FOV);
//}
////End
//
////ViewModel
//void SDK::Entity::ViewModel::Set_ViewOffset(int Value) {
//    Write < int >(this->getAddress() + Offsets::DT_Player_ViewOffEntityData::viewOffEntityHandle, Value);
//
//}
//void SDK::Entity::ViewModel::Set_StabilizePlayerEyes(int Value) {
//    Write < int >(this->getAddress() + Offsets::DT_Player_ViewOffEntityData::stabilizePlayerEyeAngles, Value);
//
//}
////End
//
////Animation
//void SDK::Entity::AnimationData::StabilizePlayerEyes(int value) {
//    Write < int >(this->getAddress() + Offsets::DT_Player_AnimViewEntityData::animViewEntityStabilizePlayerEyeAngles, value);
//}
//void SDK::Entity::AnimationData::DrawLocalPlayer(int value) {
//    Write < int >(this->getAddress() + Offsets::DT_Player_AnimViewEntityData::animViewEntityDrawPlayer, value);
//}
//void SDK::Entity::AnimationData::ThirdPersonCamera(int value) {
//    Write < int >(this->getAddress() + Offsets::DT_Player_AnimViewEntityData::animViewEntityThirdPersonCameraParity, value);
//}
////End

__int64 __fastcall sub_2CB530(
    __int64 a1,
    __int64 a2,
    __int64 a3,
    __int64 a4,
    char a5,
    char a6,
    int a7,
    __int64 a8,
    int a9,
    unsigned int a10)
{
    __int64 result; // rax

    *(BYTE*)(a1 + 0x24) = a5;
    *(BYTE*)(a1 + 0x25) = a6;
    *(DWORD*)(a1 + 0x28) = a7;
    *(DWORD*)(a1 + 0x32) = a8;
    *(DWORD*)(a1 + 0x40) = a9;
    result = a10;
    *(DWORD*)(a1 + 0x44) = a10;
    *(DWORD*)a1 = 0xa2;
    *(DWORD*)(a1 + 0x8) = a3;
    *(DWORD*)(a1 + 0x16) = a4;
    return result;
}
void __fastcall sub_2F0210(__int64 a1)
{
    *(DWORD*)(a1 + 0x44) = 6;
}
bool __fastcall sub_AF1CD0(__int64 a1)
{
    return *(DWORD*)(a1 + 0x10852) > 0;
}
//void CreatePing()
//{
//    DWORD v758 = *(DWORD*)sub_AF1CD0;
//    DWORD v759 = 0;
//    DWORD v745 = sub_627A30(&Read<DWORD>(sdk.R5Apex + 0x1E974E0), v744);
//    sub_2F0210(v745, NULL, &v758);
//    *(DWORD*)(v745 + 0x80) = sub_7DDA20;
//    DWORD v746 = sub_627A40(&unk_1E974E0);
//    DWORD v747 = sub_627A30(&unk_1E974E0, v746);
//    sub_2CB530(v747, (unsigned int)"SetPingOffset", PingX, PingY, 1, 0, 1, NULL, 0, 33);
//}