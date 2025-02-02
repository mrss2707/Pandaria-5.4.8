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
#include "../AI/SmartScripts/SmartAI.h"
#include "Random.h"
#include "Group.h"
#include "GroupMgr.h"
#include "ScriptedCreature.h"
#include "ScriptMgr.h"
#include "CreatureAI.h"
#include "BattlePetMgr.h"

enum ElwynnForest
{
    SPELL_FIRE_EXTINGUISHER_AURA            = 80209,

    /// Infantries vs. Wolfs
    // Texts
    INFANTRY_HELP_YELL                      = 0,
    INFANTRY_COMBAT_YELL                    = 1,
    // Creatures
    NPC_BLACKROCK_BATTLE_WORG               = 49871,
    NPC_STORMWIND_INFANTRY                  = 49869,
    // Spells
    WORG_GROWL                              = 2649,
    // Misc
    WORG_FIGHTING_FACTION                   = 232,
    WORG_FACTION_RESTORE                    = 32,
    AI_HEALTH_MIN                           = 85,
    INFANTRY_YELL_CHANCE                    = 10,

    /// Brother Paxton
    // Spells
    SPELL_FORTITUDE                         = 13864,
    SPELL_PENANCE                           = 66097,
    SPELL_FLASH_HEAL                        = 38588,
    SPELL_RENEW                             = 8362,
    SPELL_REVIVE                            = 93799,
    // Texts
    BROTHER_PAXTON_TEXT                     = 0,
    BROTHER_PAXTON_TEXT_PLAYER              = 1,
    // Events
    BROTHER_PAXTON_HEAL_EVENT_01            = 0,
    BROTHER_PAXTON_HEAL_EVENT_02            = 1,
    BROTHER_PAXTON_HEAL_EVENT_03            = 2,
    BROTHER_PAXTON_HEAL_EVENT_04            = 3,
    HEAL_EVENT_01_STEP_01                   = 1,
    HEAL_EVENT_01_STEP_02                   = 2,
    HEAL_EVENT_01_STEP_03                   = 3,
    HEAL_EVENT_01_STEP_04                   = 4,
    HEAL_EVENT_02_STEP_01                   = 5,
    HEAL_EVENT_02_STEP_02                   = 6,
    HEAL_EVENT_02_STEP_03                   = 7,
    HEAL_EVENT_02_STEP_04                   = 8,
    HEAL_EVENT_03_STEP_01                   = 9,
    HEAL_EVENT_03_STEP_02                   = 10,
    HEAL_EVENT_03_STEP_03                   = 11,
    HEAL_EVENT_03_STEP_04                   = 12,
    HEAL_EVENT_04_STEP_01                   = 13,
    HEAL_EVENT_04_STEP_02                   = 14,
    HEAL_EVENT_04_STEP_03                   = 15,
    HEAL_EVENT_04_STEP_04                   = 16,
    HEAL_EVENT_RESET                        = 17,

    /// Blackrock Spy
    // Texts
    TEXT_BLACKROCK_SPY_COMBAT               = 0,

    /// Blackrock Invader
    // Texts
    TEXT_BLACKROCK_INVADER_COMBAT           = 0,

    /// Goblin Assassin
    // Texts
    ASSASSIN_SAY_COMBAT                     = 0,

    /// Hogger + End Event
    // Texts
    SAY_AGGRO                               = 0,
    SAY_HELP                                = 1,
    SAY_GRR                                 = 2,
    SAY_NO                                  = 3,
    SAY_EATING                              = 4,
    SAY_STUNNED                             = 5,
    SAY_NO_HURT                             = 6,
    // Spells
    SPELL_TELEPORT_VISUAL_ONLY              = 64446,
    SPELL_VICIOUS_SLICE                     = 87337,
    SPELL_EATING                            = 87351,
    SPELL_UPSET_STOMACH                     = 87352,
    SPELL_SUMMON_MINIONS                    = 87366,
    SPELL_BLOODY_STRIKE                     = 87359,
    // Creatures
    NPC_HOGGER                              = 448,
    NPC_DUMAS                               = 46940,
    NPC_ANDROMATH                           = 46941,
    NPC_JONATHAN                            = 46942,
    NPC_RAGAMUFFIN                          = 46943,
    NPC_TRIGGER_MEAT                        = 45979,
    // Phases
    PHASE_EATING                            = 1,
    PHASE_EATING_ENDED                      = 2,
    PHASE_FINAL                             = 3,
    // Events
    EVENT_CAST_VICIOUS_SLICE                = 1,
    EVENT_HALF_HP_ONCE                      = 2,
    EVENT_CAST_BLOODY_STRIKE                = 3,
    EVENT_BACK_TO_FIGHT                     = 4,
    EVENT_SUMMON_GUARDS                     = 5,
    EVENT_SUMMON_KIDS                       = 6,
    EVENT_SAY_GRR                           = 7,
    EVENT_SAY_NO                            = 8,
    // Hogger Minion Spells
    SPELL_ADVENTURERS_RUSH                  = 87402,

    /// Alliance Way
    // Texts
    SAY_INTRO                               = 0,
    SAY_SPECIAL_1                           = 1,
    SAY_SPECIAL_2                           = 2,
    SAY_SPECIAL_3                           = 3,
    SAY_SPECIAL_4                           = 4,
    SAY_SPECIAL_5                           = 5,
    SAY_SPECIAL_6                           = 6,
    SAY_SPECIAL_7                           = 7,
    SAY_SPECIAL_8                           = 8,
    SAY_SPECIAL_9                           = 9,
    SAY_SPECIAL_10                          = 10,
    SAY_SPECIAL_11                          = 11,
    SAY_SPECIAL_12                          = 12,
    SAY_SPECIAL_13                          = 13,
    SAY_SPECIAL_14                          = 14,
    SAY_SPECIAL_15                          = 15,
    SAY_SPECIAL_16                          = 16,
    SAY_SPECIAL_17                          = 17,
    SAY_SPECIAL_18                          = 18,
    SAY_SPECIAL_19                          = 19,
    // Quests
    QUEST_ALLIANCE_WAY                      = 30988,
    QUEST_AN_OLD_PIT_FIGHTER                = 30989,
    // Creatures
    NPC_KING_VARIAN_WRYNN                   = 29611,
    NPC_VARIAN_WRYNN_ALLIANCE_WAY           = 61796,
    NPC_AYISA_ALLIANCE_WAY                  = 61792,
    NPC_JO_JO_ALLIANCE_WAY                  = 61793,
    NPC_WALK_WITH_VARIAN_CREDIT             = 61798,
    NPC_FIGHT_WITH_VARIAN_CREDIT            = 61824,
    // Spells
    SPELL_SUMMON_VARIAN                     = 120352,
    SPELL_SUMMON_AYSA_AND_JOJO              = 120344,
    SPELL_SPYING                            = 92857,
    SPELL_SNEAKING                          = 93046,
    SPELL_SPYGLASS                          = 80676,
    SPELL_VARIAN_GET_PUNCHED_SCENE          = 120568, // SPELL_EFFECT_186 not implemented in core
    // Actions
    ACTION_AN_OLD_PIT_FIGHTER               = 1
};

const Position AysaJojoStandPos[2]
{
    { -8331.30f, 290.36f, 156.83f, 5.99f }, // Ayisa
    { -8313.47f, 277.04f, 156.83f, 2.26f },
};

const Position VarianPath[9]
{
    { -8363.68f, 241.96f, 155.31f, 1.50f },
    { -8358.11f, 258.80f, 155.34f, 1.25f },
    { -8343.70f, 269.41f, 155.34f, 0.63f },
    { -8325.33f, 246.29f, 155.34f, 5.39f },
    { -8277.68f, 283.86f, 155.34f, 0.67f },
    { -8315.63f, 331.37f, 155.34f, 2.25f },
    { -8339.31f, 312.58f, 155.34f, 3.76f },
    { -8334.64f, 307.08f, 157.34f, 5.34f },
    { -8323.51f, 293.86f, 156.83f, 5.34f },
};

const Position VarianHomePath[3]
{
    { -8338.44f, 274.53f, 157.34f, 3.78f },
    { -8362.87f, 254.89f, 155.34f, 3.78f },
    { -8363.05f, 232.23f, 157.07f, 2.23f },
};

struct npc_stormwind_infantry : public ScriptedAI
{
    npc_stormwind_infantry(Creature* creature) : ScriptedAI(creature)
    {
        me->SetUInt32Value(UNIT_FIELD_NPC_EMOTESTATE, Emote::EMOTE_STATE_READY1H);
    }

    uint32 tSeek, cYell,tYell;

    void Reset() override
    {
        me->SetUInt32Value(UNIT_FIELD_NPC_EMOTESTATE, Emote::EMOTE_STATE_READY1H);
        tSeek = urand(1 * TimeConstants::IN_MILLISECONDS, 2 * TimeConstants::IN_MILLISECONDS);
        cYell = urand(0, 100);
        tYell = urand(5 * TimeConstants::IN_MILLISECONDS, 60 * TimeConstants::IN_MILLISECONDS);
    }

    void DamageTaken(Unit* who, uint32& damage) override
    {
        if (who->GetTypeId() == TYPEID_PLAYER)
        {
            me->GetThreatManager().resetAllAggro();
            who->AddThreat(me, 1.0f);
            me->AddThreat(who, 1.0f);
            me->AI()->AttackStart(who);
        }
        else if (who->IsPet())
        {
            me->GetThreatManager().resetAllAggro();
            me->AddThreat(who, 1.0f);
            me->AI()->AttackStart(who);
        }

        if (who->GetEntry() == ElwynnForest::NPC_BLACKROCK_BATTLE_WORG && me->HealthBelowPct(ElwynnForest::AI_HEALTH_MIN))
        {
            damage = 0;
            me->AddThreat(who, 1.0f);
            me->AI()->AttackStart(who);
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;
        else
        {
            if (tYell <= diff)
            {
                if (cYell < ElwynnForest::INFANTRY_YELL_CHANCE)
                {
                    Talk(ElwynnForest::INFANTRY_COMBAT_YELL);
                    tYell = urand(10 * TimeConstants::IN_MILLISECONDS, 120 * TimeConstants::IN_MILLISECONDS);
                }
                else
                    tYell = urand(10 * TimeConstants::IN_MILLISECONDS, 120 * TimeConstants::IN_MILLISECONDS);
            }
            else
            {
                tYell -= diff;
                DoMeleeAttackIfReady();
            }
        }
    }
};

struct npc_blackrock_battle_worg : public ScriptedAI
{
    npc_blackrock_battle_worg(Creature* creature) : ScriptedAI(creature) { }

    uint32 tSeek, tGrowl;

    void Reset() override
    {
        tSeek = urand(1 * TimeConstants::IN_MILLISECONDS, 2 * TimeConstants::IN_MILLISECONDS);
        tGrowl = urand(8 * TimeConstants::IN_MILLISECONDS + 500, 10 * TimeConstants::IN_MILLISECONDS);
        me->SetFaction(ElwynnForest::WORG_FACTION_RESTORE);
    }

    void DamageTaken(Unit* who, uint32& damage) override
    {
        if (who->GetTypeId() == TYPEID_PLAYER)
        {
            me->GetThreatManager().resetAllAggro();
            who->AddThreat(me, 1.0f);
            me->AddThreat(who, 1.0f);
            me->AI()->AttackStart(who);
        }
        else if (who->IsPet())
        {
            me->GetThreatManager().resetAllAggro();
            me->AddThreat(who, 1.0f);
            me->AI()->AttackStart(who);
        }

        if (who->GetEntry() == ElwynnForest::NPC_STORMWIND_INFANTRY && me->HealthBelowPct(ElwynnForest::AI_HEALTH_MIN))
        {
            damage = 0;
            me->AddThreat(who, 1.0f);
            me->AI()->AttackStart(who);
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (tSeek <= diff)
        {
            if ((me->IsAlive()) && (!me->IsInCombat() && (me->GetDistance2d(me->GetHomePosition().GetPositionX(), me->GetHomePosition().GetPositionY()) <= 1.0f)))
                if (Creature* enemy = me->FindNearestCreature(ElwynnForest::NPC_STORMWIND_INFANTRY, 1.0f, true))
                {
                    me->SetFaction(ElwynnForest::WORG_FIGHTING_FACTION);
                    me->AI()->AttackStart(enemy);
                    tSeek = urand(1 * TimeConstants::IN_MILLISECONDS, 2 * TimeConstants::IN_MILLISECONDS);
                }
        }
        else
            tSeek -= diff;

        if (UpdateVictim())
        {
            if (tGrowl <=diff)
            {
                DoCast(me->GetVictim(), ElwynnForest::WORG_GROWL);
                tGrowl = urand(8 * TimeConstants::IN_MILLISECONDS + 500, 10 * TimeConstants::IN_MILLISECONDS);
            }
            else
            {
               tGrowl -= diff;
               DoMeleeAttackIfReady();
            }
        }
        else
        {
            me->SetFaction(ElwynnForest::WORG_FACTION_RESTORE);
            return;
        }
    }
};

struct npc_brother_paxton : public ScriptedAI
{
    npc_brother_paxton(Creature *c) : ScriptedAI(c) { }

    EventMap _events;

    uint32 _cooldownTimer;

    bool _cooldown;

    void Reset() override
    {
        _events.Reset();

        me->SetFlag(UNIT_FIELD_FLAGS, UnitFlags::UNIT_FLAG_IMMUNE_TO_PC | UnitFlags::UNIT_FLAG_IMMUNE_TO_NPC);
        DoCast(me, ElwynnForest::SPELL_FORTITUDE);
        me->InitializeReactState();

        _cooldown = false;
        _cooldownTimer = 0;
    }

    void EnterEvadeMode() override
    {
        return;
    }

    void MoveInLineOfSight(Unit* p_Who) override
    {
        if (me->GetDistance(p_Who) < 15.0f)
        {
            if (p_Who && p_Who->GetTypeId() == TYPEID_PLAYER && !p_Who->HasAura(ElwynnForest::SPELL_FORTITUDE) && !_cooldown)
            {
               if (roll_chance_i(30))
               {
                    _cooldown = true;
                    me->CastSpell(p_Who, ElwynnForest::SPELL_FORTITUDE);
                    me->CastSpell(p_Who, ElwynnForest::SPELL_RENEW, true);
                    Talk(ElwynnForest::BROTHER_PAXTON_TEXT_PLAYER, p_Who);
                }
            }
        }
    }

    void JustEngagedWith(Unit* /*p_Who*/) override
    {
        return;
    }

    void MovementInform(uint32 p_Type, uint32 p_ID) override
    {
        if (p_Type == 2 && p_ID == 5 || p_ID == 14 || p_ID == 22 || p_ID == 33 || p_ID == 40 || p_ID == 51 || p_ID == 60 || p_ID == 62)
        {
            switch(urand(ElwynnForest::BROTHER_PAXTON_HEAL_EVENT_01, ElwynnForest::BROTHER_PAXTON_HEAL_EVENT_04))
            {
                case ElwynnForest::BROTHER_PAXTON_HEAL_EVENT_01:
                    _events.ScheduleEvent(ElwynnForest::HEAL_EVENT_01_STEP_01, 500ms);
                    break;
                case ElwynnForest::BROTHER_PAXTON_HEAL_EVENT_02:
                    _events.ScheduleEvent(ElwynnForest::HEAL_EVENT_02_STEP_01, 500ms);
                    break;
                case ElwynnForest::BROTHER_PAXTON_HEAL_EVENT_03:
                    _events.ScheduleEvent(ElwynnForest::HEAL_EVENT_03_STEP_01, 500ms);
                    break;
                case ElwynnForest::BROTHER_PAXTON_HEAL_EVENT_04:
                    _events.ScheduleEvent(ElwynnForest::HEAL_EVENT_04_STEP_01, 500ms);
                    break;
            }
        }
    }

