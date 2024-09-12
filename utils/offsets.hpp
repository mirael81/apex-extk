#include <Windows.h>
#include <iostream>
#
#define Off constexpr uint64_t
#define StaticAddress(name,value) inline constexpr uint64_t m_##name = value
//v3.0.75.30


namespace Offsets {
    namespace Misc {
        // Existing constants
        StaticAddress(LocalPlayer, 0x23e91f8);  // No change
        StaticAddress(m_hViewModels, 0x2d98);  // No change
        StaticAddress(m_armsModelIndex, 0x497c);  // No change
        StaticAddress(GlobalVars, 0x17eaf90);   // Address swapped with 0x17e8830
        StaticAddress(EntityList, 0x1f15f88);   // No change // sig 0F 11 0D 3E 7B 6F 01
        StaticAddress(InputSystem, 0x18765c0);  // Address swapped with 0x1897c80
        StaticAddress(NameList, 0xd388450);     // Address swapped with 0xd2e3460
        StaticAddress(m_customScriptInt, 0x1568);     // Address swapped with 0xd2e3460
        StaticAddress(ClientState, 0x17eb2d0);  // Address swapped with 0x17e9b60
        StaticAddress(SignonState, 0x17eb37c);  // Address swapped with 0x17e9c0c
        StaticAddress(LevelName, 0x17eb494);    // Address swapped with 0x17c5120
        StaticAddress(ViewRender, 0x769b558);   // Address swapped with 0x7543e00
        StaticAddress(ViewMatrix, 0x11a350);    // No change
        StaticAddress(Bones, 0x0db0 + 0x48);    // No change m_nForceBone=0x0db0 +0x48
        StaticAddress(PrimaryWeapon, 0x1944);    // No change m_nForceBone=0x0db0 +0x48
        StaticAddress(lastVisibleTime, 0x19a0);    // No change m_nForceBone=0x0db0 +0x48
        StaticAddress(WorldTime, 0x2088);    // No change m_nForceBone=0x0db0 +0x48
        StaticAddress(LastKillTime, 0x35dc);    // No change m_nForceBone=0x0db0 +0x48
        StaticAddress(GameWorld, 0x17ec544);    // No change m_nForceBone=0x0db0 +0x48
      //  float LastKillTime = Read<float>((uintptr_t)localPlayer + 0x35dc);

