/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
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

#ifndef TRINITY_BAG_H
#define TRINITY_BAG_H

// Maximum 36 Slots ((CONTAINER_END - CONTAINER_FIELD_SLOT_1)/2
#define MAX_BAG_SIZE 36                                     // 2.0.12

#include "Item.h"
#include "ItemTemplate.h"

class TC_GAME_API Bag : public Item
{
    public:

        Bag();
        ~Bag();

        void AddToWorld() override;
        void RemoveFromWorld() override;

        void SetMap(Map* map) override;
        void ResetMap() override;

        bool Create(ObjectGuid::LowType const& guidlow, uint32 itemid, Player const* owner) override;

        void StoreItem(uint8 slot, Item* pItem, bool update);
        void RemoveItem(uint8 slot, bool update);

        Item* GetItemByPos(uint8 slot) const;
        uint32 GetItemCount(uint32 item, Item* eItem = nullptr) const;
        uint32 GetItemCountByQuality(uint8 Quality, int8 Expansion) const;
        uint32 GetItemCountWithLimitCategory(uint32 limitCategory, Item* skipItem = nullptr) const;

        uint8 GetSlotByItemGUID(ObjectGuid guid) const;
        bool IsEmpty() const;
        uint32 GetFreeSlots() const;
        uint32 GetBagSize() const { return GetUInt32Value(CONTAINER_FIELD_NUM_SLOTS); }

        // DB operations
        // overwrite virtual Item::SaveToDB
        void SaveToDB(CharacterDatabaseTransaction& trans) override;
        // overwrite virtual Item::LoadFromDB
        bool LoadFromDB(ObjectGuid::LowType const& guid, ObjectGuid const& owner_guid, Field* fields, uint32 entry, uint8 oLevel = 0) override;
        // overwrite virtual Item::DeleteFromDB
        void DeleteFromDB(CharacterDatabaseTransaction& trans) override;

        void BuildCreateUpdateBlockForPlayer(UpdateData* data, Player* target) const override;

    protected:

        // Bag Storage space
        Item* m_bagslot[MAX_BAG_SIZE];
};

inline Item* NewItemOrBag(ItemTemplate const* proto)
{
    return (proto->GetInventoryType() == INVTYPE_BAG) ? new Bag : new Item;
}
#endif

