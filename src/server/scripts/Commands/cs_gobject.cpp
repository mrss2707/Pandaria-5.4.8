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

/* ScriptData
Name: gobject_commandscript
%Complete: 100
Comment: All gobject related commands
Category: commandscripts
EndScriptData */

#include "ScriptMgr.h"
#include "GameEventMgr.h"
#include "ObjectMgr.h"
#include "PoolMgr.h"
#include "MapManager.h"
#include "Chat.h"
#include "Language.h"
#include "Player.h"
#include "Opcodes.h"
#include "Transport.h"

class gobject_commandscript : public CommandScript
{
public:
    gobject_commandscript() : CommandScript("gobject_commandscript") { }

    std::vector<ChatCommand> GetCommands() const
    {
        static std::vector<ChatCommand> gobjectAddCommandTable =
        {
            { "temp",       SEC_GAMEMASTER, false,  &HandleGameObjectAddTempCommand,    },
            { "",           SEC_GAMEMASTER, false,  &HandleGameObjectAddCommand,        },
        };
        static std::vector<ChatCommand> gobjectSetCommandTable =
        {
            { "phase",      SEC_GAMEMASTER, false,  &HandleGameObjectSetPhaseCommand,   },
            { "phaseid",    SEC_GAMEMASTER, false,  &HandleGameObjectSetPhaseIDCommand, },
            { "state",      SEC_GAMEMASTER, false,  &HandleGameObjectSetStateCommand,   },
        };
        static std::vector<ChatCommand> gobjectCommandTable =
        {
            { "activate",   SEC_GAMEMASTER, false,  &HandleGameObjectActivateCommand,   },
            { "delete",     SEC_GAMEMASTER, false,  &HandleGameObjectDeleteCommand,     },
            { "info",       SEC_GAMEMASTER, false,  &HandleGameObjectInfoCommand,       },
            { "move",       SEC_GAMEMASTER, false,  &HandleGameObjectMoveCommand,       },
            { "near",       SEC_GAMEMASTER, false,  &HandleGameObjectNearCommand,       },
            { "target",     SEC_GAMEMASTER, false,  &HandleGameObjectTargetCommand,     },
            { "turn",       SEC_GAMEMASTER, false,  &HandleGameObjectTurnCommand,       },
            { "add",        SEC_GAMEMASTER, false,  gobjectAddCommandTable              },
            { "set",        SEC_GAMEMASTER, false,  gobjectSetCommandTable              },
            
        };
        static std::vector<ChatCommand> commandTable =
        {
            { "gobject",    SEC_GAMEMASTER, false,  gobjectCommandTable                 },
        };
        return commandTable;
    }

    static bool HandleGameObjectActivateCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        char* id = handler->extractKeyFromLink((char*)args, "Hgameobject");
        if (!id)
            return false;

        uint32 guidLow = atoi(id);
        if (!guidLow)
            return false;

        GameObject* object = NULL;

        // by DB guid
        if (GameObjectData const* goData = sObjectMgr->GetGOData(guidLow))
            object = handler->GetObjectGlobalyWithGuidOrNearWithDbGuid(guidLow, goData->id);

        if (!object)
        {
            handler->PSendSysMessage(LANG_COMMAND_OBJNOTFOUND, guidLow);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // Activate
        object->SetLootState(GO_READY);
        object->UseDoorOrButton(10000, false, handler->GetSession()->GetPlayer());

        handler->PSendSysMessage("Object activated!");

        return true;
    }

    //spawn go
    static bool HandleGameObjectAddCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        // number or [name] Shift-click form |color|Hgameobject_entry:go_id|h[name]|h|r
        char* id = handler->extractKeyFromLink((char*)args, "Hgameobject_entry");
        if (!id)
            return false;

        uint32 objectId = atol(id);
        if (!objectId)
            return false;

        char* spawntimeSecs = strtok(NULL, " ");

        const GameObjectTemplate* objectInfo = sObjectMgr->GetGameObjectTemplate(objectId);

