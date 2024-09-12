#pragma once
//#include "../Exploit Driver/SuperDriver.h"
#include "../interface.h"
#include "../utils/xor.hpp"

#define RESET   _("\033[0m")
#define BLACK   _("\033[30m")     /* Black */
#define RED      _("\033[31m")     /* Red */
#define GREEN    _("\033[32m")    /* Green */
#define YELLOW   _("\033[33m")   /* Yellow */
#define BLUE     _("\033[34m")  /* Blue */
#define MAGENTA  _("\033[35m") /* Magenta */
#define CYAN     _("\033[36m")/* Cyan */
#define WHITE    _("\033[37m")/* White */
#define BOLDBLACK    _("\033[1m\033[30m")      /* Bold Black */
#define BOLDRED      _("\033[1m\033[31m")      /* Bold Red */
#define BOLDGREEN    _("\033[1m\033[32m")      /* Bold Green */
#define BOLDYELLOW   _("\033[1m\033[33m")      /* Bold Yellow */
#define BOLDBLUE     _("\033[1m\033[34m")      /* Bold Blue */
#define BOLDMAGENTA  _("\033[1m\033[35m")      /* Bold Magenta */
#define BOLDCYAN     _("\033[1m\033[36m")      /* Bold Cyan */
#define BOLDWHITE    _("\033[1m\033[37m")      /* Bold White */

#define LOG(arg) std::cout << BOLDWHITE << "[" << RED << "Apex" << BOLDWHITE << "] " << BOLDWHITE << arg << "\n";
#define LOGF(arg) std::cout << BOLDWHITE << "[" << CYAN << "XEX" << BOLDWHITE << "] " << BOLDWHITE << arg << "\n";
#define LOG_DEBUG(arg) std::cout << RED << "[DEBUG] " << BOLDWHITE << arg << "\n";

namespace WeaponIDs {
    // Light Weapons
    inline int P2020 = 112;
    inline int RE45 = 85;
    inline int ALTERNATOR = 84;
    inline int R99 = 111;
    inline  int R301 = 0;
    inline  int SPITFIRE = 113;
    inline  int G7_SCOUT = 95;

    // Heavy Weapons
    inline  int FLATLINE = 94;
    inline  int HEMLOCK = 96;
    inline   int PROWLER = 107;
    inline  int REPEATER_3030 = 118;
    inline   int RAMPAGE = 6;
    inline   int CAR = 119;

    // Energy Weapons
    inline  int HAVOC = 91;
    inline   int DEVOTION = 89;
    inline  int LSTAR = 99;
    inline   int TRIPLE_TAKE = 114;
    inline   int VOLT = 117;
    inline   int NEMESIS = 120;

    // Shotguns
    inline int MOZAMBIQUE = 102;
    inline  int PEACEKEEPER = 109;
    inline  int MASTIFF = 101;
    inline int EVA8 = 92;

    // Sniper Rifles
    inline   int LONGBOW = 90;
    inline   int CHARGE_RIFLE = 87;
    inline   int SENTINEL = 1;

    // Legendary Weapons
    inline   int WINGMAN = 115;
    inline   int BOCEK = 2;
    inline  int KRABER = 98;
    inline   int KNIFE = 176;
};