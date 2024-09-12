#include "FastFire.hpp"

inline float PreviousKillTime = 0.0f;
struct KillInfo {
    std::string name;
    std::chrono::steady_clock::time_point expirationTime;
};
inline std::vector<KillInfo> killList;

inline void DrawKillText(const std::vector<KillInfo>& kills) {
    float startX = 10.0f;
    float startY = 150;
    float offsetY = 20.0f; 
    //goofy ass feature 
    for (size_t i = 0; i < kills.size(); ++i) {
        const KillInfo& kill = kills[i];
        std::string text = "Killed " + kill.name;
       
        Draw::esp->draw_text_outline_font(startX, startY + i * offsetY, ImColor(255, 255, 255, 255), text.c_str(), 1.f);
    }
}
inline void UpdateKills() {
    auto currentTime = std::chrono::steady_clock::now();
    killList.erase(std::remove_if(killList.begin(), killList.end(),
        [currentTime](const KillInfo& kill) {
            return currentTime > kill.expirationTime;
        }),
        killList.end());
}
inline void HandleKillEvent(float KillTime, const std::string& EntityName) {
    if (KillTime > PreviousKillTime) {
        PlaySound("Hitsound.wav", GetModuleHandleA(NULL), SND_FILENAME | SND_ASYNC);

        KillInfo newKill;
        newKill.name = EntityName;
        newKill.expirationTime = std::chrono::steady_clock::now() + std::chrono::seconds(5);
        killList.push_back(newKill);

        PreviousKillTime = KillTime;
    }
}