        if (!objectInfo)
        {
            handler->PSendSysMessage(LANG_GAMEOBJECT_NOT_EXIST, objectId);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (objectInfo->displayId && !sGameObjectDisplayInfoStore.LookupEntry(objectInfo->displayId))
        {
            // report to DB errors log as in loading case
            TC_LOG_ERROR("sql.sql", "Gameobject (Entry %u GoType: %u) have invalid displayId (%u), not spawned.", objectId, objectInfo->type, objectInfo->displayId);
            handler->PSendSysMessage(LANG_GAMEOBJECT_HAVE_INVALID_DATA, objectId);
            handler->SetSentErrorMessage(true);
            return false;
        }

        Player* player = handler->GetSession()->GetPlayer();
        float x = float(player->GetPositionX());
        float y = float(player->GetPositionY());
        float z = float(player->GetPositionZ());
        float o = float(player->GetOrientation());
        Map* map = player->GetMap();

        GameObject* object = new GameObject;
        if (!object->Create(map->GenerateLowGuid<HighGuid::GameObject>(), objectInfo->entry, map, player->GetPhaseMgr().GetPhaseMaskForSpawn(), x, y, z, o, { }, 0, GO_STATE_READY))
        {
            delete object;
            return false;
        }

        for (auto phase : player->GetPhases())
            object->SetPhased(phase, false, true);

        if (spawntimeSecs)
        {
            uint32 value = atoi((char*)spawntimeSecs);
            object->SetRespawnTime(value);
        }

        // fill the gameobject data and save to the db
        object->SaveToDB(map->GetId(), (1 << map->GetSpawnMode()), player->GetPhaseMgr().GetPhaseMaskForSpawn());
        ObjectGuid::LowType spawnId = object->GetDBTableGUIDLow();

        // this will generate a new guid if the object is in an instance
        if (!object->LoadGameObjectFromDB(spawnId, map))
        {
            delete object;
            return false;
        }

        /// @todo is it really necessary to add both the real and DB table guid here ?
        sObjectMgr->AddGameobjectToGrid(spawnId, sObjectMgr->GetGOData(spawnId));

        handler->PSendSysMessage(LANG_GAMEOBJECT_ADD, objectId, objectInfo->name.c_str(), spawnId, x, y, z);
        return true;
    }

    // add go, temp only
    static bool HandleGameObjectAddTempCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        char* id = strtok((char*)args, " ");
        if (!id)
            return false;

        Player* player = handler->GetSession()->GetPlayer();

        char* spawntime = strtok(NULL, " ");
        uint32 spawntm = 300;

        if (spawntime)
            spawntm = atoi((char*)spawntime);

        float x = player->GetPositionX();
        float y = player->GetPositionY();
        float z = player->GetPositionZ();
        float ang = player->GetOrientation();


        uint32 objectId = atoi(id);

        player->SummonGameObject(objectId, x, y, z, ang, { }, spawntm);

