//
// Created by sillv on 10/17/2024.
//

#ifndef REAGENTBANK_H
#define REAGENTBANK_H
#define MAX_OPTIONS 23
#define MAX_PAGE_NUMBER 700 // Values higher than this are considered Item IDs
#define NPC_TEXT_ID 4259 // Pre-existing NPC text

enum GossipItemType : uint8
{
    DEPOSIT_ALL_REAGENTS = 16,
    MAIN_MENU = 17
};
#endif //REAGENTBANK_H
