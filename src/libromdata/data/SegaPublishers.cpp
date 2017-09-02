/***************************************************************************
 * ROM Properties Page shell extension. (libromdata)                       *
 * SegaPublishers.cpp: Sega third-party publishers list.                   *
 *                                                                         *
 * Copyright (c) 2016-2017 by David Korth.                                 *
 *                                                                         *
 * This program is free software; you can redistribute it and/or modify it *
 * under the terms of the GNU General Public License as published by the   *
 * Free Software Foundation; either version 2 of the License, or (at your  *
 * option) any later version.                                              *
 *                                                                         *
 * This program is distributed in the hope that it will be useful, but     *
 * WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 * GNU General Public License for more details.                            *
 *                                                                         *
 * You should have received a copy of the GNU General Public License along *
 * with this program; if not, write to the Free Software Foundation, Inc., *
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.           *
 ***************************************************************************/

#include "SegaPublishers.hpp"

// C includes.
#include <stdlib.h>

namespace LibRomData {

class SegaPublishersPrivate {
	private:
		// Static class.
		SegaPublishersPrivate();
		~SegaPublishersPrivate();
		RP_DISABLE_COPY(SegaPublishersPrivate)

	public:
		/**
		 * Sega third-party publisher list.
		 * Reference: http://segaretro.org/Third-party_T-series_codes
		 */
		struct TCodeEntry {
			unsigned int t_code;
			const rp_char *publisher;
		};
		static const TCodeEntry tcodeList[];

