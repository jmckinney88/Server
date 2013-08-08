#ifndef MAC_STRUCTS_H_
#define MAC_STRUCTS_H_

#include <string>

namespace Mac {
	namespace structs {


//paste contents of eq_packet_structs.h here...

		
/*
** Compiler override to ensure
** byte aligned structures
*/
#pragma pack(1)

// Valus of weapon types
enum SKILLTYPE : uint8
{
	SKILLTYPE_1HSLASHING = 0x00,
	SKILLTYPE_2HSLASHING = 0x01,
	SKILLTYPE_PIERCING = 0x02,
	SKILLTYPE_1HBLUNT = 0x03,
	SKILLTYPE_2HBLUNT = 0x04,
	SKILLTYPE_2HPIERCING = 0x23
};

enum TSpawnAppearanceType : uint16 {		// Cofruben: Better this way..
	SAT_SendToBind			= 0,	// Comment: 0=send to bind, >0 = kill them
	SAT_LevelChange			= 1,	// Comment: the level that shows up on /who
	SAT_Invis				= 3,	// Comment: 0=visable, 1=invisable
	SAT_PvP					= 4,	// Comment:	0=disable, 1=enable
	SAT_Light				= 5,	// Comment:	
	SAT_Position_Update		= 14,	// Comment: 100=standing, 102=lose control (fear, mez, charm), 110=sitting, 111=ducking, 115=feigned, 105=looting
	SAT_Sneaking			= 15,	// Comment:
	SAT_Camp				= 16,	// Comment:
	SAT_HP_Regen			= 17,	// Comment: Client->Server, my HP has changed (like regen tic)
	SAT_LD					= 18,	// Comment:
	SAT_Levitate			= 19,	// Comment: 0=off, 1=flymode, 2=levitate
	SAT_GM_Tag				= 20,
	SAT_NameColor			= 21,	// Comment:	AT_PVP[0=green,1=dark red,2=light red] or !AT_PVP[0=green,1=blue,2=purple]
	SAT_Guild_ID			= 22,	// Comment: Joins player to the specified guild id param.
	SAT_Guild_Rank			= 23,	// Comment: 0=member, 1=officer, 2=leader
	SAT_AFK					= 24,	// Comment: 0=off, 1=on
	SAT_Autosplit			= 28,
	SAT_Size				= 29,	// Comment: spawn's size (0=smallest)
	SAT_NPC_Name			= 30	// Comment: change PC's name's color to NPC color (unreversable)
};

enum TBodyType : uint16 {	// Cofruben: 16/08/08.
	BT_Humanoid			= 1,
	BT_Lycanthrope		= 2,
	BT_Undead			= 3,
	BT_Giant			= 4,
	BT_Construct		= 5,
	BT_Extraplanar		= 6,
	BT_Magical			= 7,	//this name might be a bit off, 
	BT_SummonedUndead	= 8,
	BT_NoTarget			= 11,	// can't target this bodytype
	BT_Vampire			= 12,
	BT_Atenha_Ra		= 13,
	BT_Greater_Akheva	= 14,
	BT_Khati_Sha		= 15,
	BT_Zek				= 19,
	BT_Luggald			= 20,
	BT_Animal			= 21,
	BT_Insect			= 22,
	BT_Monster			= 23,
	BT_Summoned			= 24,	//Elemental?
	BT_Plant			= 25,
	BT_Dragon			= 26,
	BT_Summoned2		= 27,
	BT_Summoned3		= 28,
	BT_VeliousDragon	= 30,	//might not be a tight set
	BT_Dragon3			= 32,
	BT_Boxes			= 33,
	BT_Muramite			= 34,	//tribal dudes
	BT_NoTarget2		= 60,
	BT_SwarmPet			= 63,	//is this valid, or made up?
	BT_Trigger			= 65,   //Yeahlight: Body type to completely hide the spawn
	BT_InvisMan			= 66,	//seen on 'InvisMan'
	BT_Special			= 67
};

enum TSpawnAppearancePositionParameter : uint32 {
	SAPP_Sitting_To_Standing	= 100,
	SAPP_Lose_Control			= 102,
	SAPP_Looting				= 105,
	SAPP_Standing_To_Sitting	= 110,
	SAPP_Ducking				= 111,
	SAPP_Unconscious			= 115
};

/************************************************************** 
CharacterSelect_Struct - neorab 9/28/2007 

This structure is sent from the world in world/client.cpp in 
the Client::SendCharInfo() method.  Although there are only
eight character slots, all ten must be sent to correctly pack
the struct.

The equip portion of the character's data is represented by:
equip[x][0]=helm 
equip[x][1]=chest 
equip[x][2]=arm
equip[x][3]=bracer
equip[x][4]=hand
equip[x][5]=leg
equip[x][6]=boot
equip[x][7]=melee1
equip[x][8]=melee2

1-6 all follow the format of 0=none, 1=leather, 2=chain, 3=plate
and 4=monk straps (sexy humans)

7 and 8 need not be sent.  They must be there for padding but
the actuall data is requested by the client when they select the
char on screen.

I am not sure what, if any, purpose the unknown serves here 
other than padding.  Removing it does break the character select 
screen.

03/09/08 - Wizzel
Verified that the color was reading grabbing red values from blue,
green from alpha, and blue from red. Shifted the color portion
over two bytes and fixed the problem. No luck with weapons yet.

***************************************************************/
struct CharacterSelect_Struct
{
/*0000*/	char	name[10][64];		// Characters Names
/*0640*/	uint8	level[10];			// Characters Levels
/*0650*/	uint8	class_[10];			// Characters Classes
/*0660*/	uint16	race[10];			// Characters Race
/*0680*/	uint32	zone[10];			// Characters Current Zone
/*0720*/	uint8	gender[10];			// Characters Gender
/*0730*/	uint8	face[10];			// Characters Face Type
/*0740*/	uint32	equip[10][9];		// 0=helm, 1=chest, 2=arm, 3=bracer, 4=hand, 5=leg, 6=boot, 7=melee1, 8=melee2
/*1100*/	Color_Struct cs_colors[10][9];	// Characters Equipment Colors (RR GG BB 00)
/*1480*/	uint32	deity[10];			// Characters Deity
/*1520*/	uint32	primary[10];		// Characters primary and secondary IDFile number
/*1520*/	uint32	secondary[10];		// Characters primary and secondary IDFile number
/*1600*/	uint8	haircolor[10];	// vesuvias - found values
/*1610*/	uint8	beardcolor[10];
/*1620*/	uint8	eyecolor2[10];
/*1630*/	uint8	eyecolor1[10];
/*1640*/	uint8	hairstyle[10];
/*1650*/	uint8	beard[10];
///*1460*/	uint8	cs_unknown[160];	// ***Placeholder
};

//Tazadar : This is used to show weapons on char select screen
struct CharWeapon_Struct
{
	uint16 righthand[10];
	uint16 lefthand[10];
};

struct ServerZoneEntry_Struct {
/*0000*/	uint8	checksum[4];		// Checksum
/*0004*/	uint8	unknown0004;		// ***Placeholder
/*0005*/	char	name[64];			// Name
/*0069*/	uint8	sze_unknown0069;	// ***Placeholder
/*0070*/	uint16	unknown0070;		// ***Placeholder
/*0072*/	uint32	zone;				// Current Zone
#ifndef INVERSEXY
/*0076*/	float	x;					// X Position (Not Inversed)
/*0080*/	float	y;					// Y Position (Not Inversed)
#else
/*0076*/	float	y;					// Y Position (Inversed)
/*0080*/	float	x;					// X Position (Inversed)
#endif
/*0084*/	float	z;					// Z Position
/*0088*/	float	heading;			// Heading
/*0092*/	uint32	unknown0092[18];	// ***Placeholder
/*0164*/	uint16	guildeqid;			// Guild ID Number
/*0166*/	uint8	unknown0166[7];		// ***Placeholder
/*0173*/	uint8	class_;				// Class
/*0174*/	uint16	race;				// Race
/*0176*/	uint8	gender;				// Gender
/*0177*/	uint8	level;				// Level
/*0178*/	uint16	unknown0178;		// ***Placeholder	
/*0180*/	uint8	pvp;				// PVP Flag
/*0181*/	uint16	unknown0181;		// ***Placeholder
/*0183*/	int8	face;				// Face Type
/*0197*/    uint16  equipment[MAX_MATERIALS]; // Array elements correspond to struct equipment above
/*0202*/	uint16	unknown;			// ***Placeholder
/*0206*/	Color_Struct colors[MAX_MATERIALS]; // Array elements correspond to struct equipment_colors above
/*0240*/	uint8	npc_armor_graphic;	// Texture (0xFF=Player - See list of textures for more)
/*0241*/	uint8	unknown0241[19];	// ***Placeholder
/*0260*/	float	walkspeed;			// Speed when you walk
/*0264*/	float	runspeed;			// Speed when you run
/*0268*/	uint32	unknown0268[3];		// ***Placeholder (At least one flag in here disables a zone point or all)
/*0280*/	uint8	anon;				// Anon. Flag
/*0281*/	uint8	unknown0281[23];	// ***Placeholder (At least one flag in here disables a zone point or all)
/*0304*/	char	Surname[34];		// Lastname (This has to be wrong.. but 70 is to big =/..)
/*0338*/	uint16	deity;				// Diety (Who you worship for those less literate)
/*0340*/	uint8	unknown0340;		// ***Placeholder
/*0341*/	uint8	haircolor;			// Hair Color
/*0342*/	uint8	beardcolor;			// Beard Color
/*0343*/	uint8	eyecolor1;			// Left Eye Color
/*0344*/	uint8	eyecolor2;			// Right Eye Color
/*0345*/	uint8	hairstyle;			// Hair Style
/*0346*/	uint8	title;				// AA Title
/*0347*/	uint8	luclinface;			// Face Type
/*0348*/	uint8	skyradius;			// Skyradius (Lyenu: Not sure myself what this is)
/*0349*/	uint8	unknown321[7];		// ***Placeholder
};

struct ZoneServerInfo_Struct
{
/*0000*/	char	ip[128];
/*0128*/	uint16	port;
};


// 372 bytes

/*
** New Zone Struct
** OPCODE: 5b20
** Length: 372 Bytes
*/
// Wizzel: Loads information about the zone to be entered by the client.
// I have figured out nearly all relevant stuff. The unknowns are
// still handled correctly. This is a very fragile struct. If you have
// any questions, ask me about it.

struct NewZone_Struct 
{
/*0000*/	char	char_name[64];			// Character Name
/*0064*/	char	zone_short_name[32];	// Zone Short Name
/*0096*/	char	zone_long_name[278];	// Zone Long Name
/*0374*/	uint8	ztype;
/*0375*/	uint8	fog_red[4];				// Red Fog 0-255 repeated over 4 bytes (confirmed: Wizzel)
/*0379*/	uint8	fog_green[4];			// Green Fog 0-255 repeated over 4 bytes (confirmed: Wizzel)
/*0383*/	uint8	fog_blue[4];			// Blue Fog 0-255 repeated over 4 bytes (confirmed: Wizzel)
/*0387*/	uint8	unknown387;
/*0388*/	float	fog_minclip[4];			// Where the fog begins (lowest clip setting). Repeated over 4 floats. (confirmed: Wizzel)
/*0404*/	float	fog_maxclip[4];			// Where the fog ends (highest clip setting). Repeated over 4 floats. (confirmed: Wizzel)	
/*0420*/	float	gravity;				// CD CC CC 3E Can't move if incorrect
/*0424*/	uint8	time_type;
/*0425*/	uint8	unknown425[49];
/*0474*/	uint8	sky;
/*0475*/	uint8	zone_exp_multiplier;
/*0492*/	float	safe_y;
/*0496*/	float	safe_x;
/*0500*/	float	safe_z;
/*0504*/	float	max_z;
/*0508*/	float	underworld;
/*0512*/	float	minclip;				// Minimum View Distance
/*0516*/	float	maxclip;				// Maximum View DIstance
/*0520*/	uint8	unknown_end[52];		// ***Placeholder
};


struct MemorizeSpell_Struct 
{ 
	uint32 slot;			// Comment:  Spot in the spell book/memorized slot 
	uint32 spell_id;		// Comment:  Spell id (200 or c8 is minor healing, etc) 
	uint32 scribing;		// Comment:  1 if memorizing a spell, set to 0 if scribing to book 
}; 

struct CastOn_Struct 
{
/*00*/	uint32	target_id;			// Comment: Spell Targets ID 
/*02*/	uint32	source_id;			// Comment: Spell Caster ID
/*04*/	uint8	source_level;		// Comment: Spell Casters Level
/*05*/	uint8	unknown1[4];		// Comment: Unknown -> needs confirming 
/*09*/	uint8	unknown_zero1[7];	// Comment: Unknown -> needs confirming -> (orginal comment: lol) <- lol 
/*16*/	float	heading;			// Comment: Heading of Who? Caster or Target? Needs confirming
/*20*/	uint8	unknown_zero2[4];	// Comment: Unknown -> needs confirming
/*24*/	uint32	action;				// Comment: Unknown -> needs confirming -> Which action target or caster does maybe?
/*28*/	uint16	spell_id;			// Comment: Spell ID of the Spell being casted? Needs Confirming
/*30*/	uint8	unknown2[2];		// Comment: Unknown -> needs confirming
};

struct InterruptCast_Struct
{
	uint16	spawnid;		// Comment: ID of Spell Caster
	uint16	unknown1;		// Comment: Unknown -> needs confirming -> placeholder?
	char	message[0];		// Comment: Unknown -> needs confirming -> Message of what? the spell cast text?
};

struct ManaChange_Struct
{
	uint16 new_mana;	// Comment:  New Mana AMount
	uint16 spell_id;	// Comment:  Last Spell Cast
};

struct SwapSpell_Struct 
{ 
	uint32 from_slot;	// Comment: Moving Spells around?
	uint32 to_slot;		// Comment: Moving Spells Around?
}; 

struct BeginCast_Struct
{
/*000*/	uint32	caster_id;		// Comment: Unknown -> needs confirming -> ID of Spell Caster? 
/*004*/	uint32	spell_id;		// Comment: Unknown -> needs confirming -> ID of Spell being Cast?
/*008*/	uint32	cast_time;		// Comment: Unknown -> needs confirming -> in miliseconds?
};

struct Buff_Struct
{
	uint32	target_id;		// Comment: Unknown -> needs confirming -> Target of the Buff
	uint32	b_unknown1;		// Comment: Unknown -> needs confirming
	uint16	spell_id;		// Comment: Unknown -> needs confirming -> Spell ID?
	uint32	b_unknown2;		// Comment: Unknown -> needs confirming
	uint16	b_unknown3;		// Comment: Unknown -> needs confirming
	uint32	buff_slot;		// Comment: Unknown -> needs confirming -> Which buff slot on the target maybe?
};

#define SLOT_ITEMSPELL		10		// Cofruben: we right clicked into a clickable item which allow us casting some spell.
struct CastSpell_Struct
{
	uint16	slot;
	uint16	spell_id;
	uint16	inventoryslot;  // slot for clicky item, 0xFFFF = normal cast
	uint16	target_id;
	uint32	cs_unknown2;
};


//Yeahlight
//NOTEABLE TYPES (In decimal):
//  + 21: This type will remove you from your own client list and
//        possibly the list of others (GM spying).
struct SpawnAppearance_Struct
{
// len = 8
/*0000*/ uint16 spawn_id;          // ID of the spawn
/*0002*/ uint16 type;              // Values associated with the type
/*0004*/ uint32 parameter;         // Type of data sent
};

// Length: 24
struct SpellBuffFade_Struct {
/*000*/ uint32  playerid;       // Comment: Id of the player
/*004*/	uint8	unknown000[4];	// Comment: 
/*008*/	uint16	spellid;		// Comment: 
/*010*/	uint8	unknown010[6];	// Comment: 
/*016*/	uint8	slotid;			// Comment:  Buff slot # on the client
/*017*/	uint8	unknown017[3];	// Comment: 
/*020*/	uint8	fade;			// Comment: 01 = true
/*021*/	uint8	unknown[3];		// Comment: 
};

/*
** client changes target struct
** Length: 2 Bytes
** OpCode: 6221
*/
struct ClientTarget_Struct {
/*000*/	uint16	new_target;			// Target ID
};

/*
** Yeahlight
** Client hits taunt
** Length: 12 Bytes
** OpCode: 3b21
*/
struct ClientTaunt_Struct
{
	uint16  tauntTarget;		// Comment: ID of target
	uint16  buffer;          // Comment: ***Placeholder
	uint16  tauntUser;		// Comment: ID of taunter
	uint8   buffer2[6];		// Comment: ***Placeholder
};

struct Spawn_Struct
{
/*0000*/	uint8	animation;
/*0001*/	uint8	heading;			// Current Heading
/*0002*/	uint8	deltaHeading;		// Delta Heading
#ifndef INVERSEXY
/*0003*/	int16	x_pos;				// X Position
/*0005*/	int16	y_pos;				// Y Position
#else
/*0003*/	int16	y_pos;				// Y Position
/*0005*/	int16	x_pos;				// X Position
#endif
/*0007*/	int16	z_pos;				// Z Position
/*0009*/	int32	deltaY:10,			// Velocity Y
					spacer1:1,			// Placeholder
					deltaZ:10,			// Velocity Z
					spacer2:1,			// ***Placeholder
					deltaX:10;			// Velocity X
/*0013*/	uint8	unknown0051;
/*0014*/	uint16	pet_owner_id;		// Id of pet owner (0 if not a pet)
/*0016*/	uint8	s_unknown1a[8];		// Placeholder
/*0024*/	float	size;
/*0028*/	float	walkspeed;
/*0032*/	float	runspeed;
/*0036*/	Color_Struct	equipcolors[9];
/*0072*/	uint16	spawn_id;			// Id of new spawn
/*0074*/	uint8	traptype;			// 65 is disarmable trap, 66 and 67 are invis triggers/traps
/*0075*/	uint8	unknown0075;
/*0076*/	int16	cur_hp;				// Current hp's of Spawn
/*0078*/	uint16	GuildID;			// GuildID - previously Current hp's of Spawn
/*0080*/	uint16	race;				// Race
/*0082*/	uint8	NPC;				// NPC type: 0=Player, 1=NPC, 2=Player Corpse, 3=Monster Corpse, 4=???, 5=Unknown Spawn,10=Self
/*0083*/	uint8	class_;				// Class
/*0084*/	uint8	gender;				// Gender Flag, 0 = Male, 1 = Female, 2 = Other
/*0085*/	uint8	level;				// Level of spawn (might be one int8)
/*0086*/	uint8	invis;				// 0=visable, 1=invisable
/*0087*/	uint8	unknown0087;
/*0088*/	uint8	pvp;
/*0089*/	uint8	anim_type;
/*0090*/	uint8	light;				// Light emitting
/*0091*/	uint8	anon;				// 0=normal, 1=anon, 2=RP
/*0092*/	uint8	AFK;				// 0=off, 1=on
/*0093*/	uint8	unknown078;
/*0094*/	uint8	LD;					// 0=NotLD, 1=LD
/*0095*/	uint8	GM;					// 0=NotGM, 1=GM
/*0096*/	uint8	s_unknown5_5;		// used to be s_unknown5[5]
/*0097*/	uint8	npc_armor_graphic;	// 0xFF=Player, 0=none, 1=leather, 2=chain, 3=steelplate
/*0098*/	uint8	npc_helm_graphic;	// 0xFF=Player, 0=none, 1=leather, 2=chain, 3=steelplate
/*0099*/	uint8	s_unknown0099;		// used to be s_unknown5[2]
/*0100*/	uint16	equipment[9];		// Equipment worn: 0=helm, 1=chest, 2=arm, 3=bracer, 4=hand, 5=leg, 6=boot, 7=melee1, 8=melee2
/*0118*/	int8	guildrank;			// ***Placeholder
/*0119*/	uint8	unknown0207;
/*0120*/	uint16	deity;				// Deity.
/*0122*/	uint8	unknown122;			// ***Placeholder
/*0123*/	char	name[64];			// Name of spawn (len is 30 or less)
/*0187*/	char	Surname[20];		// Last Name of player
/*0207*/	uint8	haircolor;
/*0208*/	uint8	beardcolor;
/*0209*/	uint8	eyecolor1;			// the eyecolors always seem to be the same, maybe left and right eye?
/*0210*/	uint8	eyecolor2;
/*0211*/	uint8	hairstyle;
/*0212*/	uint8	title;				//Face Overlay? (barbarian only)
/*0213*/	uint8	luclinface;			// and beard
			uint8	unknownpop[6];
};

/*
** New Spawn
** Length: 176 Bytes
** OpCode: 4921
*/
struct NewSpawn_Struct
{
	uint32  ns_unknown1;            // Comment: ***Placeholder
	struct Spawn_Struct spawn;     // Comment: Spawn Information
};

/*
** Delete Spawn
** Length: 2 Bytes
** OpCode: 2b20
*/
struct DeleteSpawn_Struct
{
/*00*/ uint16 spawn_id;				// Comment: Spawn ID to delete
	   uint32 ds_unknown1;			// Comment: 
};

/*
** Channel Message received or sent
** Length: 71 Bytes + Variable Length + 4 Bytes
** OpCode: 0721
*/
//Yeahlight: Old ChannelMessage_Struct struct (DO NOT DELETE)
//struct ChannelMessage_Struct
//{
//	char  targetname[32];		// Comment:  Tell recipient
//	char  sender[23];           // Comment:  The senders name (len might be wrong)
//	uint8  cm_unknown2[9];       // Comment:  ***Placeholder
//	uint16  language;            // Comment:  Language
//	uint16  chan_num;            // Comment:  Channel
//	uint8  cm_unknown4[5-1];     // Comment:  ***Placeholder
//	char  message[0];           // Comment:  Variable length message
//};

//Yeahlight: New ChannelMessage_Struct struct
struct ChannelMessage_Struct
{
/*000*/	char	targetname[64];		// Tell recipient
/*064*/	char	sender[64];			// The senders name (len might be wrong)
/*128*/	uint16	language;			// Language
/*130*/	uint16	chan_num;			// Channel
/*132*/	uint8	cm_unknown4[2];		// ***Placeholder
/*134*/	uint16	skill_in_language;	// The players skill in this language? might be wrong
/*136*/	char	message[0];			// Variable length message
};

//Kibanu: New EmoteMessage_Struct
struct EmoteMessage_Struct
{
	char to[32];		// Comment: Recipient
	uint32 guilddbid;	// Comment: 
	uint32 type;			// Comment: 
	char message[0];	// Comment: variable-length message
};

/*
** When somebody changes what they're wearing
**      or give a pet a weapon (model changes)
** Length: 16 Bytes
** Opcode: 9220
** This is not correct, but close.
*/

struct WearChange_Struct
{
/*000*/ uint16 spawn_id;
/*002*/ uint16 wear_slot_id;
/*004*/ uint16 slot_graphic;
/*006*/ uint8 color;
/*007*/ uint8 unknown3;
/*009*/ uint8 blue;
/*010*/ uint8 green;
/*011*/ uint8 red;
/*012*/ uint8 unknown4;
};

/*
** Type:   Bind Wound Structure		//////////////////////////////////////////
** Length: 8 Bytes					//		BindWound_Struct				//
** OpCode: 9320						//		Moraj 08.20.09					//
*/									//////////////////////////////////////////
struct BindWound_Struct				// to = TargetID						//
{									// type = Return Action Type			//
/*000*/	uint16	to;					// Bind Wound Return Action Types:		//
/*002*/	uint16	unknown2;			// 0/1 = Complete						//
/*004*/	uint16	type;				// 2 = Unlock Movement					//
/*006*/	uint16	unknown6;			// 3 = Unlock Interface					//
};									// 4 = Fail: Target Died				//
									// 5 = Fail: Target Left Zone			//
									// 6 = Fail: Target Moved Away			//
									// 7 = Fail: You Moved					//
									//////////////////////////////////////////

//Used inside the object struct for items with effects.
//Size: 10 bytes
struct Object_Data_Struct{
	uint8	max_charges;	//Max stack or charges. (Confirmed Sp0tter).
	uint8	stack_size;		//Current stack size or current charges.
	uint8	has_effect;		// 1 for has effect?  (not sure)
	uint16	click_effect;	//ID of click effect.	(Confirmed Sp0tter).
	uint8	unknown[5];
};

struct Object_Struct {
		uint8	unknown001[8];
		uint32	itemid;	//maybe
		uint32	dropid;	//this id will be used, if someone clicks on this object
		uint8	unknown014[128];		// ***Placeholder
		float	ypos;
		float	xpos;
		float	zpos;					// Z Position
		char	idFile[16];				// ACTOR ID
		uint16	heading;
		char	objectname[16];
		uint16	itemsinbag[10]; //if you drop a bag, thats where the items are
		uint8	unknowneos[14];
};
struct ClickObject_Struct {
	uint32	objectID;
	uint16	PlayerID;
	uint16	unknown;
};
struct ClickObjectAck_Struct {
/*00*/	uint32	player_id;		// Comment: Entity Id of player who clicked object
/*04*/	uint8	unknown[4];		// Comment: Unknown 
/*08*/	uint8	open;			// Comment: 0=close 1=open
/*09*/	uint8	unknown6;		// Comment: Unknown 
/*10*/	uint8	type;			// Comment: number that determines the type of the item (i.e forge) 
/*11*/	uint8	unknown8;		// Comment: Unknown 
/*12*/	uint8	slot;			// Comment: number of slots of the container
/*13*/  uint8	unknown10[3];	// Comment: Unknown 
/*14*/	uint16	icon_nr;		// Comment: Icon of the item
/*16*/	uint8	unknown16[4];	// Comment: Unknown
};

/*
** Drop Coins
** Length: 112 Bytes
** OpCode: 0720
*/
struct DropCoins_Struct
{
/*0000*/ uint8	unknown0002[8];		    // Comment: Always 00's
/*0008*/ uint32  platinumPieces;         // Comment: Number of PP dropped (confirmed: Yeahlight)
/*0012*/ uint32  goldPieces;				// Comment: Number of GP dropped (confirmed: Yeahlight)
/*0016*/ uint32  silverPieces;			// Comment: Number of SP dropped (confirmed: Yeahlight)
/*0020*/ uint32  copperPieces;			// Comment: Number of CP dropped (confirmed: Yeahlight)
/*0024*/ uint8	unknown0024[4];         // Comment: ***Placeholder
/*0028*/ uint32	always34;				// Comment: Always 0x34
/*0032*/ uint8	unknown0028[16];		// Comment: ***Placeholder
/*0048*/ uint32	amount;					// Comment: Total Dropped (confirmed: Yeahlight)
/*0052*/ uint16  test1;                  // Comment: ***Placeholder
/*0054*/ uint16	test2;					// Comment: ***Placeholder
/*0056*/ float	yPos;					// Comment: Y Position (confirmed: Yeahlight)
/*0060*/ float	xPos;					// Comment: X Position (confirmed: Yeahlight)
/*0064*/ float	zPos;					// Comment: Z Position (confirmed: Yeahlight)
/*0068*/ uint8	unknown0070[12];		// Comment: ***Placeholder
/*0080*/ char	coinName[16];			// Comment: Texture file name; ie, PLAT_ACTORDEF (confirmed: Yeahlight)
/*0096*/ uint8	unknown0097[16];		// Comment: ***Placeholder
};

/************************************************************** 
Beg_Struct - neorab 5/24/2008 [Opcode: 0x2521  Size: 18]

This is the structure of the beg request and the return to the
client.  Using success >= 5 is the same as using success = 0.
I suspect the unknown is completely padding and nothing else,
the client certainly isn't using it for anything that I can see.
***************************************************************/
struct Beg_Struct
{
	uint16	target;		// The player's target at time of beg.
	uint16	begger;		// The player making the coin request.
	uint8	skill;		// The player's begging skill level.
	uint8	success;	// -1 = request | 0 = failure | 1 = plat | 2 = gold | 3 = silver | 4 = copper
	uint16	unknown1;		// This is the time since player logged in.
	uint32	coins;		// The number of coins.  Whatever success is set to.
	uint8	unknown3[6];	// Not sure.  Maybe we'll find out one day.
};


/*
** Type:   Zone Change Request (before hand)
** Length: 70 Bytes-2 = 68 bytes 
** OpCode: a320
*/

#define ZONE_ERROR_NOMSG 0
#define ZONE_ERROR_NOTREADY -1
#define ZONE_ERROR_VALIDPC -2
#define ZONE_ERROR_STORYZONE -3
#define ZONE_ERROR_NOEXPANSION -6
#define ZONE_ERROR_NOEXPERIENCE -7

struct ZoneChange_Struct {
/*000*/	char	char_name[64];     // Character Name
/*064*/	uint32	zoneID;
/*068*/ uint8	unknown1[4];
/*072*/	int8	success;		// =0 client->server, =1 server->client, -X=specific error
/*073*/	uint8	unknown0073[3]; // =0 ok, =ffffff error
};

struct Attack_Struct
{
/*00*/ uint32   spawn_id;		// Comment: Spawn ID
/*04*/ uint8    type;			// Comment: 
/*05*/ uint8    a_unknown2[7];	// Comment: ***Placeholder};
};
/*
** Battle Code
** Length: 24 Bytes
** OpCode: 5820
*/
struct Action_Struct
{
	// len = 24
/*000*/	uint16	target;
/*002*/	uint16	source;
/*004*/	uint8	type;
/*005*/	uint8	unknown005;
/*006*/	uint16	spell;
/*008*/	int32	damage;
/*012*/	uint8	unknown4[12];
};

/************************************************************** 
Consider_Struct - neorab 9/23/2007 

OPCODE - 0x3721 

Used by the client to request consider information from server 
and by server to return consider information to client.  The 
unworthy code was never used live as far as I know.  Set it to 
anything but 0 and when the con is "green" the message is that 
the mob "would not make a worthy opponent."  When the con is 
"yellow" the little message is removed completely.  The two 
before it are padding that I think is used for sending data to 
the server, but we don't need it and we don't use it going out. 

At some point, unknown_c was level, cur_hp and max_hp.  After 
testing this many many times, I found that those three values 
make no difference.  The level for the consider is taken from 
the data in update structs and spawn_struct.  I verified that 
the HP items make no difference as well.  The two unknown_a(b) 
are padding around the player and target id.  It has been 
verified that they are not used as part of the IDs as I thought 
they were originally. 

***************************************************************/ 

struct Consider_Struct{
/*000*/ uint16	playerid;               // PlayerID
/*002*/ uint16	targetid;               // TargetID
/*004*/ uint32	faction;                // Faction
/*008*/ uint32	level;                  // Level
/*012*/ int32	cur_hp;                  // Current Hitpoints
/*016*/ int32	max_hp;                  // Maximum Hitpoints
/*020*/ uint8	unknown3[4];
};

struct ConsentRequest_Struct
{
	char name[1];				//Comment: Name of player who consent is being given to.
};

struct ConsentResponse_Struct
{
/*0000*/ char consentee[32];        // Name of player who was consented
/*0064*/ char consenter[32];        // Name of player who consented
/*0128*/ uint8   allow;             // 00 = deny, 01 = allow
/*0129*/ char corpseZoneName[32];   // Zone where the corpse is
/*0193*/
};

//Tazadar: New working packet for NPC_Death (12/08/08)
  struct Death_Struct
{
/*000*/	uint32	spawn_id;		// Comment: 
/*004*/	uint32	killer_id;		// Comment: 
/*008*/	uint32	corpseid;		// Comment: corpseid used for looting PC corpses ! (Tazadar)
/*012*/	uint16	unknown12;		// Comment: 
/*014*/	uint8	attack_skill;	// Comment: Attack skill (Confirmed by Tazadar)
/*015*/	uint8	unknown15;		// Comment: 
/*016*/	uint16	damage;			// Comment: Damage taken, (Confirmed by Tazadar)
/*018*/ uint16	unknown18;		// Comment: 
};

/*
** Generic Spawn Update
** Length: 15 Bytes
** Used in:
**
*/
struct SpawnPositionUpdate_Struct
{
/*0000*/ uint16  spawn_id;               // Id of spawn to update
/*0002*/ uint8   anim_type; // ??
/*0003*/ uint8	heading;                // Heading
/*0004*/ int8  delta_heading;          // Heading Change
/*0005*/ int16 x_pos;                  // New X position of spawn
/*0007*/ int16 y_pos;                  // New Y position of spawn
/*0009*/ int16 z_pos;                  // New Z position of spawn
/*0011*/ uint32  delta_y:10,             // Y Velocity
                spacer1:1,              // ***Placeholder
                delta_z:10,             // Z Velocity
                spacer2:1,              // ***Placeholder
                delta_x:10;             // Z Velocity
};

/*
** Spawn Position Update
** Length: 6 Bytes + Number of Updates * 15 Bytes
** OpCode: a120
*/
struct SpawnPositionUpdates_Struct
{
/*0000*/ uint32  num_updates;               // Number of SpawnUpdates
/*0004*/ struct SpawnPositionUpdate_Struct // Spawn Position Update
                     spawn_update[0];
};

/*
** Spawn HP Update
** Length: 14 Bytes
** OpCode: b220
*/
struct SpawnHPUpdate_Struct
{
/*00*/ uint32  spawn_id;		// Comment: Id of spawn to update
/*04*/ int32 cur_hp;		// Comment:  Current hp of spawn
/*08*/ int32 max_hp;		// Comment: Maximum hp of spawn
};

/*
** Stamina
** Length: 8 Bytes
** OpCode: 5721
*/
struct Stamina_Struct 
{
/*00*/ uint16 food;		// Comment: low more hungry 6000-0
/*02*/ uint16 water;		// Comment: low more thirsty 6000-0
/*04*/ uint16 fatigue;	// Comment: high more fatigued 0-100
};

/*
** Tazadar/Yeahlight : Resurrection struct (Corrected)
** Length: 160
** OpCode: 0x2a21
*/
struct Resurrect_Struct	
{            
	/* 000 */	uint32	corpseEntityID; // Tazadar : Client do not use any bytes till 52
	/* 004 */	char	zoneName[16]; 
	/* 020 */	char	unknown20[16]; 
	/* 036 */	float	y; 
	/* 040 */	float	x; 
	/* 044 */	float	z; 
	/* 050 */	uint32	fullGMRez;
	/* 052 */	char	targetName[28]; // Tazadar : Client uses this !!! If its wrong you wont see any window
	/* 082 */   char	unknown82[8];
	/* 088 */	char	casterName[28]; // Tazadar : Caster name (Confirmed)
	/* 118 */   uint32	unknown118;
	/* 120 */	uint16	spellID; // Tazadar : ID of the spell (Confirmed)
	/* 122 */	char	corpseName[28];
	/* 150 */	char	unknown[6];
	/* 156 */	uint32	action; // Tazadar : Action => player clicked yes = 1 or no = 0 (Confirmed)
};

/*
** Tazadar : Sacrifice struct 
** Length: 12
** OpCode: 0xea21
*/
struct Sacrifice_Struct{
	/* 000 */	uint32 casterID;	// Tazadar : Caster who sends the request (Confirmed)
	/* 004 */	uint32 targetID; // Tazadar : Player who recieves the request (Confirmed)
	/* 008 */	uint32 action; // Tazadar : Action => player clicked yes = 1 or no = 0 (Confirmed)
};

/*
** Special Message
** Length: 6 Bytes + Variable Text Length
** OpCode: 8021
*/
struct SpecialMesg_Struct
{
/*0000*/ uint32 msg_type;		// Comment: Type of message
/*0004*/ char  message[0];		// Comment: Message, followed by four bytes?
};

/*************************************************************
LevelUpdate_Struct - neorab, SpOtter 9/29/2008

This structure is sent to the client when a character levels.
The exp portion of the struct must not be read by out version
of the client because not byte in the first 200 could be found
to make any difference.

This may be different one we start on ExpUpdate_Struct.  We
can't know for sure that somewhere the client is just being
updated over and over that the exp is some bizarre number.

TODO: Look into this issue later.

The second byte is a flag.  If not equal to zero, the client
allows the character to de-level.  If it is equal to zero, the
client does not change the level of the played char.  Weird,
but maybe they just have a check in there for hackers.

There does not appear to be a problem at this point with just
using two bytes.  When this get re-evaluated, be sure to check
and see if you can send exp and if we need to increase the
length of this struct.
--------------------------------------------------------------
00 - level
01 - can_delevel
*************************************************************/
struct LevelUpdate_Struct
{
/*00*/	uint8	level;			// Comment: Target Level of character
/*01*/	uint8	can_delevel;	// Comment: If zero, don't delevel (clientside)
};

/*
** Experience Update
** Length: 14 Bytes
** OpCode: 9921
*/
struct ExpUpdate_Struct
{
/*0000*/ uint32 exp;			// Comment: Current experience value
};

/*
** Generic Item structure
** Length: 244 bytes
** Used in:
**    itemShopStruct(0c20), itemReceivedPlayerStruct(5220),
**    itemPlayerStruct(6421), bookPlayerStruct(6521),
**    containerPlayerStruct(6621), summonedItemStruct(7821),
**    tradeItemStruct(df20),
*/
#define ITEM_STRUCT_SIZE 360
#define SHORT_BOOK_ITEM_STRUCT_SIZE	264
#define SHORT_CONTAINER_ITEM_STRUCT_SIZE 276
struct Item_Struct
{
/*0000*/ char      name[64];        // Name of item
/*0064*/ char      lore[80];        // Lore text
/*0144*/ char      idfile[6];       // Not sure what this is used for
/*0150*/ int16    flag;
/*0152*/ uint8	   unknown0150[22]; // Placeholder
/*0174*/ uint8	   weight;          // Weight of item
/*0175*/ int8     norent;          // Nosave flag 1=normal, 0=nosave, -1=spell?
/*0176*/ int8     nodrop;          // Nodrop flag 1=normal, 0=nodrop, -1=??
/*0177*/ uint8     size;            // Size of item
/*0178*/ uint8      type;
/*0179*/ uint8     unknown0178;     // ***Placeholder
/*0180*/ uint16    item_nr;         // Unique Item number
/*0182*/ uint16    icon_nr;         // Icon Number
/*0184*/ int16    equipSlot;       // Current Equip slot
/*0186*/ uint8     unknwn0186[2];   // Equip slot cont.?
/*0188*/ uint32    equipableSlots;  // Slots where this item goes
/*0192*/ int32    cost;            // Item cost in copper
/*0196*/ uint8     unknown0196[32]; // ***Placeholder
union
{
	struct
	{
	// 0228- have different meanings depending on flags
	/*0228*/ int8    STR;              // Strength
	/*0229*/ int8    STA;              // Stamina
	/*0230*/ int8    CHA;              // Charisma
	/*0231*/ int8    DEX;              // Dexterity
	/*0232*/ int8    INT;              // Intelligence
	/*0233*/ int8    AGI;              // Agility
	/*0234*/ int8    WIS;              // Wisdom
	/*0235*/ int8    MR;               // Magic Resistance
	/*0236*/ int8    FR;               // Fire Resistance
	/*0237*/ int8    CR;               // Cold Resistance
	/*0238*/ int8    DR;               // Disease Resistance
	/*0239*/ int8    PR;               // Poison Resistance
	/*0240*/ uint16   HP;               // Hitpoints
	/*0242*/ uint16   MANA;             // Mana
	/*0244*/ uint16   AC;               // Armor Class
	/*0246*/ uint8    MaxCharges;       // Maximum number of charges, for rechargable? (Sept 25, 2002)
	/*0247*/ int8    GMFlag;           // GM flag 0  - normal item, -1 - gm item (Sept 25, 2002)
	/*0248*/ uint8    light;            // Light effect of this item
	/*0249*/ uint8    delay;            // Weapon Delay
	/*0250*/ uint8    damage;           // Weapon Damage
	/*0251*/ int8    clicktype;      // 0=combat, 1=click anywhere w/o class check, 2=latent/worn, 3=click anywhere EXPENDABLE, 4=click worn, 5=click anywhere w/ class check, -1=no effect
	/*0252*/ uint8    range;            // Range of weapon
	/*0253*/ uint8    itemType;            // Skill of this weapon, refer to weaponskill chart
	/*0254*/ int8    magic;            // Magic flag
                        //   00  (0000)  =   ???
                        //   01  (0001)  =  magic
                        //   12  (1100)  =   ???
                        //   14  (1110)  =   ???
                        //   15  (1111)  =   ???
	/*0255*/ int8    clicklevel2;           // Casting level
	/*0256*/ uint8    material;         // Material?
	/*0257*/ uint8    unknown0258[3];   // ***Placeholder
	/*0260*/ uint32   color;            // Amounts of RGB in original color
	/*0264*/ uint8    unknown0264[2];   // ***Placeholder (Asiel: Has to do with Diety, will unwrap later)
	/*0266*/ uint16   spell_effect_id;         // SpellID of special effect
	/*0268*/ uint16   classes;          // Classes that can use this item
	/*0270*/ uint8    unknown0270[2];   // ***Placeholder
	union
	{
		struct
		{
		/*0272*/ uint16   races;            // Races that can use this item
		/*0274*/ int8    unknown0274[2];   // ***Placeholder
		/*0276*/ int8    stackable;        //  1= stackable, 3 = normal, 0 = ? (not stackable)
		} normal;
	};
	/*0277*/ uint8    level;            // Casting level
	union // 0278 has different meanings depending on an stackable
	{
    /*0278*/ int8    number;          // Number of items in stack
    /*0278*/ int8    charges;         // Number of charges (-1 = unlimited)
	};
	/*0279*/ int8    effecttype;      // 0=combat, 1=click anywhere w/o class check, 2=latent/worn, 3=click anywhere EXPENDABLE, 4=click worn, 5=click anywhere w/ class check, -1=no effect
	/*0280*/ uint16   click_effect_id;         // spellId of special effect
	/*0282*/ uint8    unknown0282[10]; // ***Placeholder 0288
	/*0292*/ uint32   casttime;        // Cast time of clicky item in miliseconds
	/*0296*/ uint8    unknown0296[16]; // ***Placeholder
	/*0312*/ uint16   skillModPercent; // Skill mod value in % (Sept 25, 2002)
	/*0314*/ int16   skillModId;      // Skill mod index (Sept 25, 2002)
	/*0316*/ uint8    unknown0315[44]; // Bane and Elemental dmg struct (writing it now, hopefully will be up soon)
	} common;
	struct // Book Structure (flag == 0x7669)
	{
    /*0228*/ int8    unknown0172[6];      // ***Placeholder
    /*0234*/ char     file[15];            // Filename of book text on server
    /*0249*/ int8    unknown0190[15];    // ***Placeholder
	} book;
	struct // containers flag == 0x5400 or 0x5450
	{
		/*0228*/ int8    unknown0212[41];     // ***Placeholder
		/*0269*/ uint8    BagSlots;        // number of slots in container
		/*0270*/ int8    unknown0214;     // ***Placeholder
		/*0271*/ int8    BagSize;    // Maximum size item container can hold
		/*0272*/ uint8    weightReduction; // % weight reduction of container
		/*0273*/ uint8    unknown0273[3];     // ***Placeholder
		} container;
};
};

struct BulkedItem_Struct {
/*000*/	uint16		opcode;
/*002*/	Item_Struct	item;
};

/*
** Summoned Item - Player Made Item?
** Length: 244 Bytes
** OpCode: 7821
*/
struct SummonedItem_Struct
{
/*0000*/ struct Item_Struct item;        // Comment: Refer to itemStruct for members
};

/*
** Summoned Item waiting.
** Length: 3 Bytes
** 
*/
struct SummonedItemWaiting_Struct
{
/*0000*/ uint16 itemID;
/*0002*/ uint8  charge;
};

enum CONSUMETYPE : uint8
{
	CONSUMEFOOD = 0x01,						// Comment: Food
	CONSUMEDRINK = 0x02						// Comment: Drink
};

enum HOWCONSUMEDTYPE: uint32
{
	AUTO = 0xffffffff,				// Comment: Auto Consumed by the client as food/drink is needed
	RIGHTCLICKED = 222				// Comment: User has right clicked on food/drink to force eating/drinking
};

struct Consume_Struct
{
/*0000*/ uint32 slot;						// Comment: slot the food/drink is being consumed from
/*0004*/ HOWCONSUMEDTYPE auto_consumed;		// Comment: 
/*0008*/ uint8  c_unknown1[4];				// Comment: 
/*0012*/ CONSUMETYPE  Type;				// Comment: 
/*0013*/ uint8  unknown13[3];				// Comment: 
};

struct MoveItem_Struct
{
/*0000*/ uint32 from_slot;				// Comment: 
/*0004*/ uint32 to_slot;				// Comment: 
/*0008*/ uint32 number_in_stack;		// Comment: 
};

struct MoveCoin_Struct
{
/*0000*/ uint32 from_slot;			// Comment: 
/*0004*/ uint32 to_slot;			// Comment: 
/*0008*/ uint32 cointype1;			// Comment: 
/*0012*/ uint32 cointype2;			// Comment: 
/*0016*/ uint32 amount;				// Comment: 
};

struct Split_Struct
{
	uint32	platinum;
	uint32	gold;
	uint32	silver;
	uint32	copper;
};

/* Sp0tter - fixed the surname struct.
There are some more letters received in the unknown
range that still need to be identified, but as is
players can set thier surname and it saves it to the
database. Currently, it still sends a message to client
saying the name was not valid, but the client does recognize
the name.*/
struct Surname_Struct
{
	char name[16];				// Comment: Player's first name
	uint8 s_unknown1[20];		// Comment: Tazadar put 1 in this in order to accept the surname  ^^
	char Surname[30];			// Comment: Player's Surname (max size 20 limited by client)
};

/*
** Money Loot
** Length: 22 Bytes
** OpCode: 5020
*/
struct MoneyOnCorpse_Struct
{
/*0000*/ uint8	response;		// Comment: 0 = someone else is, 1 = OK, 2 = not at this time
/*0001*/ uint8	unknown1;		// Comment: = 0x5a
/*0002*/ uint8	unknown2;		// Comment: = 0x40
/*0003*/ uint8	unknown3;		// Comment: = 0
/*0004*/ uint32	platinum;		// Comment: Platinum Pieces
/*0008*/ uint32	gold;			// Comment: Gold Pieces
/*0012*/ uint32	silver;			// Comment: Silver Pieces
/*0016*/ uint32	copper;			// Comment: Copper Pieces
};

// size 292
struct ItemOnCorpse_Struct 
{
  Item_Struct item;				// Comment: 
};

struct LootingItem_Struct 
{
/*000*/	uint32	lootee;			// Comment: 
/*002*/	uint32	looter;			// Comment: 
/*004*/	uint16	slot_id;		// Comment: 
/*006*/	uint8	unknown3[2];	// Comment: 
/*008*/	uint32	type;			// Comment: 
};


// Size = 84 bytes
struct GMZoneRequest_Struct {
	char	charname[64];
	uint32	zoneID;
	uint8	unknown1[16];
	uint8	success; // 0 if command failed, 1 if succeeded?
	uint8	unknown2[3]; // 0x00
};

struct GMSummon_Struct {
/*  0*/	char    charname[64];
/* 30*/	char    gmname[64];
/* 60*/ uint32	success;
/* 61*/	uint32	zoneID;
/*92*/	int32  x;
/*96*/	int32  y;
/*100*/ int32  z;
/*104*/	uint8 unknown2[4]; // E0 E0 56 00
};


struct GMGoto_Struct { // x,y is swapped as compared to summon and makes sense as own packet
/*  0*/ char    charname[64];
/* 30*/ char    gmname[64];
/* 60*/ uint32   success;
/* 61*/ uint32   zoneID;

/*92*/  int32  x;
/*96*/  int32  y;
/*100*/ int32  z;
/*104*/ uint32 unknown2; // E0 E0 56 00
};



/*struct GMGoto_Struct 
{
	char	gotoname[30];		// Comment: 
	char	myname[30];			// Comment: 
	uint8	unknown[48];		// Comment: 
};*/

struct GMSurname_Struct 
{
	char name[64];			// Comment: 
	char gmname[64];		// Comment: 
	char Surname[32];		// Comment: 
	uint8 unknown[2];		// Comment: 0x00, 0x00, 0x01, 0x00 = Update the clients
};

//Dueling
struct Duel_Struct
{
int32 duel_initiator;
int32 duel_target;
};

struct DuelResponse_Struct
{
int32 target_id;
int32 entity_id;
int8 response[2];
};

//Combat Abilities
struct CombatAbility_Struct
{
	uint32 m_id;			// Comment: 
	uint32 m_atk;		// Comment: 
	uint32 m_type;		// Comment: 
};

//Instill Doubt
struct Instill_Doubt_Struct 
{
	uint8 i_id;			// Comment: 
	uint8 ia_unknown;	// Comment: 
	uint8 ib_unknown;	// Comment: 
	uint8 ic_unknown;	// Comment: 
	uint8 i_atk;			// Comment: 
	uint8 id_unknown;	// Comment: 
	uint8 ie_unknown;	// Comment: 
	uint8 if_unknown;	// Comment: 
	uint8 i_type;		// Comment: 
	uint8 ig_unknown;	// Comment: 
	uint8 ih_unknown;	// Comment: 
	uint8 ii_unknown;	// Comment: 
};

//Pick Pockets struct verified by Wizzel
struct PickPockets_Struct {
// Size 18
    uint16 to;
    uint16 from;
    uint8 myskill;
    uint8 unknown0;
    uint8 type; // -1 you are being picked, 0 failed , 1 = plat, 2 = gold, 3 = silver, 4 = copper, 5 = item
    uint8 unknown1; // 0 for response, unknown for input
    uint32 coin;
    uint8 lastsix[6];
};

// This is only being used for fishing right now,
// but i think it gets used for more abilities (Sp0tter). That would make sense (Dark-Prince)
struct UseAbility_Struct 
{
	uint16 player_id;	// Comment: Entity ID
	uint8  unkown[10];	// Comment: Only two of these bytesever have values.  Guessing lore and skill.
};



struct GiveItem_Struct 
{
	uint16 to_entity;		// Comment: 
	int16 to_equipSlot;	// Comment: 
	uint16 from_entity;		// Comment: 
	int16 from_equipSlot;	// Comment: 
};


struct CancelTrade_Struct { 
	uint16 fromid;
	uint16 action;
	uint8 unknown1337[4];
};


struct Random_Struct 
{
	uint32 low;		// Comment: 
	uint32 high;		// Comment: 
};

//Yeahlight: Old LFG_Struct (DO NOT DELETE)
//struct LFG_Struct 
//{
//	char	name[64];	// Comment: 
//	uint32	value;		// Comment: 
//};

//Yeahligth: New LFG_Struct
struct LFG_Struct 
{
	char	name[64 + 2];	// Comment: 
	uint32	value;		// Comment: 
};

// EverQuest Time Information:
// 72 minutes per EQ Day
// 3 minutes per EQ Hour
// 6 seconds per EQ Tick (2 minutes EQ Time)
// 3 seconds per EQ Minute
struct TimeOfDay_Struct 
{
	uint8	hour;			// Comment: 
	uint8	minute;			// Comment: 
	uint8	day;			// Comment: 
	uint8	month;			// Comment: 
	uint16	year;			// Comment: Kibanu - Changed from long to uint16 on 7/30/2009
};

struct Merchant_Click_Struct {
/*000*/ uint16	entityid;			// Merchant NPC's entity id
/*002*/ uint16	playerid;
/*004*/ uint8	unknown[8]; /*
0 is e7 from 01 to // MAYBE SLOT IN PURCHASE
1 is 03
2 is 00
3 is 00
4 is ??
5 is ??
6 is 00 from a0 to
7 is 00 from 3f to */
/*
0 is F6 to 01
1 is CE CE
4A 4A
00 00
00 E0
00 CB
00 90
00 3F
*/
};			
struct Merchant_Purchase_Struct {
/*000*/	uint16	npcid;			// Merchant NPC's entity id
/*002*/	uint16	playerid;		// Player's entity id
/*004*/	uint16	itemslot;
/*006*/	uint8	IsSold;		// Already sold
/*007*/	uint8	unknown001;	// always 0x0b, 0x7c, 0x00 ??
//		uint8	unknown002;  On live, it looks like it is only 16 bytes now and quanity is put at byte 9 (Hogie on 12/29/2002)
/*008*/	uint8	quantity;		// Qty - when used in Merchant_Purchase_Struct
/*009*/	uint8	unknown003;
/*010*/	uint8	unknown004;
/*011*/	uint8	unknown005;
/*012*/	int32  itemcost;
};

struct Item_Shop_Struct {
	uint16 merchantid;
	uint8 itemtype;
	Item_Struct item;
	uint8 iss_unknown001[6];
};

struct Merchant_DelItem_Struct{
/*000*/	uint32	npcid;			// Merchant NPC's entity id
/*004*/	uint32	playerid;		// Player's entity id
/*008*/	uint8	itemslot;       // Slot of the item you want to remove
/*009*/	uint8	unknown[3];
};

