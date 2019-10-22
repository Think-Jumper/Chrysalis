#pragma once

#include <CrySchematyc/Reflection/TypeDesc.h>


/**
Exposes the methods needed for management of items that can be added to an inventory.

**/

namespace Chrysalis
{
struct IActor;


/** Allows for handling of customised items. */
class IItemCustomisation
{
public:

};


/** Item receipt's allow for the storage and transfer of items between interested parties. */
class IItemReceipt
{
public:
	inline bool operator==(const IItemReceipt& rhs) const { return 0 == memcmp(this, &rhs, sizeof(rhs)); }

	static void ReflectType(Schematyc::CTypeDesc<IItemReceipt>& desc)
	{
		desc.SetGUID("{520CBE44-98C8-4885-9F63-918E001F560C}"_cry_guid);
		desc.SetLabel("Item Receipt Properties");
		desc.SetDescription("Item Receipt.");
	}

	virtual void Serialize(Serialization::IArchive& ar)
	{
		Serialization::SContext context(ar, this);
		ar(itemClass, "itemClass", "Item Class");
		ar(quantity, "quantity", "quantity");
	}


	/**
	Executes when an actor receives this receipt. This can be via pickup, trade, mail, auction house, etc.

	\param [in,out]	pActorOwner The owner of the actor.
	**/
	virtual void OnReceive(IActor& pActorOwner) = 0;


	/**
	Executes when an actor receives uses this receipt.

	\param [in,out]	pActorOwner  The owner of the receipt.
	\param [in,out]	pActorTarget The target actor for using the recipt upon.
	**/
	virtual void OnUse(IActor& pActorOwner, IActor& pActorTarget) = 0;


	/**
	Executes when an actor destroys this receipt.

	\param [in,out]	pActorOwner The owner of the actor.
	**/
	virtual void OnDestroy(IActor& pActorOwner) = 0;


	/** A reference to the item's class, which holds common information for this sort of item. */
	string itemClass;

	/** The quantity */
	uint32 quantity;

	/**
	Provides a means of customisation. NOTE: This is here as a reminder I need a way to customise
	components. That will need to be polymorphic.
	**/
	IItemCustomisation ItemCustomisation;
};



class IItemClass
{
public:
	inline bool operator==(const IItemClass& rhs) const { return 0 == memcmp(this, &rhs, sizeof(rhs)); }

	static void ReflectType(Schematyc::CTypeDesc<IItemClass>& desc)
	{
		desc.SetGUID("{6B1A4FD2-803C-4D4D-9924-174843B13EFD}"_cry_guid);
		desc.SetLabel("Item Class Properties");
		desc.SetDescription("Item Class Properties.");
	}

	virtual void Serialize(Serialization::IArchive& ar)
	{
		Serialization::SContext context(ar, this);
		ar(itemClass, "ItemClass", "Item Class");
		ar(displayName, "DisplayName", "Display Name");
		ar(isSelectable, "isSelectable", "Selectable?");
		ar(isUsable, "isUsable", "Usable?");
		ar(isGiveable, "isGiveable", "Giveable?");
		ar(isDroppable, "isDroppable", "Droppable?");
		ar(isAutoDroppable, "isAutoDroppable", "Auto droppable?");
		ar(isPickable, "isPickable", "Pickable?");
		ar(isAutoPickable, "isAutoPickable", "Auto pickable?");
		ar(isConsumable, "isConsumable", "Consumable?");
		ar(mass, "mass", "Mass");
		ar(dropImpulse, "dropImpulse", "Impulse when dropped");
		ar(shouldRemoveOnDrop, "shouldRemoveOnDrop", "Remove on drop?");
		ar(isUsableUnderWater, "isUsableUnderWater", "Usable under water?");
		ar(isWeapon, "isWeapon", "Weapon?");
		ar(isUniqueInventory, "isUniqueInventory", "Unique in inventory?");
		ar(isUniqueEquipment, "isUniqueEquipment", "Unique in equipment?");
		ar(canSupplyAmmo, "canSupplyAmmo", "Supply ammo?");
		ar(annimationTag, "annimationTag", "Animation tag");
		ar(isAttachedToBack, "isAttachedToBack", "Attached to back?");
	}

	/** Resets this item to it's default state. */
	virtual void OnResetState() { *this = IItemClass(); };

	/** Unique name for this class of item. */
	string itemClass;

	/** The name to display in the UI. This should be a localised string. */
	string displayName;

	/** True if this entity can be selected in the player's inventory. */
	bool isSelectable {true};

	/** true if this item is usable. */
	bool isUsable {true};

	/** Is this entity able to be bought / picked up / given / traded to a character? */
	bool isGiveable {true};

	/** Is this entity droppable? */
	bool isDroppable {true};

	/** Is this entity droppable automatically? */
	bool isAutoDroppable {false};

	/** true if this item is able to be picked up. */
	bool isPickable {true};

	/** true if this item is automatically able to be picked up. */
	bool isAutoPickable {true};

	/** Is this entity consumable? */
	bool isConsumable {false};

	/** The weight of the item when dropped. */
	float mass {1.0f};

	/** The impulse to apply when the item is dropped. */
	float dropImpulse {1.0f};

	/** Should the entity be removed from the game when it's dropped. */
	bool shouldRemoveOnDrop {false};

	/** true if this item is usable under water. */
	bool isUsableUnderWater {false};

	///** true if this item can be mounted. */
	//bool isMountable {true};

	///** Multiplier for how long it takes to select a given item. */
	//float selectTimeMultiplier {1.0f};


	// ***
	// *** Weapon Related
	// ***

	/** Is this item a weapon? */
	bool isWeapon {false};

	///** Is this item a heavy weapon? */
	//bool isHeavyWeapon {false};

	///** Can this item overcharge / overheat through use? */
	//bool canOvercharge {false};

	///** Time delay to automatically reload the weapon on an empty magazine. */
	//float autoReloadDelay {0.5f};

	///** The scope attachment. Assumption that this is the slot in which to add the scope, if it should be one. */
	//int scopeAttachment {0};

	///** Time delay from when the item is selected to when it is usable. */
	//float selectOverride {1.0f};


	// ***
	// *** Inventory / Equipment Related
	// ***


	/** true if this item is unique within an inventory. */
	bool isUniqueInventory {true};

	/** true if this item is unique when equipped. */
	bool isUniqueEquipment {true};

	/** true if this supplies some form of ammo. */
	bool canSupplyAmmo {false};


	// ***
	// *** Character attachment and animation / sound.
	// ***

	/** A tag(s) to apply to mannequin when this item is in use. */
	string annimationTag;

	/** Visually attaches the item to the players back in third person view, when not in use. */
	bool isAttachedToBack {false};
};


class IItem
{
public:
	inline bool operator==(const IItem& rhs) const { return 0 == memcmp(this, &rhs, sizeof(rhs)); }

	static void ReflectType(Schematyc::CTypeDesc<IItem>& desc)
	{
		desc.SetGUID("{222ECAC7-D041-43C0-B54A-F4355E98FA12}"_cry_guid);
		desc.SetLabel("Item Properties");
		desc.SetDescription("Item Properties.");
	}

	virtual void Serialize(Serialization::IArchive& ar)
	{
		Serialization::SContext context(ar, this);
		ar(itemClass, "itemClass", "Item Class");
		ar(displayName, "displayName", "Display Name");
		ar(quantity, "quantity", "quantity");
	}

	/** Which class of item does this belong to? */
	string itemClass;

	/** The name to display in the UI. This should be a localised string. */
	string displayName;

	/** The quantity */
	uint32 quantity {1};
};
}