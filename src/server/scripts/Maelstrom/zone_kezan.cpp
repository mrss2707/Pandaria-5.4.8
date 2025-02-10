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

#include "ScriptPCH.h"

enum {
    QUEST_NECESSARY_ROUGHNESS = 24502,
    QUEST_FOURTH_AND_GOAL = 28414,

    SPELL_DESPAWN_SHARKS = 69987,
    SPELL_SUMMON_BILGWATER_BUCCANEER = 70015,
    SPELL_SUMMON_BILGWATER_BUCCANEER_2 = 70075,
    SPELL_GROUND_RUMBLE_EARTHQUAKE = 78607,

    SPELL_THROW_FOOTBOMB = 69993,
    SPELL_KICK_FOOTBOMB = 70052,

    SPELL_SUMMON_DEATHWING = 66322,

    NPC_SUMMON_BILGWATER_BUCCANEER = 37179,
    NPC_SUMMON_BILGWATER_BUCCANEER_2 = 37213,
};

enum QuestRollingMyHomies {
    QUEST_ROLLING_WITH_MY_HOMIES = 14071,
    OBJECTIVE_IZZY_PICKED_UP = 265516,
    OBJECTIVE_ACE_PICKED_UP = 265517,
    OBJECTIVE_GOBBER_PICKED_UP = 265518,

    NPC_HOT_ROD = 34840,

    NPC_IZZY = 34890,
    NPC_ACE = 34892,
    NPC_GOBBER = 34954,

    NPC_IZZY_SUMMON = 34959,
    NPC_ACE_SUMMON = 34957,
    NPC_GOBBER_SUMMON = 34958,

    SPELL_GENERIC_INVISIBILITY_DETECTION_1 = 49416,
    SPELL_GENERIC_INVISIBILITY_DETECTION_2 = 49417,
    SPELL_GENERIC_INVISIBILITY_DETECTION_3 = 60922,
    SPELL_GENERIC_INVISIBILITY_DETECTION_4 = 90161,

    SPELL_SUMMON_ACE = 66597,
    SPELL_SUMMON_GOBBER = 66599,
    SPELL_SUMMON_IZZY = 66600,

    SPELL_RESUMMON_ACE = 66644,
    SPELL_RESUMMON_GOBBER = 66645,
    SPELL_RESUMMON_IZZY = 66646,

    SPELL_HOT_ROD_KNOCKBACK = 66301,

    ACTION_HOMIES_ENTER_VEHICLE = 1,
};

struct npc_sister_goldskimmer : public ScriptedAI
{
    npc_sister_goldskimmer(Creature* creature) : ScriptedAI(creature) { }

    void MoveInLineOfSight(Unit* who) override
    {
        if (who->GetTypeId() == TYPEID_PLAYER && me->IsFriendlyTo(who) && me->isInFrontInMap(who, 7) && !who->HasAura(74973))
        {
            Talk(0, who);
            me->CastSpell(who, 74973, true);
        }
    }
};

// 37106
class npc_coach_crosscheck : public CreatureScript {
public:
    npc_coach_crosscheck() : CreatureScript("npc_coach_crosscheck") {}

    bool OnQuestAccept(Player* player, Creature* /*creature*/, Quest const* quest) override {
        if (quest->GetQuestId() == QUEST_NECESSARY_ROUGHNESS) {
            player->CastSpell(nullptr, SPELL_SUMMON_BILGWATER_BUCCANEER, true);
            player->RemoveAurasDueToSpell(SPELL_GENERIC_INVISIBILITY_DETECTION_4);
        }

        return false;
    }
};

void AddSC_kezan()
{
    new creature_script<npc_sister_goldskimmer>("npc_sister_goldskimmer");
    new npc_coach_crosscheck();
}
