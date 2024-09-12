#include "../utils/Features.hpp"
#include <fstream>
#include <string>
#include <filesystem>

// Random string names for config files
inline const char* configNames[] = { "abc123", "def456", "ghi789", "jkl012" };

// Obfuscated string names for ESP settings
inline const char* espSettings[] = { "Xx1A", "Fb6W", "Vc7R", "Al8Q", "Cb2F", "Ai9P", "Wi0O", "Db3X", "Pg1I", "Ek2U",
                             "Sk3Y", "Nm4T", "Ds4Y", "Oa5S", "Op6D", "Rd6C", "Sh7V", "Lv9Z", "Hg0N", "Wn7F",
                             "Gw8G", "Rg9H", "Oi0J", "Wg1K", "Hg2L", "Se3M", "Rt4N", "Rk5B", "Fa8X", "Bs1E" };

// Obfuscated string names for Aimbot settings
inline const char* aimbotSettings[] = { "Vb1A", "Ak2K", "Fc3C", "Fr4F", "Rc5C", "Fcs6S", "Sn7L", "Ps8P", "Tb9B", "Sa0G", "FcC1", "SlC2" };

// Obfuscated string names for Misc settings
inline const char* miscSettings[] = { "Fm1F", "Fd2D", "FdK3", "KgB4", "Ag5G", "Sc6H", "Si7I", "Ff8F", "Ab9A", "Sg0S" };

// Obfuscated string names for Settings
inline const char* settingsKeys[] = { "Cs1", "Rd2", "Rs3" };

// Obfuscated string names for Configurations
inline const char* configSettings[] = { "Cn0", "Ci1", "Lc2", "Sc3", "Rc4" };
inline bool CreateConfig()
{
    std::string Y9u3X5;
    switch (Cheat_Private::Config::ConfigIndex)
    {
    case 0:
        Y9u3X5 = configNames[0];  // "abc123"
        break;
    case 1:
        Y9u3X5 = configNames[1];  // "def456"
        break;
    case 2:
        Y9u3X5 = configNames[2];  // "ghi789"
        break;
    case 3:
        Y9u3X5 = configNames[3];  // "jkl012"
        break;
    }
    std::filesystem::path o9z2A4 = std::filesystem::current_path();
    std::filesystem::path m1p7K8 = o9z2A4 / Y9u3X5;

    std::ofstream t6r9L2(m1p7K8);

    if (!t6r9L2) {
        return false;
    }

    t6r9L2.close();
    return true;
}