        return true;
    }

    static bool HandleGameObjectTargetCommand(ChatHandler* handler, char const* args)
    {
        Player* player = handler->GetSession()->GetPlayer();
        QueryResult result;
        GameEventMgr::ActiveEvents const& activeEventsList = sGameEventMgr->GetActiveEventList();

        if (*args)
        {
            // number or [name] Shift-click form |color|Hgameobject_entry:go_id|h[name]|h|r
            char* id = handler->extractKeyFromLink((char*)args, "Hgameobject_entry");
            if (!id)
                return false;

            uint32 objectId = atol(id);

            if (objectId)
                result = WorldDatabase.PQuery("SELECT guid, id, position_x, position_y, position_z, orientation, map, phaseMask, (POW(position_x - '%f', 2) + POW(position_y - '%f', 2) + POW(position_z - '%f', 2)) AS order_ FROM gameobject WHERE map = '%i' AND id = '%u' ORDER BY order_ ASC LIMIT 1",
                player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), player->GetMapId(), objectId);
            else
            {
                std::string name = id;
                WorldDatabase.EscapeString(name);
                result = WorldDatabase.PQuery(
                    "SELECT guid, id, position_x, position_y, position_z, orientation, map, phaseMask, (POW(position_x - %f, 2) + POW(position_y - %f, 2) + POW(position_z - %f, 2)) AS order_ "
                    "FROM gameobject, gameobject_template WHERE gameobject_template.entry = gameobject.id AND map = %i AND name like '%%%s%%' ORDER BY order_ ASC LIMIT 1",
                    player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), player->GetMapId(), name.c_str());
            }
        }
        else
        {
            std::ostringstream eventFilter;
            eventFilter << " AND (eventEntry IS NULL ";
            bool initString = true;

            for (GameEventMgr::ActiveEvents::const_iterator itr = activeEventsList.begin(); itr != activeEventsList.end(); ++itr)
            {
                if (initString)
                {
                    eventFilter  <<  "OR eventEntry IN (" << *itr;
                    initString = false;
                }
                else
                    eventFilter << ',' << *itr;
            }

            if (!initString)
                eventFilter << "))";
            else
                eventFilter << ')';

            result = WorldDatabase.PQuery("SELECT gameobject.guid, id, position_x, position_y, position_z, orientation, map, phaseMask, "
                "(POW(position_x - %f, 2) + POW(position_y - %f, 2) + POW(position_z - %f, 2)) AS order_ FROM gameobject "
                "LEFT OUTER JOIN game_event_gameobject on gameobject.guid = game_event_gameobject.guid WHERE map = '%i' %s ORDER BY order_ ASC LIMIT 10",
                handler->GetSession()->GetPlayer()->GetPositionX(), handler->GetSession()->GetPlayer()->GetPositionY(), handler->GetSession()->GetPlayer()->GetPositionZ(),
                handler->GetSession()->GetPlayer()->GetMapId(), eventFilter.str().c_str());
        }

        if (!result)
        {
            handler->SendSysMessage(LANG_COMMAND_TARGETOBJNOTFOUND);
            return true;
        }

        bool found = false;
        float x, y, z, o;
        uint32 guidLow, id, phase;
        uint16 mapId;
        uint32 poolId;

        do
        {
            Field* fields = result->Fetch();
            guidLow = fields[0].GetUInt32();
            id =      fields[1].GetUInt32();
            x =       fields[2].GetFloat();
            y =       fields[3].GetFloat();
            z =       fields[4].GetFloat();
            o =       fields[5].GetFloat();
            mapId =   fields[6].GetUInt16();
            phase =   fields[7].GetUInt32();
            poolId =  sPoolMgr->IsPartOfAPool<GameObject>(guidLow);
            if (!poolId || sPoolMgr->IsSpawnedObject<GameObject>(handler->GetSession()->GetPlayer()->GetMap()->GetPoolData(), guidLow))
                found = true;
        } while (result->NextRow() && !found);

        if (!found)
        {
            handler->PSendSysMessage(LANG_GAMEOBJECT_NOT_EXIST, id);
            return false;
        }

        GameObjectTemplate const* objectInfo = sObjectMgr->GetGameObjectTemplate(id);

        if (!objectInfo)
        {
            handler->PSendSysMessage(LANG_GAMEOBJECT_NOT_EXIST, id);
            return false;
        }

        GameObject* target = handler->GetSession()->GetPlayer()->GetMap()->GetGameObject(ObjectGuid(HighGuid::GameObject, id, guidLow));

        handler->PSendSysMessage(LANG_GAMEOBJECT_DETAIL, guidLow, objectInfo->name.c_str(), guidLow, id, x, y, z, mapId, o, phase);

        if (target)
        {
            int32 curRespawnDelay = int32(target->GetRespawnTimeEx() - time(NULL));
            if (curRespawnDelay < 0)
                curRespawnDelay = 0;

            std::string curRespawnDelayStr = secsToTimeString(curRespawnDelay, true);
            std::string defRespawnDelayStr = secsToTimeString(target->GetRespawnDelay(), true);

            handler->PSendSysMessage(LANG_COMMAND_RAWPAWNTIMES, defRespawnDelayStr.c_str(), defRespawnDelayStr.c_str(), curRespawnDelayStr.c_str());
        }
        return true;
    }

    //delete object by selection or guid
    static bool HandleGameObjectDeleteCommand(ChatHandler* handler, char const* args)
    {
        // number or [name] Shift-click form |color|Hgameobject:go_guid|h[name]|h|r
        char* id = handler->extractKeyFromLink((char*)args, "Hgameobject");
        if (!id)
            return false;

        uint32 guidLow = atoi(id);
        if (!guidLow)
            return false;

        GameObject* object = NULL;

        // by DB guid
        if (GameObjectData const* gameObjectData = sObjectMgr->GetGOData(guidLow))
            object = handler->GetObjectGlobalyWithGuidOrNearWithDbGuid(guidLow, gameObjectData->id);

        if (!object)
        {
            handler->PSendSysMessage(LANG_COMMAND_OBJNOTFOUND, guidLow);
            handler->SetSentErrorMessage(true);
            return false;
        }

        ObjectGuid ownerGuid = object->GetOwnerGUID();
        if (ownerGuid)
        {
            Unit* owner = ObjectAccessor::GetUnit(*handler->GetSession()->GetPlayer(), ownerGuid);
            if (!owner || !ownerGuid.IsPlayer())
            {
                handler->PSendSysMessage(LANG_COMMAND_DELOBJREFERCREATURE, ownerGuid.GetCounter(), object->GetGUID().GetCounter());
                handler->SetSentErrorMessage(true);
                return false;
            }

            owner->RemoveGameObject(object, false);
        }

        object->SetRespawnTime(0);                                 // not save respawn time
        object->Delete();
        object->DeleteFromDB();

        handler->PSendSysMessage(LANG_COMMAND_DELOBJMESSAGE, object->GetGUID().GetCounter());

        return true;
    }

    //turn selected object
    static bool HandleGameObjectTurnCommand(ChatHandler* handler, char const* args)
    {
        // number or [name] Shift-click form |color|Hgameobject:go_id|h[name]|h|r
        char* id = handler->extractKeyFromLink((char*)args, "Hgameobject");
        if (!id)
            return false;

        uint32 guidLow = atoi(id);
        if (!guidLow)
            return false;

        GameObject* object = NULL;

        // by DB guid
        if (GameObjectData const* gameObjectData = sObjectMgr->GetGOData(guidLow))
            object = handler->GetObjectGlobalyWithGuidOrNearWithDbGuid(guidLow, gameObjectData->id);

        if (!object)
        {
            handler->PSendSysMessage(LANG_COMMAND_OBJNOTFOUND, guidLow);
            handler->SetSentErrorMessage(true);
            return false;
        }

        char* orientation = strtok(NULL, " ");
        float o;

        if (orientation)
            o = (float)atof(orientation);
        else
        {
            Player* player = handler->GetSession()->GetPlayer();
            o = player->GetOrientation();
        }

        object->Relocate(object->GetPositionX(), object->GetPositionY(), object->GetPositionZ(), o);
        object->DestroyForNearbyPlayers();
        object->UpdateObjectVisibility();

        object->SaveToDB();
        object->Refresh();

        handler->PSendSysMessage(LANG_COMMAND_TURNOBJMESSAGE, object->GetGUID().GetCounter(), object->GetGOInfo()->name.c_str(), object->GetGUID().GetCounter(), o);

        return true;
    }

    //move selected object
    static bool HandleGameObjectMoveCommand(ChatHandler* handler, char const* args)
    {
        // number or [name] Shift-click form |color|Hgameobject:go_guid|h[name]|h|r
        char* id = handler->extractKeyFromLink((char*)args, "Hgameobject");
        if (!id)
            return false;

        uint32 guidLow = atoi(id);
        if (!guidLow)
            return false;

        GameObject* object = NULL;

        // by DB guid
        if (GameObjectData const* gameObjectData = sObjectMgr->GetGOData(guidLow))
            object = handler->GetObjectGlobalyWithGuidOrNearWithDbGuid(guidLow, gameObjectData->id);

        if (!object)
        {
            handler->PSendSysMessage(LANG_COMMAND_OBJNOTFOUND, guidLow);
            handler->SetSentErrorMessage(true);
            return false;
        }

        char* toX = strtok(NULL, " ");
        char* toY = strtok(NULL, " ");
        char* toZ = strtok(NULL, " ");

        if (!toX)
        {
            Player* player = handler->GetSession()->GetPlayer();
            object->Relocate(player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), object->GetOrientation());
            object->DestroyForNearbyPlayers();
            object->UpdateObjectVisibility();
        }
        else
        {
            if (!toY || !toZ)
                return false;

            float x = (float)atof(toX);
            float y = (float)atof(toY);
            float z = (float)atof(toZ);

            if (!MapManager::IsValidMapCoord(object->GetMapId(), x, y, z))
            {
                handler->PSendSysMessage(LANG_INVALID_TARGET_COORD, x, y, object->GetMapId());
                handler->SetSentErrorMessage(true);
                return false;
            }

            object->Relocate(x, y, z, object->GetOrientation());
            object->DestroyForNearbyPlayers();
            object->UpdateObjectVisibility();
        }

        object->SaveToDB();
        object->Refresh();

        handler->PSendSysMessage(LANG_COMMAND_MOVEOBJMESSAGE, object->GetGUID().GetCounter(), object->GetGOInfo()->name.c_str(), object->GetGUID().GetCounter());

        return true;
    }

    //set phasemask for selected object
    static bool HandleGameObjectSetPhaseCommand(ChatHandler* handler, char const* args)
    {
        // number or [name] Shift-click form |color|Hgameobject:go_id|h[name]|h|r
        char* id = handler->extractKeyFromLink((char*)args, "Hgameobject");
        if (!id)
            return false;

        uint32 guidLow = atoi(id);
        if (!guidLow)
            return false;

        GameObject* object = NULL;

        // by DB guid
        if (GameObjectData const* gameObjectData = sObjectMgr->GetGOData(guidLow))
            object = handler->GetObjectGlobalyWithGuidOrNearWithDbGuid(guidLow, gameObjectData->id);

        if (!object)
        {
            handler->PSendSysMessage(LANG_COMMAND_OBJNOTFOUND, guidLow);
            handler->SetSentErrorMessage(true);
            return false;
        }

        char* phase = strtok (NULL, " ");
        uint32 phaseMask = phase ? atoi(phase) : 0;
        if (phaseMask == 0)
        {
            handler->SendSysMessage(LANG_BAD_VALUE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        object->SetPhaseMask(phaseMask, true);
        object->SaveToDB();
        return true;
    }

    //go phase handling
    //change phase of gameobject
    static bool HandleGameObjectSetPhaseIDCommand(ChatHandler* handler, char const* args)
    {
        // number or [name] Shift-click form |color|Hgameobject:go_id|h[name]|h|r
        char* id = handler->extractKeyFromLink((char*)args, "Hgameobject");
        if (!id)
            return false;

        uint32 phase = (uint32)atoi((char*)args);

        uint32 guidLow = atoi(id);
        if (!guidLow)
            return false;

        GameObject* object = nullptr;

        // by DB guid
        if (GameObjectData const* gameObjectData = sObjectMgr->GetGOData(guidLow))
            object = handler->GetObjectGlobalyWithGuidOrNearWithDbGuid(guidLow, gameObjectData->id);

        if (!object)
        {
            handler->PSendSysMessage(LANG_COMMAND_OBJNOTFOUND, guidLow);
            handler->SetSentErrorMessage(true);
            return false;
        }

        object->ClearPhases();
        object->SetPhased(phase, true, true);

        object->SaveToDB();
        return true;
    }

    static bool HandleGameObjectNearCommand(ChatHandler* handler, char const* args)
    {
        uint32 dist = 0;
        uint32 goEntry = 0;
        if (!*args)
            dist = 10;
        else
        {
            Tokenizer tok{ args, ' ' };
            uint32 dist = std::strtoul(tok[0], nullptr, 10);
            if (tok.size() == 2)
                goEntry = std::strtoul(tok[1], nullptr, 10);
        }

        float distance = !dist ? 10.0f : (float)dist;
        uint32 count = 0;

        Player* player = handler->GetSession()->GetPlayer();
        bool moTransport = player->GetTransport() && player->GetTransport()->GetGoType() == GAMEOBJECT_TYPE_MO_TRANSPORT;
        uint32  mapId = moTransport ? player->GetTransport()->GetGOInfo()->moTransport.mapID : player->GetMapId();
        Position pos = moTransport ? player->m_movementInfo.transport.pos : *player;

        WorldDatabasePreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_GAMEOBJECT_NEAREST);
        stmt->setFloat(0, pos.GetPositionX());
        stmt->setFloat(1, pos.GetPositionY());
        stmt->setFloat(2, pos.GetPositionZ());
        stmt->setUInt32(3, mapId);
        stmt->setFloat(4, pos.GetPositionX());
        stmt->setFloat(5, pos.GetPositionY());
        stmt->setFloat(6, pos.GetPositionZ());
        stmt->setFloat(7, distance * distance);
        PreparedQueryResult result = WorldDatabase.Query(stmt);

        if (result)
        {
            do
            {
                Field* fields = result->Fetch();
                uint32 guid = fields[0].GetUInt32();
                uint32 entry = fields[1].GetUInt32();
                float x = fields[2].GetFloat();
                float y = fields[3].GetFloat();
                float z = fields[4].GetFloat();
                uint16 mapId = fields[5].GetUInt16();

                GameObjectTemplate const* gameObjectInfo = sObjectMgr->GetGameObjectTemplate(entry);
                if (!gameObjectInfo)
                    continue;

                if (goEntry && gameObjectInfo->entry != goEntry)
                    continue;

                handler->PSendSysMessage(LANG_GO_LIST_CHAT, guid, entry, guid, gameObjectInfo->name.c_str(), x, y, z, mapId);

                ++count;
            } while (result->NextRow());
        }

        handler->PSendSysMessage(LANG_COMMAND_NEAROBJMESSAGE, distance, count);
        return true;
    }

    //show info of gameobject
    static bool HandleGameObjectInfoCommand(ChatHandler* handler, char const* args)
    {
        uint32 entry = 0;
        uint32 type = 0;
        uint32 displayId = 0;
        std::string name;
        uint32 lootId = 0;

        if (!*args)
        {
            if (WorldObject* object = handler->getSelectedObject())
                entry = object->GetEntry();
            else
                entry = atoi((char*)args);
        } else
                entry = atoi((char*)args);

        GameObjectTemplate const* gameObjectInfo = sObjectMgr->GetGameObjectTemplate(entry);

        if (!gameObjectInfo)
            return false;

        type = gameObjectInfo->type;
        displayId = gameObjectInfo->displayId;
        name = gameObjectInfo->name;
        if (type == GAMEOBJECT_TYPE_CHEST)
            lootId = gameObjectInfo->chest.lootId;
        else if (type == GAMEOBJECT_TYPE_FISHINGHOLE)
            lootId = gameObjectInfo->fishinghole.lootId;

        handler->PSendSysMessage(LANG_GOINFO_ENTRY, entry);
        handler->PSendSysMessage(LANG_GOINFO_TYPE, type);
        handler->PSendSysMessage(LANG_GOINFO_LOOTID, lootId);
        handler->PSendSysMessage(LANG_GOINFO_DISPLAYID, displayId);
        handler->PSendSysMessage(LANG_GOINFO_NAME, name.c_str());

        return true;
    }

    static bool HandleGameObjectSetStateCommand(ChatHandler* handler, char const* args)
    {
        // number or [name] Shift-click form |color|Hgameobject:go_id|h[name]|h|r
        char* id = handler->extractKeyFromLink((char*)args, "Hgameobject");
        if (!id)
            return false;

        uint32 guidLow = atoi(id);
        if (!guidLow)
            return false;

        GameObject* object = NULL;

        if (GameObjectData const* gameObjectData = sObjectMgr->GetGOData(guidLow))
            object = handler->GetObjectGlobalyWithGuidOrNearWithDbGuid(guidLow, gameObjectData->id);

        if (!object)
        {
            handler->PSendSysMessage(LANG_COMMAND_OBJNOTFOUND, guidLow);
            handler->SetSentErrorMessage(true);
            return false;
        }

        char* type = strtok(NULL, " ");
        if (!type)
            return false;

        int32 objectType = atoi(type);
        if (objectType < 0)
        {
            if (objectType == -1)
                object->SendObjectDeSpawnAnim(object->GetGUID());
            else if (objectType == -2)
                return false;
            return true;
        }

        char* state = strtok(NULL, " ");
        if (!state)
            return false;

        int32 objectState = atoi(state);

        if (objectType < 4)
            object->SetByteValue(GAMEOBJECT_FIELD_STATE_SPELL_VISUAL_ID, objectType, objectState);
        else if (objectType == 4)
        {
            ObjectGuid guid = object->GetGUID();
            WorldPacket data(SMSG_GAMEOBJECT_CUSTOM_ANIM, 8+4);
            data.WriteBit(guid[4]);
            data.WriteBit(guid[7]);
            data.WriteBit(guid[1]);
            data.WriteBit(guid[0]);
            data.WriteBit(guid[5]);
            data.WriteBit(guid[3]);
            data.WriteBit(guid[2]);
            data.WriteBit(0); //unk
            data.WriteBit(guid[6]);
            data.FlushBits();

            data << uint32(objectState);
            data.WriteByteSeq(guid[5]);
            data.WriteByteSeq(guid[6]);
            data.WriteByteSeq(guid[7]);
            data.WriteByteSeq(guid[3]);
            data.WriteByteSeq(guid[4]);
            data.WriteByteSeq(guid[0]);
            data.WriteByteSeq(guid[2]);
            data.WriteByteSeq(guid[1]);
            object->SendMessageToSet(&data, true);
        }
        handler->PSendSysMessage("Set gobject type %d state %d", objectType, objectState);
        return true;
    }
};

void AddSC_gobject_commandscript()
{
    new gobject_commandscript();
}
