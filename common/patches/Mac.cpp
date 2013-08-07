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
		OUT(buffs[r].slotid);
		OUT(buffs[r].level);
		OUT(buffs[r].bard_modifier);
		OUT(buffs[r].effect);
		OUT(buffs[r].spellid);
		OUT(buffs[r].duration);
		OUT(buffs[r].counters);
		OUT(buffs[r].player_id);
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
	CRC32::SetEQChecksum(__packet->pBuffer, sizeof(structs::PlayerProfile_Struct)-4);
	EQApplicationPacket* outapp = new EQApplicationPacket();
	outapp->SetOpcode(OP_PlayerProfile);
	outapp->pBuffer = new uchar[10000];
	outapp->size = DeflatePacket((unsigned char*)__emu_buffer, sizeof(PlayerProfile_Struct), outapp->pBuffer, 10000);
	EncryptProfilePacket(outapp->pBuffer, outapp->size);
	dest->FastQueuePacket(&outapp);
	delete[] __emu_buffer;
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












} //end namespace Mac