inline bool SaveConfig()
{
    std::string Y9u3X5;
    switch (Cheat_Private::Config::ConfigIndex)
    {
    case 0:
        Y9u3X5 = configNames[0];  // "abc123"
        break;
    case 1:
        Y9u3X5 = configNames[1];  // "def456"
        break;
    case 2:
        Y9u3X5 = configNames[2];  // "ghi789"
        break;
    case 3:
        Y9u3X5 = configNames[3];  // "jkl012"
        break;
    }

    std::filesystem::path o9z2A4 = std::filesystem::current_path();
    std::filesystem::path m1p7K8 = o9z2A4 / Y9u3X5;
    std::ofstream t6r9L2(m1p7K8);

    if (!t6r9L2) {
        return false;
    }

    // Save ESP settings
    t6r9L2 << espSettings[0] << " : " << (Cheat_Private::ESP::Box ? "1" : "0") << "\n";
    t6r9L2 << espSettings[1] << " : " << (Cheat_Private::ESP::Filledbox ? "1" : "0") << "\n";
    t6r9L2 << espSettings[2] << " : " << (Cheat_Private::ESP::VisCheck ? "1" : "0") << "\n";
    t6r9L2 << espSettings[3] << " : " << (Cheat_Private::ESP::alert ? "1" : "0") << "\n";
    t6r9L2 << espSettings[4] << " : " << (Cheat_Private::ESP::CornerBox ? "1" : "0") << "\n";
    t6r9L2 << espSettings[5] << " : " << (Cheat_Private::ESP::ArmorICON ? "1" : "0") << "\n";
    t6r9L2 << espSettings[6] << " : " << (Cheat_Private::ESP::WeaponICON ? "1" : "0") << "\n";
    t6r9L2 << espSettings[7] << " : " << (Cheat_Private::ESP::DeathBox ? "1" : "0") << "\n";
    t6r9L2 << espSettings[8] << " : " << (Cheat_Private::ESP::PeterGriffen ? "1" : "0") << "\n";
    t6r9L2 << espSettings[9] << " : " << (Cheat_Private::ESP::EKitten ? "1" : "0") << "\n";
    t6r9L2 << espSettings[10] << " : " << (Cheat_Private::ESP::Skeleton ? "1" : "0") << "\n";
    t6r9L2 << espSettings[11] << " : " << (Cheat_Private::ESP::Name ? "1" : "0") << "\n";
    t6r9L2 << espSettings[12] << " : " << (Cheat_Private::ESP::Distance ? "1" : "0") << "\n";
    t6r9L2 << espSettings[13] << " : " << (Cheat_Private::ESP::OFFArrow ? "1" : "0") << "\n";
    t6r9L2 << espSettings[14] << " : " << (Cheat_Private::ESP::Operator ? "1" : "0") << "\n";
    t6r9L2 << espSettings[15] << " : " << (Cheat_Private::ESP::Radar ? "1" : "0") << "\n";
    t6r9L2 << espSettings[16] << " : " << (Cheat_Private::ESP::Shield ? "1" : "0") << "\n";
    t6r9L2 << espSettings[17] << " : " << (Cheat_Private::ESP::Level ? "1" : "0") << "\n";
    t6r9L2 << espSettings[18] << " : " << (Cheat_Private::ESP::HandGlow ? "1" : "0") << "\n";
    t6r9L2 << espSettings[19] << " : " << (Cheat_Private::ESP::Weapon ? "1" : "0") << "\n";
    t6r9L2 << espSettings[20] << " : " << (Cheat_Private::ESP::Glow ? "1" : "0") << "\n";
    t6r9L2 << espSettings[21] << " : " << (Cheat_Private::ESP::RainbowGlow ? "1" : "0") << "\n";
    t6r9L2 << espSettings[22] << " : " << (Cheat_Private::ESP::OperatorICON ? "1" : "0") << "\n";
    t6r9L2 << espSettings[23] << " : " << (Cheat_Private::ESP::WeaponGlow ? "1" : "0") << "\n";
    t6r9L2 << espSettings[24] << " : " << (Cheat_Private::ESP::HealthBasedGlow ? "1" : "0") << "\n";
    t6r9L2 << espSettings[25] << " : " << (Cheat_Private::ESP::SernEsp ? "1" : "0") << "\n";
    t6r9L2 << espSettings[26] << " : " << (Cheat_Private::ESP::RemoveTeam ? "1" : "0") << "\n";
    t6r9L2 << espSettings[27] << " : " << (Cheat_Private::ESP::RemoveKnocked ? "1" : "0") << "\n";
    t6r9L2 << espSettings[28] << " : " << (Cheat_Private::ESP::FOVArrows ? "1" : "0") << "\n";

    // Save ESP BoxStyle
    t6r9L2 << espSettings[29] << " : " << Cheat_Private::ESP::BoxStyle << "\n";

    // Save ESP Colors
    t6r9L2 << "Bx1C : " << Cheat_Private::ESP::BoxColor[0] << ", " << Cheat_Private::ESP::BoxColor[1] << ", " << Cheat_Private::ESP::BoxColor[2] << ", " << Cheat_Private::ESP::BoxColor[3] << "\n";
    t6r9L2 << "WnC1 : " << Cheat_Private::ESP::WeaponColor[0] << ", " << Cheat_Private::ESP::WeaponColor[1] << ", " << Cheat_Private::ESP::WeaponColor[2] << ", " << Cheat_Private::ESP::WeaponColor[3] << "\n";
    t6r9L2 << "Dc2D : " << Cheat_Private::ESP::DeathBoxColor[0] << ", " << Cheat_Private::ESP::DeathBoxColor[1] << ", " << Cheat_Private::ESP::DeathBoxColor[2] << ", " << Cheat_Private::ESP::DeathBoxColor[3] << "\n";
    t6r9L2 << "Vc3C : " << Cheat_Private::ESP::VisColor[0] << ", " << Cheat_Private::ESP::VisColor[1] << ", " << Cheat_Private::ESP::VisColor[2] << ", " << Cheat_Private::ESP::VisColor[3] << "\n";
    t6r9L2 << "Nv4N : " << Cheat_Private::ESP::NonVisColor[0] << ", " << Cheat_Private::ESP::NonVisColor[1] << ", " << Cheat_Private::ESP::NonVisColor[2] << ", " << Cheat_Private::ESP::NonVisColor[3] << "\n";
    t6r9L2 << "Sk5S : " << Cheat_Private::ESP::SkeletonColor[0] << ", " << Cheat_Private::ESP::SkeletonColor[1] << ", " << Cheat_Private::ESP::SkeletonColor[2] << ", " << Cheat_Private::ESP::SkeletonColor[3] << "\n";
    t6r9L2 << "Lc6L : " << Cheat_Private::ESP::LevelColor[0] << ", " << Cheat_Private::ESP::LevelColor[1] << ", " << Cheat_Private::ESP::LevelColor[2] << ", " << Cheat_Private::ESP::LevelColor[3] << "\n";
    t6r9L2 << "Nc7C : " << Cheat_Private::ESP::NameColor[0] << ", " << Cheat_Private::ESP::NameColor[1] << ", " << Cheat_Private::ESP::NameColor[2] << ", " << Cheat_Private::ESP::NameColor[3] << "\n";
    t6r9L2 << "Op8O : " << Cheat_Private::ESP::OperatorColor[0] << ", " << Cheat_Private::ESP::OperatorColor[1] << ", " << Cheat_Private::ESP::OperatorColor[2] << ", " << Cheat_Private::ESP::OperatorColor[3] << "\n";
    t6r9L2 << "Cc9C : " << Cheat_Private::ESP::CornerBoxColor[0] << ", " << Cheat_Private::ESP::CornerBoxColor[1] << ", " << Cheat_Private::ESP::CornerBoxColor[2] << ", " << Cheat_Private::ESP::CornerBoxColor[3] << "\n";
    t6r9L2 << "Dc0D : " << Cheat_Private::ESP::DistanceColor[0] << ", " << Cheat_Private::ESP::DistanceColor[1] << ", " << Cheat_Private::ESP::DistanceColor[2] << ", " << Cheat_Private::ESP::DistanceColor[3] << "\n";

    // Save Aimbot settings
 // Save Aimbot settings
    for (int i = 0; i < 10; ++i)
    {
        t6r9L2 << aimbotSettings[i] << " : ";

        // Handle specific types for Aimbot settings
        if (i == 0)  // bool VABot
            t6r9L2 << (Cheat_Private::Aimbot::VABot ? "1" : "0") << "\n";
        else if (i == 1)  // int AimbotKey
            t6r9L2 << Cheat_Private::Aimbot::AimbotKey << "\n";
        else if (i == 2)  // bool FovCircle
            t6r9L2 << (Cheat_Private::Aimbot::FovCircle ? "1" : "0") << "\n";
        else if (i == 3)  // bool Fakefire
            t6r9L2 << (Cheat_Private::Aimbot::Fakefire ? "1" : "0") << "\n";
        else if (i == 4)  // bool RcsControl
            t6r9L2 << (Cheat_Private::Aimbot::RcsControl ? "1" : "0") << "\n";
        else if (i == 5)  // float FovCircleSize
            t6r9L2 << Cheat_Private::Aimbot::FovCircleSize << "\n";
        else if (i == 6)  // bool Snapline
            t6r9L2 << (Cheat_Private::Aimbot::Snapline ? "1" : "0") << "\n";
        else if (i == 7)  // bool PSilent
            t6r9L2 << (Cheat_Private::Aimbot::PSilent ? "1" : "0") << "\n";
        else if (i == 8)  // int TargetBone
            t6r9L2 << Cheat_Private::Aimbot::TargetBone << "\n";
        else if (i == 9)  // float SmoothingAmount
            t6r9L2 << Cheat_Private::Aimbot::SmoothingAmount << "\n";
    }
    // Save Misc settings
    for (int i = 0; i < 10; ++i)
    {
        t6r9L2 << miscSettings[i] << " : ";

        // Handle specific types for Misc settings
        if (i == 0)  // bool Freecam
            t6r9L2 << (Cheat_Private::Misc::Freecam ? "1" : "0") << "\n";
        else if (i == 1)  // bool FakeDuck
            t6r9L2 << (Cheat_Private::Misc::FakeDuck ? "1" : "0") << "\n";
        else if (i == 2)  // int FakeDuckKEY
            t6r9L2 << Cheat_Private::Misc::FakeDuckKEY << "\n";
        else if (i == 3)  // int KafeDuckBIND
            t6r9L2 << Cheat_Private::Misc::KafeDuckBIND << "\n";
        else if (i == 4)  // bool AutoGrapple
            t6r9L2 << (Cheat_Private::Misc::AutoGrapple ? "1" : "0") << "\n";
        else if (i == 5)  // bool SkinChanger
            t6r9L2 << (Cheat_Private::Misc::SkinChanger ? "1" : "0") << "\n";
        else if (i == 6)  // int SkinID
            t6r9L2 << Cheat_Private::Misc::SkinID << "\n";
        else if (i == 7)  // bool Fakefire
            t6r9L2 << (Cheat_Private::Misc::Fakefire ? "1" : "0") << "\n";
        else if (i == 8)  // bool AntiBan
            t6r9L2 << (Cheat_Private::Misc::AntiBan ? "1" : "0") << "\n";
        else if (i == 9)  // bool SuperGlide
            t6r9L2 << (Cheat_Private::Misc::SuperGlide ? "1" : "0") << "\n";
    }

    // Save Aimbot colors
    t6r9L2 << aimbotSettings[10] << " : " << Cheat_Private::Aimbot::FovCircleColor[0] << ", "
        << Cheat_Private::Aimbot::FovCircleColor[1] << ", "
        << Cheat_Private::Aimbot::FovCircleColor[2] << ", "
        << Cheat_Private::Aimbot::FovCircleColor[3] << "\n";

    t6r9L2 << aimbotSettings[11] << " : " << Cheat_Private::Aimbot::SnaplineColor[0] << ", "
        << Cheat_Private::Aimbot::SnaplineColor[1] << ", "
        << Cheat_Private::Aimbot::SnaplineColor[2] << ", "
        << Cheat_Private::Aimbot::SnaplineColor[3] << "\n";


    t6r9L2.close();
    return true;
}


