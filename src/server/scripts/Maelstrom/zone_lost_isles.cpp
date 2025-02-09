
#include "ScriptPCH.h"

// 38387
class npc_sassy_hardwrench : public CreatureScript {
public:
    npc_sassy_hardwrench() : CreatureScript("npc_sassy_hardwrench") {}

    bool OnQuestAccept(Player* player, Creature* /*creature*/, const Quest* quest) override {
        /*
        if (quest->GetQuestId() == 25265) {
            player->AddAura(72971, player);
            player->CastSpell(player, 67789, true);
            player->AddAura(90418, player);
            player->GetMotionMaster()->MoveJump(2352.31f, 2483.97f, 13.0f, 15.0f, 20.0f, 150.0f);
        }

        if (quest->GetQuestId() == 25066) {
            player->CastSpell(nullptr, 73430);
            if (Unit* vehicle = player->FindNearestCreature(39074, 50.0, true)) {
                vehicle->SetUnitMovementFlags(75497984);
                vehicle->SetExtraUnitMovementFlags(276);
                vehicle->SetFlying(true);
                vehicle->CanFly();
                //vehicle->SetCanTransitionBetweenSwimAndFly(true);
            }
        }
        */
        if (quest->GetQuestId() == 25251) {
            if (Creature* t = player->SummonCreature(39592, player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(),
                player->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3 * IN_MILLISECONDS))
                t->setActive(1);
        }

        return true;
    }
    
    //bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*sender*/, uint32 /*action*/) override {
    //    if (player->HasQuest(25266)) {
    //        player->TeleportTo(1468, Position(-5012.0f, 13.0f, 3.26f));
    //    }
    //    return true;
    //}
};

void AddSC_lost_isles() {
    new npc_sassy_hardwrench();
}