    void UpdateAI(const uint32 diff) override
    {
        if (_cooldownTimer <= diff)
        {
            _cooldown = false;
            _cooldownTimer = 20 * TimeConstants::IN_MILLISECONDS;
        }
        else _cooldownTimer -= diff;

        _events.Update(diff);

        switch (_events.ExecuteEvent())
        {
            case ElwynnForest::HEAL_EVENT_01_STEP_01:
                me->SetReactState(ReactStates::REACT_PASSIVE);

                if (Creature* stormwind_infantry = me->FindNearestCreature(ElwynnForest::NPC_STORMWIND_INFANTRY, 6.0f))
                    stormwind_infantry->AI()->Talk(ElwynnForest::INFANTRY_HELP_YELL);
                _events.ScheduleEvent(ElwynnForest::HEAL_EVENT_01_STEP_02, 1s);
                break;
            case ElwynnForest::HEAL_EVENT_01_STEP_02:
                if (Creature* stormwind_infantry = me->FindNearestCreature(ElwynnForest::NPC_STORMWIND_INFANTRY, 6.0f))
                    me->SetFacingTo(me->GetAngle(stormwind_infantry));
                _events.ScheduleEvent(ElwynnForest::HEAL_EVENT_01_STEP_03, 2s);
                break;
            case ElwynnForest::HEAL_EVENT_01_STEP_03:
                Talk(ElwynnForest::BROTHER_PAXTON_TEXT);
                _events.ScheduleEvent(ElwynnForest::HEAL_EVENT_01_STEP_04, 1s);
                break;
            case ElwynnForest::HEAL_EVENT_01_STEP_04:
                if (Creature* stormwind_infantry = me->FindNearestCreature(ElwynnForest::NPC_STORMWIND_INFANTRY, 6.0f))
                    me->CastSpell(stormwind_infantry, ElwynnForest::SPELL_PENANCE);
                _events.ScheduleEvent(ElwynnForest::HEAL_EVENT_RESET, 4s);
                break;
            case ElwynnForest::HEAL_EVENT_02_STEP_01:
                me->SetReactState(ReactStates::REACT_PASSIVE);

                if (Creature* stormwind_infantry = me->FindNearestCreature(ElwynnForest::NPC_STORMWIND_INFANTRY, 6.0f))
                    stormwind_infantry->AI()->Talk(ElwynnForest::INFANTRY_HELP_YELL);
                _events.ScheduleEvent(ElwynnForest::HEAL_EVENT_02_STEP_02, 1s);
                break;
            case HEAL_EVENT_02_STEP_02:
                if (Creature* stormwind_infantry = me->FindNearestCreature(ElwynnForest::NPC_STORMWIND_INFANTRY, 6.0f))
                    me->SetFacingTo(me->GetAngle(stormwind_infantry));
                _events.ScheduleEvent(ElwynnForest::HEAL_EVENT_02_STEP_03, 2s);
                break;
            case ElwynnForest::HEAL_EVENT_02_STEP_03:
                Talk(ElwynnForest::BROTHER_PAXTON_TEXT);
                _events.ScheduleEvent(ElwynnForest::HEAL_EVENT_02_STEP_04, 1s);
                break;
            case ElwynnForest::HEAL_EVENT_02_STEP_04:
                if (Creature* stormwind_infantry = me->FindNearestCreature(ElwynnForest::NPC_STORMWIND_INFANTRY, 6.0f))
                    me->CastSpell(stormwind_infantry, ElwynnForest::SPELL_FLASH_HEAL);
                _events.ScheduleEvent(ElwynnForest::HEAL_EVENT_RESET, 4s);
                break;
            case ElwynnForest::HEAL_EVENT_03_STEP_01:
                me->SetReactState(ReactStates::REACT_PASSIVE);

                if (Creature* stormwind_infantry = me->FindNearestCreature(ElwynnForest::NPC_STORMWIND_INFANTRY, 6.0f))
                    stormwind_infantry->AI()->Talk(ElwynnForest::INFANTRY_HELP_YELL);
                _events.ScheduleEvent(ElwynnForest::HEAL_EVENT_03_STEP_02, 1s);
                break;
            case ElwynnForest::HEAL_EVENT_03_STEP_02:
                if (Creature* stormwind_infantry = me->FindNearestCreature(ElwynnForest::NPC_STORMWIND_INFANTRY, 6.0f))
                    me->SetFacingTo(me->GetAngle(stormwind_infantry));
                _events.ScheduleEvent(ElwynnForest::HEAL_EVENT_03_STEP_03, 2s);
                break;
            case ElwynnForest::HEAL_EVENT_03_STEP_03:
                Talk(ElwynnForest::BROTHER_PAXTON_TEXT);
                _events.ScheduleEvent(ElwynnForest::HEAL_EVENT_03_STEP_04, 1s);
                break;
            case ElwynnForest::HEAL_EVENT_03_STEP_04:
                if (Creature* stormwind_infantry = me->FindNearestCreature(ElwynnForest::NPC_STORMWIND_INFANTRY, 6.0f))
                    me->CastSpell(stormwind_infantry, ElwynnForest::SPELL_RENEW);
                _events.ScheduleEvent(ElwynnForest::HEAL_EVENT_RESET, 4s);
                break;
            case ElwynnForest::HEAL_EVENT_04_STEP_01:
                me->SetReactState(ReactStates::REACT_PASSIVE);

                if (Creature* stormwind_infantry = me->FindNearestCreature(ElwynnForest::NPC_STORMWIND_INFANTRY, 6.0f))
                    stormwind_infantry->AI()->Talk(ElwynnForest::INFANTRY_HELP_YELL);
                _events.ScheduleEvent(ElwynnForest::HEAL_EVENT_04_STEP_02, 1s);
                break;
            case ElwynnForest::HEAL_EVENT_04_STEP_02:
                if (Creature* stormwind_infantry = me->FindNearestCreature(ElwynnForest::NPC_STORMWIND_INFANTRY, 6.0f))
                    me->SetFacingTo(me->GetAngle(stormwind_infantry));
                _events.ScheduleEvent(ElwynnForest::HEAL_EVENT_04_STEP_03, 2s);
                break;
            case ElwynnForest::HEAL_EVENT_04_STEP_03:
                Talk(ElwynnForest::BROTHER_PAXTON_TEXT);
                _events.ScheduleEvent(ElwynnForest::HEAL_EVENT_04_STEP_04, 1s);
                break;
            case ElwynnForest::HEAL_EVENT_04_STEP_04:
                if (Creature* stormwind_infantry = me->FindNearestCreature(ElwynnForest::NPC_STORMWIND_INFANTRY, 6.0f))
                    me->CastSpell(stormwind_infantry, ElwynnForest::SPELL_REVIVE);
                _events.ScheduleEvent(ElwynnForest::HEAL_EVENT_RESET, 4s);
                break;
            case ElwynnForest::HEAL_EVENT_RESET:
                me->ClearInCombat();
                Reset();
                break;
            default:
                break;
        }

        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

struct npc_blackrock_spy : public ScriptedAI
{
    npc_blackrock_spy(Creature* creature) : ScriptedAI(creature)
    {
        CastSpying();
    }

    void CastSpying()
    {
        GetCreature(-8868.88f, -99.1016f);
        GetCreature(-8936.5f, -246.743f);
        GetCreature(-8922.44f, -73.9883f);
        GetCreature(-8909.68f, -40.0247f);
        GetCreature(-8834.85f, -119.701f);
        GetCreature(-9022.08f, -163.965f);
        GetCreature(-8776.55f, -79.158f);
        GetCreature(-8960.08f, -63.767f);
        GetCreature(-8983.12f, -202.827f);
    }

    void GetCreature(float X, float Y)
    {
        if (me->GetHomePosition().GetPositionX() == X && me->GetHomePosition().GetPositionY() == Y)
            if (!me->IsInCombat() && !me->HasAura(SPELL_SPYING))
                DoCast(me, SPELL_SPYING);

        CastSpyglass();
    }

    void CastSpyglass()
    {
        Spyglass(-8868.88f, -99.1016f, -8936.5f, -246.743f, -8922.44f, -73.9883f, -8909.68f, -40.0247f, -8834.85f,
            -119.701f, -9022.08f, -163.965f, -8776.55f, -79.158f, -8960.08f, -63.767f, -8983.12f, -202.827f);
    }

    void Spyglass(float X1, float Y1, float X2, float Y2, float X3, float Y3, float X4, float Y4, float X5, float Y5,
        float X6, float Y6, float X7, float Y7, float X8, float Y8, float X9, float Y9)
    {
        if ((me->GetHomePosition().GetPositionX() != X1 && me->GetHomePosition().GetPositionY() != Y1) &&
            (me->GetHomePosition().GetPositionX() != X2 && me->GetHomePosition().GetPositionY() != Y2) &&
            (me->GetHomePosition().GetPositionX() != X3 && me->GetHomePosition().GetPositionY() != Y3) &&
            (me->GetHomePosition().GetPositionX() != X4 && me->GetHomePosition().GetPositionY() != Y4) &&
            (me->GetHomePosition().GetPositionX() != X5 && me->GetHomePosition().GetPositionY() != Y5) &&
            (me->GetHomePosition().GetPositionX() != X6 && me->GetHomePosition().GetPositionY() != Y6) &&
            (me->GetHomePosition().GetPositionX() != X7 && me->GetHomePosition().GetPositionY() != Y7) &&
            (me->GetHomePosition().GetPositionX() != X8 && me->GetHomePosition().GetPositionY() != Y8) &&
            (me->GetHomePosition().GetPositionX() != X9 && me->GetHomePosition().GetPositionY() != Y9))
            if (me->GetHomePosition().GetPositionX() == me->GetPositionX() && me->GetHomePosition().GetPositionY() == me->GetPositionY())
                if (!me->IsInCombat() && !me->HasAura(SPELL_SPYGLASS))
                    DoCast(me, SPELL_SPYGLASS);
    }

    void JustEngagedWith(Unit* who) override
    {
        if (who && who->GetTypeId() == TypeID::TYPEID_PLAYER)
            if (roll_chance_i(50))
                Talk(ElwynnForest::TEXT_BLACKROCK_SPY_COMBAT, who);
    }

    void UpdateAI(uint32 /*diff*/) override
    {
        CastSpyglass();

        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

struct npc_blackrock_invader : public ScriptedAI
{
    npc_blackrock_invader(Creature* creature) : ScriptedAI(creature) { }

    void JustEngagedWith(Unit* who) override
    {
        if (who && who->GetTypeId() == TypeID::TYPEID_PLAYER)
            if (roll_chance_i(50))
                Talk(ElwynnForest::TEXT_BLACKROCK_INVADER_COMBAT, who);
    }

    void UpdateAI(uint32 /*diff*/) override
    {
        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

struct npc_goblin_assassin : public ScriptedAI
{
    npc_goblin_assassin(Creature* creature) : ScriptedAI(creature)
    {
        if (!me->IsInCombat() && !me->HasAura(SPELL_SPYING))
            DoCast(SPELL_SNEAKING);
    }

    void JustEngagedWith(Unit* who) override
    {
        if (who && who->GetTypeId() == TypeID::TYPEID_PLAYER)
            if (roll_chance_i(50))
                Talk(ASSASSIN_SAY_COMBAT, who);
    }

    void UpdateAI(uint32 /*diff*/) override
    {
        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

// King Varian Wrynn 29611
class npc_king_varian_wrynn : public CreatureScript
{
    public:
        npc_king_varian_wrynn() : CreatureScript("npc_king_varian_wrynn") { }

        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) override
        {
            if (quest->GetQuestId() == QUEST_ALLIANCE_WAY)
                player->CastSpell(creature, SPELL_SUMMON_VARIAN, true);

            return false;
        }

        struct npc_king_varian_wrynnAI : public SmartAI
        {
            npc_king_varian_wrynnAI(Creature* creature) : SmartAI(creature) { }

            void JustEngagedWith(Unit* who) override
            {
                SmartAI::JustEngagedWith(who);
            }

            void UpdateAI(uint32 diff) override
            {
                SmartAI::UpdateAI(diff);
            }
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return new npc_king_varian_wrynnAI(creature);
        }
};

// Varian Wrynn Alliance Way 61796
class npc_varian_wrynn_alliance_way_quest : public CreatureScript
{
    public:
        npc_varian_wrynn_alliance_way_quest() : CreatureScript("npc_varian_wrynn_alliance_way_quest") { }

        bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) override
        {
            if (quest->GetQuestId() == QUEST_AN_OLD_PIT_FIGHTER)
                player->CastSpell(creature, SPELL_SUMMON_VARIAN, true);

            return false;
        }

        struct npc_varian_wrynn_alliance_way_questAI : public ScriptedAI
        {
            npc_varian_wrynn_alliance_way_questAI(Creature* creature) : ScriptedAI(creature) { }

            ObjectGuid summonerGUID;
            uint32 delay;

            void IsSummonedBy(Unit* summoner) override
            {
                summonerGUID = summoner->GetGUID();
                me->SetFacingToObject(summoner);
                me->RemoveFlag(UNIT_FIELD_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                me->SetPhaseMask(2, true);

                if (summoner->ToPlayer() && summoner->ToPlayer()->GetQuestStatus(QUEST_ALLIANCE_WAY) == QUEST_STATUS_REWARDED)
                {
                    DoAction(ACTION_AN_OLD_PIT_FIGHTER);
                    return;
                }

                delay = 0;
                me->m_Events.Schedule(delay += 1500, 17, [this]()
                {
                    Movement::MoveSplineInit init(me);
                    for (auto itr : VarianPath)
                        init.Path().push_back(G3D::Vector3(itr.GetPositionX(), itr.GetPositionY(), itr.GetPositionZ()));

                    init.SetWalk(true);
                    init.Launch();

                    me->m_Events.Schedule(delay += me->GetSplineDuration(), 16, [this]()
                    {
                        me->SetFacingTo(Position::NormalizeOrientation(me->GetOrientation() + M_PI));
                        me->DespawnOrUnsummon(1 * IN_MILLISECONDS);

                        if (Player* owner = ObjectAccessor::GetPlayer(*me, summonerGUID))
                        {
                            owner->KilledMonsterCredit(NPC_WALK_WITH_VARIAN_CREDIT);

                            delay = 0;
                            owner->m_Events.Schedule(delay += 1000, 1, [owner]()
                            {
                                owner->SetPhaseMask(1, true);
                            });
                        }
                    });

                    delay = 0;
                    me->m_Events.Schedule(delay += 2000, 1, [this]()
                    {
                        Talk(SAY_INTRO);
                    });

                    me->m_Events.Schedule(delay += 5000, 2, [this]()
                    {
                        Talk(SAY_SPECIAL_1);
                    });

                    me->m_Events.Schedule(delay += 5000, 3, [this]()
                    {
                        Talk(SAY_SPECIAL_2);
                    });

                    me->m_Events.Schedule(delay += 7000, 4, [this]()
                    {
                        Talk(SAY_SPECIAL_3);
                    });

                    me->m_Events.Schedule(delay += 9000, 5, [this]()
                    {
                        Talk(SAY_SPECIAL_4);
                    });

                    me->m_Events.Schedule(delay += 6500, 6, [this]()
                    {
                        Talk(SAY_SPECIAL_5);
                    });

                    me->m_Events.Schedule(delay += 10000, 7, [this]()
                    {
                        Talk(SAY_SPECIAL_6);
                    });

                    me->m_Events.Schedule(delay += 9000, 8, [this]()
                    {
                        Talk(SAY_SPECIAL_7);
                    });

                    me->m_Events.Schedule(delay += 6000, 9, [this]()
                    {
                        Talk(SAY_SPECIAL_8);
                    });

                    me->m_Events.Schedule(delay += 6000, 10, [this]()
                    {
                        Talk(SAY_SPECIAL_9);
                    });

                    me->m_Events.Schedule(delay += 5000, 11, [this]()
                    {
                        Talk(SAY_SPECIAL_10);
                    });

                    me->m_Events.Schedule(delay += 7000, 12, [this]()
                    {
                        Talk(SAY_SPECIAL_11);
                    });

                    me->m_Events.Schedule(delay += 9000, 13, [this]()
                    {
                        Talk(SAY_SPECIAL_12);
                    });

                    me->m_Events.Schedule(delay += 13000, 14, [this]()
                    {
                        Talk(SAY_SPECIAL_13);
                    });
                });
            }

            void DoAction(int32 actionId) override
            {
                if (actionId == ACTION_AN_OLD_PIT_FIGHTER)
                {
                    delay = 0;
                    me->m_Events.Schedule(delay += 1500, 18, [this]()
                    {
                        Talk(SAY_SPECIAL_14);
                    });

                    me->m_Events.Schedule(delay += 11000, 20, [this]()
                    {
                        me->SetFaction(16);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
                        Talk(SAY_SPECIAL_15);
                    });

                    me->m_Events.Schedule(delay += 9300, 21, [this]()
                    {
                        Talk(SAY_SPECIAL_16);
                    });

                    me->m_Events.Schedule(delay += 6000, 22, [this]()
                    {
                        Talk(SAY_SPECIAL_17);
                    });

                    me->m_Events.Schedule(delay += 12000, 23, [this]()
                    {
                        Talk(SAY_SPECIAL_18);
                    });

                    me->m_Events.Schedule(delay += 2900, 24, [this]()
                    {
                        if (Player* owner = ObjectAccessor::GetPlayer(*me, summonerGUID))
                        {
                            owner->KilledMonsterCredit(NPC_FIGHT_WITH_VARIAN_CREDIT);
                            owner->CombatStop();
                        }

                        me->CombatStop();
                        me->SetFaction(35);
                    });

                    me->m_Events.Schedule(delay += 3500, 25, [this]()
                    {
                        Talk(SAY_SPECIAL_19);
                    });

                    me->m_Events.Schedule(delay += 4000, 26, [this]()
                    {
                        Movement::MoveSplineInit init(me);
                        for (auto itr : VarianHomePath)
                            init.Path().push_back(G3D::Vector3(itr.GetPositionX(), itr.GetPositionY(), itr.GetPositionZ()));

                        init.SetUncompressed();
                        init.Launch();

                        delay = 0;
                        me->m_Events.Schedule(delay += me->GetSplineDuration(), 27, [this]()
                        {
                            if (Player* owner = ObjectAccessor::GetPlayer(*me, summonerGUID))
                                owner->SetPhaseMask(1, true);

                            me->DespawnOrUnsummon();
                        });
                    });
                }
            }

            void DamageTaken(Unit* who, uint32& damage) override
            {
                damage = 0;
                me->HandleEmoteCommand(EMOTE_ONESHOT_DODGE);
            }
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return new npc_varian_wrynn_alliance_way_questAI(creature);
        }
};

// Ayisa and Jo Jo Alliance way 61792, 61793
class npc_ayisa_jojo_alliance_way_quest : public CreatureScript
{
    public:
        npc_ayisa_jojo_alliance_way_quest() : CreatureScript("npc_ayisa_jojo_alliance_way_quest") { }

        struct npc_ayisa_jojo_alliance_way_questAI : public ScriptedAI
        {
            npc_ayisa_jojo_alliance_way_questAI(Creature* creature) : ScriptedAI(creature) { }

            ObjectGuid summonerGUID;
            uint32 delay;
            uint8 point;
            bool follow;

            void IsSummonedBy(Unit* summoner) override
            {
                point = 0;
                summonerGUID = summoner->GetGUID();
                me->SetPhaseMask(2, true);
                me->DespawnOrUnsummon(2 * MINUTE * IN_MILLISECONDS + 30 * IN_MILLISECONDS);
                follow = true;

                if (summoner->ToPlayer() && summoner->ToPlayer()->GetQuestStatus(QUEST_ALLIANCE_WAY) == QUEST_STATUS_REWARDED)
                {
                    DoAction(ACTION_AN_OLD_PIT_FIGHTER);
                    follow = false;
                    return;
                }

                if (me->GetEntry() == NPC_AYISA_ALLIANCE_WAY)
                {
                    delay = 0;
                    me->m_Events.Schedule(delay += 300, 1, [this]()
                    {
                        follow = false;
                    });
                    
                    me->m_Events.Schedule(delay += 6000, 2, [this]()
                    {
                        Talk(SAY_INTRO);
                    });

                    me->m_Events.Schedule(delay += 46000, 3, [this]()
                    {
                        Talk(SAY_SPECIAL_1);
                    });

                    me->m_Events.Schedule(delay += 51000, 4, [this]()
                    {
                        Talk(SAY_SPECIAL_2);
                    });
                }
                
                if (me->GetEntry() == NPC_JO_JO_ALLIANCE_WAY)
                {
                    delay = 0;
                    me->m_Events.Schedule(delay += 600, 1, [this]()
                    {
                        follow = false;
                    });
                }
            }

            void DoAction(int32 actionId) override
            {
                if (actionId == ACTION_AN_OLD_PIT_FIGHTER)
                {
                    delay = 0;
                    me->m_Events.Schedule(delay += 11000, 19, [this]()
                    {
                        Movement::MoveSplineInit init(me);
                        point = me->GetEntry() == NPC_AYISA_ALLIANCE_WAY ? 0 : 1;
                        init.MoveTo(AysaJojoStandPos[point].GetPositionX(), AysaJojoStandPos[point].GetPositionY(), AysaJojoStandPos[point].GetPositionZ());

                        init.Launch();

                        me->m_Events.Schedule(delay += 19000, 21, [this]()
                        {
                            if (me->GetEntry() == NPC_AYISA_ALLIANCE_WAY)
                                if (Unit* owner = ObjectAccessor::GetUnit(*me, summonerGUID))
                                    Talk(SAY_SPECIAL_3, owner);
                        });

                        me->m_Events.Schedule(delay += 10800, 22, [this]()
                        {
                            follow = true;
                        });

                        delay = 0;
                        me->m_Events.Schedule(delay += me->GetSplineDuration(), 20, [this]()
                        {
                            me->SetFacingTo(AysaJojoStandPos[point].GetOrientation());
                        });
                    });
                }
            }

            void UpdateAI(uint32 diff) override
            {
                if (follow)
                    if (Unit* owner = ObjectAccessor::GetUnit(*me, summonerGUID))
                        me->GetMotionMaster()->MoveFollow(owner, 2.5f, me->GetAngle(owner));
            }
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return new npc_ayisa_jojo_alliance_way_questAI(creature);
        }
};

// Summon Varian alliance way 120352
class spell_summ_varian_alliance_way : public SpellScript
{
    PrepareSpellScript(spell_summ_varian_alliance_way);

    void HandleAfterCast()
    {
        if (Player* pCaster = GetCaster()->ToPlayer())
        {
            pCaster->SetPhaseMask(3, true);
            pCaster->CastSpell(pCaster, SPELL_SUMMON_AYSA_AND_JOJO, true);
        }
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_summ_varian_alliance_way::HandleAfterCast);
    }
};

struct npc_hogger : public ScriptedAI
{
    npc_hogger(Creature* creature) : ScriptedAI(creature)
    {
        if (Creature* trigger_meat = me->FindNearestCreature(ElwynnForest::NPC_TRIGGER_MEAT, 30))
            trigger_meat_guid = trigger_meat->GetGUID();
    }

    void Reset() override
    {
        me->SetReactState(REACT_AGGRESSIVE);
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
        phase = 0;
        events.Reset();
    }

    void JustEngagedWith(Unit* /*who*/) override
    {
        if (urand(0, 9) < 3)
            Talk(ElwynnForest::SAY_AGGRO);

        events.ScheduleEvent(ElwynnForest::EVENT_CAST_VICIOUS_SLICE, 3s);
    }

    void DamageTaken(Unit* attacker, uint32& damage) override
    {
        if (!phase && !HealthAbovePct(50))
        {
            Talk(ElwynnForest::SAY_HELP);
            me->CastSpell(me, ElwynnForest::SPELL_SUMMON_MINIONS, true);
            me->AttackStop();
            me->SetReactState(REACT_PASSIVE);
            phase = ElwynnForest::PHASE_EATING;
            events.CancelEvent(ElwynnForest::EVENT_CAST_VICIOUS_SLICE);
            events.ScheduleEvent(ElwynnForest::EVENT_HALF_HP_ONCE, 4s);
        }
        else if (phase == ElwynnForest::PHASE_EATING && me->HasAura(ElwynnForest::SPELL_UPSET_STOMACH))
        {
            Talk(ElwynnForest::SAY_STUNNED);
            phase = ElwynnForest::PHASE_EATING_ENDED;
            events.CancelEvent(ElwynnForest::EVENT_CAST_BLOODY_STRIKE);
            events.RescheduleEvent(ElwynnForest::EVENT_BACK_TO_FIGHT, 10s);
        }

        if (damage >= me->GetHealth() && phase != ElwynnForest::PHASE_FINAL)
        {
            Talk(ElwynnForest::SAY_NO_HURT);
            me->RemoveAllAuras();
            me->AttackStop();
            attacker->AttackStop();
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            me->SetWalk(true);
            me->GetMotionMaster()->MovePoint(1, -10136.9f, 670.009f, 36.03682f);
            damage = me->GetHealth() - 1;
            phase = ElwynnForest::PHASE_FINAL;
            events.Reset();

            if (Player* player = me->GetLootRecipient())
                player->RewardPlayerAndGroupAtKill(me, false);
        }
        else if (phase == ElwynnForest::PHASE_FINAL)
        {
            attacker->AttackStop();
            damage = me->GetHealth() - 1;
        }
    }

    void MovementInform(uint32 /*type*/, uint32 waypoint_id) override
    {
        switch (waypoint_id)
        {
            case 0:
                me->CastSpell(me, ElwynnForest::SPELL_EATING, true);
                events.ScheduleEvent(ElwynnForest::EVENT_CAST_BLOODY_STRIKE, 0);
                events.ScheduleEvent(ElwynnForest::EVENT_BACK_TO_FIGHT, 15s);
                break;
            case 1:
                events.ScheduleEvent(ElwynnForest::EVENT_SUMMON_GUARDS, 1s);
                break;
        }
    }

    void SetData(uint32 /*type*/, uint32 /*data*/) override
    {
        me->CastSpell(me, ElwynnForest::SPELL_TELEPORT_VISUAL_ONLY, true);
        me->DespawnOrUnsummon(1 * TimeConstants::IN_MILLISECONDS);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case ElwynnForest::EVENT_CAST_VICIOUS_SLICE:
                    if (Unit* victim = me->GetVictim())
                        me->CastSpell(victim, ElwynnForest::SPELL_VICIOUS_SLICE, false);

                    events.ScheduleEvent(ElwynnForest::EVENT_CAST_VICIOUS_SLICE, 12s);
                    break;
                case ElwynnForest::EVENT_HALF_HP_ONCE:
                {
                    Talk(ElwynnForest::SAY_EATING);
                    float trigger_x, trigger_y;

                    if (Creature* trigger_meat = ObjectAccessor::GetCreature(*me, trigger_meat_guid))
                    {
                        trigger_meat->GetPosition(trigger_x, trigger_y);
                        const float angle = me->GetAngle(trigger_x, trigger_y);
                        const float x = trigger_meat->GetPositionX() - 2 * cos(angle);
                        const float y = trigger_meat->GetPositionY() - 2 * sin(angle);
                        const float z = trigger_meat->GetMap()->GetHeight(x, y, trigger_meat->GetPositionZ());
                        me->GetMotionMaster()->MovePoint(0, x, y, z);
                    }
                    break;
                }
                case ElwynnForest::EVENT_CAST_BLOODY_STRIKE:
                    if (Creature* meatTrigger = ObjectAccessor::GetCreature(*me, trigger_meat_guid))
                        me->CastSpell(meatTrigger, ElwynnForest::SPELL_BLOODY_STRIKE, false);

                    events.ScheduleEvent(ElwynnForest::EVENT_CAST_BLOODY_STRIKE, 3s);
                    break;
                case ElwynnForest::EVENT_BACK_TO_FIGHT:
                    me->SetReactState(REACT_AGGRESSIVE);
                    phase = ElwynnForest::PHASE_EATING_ENDED;
                    events.CancelEvent(ElwynnForest::EVENT_CAST_BLOODY_STRIKE);
                    events.ScheduleEvent(ElwynnForest::EVENT_CAST_VICIOUS_SLICE, 3s);
                    break;
                case ElwynnForest::EVENT_SUMMON_GUARDS:
                    me->SummonCreature(ElwynnForest::NPC_JONATHAN, -10128.3f, 656.465f, 36.05443f, 2.045435f, TEMPSUMMON_MANUAL_DESPAWN);
                    me->SummonCreature(ElwynnForest::NPC_DUMAS, -10132.9f, 653.561f, 36.05033f, 2.020999f, TEMPSUMMON_MANUAL_DESPAWN);
                    me->SummonCreature(ElwynnForest::NPC_ANDROMATH, -10123.0f, 656.875f, 36.05113f, 1.971813f, TEMPSUMMON_MANUAL_DESPAWN);
                    events.ScheduleEvent(ElwynnForest::EVENT_SUMMON_KIDS, 4s);
                    break;
                case ElwynnForest::EVENT_SUMMON_KIDS:
                {
                    if (Creature* ragamuffin_1 = me->SummonCreature(ElwynnForest::NPC_RAGAMUFFIN, -10130.9f, 653.302f, 36.05013f, 1.652422f, TEMPSUMMON_TIMED_DESPAWN, 7500))
                        ragamuffin_1->AI()->SetData(0, 1);

                    if (Creature* ragamuffin_2 = me->SummonCreature(ElwynnForest::NPC_RAGAMUFFIN, -10122.5f, 660.198f, 36.03663f, 2.837752f, TEMPSUMMON_TIMED_DESPAWN, 6500))
                        ragamuffin_2->AI()->SetData(0, 2);

                    events.ScheduleEvent(ElwynnForest::EVENT_SAY_GRR, 8s + 500ms);
                    break;
                }
                case ElwynnForest::EVENT_SAY_GRR:
                    Talk(ElwynnForest::SAY_GRR);

                    if (Creature* jonathan = me->FindNearestCreature(ElwynnForest::NPC_JONATHAN, 10))
                        me->SetFacingToObject(jonathan);

                    events.ScheduleEvent(ElwynnForest::EVENT_SAY_NO, 15s);
                    break;
                case ElwynnForest::EVENT_SAY_NO:
                    Talk(ElwynnForest::SAY_NO);
                    break;
            }
        }

        DoMeleeAttackIfReady();
    }

private:
    EventMap events;
    ObjectGuid trigger_meat_guid;
    uint8 phase = 0;
};

struct npc_minion_of_hogger : public ScriptedAI
{
    npc_minion_of_hogger(Creature* creature) : ScriptedAI(creature) { }

    void JustDied(Unit* /*killer*/) override
    {
        DoCastAOE(ElwynnForest::SPELL_ADVENTURERS_RUSH);
    }

    void IsSummonedBy(Unit* summoner) override
    {
        if (summoner->GetVictim())
            me->AI()->AttackStart(summoner->GetVictim());
    }
};

// 26391
class quest_extinguishing_hope : public QuestScript
{
public:
    quest_extinguishing_hope() : QuestScript("quest_extinguishing_hope") {}

    void OnQuestStatusChange(Player* player, Quest const* /*quest*/, QuestStatus /*oldStatus*/, QuestStatus newStatus) override
    {
        if (newStatus == QUEST_STATUS_INCOMPLETE)
            player->CastSpell(player, SPELL_FIRE_EXTINGUISHER_AURA, true);
        else if (newStatus == QUEST_STATUS_REWARDED || newStatus == QUEST_STATUS_NONE)
            player->RemoveAurasDueToSpell(SPELL_FIRE_EXTINGUISHER_AURA);
    }
};

// CUSTOM
class npc_shop_guy : public CreatureScript
{
public:
    npc_shop_guy() : CreatureScript("npc_shop_guy") { }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
    {
        if (action == 1007)
        {
            if (player->GetCurrency(CURRENCY_TYPE_TIMELESS_COIN, false) < 1000)
            {
                creature->Whisper("You do not have enough Timeless Coins!", LANG_UNIVERSAL, player);
                return false;
            }

            if (player->GetCurrency(CURRENCY_TYPE_TIMELESS_COIN, false) >= 1000)
            {
                // Give random pet after completing any LFG scenario or dungeon
// select entry from item_template where BagFamily = 4096;
                LoginDatabase.PExecute("UPDATE account SET dp = dp + %u WHERE id = %u", 100000, player->GetSession()->GetAccountId());
                player->ModifyCurrency(777, -1000);
                creature->Whisper("You've exchanged 1000 Timeless coins for 10 shop points!", LANG_UNIVERSAL, player);
            }
            return true;
        }
        if (action == 1008)
        {
            if (player->GetCurrency(738, false) < 100)
            {
                creature->Whisper("You do not have enough Lesser charms of Good Fortune!", LANG_UNIVERSAL, player);
                return false;
            }

            if (player->GetCurrency(738, false) >= 100)
            {
                // Give random pet after completing any LFG scenario or dungeon
// select entry from item_template where BagFamily = 4096;
                LoginDatabase.PExecute("UPDATE account SET dp = dp + %u WHERE id = %u", 50000, player->GetSession()->GetAccountId());
                player->ModifyCurrency(738, -100);
                creature->Whisper("You've exchanged 100 Lesser charms of Good Fortune for 5 shop points!", LANG_UNIVERSAL, player);
            }
            return true;
        }
        if (action == 1009)
        {
            QueryResult result = LoginDatabase.PQuery("SELECT dp FROM `account` WHERE id = %u", player->GetSession()->GetAccountId());
            if (result)
            {
                Field* fields = result->Fetch();
                uint32 dp = fields[0].GetUInt32();
                if (dp < 50000) // less than 5 donation points.
                {
                    return false;
                }
                else
                {
                    if (urand(0, 100) <= 20)
                    {
                        creature->Whisper("You've rolled the dice and... good luck has found you your shop points have been doubled.", LANG_UNIVERSAL, player);
                        LoginDatabase.PExecute("UPDATE account SET dp = dp + %u WHERE id = %u", 100000, player->GetSession()->GetAccountId());
                    }
                    else
                    {
                        creature->Whisper("You've rolled the dice and... lost better luck next time! 5 points have been deducted from your balance.", LANG_UNIVERSAL, player);
                        LoginDatabase.PExecute("UPDATE account SET dp = dp - %u WHERE id = %u", 50000, player->GetSession()->GetAccountId());
                    }
                }
            }
            return true;
        }

        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Exchange 1000 timeless coins for 10 shop points.", GOSSIP_SENDER_MAIN, 1007, "Continue?", 0, false);
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Exchange 100 Lesser Charms of Good Fortune for 5 shop points.", GOSSIP_SENDER_MAIN, 1008, "Continue?", 0, false);
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "I want to gamble and risk 5 shop points for a 20% chance to double it.", GOSSIP_SENDER_MAIN, 1009, "Continue?", 0, false);

        SendGossipMenuFor(player, player->GetGossipTextId(creature), creature->GetGUID());

        return true;
    }
};

// CUSTOM
class npc_catchup_leveler : public CreatureScript
{
public:
    npc_catchup_leveler() : CreatureScript("npc_catchup_leveler") { }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
    {
        ClearGossipMenuFor(player);
        if (action == 1003)
        {
            if (player->GetLevel() >= 85)
            {
                creature->Whisper("You are to high of level to use this boost!", LANG_UNIVERSAL, player);
                return false;
            }
            player->GiveLevel(85);
            player->StoreNewItemInBestSlots(67387, 4); // 14 slot bag.
            player->LearnSpell(34090, false);  // Expert Riding
            player->LearnSpell(90267, false);  // Flight Master's License
            player->LearnSpell(54197, false);  // Cold Weather Flying
            player->LearnSpell(115913, false);  // Wisdom of Pandaria

            // Mounts
            if (player->GetTeamId() == TEAM_ALLIANCE)
            {
                player->AddItem(25472, 1); // Snowy Gryphon
                player->AddQuest(sObjectMgr->GetQuestTemplate(29547), nullptr); // The King's Command
            }
            else
            {
                player->AddItem(25475, 1); // Blue wind rider
                player->AddQuest(sObjectMgr->GetQuestTemplate(29611), nullptr); // The Art of War
            }

            if (player->GetClass() == CLASS_MAGE || player->GetClass() == CLASS_WARLOCK || player->GetClass() == CLASS_PRIEST) //Cloth
            {
                player->AddItem(56460, 1); // Head
                player->AddItem(56311, 1); // Chest
                player->AddItem(56348, 1); // Feet
                player->AddItem(56286, 1); // Hands
                player->AddItem(56413, 1); // Legs
                player->AddItem(56399, 1); // Shoulders
                player->AddItem(56305, 1); // Waist
                player->AddItem(56389, 1); // Wrist
                player->AddItem(56267, 1); // Cloak
                player->AddItem(56461, 1); //weapon
                player->AddItem(56380, 1); // finger 1
                player->AddItem(56432, 1); // finger 2
                player->AddItem(56400, 1); // trink 1
                player->AddItem(56320, 1); // trink 2
                player->AddItem(56385, 1); // Neck
            }
            if (player->GetClass() == CLASS_DRUID || player->GetClass() == CLASS_ROGUE || player->GetClass() == CLASS_MONK) // Leather
            {
                player->AddItem(56344, 1); // Head
                player->AddItem(56455, 1); // Chest
                player->AddItem(56395, 1); // Feet
                player->AddItem(56368, 1); // Hands
                player->AddItem(56309, 1); // Legs
                player->AddItem(56273, 1); // Shoulders
                player->AddItem(56429, 1); // Waist
                player->AddItem(56409, 1); // Wrist
                player->AddItem(56315, 1); // Cloak
                player->AddItem(56310, 1); // finger 1
                player->AddItem(56445, 1); // finger 2
                player->AddItem(56295, 1); // trink 1
                player->AddItem(56440, 1); // trink 2
                player->AddItem(56422, 1); // Neck
                if (player->GetClass() == CLASS_ROGUE)
                {
                    player->StoreNewItemInBestSlots(56302, 2);
                }
                else
                    player->StoreNewItemInBestSlots(56382, 1);
            }
            if (player->GetClass() == CLASS_HUNTER || player->GetClass() == CLASS_SHAMAN) // Mail
            {
                player->AddItem(56298, 1); // Head
                player->AddItem(56281, 1); // Chest
                player->AddItem(57867, 1); // Feet
                player->AddItem(56268, 1); // Hands
                player->AddItem(56386, 1); // Legs
                player->AddItem(56419, 1); // Shoulders
                player->AddItem(56363, 1); // Waist
                player->AddItem(56340, 1); // Wrist
                player->AddItem(56315, 1); // Cloak
                player->AddItem(56317, 1); //weapon
                player->AddItem(56310, 1); // finger 1
                player->AddItem(56445, 1); // finger 2
                player->AddItem(56295, 1); // trink 1
                player->AddItem(56440, 1); // trink 2
                player->AddItem(56422, 1); // Neck
            }
if (player->GetClass() == CLASS_WARRIOR || player->GetClass() == CLASS_PALADIN || player->GetClass() == CLASS_DEATH_KNIGHT) // Plate
{
    player->AddItem(56278, 1); // Head
    player->AddItem(56308, 1); // Chest
    player->AddItem(63444, 1); // Feet
    player->AddItem(56428, 1); // Hands
    player->AddItem(56283, 1); // Legs
    player->AddItem(56318, 1); // Shoulders
    player->AddItem(56447, 1); // Waist
    player->AddItem(56301, 1); // Wrist
    player->AddItem(56275, 1); // Cloak
    player->AddItem(56284, 1); //weapon
    player->AddItem(56270, 1); // finger 1
    player->AddItem(56299, 1); // finger 2
    player->AddItem(56458, 1); // trink 1
    player->AddItem(56345, 1); // trink 2
    player->AddItem(56319, 1); // Neck
    if (player->GetClass() == CLASS_WARRIOR || player->GetClass() == CLASS_PALADIN)
    {
        player->AddItem(56430, 1); // shield
        player->AddItem(56426, 1); // wep
    }
    else
    {
        player->AddItem(56430, 2); //dual wield weapon
        if (player->HasAura(51915))
        {
            player->RemoveAura(51915);
        }
        player->LearnSpell(50977, false); // Death Gate
    }
}
// Racials for worgens
if (player->GetRace() == RACE_WORGEN)
{
    player->LearnSpell(68992, false);
    player->LearnSpell(87840, false);
    player->LearnSpell(68996, false);
    player->LearnSpell(68976, false);
    player->LearnSpell(69978, false);
    player->LearnSpell(68975, false);
}
if (player->GetTeamId() == TEAM_ALLIANCE)
{
    player->BypassChecksTeleportTo(0, -8452.63f, 344.90f, 135.90f, 5.41f); // Stormwind City
}
else
{
    player->BypassChecksTeleportTo(1, 1573.77f, -4395.17f, 15.97f, 0.5f); // Orgrimmar
}
        }
        if (action == 1004)
        {
            if (player->GetLevel() <= 84)
            {
                creature->Whisper("Your level is to low - use the character boost to 85 then use this!", LANG_UNIVERSAL, player);
                return false;
            }

            QueryResult result = CharacterDatabase.PQuery("SELECT MAX(characters.level) FROM `characters` WHERE characters.account = %u", player->GetSession()->GetAccountId());
            if (result)
            {
                Field* fields = result->Fetch();
                uint32 minmax = fields[0].GetUInt32();
                if (minmax > 85)
                {
                    player->GiveLevel(minmax);
                    player->BypassChecksTeleportTo(870, 2093.72f, 4900.299f, 198.90f, 3.41f);
                }
                CloseGossipMenuFor(player);
            }
            return true;
        }
        if (action == 1005)
        {
            player->AddQuest(sObjectMgr->GetQuestTemplate(31450), nullptr);
            player->ShowNeutralPlayerFactionSelectUI();
            return true;
        }
        if (action == 1006)
        {
            player->AddItem(32588, 1);
            player->AddItem(34493, 1);
            player->AddItem(79744, 1);
            player->AddItem(72134, 1);
            player->AddItem(93669, 1);
            player->AddItem(23713, 1);
            player->AddItem(34493, 1);
            player->AddItem(68840, 1);
            player->AddItem(67128, 1);
            player->AddItem(68841, 1);
            player->AddItem(71624, 1);
            player->AddItem(34492, 1);
            player->AddItem(72153, 1);
            player->AddItem(49343, 1);
            player->AddItem(49287, 1);
            return true;
        }
        if (action == 1007)
        {
            if (player->GetCurrency(CURRENCY_TYPE_TIMELESS_COIN, true) >= 500)
            {
                player->ModifyCurrency(777, -1000);
                // Give random pet after completing any LFG scenario or dungeon
// select entry from item_template where BagFamily = 4096;
                QueryResult result = WorldDatabase.PQuery("select entry from item_template WHERE BagFamily = 4096 ORDER BY RAND() LIMIT 1");
                if (result)
                {
                    Field* fields = result->Fetch();
                    uint32 randomPetId = fields[0].GetUInt32();
                    player->AddItem(randomPetId, 1);
                }
            }
            return true;
        }

        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (player->GetRace() == RACE_PANDAREN_NEUTRAL)
        { 
            AddGossipItemFor(player, GOSSIP_ICON_TALK, "I would like to choose my faction and then boost.", GOSSIP_SENDER_MAIN, 1005, "Are you sure you want to choose a faction? After choosing you will be teleported to that faction city where you can boost to 85!", 0, false);
        }
        else
        {
            AddGossipItemFor(player, GOSSIP_ICON_TALK, "I would like to boost my character to 85.", GOSSIP_SENDER_MAIN, 1003, "Are you sure you want to Level Boost to 85? You will be provided with equipment to begin adventures on Pandaria.", 0, false);
        }
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "I'd like to synchronize my level to the highest character level on my account", GOSSIP_SENDER_MAIN, 1004, "Your level will be synchronized to your highest level on your account. Continue?", 0, false);
        AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Add trading card game battle pets to my account", GOSSIP_SENDER_MAIN, 1006, "MAKE SURE YOU HAVE 15 IVENTORY SLOTS!! Continue?", 0, false);

        SendGossipMenuFor(player, player->GetGossipTextId(creature), creature->GetGUID());

        return true;
    }
};

// CUSTOM
class npc_bot_menu_dunraid : public CreatureScript
{
public:
    npc_bot_menu_dunraid() : CreatureScript("npc_bot_menu_dunraid") { }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
    {
        ClearGossipMenuFor(player);
        if (action == 1001)
        {
            if (player)
            {
                if (creature->GetMapId() == 1050 || creature->GetMapId() == 1005 || creature->GetMapId() == 1051 || creature->GetMapId() == 1030 || creature->GetMapId() == 1095 || creature->GetMapId() == 1024 || creature->GetMapId() == 1048 || creature->GetMapId() == 1000)
                {
                    creature->Whisper("You can only have a healer bot in a Scenario!", LANG_UNIVERSAL, player);
                    return false;
                }

                if (creature->FindNearestCreature(98000, 300.0f))
                {
                    creature->FindNearestCreature(98000, 300.0f)->DespawnOrUnsummon(1000);
                    creature->Whisper("I've despawned a previously found tank bot, please talk to me again to summon a new bot!", LANG_UNIVERSAL, player);
                    return false;
                }

                if (!creature->FindNearestCreature(98000, 300.0f))
                {
                    creature->SummonCreature(98000, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
                    if (player->GetTeamId() == TEAM_ALLIANCE)
                    {
                        creature->FindNearestCreature(98000, 300.0f)->SetLevel(player->GetLevel());
                        creature->FindNearestCreature(98000, 300.0f)->SetFaction(11);
                        switch (urand(0, 6))
                        {
                        case 0:
                            creature->FindNearestCreature(98000, 300.0f)->SetDisplayId(14492); // Human
                            break;
                        case 1:
                            creature->FindNearestCreature(98000, 300.0f)->SetDisplayId(14396); // Dwarf
                            break;
                        case 2:
                            creature->FindNearestCreature(98000, 300.0f)->SetDisplayId(17375); // Draenei
                            break;
                        case 3:
                            creature->FindNearestCreature(98000, 300.0f)->SetDisplayId(39608); // Pandarian
                            break;
                        case 4:
                            creature->FindNearestCreature(98000, 300.0f)->SetDisplayId(17373); // Draenei
                            break;
                        case 5:
                            creature->FindNearestCreature(98000, 300.0f)->SetDisplayId(5446); // human f
                            break;
                        case 6:
                            creature->FindNearestCreature(98000, 300.0f)->SetDisplayId(32680); // Dwarf f
                            break;
                        default:
                            break;
                        }
                    }
                    else
                    {
                        creature->FindNearestCreature(98000, 300.0f)->SetFaction(85);
                    }
                    creature->FindNearestCreature(98000, 300.0f)->GetMotionMaster()->MoveFollow(player, 2.0f, 2.0f);
                }
            }
        }
        if (action == 1002)
        {
            if (player)
            {
                switch (urand(0, 1))
                {
                case 0: // Druid
                    if (creature->FindNearestCreature(98003, 300.0f))
                    {
                        creature->FindNearestCreature(98003, 300.0f)->DespawnOrUnsummon(1000);
                        creature->Whisper("I've despawned a previously found healer bot, please talk to me again to summon a new bot!", LANG_UNIVERSAL, player);
                        return false;
                    }

                    if (!creature->FindNearestCreature(98003, 300.0f))
                    {
                        creature->SummonCreature(98003, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
                        if (player->GetTeamId() == TEAM_ALLIANCE)
                        {
                            creature->FindNearestCreature(98003, 300.0f)->SetLevel(player->GetLevel());
                            creature->FindNearestCreature(98003, 300.0f)->SetFaction(11);
                        }
                        else
                        {
                            creature->FindNearestCreature(98003, 300.0f)->SetFaction(85);
                        }
                        creature->FindNearestCreature(98003, 300.0f)->GetMotionMaster()->MoveFollow(player, 3.0f, 3.0f);
                    }
                    break;
                case 1: // Priest
                    if (creature->FindNearestCreature(98004, 300.0f))
                    {
                        creature->FindNearestCreature(98004, 300.0f)->DespawnOrUnsummon(1000);
                        creature->Whisper("I've despawned a previously found healer bot, please talk to me again to summon a new bot!", LANG_UNIVERSAL, player);
                        return false;
                    }

                    if (!creature->FindNearestCreature(98004, 300.0f))
                    {
                        creature->SummonCreature(98004, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
                        if (player->GetTeamId() == TEAM_ALLIANCE)
                        {
                            creature->FindNearestCreature(98004, 300.0f)->SetLevel(player->GetLevel());
                            creature->FindNearestCreature(98004, 300.0f)->SetFaction(11);
                        }
                        else
                        {
                            creature->FindNearestCreature(98004, 300.0f)->SetFaction(85);
                        }
                        creature->FindNearestCreature(98004, 300.0f)->GetMotionMaster()->MoveFollow(player, 3.0f, 3.0f);
                    }
                    break;
                }
            }
        }
        if (action == 1003)
        {
            if (player)
            {
                if (creature->GetMapId() == 1050 || creature->GetMapId() == 1005 || creature->GetMapId() == 1051 || creature->GetMapId() == 1030 || creature->GetMapId() == 1095 || creature->GetMapId() == 1024 || creature->GetMapId() == 1048 || creature->GetMapId() == 1000)
                {
                    creature->Whisper("You can only have a healer bot in a Scenario!", LANG_UNIVERSAL, player);
                    return false;
                }

                    if (creature->FindNearestCreature(98002, 300.0f))
                    {
                        creature->FindNearestCreature(98002, 300.0f)->DespawnOrUnsummon(1000);
                        creature->Whisper("I've despawned a previously found dps bot, please talk to me again to summon a new bot!", LANG_UNIVERSAL, player);
                        return false;
                    }

                    if (!creature->FindNearestCreature(98002, 300.0f))
                    {
                        creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
                        if (player->GetTeamId() == TEAM_ALLIANCE)
                        {
                            creature->FindNearestCreature(98002, 300.0f)->SetFaction(11);
                        }
                        else
                        {
                            creature->FindNearestCreature(98002, 300.0f)->SetFaction(85);
                        }
                        creature->FindNearestCreature(98002, 300.0f)->GetMotionMaster()->MoveFollow(player, 4.0f, 4.0f);
                    }
            }
        }
        if (action == 1004)
        {
            // 98000 - tank and 98002 - mage dps and 98003 - druid healer and 98004 - priest healer and 98005 - rogue dps
            // 10 man (2 tanks, 4 healers, 4 dps)

            std::list<Creature*> themobsinRange;
            creature->GetCreaturesInRange(themobsinRange, 9999.0f);
            for (auto Aunit : themobsinRange)
            {
                if (Aunit)
                {
                    if (Aunit->GetEntry() == 98000 || Aunit->GetEntry() == 98003 || Aunit->GetEntry() == 98004 || Aunit->GetEntry() == 98002)
                    {
                        Aunit->DespawnOrUnsummon(1000);
                    }
                }
            }

            creature->SummonCreature(98000, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98000, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98000, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98000, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98000, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98000, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98000, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98000, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98000, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98000, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98000, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98000, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98000, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98000, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98000, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98000, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98000, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98000, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98000, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98000, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);

            creature->SummonCreature(98003, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98003, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98004, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98004, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98003, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98003, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98004, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98004, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98003, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98003, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98004, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98004, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98003, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98003, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98004, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98004, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98004, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98003, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98003, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98004, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98004, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98003, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98003, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98004, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98004, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98003, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98003, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98004, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98004, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98003, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98003, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98004, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98004, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98003, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98003, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98004, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98004, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98003, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98003, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98004, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98004, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98004, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98003, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98003, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98004, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98004, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98003, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98003, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98004, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98004, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);

            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
            creature->SummonCreature(98002, player->GetPosition(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);

            std::list<Creature*> athemobsinRange;
            creature->GetCreaturesInRange(athemobsinRange, 9999.0f);
            for (auto aAunit : athemobsinRange)
            {
                if (aAunit)
                {
                    if (aAunit->GetEntry() == 98000 || aAunit->GetEntry() == 98003 || aAunit->GetEntry() == 98004 || aAunit->GetEntry() == 98002)
                    {
                        aAunit->SetLevel(90);
                        aAunit->GetMotionMaster()->MoveFollow(player, urand(2.0f, 3.5f), urand(2.0f, 3.5f));
                    }
                }
            }
        }

        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        AddGossipItemFor(player, GOSSIP_ICON_TALK, "I would like to hire a Tank NPCBOT for this dungeon or raid.", GOSSIP_SENDER_MAIN, 1001, "After leaving this dungeon this bot will dissapear!", 0, false);
        AddGossipItemFor(player, GOSSIP_ICON_TALK, "I would like to hire a Healer NPCBOT for this dungeon or raid.", GOSSIP_SENDER_MAIN, 1002, "After leaving this dungeon this bot will dissapear!", 0, false);
        AddGossipItemFor(player, GOSSIP_ICON_TALK, "I would like to hire a DPS NPCBOT for this dungeon or raid.", GOSSIP_SENDER_MAIN, 1003, "After leaving this dungeon this bot will dissapear!", 0, false);
        if (creature->GetMap())
        {
            if (creature->GetMap()->IsRaid())
            {
                AddGossipItemFor(player, GOSSIP_ICON_TALK, "Set-up a 10-man raid group.", GOSSIP_SENDER_MAIN, 1004, "After leaving this dungeon this bot will dissapear!", 0, false);
                AddGossipItemFor(player, GOSSIP_ICON_TALK, "Set-up a 25-man raid group.", GOSSIP_SENDER_MAIN, 1005, "After leaving this dungeon this bot will dissapear!", 0, false);
            }
        }

        SendGossipMenuFor(player, 1, creature->GetGUID());

        return true;
    }
};

// Tank Bot 98000
class npc_bot_tank : public CreatureScript
{
public:
    npc_bot_tank() : CreatureScript("npc_bot_tank") { }

    enum iSpells
    {
        SPELL_RIGHTEOUS_FURY = 25780,
        SPELL_SEAL_OF_RIGHTEOUS = 111351,
        SPELL_HAMMER_OF_RIGHTEOUS = 53595,
        SPELL_CONSECRATION = 69930,
        SPELL_TAUNT_BOT = 355,
    };

    enum iEvents
    {
        EVENT_RIGHTEOUS_FURY = 1,
        EVENT_HAMMER_OF_RIGHTEOUS = 2,
        EVENT_CONSECRATION = 3,
        EVENT_TAUNT_CHECK = 4,
        EVENT_TARGET_CHECK = 5,
    };

    struct npc_bot_tankAI : public ScriptedAI
    {
        npc_bot_tankAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;

        void Reset() override
        {
            if (me->FindNearestPlayer(400.0f) && !me->IsInCombat())
            {
                me->GetMotionMaster()->MoveFollow(me->FindNearestPlayer(400.0f), 2.0f, 2.0f);
            }

            events.Reset();
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            if (me->GetMap())
            {
                if (me->GetMap()->IsDungeon())
                {
                    if (!me->HasAura(62552))
                    {
                        me->AddAura(62552, me); // Defend (30% damage reduction)
                        if (me->HasAura(62552))
                        {
                            me->GetAura(62552)->SetDuration(3000000);
                        }
                    }
                }
                if (me->GetMap()->IsRaid())
                {
                    if (!me->HasAura(62552))
                    {
                        me->AddAura(62552, me); // Defend (60% damage reduction)
                        if (me->HasAura(62552))
                        {
                            me->GetAura(62552)->SetStackAmount(2);
                            me->GetAura(62552)->SetDuration(3000000);
                        }
                    }
                }
                if (me->GetMapId() == 870 && me->GetZoneId() == 6757 && me->GetAreaId() == 6830)
                {
                    if (!me->HasAura(62552))
                    {
                        me->AddAura(62552, me); // Defend (60% damage reduction)
                        if (me->HasAura(62552))
                        {
                            me->GetAura(62552)->SetStackAmount(2);
                            me->GetAura(62552)->SetDuration(3000000);
                        }
                    }
                }
            }

            events.ScheduleEvent(EVENT_RIGHTEOUS_FURY, 1000);
            events.ScheduleEvent(EVENT_HAMMER_OF_RIGHTEOUS, urand(2 * IN_MILLISECONDS, 3 * IN_MILLISECONDS));
            events.ScheduleEvent(EVENT_CONSECRATION, 6 * IN_MILLISECONDS);
            events.ScheduleEvent(EVENT_TAUNT_CHECK, 8 * IN_MILLISECONDS);
            events.ScheduleEvent(EVENT_TARGET_CHECK, urand(1 * IN_MILLISECONDS, 2 * IN_MILLISECONDS));
        }

        void JustDied(Unit* /*killer*/) override
        {
        }

        void TempleOfJadeSerpent_Strategy()
        {
            if (me->GetMapId() == 960) // Temple of Jade Serpent (56511)
            {
                if (me->FindNearestCreature(56792, 30.0f))
                {
                    //Force change target
                    if (me->FindNearestCreature(56792, 30.0f)->IsInCombat() && me->FindNearestCreature(56792, 30.0f)->GetHealthPct() >= 80)
                        me->GetThreatManager().doAddThreatNoRedirect(me->FindNearestCreature(56792, 30.0f), 999999.0f);
                }
                if (me->HasAura(106653)) // Sha Residue
                {
                    if (me->FindNearestPlayer(30.0f))
                    {
                        me->MonsterMoveWithSpeed(me->FindNearestPlayer(30.0f)->GetPositionX(), me->FindNearestPlayer(30.0f)->GetPositionY(), me->FindNearestPlayer(30.0f)->GetPositionZ(), 0, true);
                    }
                }
                if (me->GetAreaId() == 6117)
                {
                    if (me->FindNearestCreature(56511, 30.0f))
                    {
                        //Force change target
                        if (me->FindNearestCreature(56511, 30.0f)->IsInCombat() && me->FindNearestCreature(56511, 30.0f)->GetHealthPct() >= 80)
                            me->GetThreatManager().doAddThreatNoRedirect(me->FindNearestCreature(56511, 30.0f), 999999.0f);
                    }
                }
            }
        }

        void SiegeOfOrgrimmar_Strategy_TANKDPS()
        {
            if (me->GetMapId() != 1136)
                return;

            if (me->GetMapId() == 1136)
            {
                if (me->HasAuraEffect(149164, 0)) // We are getting Frost AoE damage move.
                {
                    if (me->FindNearestPlayer(30.0f))
                    {
                        me->MonsterMoveWithSpeed(me->FindNearestPlayer(30.0f)->GetPositionX(), me->FindNearestPlayer(30.0f)->GetPositionY(), me->FindNearestPlayer(30.0f)->GetPositionZ(), 0.0f, true);
                    }
                    else
                    {
                        me->MonsterMoveWithSpeed(me->GetPositionX() + urand(2.0f, 4.0f), me->GetPositionY() + urand(4.0f, 5.0f), me->GetPositionZ(), 0.0f, false);
                    }
                }

                //Immerseius
                if (me->FindNearestCreature(71543, 100.0f) && me->FindNearestCreature(71603, 100.0f)) // Corrupted Sha
                {
                    // Sha puddles
                    if (me->FindNearestCreature(71543, 100.0f)->IsInCombat()) // Make sure we are in combat with boss
                    {
                        if (me->FindNearestCreature(71603, 100.0f))
                        {
                            me->GetThreatManager().resetAllAggro();
                            me->GetThreatManager().doAddThreatNoRedirect(me->FindNearestCreature(71603, 100.0f), 999999.0f);
                        }
                    }
                }
                //Protectors
                if (me->GetAreaId() == 6798)
                {
                    Unit* sun = me->FindNearestCreature(71480, 50.0f, false);
                    Unit* he = me->FindNearestCreature(71479, 50.0f, false);
                    Unit* rook = me->FindNearestCreature(71475, 50.0f, false);
                    if (sun && he && rook)
                    {
                        if (sun->IsInCombat())
                        {
                            me->GetThreatManager().resetAllAggro();
                            me->GetThreatManager().doAddThreatNoRedirect(sun, 999999.0f);
                            // We've damaged sun down to 5% but we need to make sure others are down as well.
                            if (sun->GetHealthPct() <= 5.0f && he->GetHealthPct() >= 5.0f && rook->GetHealthPct() >= 5.0f)
                            {
                                me->GetThreatManager().resetAllAggro();
                                me->GetThreatManager().doAddThreatNoRedirect(he, 999999.0f);
                            }
                            if (he->GetHealthPct() <= 5.0f && sun->GetHealthPct() <= 5.0f && rook->GetHealthPct() >= 5.0f)
                            {
                                me->GetThreatManager().resetAllAggro();
                                me->GetThreatManager().doAddThreatNoRedirect(rook, 999999.0f);
                            }
                            if (he->GetHealthPct() <= 5.0f && sun->GetHealthPct() <= 5.0f && rook->GetHealthPct() <= 5.0f)
                            {
                                me->GetThreatManager().resetAllAggro();
                                me->GetThreatManager().doAddThreatNoRedirect(he, 999999.0f);
                                he->Kill(he);
                                sun->Kill(sun);
                                rook->Kill(rook);
                            }
                        }
                    }
                }
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_RIGHTEOUS_FURY:
                    if (!me->HasAura(SPELL_RIGHTEOUS_FURY) || !me->HasAura(SPELL_SEAL_OF_RIGHTEOUS))
                    {
                        me->AddAura(SPELL_RIGHTEOUS_FURY, me);
                        me->AddAura(SPELL_SEAL_OF_RIGHTEOUS, me);
                    }
                    break;
                case EVENT_HAMMER_OF_RIGHTEOUS:
                    if (Unit* vict = me->GetVictim())
                        me->CastSpell(vict, SPELL_HAMMER_OF_RIGHTEOUS, false);

                    events.ScheduleEvent(EVENT_HAMMER_OF_RIGHTEOUS, urand(2 * IN_MILLISECONDS, 5 * IN_MILLISECONDS));
                    break;
                case EVENT_CONSECRATION:
                {
                    me->SetPower(POWER_MANA, me->GetMaxPower(POWER_MANA));
                    me->CastSpell(me, SPELL_CONSECRATION, false);
                    events.ScheduleEvent(EVENT_CONSECRATION, urand(9 * IN_MILLISECONDS, 10 * IN_MILLISECONDS));
                    break;
                }
                case EVENT_TAUNT_CHECK:
                {
                    std::list<Creature*> mobsinRange;
                    me->GetCreaturesInRange(mobsinRange, 30.0f);
                    for (auto unit : mobsinRange)
                    {
                        if (unit && unit->IsInCombat() && unit->GetVictim() != me)
                        {
                            me->CastSpell(unit, SPELL_TAUNT_BOT, true);
                            unit->GetThreatManager().doAddThreatNoRedirect(me, 500000.0f);
                        }
                    }
                    events.ScheduleEvent(EVENT_TAUNT_CHECK, urand(4 * IN_MILLISECONDS, 6 * IN_MILLISECONDS));
                    break;
                }
                case EVENT_TARGET_CHECK:
                {
                    if (me->GetMapId() == 960) // Temple of Jade Serpent (56511)
                    {
                        TempleOfJadeSerpent_Strategy();
                    }
                    if (me->GetMapId() == 1136) // Siege of Orgrimmar
                    {
                        SiegeOfOrgrimmar_Strategy_TANKDPS();
                    }
                    events.ScheduleEvent(EVENT_TARGET_CHECK, urand(1 * IN_MILLISECONDS, 2 * IN_MILLISECONDS));
                    break;
                }
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_bot_tankAI(creature);
    }
};

// DPS Bot 98005
class npc_bot_dps_rogue : public CreatureScript
{
public:
    npc_bot_dps_rogue() : CreatureScript("npc_bot_dps_rogue") { }

    enum iSpells
    {
        SPELL_SINISTER_STRIKE = 112931,
        SPELL_MUTILATE = 145414,
        SPELL_DEADLY_POISON = 145420,
    };

    enum iEvents
    {
        EVENT_ROGUE_SPELLS = 1,
        EVENT_TARGET_CHECK = 2,
    };

    struct npc_bot_dps_rogueAI : public ScriptedAI
    {
        npc_bot_dps_rogueAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;

        void Reset() override
        {
            if (me->FindNearestPlayer(400.0f) && !me->IsInCombat())
            {
                me->GetMotionMaster()->MoveFollow(me->FindNearestPlayer(400.0f), 4.0f, 4.0f);
            }

            events.Reset();
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            if (me->GetMap())
            {
                if (me->GetMap()->IsDungeon())
                {
                    if (!me->HasAura(62552))
                    {
                        me->AddAura(62552, me); // Defend (30% damage reduction)
                        if (me->HasAura(62552))
                        {
                            me->GetAura(62552)->SetDuration(3000000);
                        }
                    }
                }
                if (me->GetMap()->IsRaid())
                {
                    if (!me->HasAura(62552))
                    {
                        me->AddAura(62552, me); // Defend (60% damage reduction)
                        if (me->HasAura(62552))
                        {
                            me->GetAura(62552)->SetStackAmount(2);
                            me->GetAura(62552)->SetDuration(3000000);
                        }
                    }
                }
                if (me->GetMapId() == 870 && me->GetZoneId() == 6757 && me->GetAreaId() == 6830)
                {
                    if (!me->HasAura(62552))
                    {
                        me->AddAura(62552, me); // Defend (60% damage reduction)
                        if (me->HasAura(62552))
                        {
                            me->GetAura(62552)->SetStackAmount(2);
                            me->GetAura(62552)->SetDuration(3000000);
                        }
                    }
                }
            }
            events.ScheduleEvent(EVENT_ROGUE_SPELLS, 750);
            events.ScheduleEvent(EVENT_TARGET_CHECK, 3000);
        }

        void SiegeOfOrgrimmar_Strategy_TANKDPS()
        {
            if (me->GetMapId() != 1136)
                return;

            if (me->GetMapId() == 1136)
            {
                if (me->HasAuraEffect(149164, 0)) // We are getting Frost AoE damage move.
                {
                    if (me->FindNearestPlayer(30.0f))
                    {
                        me->MonsterMoveWithSpeed(me->FindNearestPlayer(30.0f)->GetPositionX(), me->FindNearestPlayer(30.0f)->GetPositionY(), me->FindNearestPlayer(30.0f)->GetPositionZ(), 0.0f, true);
                    }
                    else
                    {
                        me->MonsterMoveWithSpeed(me->GetPositionX() + urand(2.0f, 4.0f), me->GetPositionY() + urand(4.0f, 5.0f), me->GetPositionZ(), 0.0f, false);
                    }
                }

                //Immerseius
                if (me->FindNearestCreature(71543, 100.0f) && me->FindNearestCreature(71603, 100.0f)) // Corrupted Sha
                {
                    // Sha puddles
                    if (me->FindNearestCreature(71543, 100.0f)->IsInCombat()) // Make sure we are in combat with boss
                    {
                        if (me->FindNearestCreature(71603, 100.0f))
                        {
                            me->GetThreatManager().resetAllAggro();
                            me->GetThreatManager().doAddThreatNoRedirect(me->FindNearestCreature(71603, 100.0f), 999999.0f);
                        }
                    }
                }
                //Protectors
                if (me->GetAreaId() == 6798)
                {
                    Unit* sun = me->FindNearestCreature(71480, 50.0f, false);
                    Unit* he = me->FindNearestCreature(71479, 50.0f, false);
                    Unit* rook = me->FindNearestCreature(71475, 50.0f, false);
                    if (sun && he && rook)
                    {
                        if (sun->IsInCombat())
                        {
                            me->GetThreatManager().resetAllAggro();
                            me->GetThreatManager().doAddThreatNoRedirect(sun, 999999.0f);
                            // We've damaged sun down to 5% but we need to make sure others are down as well.
                            if (sun->GetHealthPct() <= 5.0f && he->GetHealthPct() >= 5.0f && rook->GetHealthPct() >= 5.0f)
                            {
                                me->GetThreatManager().resetAllAggro();
                                me->GetThreatManager().doAddThreatNoRedirect(he, 999999.0f);
                            }
                            if (he->GetHealthPct() <= 5.0f && sun->GetHealthPct() <= 5.0f && rook->GetHealthPct() >= 5.0f)
                            {
                                me->GetThreatManager().resetAllAggro();
                                me->GetThreatManager().doAddThreatNoRedirect(rook, 999999.0f);
                            }
                            if (he->GetHealthPct() <= 5.0f && sun->GetHealthPct() <= 5.0f && rook->GetHealthPct() <= 5.0f)
                            {
                                me->GetThreatManager().resetAllAggro();
                                me->GetThreatManager().doAddThreatNoRedirect(he, 999999.0f);
                                he->Kill(he);
                                sun->Kill(sun);
                                rook->Kill(rook);
                            }
                        }
                    }
                }
            }
        }

        void JustDied(Unit* /*killer*/) override
        {
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_ROGUE_SPELLS:
                    me->SetPower(POWER_MANA, me->GetMaxPower(POWER_MANA));
                    if (Unit* vict = me->GetVictim())
                    {
                        switch (urand(0, 1))
                        {
                        case 0:
                            me->CastSpell(vict, SPELL_SINISTER_STRIKE, false);

                            if (urand(0, 100) <= 10)
                            {
                                me->CastSpell(vict, SPELL_DEADLY_POISON, false);
                            }

                            break;
                        case 1:
                            me->CastSpell(vict, SPELL_MUTILATE, false);

                            if (urand(0, 100) <= 10)
                            {
                                me->CastSpell(vict, SPELL_DEADLY_POISON, false);
                            }
                            break;
                        }
                    }

                    events.ScheduleEvent(EVENT_ROGUE_SPELLS, urand(1 * IN_MILLISECONDS, 2 * IN_MILLISECONDS));
                    break;
                case EVENT_TARGET_CHECK:
                {
                    if (me->GetMapId() == 960) // Temple of Jade Serpent (56511)
                    {
                        if (me->FindNearestCreature(56792, 30.0f))
                        {
                            //Force change target
                            if (me->FindNearestCreature(56792, 30.0f)->IsInCombat() && me->FindNearestCreature(56792, 30.0f)->GetHealthPct() >= 80)
                                me->GetThreatManager().doAddThreatNoRedirect(me->FindNearestCreature(56792, 30.0f), 999999.0f);
                        }
                        if (me->HasAura(106653)) // Sha Residue
                        {
                            if (me->FindNearestPlayer(30.0f))
                            {
                                me->MonsterMoveWithSpeed(me->FindNearestPlayer(30.0f)->GetPositionX(), me->FindNearestPlayer(30.0f)->GetPositionY(), me->FindNearestPlayer(30.0f)->GetPositionZ(), 0, true);
                            }
                        }
                        if (me->GetAreaId() == 6117)
                        {
                            if (me->FindNearestCreature(56511, 30.0f))
                            {
                                //Force change target
                                if (me->FindNearestCreature(56511, 30.0f)->IsInCombat() && me->FindNearestCreature(56511, 30.0f)->GetHealthPct() >= 80)
                                    me->GetThreatManager().doAddThreatNoRedirect(me->FindNearestCreature(56511, 30.0f), 999999.0f);
                            }
                        }
                    }
                    SiegeOfOrgrimmar_Strategy_TANKDPS();
                    events.ScheduleEvent(EVENT_TARGET_CHECK, 3 * IN_MILLISECONDS);
                    break;
                }
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_bot_dps_rogueAI(creature);
    }
};

// DPS Bot 98000
class npc_bot_dps_mage : public CreatureScript
{
public:
    npc_bot_dps_mage() : CreatureScript("npc_bot_dps_mage") { }

    enum iSpells
    {
        SPELL_ARCANE_BLAST = 101816,
        SPELL_ARCANE_BARRAGE = 145437,
        SPELL_SCORCH = 75412,
    };

    enum iEvents
    {
        EVENT_ARCANE_SPELLS = 1,
        EVENT_TARGET_CHECK = 2,
    };

    struct npc_bot_dps_mageAI : public ScriptedAI
    {
        npc_bot_dps_mageAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;

        void Reset() override
        {
            if (me->FindNearestPlayer(400.0f) && !me->IsInCombat())
            {
                me->GetMotionMaster()->MoveFollow(me->FindNearestPlayer(400.0f), 4.0f, 4.0f);
            }

            me->SetControlled(false, UNIT_STATE_ROOT);

            events.Reset();
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            if (me->GetMap())
            {
                if (me->GetMap()->IsDungeon())
                {
                    if (!me->HasAura(62552))
                    {
                        me->AddAura(62552, me); // Defend (30% damage reduction)
                        if (me->HasAura(62552))
                        {
                            me->GetAura(62552)->SetDuration(3000000);
                        }
                    }
                }
                if (me->GetMap()->IsRaid())
                {
                    if (!me->HasAura(62552))
                    {
                        me->AddAura(62552, me); // Defend (60% damage reduction)
                        if (me->HasAura(62552))
                        {
                            me->GetAura(62552)->SetStackAmount(2);
                            me->GetAura(62552)->SetDuration(3000000);
                        }
                    }
                }
                if (me->GetMapId() == 870 && me->GetZoneId() == 6757 && me->GetAreaId() == 6830)
                {
                    if (!me->HasAura(62552))
                    {
                        me->AddAura(62552, me); // Defend (60% damage reduction)
                        if (me->HasAura(62552))
                        {
                            me->GetAura(62552)->SetStackAmount(2);
                            me->GetAura(62552)->SetDuration(3000000);
                        }
                    }
                }
            }
            me->SetControlled(true, UNIT_STATE_ROOT);
            events.ScheduleEvent(EVENT_ARCANE_SPELLS, 750);
            events.ScheduleEvent(EVENT_TARGET_CHECK, 3000);
        }

        void JustDied(Unit* /*killer*/) override
        {
        }

        void SiegeOfOrgrimmar_Strategy_TANKDPS()
        {
            if (me->GetMapId() != 1136)
                return;

            if (me->GetMapId() == 1136)
            {
                if (me->HasAuraEffect(149164, 0)) // We are getting Frost AoE damage move.
                {
                    if (me->FindNearestPlayer(30.0f))
                    {
                        me->MonsterMoveWithSpeed(me->FindNearestPlayer(30.0f)->GetPositionX(), me->FindNearestPlayer(30.0f)->GetPositionY(), me->FindNearestPlayer(30.0f)->GetPositionZ(), 0.0f, true);
                    }
                    else
                    {
                        me->MonsterMoveWithSpeed(me->GetPositionX() + urand(2.0f, 4.0f), me->GetPositionY() + urand(4.0f, 5.0f), me->GetPositionZ(), 0.0f, false);
                    }
                }

                //Immerseius
                if (me->FindNearestCreature(71543, 100.0f) && me->FindNearestCreature(71603, 100.0f)) // Corrupted Sha
                {
                    // Sha puddles
                    if (me->FindNearestCreature(71543, 100.0f)->IsInCombat()) // Make sure we are in combat with boss
                    {
                        if (me->FindNearestCreature(71603, 100.0f))
                        {
                            me->GetThreatManager().resetAllAggro();
                            me->GetThreatManager().doAddThreatNoRedirect(me->FindNearestCreature(71603, 100.0f), 999999.0f);
                        }
                    }
                }
                //Protectors
                if (me->GetAreaId() == 6798)
                {
                    Unit* sun = me->FindNearestCreature(71480, 50.0f, false);
                    Unit* he = me->FindNearestCreature(71479, 50.0f, false);
                    Unit* rook = me->FindNearestCreature(71475, 50.0f, false);
                    if (sun && he && rook)
                    {
                        if (sun->IsInCombat())
                        {
                            me->GetThreatManager().resetAllAggro();
                            me->GetThreatManager().doAddThreatNoRedirect(sun, 999999.0f);
                            // We've damaged sun down to 5% but we need to make sure others are down as well.
                            if (sun->GetHealthPct() <= 5.0f && he->GetHealthPct() >= 5.0f && rook->GetHealthPct() >= 5.0f)
                            {
                                me->GetThreatManager().resetAllAggro();
                                me->GetThreatManager().doAddThreatNoRedirect(he, 999999.0f);
                            }
                            if (he->GetHealthPct() <= 5.0f && sun->GetHealthPct() <= 5.0f && rook->GetHealthPct() >= 5.0f)
                            {
                                me->GetThreatManager().resetAllAggro();
                                me->GetThreatManager().doAddThreatNoRedirect(rook, 999999.0f);
                            }
                            if (he->GetHealthPct() <= 5.0f && sun->GetHealthPct() <= 5.0f && rook->GetHealthPct() <= 5.0f)
                            {
                                me->GetThreatManager().resetAllAggro();
                                me->GetThreatManager().doAddThreatNoRedirect(he, 999999.0f);
                                he->Kill(he);
                                sun->Kill(sun);
                                rook->Kill(rook);
                            }
                        }
                    }
                }
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_ARCANE_SPELLS:
                    me->SetPower(POWER_MANA, me->GetMaxPower(POWER_MANA));
                    if (Unit* vict = me->GetVictim())
                    {
                        switch (urand(0, 2))
                        {
                        case 0:
                            me->CastSpell(vict, SPELL_ARCANE_BARRAGE, false);
                            if (me->HasAura(102442))
                            {
                                me->RemoveAura(102442);
                            }
                            break;
                        case 1:
                            me->CastSpell(vict, SPELL_ARCANE_BLAST, false);
                            break;
                        case 2:
                            me->CastSpell(vict, SPELL_SCORCH, false);
                            break;
                        }
                    }

                    events.ScheduleEvent(EVENT_ARCANE_SPELLS, urand(1 * IN_MILLISECONDS, 2 * IN_MILLISECONDS));
                    break;
                case EVENT_TARGET_CHECK:
                {
                    if (me->GetMapId() == 960)
                    {
                        if (me->FindNearestCreature(56792, 30.0f))
                        {
                            //Force change target
                            if (me->FindNearestCreature(56792, 30.0f)->IsInCombat() && me->FindNearestCreature(56792, 30.0f)->GetHealthPct() >= 80)
                                me->GetThreatManager().doAddThreatNoRedirect(me->FindNearestCreature(56792, 30.0f), 999999.0f);
                        }
                        if (me->GetAreaId() == 6117)
                        {
                            if (me->FindNearestCreature(56511, 30.0f))
                            {
                                //Force change target
                                if (me->FindNearestCreature(56511, 30.0f)->IsInCombat() && me->FindNearestCreature(56511, 30.0f)->GetHealthPct() >= 80)
                                    me->GetThreatManager().doAddThreatNoRedirect(me->FindNearestCreature(56511, 30.0f), 999999.0f);
                            }
                        }
                    }
                    SiegeOfOrgrimmar_Strategy_TANKDPS();
                    events.ScheduleEvent(EVENT_TARGET_CHECK, 3 * IN_MILLISECONDS);
                    break;
                }
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_bot_dps_mageAI(creature);
    }
};

// Heal Bot 98003
class npc_bot_healer_druid : public CreatureScript
{
public:
    npc_bot_healer_druid() : CreatureScript("npc_bot_healer_druid") { }

    enum iSpells
    {
        SPELL_REGROWTH = 66067, // hEALS 55499 to 64500 and 11099 to 12900 every 3 seconds
        SPELL_REJUV = 66065,
        SPELL_LIFEBLOOM = 66093,
    };

    enum iEvents
    {
        EVENT_HEAL_CHECK_UNIT = 1,
        EVENT_HEAL_CHECK_PLAYER = 2,
    };

    struct npc_bot_healer_druidAI : public ScriptedAI
    {
        npc_bot_healer_druidAI(Creature* creature) : ScriptedAI(creature)
        { 
           SetCombatMovement(false);
        }

        EventMap events;

        void Reset() override
        {
            if (me->FindNearestPlayer(400.0f) && !me->IsInCombat())
            {
                me->GetMotionMaster()->MoveFollow(me->FindNearestPlayer(400.0f), 3.0f, 3.0f);
            }

            events.Reset();
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            if (me->GetMap())
            {
                if (me->GetMap()->IsDungeon())
                {
                    if (!me->HasAura(62552))
                    {
                        me->AddAura(62552, me); // Defend (30% damage reduction)
                        if (me->HasAura(62552))
                        {
                            me->GetAura(62552)->SetDuration(3000000);
                        }
                    }
                }
                if (me->GetMap()->IsRaid())
                {
                    if (!me->HasAura(62552))
                    {
                        me->AddAura(62552, me); // Defend (90% damage reduction)
                        if (me->HasAura(62552))
                        {
                            me->GetAura(62552)->SetStackAmount(2);
                            me->GetAura(62552)->SetDuration(3000000);
                        }
                    }
                }
                if (me->GetMapId() == 870 && me->GetZoneId() == 6757 && me->GetAreaId() == 6830)
                {
                    if (!me->HasAura(62552))
                    {
                        me->AddAura(62552, me); // Defend (60% damage reduction)
                        if (me->HasAura(62552))
                        {
                            me->GetAura(62552)->SetStackAmount(2);
                            me->GetAura(62552)->SetDuration(3000000);
                        }
                    }
                }
            }

            events.ScheduleEvent(EVENT_HEAL_CHECK_UNIT, 1000);
        }

        void JustDied(Unit* /*killer*/) override
        {
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_HEAL_CHECK_UNIT:
                    // Check all friendly units in a 30 yard range
                    events.ScheduleEvent(EVENT_HEAL_CHECK_UNIT, 750);
                    me->SetPower(POWER_MANA, me->GetMaxPower(POWER_MANA));
                    std::list<Player*> playerList;
                    GetPlayerListInGrid(playerList, me, 30.0f);
                    for (auto unit : playerList)
                    {
                        if (unit)
                        {
                            if (unit->IsPlayer() && !unit->isDead())
                            {
                                if (unit->GetHealthPct() <= 75)
                                {
                                    me->CastSpell(unit, SPELL_REGROWTH, true);
                                    return;
                                }
                                if (unit->GetHealthPct() >= 76 && unit->GetHealthPct() <= 95)
                                {
                                    if (!unit->HasAura(SPELL_REJUV))
                                    {
                                        me->CastSpell(unit, SPELL_REJUV, false);
                                        me->CastSpell(me, SPELL_REJUV, false);
                                    }
                                }
                            }
                        }
                    }

                    if (!me->FindNearestCreature(98000, 30.0f))
                        return;
                    if (!me->FindNearestCreature(98002, 30.0f))
                        return;

                    if (me->FindNearestCreature(98000, 30.0f) && !me->FindNearestCreature(98000, 30.0f)->isDead())
                    {
                        if (me->FindNearestCreature(98000, 30.0f) && me->FindNearestCreature(98000, 30.0f)->GetHealthPct() <= 80 && !me->FindNearestCreature(98000, 30.0f)->isDead())
                        {
                            if (me->FindNearestCreature(98000, 30.0f) && !me->FindNearestCreature(98000, 30.0f)->HasAura(SPELL_REJUV) && !me->FindNearestCreature(98000, 30.0f)->isDead())
                            {
                                me->CastSpell(me->FindNearestCreature(98000, 30.0f), SPELL_REJUV, true);
                            }
                            if (me->FindNearestCreature(98000, 30.0f) && !me->FindNearestCreature(98000, 30.0f)->HasAura(SPELL_LIFEBLOOM) && !me->FindNearestCreature(98000, 30.0f)->isDead())
                            {
                                me->CastSpell(me->FindNearestCreature(98000, 30.0f), SPELL_LIFEBLOOM, true);
                                if (me->FindNearestCreature(98000, 30.0f) && me->FindNearestCreature(98000, 30.0f)->HasAura(SPELL_LIFEBLOOM) && !me->FindNearestCreature(98000, 30.0f)->isDead())
                                {
                                    me->FindNearestCreature(98000, 30.0f)->GetAura(SPELL_LIFEBLOOM)->SetStackAmount(3);
                                }
                            }
                            me->CastSpell(me->FindNearestCreature(98000, 30.0f), SPELL_REGROWTH, false);
                            return;
                        }
                        if (me->FindNearestCreature(98000, 30.0f) && me->FindNearestCreature(98000, 30.0f)->GetHealthPct() >= 81 && me->FindNearestCreature(98000, 30.0f)->GetHealthPct() <= 95 && !me->FindNearestCreature(98000, 30.0f)->isDead())
                        {
                            if (me->FindNearestCreature(98000, 30.0f) && !me->FindNearestCreature(98000, 30.0f)->HasAura(SPELL_REJUV) && !me->FindNearestCreature(98000, 30.0f)->isDead())
                            {
                                me->CastSpell(me->FindNearestCreature(98000, 30.0f), SPELL_REJUV, false);
                            }
                        }
                    }
                    if (me->FindNearestCreature(98002, 30.0f) && !me->FindNearestCreature(98002, 30.0f)->isDead())
                    {
                        if (me->FindNearestCreature(98002, 30.0f) && me->FindNearestCreature(98002, 30.0f)->GetHealthPct() <= 40 && !me->FindNearestCreature(98002, 30.0f)->isDead())
                        {
                            if (me->FindNearestCreature(98002, 30.0f) && !me->FindNearestCreature(98002, 30.0f)->HasAura(SPELL_REJUV))
                            {
                                me->CastSpell(me->FindNearestCreature(98002, 30.0f), SPELL_REJUV, true);
                            }
                            if (me->FindNearestCreature(98002, 30.0f) && !me->FindNearestCreature(98002, 30.0f)->HasAura(SPELL_LIFEBLOOM) && !me->FindNearestCreature(98002, 30.0f)->isDead())
                            {
                                me->CastSpell(me->FindNearestCreature(98002, 30.0f), SPELL_LIFEBLOOM, true);
                                if (me->FindNearestCreature(98002, 30.0f) && me->FindNearestCreature(98002, 30.0f)->HasAura(SPELL_LIFEBLOOM) && !me->FindNearestCreature(98002, 30.0f)->isDead())
                                {
                                    me->FindNearestCreature(98002, 30.0f)->GetAura(SPELL_LIFEBLOOM)->SetStackAmount(3);
                                }
                            }
                            me->CastSpell(me->FindNearestCreature(98002, 30.0f), SPELL_REGROWTH, false);
                            return;
                        }
                        if (me->FindNearestCreature(98002, 30.0f) && me->FindNearestCreature(98002, 30.0f)->GetHealthPct() >= 41 && me->FindNearestCreature(98000, 30.0f)->GetHealthPct() <= 95 && !me->FindNearestCreature(98002, 30.0f)->isDead())
                        {
                            if (me->FindNearestCreature(98002, 30.0f) && !me->FindNearestCreature(98002, 30.0f)->HasAura(SPELL_REJUV) && !me->FindNearestCreature(98002, 30.0f)->isDead())
                            {
                                me->CastSpell(me->FindNearestCreature(98002, 30.0f), SPELL_REJUV, false);
                            }
                        }
                    }
                    break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_bot_healer_druidAI(creature);
    }
};

// Heal Bot 98004
class npc_bot_healer_priest : public CreatureScript
{
public:
    npc_bot_healer_priest() : CreatureScript("npc_bot_healer_priest") { }

    enum iSpells
    {
        SPELL_PENANCE = 69906,
        SPELL_RENEW = 46543,
        SPELL_FLASH_HEAL = 71782,
        SPELL_POWER_WORD_SHIELD = 20697,
    };

    enum iEvents
    {
        EVENT_HEAL_CHECK_UNIT = 1,
        EVENT_HEAL_CHECK_PLAYER = 2,
    };

    struct npc_bot_healer_priestAI : public ScriptedAI
    {
        npc_bot_healer_priestAI(Creature* creature) : ScriptedAI(creature)
        {
            SetCombatMovement(false);
        }

        EventMap events;

        void Reset() override
        {
            if (me->FindNearestPlayer(400.0f) && !me->IsInCombat())
            {
                me->GetMotionMaster()->MoveFollow(me->FindNearestPlayer(400.0f), 3.0f, 3.0f);
            }

            events.Reset();
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            if (me->GetMap())
            {
                if (me->GetMap()->IsDungeon())
                {
                    if (!me->HasAura(62552))
                    {
                        me->AddAura(62552, me); // Defend (30% damage reduction)
                        if (me->HasAura(62552))
                        {
                            me->GetAura(62552)->SetDuration(3000000);
                        }
                    }
                }
                if (me->GetMap()->IsRaid())
                {
                    if (!me->HasAura(62552))
                    {
                        me->AddAura(62552, me); // Defend (90% damage reduction)
                        if (me->HasAura(62552))
                        {
                            me->GetAura(62552)->SetStackAmount(2);
                            me->GetAura(62552)->SetDuration(3000000);
                        }
                    }
                }
                if (me->GetMapId() == 870 && me->GetZoneId() == 6757 && me->GetAreaId() == 6830)
                {
                    if (!me->HasAura(62552))
                    {
                        me->AddAura(62552, me); // Defend (60% damage reduction)
                        if (me->HasAura(62552))
                        {
                            me->GetAura(62552)->SetStackAmount(2);
                            me->GetAura(62552)->SetDuration(3000000);
                        }
                    }
                }
            }
            events.ScheduleEvent(EVENT_HEAL_CHECK_PLAYER, 1000);
            events.ScheduleEvent(EVENT_HEAL_CHECK_UNIT, 3000);
        }

        void JustDied(Unit* /*killer*/) override
        {
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_HEAL_CHECK_UNIT:
                    events.ScheduleEvent(EVENT_HEAL_CHECK_UNIT, 3000);

                    if (!me->FindNearestCreature(98000, 30.0f))
                        return;
                    if (!me->FindNearestCreature(98002, 30.0f))
                        return;

                    if (me->FindNearestCreature(98000, 30.0f) && !me->FindNearestCreature(98000, 30.0f)->isDead())
                    {
                        if (me->FindNearestCreature(98000, 30.0f) && me->FindNearestCreature(98000, 30.0f)->GetHealthPct() <= 80 && !me->FindNearestCreature(98000, 30.0f)->isDead())
                        {
                            if (me->FindNearestCreature(98000, 30.0f) && !me->FindNearestCreature(98000, 30.0f)->HasAura(SPELL_RENEW) && !me->FindNearestCreature(98000, 30.0f)->isDead())
                            {
                                me->CastSpell(me->FindNearestCreature(98000, 30.0f), SPELL_RENEW, true);
                            }
                            if (me->FindNearestCreature(98000, 30.0f) && !me->FindNearestCreature(98000, 30.0f)->HasAura(SPELL_POWER_WORD_SHIELD) && !me->FindNearestCreature(98000, 30.0f)->isDead())
                            {
                                me->FindNearestCreature(98000, 30.0f)->CastSpell(me->FindNearestCreature(98000, 30.0f), SPELL_POWER_WORD_SHIELD, true);
                            }
                            me->CastSpell(me->FindNearestCreature(98000, 30.0f), SPELL_FLASH_HEAL, true);
                        }
                        if (me->FindNearestCreature(98000, 30.0f) && me->FindNearestCreature(98000, 30.0f)->GetHealthPct() >= 81 && me->FindNearestCreature(98000, 30.0f)->GetHealthPct() <= 95 && !me->FindNearestCreature(98000, 30.0f)->isDead())
                        {
                            if (me->FindNearestCreature(98000, 30.0f) && !me->FindNearestCreature(98000, 30.0f)->HasAura(SPELL_RENEW) && !me->FindNearestCreature(98000, 30.0f)->isDead())
                            {
                                me->CastSpell(me->FindNearestCreature(98000, 30.0f), SPELL_RENEW, true);
                            }
                        }
                    }
                    if (me->FindNearestCreature(98002, 30.0f) && !me->FindNearestCreature(98002, 30.0f)->isDead())
                    {
                        if (me->FindNearestCreature(98002, 30.0f) && me->FindNearestCreature(98002, 30.0f)->GetHealthPct() <= 40 && !me->FindNearestCreature(98002, 30.0f)->isDead())
                        {
                            if (me->FindNearestCreature(98002, 30.0f) && !me->FindNearestCreature(98002, 30.0f)->HasAura(SPELL_RENEW) && !me->FindNearestCreature(98002, 30.0f)->isDead())
                            {
                                me->CastSpell(me->FindNearestCreature(98002, 30.0f), SPELL_RENEW, true);
                            }
                            if (me->FindNearestCreature(98002, 30.0f) && !me->FindNearestCreature(98002, 30.0f)->HasAura(SPELL_POWER_WORD_SHIELD) && !me->FindNearestCreature(98002, 30.0f)->isDead())
                            {
                                me->FindNearestCreature(98002, 30.0f)->CastSpell(me->FindNearestCreature(98002, 30.0f), SPELL_POWER_WORD_SHIELD, true);
                            }
                            me->CastSpell(me->FindNearestCreature(98002, 30.0f), SPELL_FLASH_HEAL, true);
                        }
                        if (me->FindNearestCreature(98002, 30.0f) && me->FindNearestCreature(98002, 30.0f)->GetHealthPct() >= 41 && me->FindNearestCreature(98002, 30.0f)->GetHealthPct() <= 95 && !me->FindNearestCreature(98002, 30.0f)->isDead())
                        {
                            if (me->FindNearestCreature(98002, 30.0f) && !me->FindNearestCreature(98002, 30.0f)->HasAura(SPELL_RENEW) && !me->FindNearestCreature(98002, 30.0f)->isDead())
                            {
                                me->CastSpell(me->FindNearestCreature(98002, 30.0f), SPELL_RENEW, false);
                            }
                        }
                    }
                    break;
                case EVENT_HEAL_CHECK_PLAYER:
                    // Check all friendly units in a 30 yard range
                    events.ScheduleEvent(EVENT_HEAL_CHECK_PLAYER, 750);
                    me->SetPower(POWER_MANA, me->GetMaxPower(POWER_MANA));
                    std::list<Player*> PriestplayerList;
                    GetPlayerListInGrid(PriestplayerList, me, 30.0f);
                    for (auto unit : PriestplayerList)
                    {
                        if (unit)
                        {
                            if (unit->IsPlayer() && !unit->isDead())
                            {
                                if (unit->GetHealthPct() <= 75)
                                {
                                    me->CastSpell(unit, SPELL_FLASH_HEAL, false);
                                    unit->AddAura(SPELL_POWER_WORD_SHIELD, unit);
                                    return;
                                }
                                if (unit->GetHealthPct() >= 76 && unit->GetHealthPct() <= 95)
                                {
                                    if (!unit->HasAura(SPELL_RENEW))
                                    {
                                        me->CastSpell(unit, SPELL_RENEW, false);
                                        me->CastSpell(me, SPELL_RENEW, false);
                                    }
                                    return;
                                }
                            }
                        }
                    }
                    break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_bot_healer_priestAI(creature);
    }
};

// A-I-O Bot 98008
class npc_bot_multi_dps : public CreatureScript
{
public:
    npc_bot_multi_dps() : CreatureScript("npc_bot_multi_dps") { }

    enum iSpells
    {
        //MAGE
        SPELL_ARCANE_BLAST = 101816,
        SPELL_ARCANE_BARRAGE = 145437,
        SPELL_SCORCH = 75412,
        // ROGUE
        SPELL_SINISTER_STRIKE = 112931,
        SPELL_MUTILATE = 145414,
        SPELL_DEADLY_POISON = 145420,
        // WARLOCK
        SPELL_AGONY = 112999,
        SPELL_CORRUPTION = 65810,
        SPELL_SHADOW_BOLT = 133655,
        SPELL_SUMMON_FELGUARD = 79958,
        // Priest
        SPELL_SHADOW_WORD_PAIN = 65541,
        SPELL_DEVOUR_PLAGUE = 138490,
        SPELL_MIND_FLAY = 85643,
        SPELL_SHADOW_FORM = 16592,
        SPELL_MIND_BLAST = 58850,
        //Warrior
        SPELL_HEROIC_STRIKE = 59035,
        SPELL_WHIRLWIND_DAMAGE = 138190,
        SPELL_THUNDER_CLAP = 145046,
        //Paladin
        SPELL_PALA_JUDGMENT = 41470,
        SPELL_PALA_SEAL_OF_BLOOD = 111351,
        SPELL_PALA_CRUSADER_STRIKE = 134822,
        SPELL_PALA_DIVINE_STORM = 135404,
        //ele shaman
        SPELL_SHAM_LAVA_BURST = 102475,
        SPELL_SHAM_FLAME_SHOCK = 43303,
        SPELL_SHAM_CHAIN_LIGHTNING = 136018,
        SPELL_SHAM_LIGHTNING_BOLT = 97474,
        //feral druid
        SPELL_DRU_CATFORM = 57655,
        SPELL_DRU_MANGLE = 57657,
        SPELL_DRU_RAKE = 125099,
        //Death knight
        SPELL_DK_ICY_TOCUH = 69916,
        SPELL_DK_PLAGUESTRIKE = 55321,
        SPELL_DK_BLOODSTRIKE = 60945,
        SPELL_DK_OBLITERATE = 72360,
        SPELL_DK_DEATH_DECAY = 61603,
    };

    enum iEvents
    {
        EVENT_ROGUE_SPELLS = 1,
        EVENT_MAGE_SPELLS = 2,
        EVENT_WARLOCK_SPELLS = 3,
        EVENT_SHADOW_PRIEST_SPELLS = 4,
        EVENT_WARRIOR_SPELLS = 5,
        EVENT_RET_PALADIN_SPELLS = 6,
        EVENT_ELE_SHAMAN_SPELLS = 7,
        EVENT_FERAL_DRUID_SPELLS = 8,
        EVENT_DEATH_KNIGHT_SPELLS = 9,
        EVENT_STRATEGY_CHECK = 10,
    };

    struct npc_bot_multi_dpsAI : public ScriptedAI
    {
        npc_bot_multi_dpsAI(Creature* creature) : ScriptedAI(creature)
        {
            me->bot_Class = urand(0, 8);
        }

        EventMap events;


        void Reset() override
        {
            me->SetControlled(false, UNIT_STATE_ROOT);
            if (me->FindNearestPlayer(400.0f) && !me->IsInCombat())
            {
                me->GetMotionMaster()->MoveFollow(me->FindNearestPlayer(400.0f), 3.0f, 3.0f);
            }

            events.Reset();
        }

        void SiegeOfOrgrimmar_Strategy_TANKDPS()
        {
            if (me->GetMapId() != 1136)
                return;

            if (me->GetMapId() == 1136)
            {
                if (me->HasAura(149164) || me->HasAura(149164)) // We are getting Frost AoE damage move.
                {
                    if (me->FindNearestPlayer(30.0f))
                    {
                        me->MonsterMoveWithSpeed(me->FindNearestPlayer(30.0f)->GetPositionX(), me->FindNearestPlayer(30.0f)->GetPositionY(), me->FindNearestPlayer(30.0f)->GetPositionZ(), 0.0f, true);
                    }
                    else
                    {
                        me->MonsterMoveWithSpeed(me->GetPositionX() + urand(2.0f, 4.0f), me->GetPositionY() + urand(4.0f, 5.0f), me->GetPositionZ(), 0.0f, false);
                    }
                }

                //Immerseius
                if (me->FindNearestCreature(71543, 100.0f) && me->FindNearestCreature(71603, 100.0f)) // Corrupted Sha
                {
                    // Sha puddles
                    if (me->FindNearestCreature(71543, 100.0f)->IsInCombat()) // Make sure we are in combat with boss
                    {
                        if (me->FindNearestCreature(71603, 100.0f))
                        {
                            me->GetThreatManager().resetAllAggro();
                            me->GetThreatManager().doAddThreatNoRedirect(me->FindNearestCreature(71603, 100.0f), 999999.0f);
                        }
                    }
                }
                //Protectors
                if (me->GetAreaId() == 6798)
                {
                    Unit* sun = me->FindNearestCreature(71480, 50.0f, false);
                    Unit* he = me->FindNearestCreature(71479, 50.0f, false);
                    Unit* rook = me->FindNearestCreature(71475, 50.0f, false);
                    if (sun && he && rook)
                    {
                        if (sun->IsInCombat())
                        {
                            me->GetThreatManager().resetAllAggro();
                            me->GetThreatManager().doAddThreatNoRedirect(sun, 999999.0f);
                            // We've damaged sun down to 5% but we need to make sure others are down as well.
                            if (sun->GetHealthPct() <= 5.0f && he->GetHealthPct() >= 5.0f && rook->GetHealthPct() >= 5.0f)
                            {
                                me->GetThreatManager().resetAllAggro();
                                me->GetThreatManager().doAddThreatNoRedirect(he, 999999.0f);
                            }
                            if (he->GetHealthPct() <= 5.0f && sun->GetHealthPct() <= 5.0f && rook->GetHealthPct() >= 5.0f)
                            {
                                me->GetThreatManager().resetAllAggro();
                                me->GetThreatManager().doAddThreatNoRedirect(rook, 999999.0f);
                            }
                            if (he->GetHealthPct() <= 5.0f && sun->GetHealthPct() <= 5.0f && rook->GetHealthPct() <= 5.0f)
                            {
                                me->GetThreatManager().resetAllAggro();
                                me->GetThreatManager().doAddThreatNoRedirect(he, 999999.0f);
                                he->Kill(he);
                                sun->Kill(sun);
                                rook->Kill(rook);
                            }
                        }
                    }
                }
            }
        }

        void JustEngagedWith(Unit* /*who*/) override
        {
            if (me->GetMap())
            {
                if (me->GetMap()->IsDungeon())
                {
                    if (!me->HasAura(62552))
                    {
                        me->AddAura(62552, me); // Defend (30% damage reduction)
                        if (me->HasAura(62552))
                        {
                            me->GetAura(62552)->SetDuration(3000000);
                        }
                    }
                }
                if (me->GetMap()->IsRaid())
                {
                    if (!me->HasAura(62552))
                    {
                        me->AddAura(62552, me); // Defend (90% damage reduction)
                        if (me->HasAura(62552))
                        {
                            me->GetAura(62552)->SetStackAmount(2);
                            me->GetAura(62552)->SetDuration(3000000);
                        }
                    }
                }
                if (me->GetMapId() == 870 && me->GetZoneId() == 6757 && me->GetAreaId() == 6830)
                {
                    if (!me->HasAura(62552))
                    {
                        me->AddAura(62552, me); // Defend (60% damage reduction)
                        if (me->HasAura(62552))
                        {
                            me->GetAura(62552)->SetStackAmount(2);
                            me->GetAura(62552)->SetDuration(3000000);
                        }
                    }
                }
            }

            if (me->GetMap())
            {
                if (me->GetMap()->IsDungeon())
                {
                    me->SetLevel(urand(85, 90));
                }
                if (me->GetMap()->IsScenario() || me->GetMap()->IsRaid())
                {
                    me->SetLevel(90);
                }
            }

            if (me->bot_Class == 0) // Rogue
            {
                me->SetDisplayId(51166);
                me->SetAttackTime(WeaponAttackType::BASE_ATTACK, 1200);
                me->SetAttackTime(WeaponAttackType::OFF_ATTACK, 2000);
                me->SetUInt32Value(UNIT_FIELD_VIRTUAL_ITEM_ID, 110883); // MH
                me->SetUInt32Value(UNIT_FIELD_VIRTUAL_ITEM_ID + 1, 110883); // OH
            }
            if (me->bot_Class == 1) // Mage
            {
                me->SetDisplayId(28186);
                me->SetUInt32Value(UNIT_FIELD_VIRTUAL_ITEM_ID, 120755); // MH
            }
            if (me->bot_Class == 2) // warlock
            {
                me->SetDisplayId(36879);
                me->SetUInt32Value(UNIT_FIELD_VIRTUAL_ITEM_ID, 120755); // MH
            }
            if (me->bot_Class == 3) // shadow priest
            {
                me->SetDisplayId(28191);
                me->SetUInt32Value(UNIT_FIELD_VIRTUAL_ITEM_ID, 120755); // MH
            }
            if (me->bot_Class == 4) // warr
            {
                me->SetDisplayId(28201);
                me->SetUInt32Value(UNIT_FIELD_VIRTUAL_ITEM_ID, 119482); // MH
            }
            if (me->bot_Class == 5) // ret pally
            {
                me->SetDisplayId(36883);
                me->SetUInt32Value(UNIT_FIELD_VIRTUAL_ITEM_ID, 119482); // MH
            }
            if (me->bot_Class == 6) // shaman
            {
                me->SetDisplayId(28195);
                me->SetUInt32Value(UNIT_FIELD_VIRTUAL_ITEM_ID, 119457); // MH
                me->SetUInt32Value(UNIT_FIELD_VIRTUAL_ITEM_ID + 1, 120225); // OH
            }
            if (me->bot_Class == 7) // feral
            {
                me->SetAttackTime(WeaponAttackType::BASE_ATTACK, 1200);
                me->SetDisplayId(28182);
            }
            if (me->bot_Class == 8) // dk
            {
                me->SetDisplayId(28180);
                me->SetUInt32Value(UNIT_FIELD_VIRTUAL_ITEM_ID, 119482); // MH
            }
            me->SetBaseWeaponDamage(WeaponAttackType::BASE_ATTACK, WeaponDamageRange::MINDAMAGE, 18554.0f);
            me->SetBaseWeaponDamage(WeaponAttackType::BASE_ATTACK, WeaponDamageRange::MAXDAMAGE, 26554.0f);

            if (me->bot_Class == 0) // Rogue
            {
                events.ScheduleEvent(EVENT_ROGUE_SPELLS, 750);
            }
            if (me->bot_Class == 1) // Mage
            {
                events.ScheduleEvent(EVENT_MAGE_SPELLS, 750);
                me->SetControlled(true, UNIT_STATE_ROOT);
            }
            if (me->bot_Class == 2) // Warlock
            {
                events.ScheduleEvent(EVENT_WARLOCK_SPELLS, 750);
                me->SetControlled(true, UNIT_STATE_ROOT);
                if (me->GetMinionGUID() == NULL)
                {
                    me->CastSpell(me, SPELL_SUMMON_FELGUARD, true);
                }
            }
            if (me->bot_Class == 3) // Shadow Priest
            {
                events.ScheduleEvent(EVENT_SHADOW_PRIEST_SPELLS, 750);
                me->SetControlled(true, UNIT_STATE_ROOT);
                if (!me->HasAura(SPELL_SHADOW_FORM))
                {
                    me->CastSpell(me, SPELL_SHADOW_FORM, false);
                }
            }
            if (me->bot_Class == 4) // WARRIOR
            {
                events.ScheduleEvent(EVENT_WARRIOR_SPELLS, 750);
            }
            if (me->bot_Class == 5) // RET PALADIN
            {
                events.ScheduleEvent(EVENT_RET_PALADIN_SPELLS, 750);
            }
            if (me->bot_Class == 6) // ELEMENTAL SHAMAN
            {
                events.ScheduleEvent(EVENT_ELE_SHAMAN_SPELLS, 750);
                me->SetControlled(true, UNIT_STATE_ROOT);
            }
            if (me->bot_Class == 7) // FERAL DRUID
            {
                if (!me->HasAura(SPELL_DRU_CATFORM))
                {
                    me->CastSpell(me, SPELL_DRU_CATFORM, false);
                }
                events.ScheduleEvent(EVENT_FERAL_DRUID_SPELLS, 750);
            }
            if (me->bot_Class == 8) // DEATH KNIGHT
            {
                events.ScheduleEvent(EVENT_DEATH_KNIGHT_SPELLS, 750);
            }
        }

        void JustDied(Unit* /*killer*/) override
        {
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_ROGUE_SPELLS:   
                    me->SetPower(POWER_MANA, me->GetMaxPower(POWER_MANA));
                    if (Unit* vict = me->GetVictim())
                    {
                        switch (urand(0, 1))
                        {
                        case 0:
                            me->CastSpell(vict, SPELL_SINISTER_STRIKE, false);

                            if (urand(0, 100) <= 10)
                            {
                                me->CastSpell(vict, SPELL_DEADLY_POISON, false);
                            }

                            break;
                        case 1:
                            me->CastSpell(vict, SPELL_MUTILATE, false);

                            if (urand(0, 100) <= 10)
                            {
                                me->CastSpell(vict, SPELL_DEADLY_POISON, false);
                            }
                            break;
                        }
                    }

                    events.ScheduleEvent(EVENT_ROGUE_SPELLS, urand(1 * IN_MILLISECONDS, 2 * IN_MILLISECONDS));
                    break;
                case EVENT_MAGE_SPELLS:
                    me->SetPower(POWER_MANA, me->GetMaxPower(POWER_MANA));
                    if (Unit* vict = me->GetVictim())
                    {
                        switch (urand(0, 2))
                        {
                        case 0:
                            me->CastSpell(vict, SPELL_ARCANE_BARRAGE, false);
                            if (me->HasAura(102442))
                            {
                                me->RemoveAura(102442);
                            }
                            break;
                        case 1:
                            me->CastSpell(vict, SPELL_ARCANE_BLAST, false);
                            break;
                        case 2:
                            me->CastSpell(vict, SPELL_SCORCH, false);
                            break;
                        }
                    }

                    events.ScheduleEvent(EVENT_MAGE_SPELLS, urand(1 * IN_MILLISECONDS, 2 * IN_MILLISECONDS));
                    break;
                case EVENT_WARLOCK_SPELLS:
                    me->SetPower(POWER_MANA, me->GetMaxPower(POWER_MANA));
                    if (Unit* vict = me->GetVictim())
                    {
                        switch (urand(0, 2))
                        {
                        case 0:
                            me->CastSpell(vict, SPELL_SHADOW_BOLT, false);
                            break;
                        case 1:
                            if (!vict->HasAura(SPELL_CORRUPTION))
                            {
                                me->CastSpell(vict, SPELL_CORRUPTION, true);
                            }
                            else
                            {
                                me->CastSpell(vict, SPELL_SHADOW_BOLT, false);
                            }
                            break;
                        case 2:
                            if (!vict->HasAura(SPELL_AGONY))
                            {
                                me->CastSpell(vict, SPELL_AGONY, true);
                            }
                            else
                            {
                                me->CastSpell(vict, SPELL_SHADOW_BOLT, false);
                            }
                            break;
                        }
                    }

                    events.ScheduleEvent(EVENT_WARLOCK_SPELLS, urand(1 * IN_MILLISECONDS, 2 * IN_MILLISECONDS));
                    break;
                case EVENT_SHADOW_PRIEST_SPELLS:
                    me->SetPower(POWER_MANA, me->GetMaxPower(POWER_MANA));
                    if (Unit* vict = me->GetVictim())
                    {
                        switch (urand(0, 2))
                        {
                        case 0:
                            me->CastSpell(vict, SPELL_MIND_BLAST, false);
                            break;
                        case 1:
                            if (!vict->HasAura(SPELL_SHADOW_WORD_PAIN))
                            {
                                me->CastSpell(vict, SPELL_SHADOW_WORD_PAIN, true);
                            }
                            else
                            {
                                me->CastSpell(vict, SPELL_MIND_FLAY, false);
                            }
                            break;
                        case 2:
                            if (!vict->HasAura(SPELL_DEVOUR_PLAGUE))
                            {
                                me->CastSpell(vict, SPELL_DEVOUR_PLAGUE, false);
                            }
                            else
                            {
                                me->CastSpell(vict, SPELL_MIND_FLAY, false);
                            }
                            break;
                        }
                    }

                    events.ScheduleEvent(EVENT_SHADOW_PRIEST_SPELLS, urand(1 * IN_MILLISECONDS, 2 * IN_MILLISECONDS));
                    break;
                case EVENT_WARRIOR_SPELLS:
                    me->SetPower(POWER_MANA, me->GetMaxPower(POWER_MANA));
                    if (Unit* vict = me->GetVictim())
                    {
                        switch (urand(0, 2))
                        {
                        case 0:
                            me->CastSpell(vict, SPELL_HEROIC_STRIKE, false);
                            break;
                        case 1:
                            me->CastSpell(vict, SPELL_WHIRLWIND_DAMAGE, false);
                            break;
                        case 2:
                            me->CastSpell(vict, SPELL_THUNDER_CLAP, false);
                            break;
                        }
                    }

                    events.ScheduleEvent(EVENT_WARRIOR_SPELLS, urand(2 * IN_MILLISECONDS, 3 * IN_MILLISECONDS));
                    break;
                case EVENT_RET_PALADIN_SPELLS:
                    me->SetPower(POWER_MANA, me->GetMaxPower(POWER_MANA));
                    if (Unit* vict = me->GetVictim())
                    {
                        switch (urand(0, 3))
                        {
                        case 0:
                            me->CastSpell(vict, SPELL_PALA_JUDGMENT, false);
                            break;
                        case 1:
                            me->CastSpell(vict, SPELL_PALA_CRUSADER_STRIKE, false);
                            break;
                        case 2:
                            me->CastSpell(vict, SPELL_PALA_DIVINE_STORM, true);
                            me->CastSpell(vict, SPELL_WHIRLWIND_DAMAGE, true);
                            break;
                        case 3:
                            me->CastSpell(me, SPELL_PALA_SEAL_OF_BLOOD, true);
                            break;
                        }
                    }

                    events.ScheduleEvent(EVENT_RET_PALADIN_SPELLS, urand(2 * IN_MILLISECONDS, 3 * IN_MILLISECONDS));
                    break;
                case EVENT_ELE_SHAMAN_SPELLS:
                    me->SetPower(POWER_MANA, me->GetMaxPower(POWER_MANA));
                    if (Unit* vict = me->GetVictim())
                    {
                        switch (urand(0, 3))
                        {
                        case 0:
                            me->CastSpell(vict, SPELL_SHAM_FLAME_SHOCK, false);
                            break;
                        case 1:
                            me->CastSpell(vict, SPELL_SHAM_LAVA_BURST, false);
                            break;
                        case 2:
                            me->CastSpell(vict, SPELL_SHAM_CHAIN_LIGHTNING, true);
                            break;
                        case 3:
                            me->CastSpell(me, SPELL_SHAM_LIGHTNING_BOLT, true);
                            break;
                        }
                    }

                    events.ScheduleEvent(EVENT_ELE_SHAMAN_SPELLS, urand(1 * IN_MILLISECONDS, 2 * IN_MILLISECONDS));
                    break;
                case EVENT_FERAL_DRUID_SPELLS:
                    me->SetPower(POWER_MANA, me->GetMaxPower(POWER_MANA));
                    if (Unit* vict = me->GetVictim())
                    {
                        switch (urand(0, 1))
                        {
                        case 0:
                            me->CastSpell(vict, SPELL_DRU_MANGLE, false);
                            break;
                        case 1:
                            if (!me->HasAura(SPELL_DRU_RAKE))
                            {
                                me->CastSpell(vict, SPELL_DRU_RAKE, false);
                            }
                            else
                            {
                                me->CastSpell(vict, SPELL_DRU_MANGLE, false);
                            }
                            break;
                        }
                    }

                    events.ScheduleEvent(EVENT_FERAL_DRUID_SPELLS, urand(2 * IN_MILLISECONDS, 3 * IN_MILLISECONDS));
                    break;
                case EVENT_DEATH_KNIGHT_SPELLS:
                    me->SetPower(POWER_MANA, me->GetMaxPower(POWER_MANA));
                    if (Unit* vict = me->GetVictim())
                    {
                        switch (urand(0, 4))
                        {
                        case 0:
                            me->CastSpell(vict, SPELL_DK_ICY_TOCUH, false);
                            break;
                        case 1:
                            me->CastSpell(vict, SPELL_DK_BLOODSTRIKE, false);
                            break;
                        case 2:
                            me->CastSpell(vict, SPELL_DK_PLAGUESTRIKE, false);
                            break;
                        case 3:
                            me->CastSpell(vict, SPELL_DK_OBLITERATE, false);
                            break;
                        case 4:
                            me->CastSpell(vict, SPELL_DK_DEATH_DECAY, false);
                            break;
                        }
                    }

                    events.ScheduleEvent(EVENT_DEATH_KNIGHT_SPELLS, urand(2 * IN_MILLISECONDS, 3 * IN_MILLISECONDS));
                    break;
                    case EVENT_STRATEGY_CHECK:
                        SiegeOfOrgrimmar_Strategy_TANKDPS();
                        events.ScheduleEvent(EVENT_STRATEGY_CHECK, 4000);
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_bot_multi_dpsAI(creature);
    }
};

void AddSC_elwynn_forest()
{
    new npc_bot_multi_dps();
    new npc_shop_guy();
    new npc_bot_dps_rogue();
    new npc_bot_healer_priest();
    new npc_bot_healer_druid();
    new npc_bot_dps_mage();
    new npc_bot_tank();
    new npc_bot_menu_dunraid();
    new npc_catchup_leveler();
    RegisterCreatureAI(npc_stormwind_infantry);
    new creature_script<npc_blackrock_battle_worg>("npc_blackrock_battle_worg");
    RegisterCreatureAI(npc_brother_paxton);
    RegisterCreatureAI(npc_blackrock_spy);
    new creature_script<npc_goblin_assassin>("npc_goblin_assassin");
    new creature_script<npc_blackrock_invader>("npc_blackrock_invader");
    new npc_king_varian_wrynn();
    new npc_varian_wrynn_alliance_way_quest();
    new npc_ayisa_jojo_alliance_way_quest();
    new spell_script<spell_summ_varian_alliance_way>("spell_summ_varian_alliance_way");
    new creature_script<npc_hogger>("npc_hogger");
    new creature_script<npc_minion_of_hogger>("npc_minion_of_hogger");
    new quest_extinguishing_hope();
}