inline bool LoadConfig()
{
    std::string Y9u3X5;
    switch (Cheat_Private::Config::ConfigIndex)
    {
    case 0:
        Y9u3X5 = configNames[0];  // "abc123"
        break;
    case 1:
        Y9u3X5 = configNames[1];  // "def456"
        break;
    case 2:
        Y9u3X5 = configNames[2];  // "ghi789"
        break;
    case 3:
        Y9u3X5 = configNames[3];  // "jkl012"
        break;
    }

    std::filesystem::path o9z2A4 = std::filesystem::current_path();
    std::filesystem::path m1p7K8 = o9z2A4 / Y9u3X5;
    std::ifstream q8k2L5(m1p7K8);

    if (!q8k2L5) {
        return false;
    }

    std::string W2l6J8;
    while (std::getline(q8k2L5, W2l6J8))
    {
        // Load ESP settings
        if (W2l6J8.find(espSettings[0]) != std::string::npos)
            Cheat_Private::ESP::Box = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(espSettings[1]) != std::string::npos)
            Cheat_Private::ESP::Filledbox = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(espSettings[2]) != std::string::npos)
            Cheat_Private::ESP::VisCheck = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(espSettings[3]) != std::string::npos)
            Cheat_Private::ESP::alert = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(espSettings[4]) != std::string::npos)
            Cheat_Private::ESP::CornerBox = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(espSettings[5]) != std::string::npos)
            Cheat_Private::ESP::ArmorICON = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(espSettings[6]) != std::string::npos)
            Cheat_Private::ESP::WeaponICON = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(espSettings[7]) != std::string::npos)
            Cheat_Private::ESP::DeathBox = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(espSettings[8]) != std::string::npos)
            Cheat_Private::ESP::PeterGriffen = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(espSettings[9]) != std::string::npos)
            Cheat_Private::ESP::EKitten = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(espSettings[10]) != std::string::npos)
            Cheat_Private::ESP::Skeleton = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(espSettings[11]) != std::string::npos)
            Cheat_Private::ESP::Name = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(espSettings[12]) != std::string::npos)
            Cheat_Private::ESP::Distance = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(espSettings[13]) != std::string::npos)
            Cheat_Private::ESP::OFFArrow = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(espSettings[14]) != std::string::npos)
            Cheat_Private::ESP::Operator = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(espSettings[15]) != std::string::npos)
            Cheat_Private::ESP::Radar = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(espSettings[16]) != std::string::npos)
            Cheat_Private::ESP::Shield = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(espSettings[17]) != std::string::npos)
            Cheat_Private::ESP::Level = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(espSettings[18]) != std::string::npos)
            Cheat_Private::ESP::HandGlow = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(espSettings[19]) != std::string::npos)
            Cheat_Private::ESP::Weapon = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(espSettings[20]) != std::string::npos)
            Cheat_Private::ESP::Glow = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(espSettings[21]) != std::string::npos)
            Cheat_Private::ESP::RainbowGlow = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(espSettings[22]) != std::string::npos)
            Cheat_Private::ESP::OperatorICON = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(espSettings[23]) != std::string::npos)
            Cheat_Private::ESP::WeaponGlow = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(espSettings[24]) != std::string::npos)
            Cheat_Private::ESP::HealthBasedGlow = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(espSettings[25]) != std::string::npos)
            Cheat_Private::ESP::SernEsp = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(espSettings[26]) != std::string::npos)
            Cheat_Private::ESP::RemoveTeam = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(espSettings[27]) != std::string::npos)
            Cheat_Private::ESP::RemoveKnocked = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(espSettings[28]) != std::string::npos)
            Cheat_Private::ESP::FOVArrows = W2l6J8.find("1") != std::string::npos;

        // Load ESP BoxStyle
        if (W2l6J8.find(espSettings[29]) != std::string::npos)
            Cheat_Private::ESP::BoxStyle = std::stoi(W2l6J8.substr(W2l6J8.find(":") + 2));

        // Load ESP Colors
        if (W2l6J8.find("Bx1C : ") != std::string::npos)
            sscanf(W2l6J8.c_str(), "Bx1C : %f, %f, %f, %f", &Cheat_Private::ESP::BoxColor[0], &Cheat_Private::ESP::BoxColor[1], &Cheat_Private::ESP::BoxColor[2], &Cheat_Private::ESP::BoxColor[3]);

        if (W2l6J8.find("WnC1 : ") != std::string::npos)
            sscanf(W2l6J8.c_str(), "WnC1 : %f, %f, %f, %f", &Cheat_Private::ESP::WeaponColor[0], &Cheat_Private::ESP::WeaponColor[1], &Cheat_Private::ESP::WeaponColor[2], &Cheat_Private::ESP::WeaponColor[3]);

        if (W2l6J8.find("Dc2D : ") != std::string::npos)
            sscanf(W2l6J8.c_str(), "Dc2D : %f, %f, %f, %f", &Cheat_Private::ESP::DeathBoxColor[0], &Cheat_Private::ESP::DeathBoxColor[1], &Cheat_Private::ESP::DeathBoxColor[2], &Cheat_Private::ESP::DeathBoxColor[3]);

        if (W2l6J8.find("Vc3C : ") != std::string::npos)
            sscanf(W2l6J8.c_str(), "Vc3C : %f, %f, %f, %f", &Cheat_Private::ESP::VisColor[0], &Cheat_Private::ESP::VisColor[1], &Cheat_Private::ESP::VisColor[2], &Cheat_Private::ESP::VisColor[3]);

        if (W2l6J8.find("Nv4N : ") != std::string::npos)
            sscanf(W2l6J8.c_str(), "Nv4N : %f, %f, %f, %f", &Cheat_Private::ESP::NonVisColor[0], &Cheat_Private::ESP::NonVisColor[1], &Cheat_Private::ESP::NonVisColor[2], &Cheat_Private::ESP::NonVisColor[3]);

        if (W2l6J8.find("Sk5S : ") != std::string::npos)
            sscanf(W2l6J8.c_str(), "Sk5S : %f, %f, %f, %f", &Cheat_Private::ESP::SkeletonColor[0], &Cheat_Private::ESP::SkeletonColor[1], &Cheat_Private::ESP::SkeletonColor[2], &Cheat_Private::ESP::SkeletonColor[3]);

        if (W2l6J8.find("Lc6L : ") != std::string::npos)
            sscanf(W2l6J8.c_str(), "Lc6L : %f, %f, %f, %f", &Cheat_Private::ESP::LevelColor[0], &Cheat_Private::ESP::LevelColor[1], &Cheat_Private::ESP::LevelColor[2], &Cheat_Private::ESP::LevelColor[3]);

        if (W2l6J8.find("Nc7C : ") != std::string::npos)
            sscanf(W2l6J8.c_str(), "Nc7C : %f, %f, %f, %f", &Cheat_Private::ESP::NameColor[0], &Cheat_Private::ESP::NameColor[1], &Cheat_Private::ESP::NameColor[2], &Cheat_Private::ESP::NameColor[3]);

        if (W2l6J8.find("Op8O : ") != std::string::npos)
            sscanf(W2l6J8.c_str(), "Op8O : %f, %f, %f, %f", &Cheat_Private::ESP::OperatorColor[0], &Cheat_Private::ESP::OperatorColor[1], &Cheat_Private::ESP::OperatorColor[2], &Cheat_Private::ESP::OperatorColor[3]);

        if (W2l6J8.find("Cc9C : ") != std::string::npos)
            sscanf(W2l6J8.c_str(), "Cc9C : %f, %f, %f, %f", &Cheat_Private::ESP::CornerBoxColor[0], &Cheat_Private::ESP::CornerBoxColor[1], &Cheat_Private::ESP::CornerBoxColor[2], &Cheat_Private::ESP::CornerBoxColor[3]);

        if (W2l6J8.find("Dc0D : ") != std::string::npos)
            sscanf(W2l6J8.c_str(), "Dc0D : %f, %f, %f, %f", &Cheat_Private::ESP::DistanceColor[0], &Cheat_Private::ESP::DistanceColor[1], &Cheat_Private::ESP::DistanceColor[2], &Cheat_Private::ESP::DistanceColor[3]);

        // Load Aimbot settings
        if (W2l6J8.find(aimbotSettings[0]) != std::string::npos)
            Cheat_Private::Aimbot::VABot = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(aimbotSettings[1]) != std::string::npos)
            Cheat_Private::Aimbot::AimbotKey = std::stoi(W2l6J8.substr(W2l6J8.find(":") + 2));
        if (W2l6J8.find(aimbotSettings[2]) != std::string::npos)
            Cheat_Private::Aimbot::FovCircle = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(aimbotSettings[3]) != std::string::npos)
            Cheat_Private::Aimbot::Fakefire = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(aimbotSettings[4]) != std::string::npos)
            Cheat_Private::Aimbot::RcsControl = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(aimbotSettings[5]) != std::string::npos)
            Cheat_Private::Aimbot::FovCircleSize = std::stof(W2l6J8.substr(W2l6J8.find(":") + 2));
        if (W2l6J8.find(aimbotSettings[6]) != std::string::npos)
            Cheat_Private::Aimbot::Snapline = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(aimbotSettings[7]) != std::string::npos)
            Cheat_Private::Aimbot::PSilent = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(aimbotSettings[8]) != std::string::npos)
            Cheat_Private::Aimbot::TargetBone = std::stoi(W2l6J8.substr(W2l6J8.find(":") + 2));
        if (W2l6J8.find(aimbotSettings[9]) != std::string::npos)
            Cheat_Private::Aimbot::SmoothingAmount = std::stof(W2l6J8.substr(W2l6J8.find(":") + 2));

        // Load Aimbot Colors
        if (W2l6J8.find("FcC1 : ") != std::string::npos)
            sscanf(W2l6J8.c_str(), "FcC1 : %f, %f, %f, %f", &Cheat_Private::Aimbot::FovCircleColor[0], &Cheat_Private::Aimbot::FovCircleColor[1], &Cheat_Private::Aimbot::FovCircleColor[2], &Cheat_Private::Aimbot::FovCircleColor[3]);

        if (W2l6J8.find("SlC2 : ") != std::string::npos)
            sscanf(W2l6J8.c_str(), "SlC2 : %f, %f, %f, %f", &Cheat_Private::Aimbot::SnaplineColor[0], &Cheat_Private::Aimbot::SnaplineColor[1], &Cheat_Private::Aimbot::SnaplineColor[2], &Cheat_Private::Aimbot::SnaplineColor[3]);

        // Load Misc settings
        if (W2l6J8.find(miscSettings[0]) != std::string::npos)
            Cheat_Private::Misc::Freecam = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(miscSettings[1]) != std::string::npos)
            Cheat_Private::Misc::FakeDuck = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(miscSettings[2]) != std::string::npos)
            Cheat_Private::Misc::FakeDuckKEY = std::stoi(W2l6J8.substr(W2l6J8.find(":") + 2));
        if (W2l6J8.find(miscSettings[3]) != std::string::npos)
            Cheat_Private::Misc::KafeDuckBIND = std::stoi(W2l6J8.substr(W2l6J8.find(":") + 2));
        if (W2l6J8.find(miscSettings[4]) != std::string::npos)
            Cheat_Private::Misc::AutoGrapple = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(miscSettings[5]) != std::string::npos)
            Cheat_Private::Misc::SkinChanger = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(miscSettings[6]) != std::string::npos)
            Cheat_Private::Misc::SkinID = std::stoi(W2l6J8.substr(W2l6J8.find(":") + 2));
        if (W2l6J8.find(miscSettings[7]) != std::string::npos)
            Cheat_Private::Misc::Fakefire = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(miscSettings[8]) != std::string::npos)
            Cheat_Private::Misc::AntiBan = W2l6J8.find("1") != std::string::npos;
        if (W2l6J8.find(miscSettings[9]) != std::string::npos)
            Cheat_Private::Misc::SuperGlide = W2l6J8.find("1") != std::string::npos;
    }

    q8k2L5.close();
    return true;
}
