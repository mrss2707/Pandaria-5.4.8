#ifndef _PLAYERBOT_DPSASSISTSTRATEGY_H
#define _PLAYERBOT_DPSASSISTSTRATEGY_H

#include "NonCombatStrategy.h"

class PlayerbotAI;

class DpsAssistStrategy : public NonCombatStrategy
{
public:
    DpsAssistStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI) {}

    std::string const getName() override { return "dps assist"; }
    // uint32 GetType() const override { return STRATEGY_TYPE_DPS; }
    void InitTriggers(std::vector<TriggerNode*>& triggers) override;
};

class DpsAoeStrategy : public NonCombatStrategy
{
public:
    DpsAoeStrategy(PlayerbotAI* botAI) : NonCombatStrategy(botAI) {}

    std::string const getName() override { return "dps aoe"; }
    uint32 GetType() const override { return STRATEGY_TYPE_DPS; }
    void InitTriggers(std::vector<TriggerNode*>& triggers) override;
};

#endif
