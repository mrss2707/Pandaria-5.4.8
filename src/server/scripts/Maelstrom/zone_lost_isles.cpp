
#include "ScriptPCH.h"

// 38387
class npc_sassy_hardwrench : public CreatureScript {
public:
    npc_sassy_hardwrench() : CreatureScript("npc_sassy_hardwrench") {}

    bool OnQuestAccept(Player* player, Creature* /*creature*/, const Quest* quest) override {
        if (quest->GetQuestId() == 25251) {
            if (Creature* t = player->SummonCreature(39592, player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(),
                player->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3 * IN_MILLISECONDS))
                t->setActive(1);
        }
        return true;
    }
};

void AddSC_lost_isles() {
    new npc_sassy_hardwrench();
}
