/*
* This file is part of the Pandaria 5.4.8 Project. See THANKS file for Copyright information
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "BattlePetAbilityEffect.h"
#include "DBCStores.h"
#include "BattlePet.h"
#include "PetBattle.h"
#include "DB2Stores.h"

struct BattlePetAbilityEffectHandler
{
    void (BattlePetAbilityEffect::*Handle)();
    PetBattleAbilityTarget Target;
};

static BattlePetAbilityEffectHandler Handlers[PET_BATTLE_TOTAL_ABILITY_EFFECTS] =
{
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 022 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 023 */ { &BattlePetAbilityEffect::HandleHeal,                     PET_BATTLE_ABILITY_TARGET_CASTER },
    /* Effect 024 */ { &BattlePetAbilityEffect::HandleDamage,                   PET_BATTLE_ABILITY_TARGET_TARGET },
    /* Effect 025 */ { &BattlePetAbilityEffect::HandleCatch,                    PET_BATTLE_ABILITY_TARGET_TARGET },
    /* Effect 026 */ { &BattlePetAbilityEffect::HandlePositiveAura,             PET_BATTLE_ABILITY_TARGET_CASTER },
    /* Effect 027 */ { &BattlePetAbilityEffect::HandleRampingDamage,            PET_BATTLE_ABILITY_TARGET_TARGET },
    /* Effect 028 */ { &BattlePetAbilityEffect::HandleCancellableAura,          PET_BATTLE_ABILITY_TARGET_CASTER   },
    /* Effect 029 */ { &BattlePetAbilityEffect::HandleStateDamage,              PET_BATTLE_ABILITY_TARGET_TARGET   },
    /* Effect 030 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 031 */ { &BattlePetAbilityEffect::HandleSetState,                 PET_BATTLE_ABILITY_TARGET_CASTER },
    /* Effect 032 */ { &BattlePetAbilityEffect::HandleHealPctDealt,             PET_BATTLE_ABILITY_TARGET_CASTER },
    /* Effect 033 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 043 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 044 */ { &BattlePetAbilityEffect::HandleHealLastHitTaken,         PET_BATTLE_ABILITY_TARGET_CASTER },
    /* Effect 045 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 049 */ { &BattlePetAbilityEffect::HandleRemoveAura,               PET_BATTLE_ABILITY_TARGET_CASTER   },
    /* Effect 050 */ { &BattlePetAbilityEffect::HandleNegativeAura,             PET_BATTLE_ABILITY_TARGET_TARGET },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 052 */ { &BattlePetAbilityEffect::HandleControlAura,              PET_BATTLE_ABILITY_TARGET_TARGET   },
    /* Effect 053 */ { &BattlePetAbilityEffect::HandleHealPercent,              PET_BATTLE_ABILITY_TARGET_CASTER   },
    /* Effect 054 */ { &BattlePetAbilityEffect::HandlePeriodicTrigger,          PET_BATTLE_ABILITY_TARGET_TARGET },
    /* Effect 055 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 056 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 057 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 058 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 059 */ { &BattlePetAbilityEffect::HandleWitchingDamage,           PET_BATTLE_ABILITY_TARGET_TARGET   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 061 */ { &BattlePetAbilityEffect::HandleHealCasterPercentNotState,PET_BATTLE_ABILITY_TARGET_CASTER_TEAM_UNCONDITIONAL   },
    /* Effect 062 */ { &BattlePetAbilityEffect::HandleDamagePercent,            PET_BATTLE_ABILITY_TARGET_TARGET },
    /* Effect 063 */ { &BattlePetAbilityEffect::HandlePeriodicPositiveTrigger,  PET_BATTLE_ABILITY_TARGET_CASTER },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 065 */ { &BattlePetAbilityEffect::HandleDamageStateBonus,         PET_BATTLE_ABILITY_TARGET_TARGET },
    /* Effect 066 */ { &BattlePetAbilityEffect::HandleDamageRuthless,           PET_BATTLE_ABILITY_TARGET_TARGET   },
    /* Effect 067 */ { &BattlePetAbilityEffect::HandleEqualizeLife,             PET_BATTLE_ABILITY_TARGET_TARGET   },
    /* Effect 068 */ { &BattlePetAbilityEffect::HandleDamageCasterPercent,      PET_BATTLE_ABILITY_TARGET_CASTER },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 072 */ { &BattlePetAbilityEffect::HandleHealToggleAura,           PET_BATTLE_ABILITY_TARGET_CASTER   },
    /* Effect 073 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 074 */ { &BattlePetAbilityEffect::HandleInitialization,           PET_BATTLE_ABILITY_TARGET_CASTER  },
    /* Effect 075 */ { &BattlePetAbilityEffect::HandleDamageToggleAura,         PET_BATTLE_ABILITY_TARGET_TARGET   },
    /* Effect 076 */ { &BattlePetAbilityEffect::HandleDamageToggleAura,         PET_BATTLE_ABILITY_TARGET_TARGET },
    /* Effect 077 */ { &BattlePetAbilityEffect::HandleDamageToggleAura,         PET_BATTLE_ABILITY_TARGET_TARGET   },
    /* Effect 078 */ { &BattlePetAbilityEffect::HandleHealStateToggleAura,      PET_BATTLE_ABILITY_TARGET_CASTER   },
    /* Effect 079 */ { &BattlePetAbilityEffect::HandleModState,                 PET_BATTLE_ABILITY_TARGET_CASTER   },
    /* Effect 080 */ { &BattlePetAbilityEffect::HandleWeatherAura,              PET_BATTLE_ABILITY_TARGET_ALL    },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 085 */ { &BattlePetAbilityEffect::HandleResetState,               PET_BATTLE_ABILITY_TARGET_ALL    },
    /* Effect 086 */ { &BattlePetAbilityEffect::HandleDamageAuraToggleAura,     PET_BATTLE_ABILITY_TARGET_TARGET   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 096 */ { &BattlePetAbilityEffect::HandleDamageHitState,           PET_BATTLE_ABILITY_TARGET_TARGET },
    /* Effect 097 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 099 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 100 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 103 */ { &BattlePetAbilityEffect::HandleExtraAttackFirst,         PET_BATTLE_ABILITY_TARGET_TARGET },
    /* Effect 104 */ { &BattlePetAbilityEffect::HandleHealState,                PET_BATTLE_ABILITY_TARGET_TARGET },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 107 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 108 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 111 */ { &BattlePetAbilityEffect::HandleResurect,                 PET_BATTLE_ABILITY_TARGET_CASTER },
    /* Effect 112 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 116 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 117 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 121 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 122 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 123 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 124 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 125 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 128 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 129 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 131 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 132 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 133 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 134 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 135 */ { &BattlePetAbilityEffect::HandleKill,                     PET_BATTLE_ABILITY_TARGET_CASTER   },
    /* Effect 136 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 137 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 138 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 139 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 140 */ { &BattlePetAbilityEffect::HandleResetAuraDuration,        PET_BATTLE_ABILITY_TARGET_TARGET   },
    /* Effect 141 */ { &BattlePetAbilityEffect::HandleSplittedDamage,           PET_BATTLE_ABILITY_TARGET_TARGET_TEAM },
    /* Effect 142 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 143 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 144 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 145 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 147 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 149 */ { &BattlePetAbilityEffect::HandleDamageNonLethal,          PET_BATTLE_ABILITY_TARGET_TARGET },
    /* Effect 150 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 156 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 157 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 158 */ { &BattlePetAbilityEffect::HandleStopChainFailure,         PET_BATTLE_ABILITY_TARGET_CASTER },
    /* Effect 159 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 160 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 164 */ { &BattlePetAbilityEffect::HandleExtraAttack,              PET_BATTLE_ABILITY_TARGET_TARGET },
    /* Effect 165 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 168 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 169 */ { &BattlePetAbilityEffect::HandleStateDamage,              PET_BATTLE_ABILITY_TARGET_HEAD   },
    /* Effect 170 */ { &BattlePetAbilityEffect::HandleWeatherDamage,            PET_BATTLE_ABILITY_TARGET_TARGET },
    /* Effect 171 */ { &BattlePetAbilityEffect::HandleHealOnSpecificWeather,    PET_BATTLE_ABILITY_TARGET_CASTER },
    /* Effect 172 */ { &BattlePetAbilityEffect::HandleAuraCondAccuracyState,    PET_BATTLE_ABILITY_TARGET_TARGET },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 177 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 178 */ { &BattlePetAbilityEffect::HandlePowerlessAura,            PET_BATTLE_ABILITY_TARGET_TARGET },
    /* Effect 179 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 194 */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /*   UNUSED   */ { &BattlePetAbilityEffect::HandleNull,                     PET_BATTLE_ABILITY_TARGET_NONE   },
    /* Effect 197 */ { &BattlePetAbilityEffect::HandleDamagePercentTaken,       PET_BATTLE_ABILITY_TARGET_TARGET }
};

void BattlePetAbilityEffect::SetAbilityInfo(uint32 ability, BattlePetAbilityEffectEntry const* effectEntry, uint8 family)
{
    // ability information
    m_abilityId     = ability;
    m_effectEntry   = effectEntry;
    m_abilityFamily = family;
}

bool BattlePetAbilityEffect::Execute()
{
    if (!Handlers[m_effectEntry->EffectProperty].Handle)
    {
        TC_LOG_ERROR("BP", "Ability effect not handled: %u", m_effectEntry->EffectProperty);
        return false;
    }

    if (m_targets.empty())
    {
        /*// ----------------------------------------------------------------------------------
        std::stringstream ss;
        ss << "DEBUG: Ability " << m_abilityId << " (";
        ss << sBattlePetAbilityStore.LookupEntry(m_abilityId)->Name << ") has unhandled effect ";
        ss << m_effectEntry->EffectProperty << "!";

        ChatHandler(m_petBattle->Teams[PET_BATTLE_CHALLANGER_TEAM]->GetOwner()->GetSession()).PSendSysMessage(ss.str().c_str());
        // ----------------------------------------------------------------------------------*/

        return false;
    }

    // execute handler on targets
    for (auto&& target : m_targets)
    {
        m_target = target;

        if (!m_target->IsTargetable())
            m_flags |= PET_BATTLE_EFFECT_FLAG_MISS;

        (this->*Handlers[m_effectEntry->EffectProperty].Handle)();
    }

    return true;
}

BattlePet* BattlePetAbilityEffect::GetActiveOpponent()
{
    PetBattleTeamIndex index = m_caster->GetTeamIndex() == PET_BATTLE_TEAM_OPPONENT ? PET_BATTLE_TEAM_CHALLANGER : PET_BATTLE_TEAM_OPPONENT;
    return m_petBattle->GetTeam(index)->GetActivePet();
}

void BattlePetAbilityEffect::AddTargets()
{
    auto casterTeam = m_petBattle->GetTeam(m_caster->GetTeamIndex());

    // add required targets for ability
    switch (Handlers[m_effectEntry->EffectProperty].Target)
    {
        case PET_BATTLE_ABILITY_TARGET_CASTER:
        {
            AddTarget(m_caster);
            break;
        }
        case PET_BATTLE_ABILITY_TARGET_TARGET:
        {
            AddTarget(GetActiveOpponent());
            break;
        }
        case PET_BATTLE_ABILITY_TARGET_TARGET_TEAM:
        {
             for (auto battlePet : m_petBattle->GetTeam(PET_BATTLE_TEAM_OPPONENT)->BattlePets)
                AddTarget(battlePet);
            break;
        }
        // add battle pets from both teams
        case PET_BATTLE_ABILITY_TARGET_ALL:
        {
            for (auto&& teamIndex : { PET_BATTLE_TEAM_CHALLANGER, PET_BATTLE_TEAM_OPPONENT })
                for (auto battlePet : m_petBattle->GetTeam(teamIndex)->BattlePets)
                    AddTarget(battlePet);
            break;
        }
        // add unconditionally battle pets from casters team
        case PET_BATTLE_ABILITY_TARGET_CASTER_TEAM_UNCONDITIONAL:
        {
            for (auto battlePet : casterTeam->BattlePets)
                AddTarget(battlePet);
            break;
        }
        // add active battle pet from both teams
        case PET_BATTLE_ABILITY_TARGET_HEAD:
        {
            AddTarget(m_caster);
            AddTarget(GetActiveOpponent());
            break;
        }
        default:
            break;
    }
}

void BattlePetAbilityEffect::AddTarget(BattlePet* battlePet)
{
    if (!battlePet)
        return;

    /*if (!battlePet->IsAlive())
        return;*/

    m_targets.push_back(battlePet);
}

// -------------------------------------------------------------------------------

void BattlePetAbilityEffect::CalculateHit(int32 accuracy)
{
    accuracy += m_caster->States[BATTLE_PET_STATE_STAT_ACCURACY];
    accuracy -= m_target->States[BATTLE_PET_STATE_STAT_DODGE];

    // Base Hit chance fixes
    if (m_abilityId == 349) // Smash hit chance
        accuracy = 85;

    // accuracy is reduced by 2% for every level higher the opponent is
    if (m_target->GetLevel() > m_caster->GetLevel())
        accuracy -= (m_target->GetLevel() - m_caster->GetLevel()) * 2;

    if (m_caster != m_target && m_target->States[BATTLE_PET_STATE_UNTARGETABLE])
        m_flags |= PET_BATTLE_EFFECT_FLAG_MISS;

    if (m_target->GetAura(505)) // Target has Cocoon strike we miss 100%
        m_flags |= PET_BATTLE_EFFECT_FLAG_BLOCKED;

    // accuracy is less than 100%, calculate miss chance
    if (accuracy < 100 && !roll_chance_i(accuracy))
        m_flags |= PET_BATTLE_EFFECT_FLAG_MISS;
}

uint32 BattlePetAbilityEffect::CalculateHeal(uint32 heal)
{
    int32 modPercent = CalculatePct(m_caster->States[BATTLE_PET_STATE_STAT_POWER], 5);

    modPercent += m_caster->States[BATTLE_PET_STATE_MOD_HEALING_DEALT_PCT];
    modPercent += m_target->States[BATTLE_PET_STATE_MOD_HEALING_TAKEN_PCT];

    return heal + CalculatePct(heal, modPercent);
}

uint32 BattlePetAbilityEffect::GetPetType()
{
    if (BattlePetAbilityTurnEntry const* abilityTurn = sBattlePetAbilityTurnStore.LookupEntry(m_effectEntry->AbilityTurnId))
        if (BattlePetAbilityEntry const* ability = sBattlePetAbilityStore.LookupEntry(abilityTurn->AbilityId))
            return ability->FamilyId;

    return PET_BATTLE_PETTYPE_HUMANOID;
}

uint32 BattlePetAbilityEffect::CalculateDamage(uint32 damage)
{
     int32 modPct = CalculatePct(m_caster->States[BATTLE_PET_STATE_STAT_POWER], 5);

    // calculate family damage modifier
    int32 modPetTypePct = -100;
    if (auto damageModEntry = sGtBattlePetTypeDamageModStore.LookupEntry(m_target->GetFamilty() * BATTLE_PET_FAMILY_COUNT + m_abilityFamily))
        modPetTypePct += damageModEntry->Modifier * 100;

    m_flags |= PET_BATTLE_EFFECT_FLAG_HIT;
    if (modPetTypePct > 0)
        m_flags |= PET_BATTLE_EFFECT_FLAG_STRONG;
    if (modPetTypePct < 0)
        m_flags |= PET_BATTLE_EFFECT_FLAG_WEAK;

    // calculate critical chance
    if (roll_chance_i(m_target->States[BATTLE_PET_STATE_STAT_CRITICAL_CHANCE]))
    {
        modPct += 100;
        m_flags |= PET_BATTLE_EFFECT_FLAG_CRITICAL;
    }

    // Beast (237)
    // Beasts deal 25% extra damage below half health
    if (m_caster->States[BATTLE_PET_STATE_PASSIVE_BEAST])
        if ((m_caster->GetCurrentHealth() * 100 / m_caster->GetMaxHealth()) < 50)
            modPetTypePct += 25;

    damage += CalculatePct(damage, modPct);
    damage += CalculatePct(damage, m_caster->States[BATTLE_PET_STATE_MOD_DAMAGE_DEALT_PCT]);
    damage += CalculatePct(damage, m_target->States[BATTLE_PET_STATE_MOD_DAMAGE_TAKEN_PCT]);
    damage += CalculatePct(damage, modPetTypePct);

    // Magic (243)
    // Magic pets cannot be dealt more than 35% of their maximum health in one attack
    if (m_target->States[BATTLE_PET_STATE_PASSIVE_MAGIC])
        if (damage * 100 / m_target->GetMaxHealth() >= 35)
            damage = CalculatePct(m_target->GetMaxHealth(), 35);

    return damage;
}

// -------------------------------------------------------------------------------

void BattlePetAbilityEffect::Damage(BattlePet* target, uint32 damage)
{
    if (m_flags & PET_BATTLE_EFFECT_FAIL_MAKS)
        damage = 0;

    // HACKFIX until we find out why damage is rediciolus
    if (damage >= 2000)
        damage = m_caster->GetLevel() * urand(10, 25);

    /// Passive: aquatic
    if (m_target->States[BATTLE_PET_STATE_PASSIVE_AQUATIC] && (m_flags & PET_BATTLE_EFFECT_FLAG_PERIODIC))
        damage /= 2;

    /// Passive: magic
    if (m_target->States[BATTLE_PET_STATE_PASSIVE_MAGIC])
        if (damage * 100 / m_target->GetMaxHealth() >= 35)
            damage = CalculatePct(m_target->GetMaxHealth(), 35);

    // update target health and notify client
    uint32 health = damage > target->GetCurrentHealth() ? 0 : target->GetCurrentHealth() - damage;
    SetHealth(target, health);

    if (damage)
    {
        // update target states
        m_target->States[BATTLE_PET_STATE_CONDITION_WAS_DAMAGED_THIS_ROUND] = 1;
        m_target->States[BATTLE_PET_STATE_LAST_HIT_TAKEN] = damage;

        // update caster states
        m_caster->States[BATTLE_PET_STATE_CONDITION_DID_DAMAGE_THIS_ROUND] = 1;
        m_caster->States[BATTLE_PET_STATE_LAST_HIT_DEALT] = damage;
    }

   if (!sBattlePetAbilityStore.LookupEntry(m_abilityId)->Flags & 1 << 0)
    {
        for (auto&& aura : m_target->Auras)
        {
            if (aura->HasExpired())
                continue;

            // Don't self proc
            if (m_abilityId == aura->GetAbility())
                continue;

            if (target == m_caster) // Proc damage dealt
            {
                m_petBattle->Cast(m_caster, m_abilityId, 0, PET_BATTLE_ABILITY_PROC_ON_DAMAGE_DEALT);
            }
            else if (target == m_target) // Proc damage taken
            {
                m_petBattle->Cast(m_target, m_abilityId, 0, PET_BATTLE_ABILITY_PROC_ON_DAMAGE_TAKEN);
            }
        }
    }

    // HACKFIX our PROC ON DAMAGE DEALT system
   /* if (m_abilityId == 654 || m_abilityId == 1106) // Stun Effect
    {
        if (target && !target->GetAura(174) && damage > 0)
        {
            if (target->States[BATTLE_PET_STATE_MOD_PET_TYPE_ID] != BATTLE_PET_FAMILY_CRITTER)
            {
                m_petBattle->AddAura(m_caster, target, 174, 0, 1, PET_BATTLE_EFFECT_FLAG_NONE, 1);
            }
        }
    } */

    //HACKFIX our PROC ON DAMAGE TAKEN system

    // TODO: PETBATTLE_ABILITY_TURN0_PROC_ON_DAMAGE_DEALT and PETBATTLE_ABILITY_TURN0_PROC_ON_DAMAGE_TAKEN
}

void BattlePetAbilityEffect::HandleStopChainFailure()
{
    if (m_chainFailure == true)
        m_chainFailure = false;
}

void BattlePetAbilityEffect::Heal(BattlePet* target, uint32 heal)
{
    if (m_flags & PET_BATTLE_EFFECT_FAIL_MAKS)
        heal = 0;

    // make sure heal doesn't exceed targets max health
    uint32 health = target->GetCurrentHealth();
    uint32 maxHealth = target->GetMaxHealth();

    if (target->GetCurrentHealth() + heal > target->GetMaxHealth())
        heal = target->GetMaxHealth() - target->GetCurrentHealth();

    // update target health and notify client
    health += heal;
    SetHealth(target, health);

    if (!sBattlePetAbilityStore.LookupEntry(m_abilityId)->Flags & 1 << 0)
    {
        for (auto&& aura : m_target->Auras)
        {
            if (aura->HasExpired())
                continue;

            // Don't self proc
            //if (m_abilityId == aura->GetAbility())
               // continue;

            if (target == m_caster) // Proc damage dealt
            {
                m_petBattle->Cast(m_caster, m_abilityId, 0, PET_BATTLE_ABILITY_PROC_ON_HEAL_DEALT);
            }
            else if (target == m_target) // Proc damage taken
            {
                m_petBattle->Cast(m_target, m_abilityId, 0, PET_BATTLE_ABILITY_PROC_ON_HEAL_TAKEN);
            }
        }
    }
}

// -------------------------------------------------------------------------------

void BattlePetAbilityEffect::SetHealth(BattlePet* target, uint32 value)
{
    if (value > target->GetMaxHealth())
        value = target->GetMaxHealth();

    if (!(m_flags & PET_BATTLE_EFFECT_FAIL_MAKS) && value == target->GetCurrentHealth())
        m_flags |= PET_BATTLE_EFFECT_FLAG_MISS;

    if (!(m_flags & PET_BATTLE_EFFECT_FAIL_MAKS))
    {
        target->SetCurrentHealth(value);

        // target battle pet has died
        if (!value && target->IsAlive() && !target->States[BATTLE_PET_STATE_UNKILLABLE])
        {
            m_flags |= PET_BATTLE_EFFECT_FLAG_HIT;
            m_petBattle->Kill(m_caster, target, m_effectEntry->Id, m_flags);
        }
    }

    // notify client of health change
    PetBattleEffect effect{ PET_BATTLE_EFFECT_SET_HEALTH, m_caster->GetGlobalIndex(), m_flags, m_effectEntry->Id };
    effect.SetTurn(m_petBattle->GetTeam(m_caster->GetTeamIndex())->GetTurn(), 1);
    effect.UpdateHealth(target->GetGlobalIndex(), value);

    m_petBattle->AddEffect(effect);
}

// -------------------------------------------------------------------------------

// Effect 135
void BattlePetAbilityEffect::HandleKill()
{
    /// @TODO Figure out what to do with prop[1] & prop[3]
    CalculateHit(m_effectEntry->Properties[0]);

    int32 l_ImmuneStateCondition = m_effectEntry->Properties[2];

    if (!l_ImmuneStateCondition || !GetActiveOpponent()->States[l_ImmuneStateCondition])
        m_petBattle->Kill(m_caster, GetActiveOpponent(), m_effectEntry->Id, m_flags);

    if (!l_ImmuneStateCondition || !m_caster->States[l_ImmuneStateCondition])
        m_petBattle->Kill(m_caster, m_caster, m_effectEntry->Id, m_flags);
}

//Effect 78
void BattlePetAbilityEffect::HandleHealStateToggleAura()
{
    if (m_caster->GetAura(m_effectEntry->TriggerAbility))
    {
        m_caster->GetAura(m_effectEntry->TriggerAbility)->Expire();

        // Heal
        int32 stateValue = std::min(m_caster->States[m_effectEntry->Properties[1]], m_effectEntry->Properties[2]);
        int32 heal = m_effectEntry->Properties[0] + m_effectEntry->Properties[3] * stateValue;
        Heal(m_target, CalculateHeal(heal));
    }
    else
    {
        // No aura, add it
        m_petBattle->AddAura(m_caster, m_caster, m_effectEntry->TriggerAbility, m_effectEntry->Id, m_effectEntry->Properties[0], m_flags, 0);
    }
}

//Effect 74
void BattlePetAbilityEffect::HandleInitialization()
{
    //SetState(Target, BATTLEPET_STATE_Internal_InitialHealth, GetHealth(Target));
    //SetState(Target, BATTLEPET_STATE_Internal_InitialLevel, PetBattleInstance->Pets[Target]->Level);
    m_target->States[BATTLE_PET_STATE_STAT_CRITICAL_CHANCE] = 5;
    m_target->States[BATTLE_PET_STATE_MOD_PET_TYPE_ID] = m_target->GetFamilty();
    // set passive ability states
    static const uint32 familtyPassiveStates[BATTLE_PET_FAMILY_COUNT] =
    {
        BATTLE_PET_STATE_PASSIVE_HUMANOID,
        BATTLE_PET_STATE_PASSIVE_DRAGON,
        BATTLE_PET_STATE_PASSIVE_FLYING,
        BATTLE_PET_STATE_PASSIVE_UNDEAD,
        BATTLE_PET_STATE_PASSIVE_CRITTER,
        BATTLE_PET_STATE_PASSIVE_MAGIC,
        BATTLE_PET_STATE_PASSIVE_ELEMENTAL,
        BATTLE_PET_STATE_PASSIVE_BEAST,
        BATTLE_PET_STATE_PASSIVE_AQUATIC,
        BATTLE_PET_STATE_PASSIVE_MECHANICAL,
    };

    m_target->States[familtyPassiveStates[m_target->GetFamilty()]] = 1;

   /* uint32 petType = 0;
    if (BattlePetSpeciesEntry const* targetSpeciesInfo = sBattlePetSpeciesStore.LookupEntry(m_target->GetSpecies()))
        petType = targetSpeciesInfo->FamilyId;

    static const uint32 petTypePassiveState[NUM_BATTLEPET_PETTYPES] = {
        BATTLE_PET_STATE_PASSIVE_HUMANOID,
        BATTLE_PET_STATE_PASSIVE_DRAGON,
        BATTLE_PET_STATE_PASSIVE_FLYING,
        BATTLE_PET_STATE_PASSIVE_UNDEAD,
        BATTLE_PET_STATE_PASSIVE_CRITTER,
        BATTLE_PET_STATE_PASSIVE_MAGIC,
        BATTLE_PET_STATE_PASSIVE_ELEMENTAL,
        BATTLE_PET_STATE_PASSIVE_BEAST,
        BATTLE_PET_STATE_PASSIVE_AQUATIC,
        BATTLE_PET_STATE_PASSIVE_MECHANICAL,
    };

    m_target->States[petTypePassiveState[petType]] = 1; */
}

//Effect 86
void BattlePetAbilityEffect::HandleDamageAuraToggleAura()
{
    // Aura is applied independently of damages and cannot miss
    if (m_target->GetAura(m_effectEntry->Properties[3]))
    {
        m_target->GetAura(m_effectEntry->Properties[3])->Expire();
        m_petBattle->AddAura(m_caster, m_target, m_effectEntry->TriggerAbility, m_effectEntry->Id, m_effectEntry->Properties[4], m_flags, 0);
    }
    else
        m_petBattle->AddAura(m_caster, m_target, m_effectEntry->Properties[3], m_effectEntry->Id, m_effectEntry->Properties[2], m_flags, 0);

    CalculateHit(m_effectEntry->Properties[1]);

    Damage(m_target, CalculateDamage(m_effectEntry->Properties[0]));
}

//Effect 79
void BattlePetAbilityEffect::HandleModState()
{
    assert(m_effectEntry->Properties[0] < BATTLE_PET_MAX_STATES);

    /// Min check
    if (m_caster->States[m_effectEntry->Properties[0]] < m_effectEntry->Properties[2])
        return;

    /// Max check
    if (m_caster->States[m_effectEntry->Properties[0]] > m_effectEntry->Properties[3])
        return;

    m_petBattle->UpdatePetState(m_caster, m_target, m_effectEntry->Id, m_effectEntry->Properties[0], m_effectEntry->Properties[1]);
}

//Effect 72
void BattlePetAbilityEffect::HandleHealToggleAura()
{
    CalculateHit(m_effectEntry->Properties[1]);
    if (m_flags & PET_BATTLE_EFFECT_FAIL_MAKS)
    {
        SetHealth(m_target, m_target->GetCurrentHealth());
        return;
    }

    if (m_target->GetAura(m_effectEntry->TriggerAbility))
    {
        m_target->GetAura(m_effectEntry->TriggerAbility)->Expire();

        // Heal
        Heal(m_target, CalculateHeal(m_effectEntry->Properties[0]));
    }
    else
    {
        // No aura, add it
        m_petBattle->AddAura(m_caster, m_target, m_effectEntry->TriggerAbility, m_effectEntry->Id, m_effectEntry->Properties[2], m_flags, 0);
    }
}

//Effect 67
void BattlePetAbilityEffect::HandleEqualizeLife()
{
    CalculateHit(m_effectEntry->Properties[0]);
    if (m_flags & PET_BATTLE_EFFECT_FAIL_MAKS)
    {
        SetHealth(m_caster, m_caster->GetCurrentHealth());
        return;
    }

    int32 life = (m_caster->GetCurrentHealth() + m_target->GetCurrentHealth()) / 2;
    SetHealth(m_caster, life);
    SetHealth(m_target, life);
}

//Effect 66
void BattlePetAbilityEffect::HandleDamageRuthless()
{
    CalculateHit(m_effectEntry->Properties[1]);

    int32 damage = m_effectEntry->Properties[0];
    int32 l_TargetHealthPct = (m_target->GetCurrentHealth() * 100) / m_target->GetMaxHealth();

    if (l_TargetHealthPct < 25)
        damage += CalculatePct(damage, m_effectEntry->Properties[2]);

    Damage(m_target, CalculateDamage(damage));
}

//Effect 59
void BattlePetAbilityEffect::HandleWitchingDamage()
{
    CalculateHit(m_effectEntry->Properties[1]);

    /// Witching
    int32 l_Damage = m_effectEntry->Properties[0];
    int32 l_CasterHealPct = (m_caster->GetCurrentHealth() * 100) / m_caster->GetMaxHealth();

    if (m_effectEntry->Properties[2] && l_CasterHealPct < m_effectEntry->Properties[2])
        l_Damage *= 2;
    else if (m_target->GetCurrentHealth() > m_caster->GetCurrentHealth())                     ///< http://fr.wowhead.com/petability=253/repliquer
        l_Damage *= 2;

    Damage(m_target, CalculateDamage(l_Damage));
}

//Effect 53
void BattlePetAbilityEffect::HandleHealPercent()
{
    CalculateHit(m_effectEntry->Properties[1]);

    /// No sure if all ability should not use spell power on this effect
    /// Passive humanoid http://wowhead.com/petability=726
    if (m_abilityId == 726)
    {
        int32 l_ModPercent = 1;
        int32 l_Heal = CalculatePct(m_target->GetMaxHealth(), m_effectEntry->Properties[0]);

        /// Modifiers Dealt / Taken
        l_ModPercent += m_caster->States[BATTLE_PET_STATE_MOD_HEALING_DEALT_PCT];
        l_ModPercent += m_target->States[BATTLE_PET_STATE_MOD_HEALING_TAKEN_PCT];

        l_Heal += CalculatePct(l_Heal, l_ModPercent);
    }

    // Recovery
    int32 heal = CalculateHeal(CalculatePct(m_target->GetMaxHealth(), m_effectEntry->Properties[0]));

    Heal(m_target, heal);
}

//Effect 49
void BattlePetAbilityEffect::HandleRemoveAura()
{
    /// Data for this effect are unknown so we assume 100% unaura
    CalculateHit(100);
}

//Effect 29,169
void BattlePetAbilityEffect::HandleStateDamage()
{
    /// In some case, proc only if caster state prop[2] is on
    if (m_effectEntry->Properties[2] != 0 && !m_caster->States[m_effectEntry->Properties[2]])
        return;

    if (m_effectEntry->Properties[4])
        m_flags |= PET_BATTLE_EFFECT_FLAG_PERIODIC;

    CalculateHit(m_effectEntry->Properties[1]);
    int32 l_Damage = CalculateDamage(m_effectEntry->Properties[0]);

    /// Double base damage is the state in Prop[3] is on
    if (m_effectEntry->Properties[3] != 0 && m_target->States[m_effectEntry->Properties[3]] == 1)
        l_Damage *= 2;

    Damage(m_target, l_Damage);
}

//Effect 28
void BattlePetAbilityEffect::HandleCancellableAura()
{
    // Accuracy
    CalculateHit(m_effectEntry->Properties[1]);

    m_petBattle->AddAura(m_caster, m_target, m_effectEntry->TriggerAbility, m_effectEntry->Id, m_effectEntry->Properties[2], m_flags, 0);
}

// Effect 23: Points, Accuracy
void BattlePetAbilityEffect::HandleHeal()
{
    CalculateHit(m_effectEntry->Properties[1]);
    Heal(m_caster, CalculateHeal(m_effectEntry->Properties[0]));
}

// Effect 24: Points, Accuracy, IsPeriodic, OverideIndex
void BattlePetAbilityEffect::HandleDamage()
{
    CalculateHit(m_effectEntry->Properties[1]);

    if (m_effectEntry->Properties[2])
        m_flags |= PET_BATTLE_EFFECT_FLAG_PERIODIC;

    Damage(m_target, CalculateDamage(m_effectEntry->Properties[0]));
}

// Effect 25: BaseChangeToSucceed, IncreasePerToss
void BattlePetAbilityEffect::HandleCatch()
{
    // calculate catch chance
    uint32 chance = m_effectEntry->Properties[0] + (m_target->States[BATTLE_PET_STATE_INTERNAL_CAPTURE_BOOST] * m_effectEntry->Properties[1]);
    bool caught = roll_chance_i(chance);

    PetBattleEffectFlags flags = caught ? PET_BATTLE_EFFECT_FLAG_MISS : PET_BATTLE_EFFECT_FLAG_NONE;

    // notify client of catch
    PetBattleEffect effect{ PET_BATTLE_EFFECT_CATCH, m_caster->GetGlobalIndex(), flags, m_effectEntry->Id };
    effect.SetTurn(m_petBattle->GetTeam(m_caster->GetTeamIndex())->GetTurn(), 1);
    effect.UpdateStat(m_target->GetGlobalIndex(), caught ? 1 : 0);

    m_petBattle->AddEffect(effect);

    if (caught)
        m_petBattle->Catch(m_caster, m_target, m_effectEntry->Id);
    else
        m_target->States[BATTLE_PET_STATE_INTERNAL_CAPTURE_BOOST]++;
}

void BattlePetAbilityEffect::HandleResetAuraDuration()
{
    for (auto&& aura : m_target->Auras)
    {
        if (!aura->HasExpired() && m_caster == m_target && aura->GetAbility() == m_effectEntry->TriggerAbility)
        {
            // Sometimes has turn and stack depth
            PetBattleEffect effect(PET_BATTLE_EFFECT_AURA_CHANGE, m_caster->GetGlobalIndex());
            effect.UpdateAura(m_target->GetGlobalIndex(), aura->GetId(), m_effectEntry->TriggerAbility, m_effectEntry->Properties[0], m_petBattle->GetRound());
        }
    }
}

void BattlePetAbilityEffect::HandleSplittedDamage()
{
    CalculateHit(m_effectEntry->Properties[1]);
    int32 damage = CalculateDamage(m_effectEntry->Properties[0] / m_targets.size());
    Damage(m_target, damage);
}

// Effect 26: Unused, Accuracy, Duration, Unused
void BattlePetAbilityEffect::HandlePositiveAura()
{
    CalculateHit(m_effectEntry->Properties[1]);
    m_petBattle->AddAura(m_caster, m_target, m_effectEntry->TriggerAbility, m_effectEntry->Id, m_effectEntry->Properties[2], m_flags, 1);
}

// Effect 27: Points, Accuracy, PointsIncreasePerUse, PointsMax, StateToTriggerMaxPoints
void BattlePetAbilityEffect::HandleRampingDamage()
{
    CalculateHit(m_effectEntry->Properties[1]);

    // initial setup for ramping ability
    if (m_caster->States[BATTLE_PET_STATE_RAMPING_DAMAGE_ID] != m_abilityId)
    {
        m_petBattle->UpdatePetState(m_caster, m_caster, m_effectEntry->Id, BATTLE_PET_STATE_RAMPING_DAMAGE_ID, m_abilityId);
        m_petBattle->UpdatePetState(m_caster, m_caster, m_effectEntry->Id, BATTLE_PET_STATE_RAMPING_DAMAGE_USES, 0);
    }

    if (m_caster->States[BATTLE_PET_STATE_RAMPING_DAMAGE_USES] < m_effectEntry->Properties[3])
    {
        int32 newValue = m_caster->States[BATTLE_PET_STATE_RAMPING_DAMAGE_USES] + 1;
        m_petBattle->UpdatePetState(m_caster, m_caster, m_effectEntry->Id, BATTLE_PET_STATE_RAMPING_DAMAGE_USES, newValue);
    }

    uint32 damage = CalculateDamage(m_effectEntry->Properties[0] + m_effectEntry->Properties[2] * m_caster->States[BATTLE_PET_STATE_RAMPING_DAMAGE_USES]);
    Damage(m_target, damage);
}

void BattlePetAbilityEffect::HandleSetState()
{
    m_petBattle->UpdatePetState(m_caster, m_target, m_effectEntry->Id, m_effectEntry->Properties[0], m_effectEntry->Properties[1]);
};

void BattlePetAbilityEffect::HandleHealPctDealt()
{
    if (m_effectEntry->Properties[2] && m_chainFailure)
        return;

    CalculateHit(m_effectEntry->Properties[1]);
    Heal(m_target, CalculatePct(m_target->States[BATTLE_PET_STATE_LAST_HIT_DEALT], m_effectEntry->Properties[0]));
};

//Effect 52
void BattlePetAbilityEffect::HandleControlAura()
{
    // Chain Failure
    if (m_effectEntry->Properties[0] && m_chainFailure)
        return;

    CalculateHit(m_effectEntry->Properties[1]);

    // Passive Critters: Critters are immune to stun, root, and sleep effects.
    if (m_target->States[BATTLE_PET_STATE_PASSIVE_CRITTER] == 1)
    {
        if (m_effectEntry->TriggerAbility == 174 || m_effectEntry->TriggerAbility == 498 || m_effectEntry->TriggerAbility == 926 || m_effectEntry->TriggerAbility == 248) // Stun, Sleep, Root
        {
            return;
        }
    }

    m_petBattle->AddAura(m_caster, m_target, m_effectEntry->TriggerAbility, m_effectEntry->Id, m_effectEntry->Properties[2], m_flags, 0);
}

void BattlePetAbilityEffect::HandleHealCasterPercentNotState()
{
    if (m_effectEntry->Properties[2] && !m_caster->States[m_effectEntry->Properties[2]])
        return;

    if (m_effectEntry->Properties[3] && !m_target->States[m_effectEntry->Properties[3]])
        return;

    // It's caster who need to be heal
    m_target = m_caster;

    CalculateHit(m_effectEntry->Properties[1]);

    int32 heal = CalculateHeal(CalculatePct(m_target->GetMaxHealth(), m_effectEntry->Properties[0]));
    Heal(m_target, heal);
}

//Effect 172
void BattlePetAbilityEffect::HandleAuraCondAccuracyState()
{
    // Chain Failure
    if (m_effectEntry->Properties[4] && m_chainFailure)
        return;

    // Accuracy
    int32 accuracy = m_effectEntry->Properties[5];
    if ((!m_effectEntry->Properties[1] || m_caster->States[m_effectEntry->Properties[1]] != m_effectEntry->Properties[0]) && (!m_effectEntry->Properties[3] || m_target->States[m_effectEntry->Properties[3]] != m_effectEntry->Properties[0]))
        accuracy = 100;

    CalculateHit(accuracy);

    m_petBattle->AddAura(m_caster, m_target, m_effectEntry->TriggerAbility, m_effectEntry->Id, m_effectEntry->Properties[2], m_flags, 0);
}

void BattlePetAbilityEffect::HandleDamageCasterPercent()
{
    if (m_effectEntry->Properties[2])
        m_target = GetActiveOpponent();

    CalculateHit(m_effectEntry->Properties[1]);

    int32 damage = CalculateDamage(CalculatePct(m_caster->GetMaxHealth(), m_effectEntry->Properties[0]));
    Damage(m_target, damage);
}

void BattlePetAbilityEffect::HandleDamagePercentTaken()
{
    CalculateHit(m_effectEntry->Properties[1]);

    int32 damage = CalculateDamage(CalculatePct(m_caster->States[BATTLE_PET_STATE_LAST_HIT_TAKEN], m_effectEntry->Properties[0]));
    Damage(m_target, damage);
}

void BattlePetAbilityEffect::HandleResetState()
{
    m_target->States[m_effectEntry->Properties[0]] = 0;
}

void BattlePetAbilityEffect::HandleHealLastHitTaken()
{
    CalculateHit(m_effectEntry->Properties[1]);

    // Recovery
    int32 heal = CalculatePct(m_caster->States[BATTLE_PET_STATE_LAST_HIT_TAKEN], m_effectEntry->Properties[0]);
    int32 l_ModPercent = 0;

    // Modifiers Dealt / Taken
    l_ModPercent += m_caster->States[BATTLE_PET_STATE_MOD_DAMAGE_DEALT_PCT];
    l_ModPercent += m_target->States[BATTLE_PET_STATE_MOD_DAMAGE_TAKEN_PCT];

    Heal(m_target, heal + CalculatePct(heal, l_ModPercent));
}

void BattlePetAbilityEffect::HandleWeatherAura()
{
    // Chain Failure
    if (m_effectEntry->Properties[3] && m_chainFailure)
        return;

    CalculateHit(m_effectEntry->Properties[1]);

    for (auto&& aura : m_target->Auras)
    {
        if (!aura->HasExpired() && aura->GetAbility() == 590 || aura->GetAbility() == 205 || aura->GetAbility() == 229 || aura->GetAbility() == 257 || aura->GetAbility() == 203 || aura->GetAbility() == 596 || aura->GetAbility() == 718
            || aura->GetAbility() == 454 || aura->GetAbility() == 171 || aura->GetAbility() == 403)
            aura->Expire();
    }

    m_petBattle->AddAura(m_caster, m_target, m_effectEntry->TriggerAbility, m_effectEntry->Id, m_effectEntry->Properties[2], m_flags, 0);
}

void BattlePetAbilityEffect::HandleWeatherDamage()
{
    // weatherState
    if (!m_target->States[m_effectEntry->Properties[2]])
        return;

    // Accuracy
    CalculateHit(m_effectEntry->Properties[1]);

    // Periodic
    if (m_effectEntry->Properties[4])
        m_flags |= PET_BATTLE_EFFECT_FLAG_PERIODIC;

    // Damage
    Damage(m_target, CalculateDamage(m_effectEntry->Properties[0]));
}

void BattlePetAbilityEffect::HandleHealOnSpecificWeather()
{
    int32 l_RequiredState = m_effectEntry->Properties[2];

    if (l_RequiredState && !m_caster->States[l_RequiredState])
        return;

    CalculateHit(m_effectEntry->Properties[1]);

    int32 l_HealBase = m_effectEntry->Properties[0];
    int32 l_HealBonusOnStateID = m_effectEntry->Properties[3];

    if (l_HealBonusOnStateID && m_caster->States[l_HealBonusOnStateID])
        l_HealBase *= 2;

    Heal(m_target, CalculateHeal(l_HealBase));
}

//Effect 62
void BattlePetAbilityEffect::HandleDamagePercent()
{
    CalculateHit(m_effectEntry->Properties[1]);

    if (m_effectEntry->Properties[2])
        m_flags |= PET_BATTLE_EFFECT_FLAG_PERIODIC;

    int32 damage = CalculateDamage(CalculatePct(m_target->GetMaxHealth(), m_effectEntry->Properties[0]));
    Damage(m_target, damage);
}

// Effect 50: ChainFailure, Accuracy, Duration, MaxAllowed, CasterState, TargetState
void BattlePetAbilityEffect::HandleNegativeAura()
{
    if (m_effectEntry->Properties[0] && m_chainFailure)
        return;

    CalculateHit(m_effectEntry->Properties[1]);
    m_petBattle->AddAura(m_caster, m_target, m_effectEntry->TriggerAbility, m_effectEntry->Id, m_effectEntry->Properties[2], m_flags, m_effectEntry->Properties[3]);
}

void BattlePetAbilityEffect::HandleDamageStateBonus()
{
    CalculateHit(m_effectEntry->Properties[1]);

    int32 damage = m_effectEntry->Properties[0];
    if (m_effectEntry->Properties[3] && m_target->States[m_effectEntry->Properties[3]] == m_effectEntry->Properties[4])
        damage += m_effectEntry->Properties[2];

    Damage(m_target, CalculateDamage(damage));
}

// Effect 111
void BattlePetAbilityEffect::HandleResurect()
{
    SetHealth(m_target, CalculatePct(m_target->GetMaxHealth(), m_effectEntry->Properties[0]));
    m_target->States[BATTLE_PET_STATE_IS_DEAD] = 0;
}

// Effect 54: ChainFailure, Accuracy, Duration, MaxAllowed
void BattlePetAbilityEffect::HandlePeriodicTrigger()
{
    if (m_effectEntry->Properties[0] && m_chainFailure)
        return;

    CalculateHit(m_effectEntry->Properties[1]);
    m_petBattle->AddAura(m_caster, m_target, m_effectEntry->TriggerAbility, m_effectEntry->Id, m_effectEntry->Properties[2], m_flags, m_effectEntry->Properties[3]);
}

// Effect 63: Unused, Accuracy, Duration
void BattlePetAbilityEffect::HandlePeriodicPositiveTrigger()
{
    CalculateHit(m_effectEntry->Properties[1]);
    m_petBattle->AddAura(m_caster, m_target, m_effectEntry->TriggerAbility, m_effectEntry->Id, m_effectEntry->Properties[2], m_flags);
}

// Effect 76: Points, Accuracy
void BattlePetAbilityEffect::HandleDamageToggleAura()
{
    CalculateHit(m_effectEntry->Properties[1]);
    if (m_flags & PET_BATTLE_EFFECT_FAIL_MAKS)
        return;

    // aura has already been applied, expire and handle damage
    if (auto aura = m_caster->GetAura(m_effectEntry->TriggerAbility))
    {
        aura->Expire();
        Damage(m_target, CalculateDamage(m_effectEntry->Properties[0]));
    }
    // aura has yet to be applied
    else
        m_petBattle->AddAura(m_caster, m_caster, m_effectEntry->TriggerAbility, m_effectEntry->Id, m_effectEntry->Properties[2], m_flags);
}

// Effect 164
void BattlePetAbilityEffect::HandleExtraAttack()
{
    CalculateHit(m_effectEntry->Properties[1]);

    if (m_effectEntry->Properties[2])
        m_flags |= PET_BATTLE_EFFECT_FLAG_PERIODIC;

    int32 damage = CalculateDamage(m_effectEntry->Properties[0]);

    if (!(m_flags & PET_BATTLE_EFFECT_FAIL_MAKS))
    {
        Damage(m_target, damage);
    }
}

void BattlePetAbilityEffect::HandleDamageHitState()
{
    if ((!m_effectEntry->Properties[2] || !m_caster->States[m_effectEntry->Properties[2]])
        && (!m_effectEntry->Properties[3] || !m_target->States[m_effectEntry->Properties[3]]))
    {
        CalculateHit(m_effectEntry->Properties[1]);
    }

    if (m_effectEntry->Properties[1])
        m_flags |= PET_BATTLE_EFFECT_FLAG_PERIODIC;

    Damage(m_target, CalculateDamage(m_effectEntry->Properties[0]));
};

// Effect 103: Points, Accuracy
void BattlePetAbilityEffect::HandleExtraAttackFirst()
{
    if (m_petBattle->GetFirstAttackingTeam() != m_caster->GetTeamIndex())
        return;

    CalculateHit(m_effectEntry->Properties[1]);
    Damage(m_target, CalculateDamage(m_effectEntry->Properties[0]));
}

// Effect 104: Points, Accuracy, RequiredCasterState, RequiredTargetState
void BattlePetAbilityEffect::HandleHealState()
{
    // Wtf is this 2 and 3 numbers?
    auto i = m_effectEntry->Properties[2];
    ASSERT(i < BATTLE_PET_MAX_STATES);
    if (!m_caster->States[i] && m_effectEntry->Properties[2])
        return;

    i = m_effectEntry->Properties[3];
    ASSERT(i < BATTLE_PET_MAX_STATES);
    if (!m_target->States[i] && m_effectEntry->Properties[3])
        return;

    CalculateHit(m_effectEntry->Properties[1]);
    Heal(m_caster, CalculateHeal(m_effectEntry->Properties[0]));
}

// Effect 149: Points, Accuracy, IsPeriodic
void BattlePetAbilityEffect::HandleDamageNonLethal()
{
    CalculateHit(m_effectEntry->Properties[1]);

    if (m_effectEntry->Properties[2])
        m_flags |= PET_BATTLE_EFFECT_FLAG_PERIODIC;

    // make sure damage doesn't exceed targets health
    uint32 damage = CalculateDamage(m_effectEntry->Properties[0]);
    if (damage >= m_target->GetCurrentHealth())
        damage = m_target->GetCurrentHealth() - 1;

    Damage(m_target, damage);
}

// Effect 178: StatePoints, Accuracy, Duration, TargetState, ChainFailure, ReportFailAsImmune
void BattlePetAbilityEffect::HandlePowerlessAura()
{
    if (m_effectEntry->Properties[5])
        m_reportFailAsImmune = true;

    // make sure target doesn't already have state value
    if (m_effectEntry->Properties[3] && m_target->States[m_effectEntry->Properties[3]] == m_effectEntry->Properties[0])
    {
        if (m_reportFailAsImmune)
            m_flags |= PET_BATTLE_EFFECT_FLAG_IMMUNE;
        else
            return;
    }

    CalculateHit(m_effectEntry->Properties[1]);
    m_petBattle->AddAura(m_caster, m_target, m_effectEntry->TriggerAbility, m_effectEntry->Id, m_effectEntry->Properties[2], m_flags);
}