 struct ItemToTrade_Struct { 
/*000*/	uint32 playerid;
/*004*/	uint16 to_slot;
/*006*/	uint8 unknown_1;
/*007*/	Item_Struct item;
	    uint8  unknown02[3];
};

// 4-20-08 (Wizzel)
// Received when a client uses an illusion related action.
// Size: 72 Bytes
// OpCode: 9120
// Notes: Fucking finally... ;p
struct Illusion_Struct 
{ 
/*0000*/ char   name[16];
/*0016*/ uint8	unknown1[4]; // usually 00 00 00 00
/*0020*/ uint8	unknown2[4]; // dictated by packet, maybe zone but got 00 00 00 00 in grobb
/*0024*/ uint8	unknown3[4];
/*0028*/ uint8	unknown4[2];
/*0030*/ char	target[16];
/*0046*/ uint8	unknown5[2];
/*0048*/ uint16	jackbauer; //always 24
/*0050*/ uint16	unknown7;
/*0052*/ uint16  unknown8;
/*0054*/ uint16	unknown9; //00 00
/*0056*/ uint8	unknown10[4];
/*0060*/ uint8	unknown11[2];
/*0062*/ uint16	race; // 01 = human 02 = barbarian, etc
/*0064*/ uint16	gender; // 00 = male 01 = female 02 = neuter, 02 is default if nothing is entered.
/*0066*/ uint16	texture; // 00 = cloth 01 = leather FF = default
/*0068*/ uint16	helm; // 00 = cloth 01 = leather FF = default
/*0070*/ uint16	face; // 00 = cloth 01 = leather FF = default
};

struct CPlayerItems_packet_Struct 
{
/*000*/	uint16		opcode;		// Comment: OP_ItemTradeIn
/*002*/	Item_Struct	item;		// Comment: 
};

struct CPlayerItems_Struct 
{
/*000*/	uint16		count;							// Comment: 
/*002*/	CPlayerItems_packet_Struct	packets[0];		// Comment: 
};

//By Scruffy... Thanks ShowEQ and sins!
struct SkillUpdate_Struct 
{
	uint8 skillId;			// Comment: 
	uint8 unknown1[3];		// Comment: 
	uint8 value;			// Comment: 
	uint8 unknown2[3];		// Comment: 
};

struct ZoneUnavail_Struct 
{
	//This actually varies, but...
	char zonename[16];		// Comment: 
	short int unknown[4];	// Comment: 
};

struct GroupInvite_Struct 
{
	char invited[64];		// Comment: 
	char inviter[64];		// Comment: 
	char unknown[31];		// Comment: 
};


/* Do not touch this please.  Used to add and 
 * remove group members from a group. Maybe more.*/
struct GroupUpdate_Struct
{
	char	receiverName[32];	//Member who needs new info;
	char	senderName[32];		//Member with new info;
	char	senderName2[32];	//? testing, but not working yet
	uint8	unknown01[128];		
	uint8	action;				//0: Player joins the group;		
								//1: ??
								//2: ??
								//3: Player leaves the group;	
								//4: You leave the group;		
};

struct GroupFollow_Struct
{
	char leader[64];		// Comment: 
	char invited[64];		// Comment: 
};

/* Sent when player clicks disband after receiving an invite 
 * or if a player is already grouped and gets an invite it 
 * is sent automaticaly. */
struct GroupInviteDecline_Struct{
	char leader[64];		//Player1 who invited another Player2;
	char leaver[64];		//Player2 who is declining/unable to accept invite from Player1;
	uint8 action;			//Type of decline:
							//	1: 'leaver' is considering another group invite;
							//	2: 'leaver' already grouped;
							//	3: 'leaver' rejects your offer to join the group;
};

struct GroupDisband_Struct 
{
	char member[15];		// Comment: 
	char unknown1[41];		// Comment: 
	uint8 framecounter;		// A frame counter that increments by 32 each time same client sends this code;
 	char unknown2[3];
};

struct ChangeLooks_Struct 
{
/*000*/	uint8	haircolor;	// Comment: 
/*001*/	uint8	beardcolor;	// Comment: 
/*002*/	uint8	eyecolor1;	// Comment: the eyecolors always seem to be the same, maybe left and right eye?
/*003*/	uint8	eyecolor2;	// Comment: 
/*004*/	uint8	hairstyle;	// Comment: 
/*005*/	uint8	wode;		// Comment: Face Overlay? (barbarian only)
/*006*/	uint8	face;		// Comment: and beard
};

struct Trade_Window_Struct 
{
	uint32 fromid;			// Comment: 
	uint32 toid;				// Comment: 
};

struct TradeMoneyUpdate_Struct{
	uint32	trader;			// Comment: 
	uint32	type;		 // Comment: 
	uint32	amount;			// Comment: 
};

struct TradeCoin_Struct{
	uint32	trader;		// Comment: 
	uint8	slot;		// Comment: 
	uint16	unknown5;		// Comment: 
	uint8	unknown7;		// Comment: 
	uint32	amount;			// Comment: 
	uint8	unknown8[10];	// Comment:
};

struct Give_Struct 
{
	uint16 unknown[2];		// Comment: 
};

struct PetitionClientUpdate_Struct 
{
	uint32 petnumber;		// Comment: Petition Number
	uint32 color;			// Comment: 0x00 = green, 0x01 = yellow, 0x02 = red
	uint32 senttime;			// Comment: 
	uint8 unknown[4];		// Comment: 4 has to be 0x1F
	char accountid[32];		// Comment: 
	char gmsenttoo[32];		// Comment: 
	uint32 something;		// Comment: 
	char charname[64];		// Comment: 
};

struct Petition_Struct 
{
	uint32 petnumber;			// Comment: 
	uint32 urgency;				// Comment: 
	char accountid[32];			// Comment: 
	char lastgm[32];			// Comment: 
	char zone[32];				// Comment: 
	char charname[64];			// Comment: 
	uint32 charlevel;			// Comment: 
	uint32 charclass;			// Comment: 
	uint32 charrace;				// Comment: 
	time_t senttime;			// Comment: Time?
	uint32 checkouts;			// Comment: 
	uint32 unavail;				// Comment: 
	uint8 unknown5[4];			// Comment: 
	char petitiontext[1024];	// Comment: 
};

/* 
	Bug_Report tested by Sp0tter.  It is currently linked to the database 'bug_report'
	table.  I've added the table to the /create fold in the database dir
	so just source that and any bug reporting will go straight to the database.
	It still needs sql injection handling.
*/
struct Bug_Report_Struct
{
	char playername[72];		// Comment: Players name
	uint8 blankspot1;			// Comment: not used
	uint8 cannotuplicate;		// Comment: 1 for cannot duplicate, 0 for can duplicate
	uint8 noncrashbug;			// Comment: 1 for does NOT crash, 0 for does cause crash
	char bugdescription[1024];	// Comment: The bug description
};

// Comment: 76 length in total
struct Who_All_Struct 
{
	char whom[32];		// Comment: 
	uint16 wrace;		// Comment: FF FF = no race
	uint16 wclass;		// Comment: FF FF = no class
	uint16 firstlvl;		// Comment: FF FF = no numbers
	uint16 secondlvl;	// Comment: FF FF = no numbers
	uint16 gmlookup;		// Comment: FF FF = not doing /who all gm
	uint8 unknown[34];	// Comment: 

};

// Comment: 4 bytes in total
struct Stun_Struct 
{
	uint32 duration;		// Comment: Duration of stun
};

// Size: 32 Bytes
struct Combine_Struct 
{ 
	uint8 worldobjecttype;	// Comment: Harakiri if its a world object like forge, id will be here
	uint8 unknown001;		// Comment: 
	uint8 unknown002;		// Comment: 
	uint8 unknown003;
	uint16 containerslot;	// Comment: the position of the container, or 1000 if its a world container	
	uint16 iteminslot[10];	// Comment: IDs of items in container
	uint16 unknown005;		// Comment: 
	uint16 unknown006;		// Comment: 
	uint16 containerID;		// Comment: ID of container item
};

struct Emote_Text
{
	uint16 unknown1;			// Comment: 
	char message[1024];		// Comment: 
};


struct Social_Action_Struct 
{
	uint8 unknown1[4];	// Comment: 
	uint8 action;		// Comment: 
	uint8 unknown2[7];	// Comment: 
};

//Size: 8  (Request)
struct InspectRequest_Struct 
{ 
	uint32 TargetID;		// Comment: 
	uint32 PlayerID;		// Comment: 
}; 

//Size: 1044 (Answer)
struct InspectAnswer_Struct 
{ 
	uint32 TargetID;			// Comment: ? 
	uint32 PlayerID;			// Comment: ?
	uint8  unknown[1036];	// Comment: ?
}; 


struct SetDataRate_Struct 
{
	float newdatarate;	// Comment: 
};


struct SetServerFilter_Struct 
{
	uint8 unknown[60];	// Comment: 
};

struct SetServerFilterAck_Struct 
{
	uint8 blank[8];		// Comment: 
};

struct GMName_Struct 
{
	char oldname[64];	// Comment: 
	char gmname[64];	// Comment: 
	char newname[64];	// Comment: 
	uint8 badname;		// Comment: 
	uint8 unknown[3];	// Comment: 
};

struct GMDelCorpse_Struct 
{
	char corpsename[64];	// Comment: 
	char gmname[64];		// Comment: 
	uint8 unknown;			// Comment: 
};

struct GMKick_Struct 
{
	char name[64];		// Comment: 
	char gmname[64];	// Comment: 
	uint8 unknown;		// Comment: 
};

struct GMKill_Struct 
{
	char name[64];		// Comment: 
	char gmname[64];	// Comment: 
	uint8 unknown;		// Comment: 
};

struct GMEmoteZone_Struct 
{
	char text[512];		// Comment: 
};

// This is where the Text is sent to the client.
// Use ` as a newline character in the text.
// Variable length.
struct BookText_Struct 
{
	char* booktext;		// Comment: Variable Length
};

// This is the request to read a book.
// This is just a "text file" on the server
// or in our case, the 'name' column in our books table.
struct BookRequest_Struct 
{
	char txtfile[14]; // Comment: 
};

// 6-01-08 - Wizzel
// Recieved when player right clicks on guildmaster of his/her own guild
// Size: 148 Bytes
// OpCode: 9c20

struct ClassTrain_Struct{
	/*000*/ uint32 npcid;
	/*002*/ uint32 playerid;
	/*004*/ uint8  highesttrain[73];
	        uint8	unknown[32];
			uint8	highesttrainLang[24];
	/*004*/ uint8 unknown2[107];
};

struct ClassSkillChange_Struct {
/*000*/	uint32	npcid;
/*004*/ uint32	skill_type;	// 0=regular skills, 1=languages (Harakiri)
/*008*/ uint32	skill_id;		// Skill trained
};



// Harakiri Struct for Clients Request to Show specific message board
struct MBRetrieveMessages_Struct{
	uint8 entityID;
	uint8 unknown[3];
	uint8 category; // category is the type of board selected by the client
	/* 00 - OFFICIAL */
	/* 01 - FOR SALE */
	/* 02 - GENERAL */
	/* 03 - HELP WANTED */
	/* 04 - PERSONALS */
	/* 05 - GUILDS */
	uint8 unknown2[3];
};

// Valids of Guild Rank
enum GUILDRANK
{
	GuildUnknown = -1,		// Comment: Unknown guild rank
	GuildMember = 0,		// Comment: Guild Leader
	GuildOffice = 1,		// Comment: Guild Officer
	GuildLeader = 2,		// Comment: Guild Member
	NotInaGuild = 3,		// Comment: Char is not in a guild
	GuildInviteTimeOut = 4, // Comment: Client Invite Window has timed out
	GuildDeclined = 5		// Comment: User Declined to join Guild
				
};

struct GuildRankLevel_Struct 
{
	char rankname[101];		// Comment: 
	bool heargu;			// Comment: 
	bool speakgu;			// Comment: 
	bool invite;			// Comment: 
	bool remove;			// Comment: 
	bool promote;			// Comment: 
	bool demote;			// Comment: 
	bool motd;				// Comment: 
	bool warpeace;			// Comment: 
};

struct Guild_Struct
{
	char name[32];			// Comment: 
	uint32 databaseID;		// Comment: 
	uint32 leader;			// Comment: AccountID of guild leader
	GuildRankLevel_Struct rank[512+1];	// Comment: 
};

struct GuildsListEntry_Struct 
{
	uint32 guildID;				// Comment: empty = 0xFFFFFFFF
	char name[32];				// Comment: 
	uint8 unknown1[4];			// Comment: = 0xFF
	uint8 exists;				// Comment: = 1 if exists, 0 on empty
	uint8 unknown2[7];			// Comment: = 0x00
	uint8 unknown3[4];			// Comment: = 0xFF
	uint8 unknown4[8];			// Comment: = 0x00
};

struct GuildsList_Struct 
{
	uint8 head[4];							// Comment: 
	GuildsListEntry_Struct Guilds[512];		// Comment: 
};


struct GuildUpdate_Struct
{
	uint32	guildID;				// Comment: 
	GuildsListEntry_Struct entry;	// Comment: 
};

// Guild invite, remove
struct GuildCommand_Struct
{
	char Invitee[30];			// Comment: Person who is being invited (Dark-Prince - 11/05/2008) (myname)
	char Inviter[30];			// Comment: Person who did /guildinvite (Dark-Prince - 11/05/2008) (othername)
	uint16 guildeqid;			// Comment: 
	uint8 unknown[2];			// Comment: for guildinvite all 0's, for remove 0=0x56, 2=0x02
	uint32 rank;					// rank
};

struct GuildInvite_Struct
{
	char Invitee[64];
	char Inviter[64];
	uint16 guildeqid;
	uint8 unknown[2];
	uint32 rank;
};

struct GuildRemove_Struct
{
	char Remover[64];
	char Removee[64];
	uint16 guildeqid;
	uint8 unknown[2];
	uint32 rank;
};

// Harakiri struct for deleting a specific message
struct MBEraseMessage_Struct{
/*0000*/ uint32 entityID;	
/*0004*/ uint32 id; /* id of the message	
/*0008*/ uint8 category;
/*0009*/ uint8 unknown3[3];
}; 

// Harakiri struct for retrieving a specific message
struct MBRetrieveMessage_Struct{
/*0000*/ uint32 entityID;	
/*0004*/ uint32 id; /* id of the message	
/*0008*/ uint8 category;
/*0009*/ uint8 unknown3[3];
}; 


// Harakiri Struct for of a message
struct MBMessage_Struct{		
/*0000*/ uint32 id; 
/*0004*/ char date[10]; /* char year[2]; char month[2]; char day[2];
/*0014*/ uint8 unknown2[6];
/*0020*/ char author[64];
/*0050*/ uint8 unknown3[2];
/*0052*/ uint8 language;
/*0053*/ uint8 unknown4;
/*0054*/ char subject[29];
/*0083*/ uint8 unknown5[3];
/*0086*/ uint8 category;
/*0087*/ uint8 unknown6;
/*0088*/ char message[2048]; // see eqgame function at .text:0047D4E5
}; 


// Harakiri Filter Types for Message Board
enum MESSAGEBOARD_CATEGORY
{
	OFFICIAL, 
	FOR_SALE, 
	GENERAL, 
	HELP_WANTED,
	PERSONALS, 
	GUILDS 
};

struct Door_Struct
{
/*0000*/ char    name[16];            // Filename of Door // Was 10char long before... added the 6 in the next unknown to it: Daeken M. BlackBlade
/*0016*/ float   yPos;               // y loc
/*0020*/ float   xPos;               // x loc
/*0024*/ float   zPos;               // z loc
/*0028*/ float	 heading;
/*0032*/ float   incline;
/*0036*/ uint16	 size;
/*0038*/ uint8	 doorid;             // door's id #
/*0039*/ uint8	 opentype;
/*0040*/ uint8	 doorIsOpen;
/*0041*/ uint16	 inverted;		//FFFF
/*0043*/ uint16	 parameter; 
/*0045*/ uint8	 unknown[2];
};

/******Useful Open Types*******/
//53: Spell Particle Effect
//55: Bulletin Board
/******************************/

/****Yeahlight: OpenType '53' accompanied by the 'inverted' flag results in a static spell effect, which are listed below:
1:   Healing orb (blue sphere)
2:   Buff aura (lots of color moving towards the center)
3:   Rain of fire (Orange flames)
4:   Summon item (green cone)
5:   Vision buff (White small effects)
6:   Healing cone (blue cone)
7:   Misc buff (blue particles spreading from center)
8:   Misc buff (large orange explosions)
9:   Invis/Gate (blue/white balls)
10:  Poison debuff (Large green balls and small green balls)
11:  ?? (Fast moving gold balls and a gold ball aura)
12:  Dispell (Slow moving blue balls and blue sphere)
13:  ?? (Fast moving orange balls on 2 planes, moving from center)
14:  Bind (Very slow moving blue balls and blue sphere)
15:  Stun (Very fast moving red effects on two planes)
16:  Root (Green circles moving outward from center)
17:  ?? (Three different blue effects in static positions from center)
18:  Rain of fire (Small orange flames)
19:  Cannabalize (Blue clouds moving to center)
20:  Lifetap Cast (Green balls moving to center)
21:  ?? (Lots going on here: Sphere of blue crystals, small blue balls moving outward, big blue balls moving outward slowly)
22:  ?? (Medium size white balls moving slowly outward, almost makes a sphere)
23:  ?? (Blue crystals)
24:  Lifetap or Poison (Green balls spewing everywhere)
25:  Stun (Red sphere and red balls moving outward
26:  ?? (Small blue balls rising strait up and small blue balls moving away from center)
27:  ?? (Green balls raining down from center on a plane, small blue balls rising from center on a plane and yellow balls forming a sphere from center)
28:  ?? (Green circle raining green balls towards center)
29:  ?? (Small orange balls forming a ring in center with orange puffs moving to center)
30:  Healing cone (Blue healing cone flipped on axis)
31:  Fire (Fire with orange balls)
32:  ?? (Blue crystals with blue balls moving upwards from center with blue smoke moving upwards)
33:  ?? (Small teal balls raining from center with static blue buffs forming a sphere)
34:  Poison debuff (Small green balls raining down fast from center)
35:  Harvest (Many blue balls moving away in two directions from center forming large walls)
40:  ?? (Very few blue blues flashing and a blue ring)
41:  ?? (Small orange flames flickering in a sphere with a ring of orange buffs in center)
42:  ?? (Gold star forming a sphere and random gold dots moving updwards from center)
43:  ?? (Small white balls raining from center with very very small blue dots appearing randomly)
44:  ?? (A sun type effect with orange dots raining from it)
45:  ?? (A sphere a blue dots raining downwards)
46:  ?? (A sphere of green dots raining outwards)
47:  ?? (A sphere of whote dots raining outwards with small blue dots mixed in)
48:  ?? (Orange dots on a flat plane running outwards from center (disc like))
49:  Jboots (Red effects moving towards center quickly)
50:  ?? (Blue dots forming a sphere and flickering)
51:  Manastone (Green skulls forming a sphere
66:  ?? (A small pale-green sprinkler)
67:  ?? (same as above)
68:  ?? (same as above)
69:  ?? (same as above)
105: Smoke stack
110: Flame (single orange flame)
111: Flames (8ish orange flames)
112: Flames (15ish orange flames)
113: ?? (Sphere of orange flames)
114: ?? (Large sphere of orange flames)
115: Smoke stack (GIGANTIC smoke stack, can be seen for miles)
116: ?? (Pale blue sprinkler)
117: ?? (same as 116)
118: ?? (Pale blue sprinkler, little different from 116)
120: ?? (Sphere of red sparkles)
121: ?? (Sphere of orange sparkles)
122: ?? (Sphere of few blue dots)
123: ?? (Sphere of blue sparkles)
124: Sprinkler (blue sparkles rushing out of a single hole)
125: Sprinkler (orange sparkles rushing out of a single hole)
126: Sprinkler (smaller blue sparkles rushing out of a single hole)
127: Sprinkler (pale red sparkles rushing out of a single hole)
128: Water fall (Blob of steam)
129: Water fall (Steam rushing from a single hole)
130: Fire ("Realistic" fire effect)
131: Pulsing HUGE white star
132: Sprinkler (large steam puffs)
133: Water fall (same as 128)
134: Water fall (same as 129)
143: Water fall (same as 128)
144: Water fall (same as 128)
145: ?? (Blue sparkles raining down randomly)
146: ?? (Same as 145 but smaller)*/

struct DoorSpawns_Struct	//SEQ
{
	uint16 count;            
	struct Door_Struct doors[0];
};

struct ClickDoor_Struct {
	uint8	doorid;
	uint8	unknown[3];
	uint16	keyid;
	uint16	playerid;
};

struct DoorOpen_Struct {
	uint8	doorid;
	uint8	action;
};

struct LSAuth_Struct {
	uint32	lsaccount_id;
	char	name[19];
	char	key[16];
	bool	stale;
	bool	inuse;
	bool	firstconnect;
};

// Dark-Prince 22/12/2007
// Added this struct for eqemu and started eimplimentation ProcessOP_SendLoginInfo
//TODO: confirm everything in this struct
struct LoginInfo_Struct {
/*000*/	char	AccountName[127];	// Length confirmed - Dark-Prince 22/12/2007
/*064*/	char	Password[24];		// Length confirmed - Dark-Prince 22/12/2007
/*189*/	uint8	unknown189[45];		//TODO: Find out wtf is this one and confirm size
/*196*/
};

// Dark-Prince 22/12/2007
// Added this struct for eqemu and started eimplimentation ProcessOP_SendLoginInfo
//TODO: confirm everything in this struct
// this packet is a variable length...cuz its based on name
struct EnterWorld_Struct {
/*000*/	char	charname[64];	//TODO: Confirm length - Set to 30 for char name which is the same size as the name in playerprofile struct
};

// Dark-Prince 22/12/2007
//TODO: work on this
struct NameApproval_Struct
{
	char charname[64];
	uint32 race;
	uint32 class_;
	uint32 deity;
};


// Harakiri
// This can be sent on multiple occasions
// i.e. player vodka or is removed when using arrows
// or we sent OP_InitiateConsume - it can even be an item in a bag
//OpCode: 4621 Size: 12 bytes
struct ConsumeItem_Struct
{
	uint16 slot;			//The slot id of the item consumed
	uint8 other[2];		//These are all 0x00.
	uint32 filler[2];	//These are both always 0xFFFFFFFF.
};

// Dark-Prince 22/12/2007 - Added this as it appears to be different to the 
//							other Server_Motd_struct (notice case) in servertalk.
struct ServerMOTD_Struct
{
	char motd[500];
};

// Dark-Prince 29/01/2008 - In dev
struct ChangeWeather_Struct
{
/*000*/	uint32 type;
/*004*/	uint32 intensity;
};

// 4-20-08 (Yeahlight)
// Received when a client executes the /target command
// Size: 4 Bytes
// OpCode: fe21
struct BackSlashTarget_Struct
{
	uint16  bst_target;              // Target ID
	uint16  bst_unknown1;             // ***Placeholder
};

// 4-23-08 (Yeahlight)
// Received when a client executes the /assist command
// Size: 4 Bytes
// OpCode: 0022
struct BackSlashAssist_Struct
{
	uint16 bsa_target;
	uint16 bsa_unknown1;
};

struct Make_Pet_Struct { //Simple struct for getting pet info Tazadar 01/06/08
	uint8 level;
	uint8 class_;
	uint16 race;
	uint8 texture;
	uint8 pettype;
	float size;
	uint8 type;
	uint32 min_dmg;
	uint32 max_dmg;
    int32  max_hp;
};


struct GuildInviteAccept_Struct {
	char inviter[30];
	char newmember[30];
	uint32 rank;
	uint32 guildeqid;
};

// 6-22-08 - Wizzel
// Recieved when player steps onto a boat
// Size: 30 Bytes
// OpCode: bb21
struct Boat_Struct{
	char boatname[64]; //Tazadar: Changed the lenght of the name
};

// 6-24-08 - Wizzel
// Recieved when player right clicks a pilotable boat
// Size: 8 Bytes
// OpCode: bb21
struct CommandBoat_Struct{
	uint8 unknown[8];
};

//Yeahlight: Struct for pulling zoneline data from DB
struct zoneLine_Struct
{
	uint16 id;
	char zone[16];
	float x;
	float y;
	float z;
	char target_zone[16];
	float target_x;
	float target_y;
	float target_z;
	uint16 range;
	uint8 heading;
	uint16 maxZDiff;
	uint8 keepX;
	uint8 keepY;
	uint8 keepZ;
};

// Harakiri this is the generic teleport struct
// used to teleport a player
struct TeleportPC_Struct
{
/*0000*/ char zone[16];
/*0016*/ uint8 unknown2[16];			
/*0032*/ float   yPos;          // Harakiri y loc
/*0036*/ float   xPos;          // Harakiri x loc			
/*0040*/ float   zPos;          // Harakiri z loc
/*0044*/ float	 heading;		// Harakiri will be divided by 2 by the client
};

// Harakiri
// This is sent to the client for translocate requests
// This is sent back from the client to the server if the request was either confirmed or denied
struct Translocate_Struct
{
/*0000*/ char zone[16];
/*0016*/ uint8 unknown[16];
/*0032*/ uint16 spellID; // Harakiri: ID of the translocate spell being cast, Client will popup "..translocated to your bind point?" if it is translocate 1422 or group translocate 1334
/*0034*/ uint8 unknown1[6];
/*0040*/ char caster[16];
/*0056*/ uint8 unknown2[16];
/*0072*/ float y;		// Harakiri translocate to this Y pos - the client will set this in the local playerProfile to have up2date values for save client request i think
/*0076*/ float x;		// Harakiri translocate to this X pos - the client will set this in the local playerProfile to have up2date values for save client request i think
/*0080*/ float z;		// Harakiri translocate to this Z pos - the client will set this in the local playerProfile to have up2date values for save client request i think			
/*0084*/ uint32 confirmed; // Harakiri Step 1 the server sents the initial request to the client, should be 0 = Confirmation box to player
						   // Harakiri Step 2 the client will response with this struct, if confirmed it will be 1 
						   // Harakiri Step 3 the server will response with the actual translocate this time confirmed is again 1
};

//Yeahlight: 0x8c21, 8
struct BecomeNPC_Struct 
{
/*0000*/ uint32 entityID;
/*0004*/ uint8 attackLevel;
/*0005*/ uint8 unknown[3];
};

//Yeahlight: Struct for NPC roam boxes
struct RoamBox_Struct
{
	uint16 id;
	float max_x;
	float min_x;
	float max_y;
	float min_y;
};
//Tazadar : Boat Commands
enum BOATCOMMANDS
{
	CHECK_FAMILY, // Check others boats before departing
	SPAWN, // Spawn the boat
	TELEPORT_PLAYERS, // Teleport player to the other zone
	GOTO, // Move boat to node number numnode
	WAIT, // Wait at zone/dock for timeneeded
	ROTATE, // Rotate the boat
};
//Tazadar : Struct for Boats routes
struct WorldBoatCommand_Struct
{
	BOATCOMMANDS cmd;
	std::string zonename;
	union {
		struct 
		{
			float x;
			float y;
			float z;
			float heading;
		}position;
		struct
		{
			uint32 from_node; // -1 means that we keep the old one
			uint32 to_node;
			uint32 timeneeded;
		}go_to;
	};

};

//Tazadar : Struct for Boats routes
struct ZoneBoatCommand_Struct
{
	BOATCOMMANDS cmd;
	float x;
	float y;
	union {
		struct 
		{
			float speed;
		}go_to;
		struct
		{
			float heading;
		}rotate;
	};

};

//Yeahlight: Struct for the zone to communicate its status with World
struct ZoneStatus_Struct
{
	uint16 zoneID;
};

//Yeahlight: No idea what this is used for, but it creates a
//           perminent object that no client may interact with.
//			 It also accepts spell sprites (i.e., GENC00), but 
//			 they do not currently display. I guess we could use 
//			 this for GM events?
//
//Opcode: 0xF620
struct ObjectDisplayOnly_Struct
{
/*0000*/ char test1[32];
/*0032*/ char modelName[16];	//Yeahlight: Confirmed (Note: The filename suffix is ASSUMED. Only use the filename prefix like 'PLAT' or 'IT10')
/*0048*/ char test2[12];
/*0060*/ float size;			//Yeahlight: Confirmed
/*0064*/ float y;				//Yeahlight: Confirmed
/*0068*/ float x;				//Yeahlight: Confirmed
/*0072*/ float z;				//Yeahlight: Confirmed
/*0076*/ float heading;			//Yeahlight: Confirmed
/*0080*/ float tilt;			//Yeahlight: Confirmed
/*0084*/ char test4[40];
};

//Yeahlight: Size: 116 (0x74u)
//           OpCode: 0x4520
struct SpawnProjectile_Struct
{
/*0000*/ uint32 always1;				// Comment: Yeahlight: ASM claims that this member should always be a value of 1
/*0004*/ uint32 always0;				// Comment: Yeahlight: ASM claims that this member should always be a value of 0
/*0008*/ uint32 test1;				// Comment: Yeahlight: Unknown (ASM claims that this member is defined by the client and size uint32)
/*0012*/ float y;					// Comment: Yeahlight: Object's y coordinate (Verified to be float)
/*0016*/ float x;					// Comment: Yeahlight: Object's x coordinate (Verified to be float)
/*0020*/ float z;					// Comment: Yeahlight: Object's z coordinate (Verified to be float)
/*0024*/ float heading;				// Comment: Yeahlight: Object's heading (Verified to be float)
/*0028*/ float tilt;				// Comment: Yeahlight: Object's tilt (Verified to be float)
/*0032*/ float velocity;			// Comment: Yeahlight: Object's velocity (Verified to be float)
/*0036*/ float burstVelocity;		// Comment: Yeahlight: Incremental velocity on the object during its first second of travel (Verified to be float)
/*0040*/ float burstHorizontal;		// Comment: Yeahlight: Shoves the object along the horizontal plane during its first second of travel (Verified to be float)
/*0044*/ float burstVertical;		// Comment: Yeahlight: Shoves the object along the vertical plane during its first second of travel (Verified to be float)
/*0048*/ float yaw;					// Comment: Yeahlight: Rotation around the z-axis (Verified to be float)
/*0052*/ float pitch;				// Comment: Yeahlight: Rotation around the x-axis (Verified to be float)
/*0056*/ float arc;					// Comment: Yeahlight: Applies a gravitational arc on the object (Verified to be float)
/*0060*/ uint8 test5[4];				// Comment: Yeahlight: Unknown (ASM claims that this member is defined by the client)
/*0064*/ uint32 sourceID;			// Comment: Yeahlight: Entity ID of the projectile's inflictor (Verified to be uint32)
/*0068*/ uint32 targetID;			// Comment: Yeahlight: Entity ID of the projectile's inflictee (Verified to be uint32)
/*0072*/ uint16 test6;				// Comment: Yeahlight: Unknown (ASM claims that this member is defined by the client and size uint16)
/*0074*/ uint16 test7;				// Comment: Yeahlight: Unknown (ASM claims that this member is defined by the client and size uint16)
/*0076*/ uint32 spellID;				// Comment: Yeahlight: Spell ID of the projectile (ASM claims uint32)
/*0080*/ uint8 lightSource;			// Comment: Yeahlight: Light source on the object (ASM claims uint8)
/*0081*/ uint8 test9;				// Comment: Yeahlight: Unknown (ASM claims uint8)
/*0082*/ uint8 spawnBehavior;		// Comment: Yeahlight: Boolean flag to enable the attack animation and spawn of the arrow projectile (See 0x11/0x1B below)
									//                     OR used to grant extended life to a spell projectile (See 0x09 below) (ASM claims uint8)
/*0083*/ uint8 projectileType;		// Comment: Yeahlight: 0x09 - Spell bolt, 0x11 - Arrow, 0x1B - Arrow, 0x1C - Under water attack? (Verified to be uint8)
/*0084*/ uint8 sourceAnimation;		// Comment: Yeahlight: Attack animation of the inflictor (Verified to be uint8)
/*0085*/ char texture[16];			// Comment: Yeahlight: Object's texture filename (Must be set to "GENC00" or the like when using spell bolt projectiles)
/*0101*/ char spacer[15];			// Comment: Yeahlight: ASM makes no reference to any bytes after the 85th, so these must be padding
};


// Harakiri struct sent by client when using /discp
struct UseDiscipline_Struct {
/*0001*/ uint8 discipline;			   // Comment: The discipline executed
/*0001*/ uint8 unknown[3];			   // Comment: Seems to be always 0 
};

// Harakiri struct to sent to the client after completing a quest with money
// to get the fanfare sound, alternativly, just sent with all 0 to get sound
struct QuestCompletedMoney_Struct{
	/*0000*/	uint32	npcID; 	 // Comment: Harakiri The ID of the NPC which gave money for the finished quest
	/*0004*/	uint8	unknown[16];
	/*0020*/	uint32	copper;	// Comment: Harakiri amount of copper
	/*0024*/	uint32	silver; // Comment: Harakiri amount of silver
	/*0028*/	uint32	gold; 	// Comment: Harakiri amount of gold
	/*0032*/	uint32	platinum; // Comment: Harakiri amount of platinum			
	};

struct GlobalID_Struct
{
int16 entity_id;
};

struct ApproveWorld_Struct
{
	uint8 response;
};

struct ExpansionInfo_Struct
{
	uint32 flag;
};


struct OldSpellBuff_Struct
{
	/*000*/uint8  visable;		// Comment: Cofruben: 0 = Buff not visible, 1 = Visible and permanent buff(Confirmed by Tazadar) , 2 = Visible and timer on(Confirmed by Tazadar) 
	/*001*/uint8  level;			// Comment: Level of person who casted buff
	/*002*/uint8  bard_modifier;	// Comment: Harakiri: this seems to be the bard modifier, it is normally 0x0A because we set in in the CastOn_Struct when its not a bard, else its the instrument mod
	/*003*/uint8  b_unknown3;	// Comment: ***Placeholder
	/*004*/uint16 spellid;		// Comment: Unknown -> needs confirming -> ID of spell?
	/*006*/uint32 duration;		// Comment: Unknown -> needs confirming -> Duration in ticks
};

// Length: 10
struct OldItemProperties_Struct {

uint8	unknown01[2];
int8	charges;				// Comment: Harakiri signed int because unlimited charges are -1
uint8	unknown02[7];
};

/*
** Player Profile
** Length: 8104 Bytes
*/

struct OldBindStruct {
	/*004*/ float x;
	/*008*/ float y;
	/*012*/ float z;
	/*020*/
};

struct PlayerProfile_Struct
{
#define pp_inventory_size 30
#define pp_containerinv_size 80
#define pp_cursorbaginventory_size 10
#define pp_bank_inv_size 8
#define pp_bank_cont_inv_size 80
/* ***************** */

/*0000*/	uint8	checksum[4];		// Checksum
/*0004*/	uint8	unknown0004[2];		// ***Placeholder
/*0006*/	char	name[64];			// Player First Name
/*0070*/	char	Surname[70];		// Player Last Name
/*0140*/	uint8	gender;				// Player Gender
/*0141*/	uint8	unknown0141;		// ***Placeholder
/*0142*/	uint16	race;				// Player Race (Lyenu: Changed to an int16, since races can be over 255)
/*0144*/	uint16	class_;				// Player Class
/*0146*/	uint8	unknown0146;		// ***Placeholder
/*0147*/	uint8	unknown0147;		// ***Placeholder
/*0148*/	uint8	level;				// Player Level
/*0149*/	uint8	unknown0149;		// ***Placeholder
/*0150*/	uint8	unknown0150[2];		// ***Placeholder
/*0152*/	uint32	exp;				// Current Experience
/*0156*/	uint16	trainingpoints;				// Players Points
/*0158*/	uint16	mana;				// Player Mana
/*0160*/	uint16	cur_hp;				// Player Health
/*0162*/	uint16	face;				// Players Face
/*0164*/	uint16	STR;				// Player Strength
/*0166*/	uint16	STA;				// Player Stamina
/*0168*/	uint16	CHA;				// Player Charisma
/*0170*/	uint16	DEX;				// Player Dexterity
/*0172*/	uint16	INT;				// Player Intelligence
/*0174*/	uint16	AGI;				// Player Agility
/*0176*/	uint16	WIS;				// Player Wisdom
/*0178*/	uint8	face_;               //
/*0179*/    int8    EquipType[9];       // i think its the visible parts of the body armor
/*0188*/    int32   EquipColor[9];      //
/*0224*/	uint16	inventory[30];		// Player Inventory Item Numbers
/*0284*/	uint8	languages[26];		// Player Languages
/*0310*/	uint8	unknown0310[6];		// ***Placeholder
/*0316*/	struct	OldItemProperties_Struct	invItemProprieties[30];
										// These correlate with inventory[30]
/*0616*/	struct	OldSpellBuff_Struct	buffs[15];
										// Player Buffs Currently On
/*0766*/	uint16	containerinv[pp_containerinv_size];	// Player Items In "Bags"
										// If a bag is in slot 0, this is where the bag's items are
/*0926*/	uint16   cursorbaginventory[10];
/*0946*/	struct	OldItemProperties_Struct	bagItemProprieties[pp_containerinv_size];
										// Just like InvItemProperties
/*1746*/    struct  OldItemProperties_Struct	cursorItemProprieties[10];
                                          //just like invitemprops[]
/*1846*/	int16	spell_book[256];	// Player spells scribed in their book
/*2358*/	uint8	unknown2374[512];	// ***Placeholder
/*2870*/	int16	mem_spells[8];	// Player spells memorized
/*2886*/	uint8	unknown2886[14];			// ***Placeholder [16]
/*2900*/	uint16	unknown2900;
/*2902*/	float	y;					// Player X
/*2906*/	float	x;					// Player Y
/*2910*/	float	z;					// Player Z
/*2914*/	float	heading;			// Player Heading
/*2918*/	uint8	unknown2920[6];		// ***Placeholder
/*2924*/	uint32	platinum;			// Player Platinum (Character)
/*2928*/	uint32	gold;				// Player Gold (Character)
/*2932*/	uint32	silver;				// Player Silver (Character)
/*2936*/	uint32	copper;				// Player Copper (Character)
/*2940*/	uint32	platinum_bank;		// Player Platinum (Bank)
/*2944*/	uint32	gold_bank;			// Player Gold (Bank)
/*2948*/	uint32	silver_bank;		// Player Silver (Bank)
/*2952*/	uint32	copper_bank;		// Player Copper (Bank)
/*2956*/	uint32	platinum_cursor;
/*2960*/	uint32	gold_cursor;
/*2964*/	uint32	silver_cursor;
/*2968*/	uint32	copper_cursor;
/*2972*/	uint8	unknown2972[16];	// ***Placeholder
/*2988*/	uint16	skills[75];			// Player Skills
/*3138*/	uint32	hungerlevel;		// Probably wrong, previously was in the spot where skills should be.
/*3142*/	uint32	thirstlevel;		// Probably wrong, previously was in the spot where skills should be.
/*3146*/	uint8	unknown3144[202];
/*3348*/	uint8	autosplit;
/*3349*/	uint8	unknown3449[95];
/*3444*/	uint32	current_zone;		// 
/*3448*/	uint8	unknown3448[336];	// ***Placeholder
/*3784*/	uint32	bind_point_zone;	// Lyenu: Bind zone is saved as a int32 now
/*3788*/	uint32	start_point_zone[4];
										// Lyenu: Start Point Zones are saved as int32s now
/*3804*/	OldBindStruct	bind_location[5];
										// Player Bind Location (5 different X,Y,Z - Multiple bind points?)
/*3864*/	uint8	unknown3656[20];	// ***Placeholder
/*3884*/	OldItemProperties_Struct	bankinvitemproperties[8];
/*3964*/	OldItemProperties_Struct	bankbagitemproperties[80];
/*4764*/	uint8	unknown4556[4];
/*4768*/	uint16	bank_inv[8];		// Player Bank Inventory Item Numbers
/*4784*/	uint16	bank_cont_inv[80];	// Player Bank Inventory Item Numbers (Bags)
/*4944*/	uint16	deity;		// ***Placeholder
/*4946*/	uint16	guildid;			// Player Guild ID Number
/*4948*/	uint32   BirthdayTime;
/*4952*/	uint32   Unknown_4952;
/*4956*/	uint32   TimePlayedMin;
/*4960*/	uint8    Unknown_4960[2];
/*4962*/	uint8    fatigue;
/*4963*/	uint8	pvp;				// Player PVP Flag
/*4964*/	uint8	unknown4756;		// ***Placeholder
/*4965*/	uint8	anon;				// Player Anon. Flag
/*4966*/	uint8	gm;					// Player GM Flag
/*4967*/	int8	guildrank;			// Player Guild Rank (0=member, 1=officer, 2=leader)
/*4968*/	uint8	unknown4760[44];
/*5012*/	char	groupMembers[6][64];	// Group Members
/*5396*/	uint8	unknown5124[29];	// ***Placeholder 
/*5425*/	uint8	AAPercent;			// Player AA Percent
/*5426*/	uint8	haircolor;			// Player Hair Color
/*5427*/	uint8	beardcolor;			// Player Beard Color
/*5428*/	uint8	eyecolor1;			// Player Left Eye Color
/*5429*/	uint8	eyecolor2;			// Player Right Eye Color
/*5430*/	uint8	hairstyle;			// Player Hair Style
/*5431*/	uint8	beard_t;			// T7g: Beard Type, formerly title - I have no clue why, Title moved a few lines below this one
/*5432*/	uint8	luclinface;			// Player Face Type (Is that right?)
/*5433*/	uint8	unknown5225[195];	// ***Placeholder
/*5628*/	uint32	expAA;				// AA Exp
/*5632*/	uint8	title;				// AA Title
/*5633*/	uint8	perAA;				// AA Percentage
/*5634*/	uint32	aapoints;			// AA Points
/*5638*/	uint8	unknown5426[2822];	// Unknown
//			uint32	raid_id;			// Raid ID?
//			uint32	unknown5450;		// Unknown (Added 09 Oct 2002)
};

struct Weather_Struct {
	uint32	val1;	//generall 0x000000FF
	uint16	type;	//0x31=rain, 0x02=snow(i think), 0 = normal
	uint16	mode;
};


	};	//end namespace structs
};	//end namespace MAC

#endif /*MAC_STRUCTS_H_*/










