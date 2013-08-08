#include "../debug.h"
#include "Mac.h"
#include "../opcodemgr.h"
#include "../logsys.h"
#include "../EQStreamIdent.h"
#include "../crc32.h"

#include "../eq_packet_structs.h"
#include "../MiscFunctions.h"
#include "../packet_functions.h"
#include "../StringUtil.h"
#include "../Item.h"
#include "Mac_structs.h"
#include "../rulesys.h"

namespace Mac {

static const char *name = "Mac";
static OpcodeManager *opcodes = NULL;
static Strategy struct_strategy;

void Register(EQStreamIdentifier &into) {
	//create our opcode manager if we havent already
	if(opcodes == NULL) {
		std::string opfile = "patch_";
		opfile += name;
		opfile += ".conf";
		//load up the opcode manager.
		//TODO: figure out how to support shared memory with multiple patches...
		opcodes = new RegularOpcodeManager();
		if(!opcodes->LoadOpcodes(opfile.c_str())) {
			_log(NET__OPCODES, "Error loading opcodes file %s. Not registering patch %s.", opfile.c_str(), name);
			return;
		}
	}

	//ok, now we have what we need to register.

	EQStream::Signature signature;
	std::string pname;

	pname = std::string(name) + "_world";
	//register our world signature.
	signature.first_length = sizeof(structs::LoginInfo_Struct);
	signature.first_eq_opcode = opcodes->EmuToEQ(OP_SendLoginInfo);
	into.RegisterOldPatch(signature, pname.c_str(), &opcodes, &struct_strategy);

	pname = std::string(name) + "_zone";
	//register our zone signature.
	signature.first_length = sizeof(structs::SetDataRate_Struct);
	signature.first_eq_opcode = opcodes->EmuToEQ(OP_DataRate);
	into.RegisterOldPatch(signature, pname.c_str(), &opcodes, &struct_strategy);
		
	_log(NET__IDENTIFY, "Registered patch %s", name);
}

void Reload() {

	//we have a big problem to solve here when we switch back to shared memory
	//opcode managers because we need to change the manager pointer, which means
	//we need to go to every stream and replace it's manager.

	if(opcodes != NULL) {
		//TODO: get this file name from the config file
		std::string opfile = "patch_";
		opfile += name;
		opfile += ".conf";
		if(!opcodes->ReloadOpcodes(opfile.c_str())) {
			_log(NET__OPCODES, "Error reloading opcodes file %s for patch %s.", opfile.c_str(), name);
			return;
		}
		_log(NET__OPCODES, "Reloaded opcodes for patch %s", name);
	}
}



Strategy::Strategy()
: StructStrategy()
{
	//all opcodes default to passthrough.
	#include "SSRegister.h"
	#include "Mac_ops.h"
}

std::string Strategy::Describe() const {
	std::string r;
	r += "Patch ";
	r += name;
	return(r);
}


#include "SSDefine.h"



const EQClientVersion Strategy::ClientVersion() const
{
	return EQClientMac;
}


DECODE(OP_SendLoginInfo) {
	DECODE_LENGTH_EXACT(structs::LoginInfo_Struct);
	SETUP_DIRECT_DECODE(LoginInfo_Struct, structs::LoginInfo_Struct);
	memcpy(emu->login_info, eq->AccountName, 64);
	FINISH_DIRECT_DECODE();
}

DECODE(OP_EnterWorld) {
	SETUP_DIRECT_DECODE(EnterWorld_Struct, structs::EnterWorld_Struct);
	strn0cpy(emu->name, eq->charname, 64);
	emu->return_home = 0;
	emu->tutorial = 0;
	FINISH_DIRECT_DECODE();
}

ENCODE(OP_ZoneServerInfo) {
	SETUP_DIRECT_ENCODE(ZoneServerInfo_Struct, structs::ZoneServerInfo_Struct);
	strcpy(eq->ip, emu->ip);
	eq->port = ntohs(emu->port);

	FINISH_ENCODE();
}

ENCODE(OP_ZoneEntry) {
	SETUP_DIRECT_ENCODE(Spawn_Struct, structs::ServerZoneEntry_Struct);
		eq->anon = emu->anon;
		//eq->face = emu->face;
		strcpy(eq->name, emu->name);
		eq->zone = emu->zoneID;
		eq->deity = emu->deity;
		eq->haircolor = emu->haircolor;
		eq->x = emu->x;
		eq->y = emu->y;
		eq->z = emu->z;
		eq->heading = emu->heading;
		eq->eyecolor1 = emu->eyecolor1;
//		eq->showhelm = emu->showhelm;
		eq->hairstyle = emu->hairstyle;
		//eq->beard = emu->beard;
		eq->level = emu->level;
		eq->beardcolor = emu->beardcolor;
		int k;
		for(k = 0; k < 9; k++) {
			eq->equipment[k] = emu->equipment[k];
			eq->colors[k].color = emu->colors[k].color;
		}
		eq->npc_armor_graphic = 0xFF;
		eq->runspeed = emu->runspeed;
		//eq->afk = emu->afk;
		eq->guildeqid = emu->guildID;
		//strcpy(eq->title, emu->title);
		//eq->helm = emu->helm;
		eq->race = emu->race;
		strcpy(eq->Surname, emu->lastName);
		eq->walkspeed = emu->walkspeed;
	//	eq->is_pet = emu->is_pet;
	//eq->light = emu->light;
		eq->class_ = emu->class_;
		eq->eyecolor2 = emu->eyecolor2;
		eq->gender = emu->gender;
	//	eq->bodytype = emu->bodytype;
	//	eq->equip_chest2 = emu->equip_chest2;
	//	eq->spawnId = emu->spawnId;
	//	eq->lfg = emu->lfg;
	//	eq->flymode = emu->flymode;
	CRC32::SetEQChecksum(__packet->pBuffer, sizeof(structs::ServerZoneEntry_Struct));
	_log(NET__STRUCTS, "AddPlayer Packet is %i bytes uncompressed", sizeof(structs::ServerZoneEntry_Struct));
	
	FINISH_ENCODE();	
}


ENCODE(OP_PlayerProfile) {
	SETUP_DIRECT_ENCODE(PlayerProfile_Struct, structs::PlayerProfile_Struct);

	int r = 0;
	//	OUT(checksum);
	OUT(gender);
	OUT(race);
	OUT(class_);
	OUT(level);
	eq->bind_point_zone = emu->binds[0].zoneId;
	eq->bind_location[0].x = emu->binds[0].x;
	eq->bind_location[0].y = emu->binds[0].y;
	eq->bind_location[0].z = emu->binds[0].z;
	//eq->bind_heading[0] = emu->binds[0].heading;


	OUT(deity);
	//OUT(intoxication);
	//OUT_array(spellSlotRefresh, structs::MAX_PP_MEMSPELL);
	//OUT(abilitySlotRefresh);
//	OUT(unknown0166[4]);
	OUT(haircolor);
	OUT(beardcolor);
	OUT(eyecolor1);
	OUT(eyecolor2);
	OUT(hairstyle);
	eq->beard_t = emu->beard;
	eq->trainingpoints = emu->points;
	OUT(mana);
	OUT(cur_hp);
	OUT(STR);
	OUT(STA);
	OUT(CHA);
	OUT(DEX);
	OUT(INT);
	OUT(AGI);
	OUT(WIS);
	OUT(face);
	OUT_array(spell_book, 256);
	OUT_array(mem_spells, 8);
	OUT(platinum);
	OUT(gold);
	OUT(silver);
	OUT(copper);
	OUT(platinum_cursor);
	OUT(gold_cursor);
	OUT(silver_cursor);
	OUT(copper_cursor);
	OUT_array(skills, 75);
	//OUT(toxicity);
	//OUT(thirstlevel);
	//	OUT(hungerlevel);
	for(r = 0; r < 15; r++) {
		eq->buffs[r].visable = (emu->buffs[r].spellid != 0xFFFF || emu->buffs[r].spellid != 0) ? 2 : 0;
		//OUT(buffs[r].slotid);
		OUT(buffs[r].level);
		OUT(buffs[r].bard_modifier);
		//OUT(buffs[r].effect);
		OUT(buffs[r].spellid);
		OUT(buffs[r].duration);
		//OUT(buffs[r].counters);
		//OUT(buffs[r].player_id);
	}
//	OUT_array(recastTimers, structs::MAX_RECAST_TYPES);
//	OUT(endurance);
//	OUT(aapoints_spent);
	OUT(aapoints);
//	OUT(available_slots);
	OUT_str(name);
	strcpy(eq->Surname, emu->last_name);
	eq->guildid = emu->guild_id;
	//OUT(birthday);
	//OUT(lastlogin);
	//OUT(timePlayedMin);
	OUT(pvp);
	OUT(anon);
	OUT(gm);
	OUT(guildrank);
	OUT(exp);
	OUT_array(languages, 26);
	OUT(x);
	OUT(y);
	OUT(z);
	OUT(heading);
	OUT(platinum_bank);
	OUT(gold_bank);
	OUT(silver_bank);
	OUT(copper_bank);
//	OUT(platinum_shared);
//OUT(expansions);
	OUT(autosplit);
	eq->current_zone = emu->zone_id;
	//OUT(zoneInstance);
	for(r = 0; r < 6; r++) {
		OUT_str(groupMembers[r]);
	}
//	OUT_str(groupLeader);	//this is prolly right after groupMembers, but I dont feel like checking.
//	OUT(leadAAActive);
//	OUT(showhelm);
	_log(NET__STRUCTS, "Player Profile Packet is %i bytes uncompressed", sizeof(structs::PlayerProfile_Struct));
	CRC32::SetEQChecksum(__packet->pBuffer, sizeof(structs::PlayerProfile_Struct)-4);
	EQApplicationPacket* outapp = new EQApplicationPacket();
	outapp->SetOpcode(OP_PlayerProfile);
	outapp->pBuffer = new uchar[10000];
	outapp->size = DeflatePacket((unsigned char*)__packet->pBuffer, sizeof(structs::PlayerProfile_Struct), outapp->pBuffer, 10000);
	EncryptProfilePacket(outapp->pBuffer, outapp->size);
	_log(NET__STRUCTS, "Player Profile Packet is %i bytes compressed", outapp->size);
	dest->FastQueuePacket(&outapp);
	delete[] __emu_buffer;
	delete __packet;
}


ENCODE(OP_ApproveWorld) {
	SETUP_DIRECT_ENCODE(ApproveWorld_Struct, structs::ApproveWorld_Struct);
	eq->response = 0;
	FINISH_ENCODE();	
}

ENCODE(OP_EnterWorld) {
	SETUP_DIRECT_ENCODE(ApproveWorld_Struct, structs::ApproveWorld_Struct);
	eq->response = 0;
	FINISH_ENCODE();	
}


ENCODE(OP_ExpansionInfo) {
	SETUP_DIRECT_ENCODE(ExpansionInfo_Struct, structs::ExpansionInfo_Struct);
	eq->flag = 15;
	FINISH_ENCODE();	
}


ENCODE(OP_SendCharInfo) {
	int r;
	ENCODE_LENGTH_EXACT(CharacterSelect_Struct);
	SETUP_DIRECT_ENCODE(CharacterSelect_Struct, structs::CharacterSelect_Struct);
	for(r = 0; r < 10; r++) {
		OUT(zone[r]);
		OUT(eyecolor1[r]);
		OUT(eyecolor2[r]);
		OUT(hairstyle[r]);
		OUT(primary[r]);
		if(emu->race[r] > 300)
			eq->race[r] = 1;
		else
			eq->race[r] = emu->race[r];
		OUT(class_[r]);
		OUT_str(name[r]);
		OUT(gender[r]);
		OUT(level[r]);
		OUT(secondary[r]);
		OUT(face[r]);
		OUT(beard[r]);
		int k;
		for(k = 0; k < 9; k++) {
			OUT(equip[r][k]);
			OUT(cs_colors[r][k].color);
		}
		OUT(haircolor[r]);
		OUT(deity[r]);
		OUT(beardcolor[r]);
	}
	FINISH_ENCODE();	
}

ENCODE(OP_GuildsList) {
	SETUP_DIRECT_ENCODE(GuildsList_Struct, structs::GuildsList_Struct);
	OUT_array(head, 4);

	int totalcount = (__packet->size - 64) / sizeof(GuildsListEntry_Struct);
	int r = 0;
	for(r = 0; r < totalcount; r++)
	{
		if(emu->Guilds[r].name[0] != '\0')
		{
			strn0cpy(eq->Guilds[r].name, emu->Guilds[r].name, 32);
			eq->Guilds[r].exists = 1;
			eq->Guilds[r].guildID = r;
		}
	}

	FINISH_ENCODE();	
}



ENCODE(OP_Weather) {
	SETUP_DIRECT_ENCODE(Weather_Struct, structs::Weather_Struct);
	OUT(val1);
	OUT(type);
	OUT(mode);
	FINISH_ENCODE();	
}

ENCODE(OP_NewZone) {
	SETUP_DIRECT_ENCODE(NewZone_Struct, structs::NewZone_Struct);
	OUT_str(char_name);
	OUT_str(zone_short_name);
	OUT_str(zone_long_name);
	OUT(ztype);
	OUT_array(fog_red, 4);
	OUT_array(fog_green, 4);
	OUT_array(fog_blue, 4);
	OUT_array(fog_minclip, 4);
	OUT_array(fog_maxclip, 4);
	OUT(gravity);
	OUT(time_type);
	OUT(sky);
	OUT(zone_exp_multiplier);
	OUT(safe_y);
	OUT(safe_x);
	OUT(safe_z);
	OUT(max_z);
	OUT(underworld);
	OUT(minclip);
	OUT(maxclip);
	FINISH_ENCODE();	
}

ENCODE(OP_SpawnDoor) {
	SETUP_VAR_ENCODE(Door_Struct);
	int door_count = __packet->size/sizeof(Door_Struct);
	int total_length = door_count * sizeof(structs::Door_Struct);
	ALLOC_VAR_ENCODE(structs::Door_Struct, total_length);
	int r;
	for(r = 0; r < door_count; r++) {
		strcpy(eq[r].name, emu[r].name);
		eq[r].xPos = emu[r].xPos;
		eq[r].yPos = emu[r].yPos;
		eq[r].zPos = emu[r].zPos;
		eq[r].heading = emu[r].heading;
		eq[r].incline = emu[r].incline;
		eq[r].size = emu[r].size;
		eq[r].doorid = emu[r].doorId;
		eq[r].opentype = emu[r].opentype;
		eq[r].doorIsOpen = emu[r].state_at_spawn;
		eq[r].inverted = emu[r].invert_state;
		eq[r].parameter = emu[r].door_param;
	}

	EQApplicationPacket* outapp = new EQApplicationPacket();
	outapp->SetOpcode(OP_SpawnDoor);
	outapp->pBuffer = new uchar[total_length];
	outapp->size = DeflatePacket((unsigned char*)__packet->pBuffer, door_count * sizeof(structs::Door_Struct), outapp->pBuffer, __packet->size);
	dest->FastQueuePacket(&outapp);
	delete[] __emu_buffer;
	delete __packet;
}

ENCODE(OP_ZoneSpawns){

	//consume the packet
	EQApplicationPacket *in = *p;
	*p = nullptr;

	//store away the emu struct
	unsigned char *__emu_buffer = in->pBuffer;
	Spawn_Struct *emu = (Spawn_Struct *) __emu_buffer;

	//determine and verify length
	int entrycount = in->size / sizeof(Spawn_Struct);
	if(entrycount == 0 || (in->size % sizeof(Spawn_Struct)) != 0) {
		_log(NET__STRUCTS, "Wrong size on outbound %s: Got %d, expected multiple of %d", opcodes->EmuToName(in->GetOpcode()), in->size, sizeof(Spawn_Struct));
		delete in;
		return;
	}

	//make the EQ struct.
	in->size = sizeof(structs::Spawn_Struct)*entrycount;
	in->pBuffer = new unsigned char[in->size];
	structs::Spawn_Struct *eq = (structs::Spawn_Struct *) in->pBuffer;

	//zero out the packet. We could avoid this memset by setting all fields (including unknowns)
	//in the loop.
	memset(in->pBuffer, 0, in->size);

	//do the transform...
	int r;
	int k;
	for(r = 0; r < entrycount; r++, eq++, emu++) {
//		eq->unknown0000 = emu->unknown0000;
		eq->GM = emu->gm;
//		eq->unknown0003 = emu->unknown0003;
		eq->title = emu->aaitle;
//		eq->unknown0004 = emu->unknown0004;
		eq->anon = emu->anon;
		//eq->face = emu->face;
		strcpy(eq->name, emu->name);
		eq->deity = emu->deity;
//		eq->unknown0073 = emu->unknown0073;
		eq->size = emu->size;
//		eq->unknown0079 = emu->unknown0079;
		eq->NPC = emu->NPC;
		eq->invis = emu->invis;
		eq->haircolor = emu->haircolor;
		eq->cur_hp = emu->curHp;
		//eq->max_hp = emu->max_hp;
		//eq->findable = emu->findable;
//		eq->unknown0089[5] = emu->unknown0089[5];
		eq->deltaHeading = emu->deltaHeading;
		eq->x_pos = emu->x;
//		eq->padding0054 = emu->padding0054;
		eq->y_pos = emu->y;
		eq->animation = emu->animation;
//		eq->padding0058 = emu->padding0058;
		eq->z_pos = emu->z;
		eq->deltaY = emu->deltaY;
		eq->deltaX = emu->deltaX;
		eq->heading = emu->heading;
//		eq->padding0066 = emu->padding0066;
		eq->deltaZ = emu->deltaZ;
//		eq->padding0070 = emu->padding0070;
		eq->eyecolor1 = emu->eyecolor1;
//		eq->unknown0115[24] = emu->unknown0115[24];
		//eq->showhelm = emu->showhelm;
//		eq->unknown0140[4] = emu->unknown0140[4];
		//eq->is_npc = emu->is_npc;
		eq->hairstyle = emu->hairstyle;

		//if(emu->gender == 1){
		//	eq->hairstyle = eq->hairstyle == 0xFF ? 0 : eq->hairstyle;
		//}

		eq->beardcolor = emu->beardcolor;
//		eq->unknown0147[4] = emu->unknown0147[4];
		eq->level = emu->level;
//		eq->unknown0259[4] = emu->unknown0259[4];
	//	eq->beard = emu->beard;
		//eq->petOwnerId = emu->petOwnerId;
		eq->guildrank = emu->guildrank;
//		eq->unknown0194[3] = emu->unknown0194[3];
		for(k = 0; k < 9; k++) {
			eq->equipment[k] = emu->equipment[k];
			eq->equipcolors[k].color = emu->colors[k].color;
		}
		eq->runspeed = emu->runspeed;
		eq->AFK = emu->afk;
		eq->GuildID = emu->guildID;
		eq->title = emu->face;
//		eq->unknown0274 = emu->unknown0274;
		//eq->helm = emu->helm;
		if(emu->race > 473)
			eq->race = 1;
		else
			eq->race = emu->race;
//		eq->unknown0288 = emu->unknown0288;
		strcpy(eq->Surname, emu->lastName);
		eq->walkspeed = emu->walkspeed;
//		eq->unknown0328 = emu->unknown0328;
		//eq->is_pet = emu->is_pet;
		eq->light = emu->light;
		eq->class_ = emu->class_;
		eq->eyecolor2 = emu->eyecolor2;
//		eq->unknown0333 = emu->unknown0333;
	//	eq->flymode = emu->flymode;
		eq->gender = emu->gender;
	//	eq->bodytype = emu->bodytype;
//		eq->unknown0336[3] = emu->unknown0336[3];
	//	eq->equip_chest2 = emu->equip_chest2;
		eq->spawn_id = emu->spawnId;
//		eq->unknown0344[4] = emu->unknown0344[4];
		//eq->lfg = emu->lfg;

		/*
		if (emu->face == 99)	      {eq->face = 0;}
		if (emu->eyecolor1 == 99)  {eq->eyecolor1 = 0;}
		if (emu->eyecolor2 == 99)  {eq->eyecolor2 = 0;}
		if (emu->hairstyle == 99)  {eq->hairstyle = 0;}
		if (emu->haircolor == 99)  {eq->haircolor = 0;}
		if (emu->beard == 99)      {eq->beard = 0;}
		if (emu->beardcolor == 99) {eq->beardcolor = 0;}
		*/

	}
	EQApplicationPacket* outapp = new EQApplicationPacket();
	outapp->SetOpcode(OP_ZoneSpawns);
	outapp->pBuffer = new uchar[sizeof(structs::Spawn_Struct)*entrycount];
	outapp->size = DeflatePacket((unsigned char*)in->pBuffer, entrycount * sizeof(structs::NewSpawn_Struct), outapp->pBuffer, sizeof(structs::Spawn_Struct)*entrycount);
	EncryptZoneSpawnPacket(outapp->pBuffer, outapp->size);

	//kill off the emu structure and send the eq packet.
	delete[] __emu_buffer;
	delete in;
	dest->FastQueuePacket(&outapp, ack_req);

}

ENCODE(OP_NewSpawn) {
//consume the packet
	EQApplicationPacket *in = *p;
	*p = nullptr;

	//store away the emu struct
	unsigned char *__emu_buffer = in->pBuffer;
	Spawn_Struct *emu = (Spawn_Struct *) __emu_buffer;

	//determine and verify length
	int entrycount = in->size / sizeof(Spawn_Struct);
	if(entrycount == 0 || (in->size % sizeof(Spawn_Struct)) != 0) {
		_log(NET__STRUCTS, "Wrong size on outbound %s: Got %d, expected multiple of %d", opcodes->EmuToName(in->GetOpcode()), in->size, sizeof(Spawn_Struct));
		delete in;
		return;
	}

	//make the EQ struct.
	in->size = sizeof(structs::Spawn_Struct)*entrycount;
	in->pBuffer = new unsigned char[in->size];
	structs::Spawn_Struct *eq = (structs::Spawn_Struct *) in->pBuffer;

	//zero out the packet. We could avoid this memset by setting all fields (including unknowns)
	//in the loop.
	memset(in->pBuffer, 0, in->size);

	//do the transform...
	int r;
	int k;
	for(r = 0; r < entrycount; r++, eq++, emu++) {
//		eq->unknown0000 = emu->unknown0000;
		eq->GM = emu->gm;
//		eq->unknown0003 = emu->unknown0003;
		eq->title = emu->aaitle;
//		eq->unknown0004 = emu->unknown0004;
		eq->anon = emu->anon;
		//eq->face = emu->face;
		strcpy(eq->name, emu->name);
		eq->deity = emu->deity;
//		eq->unknown0073 = emu->unknown0073;
		eq->size = emu->size;
//		eq->unknown0079 = emu->unknown0079;
		eq->NPC = emu->NPC;
		eq->invis = emu->invis;
		eq->haircolor = emu->haircolor;
		eq->cur_hp = emu->curHp;
		//eq->max_hp = emu->max_hp;
		//eq->findable = emu->findable;
//		eq->unknown0089[5] = emu->unknown0089[5];
		eq->deltaHeading = emu->deltaHeading;
		eq->x_pos = emu->x;
//		eq->padding0054 = emu->padding0054;
		eq->y_pos = emu->y;
		eq->animation = emu->animation;
//		eq->padding0058 = emu->padding0058;
		eq->z_pos = emu->z;
		eq->deltaY = emu->deltaY;
		eq->deltaX = emu->deltaX;
		eq->heading = emu->heading;
//		eq->padding0066 = emu->padding0066;
		eq->deltaZ = emu->deltaZ;
//		eq->padding0070 = emu->padding0070;
		eq->eyecolor1 = emu->eyecolor1;
//		eq->unknown0115[24] = emu->unknown0115[24];
		//eq->showhelm = emu->showhelm;
//		eq->unknown0140[4] = emu->unknown0140[4];
		//eq->is_npc = emu->is_npc;
		eq->hairstyle = emu->hairstyle;

		//if(emu->gender == 1){
		//	eq->hairstyle = eq->hairstyle == 0xFF ? 0 : eq->hairstyle;
		//}

		eq->beardcolor = emu->beardcolor;
//		eq->unknown0147[4] = emu->unknown0147[4];
		eq->level = emu->level;
//		eq->unknown0259[4] = emu->unknown0259[4];
	//	eq->beard = emu->beard;
		//eq->petOwnerId = emu->petOwnerId;
		eq->guildrank = emu->guildrank;
//		eq->unknown0194[3] = emu->unknown0194[3];
		for(k = 0; k < 9; k++) {
			eq->equipment[k] = emu->equipment[k];
			eq->equipcolors[k].color = emu->colors[k].color;
		}
		eq->runspeed = emu->runspeed;
		eq->AFK = emu->afk;
		eq->GuildID = emu->guildID;
		eq->title = emu->face;
//		eq->unknown0274 = emu->unknown0274;
		//eq->helm = emu->helm;
		if(emu->race > 473)
			eq->race = 1;
		else
			eq->race = emu->race;
//		eq->unknown0288 = emu->unknown0288;
		strcpy(eq->Surname, emu->lastName);
		eq->walkspeed = emu->walkspeed;
//		eq->unknown0328 = emu->unknown0328;
		//eq->is_pet = emu->is_pet;
		eq->light = emu->light;
		eq->class_ = emu->class_;
		eq->eyecolor2 = emu->eyecolor2;
//		eq->unknown0333 = emu->unknown0333;
	//	eq->flymode = emu->flymode;
		eq->gender = emu->gender;
	//	eq->bodytype = emu->bodytype;
//		eq->unknown0336[3] = emu->unknown0336[3];
	//	eq->equip_chest2 = emu->equip_chest2;
		eq->spawn_id = emu->spawnId;
//		eq->unknown0344[4] = emu->unknown0344[4];
		//eq->lfg = emu->lfg;

		/*
		if (emu->face == 99)	      {eq->face = 0;}
		if (emu->eyecolor1 == 99)  {eq->eyecolor1 = 0;}
		if (emu->eyecolor2 == 99)  {eq->eyecolor2 = 0;}
		if (emu->hairstyle == 99)  {eq->hairstyle = 0;}
		if (emu->haircolor == 99)  {eq->haircolor = 0;}
		if (emu->beard == 99)      {eq->beard = 0;}
		if (emu->beardcolor == 99) {eq->beardcolor = 0;}
		*/

	}
	EncryptZoneSpawnPacket(in->pBuffer, in->size);

	//kill off the emu structure and send the eq packet.
	delete[] __emu_buffer;
	dest->FastQueuePacket(&in, ack_req);
}








} //end namespace Mac