		/**
		 * Comparison function for bsearch().
		 * @param a
		 * @param b
		 * @return
		 */
		static int RP_C_API compar(const void *a, const void *b);

};

/**
 * Sega third-party publisher list.
 * Reference: http://segaretro.org/Third-party_T-series_codes
 */
const SegaPublishersPrivate::TCodeEntry SegaPublishersPrivate::tcodeList[] = {
	{0,	_RP("Sega")},
	{11,	_RP("Taito")},
	{12,	_RP("Capcom")},
	{13,	_RP("Data East")},
	{14,	_RP("Namco (Namcot)")},
	{15,	_RP("Sun Electronics (Sunsoft)")},
	{16,	_RP("Ma-Ba")},
	{17,	_RP("Dempa")},
	{18,	_RP("Tecno Soft")},
	{19,	_RP("Tecno Soft")},
	{20,	_RP("Asmik")},
	{21,	_RP("ASCII")},
	{22,	_RP("Micronet")},
	{23,	_RP("VIC Tokai")},
	{24,	_RP("Treco, Sammy")},
	{25,	_RP("Nippon Computer Systems (Masaya)")},
	{26,	_RP("Sigma Enterprises")},
	{27,	_RP("Toho")},
	{28,	_RP("HOT-B")},
	{29,	_RP("Kyugo")},
	{30,	_RP("Video System")},
	{31,	_RP("SNK")},
	{32,	_RP("Wolf Team")},
	{33,	_RP("Kaneko")},
	{34,	_RP("DreamWorks")},
	{35,	_RP("Seismic Software")},
	{36,	_RP("Tecmo")},
	{38,	_RP("Mediagenic")},
	{40,	_RP("Toaplan")},
	{41,	_RP("UNIPACC")},
	{42,	_RP("UPL")},
	{43,	_RP("Human")},
	{44,	_RP("Sanritsu (SIMS)")},
	{45,	_RP("Game Arts")},
	{46,	_RP("Kodansha Research Institute")},
	{47,	_RP("Sage's Creation")},
	{48,	_RP("Tengen (Time Warner Interactive)")},
	{49,	_RP("Telenet Japan, Micro World")},
	{50,	_RP("Electronic Arts")},
	{51,	_RP("Microcabin")},
	{52,	_RP("SystemSoft (SystemSoft Alpha)")},
	{53,	_RP("Riverhillsoft")},
	{54,	_RP("Face")},
	{55,	_RP("Nuvision Entertainment")},
	{56,	_RP("Razorsoft")},
	{57,	_RP("Jaleco")},
	{58,	_RP("Visco")},
	{60,	_RP("Victor Musical Industries (Victor Entertainment, Victor Soft)")},
	{61,	_RP("Toyo Recording Co. (Wonder Amusement Studio)")},
	{62,	_RP("Sony Imagesoft")},
	{63,	_RP("Toshiba EMI")},
	{64,	_RP("Information Global Service")},
	{65,	_RP("Tsukuda Ideal")},
	{66,	_RP("Compile")},
	{67,	_RP("Home Data (Magical)")},
	{68,	_RP("CSK Research Institute (CRI)")},
	{69,	_RP("Arena Entertainment")},
	{70,	_RP("Virgin Interactive")},
	{71,	_RP("Nihon Bussan (Nichibutsu)")},
	{72,	_RP("Varie")},
	{73,	_RP("Coconuts Japan, Soft Vision")},
	{74,	_RP("PALSOFT")},
	{75,	_RP("Pony Canyon")},
	{76,	_RP("Koei")},
	{77,	_RP("Takeru (Sur De Wave)")},
	{79,	_RP("U.S. Gold")},
	{81,	_RP("Acclaim Entertainment, Flying Edge")},
	{83,	_RP("GameTek")},
	{84,	_RP("Datawest")},
	{85,	_RP("PCM Complete")},
	{86,	_RP("Absolute Entertainment")},
	{87,	_RP("Mindscape (The Software Toolworks)")},
	{88,	_RP("Domark")},
	{89,	_RP("Parker Brothers")},
	{91,	_RP("Pack-In Video (Victor Interactive Software, Pack-In-Soft, Victor Soft)")},
	{92,	_RP("Polydor (Sandstorm)")},
	{93,	_RP("Sony")},
	{95,	_RP("Konami")},
	{97,	_RP("Tradewest, Williams Entertainment, Midway Games")},
	{99,	_RP("Success")},
	{100,	_RP("THQ, Black Pearl Software)")},
	{101,	_RP("TecMagik Entertainment")},
	{102,	_RP("Samsung")},
	{103,	_RP("Takara")},
	{105,	_RP("Shogakukan Production")},
	{106,	_RP("Electronic Arts Victor")},
	{107,	_RP("Electro Brain")},
	{109,	_RP("Saddleback Graphics")},
	{110,	_RP("Dynamix (Simon & Schuster Interactive)")},
	{111,	_RP("American Laser Games")},
	{112,	_RP("Hi-Tech Expressions")},
	{113,	_RP("Psygnosis")},
	{114,	_RP("T&E Soft")},
	{115,	_RP("Core Design")},
	{118,	_RP("The Learning Company")},
	{119,	_RP("Accolade")},
	{120,	_RP("Codemasters")},
	{121,	_RP("ReadySoft")},
	{123,	_RP("Gremlin Interactive")},
	{124,	_RP("Spectrum Holobyte")},
	{125,	_RP("Interplay")},
	{126,	_RP("Maxis")},
	{127,	_RP("Working Designs")},
	{130,	_RP("Activision")},
	{132,	_RP("Playmates Interactive Entertainment")},
	{133,	_RP("Bandai")},
	{135,	_RP("CapDisc")},
	{137,	_RP("ASC Games")},
	{139,	_RP("Viacom New Media")},
	{141,	_RP("Toei Video")},
	{143,	_RP("Hudson (Hudson Soft)")},
	{144,	_RP("Atlus")},
	{145,	_RP("Sony Music Entertainment")},
	{146,	_RP("Takara")},
	{147,	_RP("Sansan")},
	{149,	_RP("Nisshouiwai Infocom")},
	{150,	_RP("Imagineer (Imadio)")},
	{151,	_RP("Infogrames")},
	{152,	_RP("Davidson & Associates")},
	{153,	_RP("Rocket Science Games")},
	{154,	_RP("Technōs Japan")},
	{157,	_RP("Angel")},
	{158,	_RP("Mindscape")},
	{159,	_RP("Crystal Dynamics")},
	{160,	_RP("Sales Curve Interactive")},
	{161,	_RP("Fox Interactive")},
	{162,	_RP("Digital Pictures")},
	{164,	_RP("Ocean Software")},
	{165,	_RP("Seta")},
	{166,	_RP("Altron")},
	{167,	_RP("ASK Kodansha")},
	{168,	_RP("Athena")},
	{169,	_RP("Gakken")},
	{170,	_RP("General Entertainment")},
	{172,	_RP("EA Sports")},
	{174,	_RP("Glams")},
	{176,	_RP("ASCII Something Good")},
	{177,	_RP("Ubisoft")},
	{178,	_RP("Hitachi")},
	{180,	_RP("BMG Interactive Entertainment (BMG Victor, BMG Japan)")},
	{181,	_RP("Obunsha")},
	{182,	_RP("Thinking Cap")},
	{185,	_RP("Gaga Communications")},
	{186,	_RP("SoftBank (Game Bank)")},
	{187,	_RP("Naxat Soft (Pionesoft)")},
	{188,	_RP("Mizuki (Spike, Maxbet)")},
	{189,	_RP("KAZe")},
	{193,	_RP("Sega Yonezawa")},
	{194,	_RP("We Net")},
	{195,	_RP("Datam Polystar")},
	{197,	_RP("KID")},
	{198,	_RP("Epoch")},
	{199,	_RP("Ving")},
	{200,	_RP("Yoshimoto Kogyo")},
	{201,	_RP("NEC Interchannel (InterChannel)")},
	{202,	_RP("Sonnet Computer Entertainment")},
	{203,	_RP("Game Studio")},
	{204,	_RP("Psikyo")},
	{205,	_RP("Media Entertainment")},
	{206,	_RP("Banpresto")},
	{207,	_RP("Ecseco Development")},
	{208,	_RP("Bullet-Proof Software (BPS)")},
	{209,	_RP("Sieg")},
	{210,	_RP("Yanoman")},
	{212,	_RP("Oz Club")},
	{213,	_RP("Nihon Create")},
	{214,	_RP("Media Rings Corporation")},
	{215,	_RP("Shoeisha")},
	{216,	_RP("OPeNBooK")},
	{217,	_RP("Hakuhodo (Hamlet)")},
	{218,	_RP("Aroma (Yumedia)")},
	{219,	_RP("Societa Daikanyama")},
	{220,	_RP("Arc System Works")},
	{221,	_RP("Climax Entertainment")},
	{222,	_RP("Pioneer LDC")},
	{223,	_RP("Tokuma Shoten")},
	{224,	_RP("I'MAX")},
	{226,	_RP("Shogakukan")},
	{227,	_RP("Vantan International")},
	{229,	_RP("Titus")},
	{230,	_RP("LucasArts")},
	{231,	_RP("Pai")},
	{232,	_RP("Ecole (Reindeer)")},
	{233,	_RP("Nayuta")},
	{234,	_RP("Bandai Visual")},
	{235,	_RP("Quintet")},
	{239,	_RP("Disney Interactive")},
	{240,	_RP("9003 (OpenBook9003)")},
	{241,	_RP("Multisoft")},
	{242,	_RP("Sky Think System")},
	{243,	_RP("OCC")},
	{246,	_RP("Increment P (iPC)")},
	{249,	_RP("King Records")},
	{250,	_RP("Fun House")},
	{251,	_RP("Patra")},
	{252,	_RP("Inner Brain")},
	{253,	_RP("Make Software")},
	{254,	_RP("GT Interactive Software")},
	{255,	_RP("Kodansha")},
	{257,	_RP("Clef")},
	{259,	_RP("C-Seven")},
	{260,	_RP("Fujitsu Parex")},
	{261,	_RP("Xing Entertainment")},
	{264,	_RP("Media Quest")},
	{268,	_RP("Wooyoung System")},
	{270,	_RP("Nihon System")},
	{271,	_RP("Scholar")},
	{273,	_RP("Datt Japan")},
	{278,	_RP("MediaWorks")},
	{279,	_RP("Kadokawa Shoten")},
	{280,	_RP("Elf")},
	{282,	_RP("Tomy")},
	{289,	_RP("KSS")},
	{290,	_RP("Mainichi Communications")},
	{291,	_RP("Warashi")},
	{292,	_RP("Metro")},
	{293,	_RP("Sai-Mate")},
	{294,	_RP("Kokopeli Digital Studios")},
	{296,	_RP("Planning Office Wada (POW)")},
	{297,	_RP("Telstar")},
	{300,	_RP("Warp, Kumon Publishing")},
	{303,	_RP("Masudaya")},
	{306,	_RP("Soft Office")},
	{307,	_RP("Empire Interactive")},
	{308,	_RP("Genki (Sada Soft)")},
	{309,	_RP("Neverland")},
	{310,	_RP("Shar Rock")},
	{311,	_RP("Natsume")},
	{312,	_RP("Nexus Interact")},
	{313,	_RP("Aplix Corporation")},
	{314,	_RP("Omiya Soft")},
	{315,	_RP("JVC")},
	{316,	_RP("Zoom")},
	{321,	_RP("TEN Institute")},
	{322,	_RP("Fujitsu")},
	{325,	_RP("TGL")},
	{326,	_RP("Red Company (Red Entertainment)")},
	{328,	_RP("Waka Manufacturing")},
	{329,	_RP("Treasure")},
	{330,	_RP("Tokuma Shoten Intermedia")},
	{331,	_RP("Sonic! Software Planning (Camelot)")},
	{339,	_RP("Sting")},
	{340,	_RP("Chunsoft")},
	{341,	_RP("Aki")},
	{342,	_RP("From Software")},
	{346,	_RP("Daiki")},
	{348,	_RP("Aspect")},
	{350,	_RP("Micro Vision")},
	{351,	_RP("Gainax")},
	{354,	_RP("FortyFive (45XLV)")},
	{355,	_RP("Enix")},
	{356,	_RP("Ray Corporation")},
	{357,	_RP("Tonkin House")},
	{360,	_RP("Outrigger")},
	{361,	_RP("B-Factory")},
	{362,	_RP("LayUp")},
	{363,	_RP("Axela")},
	{364,	_RP("WorkJam")},
	{365,	_RP("Nihon Syscom (Syscom Entertainment)")},
	{367,	_RP("FOG (Full On Games)")},
	{368,	_RP("Eidos Interactive")},
	{369,	_RP("UEP Systems")},
	{370,	_RP("Shouei System")},
	{371,	_RP("GMF")},
	{373,	_RP("ADK")},
	{374,	_RP("Softstar Entertainment")},
	{375,	_RP("Nexton")},
	{376,	_RP("Denshi Media Services")},
	{379,	_RP("Takuyo")},
	{380,	_RP("Starlight Marry")},
	{381,	_RP("Crystal Vision")},
	{382,	_RP("Kamata and Partners")},
	{383,	_RP("AquaPlus")},
	{384,	_RP("Media Gallop")},
	{385,	_RP("Culture Brain")},
	{386,	_RP("Locus")},
	{387,	_RP("Entertainment Software Publishing (ESP)")},
	{388,	_RP("NEC Home Electronics")},
	{390,	_RP("Pulse Interactive")},
	{391,	_RP("Random House")},
	{394,	_RP("Vivarium")},
	{395,	_RP("Mebius")},
	{396,	_RP("Panther Software")},
	{397,	_RP("TBS")},
	{398,	_RP("NetVillage (Gamevillage)")},
	{400,	_RP("Vision (Noisia)")},
	{401,	_RP("Shangri-La")},
	{402,	_RP("Crave Entertainment")},
	{403,	_RP("Metro3D")},
	{404,	_RP("Majesco")},
	{405,	_RP("Take-Two Interactive")},
	{406,	_RP("Hasbro Interactive")},
	{407,	_RP("Rage Software (Rage Games)")},
	{408,	_RP("Marvelous Entertainment")},
	{409,	_RP("Bottom Up")},
	{410,	_RP("Daikoku Denki")},
	{411,	_RP("Sunrise Interactive")},
	{412,	_RP("Bimboosoft")},
	{413,	_RP("UFO")},
	{414,	_RP("Mattel Interactive")},
	{415,	_RP("CaramelPot")},
	{416,	_RP("Vatical Entertainment")},
	{417,	_RP("Ripcord Games")},
	{418,	_RP("Sega Toys")},
	{419,	_RP("Gathering of Developers")},
	{421,	_RP("Rockstar Games")},
	{422,	_RP("Winkysoft")},
	{423,	_RP("Cyberfront")},
	{424,	_RP("DaZZ")},
	{428,	_RP("Kobi")},
	{429,	_RP("Fujicom")},
	{433,	_RP("Real Vision")},
	{434,	_RP("Visit")},
	{435,	_RP("Global A Entertainment")},
	{438,	_RP("Studio Wonder Effect")},
	{439,	_RP("Media Factory")},
	{441,	_RP("Red")},
	{443,	_RP("Agetec")},
	{444,	_RP("Abel")},
	{445,	_RP("Softmax")},
	{446,	_RP("Isao")},
	{447,	_RP("Kool Kizz")},
	{448,	_RP("GeneX")},
	{449,	_RP("Xicat Interactive")},
	{450,	_RP("Swing! Entertainment")},
	{451,	_RP("Yuke's")},
	{454,	_RP("AAA Game")},
	{455,	_RP("TV Asahi")},
	{456,	_RP("Crazy Games")},
	{457,	_RP("Atmark")},
	{458,	_RP("Hackberry")},
	{460,	_RP("AIA")},
	{461,	_RP("Starfish-SD")},
	{462,	_RP("Idea Factory")},
	{463,	_RP("Broccoli")},
	{465,	_RP("Oaks (Princess Soft)")},
	{466,	_RP("Bigben Interactive")},
	{467,	_RP("G.rev")},
	{469,	_RP("Symbio Planning")},
	{471,	_RP("Alchemist")},
	{473,	_RP("SNK Playmore")},
	{474,	_RP("D3Publisher")},
	{475,	_RP("Rain Software (Charara)")},
	{476,	_RP("Good Navigate (GN Software)")},
	{477,	_RP("Alfa System")},
	{478,	_RP("Milestone Inc.")},
	{479,	_RP("Triangle Service")},

	{0, nullptr}
};

/**
 * Comparison function for bsearch().
 * @param a
 * @param b
 * @return
 */
int RP_C_API SegaPublishersPrivate::compar(const void *a, const void *b)
{
	unsigned int code1 = static_cast<const TCodeEntry*>(a)->t_code;
	unsigned int code2 = static_cast<const TCodeEntry*>(b)->t_code;
	if (code1 < code2) return -1;
	if (code1 > code2) return 1;
	return 0;
}

/**
 * Look up a company code.
 * @param code Company code.
 * @return Publisher, or nullptr if not found.
 */
const rp_char *SegaPublishers::lookup(unsigned int code)
{
	// Do a binary search.
	const SegaPublishersPrivate::TCodeEntry key = {code, nullptr};
	const SegaPublishersPrivate::TCodeEntry *res =
		static_cast<const SegaPublishersPrivate::TCodeEntry*>(bsearch(&key,
			SegaPublishersPrivate::tcodeList,
			ARRAY_SIZE(SegaPublishersPrivate::tcodeList)-1,
			sizeof(SegaPublishersPrivate::TCodeEntry),
			SegaPublishersPrivate::compar));
	return (res ? res->publisher : nullptr);
}

}