        // New constants to be added
        StaticAddress(OFFSET_HIGHLIGHTSETTINGS, 0xb13c620);
        StaticAddress(OFFSET_HIGHLIGHTSERVERACTIVESTATES, 0x298);
        StaticAddress(OFFSET_HIGHLIGHTCURRENTCONID, 0x28C);
        StaticAddress(OFFSET_HIGHLIGHTVISIBILITYTYPE, 0x26c);
        StaticAddress(HIGHLIGHT_TYPE_SIZE, 0x34);
        StaticAddress(OFFSET_GLOW_COLOR, 0x1d0 + 0x30);
        StaticAddress(OFFSET_GLOW_TYPE, 0x29c);
        StaticAddress(OFFSET_GLOW_FIX, 0x278);
        StaticAddress(GLOW_DISTANCE, 0x264);
              // No change

    }
    namespace C_BaseEntity {
        StaticAddress(m_ModelName, 0x0030);
        StaticAddress(m_fFlags, 0x00c8);
        StaticAddress(m_angAbsRotation, 0x0164);
        StaticAddress(m_vecAbsOrigin, 0x017c);
        StaticAddress(m_vecPrevAbsOrigin, 0x02f4);
        StaticAddress(m_flGravity, 0x0300);
        StaticAddress(m_rgflCoordinateFrame, 0x07b0);

    }
    namespace DT_BaseEntity {
        StaticAddress(moveparent, 0x001c);
        StaticAddress(m_parentAttachment, 0x0020);
        StaticAddress(m_fEffects, 0x0040);
        StaticAddress(m_usableType, 0x0044);
        StaticAddress(m_cellX, 0x0048);
        StaticAddress(m_cellY, 0x004c);
        StaticAddress(m_cellZ, 0x0050);
        StaticAddress(m_localOrigin, 0x0054);
        StaticAddress(m_nModelIndex, 0x0060);
        StaticAddress(m_clrRender, 0x0080);
        StaticAddress(m_clIntensity, 0x0084);
        StaticAddress(m_bossPlayer, 0x0154);
        StaticAddress(m_shieldHealth, 0x01a0);
        StaticAddress(m_Shield_type, 0x46c4);
        StaticAddress(m_shieldHealthMax, 0x01a4);
        StaticAddress(m_wantsScopeHighlight, 0x02c4);
        StaticAddress(m_networkedFlags, 0x02c8);
        StaticAddress(m_ignoreParentRotation, 0x02d0);
        StaticAddress(m_visibilityFlags, 0x0320);
        StaticAddress(m_iTeamNum, 0x0338);
        StaticAddress(m_teamMemberIndex, 0x0330);
        StaticAddress(m_squadID, 0x0344);
        StaticAddress(m_grade, 0x0338);
        StaticAddress(m_ignorePredictedTriggerFlags, 0x033c);
        StaticAddress(m_passThroughFlags, 0x0344);
        StaticAddress(m_passThroughThickness, 0x0348);
        StaticAddress(m_passThroughDirection, 0x034c);
        StaticAddress(m_bIsSoundCodeControllerValueSet, 0x0364);
        StaticAddress(m_flSoundCodeControllerValue, 0x0368);
        StaticAddress(m_localAngles, 0x0378);
        StaticAddress(m_hOwnerEntity, 0x038c);
        StaticAddress(m_bRenderWithViewModels, 0x0390);
        StaticAddress(m_nRenderFX, 0x0391);
        StaticAddress(m_nRenderMode, 0x03a1);
        StaticAddress(m_Collision, 0x03a8);
        StaticAddress(m_CollisionGroup, 0x0428);
        StaticAddress(m_contents, 0x042c);
        StaticAddress(m_collideWithOwner, 0x0430);
        StaticAddress(m_iSignifierName, 0x0478);
        StaticAddress(m_iName, 0x0471);
        StaticAddress(m_scriptNameIndex, 0x0578);
        StaticAddress(m_instanceNameIndex, 0x057c);
        StaticAddress(m_holdUsePrompt, 0x0600);
        StaticAddress(m_pressUsePrompt, 0x0608);
        StaticAddress(m_phaseShiftFlags, 0x06a0);
        StaticAddress(m_baseTakeDamage, 0x06a4);
        StaticAddress(m_invulnerableToDamageCount, 0x06a8);
        StaticAddress(m_attachmentLerpStartTime, 0x071c);
        StaticAddress(m_attachmentLerpEndTime, 0x0720);
        StaticAddress(m_attachmentLerpStartOrigin, 0x0724);
        StaticAddress(m_attachmentLerpStartAngles, 0x0730);
        StaticAddress(m_parentAttachmentModel, 0x0740);
        StaticAddress(m_fadeDist, 0x074c);
        StaticAddress(m_dissolveEffectEntityHandle, 0x07f4);
        StaticAddress(m_usablePriority, 0x0808);
        StaticAddress(m_usableDistanceOverride, 0x080c);
        StaticAddress(m_usableFOV, 0x0810);
        StaticAddress(m_usePromptSize, 0x0814);
        StaticAddress(m_spottedByTeams, 0x0828);
        StaticAddress(m_firstChildEntityLink, 0x0920);
        StaticAddress(m_firstParentEntityLink, 0x0924);
        StaticAddress(m_realmsBitMask, 0x0928);

    }
    namespace DT_Player
    {
        Off m_vecAbsOrigin = 0x0004;
        Off isLocalOriginLocal = 0x0010;
        Off m_fFlags = 0x00c8;
        Off m_hGroundEntity = 0x0314;
        Off m_iHealth = 0x0328;
        Off m_flMaxspeed = 0x031c;
        Off m_jumpPadDebounceExpireTime = 0x0340;
        Off m_iMaxHealth = 0x0460;
        Off m_lifeState = 0x0680;
        Off m_overlayEventParity = 0x1661;
        Off m_inventory = 0x18c8;
        Off m_selectedOffhands = 0x1946;
        Off m_selectedOffhandsPendingHybridAction = 0x1949;
        Off m_titanSoul = 0x19c4;
        Off m_bZooming = 0x1bd1;
        Off m_zoomToggleOnStartTime = 0x1bd4;
        Off m_zoomBaseFrac = 0x1bd8;
        Off m_zoomBaseTime = 0x1bdc;
        Off m_zoomFullStartTime = 0x1be0;
        Off m_currentFramePlayer = 0x2088;
        Off pl = 0x24b0;
        Off m_ammoPoolCapacity = 0x2534;
        Off m_hasBadReputation = 0x2538;
        Off m_hardware = 0x2540;
        Off m_unspoofedHardware = 0x2541;
        Off m_platformUserId = 0x2548;
        Off m_progressionUserId = 0x2550;
        Off m_unSpoofedPlatformUserId = 0x2558;
        Off m_EadpUserId = 0x2560;
        Off m_crossPlayChat = 0x2568;
        Off m_crossPlayChatFriends = 0x2569;
        Off m_crossProgressionMigrated = 0x256a;
        Off m_laserSightColorCustomized = 0x256b;
        Off m_laserSightColor = 0x256c;
        Off m_classModsActive = 0x2578;
        Off m_passives = 0x26b0;
        Off m_bleedoutState = 0x26e0;
        Off m_bleedoutStartTime = 0x26e4;
        Off m_statusEffectsTimedPlayerNV = 0x26e8;
        Off m_statusEffectsEndlessPlayerNV = 0x27d8;
        Off m_damageComboLatestUpdateTime = 0x289c;
        Off m_damageComboStartHealth = 0x28a0;
        Off m_gestureSequences = 0x28a4;
        Off m_gestureStartTimes = 0x28b4;
        Off m_gestureBlendInDuration = 0x28d4;
        Off m_gestureBlendOutDuration = 0x28f4;
        Off m_gestureFadeOutStartTime = 0x2914;
        Off m_gestureFadeOutDuration = 0x2934;
        Off m_gestureAutoKillBitfield = 0x2954;
        Off m_autoSprintForced = 0x2998;
        Off m_fIsSprinting = 0x299c;
        Off m_playerSettingForStickySprintForward = 0x299e;
        Off m_playerSettingForHoldToSprint = 0x299f;
        Off m_lastSprintPressTime = 0x29a0;
        Off m_stickySprintForwardEnableTime = 0x29a4;
        Off m_stickySprintForwardDisableTime = 0x29a8;
        Off m_damageImpulseNoDecelEndTime = 0x29c0;
        Off m_playerVehicles = 0x29cc;
        Off m_playerVehicleCount = 0x29d4;
        Off m_playerVehicleDriven = 0x29d8;
        Off m_playerVehicleUseTime = 0x29dc;
        Off m_duckState = 0x29e0;
        Off m_leanState = 0x29e4;
        Off m_canStand = 0x29e9;
        Off m_StandHullMin = 0x29ec;
        Off m_StandHullMax = 0x29f8;
        Off m_DuckHullMin = 0x2a04;
        Off m_DuckHullMax = 0x2a10;
        Off m_entitySyncingWithMe = 0x2a1c;
        Off m_upDir = 0x2a20;
        Off m_traversalState = 0x2aa4;
        Off m_traversalType = 0x2aa8;
        Off m_traversalForwardDir = 0x2ad4;
        Off m_traversalRefPos = 0x2ae0;
        Off m_traversalYawDelta = 0x2b0c;
        Off m_traversalYawPoseParameter = 0x2b10;
        Off m_wallClimbSetUp = 0x2b28;
        Off m_wallHanging = 0x2b29;
        Off m_grapple = 0x2c40;
        Off m_grappleActive = 0x2cd0;
        Off m_turret = 0x2d14;
        Off m_hViewModels = 0x2d18;
        Off m_viewOffEntity = 0x2534 - 0x14;
        Off m_animViewEntity = 0x2d68;
        Off m_activeZipline = 0x2e58;
        Off m_ziplineValid3pWeaponLayerAnim = 0x2e64;
        Off m_ziplineState = 0x2e68;
        Off m_ziplineGrenadeBeginStationEntity = 0x2f04;
        Off m_ziplineGrenadeBeginStationAttachmentId = 0x2f08;
        Off m_shadowShieldActive = 0x2f30;
        Off m_tempShieldHealth = 0x2f34;
        Off m_extraShieldHealth = 0x2f38;
        Off m_extraShieldTier = 0x2f3c;
        Off m_isPerformingBoostAction = 0x2f5e;
        Off m_lastJumpPadTouched = 0x3058;
        Off m_launchCount = 0x3060;
        Off m_launcherAirControlActive = 0x3064;
        Off m_melee = 0x3190;
        Off m_useCredit = 0x31c8;
        Off m_playerFlags = 0x31d8;
        Off m_hasMic = 0x31e0;
        Off m_inPartyChat = 0x31e1;
        Off m_communicationsAutoBlocked = 0x31e2;
        Off m_playerMoveSpeedScale = 0x31e4;
        Off m_bShouldDrawPlayerWhileUsingViewEntity = 0x3430;
        Off m_iSpawnParity = 0x349c;
        Off m_flDeathTime = 0x3560;
        Off m_ragdollCreationOrigin = 0x3564;
        Off m_ragdollCreationYaw = 0x3570;
        Off m_lastDodgeTime = 0x35b0;
        Off m_timeJetpackHeightActivateCheckPassed = 0x35d8;
        Off m_grappleHook = 0x3678;
        Off m_petTitan = 0x367c;
        Off m_xp = 0x3724;
        Off m_skill_mu = 0x36ac;
        Off m_bHasMatchAdminRole = 0x36b0;
        Off m_ubEFNoInterpParity = 0x3ff8;
        Off m_hColorCorrectionCtrl = 0x3ffc;
        Off m_title = 0x4020;
        Off m_Shared = 0x4350;
        Off m_pilotClassIndex = 0x43a4;
        Off m_playerScriptNetDataGlobal = 0x4630;
        Off m_helmetType = 0x4638;
        Off m_armorType = 0x463c;
        Off m_controllerModeActive = 0x4644;
        Off m_skydiveForwardPoseValueTarget = 0x4668;
        Off m_skydiveSidePoseValueTarget = 0x4674;
        Off m_skydiveState = 0x469c;
        Off m_skydiveDiveAngle = 0x46b4;
        Off m_skydiveIsDiving = 0x46b8;
        Off m_skydiveSpeed = 0x46bc;
        Off m_skydiveStrafeAngle = 0x46c0;
        Off m_skydivePlayerPitch = 0x46d4;
        Off m_skydivePlayerYaw = 0x46d8;
        Off m_skydiveFromSkywardLaunch = 0x4715;
        Off m_skydiveScriptInputOverride = 0x4718;
        Off m_skydiveContraintPostion = 0x471c;
        Off m_skydiveContraintRadius = 0x4728;
        Off m_skywardLaunchState = 0x472c;
        Off m_skywardLaunchSlowStartTime = 0x4740;
        Off m_skywardLaunchSlowEndTime = 0x4744;
        Off m_skywardLaunchFastEndTime = 0x4748;
        Off m_skywardLaunchEndTime = 0x4750;
        Off m_skywardLaunchSlowSpeed = 0x4758;
        Off m_skywardLaunchFastSpeed = 0x475c;
        Off m_skywardOff = 0x4760;
        Off m_skywardLaunchInterrupted = 0x4770;
        Off m_skywardLaunchFollowing = 0x4771;
        Off m_skywardObstacleAvoidanceEndPos = 0x4774;
        Off m_armoredLeapAirPos = 0x4784;
        Off m_armoredLeapEndPos = 0x4790;
        Off m_armoredLeapType = 0x479c;
        Off m_armoredLeapPhase = 0x47a0;
        Off m_armoredLeapStartTime = 0x47a4;
        Off m_dragReviveState = 0x4810;
        Off m_dragReviveOutroStartTime = 0x4814;
        Off m_reviveTarget = 0x4818;
    }
    namespace CollisionProperty {
        Off m_vecMins = 0x0010;
        Off m_vecMaxs = 0x001c;
        Off m_usSolidFlags = 0x0028;
        Off m_nSolidType = 0x002c;
        Off m_triggerBloat = 0x002d;
        Off m_collisionDetailLevel = 0x002e;
        Off m_nSurroundType = 0x003c;
        Off m_vecSpecifiedSurroundingMins = 0x0048;
        Off m_vecSpecifiedSurroundingMaxs = 0x0054;
    }
    namespace DT_Player_ViewOffEntityData
    {
        Off viewOffEntityHandle = 0x0008;
        Off lerpInDuration = 0x000c;
        Off lerpOutDuration = 0x0010;
        Off stabilizePlayerEyeAngles = 0x0014;
    }
    namespace DT_Player_AnimViewEntityData
    {
        Off animViewEntityAngleLerpInDuration = 0x0004;
        Off animViewEntityOriginLerpInDuration = 0x0008;
        Off animViewEntityLerpOutDuration = 0x000c;
        Off animViewEntityStabilizePlayerEyeAngles = 0x0010;
        Off animViewEntityThirdPersonCameraParity = 0x0014;
        Off animViewEntityThirdPersonCameraAttachment = 0x0018;
        Off animViewEntityNumThirdPersonCameraAttachments = 0x0020;
        Off animViewEntityThirdPersonCameraVisibilityChecks = 0x0024;
        Off animViewEntityDrawPlayer = 0x0025;
        Off fovTarget = 0x0028;
        Off fovSmoothTime = 0x002c;
        Off animViewEntityParity = 0x0038;
    }
    namespace DT_WeaponInventory
    {
        Off weapons = 0x0008;
        Off offhandWeapons = 0x0038;
        Off activeWeapons = 0x0064;
    }
    namespace DT_Player_LocalData
    {
        Off bcc_localdata = 0x0000;
        Off m_weaponGettingSwitchedOut = 0x0008;
        Off m_showActiveWeapon3p = 0x0010;
        Off m_vecViewOff_x = 0x0034;
        Off m_vecViewOff_y = 0x0038;
        Off m_vecViewOff_z = 0x003c;
        Off m_cloakEndTime = 0x01cc;
        Off m_cloakFadeInEndTime = 0x01d0;
        Off m_cloakFadeOutStartTime = 0x01d4;
        Off m_cloakFadeInDuration = 0x01d8;
        Off m_cloakFlickerAmount = 0x01dc;
        Off m_cloakFlickerEndTime = 0x01e0;
        Off m_networkedFlags = 0x02c8;
        Off m_deathVelocity = 0x0350;
        Off m_minimapData = 0x0848;
        Off m_nameVisibilityFlags = 0x0898;
        Off m_bIsPlayerOverheating = 0x1890;
        Off m_playerOverheatValue = 0x1894;
        Off m_timeLastGeneratedPlayerOverheat = 0x1898;
        Off m_lastFiredTime = 0x18a0;
        Off m_lastFiredWeapon = 0x18a4;
        Off m_raiseFromMeleeEndTime = 0x18a8;
        Off m_sharedEnergyCount = 0x18ac;
        Off m_sharedEnergyTotal = 0x18b0;
        Off m_sharedEnergyLockoutThreshold = 0x18b4;
        Off m_lastSharedEnergyRegenTime = 0x18b8;
        Off m_sharedEnergyRegenRate = 0x18bc;
        Off m_sharedEnergyRegenDelay = 0x18c0;
        Off m_lastSharedEnergyTakeTime = 0x18c4;
        Off m_selectedWeapons = 0x1930;
        Off m_latestPrimaryWeapons = 0x1934;
        Off m_latestPrimaryWeaponsIndexZeroOrOne = 0x193c;
        Off m_latestNonOffhandWeapons = 0x1944;
        Off m_lastCycleSlot = 0x194c;
        Off m_weaponPermission = 0x1954;
        Off m_weaponDelayEnableTime = 0x1958;
        Off m_weaponDisabledInScript = 0x195c;
        Off m_weaponDisabledFlags = 0x1972;
        Off m_weaponInventorySlotLockedFlags = 0x1974;
        Off m_weaponTypeDisabledFlags = 0x1978;
        Off m_weaponTypeDisabledRefCount = 0x197c;
        Off m_allowHudSelectionWhileWeaponsDisabled = 0x1986;
        Off m_weaponAmmoRegenDisabled = 0x1987;
        Off m_weaponAmmoRegenDisabledRefCount = 0x1988;
        Off m_akimboState = 0x198c;
        Off m_akimboShouldAltFire = 0x198d;
        Off m_hudInfo_visibilityTestAlwaysPasses = 0x198e;
        Off m_contextAction = 0x19a0;
        Off m_phaseShiftType = 0x19cc;
        Off m_phaseShiftTimeStart = 0x19d0;
        Off m_phaseShiftTimeEnd = 0x19d4;
        Off m_targetInfoPingValue = 0x1b60;
    }
    namespace DT_PointCamera
    {
        Off m_FOV = 0x09c0;
        Off m_bFogEnable = 0x09e8;
        Off m_bActive = 0x09e9;
    }
}