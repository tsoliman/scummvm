/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "engines/game.h"
#include "common/language.h"

namespace Glk {
namespace Glulx {

const PlainGameDescriptor GLULXE_GAME_LIST[] = {
	{ "glulx", "Glulx Game" },

	// English games
	{ "aardvarkhype",       "AardVarK versus The Hype" },
	{ "academregular",      "Academic Pursuits as Opposed to Regular Pursuits" },
	{ "acbs",               "A Cock and Bull Story" },
	{ "acg",                "Adventurer's Consumer Guide" },
	{ "acmj",               "The Making of ACMJ Game" },
	{ "adv350_glulx",       "Adventure" },
	{ "adventura",          "Adventura" },
	{ "ailiphilia",         "Ailiphilia" },
	{ "airport",            "The Airport" },
	{ "alabaster",          "Alabaster" },
	{ "aliasthemagpie",     "Alias 'The Magpie'" },
	{ "anatidaephobia",     "A N A T I D A E P H O B I A" },
	{ "anchorheaddemo",     "Anchorhead: Special Edition (Demo)" },
	{ "anchorhead",         "Anchorhead" },
	{ "andelmanyard",       "Andelmans' Yard" },
	{ "androawakefc",       "Andromeda Awakening - The Final Cut"},
	{ "andromeda1983",      "Andromeda 1983" },
	{ "andromedaapocext",   "Andromeda Apocalypse (Extended Edition)" },
	{ "andromedaascending", "Andromeda Ascending" },
	{ "andromedadream",     "Andromeda Dreaming" },
	{ "archaeologicalfict", "Archaeological Fiction" },
	{ "ariadneinaeaea",     "Ariadne in Aeaea" },
	{ "aroilingoriginal",   "A Roiling Original" },
	{ "artoffugue",         "Art of Fugue" },
	{ "ascensionlimb",      "Ascension of Limbs" },
	{ "ascentgothictower",  "The Ascent of the Gothic Tower" },
	{ "atc",                "ATC" },
	{ "aurora",             "Aurora" },
	{ "balances_glulx",     "Balances" },
	{ "baretegi",           "Baretegi" },
	{ "barroombrawl_glulx", "Barroom Brawl" },
	{ "batman66",           "Batman 66" },
	{ "beasttorrackmoor",   "The Beast of Torrack Moor" },
	{ "beingthere",         "Being There" },
	{ "briar",              "Briar" },
	{ "btyt",               "Bigger Than You Think" },
	{ "bureaucrocy_glulx",  "Bureaucrocy" },
	{ "buygold",            "Buy Gold" },
	{ "candlewindless",     "Candle Flames in Windless Air" },
	{ "canyouescape",       "Can You Escape" },
	{ "castronegroblues",   "Castronegro Blues" },
	{ "cave",               "Cave" },
	{ "checkpoint",         "Checkpoint" },
	{ "cheesedoff_glulx",   "Cheesed Off!" },
	{ "childrenloblolly",   "The Children of Loblolly Lodge" },
	{ "chipmonk",           "Chipmonk" },
	{ "codetopia",          "Codetopia - A Code Adventure" },
	{ "colderlight",        "The Colder Light" },
	{ "comp01tr",           "Comp01ter Game: N0n C0mp0s Ment1s" },
	{ "confhist",           "Conflicting Histories" },
	{ "cos",                "City of Secrets" },
	{ "cosmoserve_glulx",   "CosmoServe: An Adventure for the BBS-Enslaved" },
	{ "counterfeitmonkey",  "Counterfeit Monkey" },
	{ "countingcrabs",      "Counting Crabs: How Many Crabs Can You Count?" },
	{ "crackcoldone",       "Crack Open a Cold One With the Boiz" },
	{ "cragnemanor_glulx",  "Cragne Manor" },
	{ "damesdeadites",      "Dames and Deadites" },
	{ "darkcarnival",       "Dark Carnival" },
	{ "darkness_glulx",     "Darkness" },
	{ "deadcities",         "Dead Cities" },
	{ "deathofftc",         "Death Off the Cuff" },
	{ "diaperquest",        "Diaper Quest" },
	{ "discovertheworld",   "Discover The World" },
	{ "donotmeddle",        "Do Not Meddle" },
	{ "douchebag",          "Douchebag" },
	{ "dptmb2aa",           "Don't Push the Mailbox 2 and Aisle" },
	{ "dracula1_glulx",     "Dracula: Part 1, The First Night" },
	{ "dracula2_glulx",     "Dracula: Part 2, The Arrival" },
	{ "dragondemons",       "Dragon Demons" },
	{ "dragon_glulx",       "Dragon Adventure" },
	{ "dragonpass",         "Dragon's Pass" },
	{ "drolltolltroll",     "Droll Toll Troll" },
	{ "dudewheremyscapula", "Dude, Where's My Scapula" },
	{ "duelspannedages",    "The Duel That Spanned the Ages" },
	{ "dungeonspuzzle",     "Dungeon's Puzzle" },
	{ "dungeontext1",       "Dungeon Text I - Escape From Darkness" },
	{ "dynapowers",         "Dynamite Powers vs. The Ray of Night! (Director's Cut)" },
	{ "elsegar1",           "Elsegar I - Arrival" },
	{ "endlesssands",       "Endless Sands" },
	{ "endling",            "The Endling Archive" },
	{ "enterpriseincident", "The Enterprise Incidents: A Middle School Fantasy" },
	{ "equivocalingr",      "The Equivocal Ingredient" },
	{ "exigentseasons",     "The Exigent Seasons" },
	{ "familiar",           "The Familiar" },
	{ "farmquest",          "Farm Quest" },
	{ "fatevanguard",       "Fate of the Vanguard" },
	{ "finalproject",       "Final Project" },
	{ "flattenlondon",      "Flattened London" },
	{ "flexiblesurvival",   "Flexible Survival" },
	{ "further_glulx",      "Further" },
	{ "gaiawebch12",        "Gaia-Web Chapter 12: The Silence of the Thunder" },
	{ "gatewayferrets",     "Gateway of the Ferrets" },
	{ "genesisquest",       "Genesis Quest" },
	{ "getout",             "Get Out!" },
	{ "ghosteringtonnight", "Ghosterington Night" },
	{ "ghost",              "Ghost" },
	{ "glkchess",           "Glk Chess" },
	{ "glkebook",           "GlkeBook" },
	{ "greenmountains",     "The Green Mountains" },
	{ "hardpuzzle1",        "Hard Puzzle" },
	{ "hardpuzzle2",        "Hard Puzzle 2: The Cow" },
	{ "hardpuzzle3",        "Hard Puzzle 3: Origins" },
	{ "haroldnight2003",    "Harold Night 2003" },
	{ "herecomestreble",    "Here Comes Treble" },
	{ "hobbit",             "The Hobbit - The True Story" },
	{ "hobbitredux_glulx",  "The Hobbit - The True Story - Redux, Director's Cut" },
	{ "houseofmemories",    "House of Memories" },
	{ "houseofmystery",     "The House of Mystery" },
	{ "hungerdaemon",       "Hunger Daemon" },
	{ "illwind",            "Ill Wind" },
	{ "immunesystem",       "Immune System" },
	{ "improvorigins",      "Improv: Origins" },
	{ "ingoodcompany",      "In Good Company" },
	{ "jadeite",            "Jadeite for the Queen" },
	{ "jasonandmedea",      "Jason and Medea" },
	{ "kingshredspatches",  "The King of Shreds and Patches" },
	{ "klaustrophobia",     "Klaustrophobia" },
	{ "koa",                "Kingdom of Amphibia" },
	{ "lastresort",         "Last Resort" },
	{ "limeergot",          "Lime Ergot" },
	{ "limen",              "Limen" },
	{ "lmstvg_glulx",       "LMS The Video Game" },
	{ "lockeddoor10",       "Locked Door X: The Workprint" },
	{ "lockeddoor11",       "Locked Door XI: The US Theatrical Cut" },
	{ "lockkey",            "Lock and Key" },
	{ "lonelytroll",        "The Lonely Troll" },
	{ "lostislands",        "The Lost Islands of Alabaz" },
	{ "loveassistant",      "Lovely Assistant Magical Girl" },
	{ "makechange",         "Maybe make some change" },
	{ "makingme",           "The Making of Me" },
	{ "maryjaneoftomorrow", "The Mary Jane of Tomorrow" },
	{ "mgaeb",              "My Girlfriend's an Evil Bitch" },
	{ "midnightsnack",      "Midnight Snack" },
	{ "mollybutterthieves", "Molly and the Butter Thieves" },
	{ "moments1",           "Moments Out of Time: Renegade" },
	{ "moments2",           "Moments Out of Time 2: Adventure Type" },
	{ "monksea",            "Monk by the Sea" },
	{ "moonbaseindigo",     "Moonbase Indigo" },
	{ "mugglestudies",      "Muggle Studies" },
	{ "mystery",            "Mystery!" },
	{ "narco",              "Narcolepsy" },
	{ "necronskeep",        "Necron's Keep" },
	{ "newcat",             "New Cat" },
	{ "nightmare",          "Nightmare" },
	{ "nssri",              "No Sign Should Remain Inert" },
	{ "officegoose",        "Office Goose" },
	{ "oldfogey",           "Old Fogey" },
	{ "oliviasorphanorium", "Olivia's Orphanorium" },
	{ "onefishtwofish",     "One Fish, Two Fish, Red Fish" },
	{ "ottumwa_glulx",      "PDFA Ottumwa" },
	{ "phoenixfire",        "Phoenix-Fire" },
	{ "photopia_glulx",     "Photopia" },
	{ "piedaterreblunders", "Captain Piedaterre's Blunders" },
	{ "pinched",            "Pinched" },
	{ "pizzadelivery",      "Pizza Delivery" },
	{ "portfoliopiece",     "Portfolio Piece" },
	{ "pytho_glulx",        "Pytho's Mask" },
	{ "raidersstones",      "Raiders of the Holy Stones" },
	{ "rar",                "Reference and Representation" },
	{ "returnstars",        "Return to the Stars" },
	{ "reorbushcave_glulx", "Reor's Bush-Cave" },
	{ "risorg_glulx",       "Risorgimento Represso" },
	{ "robinorchid",        "Robin & Orchid" },
	{ "rocketmanfromsea",   "The Rocket Man from the Sea" },
	{ "roguelikegoose",     "Roguelike Goose" },
	{ "safe_glulx",         "Safe" },
	{ "sagebrushcactus",    "'Mid the sagebrush and the cactus" },
	{ "sagesanctum",        "Sage Sanctum Scramble" },
	{ "samfortunepi",       "Sam Fortune - Private Investigator" },
	{ "secretletter",       "Jack Toresal and the Secret Letter" },
	{ "section1awakened",   "Section 1 - Awakened" },
	{ "seedscafe",          "Seeds Cafe" },
	{ "sensory",            "Sensory Jam" },
	{ "shadowcathedral",    "The Shadow in the Cathedral" },
	{ "shadowoper",         "Shadow Operative" },
	{ "shapes",             "Shapes" },
	{ "sheephere",          "Sheep Here" },
	{ "signalerror",        "Signal Error" },
	{ "skmmc",              "Someone Keeps Moving My Chair" },
	{ "slouchbedlam",       "Slouching Towards Bedlam" },
	{ "smittenkittens",     "Smitten Kittens" },
	{ "songmockbird",       "The Song of the Mockingbird" },
	{ "spaceship",          "Spaceship!" },
	{ "speedracer",         "Speed Racer" },
	{ "spirI7wrak",         "SpirI7wrak" },
	{ "starlight_glulx",    "Starlight" },
	{ "superluminal",       "Superluminal Vagrant Twin" },
	{ "tcom",               "The Colour of Magic" },
	{ "terminator",         "Terminator" },
	{ "terminatorchaser",   "Terminator Chaser" },
	{ "theabbey",           "The Abbey" },
	{ "thebigfall",         "The Big Fall" },
	{ "thebox",             "The Box" },
	{ "thefourthriddle",    "The Fourth Riddle" },
	{ "thehouseoffear",     "The House of Fear, or, Loplop Introduces the World" },
	{ "theinformal7abbrev", "The Inform(al)7 Abbreviated Self Tutorial" },
	{ "thelaughinggnome",   "The Laughing Gnome" },
	{ "thelibrary",         "The Library" },
	{ "thelostkingdomcode", "The Lost Kingdom of Codetopia" },
	{ "thelostmountain",    "The Lost Mountain" },
	{ "themuseum",          "The Museum" },
	{ "theoutcasts",        "The Outcasts" },
	{ "thephoenixmove",     "The Phoenix Move" },
	{ "therealmofaoria",    "The Realm of A'oria" },
	{ "theredroom",         "The Red Room" },
	{ "thesimpletale",      "The Simple Tale" },
	{ "theskycrane",        "The Sky Crane" },
	{ "thespywhoatelunch",  "The Spy Who Ate Lunch" },
	{ "thestorm",           "The Storm" },
	{ "thethiefwovenwoods", "The Thief of Woven Woods" },
	{ "thetinyhouse",       "The Tiny House" },
	{ "thetraintoabaddon",  "The Train To Abaddon" },
	{ "thiefpokemon",       "Thief" },
	{ "timecapsule",        "A Time Capsule" },
	{ "timeless",           "Timeless" },
	{ "todayisthesame",     "Today is the Same as Any Other" },
	{ "tohellinahamper",    "To Hell in a Hamper" },
	{ "tomtrundle",         "The Incredibly Mild Misadventures of Tom Trundle" },
	{ "trialofthetnuop",    "Trial of the Inuop" },
	{ "trollslayer",        "Trollslayer" },
	{ "tryagain",           "Try Again" },
	{ "turbochest",         "Turbo Chest Hair Massacre" },
	{ "uie",                "Under, In Erebus" },
	{ "umw_glulx",          "UMW" },
	{ "uncleclemswill",     "Uncle Clem's Will" },
	{ "underground_glulx",  "Underground" },
	{ "unscientificfict",   "Unscientific Fiction" },
	{ "valleyofsteel",      "Valley of Steel" },
	{ "walking",            "Walking" },
	{ "awalkaround",        "A Walk Around the Neighborhood" },
	{ "wand",               "The Wand" },
	{ "winterstormdraco",   "Winter Storm Draco" },
	{ "wishertheurgist",    "Wisher, Theurgist, Fatalist" },
	{ "wizardsniffer",      "The Wizard Sniffer" },
	{ "wof",                "Works of Fiction" },
	{ "wordsofpower",       "Words of Power" },
	{ "yourdeath4acts",     "Your Death, in Four Acts" },
	{ "zeldata",            "The Legend of Zelda: A Text Adventure" },
	{ "zorkdm",             "Zork (by Dean Menezes)" },

	// Apollo 18+20: The IF Tribute Album
	{ "apollo3",            "Apollo 18+20 #03: She's Actual Size" },
	{ "apollo10",           "Apollo 18+20 #10: Narrow Your Eyes" },
	{ "apollo12",           "Apollo 18+20 #12: Which Describes How You're Feeling" },
	{ "apollo15",           "Apollo 18+20 #15: Turn Around" },
	{ "apollo19",           "Apollo 18+20 #19: Fingertips - I Hear the Wind Blow" },
	{ "apollo33",           "Apollo 18+20 #33: Fingertips - Mysterious Whispers" },

	// IFComp 2001
	{ "if01_bestof3",       "Best of Three" },                                                          //    7th Place
	{ "if01_carma",         "Carma" },                                                                  //   16th Place
	{ "if01_smtuc",         "Stiffy Makane: The Undiscovered Country" },                                //   31st Place
	{ "if01_aafn",          "An Apple From Nowhere" },                                                  //   39th Place
	{ "if01_sittm",         "Stick It to the Man" },                                                    //   41st Place

	// IFComp 2002
	{ "if02_eas2",          "Earth and Sky: Episode 2 - Another Earth, Another Sky" },                  //    1st Place

	// IFComp 2004
	{ "if04_eas3",          "Earth and Sky: Episode 3 - Luminous Horizon" },                            //    1st Place

	// IFComp 2005
	{ "if05_beyond_glulx",  "Beyond" },                                                                 //    2nd Place
	{ "if05_cheiron",       "Cheiron" },                                                                //   26th Place

	// IFComp 2006
	{ "if06_floatpoint",    "Floatpoint" },                                                             //    1st Place

	// IFComp 2007
	{ "if07_chineseroom",   "The Chinese Room" },                                                       //    5th Place
	{ "if07_varkana",       "Varkana" },                                                                //    6th Place
	{ "if07_ferrousring",   "Ferrous Ring" },                                                           //   13th Place

	// IFComp 2008
	{ "if08_nightfall",     "Nightfall" },                                                              //    2nd Place
	{ "if08_everybodydies", "Everybody Dies" },                                                         //    3rd Place
	{ "if08_crywolf",       "Cry Wolf" },                                                               //   11th Place
	{ "if08_recess",        "Recess at Last" },                                                         //   15th Place
	{ "if08_chnlsurf",      "Channel Surfing" },                                                        //   21st Place
	{ "if08_amo",           "A Martian Odyssey" },                                                      //   25th Place

	// IFComp 2009
	{ "if09_rover",         "Rover's Day Out" },                                                        //    1st Place
	{ "if09_brokenlegs",    "Broken Legs" },                                                            //    2nd Place
	{ "if09_earlgrey",      "Earl Grey" },                                                              //    5th Place
	{ "if09_resonance",     "Resonance" },                                                              //    7th Place
	{ "if09_gis",           "Grounded in Space" },                                                      //   10th Place

	// IFComp 2010
	{ "if10_aotearoa",      "Aotearoa" },                                                               //    1st Place
	{ "if10_oneeyeopen",    "One Eye Open" },                                                           //    3rd Place
	{ "if10_blindhouse",    "The Blind House" },                                                        //    4th Place
	{ "if10_grisjaune",     "Gris et Jaune" },                                                          //    9th Place
	{ "if10_divismortis",   "Divis Mortis" },                                                           //   11th Place
	{ "if10_oxygen",        "Oxygen" },                                                                 //   12th Place
	{ "if10_gigantomania",  "Gigantomania" },                                                           //   15th Place
	{ "if10_inerebus",      "Under, In Erebus" },                                                       //   16th Place
	{ "if10_followingstar", "The Bible Retold: Following a Star" },                                     //   19th Place

	// IFComp 2011
	{ "if11_tacofiction",   "Taco Fiction" },                                                           //    1st Place
	{ "if11_six",           "Six" },                                                                    //    2nd Place
	{ "if11_patanoir",      "PataNoir" },                                                               //    5th Place
	{ "if11_doctorm",       "The Life (and Deaths) of Doctor M" },                                      //    6th Place
	{ "if11_beet",          "Beet the Devil" },                                                         //    7th Place
	{ "if11_kerkerkruip",   "Kerkerkruip" },                                                            //    8th Place
	{ "if11_sentencing",    "Sentencing Mr. Liddell" },                                                 //   19th Place
	{ "if11_calm",          "Calm" },                                                                   //   20th Place
	{ "if11_thehours",      "The Hours" },                                                              //   22nd Place
	{ "if11_deathofschlig", "Death of Schlig" },                                                        //   26th Place
	{ "if11_faninterfer",   "Fan Interference" },                                                       //   27th Place
	{ "if11_playinggames",  "Playing Games" },                                                          //   28th Place
	{ "if11_awamightdread", "Awake the Mighty Dread" },                                                 //   31st Place
	{ "if11_luster",        "Luster" },                                                                 //   37th Place

	// IFComp 2012
	{ "if12_andromedaapoc", "Andromeda Apocalypse" },                                                   //    1st Place
	{ "if12_shufflearound", "Shuffling Around" },                                                       //    7th Place
	{ "if12_killerheadach", "A Killer Headache" },                                                      //    8th Place
	{ "if12_imos",          "In a Manor of Speaking" },                                                 //   10th Place
	{ "if12_jdal",          "J'dal" },                                                                  //   16th Place
	{ "if12_kicker",        "Kicker" },                                                                 //   20th Place

	// IFComp 2013
	{ "if13_coloratura",    "Coloratura" },                                                             //    1st Place
	{ "if13_robinorchid",   "Robin & Orchid" },                                                         //    2nd Place
	{ "if13_ooof",          "Ollie Ollie Oxen Free" },                                                  //    3rd Place
	{ "if13_captverdeterr", "Captain Verdeterre's Plunder" },                                           //    4th Place
	{ "if13_texbonavent",   "Tex Bonaventure and the Temple" },                                         //    5th Place
	{ "if13_rosewood",      "The House at the End of Rosewood Street" },                                //   16th Place
	{ "if13_awbp",          "A Wind Blown from Paradise" },                                             //   28th Place
	{ "if13_mazredugin",    "Mazredugin" },                                                             //   28th Place
	{ "if13_cardewhouse",   "The Cardew House" },                                                       //   32nd Place

	// IFComp 2014
	{ "if14_hungerdeamon",  "Hunger Daemon" },                                                          //    1st Place
	{ "if14_transparent",   "Transparent" },                                                            //   11th Place
	{ "if14_uglyoafs",      "Ugly Oafs" },                                                              //   18th Place
	{ "if14_jessedoorway",  "Jesse Stavro's Doorway" },                                                 //   19th Place
	{ "if14_andyetitmoves", "And Yet it Moves" },                                                       //   27th Place
	{ "if14_hill160",       "Hill 160" },                                                               //   36th Place
	{ "if14_arqon",         "Arqon" },                                                                  //   39th Place

	// IFComp 2015
	{ "if15_brainguzzlers", "Brain Guzzlers from Beyond!" },                                            //    1st Place
	{ "if15_map",           "Map" },                                                                    //    2nd Place
	{ "if15_midswordfight", "Midnight, Swordfight" },                                                   //    3rd Place
	{ "if15_subrosa",       "Sub Rosa" },                                                               //    6th Place
	{ "if15_untriches",     "Untold Riches" },                                                          //    8th Place
	{ "if15_ether",         "Ether" },                                                                  //   10th Place
	{ "if15_thesueno",      "The Sueño" },                                                              //   17th Place
	{ "if15_shireton",      "The Baker of Shireton" },                                                  //   19th Place
	{ "if15_gotomomi",      "Gotomomi" },                                                               //   20th Place
	{ "if15_probcompound",  "The Problems Compound" },                                                  //   24th Place
	{ "if15_laidoff",       "Laid off From the Synesthesia Factory" },                                  //   30th Place
	{ "if15_pilgrimage",    "Pilgrimage" },                                                             //   43rd Place
	{ "if15_recorded",      "Recorded" },                                                               //   51st Place

	// IFComp 2016
	{ "if16_colortruth",    "Color the Truth" },                                                        //    2nd Place
	{ "if16_pogomango",     "Pogoman GO!" },                                                            //    6th Place
	{ "if16_fair",          "Fair" },                                                                   //    7th Place
	{ "if16_rockpapsciss",  "How to Win at Rock Paper Scissors" },                                      //   10th Place
	{ "if16_ariadne",       "Ariadne in Aeaea" },                                                       //   12th Place
	{ "if16_worldstourn",   "The Game of Worlds TOURNAMENT!" },                                         //   14th Place
	{ "if16_mirrorqueen",   "Mirror and Queen" },                                                       //   22nd Place
	{ "if16_take",          "Take" },                                                                   //   28th Place
	{ "if16_sigilreader",   "Sigil Reader (Field)" },                                                   //   39th Place
	{ "if16_ventilator",    "Ventilator" },                                                             //   42nd Place
	{ "if16_theatrepeople", "Theatre People" },                                                         //   46th Place
	{ "if16_steamsacr",     "Steam and Sacrilege" },                                                    //   47th Place

	// IFComp 2017
	{ "if17_eatme",         "Eat Me" },                                                                 //    2nd Place
	{ "if17_absenceoflaw",  "Absence of Law" },                                                         //    5th Place
	{ "if17_owlconsults",   "The Owl Consults" },                                                       //    6th Place
	{ "if17_beautyaustere", "A Beauty Cold and Austere" },                                              //    7th Place
	{ "if17_1958dancing",   "1958 Dancing With Fear" },                                                 //    8th Place
	{ "if17_futurthreads",  "Future Threads" },                                                         //    9th Place
	{ "if17_thewand",       "The Wand" },                                                               //   11th Place
	{ "if17_wordoftheday",  "Word of the Day" },                                                        //   13th Place
	{ "if17_swigian",       "Swigian" },                                                                //   21st Place
	{ "if17_castlethread",  "A Castle of Thread" },                                                     //   35th Place
	{ "if17_rainbowbrdg",   "Rainbow Bridge" },                                                         //   37th Place
	{ "if17_measureless",   "Measureless to Man" },                                                     //   43th Place
	{ "if17_uerifcity",     "Ultimate Escape Room: IF City" },                                          //   47th Place
	{ "if17_8shoesshelves", "8 Shoes on the Shelves" },                                                 //   66th Place
	{ "if17_escapeterra",   "Escape From Terra" },                                                      //   75th Place
	{ "if17_hauntedp",      "Haunted P" },                                                              //   78th Place

	// IFComp 2018
	{ "if18_aliasmagpie",   "Alias The Magpie" },                                                       //    1st Place
	{ "if18_arithmancer",   "Junior Arithmancer" },                                                     //    7th Place
	{ "if18_engarde",       "En Garde" },                                                               //   14th Place
	{ "if18_rcm301303",     "Terminal Interface for Models RCM301303" },                                //   16th Place
	{ "if18_madametime",    "The Origin of Madame Time" },                                              //   17th Place
	{ "if18_templeshorgil", "The Temple of Shorgil" },                                                  //   20th Place
	{ "if18_charming",      "Charming" },                                                               //   24th Place
	{ "if18_dynapowers",    "Dynamite Powers vs. The Ray of Night!" },                                  //   25th Place
	{ "if18_redragon",      "Re: Dragon" },                                                             //   26th Place
	{ "if18_ailihphilia",   "Ailihphilia" },                                                            //   28th Place
	{ "if18_diddlebucker",  "Diddlebucker!" },                                                          //   30th Place
	{ "if18_pegasus",       "Pegasus" },                                                                //   41st Place
	{ "if18_bordereivers",  "Border Reivers" },                                                         //   46th Place
	{ "if18_bullhockey",    "Bullhockey!" },                                                            //   49th Place
	{ "if18_eunice",        "Eunice" },                                                                 //   59th Place
	{ "if18_birminghamiv",  "Birmingham IV" },                                                          //   69th Place

	// IFComp 2019
	{ "if19_zozzled",       "Zozzled" },                                                                //    1st Place
	{ "if19_sugarlawn",     "Sugarlawn" },                                                              //    4th Place
	{ "if19_skiesabove",    "Skies Above" },                                                            //   10th Place
	{ "if19_remedialwitch", "Remedial Witchcraft" },                                                    //   14th Place
	{ "if19_frenemies",     "Frenemies; or, I Won An Andy Phillips Game!" },                            //   17th Place
	{ "if19_underthesea",   "Under the Sea" },                                                          //   20th Place
	{ "if19_forthemoon",    "For the Moon Never Beams" },                                               //   22th Place
	{ "if19_clusterflux",   "Clusterflux" },                                                            //   27th Place
	{ "if19_goneoutfor",    "Gone Out For Gruyere" },                                                   //   30th Place
	{ "if19_4eccentrics",   "The Four Eccentrics" },                                                    //   31st Place
	{ "if19_hardpuzzle4",   "Hard Puzzle 4: The Ballad of Bob and Cheryl" },                            //   31st Place
	{ "if19_winterbreak",   "Winter Break at Hogwarts" },                                               //   41st Place
	{ "if19_mentertain",    "Mental Entertainment" },                                                   //   45th Place
	{ "if19_sycamorelane",  "The House on Sycamore Lane" },                                             //   50th Place
	{ "if19_jondoe",        "Jon Doe - Wildcard Nucleus" },                                             //   51st Place
	{ "if19_letsplay",      "Let's Play: Ancient Greek Punishment - The Text Adventure" },              //   54th Place
	{ "if19_citizennow",    "Citizen of Nowhere" },                                                     //   55th Place
	{ "if19_fatfair",       "Fat Fair" },                                                               //   66th Place
	{ "if19_oceanbeach",    "Ocean Beach" },                                                            //   68th Place
	{ "if19_randomescape",  "Randomized Escapeh" },                                                     //   76th Place
	{ "if19_vegibalisle",   "The Secret of Vegibal Island" },                                           //   77th Place

	// IFComp 2020
	{ "if20_vainempires",   "Vain Empires" },                                                           //    3rd Place
	{ "if20_magpietrain",   "The Magpie Takes the Train" },                                             //    5th Place
	{ "if20_eleusinian",    "The Eleusinian Miseries" },                                                //    6th Place
	{ "if20_aropeofchalk",  "A Rope of Chalk" },                                                        //    7th Place
	{ "if20_stuffoflegend", "Stuff of Legend" },                                                        //    8th Place
	{ "if20_flattenlondon", "Flattened London" },                                                       //   11th Place
	{ "if20_vampireltd",    "Vampire Ltd" },                                                            //   13th Place
	{ "if20_alone",         "Alone" },                                                                  //   14th Place
	{ "if20_sagesanctum",   "Sage Sanctum Scramble" },                                                  //   15th Place
	{ "if20_shadowoper",    "Shadow Operative" },                                                       //   20th Place
	{ "if20_ascensionlimb", "Ascension of Limbs" },                                                     //   22nd Place
	{ "if20_ferrymansgate", "Ferryman's Gate" },                                                        //   23rd Place
	{ "if20_academregular", "Academic Pursuits as Opposed to Regular Pursuits" },                       //   27th Place
	{ "if20_seasonapocal",  "Seasonal Apocalypse Disorder" },                                           //   33rd Place
	{ "if20_loveassistant", "Lovely Assistant Magical Girl" },                                          //   35th Place
	{ "if20_turbochest",    "Turbo Chest Hair Massacre" },                                              //   36th Place
	{ "if20_foraplace",     "For a Place by the Putrid Sea" },                                          //   41st Place
	{ "if20_timmott",       "The Incredibly Mild Misadventures of Tom Trundle" },                       //   59th Place
	{ "if20_desolation",    "Desolation" },                                                             //   70th Place
	{ "if20_waywardstory",  "The Wayward Story" },                                                      //   73rd Place
	{ "if20_underthey",     "Under They Thunder" },                                                     //   75th Place
	{ "if20_standshoulder", "Standing on the Shoulders of Giants" },                                    //   83rd Place
	{ "if20_lasthouse",     "Last House on the Block" },                                                //   93rd Place

	// IFComp 2021
	{ "if21_comehouse",     "And Then You Come to a House Not Unlike the Previous One" },               //    1st Place
	{ "if21_drhorror",      "Dr Horror's House of Terror" },                                            //    2nd Place
	{ "if21_songmockbird",  "The Song of the Mockingbird" },                                            //    3rd Place
	{ "if21_ghostguessed",  "What Heart Heard Of, Ghost Guessed" },                                     //    4th Place
	{ "if21_sting",         "Sting" },                                                                  //   13th Place
	{ "if21_findinglight",  "Finding Light" },                                                          //   18th Place
	{ "if21_remarkegg",     "Grandma Bethlinda's Remarkable Egg" },                                     //   23rd Place
	{ "if21_closure",       "Closure" },                                                                //   27th Place
	{ "if21_aardvarkhype",  "AardVarK versus The Hype" },                                               //   32nd Place
	{ "if21_hercules",      "Hercules!" },                                                              //   36th Place
	{ "if21_unfortunate",   "Unfortunate" },                                                            //   61st Place
	{ "if21_planewalker",   "Plane Walker" },                                                           //   68th Place

	// IFComp 2022
	{ "if22_sector471",     "Trouble in Sector 471" },                                                  //    5th Place
	{ "if22_awalkaround",   "A Walk Around the Neighborhood" },                                         //   14th Place
	{ "if22_arborea",       "Arborea" },                                                                //   15th Place
	{ "if22_crash",         "Crash" },                                                                  //   22nd Place
	{ "if22_amatter",       "A Matter of Heist Urgency" },                                              //   34th Place
	{ "if22_whoshotgum",    "Who Shot Gum E. Bear?" },                                                  //   35th Place
	{ "if22_youmaynotesc",  "You May Not Escape!" },                                                    //   38th Place
	{ "if22_lastchristmas", "The Last Christmas Present" },                                             //   43rd Place
	{ "if22_hiddentomb",    "The Hidden King's Tomb" },                                                 //   60th Place
	{ "if22_towerplargh",   "Tower of Plargh" },                                                        //   68th Place

	// The Mystery House Taken Over Project
	{ "mhto",               "Mystery House Taken Over" },
	{ "mhto3flippydisk",    "Mystery House Taken Over Ep. 3: Mystery House Kracked" },
	{ "mhto4cadre",         "Mystery House Taken Over Ep. 4: Mystery House Makeover!" },
	{ "mhto5dhan",          "Mystery House Taken Over Ep. 5: Casa Tomada" },
	{ "mhto6mg",            "Mystery House Taken Over Ep. 6: You Wake Up Itching" },
	{ "mhto7ll",            "Mystery House Taken Over Ep. 7: Glass Boxes" },
	{ "mhto8rettberg",      "Mystery House Taken Over Ep. 8: Mystery House Remixedup" },

	// Cover Stories Game-Jam
	{ "cs_spelunking",      "IFDB Spelunking" },
	{ "cs_oliviaorph",      "Olivia's Orphanorium" },

	// Ectocomp 2013
	{ "ec13_voodooyoudo",   "The Voodoo You Do" },                                                      //    9th Place
	{ "ec13_jack",          "Jack" },                                                                   //   16th Place

	// Ectocomp 2014
	{ "ec14_lisey",         "Lisey" },                                                                  //    4th Place
	{ "ec14_firstperson",   "First Person" },                                                           //    7th Place
	{ "ec14_voodooyoudo2",  "The Voodoo You Do 2" },                                                    //   10th Place
	{ "ec14_carriageret",   "Carriage Returns" },                                                       //   15th Place

	// Ectocomp 2015 - La Petite Mort
	{ "ec15_hallowdance",   "Halloween Dance" },                                                        //    5th Place

	// Ectocomp 2016 - La Petite Mort
	{ "ec16_low",           "Low" },                                                                    //    2nd Place
	{ "ec16_becausemine",   "Because You're Mine" },                                                    //    7th Place
	{ "ec16_toiletomega",   "Toiletworld Omegae" },                                                     //   13th Place

	// Ectocomp 2016 - Le Grand Guignol
	{ "ec16_psychomanteum", "Psychomanteum" },                                                          //    3rd Place

	// Ectocomp 2017 - La Petite Mort
	{ "ec17_bloodyraoul",   "Bloody Raoul" },                                                           //    5th Place
	{ "ec17_somethinnight", "Something in the Night" },                                                 //   11th Place

	// Ectocomp 2018 - La Petite Mort
	{ "ec18_wakeup_glulx",  "Wake Up" },                                                                //      Entrant

	// Ectocomp 2018 - Le Grand Guignol
	{ "ec18_tfcb1fealglas", "Tales from Castle Balderstone #1: Fealglass" },                            //       Winner
	{ "ec18_plshel_glulx",  "Please Help Me" },                                                         //      Entrant

	// Ectocomp 2019 - Le Grand Guignol
	{ "ec19_tfcb2durango",  "Tales from Castle Balderstone #2: Romance in Durango" },                   //    3rd Place
	{ "ec19_whenhedied",    "When He Died" },                                                           //    4th Place

	// Ectocomp 2020 - La Petite Mort
	{ "ec20_pilgrim",       "A Pilgrim" },                                                              //    2nd Place
	{ "ec20_lastday",       "Last Day" },                                                               //   11th Place

	// Ectocomp 2020 - Le Grand Guignol
	{ "ec20_tfcb3vultrine", "Tales from Castle Balderstone #3: The Inquisitor Vultrine" },              //    2nd Place
	{ "ec20_ritussacri",    "Ritus Sacri" },                                                            //    6th Place

	// Ectocomp 2021 - La Petite Mort
	{ "ec21_hauntedmustac", "Haunted Mustache Pizza Delivery" },                                        //    4th Place
	{ "ec21_yourdeath2act", "Your Death, in Two Acts" },                                                //    9th Place

	// Ectocomp 2021 - Le Grand Guignol
	{ "ec21_thelookout",    "The Lookout" },                                                            //    2nd Place
	{ "ec21_thecrew",       "The Crew - Journey to the Pale Planet" },                                  //    4th Place
	{ "ec21_jack",          "Jack" },                                                                   //    7th Place

	// Ectocomp 2022 - La Petite Mort
	{ "ec22_tortortortort", "Trick or Treat or Trick or Treat or Trick" },                              //   18th Place
	{ "ec22_kidnapfairy",   "Reg and the Kidnapped Fairy" },                                            //   19th Place

	// Ectocomp 2022 - Le Grand Guignol
	{ "ec22_thespectators", "The Spectators" },                                                         //    2nd Place
	{ "ec22_apumpkin",      "A Pumpkin" },                                                              //    8th Place
	{ "ec22_oldhhouse",     "This Old Haunted House" },                                                 //   12th Place
	{ "ec22_nowheresville", "Nowheresville" },                                                          //   14th Place

	// HighlandComp
	{ "hc_catchhaggid",     "Catch That Haggis" },

	// Imaginary Games From Imaginary Universes Jam
	{ "ig_dreamrevised",    "Dreamland Revised" },
	{ "ig_gaiasweb",        "Gaia's Web" },
	{ "ig_unrealcity",      "Unreal City" },

	// IntroComp 2002
	{ "ic02_jingo",         "Hey, Jingo!" },                                                            //       Winner
	{ "ic02_genie",         "Genie" },                                                                  //      Entrant

	// IntroComp 2004
	{ "ic04_gauss",         "The Homework of Little Carl Gauss" },                                      //      Entrant

	// IntroComp 2007
	{ "ic07_3princes",      "Three Princes" },                                                          // Hon. Mention

	// IntroComp 2008
	{ "ic08_phoenixland",   "Phoenix's Landing: Destiny" },                                             //       Winner

	// IntroComp 2010
	{ "ic10_fangvsclaw",    "Fang vs Claw" },                                                           // Hon. Mention

	// IntroComp 2011
	{ "ic11_chunkyblues",   "Chunky Blues" },                                                           // Hon. Mention
	{ "ic11_seasons",       "Seasons" },                                                                // Hon. Mention
	{ "ic11_zmatter",       "The Z-Machine Matter" },                                                   // Hon. Mention

	// IntroComp 2012
	{ "ic12_compliance",    "Compliance" },                                                             //    2nd Place
	{ "ic12_belief",        "Belief" },                                                                 //    3rd Place
	{ "ic12_genesis",       "Genesis" },                                                                // Hon. Mention

	// IntroComp 2013
	{ "ic13_blplains",      "Best Laid Plans" },                                                        //    1st Place
	{ "ic13_akkoteaque",    "Akkoteaque" },                                                             //    2nd Place
	{ "ic13_vanishconjur",  "The Vanishing Conjurer" },                                                 //    3rd Place
	{ "ic13_first",         "First" },                                                                  // Hon. Mention
	{ "ic13_what1984",      "What Happened in 1984" },                                                  // Hon. Mention

	// IntroComp 2014
	{ "ic14_cuckoldsegg",   "The Cuckold’s Egg" },                                                      //    1st Place
	{ "ic14_scrollthief",   "The Scroll Thief" },                                                       //    2nd Place
	{ "ic14_terribledoubt", "The Terrible Doubt of Appearances" },                                      //    3rd Place
	{ "ic14_hornetsnest",   "Hornets’ Nest" },                                                          // Hon. Mention

	// IntroComp 2015
	{ "ic15_beyondivision", "Beyond Division" },                                                        //    1st Place
	{ "ic15_meld",          "Meld" },                                                                   //    3rd Place
	{ "ic15_voltagecafe",   "Voltage Cafe" },                                                           // Hon. Mention

	// IntroComp 2016
	{ "ic16_spellbound",    "Spellbound" },                                                             //    1st Place
	{ "ic16_somexceptions", "Some Exceptions for Reasons Unknown" },                                    //    2nd Place

	// IntroComp 2017
	{ "ic17_sherlockind",   "Sherlock Indomitable" },                                                   //    1st Place
	{ "ic17_onnakabuki",    "Onna Kabuki" },                                                            //    2nd Place
	{ "ic17_adameveprj",    "The Adam and Eve Project" },                                               //    3rd Place
	{ "ic17_duckmans",      "Duckman" },                                                                // Hon. Mention
	{ "ic17_prizon",        "Prizon" },                                                                 // Hon. Mention

	// IntroComp 2018
	{ "ic18_introimplarc",  "Intro to Implements of the Arcane" },                                      //    1st Place

	// IntroComp 2019
	{ "ic19_intodevilmus",  "Intro to The Devil's Music" },                                             //    1st Place
	{ "ic19_imprisoned",    "Imprisoned" },                                                             // Hon. Mention

	// IntroComp 2020
	{ "ic20_foreignsoil",   "Foreign Soil" },                                                          //  Hon. Mention
	{ "ic20_foolrescue",    "Intro to a Fool’s Rescue" },                                              //  Hon. Mention
	{ "ic20_theinterview",  "The Interview" },                                                         //  Hon. Mention

	// IF Library Competition 2003
	{ "lc_lazygods",        "Lazy Gods of Earth" },

	// Metafilter IF Competition 2009
	{ "me09_questionable",  "The Questionable Substitute" },

	// 9th Annual New Year's Mincomp
	{ "ny09_candleflames",  "Candle Flames in Windless Air" },
	{ "ny09_trolleyprob",   "Her Majesty’s Trolley Problem" },
	{ "ny09_stayingput",    "Staying Put" },
	{ "ny09_mhairiesioux",  "Mhairie Sioux Escrivain and the Dracula of Hogwarts" },
	{ "ny09_daytimestood",  "The Day Time Stood Still" },

	// 10th Annual New Year's Mincomp
	{ "ny10_anatidaephob",  "Anatidaephobia" },
	{ "ny10_dayishootalex", "The Day I Shot Alex" },
	{ "ny10_thehorste",     "The Horste" },
	{ "ny10_yaminabe",      "Yami-Nabe!!" },

	// 11th Annual New Year's Mincomp
	{ "ny11_finishyourfoe", "Finish your Foe!" },
	{ "ny11_quickfire",     "Quickfire" },
	{ "ny11_red",           "Red" },
	{ "ny11_thedaygotpet",  "The Day We Got a Pet" },

	// One Room Game Competition 2006
	{ "1r06_formamentis",   "Forma Mentis" },

	// One Room Game Competition 2007
	{ "1r07_notteprima",    "Notte Prima dell’Esame" },

	// Shufflecomp Competition 2014
	{ "sh14_1942",          "1942" },
	{ "sh14_lightmyway",    "Light My Way Home" },
	{ "sh14_8mileshigh",    "Eight Miles High" },
	{ "sh14_fallshelter",   "Fallout Shelter" },
	{ "sh14_groovebilly",   "Groove Billygoat" },
	{ "sh14_invisiparties", "Invisible Parties" },
	{ "sh14_sequitur",      "Sequiturs" },
	{ "sh14_sparkle",       "Sparkle" },

	// ShuffleComp: Disc 2 Competition
	{ "shd_comrade",        "Comrade" },
	{ "shd_bythelake",      "By the Lake" },
	{ "shd_mollybutter",    "Molly and the Butter Thieves" },
	{ "shd_landunderwater", "When the Land Goes Under the Water" },

	// SpeedIF -1 Competition
	{ "sif_newgrant",       "NewGrant" },

	// SpeedIF 11th Anniversary Competition
	{ "sif_marvex",         "Marvex the Super-Robot vs Bolo!" },

	// SpeedIF 18th Anniversary Competition
	{ "sif_interpizza",     "Interstellar Pizza Brigade" },

	// SpeedIF New Year's Speed Competition 2011
	{ "sif_dansenocturne",  "Danse Nocturne" },

	// SpeedIF New Year's Speed Competition 2014
	{ "sif_dayofthequeen",  "The Day of the Queen" },

	// SpeedIF Potato Peeler Competition
	{ "sif_deadmanhug",     "A Dead Man’s Hug" },
	{ "sif_4dayssummer",    "Four Days of Summer" },
	{ "sif_peelinglucky",   "Peeling Lucky" },

	// SpeedIF Thanksgiving Competition
	{ "sif_yoursisearth",   "Yours Is the Earth and Everything That’s in It" },

	// SpeedIF XYZZY Competition
	{ "sif_zigzy",          "Zig-Zy" },

	// SpeedIF Bouchercomp Competition
	{ "sif_lowellprison",   "Lowell Prison" },

	// Toaster Competition
	{ "toa_youretoast",     "(You’re) TOAST!" },

	// Spring Thing 2008
	{ "stc08_bluelacuna",   "Blue Lacuna" },                                                            //    3rd Place

	// Spring Thing 2009
	{ "stc09_flustereduck", "A Flustered Duck" },                                                       //    1st Place

	// Spring Thing 2011
	{ "stc11_lostislands",  "The Lost Islands of Alabaz" },                                             //    1st Place
	{ "stc11_bonehead",     "Bonehead" },                                                               //    2nd Place
	{ "stc11_wetlands",     "Wetlands" },                                                               //    3rd Place
	{ "stc11_stiffymakane", "Mentula Macanus: Apocolocyntosis" },                                       //    4th Place
	{ "stc11_promise",      "The Promise" },                                                            //    5th Place
	{ "stc11_halloweve",    "Hallow Eve" },                                                             //    6th Place

	// Spring Thing 2012
	{ "stc12_eggnewbie",    "The Egg and the Newbie" },                                                 //    3rd Place

	// Spring Thing 2013
	{ "stc13_rollingorig",  "A Roiling Original" },                                                     //    2nd Place

	// Spring Thing 2014
	{ "stc14_bearcreek",    "Bear Creek" },                                                             //    5th Place
	{ "stc14_bibliophile",  "The Bibliophile" },                                                        //      Entrant

	// Spring Thing 2015 - Main Festival
	{ "stc15_tobysnose",    "Toby’s Nose" },                                                            //       Winner

	// Spring Thing 2016 - Back Garden
	{ "stc16_deadmanshill", "Dead Man’s Hill" },                                                        //      Entrant
	{ "stc16_foofoo",       "Foo Foo" },                                                                //      Entrant
	{ "stc16_3cardtrick",   "Three-Card Trick" },                                                       //      Entrant

	// Spring Thing 2017 - Main Festival
	{ "stc17_bobbybonnie",  "Bobby and Bonnie" },                                                       //       Winner

	// Spring Thing 2017 - Back Garden
	{ "stc17_afotwoaae",    "A Fly on the Wall, or An Appositional Eye" },                              //      Entrant
	{ "stc17_buckthepast",  "Buck the Past" },                                                          //      Entrant
	{ "stc17_weightsoul",   "The Weight of a Soul" },                                                   //      Entrant

	// Spring Thing 2018 - Main Festival
	{ "stc18_illum",        "Illuminismo Iniziato" },                                                   //       Winner
	{ "stc18_bunchkeys",    "A Bunch of Keys" },                                                        //      Entrant
	{ "stc18_sherlockind",  "Sherlock Indomitable" },                                                   //      Entrant

	// Spring Thing 2019 - Main Festival
	{ "stc19_bullhockey2",  "Bullhockey 2 - The Return of the Leather Whip" },                          //      Entrant
	{ "stc19_emptychamber", "The Empty Chamber" },                                                      //      Entrant
	{ "stc19_foundermercy", "Founder’s Mercy" },                                                        //      Entrant

	// Spring Thing 2020 - Main Festival
	{ "stc20_gameneverend", "The Game That Never Ends" },                                               //      Entrant
	{ "stc20_landlunch",    "The Land of Breakfast and Lunch" },                                        //      Entrant
	{ "stc20_napierscache", "Napier’s Cache" },                                                         //      Entrant
	{ "stc20_prongleman",   "The Prongleman Job" },                                                     //      Entrant

	// Spring Thing 2020 - Back Garden
	{ "stc20_77verbs",      "77 Verbs" },                                                               //      Entrant

	// Spring Thing 2021 - Main Festival
	{ "stc21_weightsoul",   "The Weight of a Soul" },                                                   // Best in Show
	{ "stc21_baggage",      "Baggage" },                                                                //      Entrant
	{ "stc21_meantucker",   "Mean Mother Trucker" },                                                    //      Entrant

	// Spring Thing 2021 - Back Garden
	{ "stc21_shorofcash",   "So I Was Short of Cash and Took on a Quest" },                             //      Entrant

	// Spring Thing 2022  - Main Festival
	{ "stc22_fairest",      "Fairest" },                                                                // Best in Show
	{ "stc22_brightbball",  "The Bright Blue Ball" },                                                   //      Entrant
	{ "stc22_digit",        "Digit" },                                                                  //      Entrant
	{ "stc22_hlmarooned",   "Hinterlands: Marooned!" },                                                 //      Entrant
	{ "stc22_leghorsegirl", "The Legend of Horse Girl" },                                               //      Entrant
	{ "stc22_toursrtorus",  "Tours Roust Torus" },                                                      //      Entrant

	// Spring Thing 2022 - Back Garden
	{ "stc22_adrift",       "A D R I F T" },                                                            //      Entrant

	// Spring Thing 2023  - Main Festival
	{ "stc23_repeatending", "Repeat the Ending" },                                                      // Best in Show
	{ "stc23_galaxyjones",  "Galaxy Jones" },                                                           //      Entrant
	{ "stc23_nothingfurth", "Nothing Could Be Further From the Truth" },                                //      Entrant
	{ "stc23_rdoorydoor",   "Red Door Yellow Door" },                                                   //      Entrant
	{ "stc23_sacredshovel", "The Sacred Shovel of Athenia" },                                           //      Entrant

	// Spring Thing 2023 - Back Garden
	{ "stc23_stygiandream", "Stygian Dreams" },                                                         //      Entrant

	// French games
	{ "archcivesuliroya",   "Archives Culinaires Royales - Période d’Essai" },
	{ "astressolitaires",   "Astres Solitaires" },
	{ "ekphrasis",          "Ekphrasis" },
	{ "fautedeservo",       "Faute de Servo" },
	{ "heuresduvent",       "Les Heures du Vent" },
	{ "latempete",          "La Tempête" },
	{ "kebabhante",         "Le Kébab Hanté" },
	{ "lieuxcommuns_glulx", "Lieux communs" },
	{ "petitgnome_glulx",   "Petit Gnome" },
	{ "sarvegne_glulx",     "Sarvegne" },
	{ "scarabeekatana",     "Le Scarabee et le Katana" },
	{ "tempetebermudes",    "Tempete sur les Bermudes" },
	{ "templefeu",          "Le Temple de Feu" },
	{ "tourorastre",        "La Tour d'Orastre" },

	// French Comp 2007
	{ "frc_souterraine",    "Souterraine" },                                                            //    4th Place
	{ "frc_ilephare_glulx", "L'Ile du Phare Abandonné" },                                               //    5th Place

	// French Comp 2008
	{ "frc_survivre",       "Survivre" },                                                               //    3rd Place

	// French Comp 2013
	{ "frc_noirdencre",     "Noir d'Encre" },                                                           //    2nd Place

	// French Comp 2015
	{ "frc_sourire",        "Sourire de Bois" },                                                        //    2nd Place
	{ "frc_comedie",        "Comédie" },                                                                //    3rd Place

	// French Comp 2018
	{ "frc_fauteservo",     "Faute de servo" },                                                         //    2nd Place
	{ "frc_latempete",      "La Tempête" },                                                             //    4th Place

	// German games
	{ "alleinkai",          "Allein mit Kai" },
	{ "dergarten",          "Der Garten" },
	{ "deronirischegarten", "Der Onirische Garten" },
	{ "dickeswep1",         "Dickes W - Zwischen Tanke und Panke: Der Mietstreit" },
	{ "dickeswep2",         "Dickes W - Zwischen Tanke und Panke: Weihnachtsterror" },
	{ "drkongpoodle",       "Dr. Kong in: Exploding Poodle Inevitable" },
	{ "homunculus",         "Homunculus" },
	{ "jaeger",             "Jäger der Heiligen Steine" },
	{ "kleinehalbling",     "Der Kleine Halbling" },
	{ "matthiasclaudius",   "Der Unsägliche und Vermeidbare Tod des Matthias Claudius" },
	{ "morgenwirdklausur",  "Morgen Wird Klausur Geschrieben" },
	{ "patanoirde",         "PataNoir - Ein Unvergleichlicher Kriminalfall" },
	{ "sonntagnachmittag",  "An Einem Sonntagnachmittag" },
	{ "spaterbesuch",       "Ein Später Besuch" },

	// Textfire Grand Prix 2005
	{ "tgp_bananerepublik", "Bananenrepublik" },                                                        //    2nd Place

	// Textfire Grand Prix 2010
	{ "tgp_ares",           "Ares" },                                                                   //    1st Place

	// Textfire Grand Prix 2011
	{ "tgp_roteblum",       "Die Rote Blume" },                                                         //    1st Place
	{ "tgp_schiesbefehl",   "Schießbefehl" },                                                           //    3rd Place

	// Textfire Grand Prix 2014
	{ "tgp_treffen",         "Treffen am Nebelgrat" },                                                  //    1st Place
	{ "tgp_dersigkeitenlad", "Der Süßigkeitenladen" },                                                  //    4th Place

	// Italian games
	{ "beyondita_glulx",    "Beyond" },
	{ "pietraluna_glulx",   "La Pietra della Luna" },
	{ "poesia_glulx",       "Manca Solo un Verso a Quella Poesia" },
	{ "schizo",             "Schizo - Escape to the Void" },
	{ "slenderman",         "Slenderman - L'Incubo" },
	{ "snuff",              "Snuff Movie" },
	{ "villamorgana_glulx", "Villa Morgana" },

	// Spanish games
	{ "alienlaaventura",    "ALIEN: La Aventura" },
	{ "conrumbo_glulx",     "Con Rumbo" },
	{ "hhorcus_glulx",      "Homo Homini Orcus" },
	{ "kerulen_glulx",      "Ke Rulen los Petas" },
	{ "lanochedelensayo",   "La Noche del Ensayo" },
	{ "legado",             "El Legado" },
	{ "regente",            "El Anillo Regente" },
	{ "rur",                "Las Aventuras de Rudolphine Rur" },
	{ "ultimohogar_glulx",  "Misterio en el Ultimo Hogar" },

	// Swedish games
	{ "drakmagi_glulx",     "Drakmagi (Dragon Magic)" },
	{ "vanyar_glulx",       "Vanyar" },

	// Russian games
	{ "devours",            "All Things Devours" },

	// ParserComp 2015
	{ "pc15_chlorophyll",   "Chlorophyll" },                                                            //    1st Place
	{ "pc15_oppositeopal",  "Oppositely Opal" },                                                        //    2nd Place
	{ "pc15_delphinahouse", "Delphina's House" },                                                       //    3rd Place
	{ "pc15_alongdrink",    "A Long Drink" },                                                           //      Entrant
	{ "pc15_downserpent",   "Down, the Serpent and the Sun" },                                          //      Entrant
	{ "pc15_endlesssands",  "Endless Sands" },                                                          //      Entrant
	{ "pc15_lockdown",      "Lockdown" },                                                               //      Entrant
	{ "pc15_terminator",    "Terminator" },                                                             //      Entrant
	{ "pc15_terminatchase", "Terminator Chaser" },                                                      //      Entrant

	// ParserComp 2021
	{ "pc21_grooverland",   "Grooverland" },                                                            //    1st Place
	{ "pc21_foreignsoil",   "Foreign Soil" },                                                           //    2nd Place
	{ "pc21_blackknife",    "Black Knife Dungeon" },                                                    //    3rd Place
	{ "pc21_timemachi21",   "The Time Machine" },                                                       //    6th Place
	{ "pc21_returnstars",   "Return to the Stars" },                                                    //   11th Place
	{ "pc21_daddybirthday", "Daddy's Birthday" },                                                       //   15th Place
	{ "pc21_gameon",        "Loud House ’Game On’" },                                                   //   16th Place

	// ParserComp 2022
	{ "pc22_shadowsdeep",   "Of Their Shadows Deep" },                                                  //    2nd Place
	{ "pc22_improvorigins", "Improv: Origins" },                                                        //    3rd Place
	{ "pc22_midnightself",  "Midnight at Al’s Self Storage, Truck Rentals" },                           //    8th Place
	{ "pc22_themuse",       "The Muse" },                                                               //   11th Place
	{ "pc22_anitasgoodbye", "Anita's Goodbye" },                                                        //   14th Place

	// ParserComp 2023
	{ "pc23_playerppa",     "Player A - The Purple Pearl: A Two Player Adventure" },                    //    1st Place
	{ "pc23_playerppb",     "Player B - The Purple Pearl: A Two Player Adventure" },                    //    1st Place
	{ "pc23_jessecompass",  "Jesse Stavro's Compass" },                                                 //    2nd Place
	{ "pc23_hinterlands",   "Hinterlands: Delivered!" },                                                //    5th Place

	// Event One of the Second Quadrennial Ryan Veeder Exposition for Good Interactive Fiction
	{ "caduceus",           "Caduceus" },                                                               //    1st Place
	{ "abandonedpools",     "Antique Panzitoum" },                                                      //    2nd Place
	{ "scarletportrait",    "Scarlet Portrait Parlor" },                                                //    3rd Place
	{ "gayscience",         "The Gay Science" },                                                        //    4th Place
	{ "magnificientmuseum", "The Magnificent Museum of Masterly Masterworks" },                         //    5th Place
	{ "whishperedream",     "A Whispered Dream" },                                                      //    6th Place
	{ "upspookyhouseq2e1",  "Upon the Spooky House" },                                                  //    7th Place

	// Event Two of the Second Quadrennial Ryan Veeder Exposition for Good Interactive Fiction
	{ "gaiazivajarilo",     "Gaia, Živa, Jarilo" },                                                     //    1st Place
	{ "oldkingnebb",        "Old King Nebb" },                                                          //    2nd Place
	{ "indistinguishable",  "Indistinguishable" },                                                      //    3rd Place

	// Event Three of the Second Quadrennial Ryan Veeder Exposition for Good Interactive Fiction
	{ "85verbs",            "85 Verbs" },                                                               //    1st Place
	{ "upspookyhouseq2e3",  "Upon the Spooky House" },                                                  //    3rd Place

	// SeedComp! 2023
	{ "aftertheaccident",   "After the Accident" },                                                     //    2nd Place
	{ "hismajesty",         "His Majesty's Royal Space Navy Service Handbook" },                        //    2nd Place
	{ "magicword",          "The Magic Word" },                                                         //      Entrant

	// NarraScope 2020 Game Jam
	{ "quicksketch",        "A Quick Sketch" },
	{ "movingon",           "Moving (On)" },
	{ "narcissi",           "Narcissi" },
	{ "sohoekekalmoe",      "Sohoek Ekalmoe" },
	{ "timeoutwasteland",   "Timeout in the Wasteland" },

	// Single Choice Jam
	{ "boing",              "Boing!" },
	{ "chinesefamily",      "Chinese Family Dinner Moment" },
	{ "ifyouhadoneshot",    "If You Had One Shot" },

	{ nullptr, nullptr }
};

const GlkDetectionEntry GLULXE_GAMES[] = {
	// English games
	DT_ENTRY1("aardvarkhype", "211104", "a5d8109ab52c23b571a069f840b87288", 1289116),
	DT_ENTRY1("academregular", "201018", "f960ae98eb122500ae82e5bb49b432a4", 929766),
	DT_ENTRY1("acbs", "170705", "6b108c327301ccba5de41f3b98772b33", 1334066),
	DT_ENTRY1("acg", "070501", "1a3eb782d28dd8ae8da40f21adb174f0", 817408),
	DT_ENTRY1("acmj", "220607", "581a2d9a0df17a2852cf28a14bd78a46", 602220),
	DT_ENTRY1("adv350_glulx", "961209/v1", "cf232df2a3364a6f0821a8ef631c81a1", 167424),
	DT_ENTRY1("adv350_glulx", "961209/v2", "e1939485dc2d4aab637144fc842b479d", 195406),
	DT_ENTRY1("adventura", "171031", "4ca16a77854814124e1ab8df7270ed20", 659912),
	DT_ENTRY1("ailiphilia", "220228", "d52dd34d4e48692afd7ead53ee30a026", 1317440),
	DT_ENTRY1("airport", "080204", "d3db494abc309a42b4dccfa53243a783", 234728),
	DT_ENTRY1("alabaster", "090604", "3e7913a97275d57d4f2fcec7b014b167", 3374558),
	DT_ENTRY1("alabaster", "090609", "7f664b6eef28485a2f85a1831b041246", 3132122),
	DT_ENTRY1("aliasthemagpie", "190206", "a4281a03b797582ea53aa203b1eb7236", 1875956),
	DT_ENTRY1("anatidaephobia", "170121", "a651c03db50e624fc8da5679ac731b53", 786902),
	DT_ENTRY1("anchorheaddemo", "070202", "f2e60c4c3aad4c6a2b18d4d20040ed76", 635974),
	DT_ENTRY1("anchorhead", "??????", "8913be5c1feeca879111c356daf87291", 18634158),
	DT_ENTRY1("andelmanyard", "221124", "b965b85c050000f2c32c7822e1aa3d84", 1110132),
	DT_ENTRY1("androawakefc", "120121", "64b2e5268c154130dc0d46b40c4e3e94", 884850),
	DT_ENTRY1("andromeda1983", "151208", "dcb44d52f383a4ae813145630202d49c", 9580734),
	DT_ENTRY1("andromedaapocext", "120804", "c740f7c85f5d673e0fb6b216e0433332", 7464444),
	DT_ENTRY1("andromedaascending", "130701", "5947436a0109a634506691ee744d6e3e", 1752292),
	DT_ENTRY1("andromedadream", "120716", "781b9397fdbad55e3ff5b02ce528cfbe", 2005254),
	DT_ENTRY1("archaeologicalfict", "210618", "7ad460c904ac49f6d0857ea0d10d3f30", 762222472),
	DT_ENTRY1("ariadneinaeaea", "161129", "f796d793ea7b26e21abf6478ecb841a8", 1219646),
	DT_ENTRY1("aroilingoriginal", "150327", "48719b01e0b805df27fcf1e021c6780f", 3731214),
	DT_ENTRY1("artoffugue", "100911/v1", "b570048a98acb680b8305043f1f1c866", 1596664),
	DT_ENTRY1("artoffugue", "100911/v2", "2be7f91abade14d81b85843d82d52e86", 21605450),
	DT_ENTRY1("ascensionlimb", "210110", "19a8d2f1cbd6ef612118941314ede73d", 1355276),
	DT_ENTRY1("ascentgothictower", "140831", "5fa0426759ecc243abd54f3c1c4f6d12", 2408444),
	DT_ENTRY1("atc", "??????", "312ef9bf8d06145948994ad596c57ce3", 65536),
	DT_ENTRY1("aurora", "110219", "5561b20f74d67b0e71c2b73c2ca85943", 2198110),
	DT_ENTRY1("balances_glulx", "961216", "84e0bc6295bc979754d0aa40982d1a12", 383542),
	DT_ENTRY1("baretegi", "160131", "8f1ea267fca902d07c41cb5fae8a6efb", 651420),
	DT_ENTRY1("barroombrawl_glulx", "160226", "a6b2641c76c1a28e5ff8f5188a06c63e", 637692),
	DT_ENTRY1("batman66", "220303", "a692872f5d50d2d78b937c884a9d50b7", 949954),
	DT_ENTRY1("beasttorrackmoor", "071014", "80d093ceb324b7288b6c5715f8391d3d", 579578),
	DT_ENTRY1("beingthere", "10???\?/v1", "6a7f51d6c09acca156e3ceadce7edcb9", 6005766),
	DT_ENTRY1("beyond_glulx", "100115", "64a351bc6757a58080b801a14d878fc2", 1303364),
	DT_ENTRY1("briar", "130707", "fb40823ab510ca052c8736163332ea6d", 766272),
	DT_ENTRY1("btyt", "130101", "97c6c3622d0d5a2f7a5e4f9ca521c13d", 412214),
	DT_ENTRY1("bureaucrocy_glulx", "140401", "530a9efefff27ce37d75e5dc8de8ad5d", 565522),
	DT_ENTRY1("buygold", "160302", "7db70c24b2533800187a1884ca9eacf1", 897480),
	DT_ENTRY1("candlewindless", "170828", "8decde9d474d5888d46684b8958c3a3d", 2281490),
	DT_ENTRY1("canyouescape", "131027", "330ec51e1f138a5f28df687c749ac959", 339406),
	DT_ENTRY1("castronegroblues", "130314", "fa6a51335c716de20510bd418081295b", 695186),
	DT_ENTRY1("cave", "040606", "67d3036084bb769ae925a8b6f3be84ed", 279960),
	DT_ENTRY1("checkpoint", "200506", "3c3f538628d128d32b5170e945d436ce", 966944),
	DT_ENTRY1("checkpoint", "200521", "84db33f90fd6a5cdecbcc7e2a227c3bc", 967058),
	DT_ENTRY1("checkpoint", "200914", "4e28ac9cbb61e0835644824df7c5409d", 977298),
	DT_ENTRY1("cheesedoff_glulx", "160315", "27a5288bce1b9aed55c150cba9f2e930", 666448),
	DT_ENTRY1("childrenloblolly", "220117", "1e2ebaa7bc46054d38eed6283ce71517", 824276),
	DT_ENTRY1("chipmonk", "190725", "dfd2a54378d96e2e0de203b52879501e", 647590),
	DT_ENTRY1("codetopia", "171103", "40f486f5a68fee9d99623167cf750874", 682480),
	DT_ENTRY1("colderlight", "120312", "eed41f2779bdf940f84b4e0a33036e69", 1192960),
	DT_ENTRY1("comp01tr", "012001", "1d51522ee3057a3f7206fa83c151a6de", 149760),
	DT_ENTRY1("confhist", "190603", "7409eea74565594355edb7fd6f64ee5c", 646882),
	DT_ENTRY1("cos", "030624", "21bbf38c4e358ff2fd34e3d7424c8d36", 8462908),
	DT_ENTRY1("cosmoserve_glulx", "171005", "a0e995309ba2b1bc0fda138da86ca366", 1798024),
	DT_ENTRY1("counterfeitmonkey", "160520", "24b94c1d870740880629983fc181d7b8", 14806568),
	DT_ENTRY1("counterfeitmonkey", "171224", "340232662aa8e9f4d45726e8ca7f9f5a", 12580166),
	DT_ENTRY1("counterfeitmonkey", "181204", "c3e41db7aa8642f40b157c51fa91a26b", 12348938),
	DT_ENTRY1("counterfeitmonkey", "200810", "493169aff19d6c1b42649197b7fbb6e0", 12400746),
	DT_ENTRY1("counterfeitmonkey", "210312", "dc67e9f95854b3be82ab33522c4db0e9", 11314624),
	DT_ENTRY1("countingcrabs", "090728", "ffc19674d99b4d6f530bb00287c83c7e", 1508676),
	DT_ENTRY1("crackcoldone", "170706", "c2d5bf64a0aadaead7640b5750826d55", 627136),
	DT_ENTRY1("crackcoldone", "170711", "d64bd51d8fe05dc190ac3589e11b6ea6", 627136),
	DT_ENTRY1("cragnemanor_glulx", "181208", "082f518c0120d2323ce340bef8a2d5a9", 8869096),
	DT_ENTRY1("damesdeadites", "150116", "c34b65232be2c25e558c31349e62b716", 812810),
	DT_ENTRY1("darkcarnival", "130924", "e5102c61fcb3b192c6455f214f6ca01d", 1733174),
	DT_ENTRY1("darkness_glulx", "130704", "5fd073140b9c9e0a312995e60e6761b9", 608574),
	DT_ENTRY1("darkness_glulx", "201003", "0e95840879e88523117d72ab7861f184", 1217422),
	DT_ENTRY1("deadcities", "081214", "0d276d62017b6b1b9e07b79e3fd98b5f", 1195136),
	DT_ENTRY1("deathofftc", "130930", "8e48819a77855adf1a1879b2fb2e03ab", 1211826),
	DT_ENTRY1("diaperquest", "171224", "31d355119d0aa4c719cd8093457857b3", 417101284),
	DT_ENTRY1("discovertheworld", "150731", "77b1b18260082d25f4de51318e885eaa", 17127846),
	DT_ENTRY1("donotmeddle", "160223", "7f2864618567e6d8f587ea5dc9afe879", 800588),
	DT_ENTRY1("douchebag", "150117", "20372d8a1cc2c6c8181f4ea7d6ec2a6c", 750454),
	DT_ENTRY1("dptmb2aa", "200324", "8336c30f8b28a73583b9fdd7a753ae88", 565760),
	DT_ENTRY1("dracula1_glulx", "071227", "5cb76c66a0087ac70d61e21d99cdf26a", 448324),
	DT_ENTRY1("dracula2_glulx", "080819", "8b78b92771fc0f368ebc7fd0ff8e79bb", 696250),
	DT_ENTRY1("dragondemons", "000001", "ce5c6c3e9eb5c45d83edcdba263729e9", 982528),
	DT_ENTRY1("dragon_glulx", "040211", "8daf42fd31e76a075fd2a831e6be23ac", 1625986),
	DT_ENTRY1("dragonpass", "211111", "20511b3e33d0f9a72505e42ce3708b22", 919824),
	DT_ENTRY1("drolltolltroll", "131021", "518955b338fca036fa9611c86c30f9ae", 435544),
	DT_ENTRY1("dudewheremyscapula", "160323", "95911f3a23498a24912f5cf64ddfb88d", 642518),
	DT_ENTRY1("duelspannedages", "100403", "4887e9c2e6df64ac85be17bedaed36f9", 628480),
	DT_ENTRY1("dungeonspuzzle", "180428", "6f9413eb4901da34adbdd79753094c2a", 662208),
	DT_ENTRY1("dungeontext1", "130317", "1c69e410ff3fa7c7dcf83875a7f3a963", 746466),
	DT_ENTRY1("dynapowers", "210627", "be66a1e09cb19cff49a2fa115ff4d097", 1836560),
	DT_ENTRY1("elsegar1", "200917", "76925bff593a871c2668bedafe099058", 863114),
	DT_ENTRY1("eleusinian", "201227", "325f0aad5ff624c7d4e9df5e8af39ce6", 2312476),
	DT_ENTRY1("endlesssands", "150712", "55b31591423b011bb99be2724a6bdbe9", 1005788),
	DT_ENTRY1("endling", "090217", "52500f2301277154258d2a846d45aedb", 148908),
	DT_ENTRY1("enterpriseincident", "020428", "ab2d1e4dd1ca079b502bc92b3ac4a1ac", 1067372),
	DT_ENTRY1("equivocalingr", "090509", "537279579b7c0dd2f5d8213a84209c7f", 1285236),
	DT_ENTRY1("exigentseasons", "210827", "959b453f617f5de41f5265226912236c", 1612108),
	DT_ENTRY1("exigentseasons", "220219", "7ee8c390fbddb20b72934a517e52a17e", 1616972),
	DT_ENTRY1("familiar", "200702", "4e347fdc86a979e865fa790d94bbf30a", 2294330),
	DT_ENTRY1("farmquest", "111028", "e49e02b73047fb16427c8882035a4be6", 415940),
	DT_ENTRY1("fatevanguard", "230209", "02ceac676b2aa8835e253e5a4b3ba346", 1104470),
	DT_ENTRY1("finalproject", "140517", "9ace3f9fa908a3b96a6153afa0e30720", 738248),
	DT_ENTRY1("flattenlondon", "210106", "55a9d547c9222483e72e3e76871246cf", 1790262),
	DT_ENTRY1("flexiblesurvival", "110307", "0d225782edd27fffb7ab0e423e9bad4d", 860108),
	DT_ENTRY1("flexiblesurvival", "200611", "2ee899c54cfd6c2eb8e4f8e737fa4ac9", 264677996),
	DT_ENTRY1("flexiblesurvival", "230412", "429e583862248f2bebed062d61dee351", 530020822),
	DT_ENTRY1("further_glulx", "150117", "227bf3da188ae42e43b8b88b66561252", 682770),
	DT_ENTRY1("gaiawebch12", "160104", "876c8ad8648b4035db67d09f38e9f4d4", 2458080),
	DT_ENTRY1("gatewayferrets", "191206", "0db20a85e6f044d0968dd1c6eea47c2f", 776178),
	DT_ENTRY1("genesisquest", "140319", "c51f6d78e73aa0d846a2e38d4c187cfc", 1647616),
	DT_ENTRY1("getout", "190823", "61d1b8622f47bf01027d6537dcdb256a", 641758),
	DT_ENTRY1("ghost", "210716", "8a612292dd5c09cabb64ad0cb41d842b", 794292),
	DT_ENTRY1("ghosteringtonnight", "150815", "29ee591bd93084b5a450f2324d47de3b", 1940030),
	DT_ENTRY1("glkchess", "02????", "43a14ea7a35d7944504d3017f33fd40b", 252340),
	DT_ENTRY1("glkebook", "040506/NotWorking", "1dc4d02840ee7cbf61dc359bc6a69c22", 61162),
	DT_ENTRY1("greenmountains", "110116", "4049179c3a28703705de72be734e05bc", 337868),
	DT_ENTRY1("hardpuzzle1", "151117", "ee0a36c15599629bfc4fef9d3d83f70f", 601068),
	DT_ENTRY1("hardpuzzle2", "151209", "db2880a4bf6539b30b922c83d1f35877", 626752),
	DT_ENTRY1("hardpuzzle3", "160107", "9dffb3f6fc8daf2bf4a27b4b43745b93", 796682),
	DT_ENTRY1("haroldnight2003", "141007", "ac404358f94472c2e9c8bc07596995db", 949134),
	DT_ENTRY1("herecomestreble", "160619", "573a53ce59a78c09bdfcf4f09b5cfd60", 666278),
	DT_ENTRY1("hobbit", "010911", "87212129f54fd80c1f31104eee222f2c", 183642),
	DT_ENTRY1("hobbitredux_glulx", "170425/v1", "766d0af2efc767d387ba30eeb0db81d2", 622482),
	DT_ENTRY1("hobbitredux_glulx", "170425/v2", "d0850bafc2ad394e37ee0a5d1d9c508e", 582656),
	DT_ENTRY1("houseofmemories", "200426", "bb74ef8a7831af2d99c9aaae1e02b743", 679844),
	DT_ENTRY1("houseofmystery", "180608", "97e29a1a074ab5b46f5b7edf9914a957", 1252656),
	DT_ENTRY1("houseofmystery", "180929", "4b34547babe73117e6575d559b71d1e5", 2486390),
	DT_ENTRY1("hungerdaemon","141202", "9908fa1aad277bbc968587ea388d179f", 1496460),
	DT_ENTRY1("illwind", "130515", "3904b4080d16b1e5d56caa6df64d5887", 1057002),
	DT_ENTRY1("immunesystem", "200330", "1080f88bd537e11557cc1efd43c5d4b4", 614052),
	DT_ENTRY1("ingoodcompany", "161114", "8e7d4e242f7dff5d9e9be419e2da857b", 1628586),
	DT_ENTRY1("islanddoctorwooby", "150811", "c6bf4a675821d51c1ec251ff2bfd4770", 1164724),
	DT_ENTRY1("jadeite", "201009", "1aad49311944d4e2e32b07a7d20120ab", 623962),
	DT_ENTRY1("jasonandmedea", "110307", "ce392dbb2b0c76f2c9961925dfb9229a", 646362),
	DT_ENTRY1("kingshredspatches", "090722", "87765824be7facf6400a392633f84602", 4340676),
	DT_ENTRY1("klaustrophobia", "110926", "d8751353ff883a1439c4c90cac2991fa", 3599478),
	DT_ENTRY1("koa", "000001", "f70361a47c2e9571a4fdc72ce7453197", 1085696),
	DT_ENTRY1("lastresort", "070213", "bc26a4383290d3c04657ea58841b3d91", 787200),
	DT_ENTRY1("limeergot", "151130", "1290543b3d72115bc31201ed244b5011", 1008590),
	DT_ENTRY1("limen", "210814", "d196f9bb0ea07b178b6b3fb7b5eb8649", 683000),
	DT_ENTRY1("lmstvg_glulx", "080404", "9dc7716acde7bc5bdc460f11f7ad51f9", 312920),
	DT_ENTRY1("lockeddoor10", "220202", "10002a1896d514b08416cffbf673f8c1", 989882),
	DT_ENTRY1("lockeddoor11", "220214", "d96f42aec8da45f0c194a28ce3c1892e", 1019760),
	DT_ENTRY1("lockkey", "1.12", "6f621089d571d2dada889e4367f4d20b", 269862),
	DT_ENTRY1("lonelytroll", "220501", "05b1503fa7d757ec8417a777afa9a86e", 2334570),
	DT_ENTRY1("lostislands", "110524", "9f439a77eccf4813aebebbe8093e8c57", 3145932),
	DT_ENTRY1("loveassistant", "201011", "1c219d4b89551afde0545cdfbd3d6995", 1044186),
	DT_ENTRY1("makechange", "120107", "0ee70eea03ca810bf0de3dcecfd9c741", 6456118),
	DT_ENTRY1("makingme", "220209", "96f4346cdf887a6ced4026e13ecc64ea", 2082406),
	DT_ENTRY1("maryjaneoftomorrow", "160605", "b8842f2deb9b283cccd272c0dbfc2369", 10344070),
	DT_ENTRY1("mgaeb", "110326", "9e79d4c25be31698254648579288e6dc", 676818),
	DT_ENTRY1("midnightsnack", "230101", "1c97703470406638f16874faacaa7b9c", 761726),
	DT_ENTRY1("mollybutterthieves", "160704", "e8d72805a49b658df517a91857a7feaf", 1870384),
	DT_ENTRY1("moments1", "061113", "6a7092f959c8a731cb2651860a00a4eb", 684314),
	DT_ENTRY1("moments2", "070417", "6c18999a3689234664b3daef737811ca", 13970974),
	DT_ENTRY1("monksea", "200405", "7c4240d258d9041df3ec28f1eec462e9", 680152),
	DT_ENTRY1("moonbaseindigo", "150101", "d31c005adf9f03febf5888b7fc5cf864", 1331372),
	DT_ENTRY1("mugglestudies", "120314", "0053d3c68896176ae8637752f5a855ee", 1320898),
	DT_ENTRY1("mystery", "160508", "cbd8c64ebfe2c1d7da7d3739764283ae", 1127312),
	DT_ENTRY1("narco", "1.07", "5dc6eac35d115b03f40ec61ce6e90c9d", 505840),
	DT_ENTRY1("necronskeep", "110101", "880e7b8dc89efd3a6bd8410136e9132e", 750696),
	DT_ENTRY1("necronskeep", "180120", "d533b9a3e11bd99f32ec7dcdccbae903", 749160),
	DT_ENTRY1("necronskeep", "190114", "2db002f0b695a4050249c0cd822d9c7b", 1027002),
	DT_ENTRY1("newcat", "110929", "51d263a55473d4d1ce0bceebca93a878", 795092),
	DT_ENTRY1("nightmare", "150927", "5a1800ab91062b1edf96671d4de15fb5", 646038),
	DT_ENTRY1("nssri", "180606/v1", "c8e18e3c0ea50ecab2723fa581997acc", 1376102),
	DT_ENTRY1("nssri", "180606/v2", "452fefbff5479f6aacf1b70a396c029d", 1393304),
	DT_ENTRY1("officegoose", "200101", "3def1e8a27f8d12b26d93ede124d99f7", 571742),
	DT_ENTRY1("oldfogey", "160512", "bb1cc12fcc2c0d606d237cb8bed8ef7e", 612406),
	DT_ENTRY1("oliviasorphanorium", "121118", "f0719bf95ca31e2bf964ebf11628b9ba", 1279388),
	DT_ENTRY1("onefishtwofish", "211025", "121e6cd8d048525f9a67ad7b127fd3bc", 906032),
	DT_ENTRY1("ottumwa_glulx", "021409", "1fc1da4f374493bee3a13c143beeba58", 537712),
	DT_ENTRY1("phoenixfire", "190204", "1aab4fc41f54524f98988045aa6be1df", 767690),
	DT_ENTRY1("photopia_glulx", "10274/v1", "eab3f6371531c78b2e80803e1636da7d", 627050),
	DT_ENTRY1("piedaterreblunders", "171216", "6195647baed23df20a1e16e02d046505", 1115466),
	DT_ENTRY1("pinched", "130116", "a6087088eddc38bbed669d531993c688", 1107350),
	DT_ENTRY1("pizzadelivery", "181115", "d47886a06ab5ec9ed256d56fefc75b8a", 620486),
	DT_ENTRY1("portfoliopiece", "170510", "efd348ae57ca688962388a410d273451", 636614),
	DT_ENTRY1("pytho_glulx", "020223", "3bfe1fa8468e96538b084db5c5feac55", 437408),
	DT_ENTRY1("raidersstones", "220116", "285cb947b9dbf4ad4ccd9606b4c34d44", 1485424),
	DT_ENTRY1("rar", "160423", "d45b8709505785738bb6f935c6e2cb2e", 881040),
	DT_ENTRY1("reorbushcave_glulx", "170406 Censored", "10c52283c50482a876f7fcc19d19934e", 1377424),
	DT_ENTRY1("reorbushcave_glulx", "170406 Explicit", "53ed4c8cd45aea30954e1442b169368e", 1496516),
	DT_ENTRY1("reorbushcave_glulx", "170424 Censored", "67fa7a51a11494ae58b1cd298f99c1bc", 1377276),
	DT_ENTRY1("reorbushcave_glulx", "170424 Explicit", "37883e3c63a18db1bed8bc4e81d13414", 1539506),
	DT_ENTRY1("returnstars", "211226", "c95cd6045069fd91e0114dc10e8d19de", 1186674),
	DT_ENTRY1("risorg_glulx", "060308", "86158d4fe6da56b253db871685f95c99", 545280),
	DT_ENTRY1("risorg_glulx", "171024", "3eb4e5aecb2c899bec5db264928fa252", 568576),
	DT_ENTRY1("risorg_glulx", "171114", "ba7417d44454c43a3fb9ffc31c5da0bc", 701928),
	DT_ENTRY1("robinorchid", "140602", "2561b2f1f0b9d3550e6052d6e5fa2ac3", 1210868),
	DT_ENTRY1("rocketmanfromsea", "120507", "33c7faa1be533ce760f89da13997dbbf", 2210282),
	DT_ENTRY1("roguelikegoose", "200112/gblorb", "c80283327325ce312164240d6515579f", 636244),
	DT_ENTRY1("safe_glulx", "110109", "95af9e7de6e31fdeff6bd3cf7969434d", 648720),
	DT_ENTRY1("sagebrushcactus", "100918", "de27a377b78387126b77552bccf0a085", 640246),
	DT_ENTRY1("sagesanctum", "201205", "15830904ce96b418e949f0e3b9318dec", 877568),
	DT_ENTRY1("samfortunepi", "090510", "f177d973432b7a27302f1a79c8106f72", 706326),
	DT_ENTRY1("secretletter", "150107", "152f91e432a49c3f61a8ecd7bca1d6c4", 2274048),
	DT_ENTRY1("section1awakened", "150812", "e05b999f193566771ff08679d5512143", 625112),
	DT_ENTRY1("seedscafe", "210206", "3014cd94a6505def8f3e1754b73d22f2", 652732),
	DT_ENTRY1("sensory", "000329/blb", "7432f9e1d416034acf10e8a499368b9e", 202258),
	DT_ENTRY1("sensory", "000329/ulx", "7c5a00524809e4402ddf0554394e81bc", 132608),
	DT_ENTRY1("shadowcathedral", "150228", "8da968205614859105c89e95179d268c", 2723072),
	DT_ENTRY1("shadowoper", "201007", "b19676c374b7e88ceed9b4bfdfbd1c11", 2124718),
	DT_ENTRY1("shapes", "000001", "a011827749eeef8afe6f6b8d5bfb78db", 1254912),
	DT_ENTRY1("sheephere", "160416", "1de700b758ef6f975150a6bd8926880d", 621466),
	DT_ENTRY1("signalerror", "111116", "739510541192f01467b319b70ed7bf1f", 2138394),
	DT_ENTRY1("skmmc", "150116", "46aee190f69d75592d72b1e3c573b6a8", 831452),
	DT_ENTRY1("slouchbedlam", "140613", "c3ee4e636fb1ef2a0438dc3a08d4c1eb", 982754),
	DT_ENTRY1("smittenkittens", "160816", "c3402d5d8b94675af5e3e0069366d4fd", 1240942),
	DT_ENTRY1("songmockbird", "220422", "1f0fe56c7c8bb1f87723493b60fa84a6", 1447318),
	DT_ENTRY1("spaceship", "090928", "e52390cba328a8c863150ce4651fa71f", 1429732),
	DT_ENTRY1("speedracer", "190617", "10d61f0fa2c3cbe122112f32d05e03a0", 613834),
	DT_ENTRY1("spirI7wrak", "141218", "d7e58b86d1c6e06ecdc83ebbb7b20242", 2631214),
	DT_ENTRY1("starlight_glulx", "151119", "ee4d2ed91518392981bf3cfd0fcf644d", 885152),
	DT_ENTRY1("superluminal", "160316", "7beb275a3e66b7b9840019caa3041723", 1162788),
	DT_ENTRY1("tcom", "121103 (No Gfx)", "24feef55d07cc46bcc5479ce580cbe3e", 246272),
	DT_ENTRY1("tcom", "121103", "67504ebc3d525f6a29fa800b6e12229d", 326226),
	DT_ENTRY1("terminatorchaser", "150315", "ac10ba4e7d15ebe4262cb3b9d683ef12", 1698614),
	DT_ENTRY1("theabbey", "080626", "3abcc1b85a36efb73815e1cd37143210", 645274),
	DT_ENTRY1("thebigfall", "210624", "4fcfb19c283e3860aa463dd9e3a77263", 1342530),
	DT_ENTRY1("thebigfall", "210711", "dad981d1fde0f573fd7c4b4d2652ca69", 1389634),
	DT_ENTRY1("thebigfall", "210814", "7b5f8df5b909e2ca49ab7aedf1661f56", 1389378),
	DT_ENTRY1("thebox", "170813", "91ec66de5a2b6d9e9e889835857c03e7", 1371546),
	DT_ENTRY1("thefourthriddle", "181228", "07f018d38c164615890adc44855fb15b", 1281176),
	DT_ENTRY1("thehouseoffear", "111109", "f952621c0d7d8808ec4c339f0c1b3872", 1132748),
	DT_ENTRY1("theinformal7abbrev", "150706", "79e489ca1095835e2de90b5a9ea0812c", 611172),
	DT_ENTRY1("thelaughinggnome", "160212", "c55fc26f587526618c4baf820b33f3f4", 728918),
	DT_ENTRY1("thelibrary", "141212", "a545e2f3c25715a0b693ada6407e2b54", 1201984),
	DT_ENTRY1("thelostkingdomcode", "171113", "961fcb440ebd5f7738545a2f705c9785", 747220),
	DT_ENTRY1("thelostmountain", "210228", "47ca99926b9b15ed327f07b22277d445", 1350882),
	DT_ENTRY1("themuseum", "081128", "8285ac707a9a47900c380d8af9632d1b", 3266510),
	DT_ENTRY1("theoutcasts", "170312", "234a5a35fc846aca8a4363a773d032e1", 731070),
	DT_ENTRY1("thephoenixmove", "080821/v1", "564e3f053220cb23342a6984cfcef8f9", 611890),
	DT_ENTRY1("therealmofaoria", "160412", "29f1e1568486fbcc95d06c470534c233", 4466630),
	DT_ENTRY1("therealmofaoria", "161205", "87e9e7411e535e335e580d16be255671", 6458822),
	DT_ENTRY1("theredroom", "220404", "aa04c9f178abd8261fbfe8a4f4f3740a", 617372),
	DT_ENTRY1("thesimpletale", "121216", "ad56281f7fb97718269122c014230df6", 1348802),
	DT_ENTRY1("theskycrane", "160602", "f40afca1c0252a90a614c27b39a6bd82", 626632),
	DT_ENTRY1("thespywhoatelunch", "120102", "4d6d33ff7c740020067d85cdcb46678e", 839742),
	DT_ENTRY1("thestorm", "190107", "f0a0f037fec735bdfe770f1f171e03a8", 820842),
	DT_ENTRY1("thethiefwovenwoods", "110513", "cf0cee73644411e8176c7320eb8b68d8", 388820),
	DT_ENTRY1("thetinyhouse", "091210", "5e86e6852c049ac973af5175d61b60e9", 823552),
	DT_ENTRY1("thetinyhouse", "100425", "44d3e300ced2828af1509e5019271b26", 838656),
	DT_ENTRY1("thetraintoabaddon", "141107", "55a4a454fba273067cc127c4f1a8ce3a", 848180),
	DT_ENTRY1("thiefpokemon", "140111", "2bfabf36b6171ed487858c10af0ea88d", 358392),
	DT_ENTRY1("timecapsule", "201005", "0d570e4c2cd8383fa45c99d000a40c2c", 613632),
	DT_ENTRY1("timeless", "190510", "29aeb64448b6df40399bbd41152e925a", 616386),
	DT_ENTRY1("timemachi21", "210831", "cd93405a3c77a9351bab7ccae0a6a436", 1161268),
	DT_ENTRY1("todayisthesame", "190518", "ba4478b484043d7943f834c672d5835a", 1800722),
	DT_ENTRY1("tohellinahamper", "170412", "f12baa1762e29c9528baec31347a18b0", 973550),
	DT_ENTRY1("tohellinahamper", "191217", "40cccc5fcce65c03e41dfa664487de10", 1978492),
	DT_ENTRY1("trialofthetnuop", "170813", "d8a34dc6c9b0e2d037d8cc3de006f42b", 616062),
	DT_ENTRY1("trollslayer", "151112", "fa3dee31c195732ad6a13a6e0b54d625", 920230),
	DT_ENTRY1("tryagain", "160922", "64de60e3dbc7eb492a34a0a693156659", 626116),
	DT_ENTRY1("turbochest", "201031", "b744b2b71afbf863b387bacaa2f33da4", 2210346),
	DT_ENTRY1("uie", "101122", "ed892c12a8b2d65fcda5ba6a228e04ed", 2016322),
	DT_ENTRY1("umw_glulx", "200426", "c843d3a02c0f6862401c13b45a3e85b1", 635558),
	DT_ENTRY1("uncleclemswill", "200425", "60527f2feb48e14d1fdfa7b94a8838c1", 763614),
	DT_ENTRY1("underground_glulx", "191215", "48966f89d00f4c8ce1fc2946636bd190", 3715706),
	DT_ENTRY1("unscientificfict", "090803", "de1c4a2bf4024eb4c0e5fee0e0fd4746", 679608),
	DT_ENTRY1("valleyofsteel", "140330", "88311986461cec17e776d82a5ac18416", 1853024),
	DT_ENTRY1("walking", "200626", "0a8f6530e5a619ad9e0764a645e8404d", 822256),
	DT_ENTRY1("wand", "171118", "b824638fc1d015b0837688322839ada0", 830208),
	DT_ENTRY1("winterstormdraco", "150928/v1", "b4835af78525e56420f138c2e5f6806c", 812124),
	DT_ENTRY1("wishertheurgist", "160708", "4bbe0b3a29d57d1428e6cd6cf7c97fce", 824204),
	DT_ENTRY1("wizardsniffer", "171007", "834fbcad9b93f6fab461ad4b8ff48bb5", 1240012),
	DT_ENTRY1("wof", "100515", "7de6ef1ecdec5066f65b1283b9203dc6", 10185552),
	DT_ENTRY1("wordsofpower", "021229/v1", "487ab63bce62d7fd86852b1974ba1a1c", 465306),
	DT_ENTRY1("wordsofpower", "021229/v2", "dfb5064095b4d71291b81dd281d8c520", 6240896),
	DT_ENTRY1("yourdeath4acts", "211123", "eadf48993ab9e2e8d841f60cef89d22d", 840054),
	DT_ENTRY1("zeldata", "200503", "5141a90761011ab8f70e4aa64b8b8f72", 1232604),
	DT_ENTRY1("zorkdm", "080504", "94839db9d8437e493a4b254e6e540359", 1020160),
	DT_ENTRY1("zorkdm", "190920", "4e4d79be545166fdbf5117d7c025a960", 1076736),

	// Apollo 18+20 IF Tribute Album
	DT_ENTRY0("apollo3", "33cf75f5bcc2a28af85d83e4e3f3b846", 482978),
	DT_ENTRY0("apollo10", "ac5fe600e5cf179738af4329f71304f8", 1897372),
	DT_ENTRY0("apollo12", "bfadac2b1ac0eab7187e4a5166a72798", 883926),
	DT_ENTRY0("apollo15", "c1e23a471ff61e3846b63cc21ff9edfa", 633818),
	DT_ENTRY0("apollo19", "66b599c4aecd63caa59b00bfd5101f43", 466244),
	DT_ENTRY0("apollo33", "74457b493e101e87463a0be645d2ab65", 411726),

	// IFComp 2001
	DT_ENTRY1("if01_bestof3", "010928", "53d50b3573afc12376ae5fbb342230d9", 930694),
	DT_ENTRY1("if01_carma", "010928", "cc5077c525b44748443a0e39cdc079c6", 11205418),
	DT_ENTRY1("if01_smtuc", "010928/blb", "c6e58925e082f20542bd25a2395dd00d", 1439558),
	DT_ENTRY1("if01_smtuc", "010928/ulx", "b0d09a4fa36ae1b00cccc80e4a4248d0", 194048),
	DT_ENTRY1("if01_aafn", "01???\?/NotWorking/v2", "98c22f842ffadfb08a8e2a93d32c7495", 163328),
	DT_ENTRY1("if01_aafn", "01???\?/NotWorking/v1", "07d590dc62f0be38f6f879763b6eb12c", 163072),
	DT_ENTRY1("if01_sittm", "01???\?/NotWorking/v1", "0c3d40b0340df7ff459ff7751015183a", 408576),
	DT_ENTRY1("if01_sittm", "01???\?/NotWorking/v2", "4a2ba3c1b9574b6292cbe361fc49af40", 409344),

	// IFComp 2002
	DT_ENTRY1("if02_eas2", "020925", "914e969da891835c24b3decdc6fa34c1", 842272),
	DT_ENTRY1("if02_eas2", "030112", "fc2b4a123489076679597a57d04c5acc", 845600),

	// IFComp 2004
	DT_ENTRY1("if04_eas3", "040929", "8f118c9fa10ef24a5551448d5ab2408f", 1293054),

	// IFComp 2005
	DT_ENTRY1("if05_beyond_glulx", "050930", "ad22a9d2a75f04f724ab18663399cca0", 1302846),
	DT_ENTRY1("if05_cheiron", "050929", "bca1af6d8788c178ab42883f184e7955", 2434458),

	// IFComp 2006
	DT_ENTRY1("if06_floatpoint", "060930", "1350e61da647efffc0e36f705dbc90f4", 1377946),

	// IFComp 2007
	DT_ENTRY1("if07_chineseroom", "070930", "68e11adb8574ffc4b5698499f02686d6", 988416),
	DT_ENTRY1("if07_varkana", "070930", "f92523a3a403d88aed1523de6fe12a33", 876932),
	DT_ENTRY1("if07_ferrousring", "070928", "e3763b5e021f6ee2c6e383bae2b4bc8a", 450560),
	DT_ENTRY1("if07_ferrousring", "1007276", "af11f50b1ef9ba444bd176de4ee22002", 432128),

	// IFComp 2008
	DT_ENTRY1("if08_nightfall", "080909", "1a13bdae770563bdfa09f25e40d6ea57", 1242580),
	DT_ENTRY1("if08_nightfall", "090425", "7784b0b91d27a0995cbf0f8b2ee669bf", 1339348),
	DT_ENTRY1("if08_everybodydies", "080915", "58c45023b48266cba73c776418741313", 4091836),
	DT_ENTRY1("if08_everybodydies", "081116", "2ec12958967c78e39c5ef3b9ef8fd584", 4091308),
	DT_ENTRY1("if08_crywolf", "080929", "044a5209c2ecd4401ad2f7fa0cbed256", 911818),
	DT_ENTRY1("if08_recess", "080929", "7437538b52eb78c427eb4e54e2fa1665", 712784),
	DT_ENTRY1("if08_chnlsurf", "080929", "c4b2ae121f5f0e1ae2c98c3bd4a6b3d3", 398848),
	DT_ENTRY1("if08_chnlsurf", "081122", "131aac0607a2ed5f3ae8c333bc981cd6", 409856),
	DT_ENTRY1("if08_amo", "080929", "5ab3b7c8b1446334f0703c61e4512cc4", 52505634),

	// IFComp 2009
	DT_ENTRY1("if09_rover", "090930", "5a404fb92af606a86bdae9bbf91547c1", 1739014),
	DT_ENTRY1("if09_rover", "091116", "88249e5938448be487267a4b609a45e7", 1741574),
	DT_ENTRY1("if09_brokenlegs", "090930", "4ff634e4183763bc9a34a61fad3dfd23", 1048314),
	DT_ENTRY1("if09_earlgrey", "090930", "73730db01a1bb32ffd6e2baa1877e11f", 266752),
	DT_ENTRY1("if09_resonance", "090930", "d51f6c4e99b9d283e65d836caf2f1324", 912226),
	DT_ENTRY1("if09_gis", "090929", "9370bf33a539114878b8ab95be49e38f", 667934),

	// IFComp 2010
	DT_ENTRY1("if10_aotearoa", "100928", "f62a91448362426220f811c6612f42ea", 1896012),
	DT_ENTRY1("if10_oneeyeopen", "100929", "aeb6ffc0787d36f7105a91f5a3abe444", 1779174),
	DT_ENTRY1("if10_blindhouse", "101001", "0d79dbb034056f655be3363a14d6986d", 2011166),
	DT_ENTRY1("if10_grisjaune", "100930", "849519ec9197682259d78f545fb7094f", 637952),
	DT_ENTRY1("if10_divismortis", "080126", "78e8e7f1b9350022c501eca735883d7e", 805644),
	DT_ENTRY1("if10_oxygen", "100930", "743f21619656301039d9f5113b9af50e", 1013908),
	DT_ENTRY1("if10_oxygen", "150121", "31a6aaaf3bdfde86a93583e73d50b4fb", 927386),
	DT_ENTRY1("if10_gigantomania", "100930", "4c89679dc1aa12f5d6b7e121d09e22f3", 1734624),
	DT_ENTRY1("if10_inerebus", "100930", "acda27283090aa366ef4ce99766391f0", 1986882),
	DT_ENTRY1("if10_followingstar", "034107/v1", "4f88888ed4c75099e64ef8e05bd177cc", 1170332),
	DT_ENTRY1("if10_followingstar", "034107/v2", "fec0b3c288daa456c3feff5e10bced8a", 1172892),

	// IFComp 2011
	DT_ENTRY1("if11_tacofiction", "110930", "737bc2eb191fa54c94ee4d9697d58f40", 1943184),
	DT_ENTRY1("if11_tacofiction", "111009", "c0338f36c652d48a77380c95b8eec508", 1944464),
	DT_ENTRY1("if11_tacofiction", "130422", "766be6495cb312d8270587c4d45d7e6a", 1928530),
	DT_ENTRY1("if11_six", "110930", "499fbc129639b4653928326f19e61c0a", 8819288),
	DT_ENTRY1("if11_six", "120805", "2705921eee09a568959584be1929b6b7", 8663464),
	DT_ENTRY1("if11_six", "170723", "2d1fdfe386c08fdacd620b7497bcd88f", 8661160),
	DT_ENTRY1("if11_six", "200914", "e62655c358677fd4b17e0f2ed1587a86", 8661788),
	DT_ENTRY1("if11_patanoir", "110925", "cbdfc2d2cbffdd5137afa6843666344b", 793140),
	DT_ENTRY1("if11_patanoir", "111201", "e03b27c359d71d7794ef68efe1952a72", 813876),
	DT_ENTRY1("if11_patanoir", "131204", "b328b1edff8f94715898ff0a58e845f9", 877876),
	DT_ENTRY1("if11_doctorm", "110930", "3df7bf1234c74bc035370fe8fb800707", 1289106),
	DT_ENTRY1("if11_doctorm", "120219", "7fb0073619cb071dd5d1be97285e6454", 1293208),
	DT_ENTRY1("if11_beet", "110930", "d2cecb0fff0e3234ffbfac2256c09227", 1894218),
	DT_ENTRY1("if11_kerkerkruip", "110929", "0f9169d6227e98e778247469b4666524", 1173844),
	DT_ENTRY1("if11_kerkerkruip", "120501", "b4db28a5653a63fa389e37b65b078b57", 1306720),
	DT_ENTRY1("if11_kerkerkruip", "140419", "879c34531bc7dbb66bad8fca651bc428", 22109534),
	DT_ENTRY1("if11_sentencing", "111001", "b6d55e465f163387f9ffaa753949f1c1", 983800),
	DT_ENTRY1("if11_sentencing", "111006", "4fdaaa41f63482e931296edd173f69bc", 1008888),
	DT_ENTRY1("if11_calm", "111001", "173c19aba5d36e9b4492cd9a0e089903", 1849884),
	DT_ENTRY1("if11_calm", "111201", "dba39ece18ebfbde9ebc93ccc5216fd8", 2012688),
	DT_ENTRY1("if11_thehours", "11???\?/v1", "6304dc00638793f7b25c0e6a1ec112e3", 1333980),
	DT_ENTRY1("if11_thehours", "11???\?/v2", "2d94f14e3ce959173da1ed35502f1419", 1281774),
	DT_ENTRY1("if11_deathofschlig", "110906", "1570d2c9453b549fc273a908fec6ef47", 1480090),
	DT_ENTRY1("if11_deathofschlig", "111031", "0b9b3666a0c795185724ddbd1de171dc", 1483674),
	DT_ENTRY1("if11_faninterfer", "110929", "05db96b553efcacee679cafb470b9a16", 1423366),
	DT_ENTRY1("if11_faninterfer", "111014", "7d0362957c6666d4e569d32a03d0d854", 1509382),
	DT_ENTRY1("if11_playinggames", "110929", "904e94bd17fdee40cfc0daa42325ff8a", 628188),
	DT_ENTRY1("if11_playinggames", "111127", "3e907a5feabc7ef36d019c866ec084c0", 630242),
	DT_ENTRY1("if11_awamightdread", "110930", "5f9988248a3981bed97d4c0d83371de8", 715920),
	DT_ENTRY1("if11_awamightdread", "111006", "48b3b409b565774a3cbf681225322080", 717456),
	DT_ENTRY1("if11_luster", "080126", "dc95b63ade63ddb122a3722adcfac573", 569202),

	// IFComp 2012
	DT_ENTRY1("if12_andromedaapoc", "12????", "8eb9d31ed63271fe36b9e18f979d8a87", 7116982),
	DT_ENTRY1("if12_shufflearound", "120929", "72fa2281e4636ad83666bbec74a938fd", 1634104),
	DT_ENTRY1("if12_shufflearound", "140914", "31ce78bff3833e5d2224abc4e63e6923", 3091868),
	DT_ENTRY1("if12_shufflearound", "150328", "00b2a517ec539936b96e84fabb91e5db", 3208092),
	DT_ENTRY1("if12_killerheadach", "120929", "8330f182d16e212cfcbb968f34342d4b", 1290764),
	DT_ENTRY1("if12_killerheadach", "121231", "ab18f553a035242a15f5a39f16f03173", 1382924),
	DT_ENTRY1("if12_imos", "120919", "bad26b1565e077335d319c905fbaa065", 693428),
	DT_ENTRY1("if12_imos", "121017", "c7f412b07c72ba8a6952e4ee74a37075", 716404),
	DT_ENTRY1("if12_jdal", "120930", "193ea99f5067c64447dd2c74c7e3ab9d", 761022),
	DT_ENTRY1("if12_kicker", "120929", "19d87058db3cf7503380f44929866ed5", 829156),

	// IFComp 2013
	DT_ENTRY1("if13_coloratura", "13???\?/v1", "d34ec90bdf152389d42e939a66bda0ce", 1386678),
	DT_ENTRY1("if13_coloratura", "13???\?/v2", "db4b88094929abb89fcf19ab56204b05", 1403574),
	DT_ENTRY1("if13_robinorchid", "130929", "a4574ded85c79e6e578b1a44fce302d2", 1163206),
	DT_ENTRY1("if13_robinorchid", "131027", "c9eda35f6793f96e056b49b6b2ae41d1", 1184500),
	DT_ENTRY1("if13_ooof", "130929", "5ee413df68e3e66fdf356a5df8289f85", 1391318),
	DT_ENTRY1("if13_captverdeterr", "130928", "a54ae3ab9fc03fc11294102c4281f0cf", 1549742),
	DT_ENTRY1("if13_captverdeterr", "131003", "56c78de876c57b0e02725e4d8752f139", 1549998),
	DT_ENTRY1("if13_texbonavent", "13???\?/v1", "d2bbf5ba6083323924eaf6fc7894818a", 2420258),
	DT_ENTRY1("if13_texbonavent", "13???\?/v2", "27b76acc9effd1dcf86110b74f31b61d", 2420514),
	DT_ENTRY1("if13_rosewood", "130923", "902652af146197c30760a0419bdae78e", 733488),
	DT_ENTRY1("if13_rosewood", "131116", "c766929c3cc25a13b5a60f90b618d94e", 736304),
	DT_ENTRY1("if13_awbp", "130928", "e9256df20f20e02cb43112c60cc5034d", 499962),
	DT_ENTRY1("if13_mazredugin", "130928", "0895297235681111a5fdb85bf9170613", 548588),
	DT_ENTRY1("if13_mazredugin", "131024", "510431bad4f9463b5f667cf22d414b85", 563948),
	DT_ENTRY1("if13_cardewhouse", "13????", "f99076e11ff40c0bbc9d566143d71ca9", 477126),

	// IFComp 2014
	DT_ENTRY1("if14_hungerdeamon", "140928", "fd95c400739c643d8118e8f751590c47", 1676510),
	DT_ENTRY1("if14_transparent", "?????\?/NotWorking", "bce9f905654b16d332916bb33f23d8fb", 9267518),
	DT_ENTRY1("if14_transparent", "150401", "3f4e5effb8ed8f4d0c3f277bb47ba161", 11084272),
	DT_ENTRY1("if14_transparent", "150626", "13dc495dc3ed802e663b193bd862b994", 2284454),
	DT_ENTRY1("if14_uglyoafs", "140928", "cdd8fcdc5057dedabda23df19ff5de46", 604552),
	DT_ENTRY1("if14_uglyoafs", "150403", "39ba113801d9b90d506b356f6b3ba25a", 660078),
	DT_ENTRY1("if14_jessedoorway", "140927", "f950714c28edfd199f8bc275be7e1018", 1187326),
	DT_ENTRY1("if14_andyetitmoves", "140925", "137ddc2c132b6d86232f96af7698b2f4", 941732),
	DT_ENTRY1("if14_hill160", "140911", "8ffddc4bfd6328e7beeb54ca94f725a1", 1403136),
	DT_ENTRY1("if14_arqon", "140922", "90a83d11148eda759b57f6062f4282c8", 7109254),

	// IFComp 2015
	DT_ENTRY1("if15_brainguzzlers", "150928", "620137264cd1e5b11074a50a58e8edb4", 3191138),
	DT_ENTRY1("if15_brainguzzlers", "160123", "23d22c7e8d7dff3660c436ef4951f4ae", 3210594),
	DT_ENTRY1("if15_map", "150926", "58aebee979792a1add62ce31315252f7", 2820830),
	DT_ENTRY1("if15_midswordfight", "150925", "ee7303b0385d28453761eba212026028", 1477444),
	DT_ENTRY1("if15_subrosa", "150928", "07db885f49a7c202fab2b7e882868958", 1386330),
	DT_ENTRY1("if15_subrosa", "160324", "30e7ded8624c26c04e8361d235f42c67", 1481628),
	DT_ENTRY1("if15_untriches", "150927", "543df15d2d7f67ae3e2452ac74004911", 2084218),
	DT_ENTRY1("if15_ether", "150919", "ca6d14819d43be7075029fc4d724d03b", 1019436),
	DT_ENTRY1("if15_thesueno", "150928", "4b30a5fac40aee1dc4486f4ce08f799f", 1292104),
	DT_ENTRY1("if15_shireton", "150928", "1e40822fe1bec04477c7623a63d29fe5", 1162950),
	DT_ENTRY1("if15_gotomomi", "150927", "242aaef8bfd5a1938063e326689e85d5", 1149914),
	DT_ENTRY1("if15_probcompound", "150928", "5dca1e6de048865163fae9d23dd3da1b", 785086),
	DT_ENTRY1("if15_laidoff", "150928", "2bb3c82ed6a8e7f8136fbb9b399edc34", 2479774),
	DT_ENTRY1("if15_pilgrimage", "150923", "b3c929ff383972cd42820db0207129d7", 1114454),
	DT_ENTRY1("if15_recorded", "150701", "ea4783302f6bd1a964b71e6a3e559f8a", 1933772),

	// IFComp 2016
	DT_ENTRY1("if16_colortruth", "160928", "3b0a4dc75b7a371d3d924d4064ad5fe8", 1371964),
	DT_ENTRY1("if16_colortruth", "161001", "b9ea873d69fd82d1e0535d55b4b84cac", 1372266),
	DT_ENTRY1("if16_pogomango", "160928", "c977694494e3339cd2996d5a7e4d354b", 1906710),
	DT_ENTRY1("if16_fair", "160928", "7d1e2f710cae993dccca69ce9fe71b7c", 1085358),
	DT_ENTRY1("if16_fair", "161116", "eca63537d9198a10dd6a84bf51b097b6", 1190090),
	DT_ENTRY1("if16_rockpapsciss", "160927", "6152b6bb369e9f60346c5d2160f89c50", 788182),
	DT_ENTRY1("if16_ariadne", "160928", "f17818ba3fea423d58dc6e91fd147b3e", 1218366),
	DT_ENTRY1("if16_worldstourn", "160925", "ae9803db8f5f7e457cd8fdcaa2d50b7e", 907922),
	DT_ENTRY1("if16_mirrorqueen", "160928", "005ea6a26a36ea4e51a83d5b34cd2fec", 1586550),
	DT_ENTRY1("if16_take", "160928", "db68d5e2d5e6e5d09d19ecdcccfa698a", 671300),
	DT_ENTRY1("if16_sigilreader", "160925", "be493d07c483c18a2faf0f41dfc47397", 767124),
	DT_ENTRY1("if16_ventilator", "160827", "e0c91fa164ad3487209c565928d1899a", 850360),
	DT_ENTRY1("if16_theatrepeople", "160922", "4b1eb7659590168aa22fbc75a01cb6bc", 1792644),
	DT_ENTRY1("if16_steamsacr", "160923", "bd9e96f20f3268a99ab6ea930e25b06b", 2408760),

	// IFComp 2017
	DT_ENTRY1("if17_eatme", "170928", "31fb77978d94cd6884bf9dc85177b5a0", 2569302),
	DT_ENTRY1("if17_eatme", "171013", "5e9c50e06ae1f954b9dd41abcfc0f09b", 2570070),
	DT_ENTRY1("if17_absenceoflaw", "170102", "3243039ad9fa3f51afc86bda643c7d8d", 1294084),
	DT_ENTRY1("if17_absenceoflaw", "170102", "210e6dc1d5c0fc1f4340ae9ee5bdcf4e", 1332522),
	DT_ENTRY1("if17_owlconsults", "170819", "91815dbf6dd2876e9b446c8ac640eab9", 286976),
	DT_ENTRY1("if17_owlconsults", "171124", "d1d4bd725f5e64a80f97cfc6e687a8e8", 287488),
	DT_ENTRY1("if17_beautyaustere", "170927", "3d599cee33d1f9123557b7b5a0d75769", 2073986),
	DT_ENTRY1("if17_beautyaustere", "180112", "7efa8da4a65c8e70f6783f30750f7a00", 2127234),
	DT_ENTRY1("if17_beautyaustere", "180928", "41a6d2b620c211118e2b9586fd354ea7", 2127234),
	DT_ENTRY1("if17_beautyaustere", "190516", "9176001159f15db15a3f674ddd5642f8", 2129538),
	DT_ENTRY1("if17_beautyaustere", "220220", "456b687530dd14817ac2268ddde4fd3a", 2129538),
	DT_ENTRY1("if17_1958dancing", "17????", "7267f7c66337a966ae1bb0d2add70619", 1695158),
	DT_ENTRY1("if17_futurthreads", "170927", "9fc0d3146ffc357dee47e841f372084e", 2334752),
	DT_ENTRY1("if17_thewand", "170927", "ccaf112e1bb075cf4ce15952d5c156a2", 829696),
	DT_ENTRY1("if17_wordoftheday", "170910", "67c6ae8d7a92852857c30d600765cd28", 4506714),
	DT_ENTRY1("if17_wordoftheday", "171129", "c45a9d68e80765ceff7654366fa47328", 4506970),
	DT_ENTRY1("if17_wordoftheday", "230321", "29f4dd74be498351f6d9a673075468ad", 4740364),
	DT_ENTRY1("if17_swigian", "170928", "6056cefcbb2e9e59408591108cf82c62", 785090),
	DT_ENTRY1("if17_castlethread", "170928", "c86947230252a4129bb21e2f9a29a828", 1328210),
	DT_ENTRY1("if17_rainbowbrdg", "170928", "9826f04663609f37f37c07613c532240", 626614),
	DT_ENTRY1("if17_measureless", "170928", "ecbb8fca2c880c0b50d3727a4870dae0", 980960),
	DT_ENTRY1("if17_uerifcity", "170928", "d27183094a1f4a594e4639ded7122595", 703956),
	DT_ENTRY1("if17_8shoesshelves", "170928", "09b2531f363f1a2183526194c9f7a74d", 687812),
	DT_ENTRY1("if17_escapeterra", "000001/gblorb", "7588dd6c1efdec6e94479b79c564adbc", 1350462),
	DT_ENTRY1("if17_escapeterra", "000001/ulx", "038ee5c1b681738d3164a7ea8daee4c5", 1257728),
	DT_ENTRY1("if17_hauntedp", "170928", "5912741275eaa5456bb6e4cdf7588dcb", 629774),

	// IFComp 2018
	DT_ENTRY1("if18_aliasmagpie", "180928", "3e5628127d58133a9d761068f68d878a", 1814004),
	DT_ENTRY1("if18_arithmancer", "180829", "8e1b3192eacc54bc9a4fdf4e9484f1b7", 1340328),
	DT_ENTRY1("if18_engarde", "180925/v1", "dba4583f613989b076991c5964586240", 2300176),
	DT_ENTRY1("if18_rcm301303", "18???\?/v1", "7236afe82277236b83c2af72a927000c", 744610),
	DT_ENTRY1("if18_rcm301303", "18???\?/v2", "d8a9da16c5f4001e6d0814ba7a2fbb01", 744866),
	DT_ENTRY1("if18_madametime", "180928", "365cf54b53e3308e026b19b74b239556", 1132164),
	DT_ENTRY1("if18_madametime", "190902", "b8c0d099b3da134b7163cb4b07a3268b", 1182340),
	DT_ENTRY1("if18_templeshorgil", "180924", "c48ed311aafc454a5f40c98ac54b2700", 2028796),
	DT_ENTRY1("if18_templeshorgil", "190807", "2b5e689ac5ef0a57acdda20aa4cef496", 2029052),
	DT_ENTRY1("if18_charming", "180928", "328729a90428ea9a7a25fd73117ddfa6", 1450358),
	DT_ENTRY1("if18_dynapowers", "180828", "686a7f9a6144bfcd18d9b06adcdeb14d", 1481064),
	DT_ENTRY1("if18_redragon", "180927", "7076a5b53294a53a6332c30853e55172", 1542578),
	DT_ENTRY1("if18_ailihphilia", "180928", "7f4111ca38b19cdcaeb6d4c97ab9b52c", 1187882),
	DT_ENTRY1("if18_diddlebucker", "180924", "15d47933cb104772986fb031a7d3ef3b", 2083462),
	DT_ENTRY1("if18_pegasus", "180719", "eb0a215e508e88cb652e47cf6b4480f3", 920476),
	DT_ENTRY1("if18_bordereivers", "180926", "e79c69c2ca8a5b675b7472437bef487a", 1460214),
	DT_ENTRY1("if18_bullhockey", "18???\?/v1", "91de9bbfb37af7245ec40ed4e7c3f460", 2256392),
	DT_ENTRY1("if18_bullhockey", "18???\?/v2", "c1e050f3d29b1b8b0879e09e9e73a267", 2337732),
	DT_ENTRY1("if18_bullhockey", "18???\?/v3", "546721b799eb6cf84cd7ea79b76269a5", 2565640),
	DT_ENTRY1("if18_bullhockey", "181125", "8919f32151fdc862688fb3c27aa7c46d", 2036232),
	DT_ENTRY1("if18_bullhockey", "181218", "8414393ff71519dc842cfe758ac2b0ad", 2066952),
	DT_ENTRY1("if18_bullhockey", "181220", "a2ad2f228e37ea52062e4f4f110232d3", 2065672),
	DT_ENTRY1("if18_bullhockey", "190103", "6cec5f7e1bfba0cbfa76bad81c197eba", 2065672),
	DT_ENTRY1("if18_bullhockey", "190106", "877fd221c0f6e7f7393597a8c6a4e3ca", 2065672),
	DT_ENTRY1("if18_eunice", "180928", "5f03d4d892795dfda55d72490a8d9d71", 1680256),
	DT_ENTRY1("if18_birminghamiv", "180927", "3d9aced6920925cd71510b77609448fe", 2060354),

	// IFComp 2019
	DT_ENTRY1("if19_zozzled", "190927", "61c9c0fbc3e72d063cfa3b91dcb207cf", 1142750),
	DT_ENTRY1("if19_sugarlawn", "190918", "05fedb469002274821dca9d34c1e0095", 1470216),
	DT_ENTRY1("if19_skiesabove", "190924", "4e99ccb109785b3d56815379921dffc1", 1067264),
	DT_ENTRY1("if19_skiesabove", "191120", "d2f2071d0432a657ddff53bd1a38370c", 1159352),
	DT_ENTRY1("if19_remedialwitch", "190928", "8c1ee43eb62e0a5efc2014eda4617b02", 848446),
	DT_ENTRY1("if19_frenemies", "190923", "8e2bcc981477b4a69a22f0e6c5392549", 932608),
	DT_ENTRY1("if19_underthesea", "19????", "fe5f26d808443eb8c4555bafec419f34", 1366512),
	DT_ENTRY1("if19_forthemoon", "190919", "6c3584620890d541aa5641be746ee8b4", 1428058),
	DT_ENTRY1("if19_clusterflux", "190925", "5071361ee083050c0140a0177af2b0e1", 1554906),
	DT_ENTRY1("if19_goneoutfor", "190923/v1", "1a5bf0292384322d6069ca6e0937edf8", 938958),
	DT_ENTRY1("if19_goneoutfor", "190923/v2", "baccacc67fd2575f7458ddcf406a320a", 939214),
	DT_ENTRY1("if19_4eccentrics", "190928", "bbcce2b1d753399575eef9e0a0e6a26e", 1607594),
	DT_ENTRY1("if19_hardpuzzle4", "190924", "9a51ba1efe179caf2786599add9e2909", 995024),
	DT_ENTRY1("if19_winterbreak", "190821", "da7a01866c5acecb1024aec9290fb59b", 1220128),
	DT_ENTRY1("if19_mentertain", "190928", "6ab3dbf75c2898c4302e82542692e33d", 1157598),
	DT_ENTRY1("if19_sycamorelane", "190928", "348e57968104a00e56946ed3f8585e6e", 1129550),
	DT_ENTRY1("if19_jondoe", "190928", "38e0d7e9945c3652c97a2ecb99039b90", 906054),
	DT_ENTRY1("if19_letsplay", "190916", "59a18a5e30c3dccdec37b67f6e5ef6db", 752074),
	DT_ENTRY1("if19_citizennow", "190928", "f1cb5a986120f0101c4ba0c384b4b3da", 1216474),
	DT_ENTRY1("if19_fatfair", "190928", "2e2929e471d0397576f3ad32ae2ddfea", 1374824),
	DT_ENTRY1("if19_fatfair", "191118", "006e6b5b3edf2233e020a61edf4a59ad", 1383018),
	DT_ENTRY1("if19_oceanbeach", "190927", "f3f0528c4bc862ec5df59450e77c5586", 2610492),
	DT_ENTRY1("if19_randomescape", "190828", "8d1217f45de1f8d1958d0468fe2ad8ea", 746496),
	DT_ENTRY1("if19_vegibalisle", "19????", "cb2ba74dd9cdbf7020d1a72ae0dd71b4", 700672),

	// IFComp 2020
	DT_ENTRY1("if20_vainempires", "200928", "4b28e67ecabbb8e6db40e5e99f5e8140", 3914438),
	DT_ENTRY1("if20_vainempires", "210223", "adab9cfa61fbeb284fdeb6779f014028", 3920070),
	DT_ENTRY1("if20_magpietrain", "200924", "19d8fc67b3dfbb7a1dc88fa02d26e6d4", 2315066),
	DT_ENTRY1("if20_magpietrain", "201106", "a9203d02e6439bea926a73686bec0466", 2318650),
	DT_ENTRY1("if20_eleusinian", "200926", "4ca599f36ae1559356bb224879213382", 2265116),
	DT_ENTRY1("if20_aropeofchalk", "200926", "26dfd5161d72ec2a9e88b93c74e79e36", 1653800),
	DT_ENTRY1("if20_aropeofchalk", "221202", "a90192092cb1616b22b6af769811c851", 1707862),
	DT_ENTRY1("if20_stuffoflegend", "200926", "447ea6caf1c51226b3f6a54d857b76b6", 1536382),
	DT_ENTRY1("if20_stuffoflegend", "201006", "9dbf623f1bd82be91dc728024600fe91", 1534576),
	DT_ENTRY1("if20_flattenlondon", "200926", "f3fa437bc2e99ceb97b43c5617f0d4db", 1785910),
	DT_ENTRY1("if20_vampireltd", "200926", "7d5d5a10930db0adfcadf79860f3223f", 829986),
	DT_ENTRY1("if20_vampireltd", "210129", "8a879f2a2757822b03c3d91a3289a6d5", 889540),
	DT_ENTRY1("if20_alone", "200927", "8ceba612963681d5c8a61cead9c8f1f0", 1078102),
	DT_ENTRY1("if20_alone", "201006", "891fb305a00a9a8f957f01629f59bfe5", 1093464),
	DT_ENTRY1("if20_sagesanctum", "200922", "bd21d0b625abb8bab93e83cc93fd35ee", 876800),
	DT_ENTRY1("if20_shadowoper", "200929", "3bb8da82f1d81e35ee152d5ecd6ba3e4", 1140422),
	DT_ENTRY1("if20_ascensionlimb", "200927", "30aa45bec407ff833a56e552b451ff95", 1160460),
	DT_ENTRY1("if20_ferrymansgate", "200928", "276ff9f09734b59364199fc948f9e221", 2655820),
	DT_ENTRY1("if20_ferrymansgate", "201006", "ed9aca691b1ce35f78c13fbd75077ec4", 2657868),
	DT_ENTRY1("if20_academregular", "200928", "37f8d2484cf254f7836fd938b37584b6", 931046),
	DT_ENTRY1("if20_seasonapocal", "200710", "5e951b117302169cdb77e832115937f0", 2207454),
	DT_ENTRY1("if20_loveassistant", "200923", "16931f135f38efaee72dac89a7c9ae27", 1051098),
	DT_ENTRY1("if20_turbochest", "200928", "420f40b233e4b221e6fff2bec050dc23", 2091802),
	DT_ENTRY1("if20_foraplace", "200928", "0a27fe6717a60a99e7130ea54354eaf5", 1476540),
	DT_ENTRY1("if20_foraplace", "201014", "f7196abf00de2d25c9d398756e5d92e5", 1477052),
	DT_ENTRY1("if20_timmott", "200928", "8d720c498a6a7115628f70b61eb413c6", 2885100),
	DT_ENTRY1("if20_timmott", "201024", "5952d3a8dcb659269791ceecef106d95", 2887404),
	DT_ENTRY1("if20_desolation", "20???\?/v1", "6a9f300f70d246e52dafbc65430e6cad", 675208),
	DT_ENTRY1("if20_desolation", "20???\?/v2", "cd2d1dda98cefc25b351f8330563996a", 702856),
	DT_ENTRY1("if20_waywardstory", "200929", "4fe03ab93289d4d8d53b04983010f529", 929536),
	DT_ENTRY1("if20_waywardstory", "201005", "fd731a09e32f85a38ea3ae61e153d0ed", 929792),
	DT_ENTRY1("if20_underthey", "200928", "bd069d2e3e841cea7a7d2694681b548a", 1070370),
	DT_ENTRY1("if20_standshoulder", "200925", "78cb38272e79595781f5e1be65171a75", 836802),
	DT_ENTRY1("if20_lasthouse", "200928", "94ca1a21467c2b2f07e9cf6afeeb818a", 933328),
	DT_ENTRY1("if20_lasthouse", "201013", "78cb28bc7b4a3c4d006fa4ccad759a58", 933584),

	// IFComp 2021
	DT_ENTRY1("if21_comehouse", "210813", "6e1c6b40d1ab32ffa2985ae457a8f291", 1526508),
	DT_ENTRY1("if21_comehouse", "211213", "27662487116ce47c2b0112faebae1bb6", 1539308),
	DT_ENTRY1("if21_drhorror", "21???\?/v1", "0332a2a9e94b296272d1333a8f4c008b", 2911894),
	DT_ENTRY1("if21_drhorror", "21???\?/v2", "f36db5fb5f4249d413b268cb9e20074c", 2914710),
	DT_ENTRY1("if21_songmockbird", "210821", "0f78c0017d367a5173bd3a912a272a0d", 1445526),
	DT_ENTRY1("if21_ghostguessed", "210928", "8492b4552449ae1b9bf6be977032ba6d", 1367846),
	DT_ENTRY1("if21_ghostguessed", "211117", "7b2920b6c3222e184037e2d1fdc166e8", 1368358),
	DT_ENTRY1("if21_sting", "210902", "3c8b68e4d4e928ec6d33a954dff7c874", 1112124),
	DT_ENTRY1("if21_sting", "211001", "38c227e4305d9e2c616956dc3c90da20", 1112124),
	DT_ENTRY1("if21_sting", "211211", "8e17a75bfadf744e64a06534d1fe4d83", 1152828),
	DT_ENTRY1("if21_findinglight", "210927", "7681b3aa69ac3d21b07c346e04fd2b30", 1618336),
	DT_ENTRY1("if21_remarkegg", "210922", "fe7eb5e04ebd5a3d69f244939790892d", 661504),
	DT_ENTRY1("if21_closure", "210928", "0b206eda8c05164d55fe496fbfd9aeab", 777182),
	DT_ENTRY1("if21_aardvarkhype", "210928", "02458faaa0c25d84f7d3930d98192c98", 1252508),
	DT_ENTRY1("if21_hercules", "210927", "ae27b0fff3f62cc9fcb6d63bff839164", 1395526),
	DT_ENTRY1("if21_hercules", "211121", "8883c8f48d19165bf53d9a4216240f1e", 1426246),
	DT_ENTRY1("if21_unfortunate", "210930", "dbbfa8f70df0aabbed0266b6c6e98ebc", 1276776),
	DT_ENTRY1("if21_planewalker", "210814", "c959282d031379171859f92c2c079f3f", 827974),

	// IFComp 2022
	DT_ENTRY1("if22_sector471", "220923", "890e7379e7aab307a06ec6844f05e498", 723712),
	DT_ENTRY1("if22_awalkaround", "220928", "4f1f15ba4754277db25dc11e309d5a26", 810416),
	DT_ENTRY1("if22_arborea", "220922", "287dc941bbce7b554210fa2c7e9ca3ee", 2058812),
	DT_ENTRY1("if22_crash", "220927", "82008663b8d3e7da04debed8b5380150", 1349544),
	DT_ENTRY1("if22_crash", "221124", "405241206e6368228c33ab826dd87832", 1391784),
	DT_ENTRY1("if22_amatter", "220927", "3d0db952acc0113e73076d332689f746", 5244484),
	DT_ENTRY1("if22_amatter", "221218", "3a141c1fffed5dc6195f9a517fa1d628", 7509290),
	DT_ENTRY1("if22_whoshotgum", "220928", "a83eda2d1f7f4c560e1bb78f728aac85", 703960),
	DT_ENTRY1("if22_youmaynotesc", "220927", "cf53ee039af2602b753b4dc6319f79af", 1449774),
	DT_ENTRY1("if22_lastchristmas", "220927", "cd356cee811ccf3e8582f2ed9e383fc9", 1484292),
	DT_ENTRY1("if22_hiddentomb", "220917", "822c6b245c11a5c54aa11fb1b0f2f388", 710058),
	DT_ENTRY1("if22_towerplargh", "220816", "95106d81bcf4e5ee15c2f9f5bfd4c1b4", 567358),

	// The Mystery House Taken Over Project
	DT_ENTRY1("mhto", "050316", "8eae736e39e9f816e0467c819a61f686", 281250),
	DT_ENTRY1("mhto3flippydisk", "050315", "56ff5a9955bd1f2a351016a30cf9bc80", 3006656),
	DT_ENTRY1("mhto4cadre", "05????", "6b328a9e752ab53d8ef52d0337733eec", 286660),
	DT_ENTRYL1("mhto5dhan", Common::ES_ESP, "050308", "56fa7732356783f579b26a8f62126f16", 372860),
	DT_ENTRY1("mhto6mg", "050315", "2ed66f11cc975090ff42085f92e5fd37", 613362),
	DT_ENTRY1("mhto7ll", "050228", "5f2363f67963041029051439bd630508", 2459450),
	DT_ENTRY1("mhto8rettberg", "050307", "1f48a475752dcb0ae4187f1cffde0dc6", 976736),

	// Cover Stories Game-Jam
	DT_ENTRY1("cs_spelunking", "120611", "f229157493e7fa62be56872cac3f9347", 846858),
	DT_ENTRY1("cs_oliviaorph", "120610", "b0828ab288a58329017f5c94284dd8c9", 1239964),

	// Ectocomp 2013
	DT_ENTRY1("ec13_voodooyoudo", "131029", "eb78be063dc384b53505ad3344a46635", 508604),
	DT_ENTRY1("ec13_jack", "131026", "257116a78bf705386850779a53c8155d", 622700),

	// Ectocomp 2014
	DT_ENTRY1("ec14_lisey", "141031", "4c66d4423a73a62599be37a32c899969", 622322),
	DT_ENTRY1("ec14_firstperson", "141030", "fc7012af57bc2339648902157cfc49ae", 628678),
	DT_ENTRY1("ec14_voodooyoudo2", "141028", "370c12ee14c2ee09178a291ba0fc5f33", 724162),
	DT_ENTRY1("ec14_carriageret", "141030", "c9fcca14c000c865ac94c9aaeba779cf", 769122),

	// Ectocomp 2015 - La Petite Mort
	DT_ENTRY1("ec15_hallowdance", "151028", "fc2f2a6ddaa1930f68e624d82e8abb82", 638150),

	// Ectocomp 2016 - La Petite Mort
	DT_ENTRY1("ec16_low", "161016", "d2492f1e0e495259f2a489d591cafcbc", 659134),
	DT_ENTRY1("ec16_becausemine", "161019", "643df12ae55ed54c9c1172753fc71d52", 648134),
	DT_ENTRY1("ec16_toiletomega", "161029", "474710731fffa9d5d3cdee7924265169", 626442),

	// Ectocomp 2016 - Le Grand Guignol
	DT_ENTRY1("ec16_psychomanteum", "161029", "e88338c8e1ace3391eee928f352c83ad", 3059478),

	// Ectocomp 2017 - La Petite Mort
	DT_ENTRY1("ec17_bloodyraoul", "171025", "52fe19e5bbf8787d1e29b6f804d42961", 953676),
	DT_ENTRY1("ec17_somethinnight", "171031", "b515eac0d1e33e723fabc43f7f58e478", 618442),

	// Ectocomp 2018 - La Petite Mort
	DT_ENTRY1("ec18_wakeup_glulx", "181005/gblorb", "38f9c5f1d8c2177f3d8cd53d4d7f76b0", 631666),
	DT_ENTRY1("ec18_wakeup_glulx", "181006/ulx", "b3ba90f9f6f34d32cffb623400ad9f26", 543744),

	// Ectocomp 2018 - Le Grand Guignol
	DT_ENTRY1("ec18_tfcb1fealglas", "181031", "f65f9374bf752e6a6fa78e5ee8c80429", 933586),
	DT_ENTRY1("ec18_plshel_glulx", "180923/gblorb", "8512859035c601596240128b81f1f10e", 627644),
	DT_ENTRY1("ec18_plshel_glulx", "180923/ulx", "7b10ac4e94de791c853c15b4cc12b7a9", 553472),

	// Ectocomp 2019 - Le Grand Guignol
	DT_ENTRY1("ec19_tfcb2durango", "191031", "663cf4e11efd46a784bb673aa053e9d9", 941018),
	DT_ENTRY1("ec19_whenhedied", "191031", "f7e7a3624bcb6ba5fdc3188d0cb103e9", 749584),

	// Ectocomp 2020 - La Petite Mort
	DT_ENTRY1("ec20_pilgrim", "201030", "7ad8aacc6fb4fc9c3d5288fcdf2715ea", 640728),
	DT_ENTRY1("ec20_lastday", "201028", "c644f6a6b509963ce88c522287ed862b", 669042),

	// Ectocomp 2020 - Le Grand Guignol
	DT_ENTRY1("ec20_tfcb3vultrine", "201031/v1", "ce63638be95c25549540db4e81367a79", 1419074),
	DT_ENTRY1("ec20_tfcb3vultrine", "201031/v2", "16c92b75ca2659eb27d8ee57fd952fa3", 1419074),
	DT_ENTRY1("ec20_ritussacri", "201031", "5516a9c0555f4aca02b5cb1a4236a45a", 587266),

	// Ectocomp 2021 - La Petite Mort
	DT_ENTRY1("ec21_hauntedmustac", "211030", "1f46ec76211eea399473ea9c649eddb0", 2279398),
	DT_ENTRY1("ec21_yourdeath2act", "211023", "83c184bac77795761602cc8ae55902a5", 642982),

	// Ectocomp 2021 - Le Grand Guignol
	DT_ENTRY1("ec21_thelookout", "211107", "b8617c8ab3b152a4e08622b72d160003", 745114),
	DT_ENTRY1("ec21_thelookout", "211114", "b40a96283a8d12b16243cadbf506f691", 745114),
	DT_ENTRY1("ec21_thecrew", "211102", "b30f0d790b8dd11e9f16fbbe34a56cb3", 919628),
	DT_ENTRY1("ec21_jack", "211026", "bebb45d2b6e1757b572ace1859a33a51", 924338),

	// Ectocomp 2022 - La Petite Mort
	DT_ENTRY1("ec22_tortortortort", "221121", "6690eccf20e3e43274016b736aa88152", 639206),
	DT_ENTRY1("ec22_kidnapfairy", "221014", "d6dd9a8f378ad77dd1145facf92d87ae", 980826),

	// Ectocomp 2022 - Le Grand Guignol
	DT_ENTRY1("ec22_thespectators", "221030", "02fb6521d6fa85a5692d886b16282350", 1568488),
	DT_ENTRY1("ec22_thespectators", "221107", "d58bafa06a075bb32632746c87c5147c", 1568488),
	DT_ENTRY1("ec22_apumpkin", "221103", "121643ae56df322d6c7f1d7ca53cdecb", 673554),
	DT_ENTRY1("ec22_oldhhouse", "221030", "bec430e7aad958baac37ba72b5a81c82", 849262),
	DT_ENTRY1("ec22_nowheresville", "221030", "86ecbe2738622a5a162a68704a4a3977", 1471426),

	// HighlandComp
	DT_ENTRY1("hc_catchhaggid", "010203", "f6bc94801f2a9c9c59644f21e33de610", 113664),

	// Imaginary Games From Imaginary Universes Jam
	DT_ENTRY1("ig_dreamrevised", "010203", "3e175099a1e80abef10bf72610feafe2", 1914090),
	DT_ENTRY1("ig_gaiasweb", "160104", "cc4c71a9745c994f11c3c61c02107e17", 1416212),
	DT_ENTRY1("ig_unrealcity", "160208", "00ed2d561cb3b4f1a737a9e1989ccba0", 759746),

	// IntroComp 2002
	DT_ENTRY1("ic02_jingo", "020319", "e5cbcd323604e8c567fb14005743b215", 124160),
	DT_ENTRY1("ic02_genie", "020317", "49188c3f73495f2d7cf81e4ec00aa217", 103936),

	// IntroComp 2004
	DT_ENTRY1("ic04_gauss", "040718", "a88db0c1568fb173460dbad8b567cf14", 128256),

	// IntroComp 2007
	DT_ENTRY1("ic07_3princes", "070804", "f26a5b23a9d1001d1527209f88228dad", 318864),

	// IntroComp 2008
	DT_ENTRY1("ic08_phoenixland", "08????", "d0c50e5cff1098009fbb9f893e7dc75e", 890884),

	// IntroComp 2010
	DT_ENTRY1("ic10_fangvsclaw", "100703", "a62db6db8270b794eb3f5c75d5a31fc1", 604086),

	// IntroComp 2011
	DT_ENTRY1("ic11_chunkyblues", "110630", "9d0fc0586df10d7e85c4fcd2fcca0553", 1255154),
	DT_ENTRY1("ic11_seasons", "110630", "4828e0affb26575eb5e5eda9f5025c37", 818432),
	DT_ENTRY1("ic11_zmatter", "110629", "dec030a1dce71a43a46fd96c4fac2d7b", 1516978),

	// IntroComp 2012
	DT_ENTRY1("ic12_compliance", "120716", "44b10a0d7b8e38713df34a09ca7d5373", 27561388),
	DT_ENTRY1("ic12_belief", "120716", "3c9b393c3df22cf321800a7b41938f06", 513364),
	DT_ENTRY1("ic12_genesis", "120714", "f96244e1010f16d831caf0e3f34f0546", 2383766),

	// IntroComp 2013
	DT_ENTRY1("ic13_blplains", "130715", "c8d41234000af17815a01a370ccd177f", 404432),
	DT_ENTRY1("ic13_akkoteaque", "13????", "6a4c45084a30f777453eb3a7b6fb82a7", 1444292),
	DT_ENTRY1("ic13_vanishconjur", "130709", "f8d195d882b2394950aef07b7ec75814", 830048),
	DT_ENTRY1("ic13_first", "130714", "195bff59343b0c03f5fdd91ec7d079f0", 352156),
	DT_ENTRY1("ic13_what1984", "130614", "28d374899f30b44b2e911d4e0f0b5543", 441004),

	// IntroComp 2014
	DT_ENTRY1("ic14_cuckoldsegg", "140720", "0158803bd3a4f03ab83443eb5ef14944", 734886),
	DT_ENTRY1("ic14_scrollthief", "140720", "cbaae8f12d3603e58f22fc67cd0a3a39", 1454668),
	DT_ENTRY1("ic14_scrollthief", "150729", "9c26a3dc0f4fb681bf79f681e63c0d76", 2367848),
	DT_ENTRY1("ic14_scrollthief", "160701", "4ba7874db08126bb177afd511ab16542", 2602042),
	DT_ENTRY1("ic14_terribledoubt", "140720", "bd83d2992dcf3a85347126c154fd64c8", 1467868),
	DT_ENTRY1("ic14_hornetsnest", "140720", "7a049c3232299b59f74c96418957eef1", 781682),

	// IntroComp 2015
	DT_ENTRY1("ic15_beyondivision", "15????", "fa3afc16485d3e6c24548931e24064d3", 895282),
	DT_ENTRY1("ic15_meld", "150730", "4556d3f39e2ee0af6dc01725a5cad243", 535492),
	DT_ENTRY1("ic15_voltagecafe", "150801", "c867d05bba89c06e5d2d64210fb79306", 610686),

	// IntroComp 2016
	DT_ENTRY1("ic16_spellbound", "160728", "c37e0e19a2fe74edc2d1df90bc97e132", 1061586),
	DT_ENTRY1("ic16_somexceptions", "160730", "becbb4a01a863577dc2532016b5ff223", 311296),

	// IntroComp 2017
	DT_ENTRY1("ic17_sherlockind", "170731", "d4900a94a49582feaf144bed0ef3b80c", 816850),
	DT_ENTRY1("ic17_onnakabuki", "17????", "1a0de9433b3daf3cd0f97c782580bbb9", 816076),
	DT_ENTRY1("ic17_adameveprj", "170731", "3c3476810dc8f8379e2124913cf99bf7", 709584),
	DT_ENTRY1("ic17_duckmans", "170728", "0b4c1dd28c65965781503f0ad6ae45d8", 672962),
	DT_ENTRY1("ic17_prizon", "170705", "e7741df7fb02064b8549ec08115c654a", 561920),

	// IntroComp 2018
	DT_ENTRY1("ic18_introimplarc", "180721", "e4ff7ddde364943af01cc3789c753dea", 987828),

	// IntroComp 2019
	DT_ENTRY1("ic19_intodevilmus", "190801", "a71122e9ec48267d764bf4c3a66ff9db", 840916),
	DT_ENTRY1("ic19_imprisoned", "190714", "e8973c8981920f0c4c650e8d3a95ef41", 1351324),

	// IntroComp 2020
	DT_ENTRY1("ic20_foreignsoil", "200801", "3e1000f0724582ff56ee54254fe2e817", 957330),
	DT_ENTRY1("ic20_foolrescue", "20????", "c520f331e64f7f2a5a666d7c33655aeb", 985114),
	DT_ENTRY1("ic20_theinterview", "200706", "2888fdbce5dc116284fc9e93343eeebc", 933494),

	// IF Library Competition 2003
	DT_ENTRY1("lc_lazygods", "020312", "31df98f26852782d4a23d319bb0d6f44", 187136),

	// Metafilter IF Competition 2009
	DT_ENTRY1("me09_questionable", "09????", "7fc1b036d75faf2961b67ec7bd86d157", 213104),

	// 9th Annual New Year's Mincomp
	DT_ENTRY1("ny09_candleflames", "160118", "0fa73dc37cdd6334f0bd4f335c462f67", 1921824),
	DT_ENTRY1("ny09_trolleyprob", "160102", "16a9170628ca5832ef3f6c27016c15d0", 708312),
	DT_ENTRY1("ny09_stayingput", "151231", "9da001fcc0e0b6f21e4b4a9b05bce1e8", 680946),
	DT_ENTRY1("ny09_mhairiesioux", "160102", "47aeddc1af77820afe1b1a4a4836c210", 649062),
	DT_ENTRY1("ny09_daytimestood", "16????", "ce87f48605caf12bac38428f3463f735", 678868),

	// 10th Annual New Year's Mincomp
	DT_ENTRY1("ny10_anatidaephob", "170108", "9ae9476879c988206356fd9fb623b99a", 773846),
	DT_ENTRY1("ny10_dayishootalex", "170108", "8d8977c935387f825ac195374034d24b", 707278),
	DT_ENTRY1("ny10_thehorste", "170101", "c7f4f55ebd395353ef960ae4e8b482f0", 635842),
	DT_ENTRY1("ny10_yaminabe", "170102", "3e2a7cdb37ee2fe549ff0d112034786b", 612290),

	// 11th Annual New Year's Mincomp
	DT_ENTRY1("ny11_finishyourfoe", "180104", "52638708780503016f3f56209d3d49f9", 738212),
	DT_ENTRY1("ny11_quickfire", "180111", "067cdba3f209386bbac3ab3dc371f1e1", 810696),
	DT_ENTRY1("ny11_red", "180101", "74169c3bb55fafa74d67949759bd343c", 831422),
	DT_ENTRY1("ny11_thedaygotpet", "180105", "d67483a690bcf57f04a0aa6089feb198", 664528),

	// One Room Game Competition 2006
	DT_ENTRYL1("1r06_formamentis", Common::IT_ITA, "060515", "73ae4e5e75165d763b7a5cee0a0f8c99", 294244),

	// One Room Game Competition 2007
	DT_ENTRYL1("1r07_notteprima", Common::IT_ITA, "071106", "ae2c22d0062660f2ad2c0b691a0ca09b", 1397352),

	// Shufflecomp Competition 2014
	DT_ENTRY1("sh14_1942", "140513", "1294db6a7cee749ac4dc193af33cb363", 794454),
	DT_ENTRY1("sh14_lightmyway", "140512", "b594c283a4ddcb111d825781961fbdfa", 11436804),
	DT_ENTRY1("sh14_8mileshigh", "140512", "ee38379f28afaeffa027e964e9d45c1f", 463942),
	DT_ENTRY1("sh14_fallshelter", "140511", "f125292e2401c1e140e067b649a27719", 749956),
	DT_ENTRY1("sh14_groovebilly", "140511/v1", "3ff5d7194bfafa9f0faf638e79f0d079", 853042),
	DT_ENTRY1("sh14_groovebilly", "140511/v2", "bfe3b34019ab6d2df0b9a5b793414170", 853042),
	DT_ENTRY1("sh14_invisiparties", "140513", "2ce7e978f20fd7355ece095b5cac975b", 582856),
	DT_ENTRY1("sh14_sequitur", "140813", "c7e384b1938915f17cc0b7d50f41d235", 1642480),
	DT_ENTRY1("sh14_sparkle", "140512", "106fdc837247efab6a5ab685bd1182c5", 915946),

	// ShuffleComp: Disc 2 Competition
	DT_ENTRY1("shd_comrade", "150506", "9806e5d0e7bee858107cee249d5cce7c", 728512),
	DT_ENTRY1("shd_bythelake", "150506", "8aefa40db437e93703240f6e8cc97497", 567808),
	DT_ENTRY1("shd_mollybutter", "150507", "f3bf0027b9bd50c4735588ef365f6652", 1210952),
	DT_ENTRY1("shd_landunderwater", "150505", "f04ff26834a981b8bcc67691b1b6fe04", 935306),

	// SpeedIF -1 Competition
	DT_ENTRY1("sif_newgrant", "011118", "4b2822f1e3313e6291dd10835e7a743c", 191744),

	// SpeedIF 11th Anniversary Competition
	DT_ENTRY1("sif_marvex", "090901", "658bb7a355cf36d4ef4dd7709a264fdf", 522676),

	// SpeedIF 18th Anniversary Competition
	DT_ENTRY1("sif_interpizza", "161016", "ed2618021a59ec33d964e62045b3cca1", 641494),

	// SpeedIF New Year's Speed Competition 2011
	DT_ENTRY1("sif_dansenocturne", "11???\?/v1", "d45cd4146c99974b1f5c6f2e9d403843", 476192),
	DT_ENTRY1("sif_dansenocturne", "11???\?/v2", "9a60eadb746e34c7364cbe423b712e0c", 810990),

	// SpeedIF New Year's Speed Competition 2014
	DT_ENTRY1("sif_dayofthequeen", "150103", "bcfc846828da6ac07701a11ab6321878", 728576),

	// SpeedIF Potato Peeler Competition
	DT_ENTRY1("sif_deadmanhug", "170706", "1ccc2310b076781be2bf248b1c35f3f3", 632528),
	DT_ENTRY1("sif_4dayssummer", "170707", "44b242842bb5ad7a334c0f3240bad5c7", 576886),
	DT_ENTRY1("sif_peelinglucky", "170708/v1", "a07594765ba82779bf60fc363986ff6d", 620744),
	DT_ENTRY1("sif_peelinglucky", "170708/v2", "12326b7fac754543b396a3f0acb4b70d", 621768),

	// SpeedIF Thanksgiving Competition
	DT_ENTRY1("sif_yoursisearth", "111127", "e92c6480d00c71a255b6b16db5538280", 605638),

	// SpeedIF XYZZY Competition
	DT_ENTRY1("sif_zigzy", "010311", "d46f2947830c74ae3518c8373aeb2e70", 135936),

	// SpeedIF Bouchercomp Competition
	DT_ENTRY1("sif_lowellprison", "080527", "6e4a01ed4e6eb4b83ac484335699c701", 459382),

	// Toaster Competition
	DT_ENTRY1("toa_youretoast", "000823", "26310e407b7e9a793c732f76ca472009", 142848),

	// Spring Thing 2008
	DT_ENTRY1("stc08_bluelacuna", "080402", "11607d5bb97efa405162821cdbe66dbb", 2995596),
	DT_ENTRY1("stc08_bluelacuna", "090304", "86c24b7fa879780038056d5e9a084a28", 5649260),
	DT_ENTRY1("stc08_bluelacuna", "100717", "8a2cd2e898f7375d39393b56ed64c5dd", 5673294),

	// Spring Thing 2009
	DT_ENTRY1("stc09_flustereduck", "090124", "3b317a684994410273446057595edf3c", 1075712),

	// Spring Thing 2011
	DT_ENTRY1("stc11_lostislands", "110403", "e9f66542a950e1d93343852ab523ce1b", 3659212),
	DT_ENTRY1("stc11_bonehead", "110404", "e0f2d0e1421e5d082660a80c8922606d", 1789404),
	DT_ENTRY1("stc11_bonehead", "120229", "34563c2af093239b5a908a64031eedac", 1804252),
	DT_ENTRY1("stc11_wetlands", "110404", "7f8454117437a0c8520e771f3d03bd29", 1439694),
	DT_ENTRY1("stc11_stiffymakane", "11????", "f978ca1dafb3e44f1b29bd26527f342c", 2486436),
	DT_ENTRY1("stc11_promise", "11????", "1a5e93399abf732b9b05766f555b8547", 4318236),
	DT_ENTRY1("stc11_halloweve", "110403", "7bd5ec4bf5bffe607af9a9ff517aa1e0", 940894),

	// Spring Thing 2012
	DT_ENTRY1("stc12_eggnewbie", "12????", "725f4d7c8083de053dd55e0569de9b0d", 979332),

	// Spring Thing 2013
	DT_ENTRY1("stc13_rollingorig", "130402", "73ddd7215f69a2385c6ed3f455ed8e53", 1572638),

	// Spring Thing 2014
	DT_ENTRY1("stc14_bearcreek", "14????", "a4abc8052666e8cbacb934e1448050fa", 1138076),
	DT_ENTRY1("stc14_bibliophile", "140408", "c49f829c2e8c2f90391d7ff379c52845", 1511832),

	// Spring Thing 2015n - Main Festival
	DT_ENTRY1("stc15_tobysnose", "150503", "94630602381aca7adb029f6c409122cc", 1917434),

	// Spring Thing 2016 - Back Garden
	DT_ENTRY1("stc16_deadmanshill", "160401", "e09b0954d1ab075242e421397cca4945", 1076730),
	DT_ENTRY1("stc16_foofoo", "16????", "5421140238ef2103a53ef155fe26c1a1", 1173976),
	DT_ENTRY1("stc16_3cardtrick", "160507", "60f37f9215f1c1fe0fbc9d247e0ef55a", 1327966),

	// Spring Thing 2017 - Main Festival
	DT_ENTRY1("stc17_bobbybonnie", "170508", "7d4b62541c7a601c11ebf9cba173a376", 4585366),

	// Spring Thing 2017 - Back Garden
	DT_ENTRY1("stc17_afotwoaae", "170405", "b108df8afa6bad6717cdc248abd2a238", 4936626),
	DT_ENTRY1("stc17_buckthepast", "170508", "6f150c9d8b64401d6686ab670c67ec26", 698826),
	DT_ENTRY1("stc17_weightsoul", "170329", "017f58b757ac63c4129c445069c0d19b", 3987042),

	// Spring Thing 2018 - Main Festival
	DT_ENTRY1("stc18_illum", "180228", "f6babe0280f8334036751a2a943de1a9", 7233750),
	DT_ENTRY1("stc18_illum", "181001", "c2b6e0ab32c4035a903926448332e3a9", 7241942),
	DT_ENTRY1("stc18_illum", "190221", "5220fec6734d7320cbe989ae8f12c2e0", 7242454),
	DT_ENTRY1("stc18_bunchkeys", "180412", "71f0e4edb9cc765d6265f7cd4ab49baa", 2739456),
	DT_ENTRY1("stc18_sherlockind", "180324", "58e278728ddc16da04ff3d7cd4fadab9", 1216728),

	// Spring Thing 2019 - Main Festival
	DT_ENTRY1("stc19_bullhockey2", "19???\?/v1", "e66411e7d47061243c7f47277727a2a8", 2892260),
	DT_ENTRY1("stc19_bullhockey2", "19???\?/v2", "51d4221a75bed1031e48cb69b5882a9d", 2985188),
	DT_ENTRY1("stc19_emptychamber", "190511", "9df4fcfc59b039fada68bf683fdda2ef", 1460384),
	DT_ENTRY1("stc19_foundermercy", "190330", "bf1fdee0be8d60ab88e01cb431aa62b6", 1780906),

	// Spring Thing 2020 - Main Festival
	DT_ENTRY1("stc20_gameneverend", "200426/gblorb", "6ac0dcbbcdd8635b925c3eadec00c0f0", 648526),
	DT_ENTRY1("stc20_gameneverend", "200426/ulx", "a108f8b4a2fa948c87307d4c04175072", 623360),
	DT_ENTRY1("stc20_landlunch", "200329", "5c33803710d13210137e167552b14a27", 1078414),
	DT_ENTRY1("stc20_napierscache", "200328", "829e6251bdb83c34b84af4cf42e7f588", 1362882),
	DT_ENTRY1("stc20_prongleman", "200326", "216d980e50525b000837e937dcfd23c1", 652288),

	// Spring Thing 2020 - Back Garden
	DT_ENTRY1("stc20_77verbs", "200328", "8af4034dea9ac13cd266d3daf2ce53cc", 1072018),

	// Spring Thing 2021 - Main Festival
	DT_ENTRY1("stc21_weightsoul", "210411", "8b185707d6f9d2717e2e174cf2b85bd4", 7355482),
	DT_ENTRY1("stc21_baggage", "210420", "8a9ef5d1f024ad5da0511e9daa8c2718", 708860),
	DT_ENTRY1("stc21_meantucker", "210319", "3347b37ec08d1d3a465904cd49c01302", 1041210),

	// Spring Thing 2021 - Back Garden
	DT_ENTRY1("stc21_shorofcash", "210328", "5e2b63af2799df4644413f8827eb4a4b", 721126),

	// Spring Thing 2022 - Main Festival
	DT_ENTRY1("stc22_fairest", "220331", "b39cff09fc0dafe9fc2218224c76d405", 1766826),
	DT_ENTRY1("stc22_brightbball", "220330", "0a9655100af4c7d244e11221e8ee7d48", 754072),
	DT_ENTRY1("stc22_digit", "220527", "2be254594d34dcaceb12d313af69ccf7", 828832),
	DT_ENTRY1("stc22_hlmarooned", "220325", "1266ba591132fbfe62de6ef30294f48d", 860582),
	DT_ENTRY1("stc22_hlmarooned", "220611", "db487dd770829aa94447eadfe3f260c6", 860582),
	DT_ENTRY1("stc22_leghorsegirl", "220307", "f9935349855b7b4dba8cffbd38ecc69d", 2307200),
	DT_ENTRY1("stc22_toursrtorus", "220524", "f4fc589f7d874eba028b3870d759815f", 2125196),

	// Spring Thing 2022 - Back Garden
	DT_ENTRY1("stc22_adrift", "229331", "7e1733b703de9d7fbf0de67e399e5c69", 2137226),

	// Spring Thing 2023  - Main Festival
	DT_ENTRY1("stc23_repeatending", "23???\?/v1", "827671713c35808fe11d29cf6595ed88", 8690112),
	DT_ENTRY1("stc23_repeatending", "23???\?/v2", "8136f79f609e33f15fad2407368553c2", 8694330),
	DT_ENTRY1("stc23_repeatending", "23???\?/v3", "e6d915734fd353de72860d64c2650575", 8694330),
	DT_ENTRY1("stc23_repeatending", "23???\?/v4", "41012d54347a18aa662279faec0f6d47", 8699086),
	DT_ENTRY1("stc23_galaxyjones", "230401", "f11053fe8974eb69e9bcbcd4d69781f8", 1727796),
	DT_ENTRY1("stc23_nothingfurth", "230327", "9c438278b9b7c3f0fbbce65e3727a76a", 2834794),
	DT_ENTRY1("stc23_rdoorydoor", "23???\?/v1", "c75410603b1acf9267d121c3f92eca75", 3028508),
	DT_ENTRY1("stc23_rdoorydoor", "23???\?/v2", "9fb79c06c61dd4931ea6ebe79fcb296a", 3028508),
	DT_ENTRY1("stc23_sacredshovel", "230327", "7d24886de35488c499e0afbe1f779884", 785670),

	// Spring Thing 2023 - Back Garden
	DT_ENTRY1("stc23_stygiandream", "230402", "1e4d4ee86084c116bb09732e6ab9d2fa", 1455946),

	// French games
	DT_ENTRYL1("archcivesuliroya", Common::FR_FRA, "230207", "20e4606d807b74fd18c134bdad79e808", 1907590),
	DT_ENTRYL1("astressolitaires", Common::FR_FRA, "210324", "20c40a53ee276ff877350f5e3e94e8f4", 2485834),
	DT_ENTRYL1("ekphrasis", Common::FR_FRA, "050718/v1", "009ca5994d9e8fe6cfb400a9da00b123", 64609308),
	DT_ENTRYL1("ekphrasis", Common::FR_FRA, "050718/v2", "edf22f51cb1ddb6775127f5c1f4d389a", 64609308),
	DT_ENTRYL1("fautedeservo", Common::FR_FRA, "180106", "9746a5c59bc0f160b8553781479afb3e", 926096),
	DT_ENTRYL1("kebabhante", Common::FR_FRA, "171022", "3e739bd3062390e6ce87022aa772de29", 219392),
	DT_ENTRYL1("latempete", Common::FR_FRA, "230109", "42122cf49a8d6aee9e91ee949108c408", 1169304),
	DT_ENTRYL0("lieuxcommuns_glulx", Common::FR_FRA, "6e18273de25a0b882b0cf01770003146", 15659070),
	DT_ENTRYL1("lieuxcommuns_glulx", Common::FR_FRA, "090606", "df7add410161b8a2093b61e2efb7b68f", 14870456),
	DT_ENTRYL1("petitgnome_glulx", Common::FR_FRA, "061101/gblorb", "a996d5c798c97965f5487ea0a14bea8c", 316422),
	DT_ENTRYL1("sarvegne_glulx", Common::FR_FRA, "061022/blb", "3238e643504cdfa3acbeda7d99fa5d26", 591068),
	DT_ENTRYL1("sarvegne_glulx", Common::FR_FRA, "061101/blb", "518ab27b773bb51f57c6526655f38e6f", 594306),
	DT_ENTRYL1("scarabeekatana", Common::FR_FRA, "070906", "e2ca97ca5579b544765e744964c9624f", 651590),
	DT_ENTRYL1("tempetebermudes", Common::FR_FRA, "190812", "3c86960d1a4c0df44857d082cedb284a", 892374),
	DT_ENTRYL1("templefeu", Common::FR_FRA, "061031", "42f1af9bcca85af1ffa8391eaacba7b1", 1271170),
	DT_ENTRYL1("templefeu", Common::FR_FRA, "070731", "73c3a0486d41a41c454108298014fac0", 2576096),
	DT_ENTRYL1("tourorastre", Common::FR_FRA, "170802", "6c7c91ec162a1b2fd5e23d9d6fc79193", 1664626),

	// French Comp 2007
	DT_ENTRYL1("frc_souterraine", Common::FR_FRA,"071227", "504942416635dd03d4d30ba88dd8f4e4", 2709508),
	DT_ENTRYL1("frc_ilephare_glulx", Common::FR_FRA, "071220/blb", "3e25bff50b9e333474ecfb5d6a362656", 3395902),

	// French Comp 2008
	DT_ENTRYL1("frc_survivre", Common::FR_FRA, "081122", "2840c7831b55d88ca93ef40b83c8612b", 1006394),

	// French Comp 2013
	DT_ENTRYL1("frc_noirdencre", Common::FR_FRA, "140110", "bdaf2ed62da378fb178d95269b3a46e0", 3427824),

	// French Comp 2015
	DT_ENTRYL1("frc_sourire", Common::FR_FRA,"150201", "491aa8e98ac471c5e1b5713e135c5ecf", 783616),
	DT_ENTRYL1("frc_comedie", Common::FR_FRA,"150201", "2f8089c76a46e1c6d74fcda950649680", 843520),

	// French Comp 2018
	DT_ENTRYL1("frc_fauteservo", Common::FR_FRA,"180107", "15caa46facfae8417c855c41e4dbfb45", 1101762),
	DT_ENTRYL1("frc_latempete", Common::FR_FRA, "200813", "f983ef39032a8d932cf91e7fa25effbb", 1158808),

	// German games
	DT_ENTRYL1("alleinkai", Common::DE_DEU, "101219", "9a6064271fb8e3e6e934d2d2ccab41c3", 1235408),
	DT_ENTRYL1("dergarten", Common::DE_DEU, "180510", "b90eda22c098c5d70eb2a0cb5140dbe0", 2183442),
	DT_ENTRYL1("deronirischegarten", Common::DE_DEU, "180730", "eb41961e5772ca99c03ba49f6b4ceb62", 476352),
	DT_ENTRYL1("deronirischegarten", Common::DE_DEU, "190626", "b201ade8eb29a64892cf1370de3c9131", 9562670),
	DT_ENTRYL1("dickeswep1", Common::DE_DEU, "130404", "a08b08d8c54ea59b140f6a9fe22ec757", 1263356),
	DT_ENTRYL1("dickeswep2", Common::DE_DEU, "130504", "3102ddb8eed9fbbb9d53eea347ab69be", 1264944),
	DT_ENTRYL1("dickeswep2", Common::DE_DEU, "131220", "8d61af8aed9a0dc3c863432c15f4609f", 1294640),
	DT_ENTRYL1("drkongpoodle", Common::DE_DEU, "111122", "131c5fb87a237b473b4d5b81b7c989d8", 1551344),
	DT_ENTRYL1("homunculus", Common::DE_DEU, "111122", "98a35cd1506a68a485c250edef54553a", 1311816),
	DT_ENTRYL1("jaeger", Common::DE_DEU, "210701", "4958d690aae92343b2cf4117fb65acd2", 1441682),
	DT_ENTRYL1("jaeger", Common::DE_DEU, "211130", "9f2cc6f728749d74f535dff31421df4e", 1645584),
	DT_ENTRYL1("jaeger", Common::DE_DEU, "220116", "392cc64126776d1cc9515ac66ed43b77", 1695248),
	DT_ENTRYL1("kleinehalbling", Common::DE_DEU, "180019", "2250a4a81641a49874ed78fb3cd39533", 884946),
	DT_ENTRYL1("matthiasclaudius", Common::DE_DEU, "170328", "514f28c468487b3239cb2fbc7c4a2dac", 1007368),
	DT_ENTRYL1("matthiasclaudius", Common::DE_DEU, "171010", "437460fae6cd8b57d9e9599f5c29504f", 1010696),
	DT_ENTRYL1("matthiasclaudius", Common::DE_DEU, "180730", "bc2d409cc3ab7c65f52332d64e792bae", 1016584),
	DT_ENTRYL1("morgenwirdklausur", Common::DE_DEU, "170423", "b71391f995becb65992561d57ed80829", 724164),
	DT_ENTRYL1("morgenwirdklausur", Common::DE_DEU, "170430", "85a966e56c4e0fc7d10df9bc3824da95", 727492),
	DT_ENTRYL1("patanoirde", Common::DE_DEU, "131202", "9ed40b987510c7a8b7da4386ff8879b1", 969304),
	DT_ENTRYL1("sonntagnachmittag", Common::DE_DEU, "141114", "762c003565858d952a21ac81904670e2", 712716),
	DT_ENTRYL1("spaterbesuch", Common::DE_DEU, "191013", "24bd852ecb47a6f01cdaa9be80195f4a", 9608754),

	// Textfire Grand Prix 2005
	DT_ENTRYL1("tgp_bananerepublik", Common::DE_DEU, "050330", "dad950c45fb67d80fc37aa716e88d9bb", 368640),

	// Textfire Grand Prix 2010
	DT_ENTRYL1("tgp_ares", Common::DE_DEU, "110517", "4dfe7cfab60e04a9030ba56c97579c0a", 3313846),

	// Textfire Grand Prix 2011
	DT_ENTRYL1("tgp_roteblum", Common::DE_DEU, "110331", "8e752fdcaa3e9f051ff50535e2c8f18e", 1038772),
	DT_ENTRYL1("tgp_schiesbefehl", Common::DE_DEU, "110311", "c9551891b01c10be5f1aa214be17a0ef", 236544),
	DT_ENTRYL1("tgp_schiesbefehl", Common::DE_DEU, "131119", "200bc928fd7a028e755de4d962c2e054", 448458),

	// Textfire Grand Prix 2014
	DT_ENTRYL1("tgp_treffen", Common::DE_DEU, "140331", "e395219a697b34fbbcb90ed03bf35a5b", 1727130),
	DT_ENTRYL1("tgp_dersigkeitenlad", Common::DE_DEU, "140401", "3dd57df785437293386076a062a7a415", 1619138),

	// Italian games
	DT_ENTRYL1("beyondita_glulx", Common::IT_ITA, "100115/gblorb", "a0cd0a410cc99aa7ff661129b8ec5de8", 1331582),
	DT_ENTRYL1("beyondita_glulx", Common::IT_ITA, "210810/gblorb", "a89d1095e7fc7c6ca72ffd8c3a6bcc67", 1332118),
	DT_ENTRYL1("pietraluna_glulx", Common::IT_ITA, "110106", "8834e0273fc730b8f6dcd38bbba2894d", 1060656),
	DT_ENTRYL1("poesia_glulx", Common::IT_ITA, "398874/blb", "de6d58b378dee41d273f7bb3c5da4220", 978440),
	DT_ENTRYL1("schizo", Common::IT_ITA, "180907/v1", "3531f6066802f53f9b095b5221fac4d2", 6198900),
	DT_ENTRYL1("schizo", Common::IT_ITA, "180907/v2", "30ff0bffbe7e1c11ea4a7ec30e0b8c76", 194560),
	DT_ENTRYL1("slenderman", Common::IT_ITA, "140721/v1", "6765e1c656f4dd1af25235bc9b11585c", 1156562),
	DT_ENTRYL1("slenderman", Common::IT_ITA, "140721/v2", "b6a73057d3ff8e54011eab2556c2332c", 13465166),
	DT_ENTRYL1("snuff", Common::IT_ITA, "180827", "1005bf49b80982997ed3b0930c390d5d", 135168),
	DT_ENTRYL1("snuff", Common::IT_ITA, "081125", "82724ff65cd9c839ee9621245326e8f6", 129884),
	DT_ENTRYL1("villamorgana_glulx", Common::IT_ITA, "090404", "88feac9efb31e7e6bd832bda02ff0cfa", 1263196),

	// Spanish games
	DT_ENTRYL1("alienlaaventura", Common::ES_ESP, "081124", "e09c0e91e53a07c768eb473deae9619c", 6884846),
	DT_ENTRYL1("conrumbo_glulx", Common::ES_ESP, "010527", "024946d9d10190694d90dedd34ab648e", 127744),
	DT_ENTRYL1("dracula1_glulx", Common::ES_ESP, "071227", "a2266f816a8e6afa324ad98e8ddb707b", 467354),
	DT_ENTRYL1("dracula2_glulx", Common::ES_ESP, "080819", "c9ff350c10f4ef88db667e58a3696938", 715450),
	DT_ENTRYL1("hhorcus_glulx", Common::ES_ESP, "100818", "48e7d8f6cd53506778e035eeab6c545c", 4191072),
	DT_ENTRYL1("kerulen_glulx", Common::ES_ESP, "090720", "0f4c8d5fb20666d5e66da025c3167285", 6842790),
	DT_ENTRYL1("lanochedelensayo", Common::ES_ESP, "100122", "23845407e62d47b5d51267492137e05e", 2527892),
	DT_ENTRYL0("legado", Common::ES_ESP, "3f5652cfb07d22c1cf668c33fc92a611", 513472),
	DT_ENTRYL1("regente", Common::ES_ESP, "021129", "7c8608e214821c55bc9224ccfd5beb44", 273092),
	DT_ENTRYL0("rur", Common::ES_ESP, "4d7dab1227494292f37107da1729392e", 3432966),
	DT_ENTRYL0("rur", Common::ES_ESP, "de15e8cdd8523c774b66950a0232a0f9", 413184),
	DT_ENTRYL1("ultimohogar_glulx", Common::ES_ESP, "021225", "08d4168a767dce4899640a000d2809d8", 663576),

	// Swedish games
	DT_ENTRYL1("drakmagi_glulx", Common::SE_SWE, "080419", "93db2e43fafb22b9e4d10f7d6f3a5136", 203630),
	DT_ENTRYL1("vanyar_glulx", Common::SE_SWE, "030613", "4a80396f31f9cced2b6689341ac5d2cc", 278780),

	// Russian games
	DT_ENTRYL1("devours", Common::RU_RUS, "r2/220224", "65a51e53c1498823024dcec286971f19", 365312),

	// ParserComp 2015
	DT_ENTRY1("pc15_chlorophyll", "150212", "447eae9f3c961baec28cbef9432839e7", 1089226),
	DT_ENTRY1("pc15_oppositeopal", "150214", "e7bbe4bca68cf243c64528b464b99ebf", 1515910),
	DT_ENTRY1("pc15_delphinahouse", "150214", "5c6e7d0f23ccc3fb17d64bcfdc14ae5e", 2199754),
	DT_ENTRY1("pc15_alongdrink", "150214", "8120604cd0cb566897fdb0f2786f4b43", 2164954),
	DT_ENTRY1("pc15_downserpent", "150214", "276a492ca99e76827265a70f84bcddd7", 1456140),
	DT_ENTRY1("pc15_endlesssands", "150215", "2105d775eb759af04ab788e046d965e0", 982748),
	DT_ENTRY1("pc15_lockdown", "150112", "556ecd86ad03658d443e8deaba126601", 1338172),
	DT_ENTRY1("pc15_terminator", "150214", "596b41d3ecc38bfb9a6aee085f333591", 1054550),
	DT_ENTRY1("pc15_terminatchase", "150212", "60a5c3ba6f2a3c07aa2c40904c05abd4", 1702244),

	// ParserComp 2021
	DT_ENTRY1("pc21_grooverland", "21???\?/v1", "3c0a17a7bce7b7cf9a8ab9f0e6342b85", 2180180),
	DT_ENTRY1("pc21_grooverland", "21???\?/v2", "d9438ba0fc0583a30f907b877f068710", 2180180),
	DT_ENTRY1("pc21_grooverland", "21???\?/v3", "9525338240712090703a07acfa0fddb0", 2180436),
	DT_ENTRY1("pc21_foreignsoil", "210806", "3e68ec0287ec8a6e94b29e57912e7ee7", 1172610),
	DT_ENTRY1("pc21_blackknife", "210620", "077647a5bbec44dc32f663c2f793bf01", 691968),
	DT_ENTRY1("pc21_timemachi21", "210627", "92409db44e62a5d91ee6a0f0767294c7", 1150004),
	DT_ENTRY1("pc21_timemachi21", "210831", "cd93405a3c77a9351bab7ccae0a6a436", 1161268),
	DT_ENTRY1("pc21_returnstars", "210630", "4949a959d70580e9c8b69b5dd4629395", 1144178),
	DT_ENTRY1("pc21_daddybirthday", "210630", "c03d6ca441e5cef88b849ffc729bac38", 2345122),
	DT_ENTRY1("pc21_gameon", "210629", "7bb02775b620727fcfbe31243a5a73df", 916302),

	// ParserComp 2022
	DT_ENTRY1("pc22_shadowsdeep", "220630", "4d0b65a40f50e1d04bfc5bdef31b5aa6", 1307402),
	DT_ENTRY1("pc22_improvorigins", "220810", "d734064ca6f678017db416820eee43dc", 1006110),
	DT_ENTRY1("pc22_midnightself", "220630", "c82a68d5c7d540076fba84c13439745d", 1700460),
	DT_ENTRY1("pc22_themuse", "220509/v1", "b49ebc65deec4a2ef8342f208f8ccc8d", 3752436),
	DT_ENTRY1("pc22_themuse", "220509/v2", "d2b3538da842da0b8fc962e2228ef5be", 12306774),
	DT_ENTRY1("pc22_anitasgoodbye", "220703", "f38cc906507c1812591b70ac6f48e1c2", 691150),

	// ParserComp 2023
	DT_ENTRY1("pc23_playerppa", "230705", "27b44da04b48ae78de23c27258341191", 1043074),
	DT_ENTRY1("pc23_playerppb", "230630", "f27087dcd2038023ffdbd46bf5a6a7c3", 1095758),
	DT_ENTRY1("pc23_jessecompass", "230625", "7f212aeaf99b668967277cb004d71072", 1861500),
	DT_ENTRY1("pc23_hinterlands", "230629", "e2a5503c2ec0f7a53dc7c6e226121279", 5491036),

	// Event One of the Second Quadrennial Ryan Veeder Exposition for Good Interactive Fiction
	DT_ENTRY1("caduceus", "200203", "259a1d733d0f6c2abae2a484a0700d1f", 615580),
	DT_ENTRY1("abandonedpools", "200203", "88cbebd3ab156775fe23b9bd645b7223", 683472),
	DT_ENTRY1("scarletportrait", "200203", "4e08aceed147b98df25272a66e27e303", 611496),
	DT_ENTRY1("gayscience", "200203", "3a0e6a116d4f5eecbeafc066459017f3", 625322),
	DT_ENTRY1("magnificientmuseum", "200203", "ca14c780a0e116d1688c056432958cc3", 615366),
	DT_ENTRY1("whishperedream", "200203", "acceef1437ebab55e9277d7832ed935b", 612008),
	DT_ENTRY1("upspookyhouseq2e1", "200203", "2dbb1454df956239dceecce5622774bf", 637434),

	// Event Two of the Second Quadrennial Ryan Veeder Exposition for Good Interactive Fiction
	DT_ENTRY1("gaiazivajarilo", "200221", "bb692481e7a261bf31ee04c889dcb50c", 944072),
	DT_ENTRY1("oldkingnebb", "200221", "7376454ebf5c470d5fd9c4fb61b7f757", 714216),
	DT_ENTRY1("indistinguishable", "200219", "b6ef0d6e638536490ea94c3fa8e41235", 628680),

	// Event Three of the Second Quadrennial Ryan Veeder Exposition for Good Interactive Fiction
	DT_ENTRY1("85verbs", "200229", "4a533c072eefba88764914fe04db5c89", 708798),
	DT_ENTRY1("upspookyhouseq2e3", "200229", "d299e2f4eaa2828de49bbcd7a618c4db", 643616),

	// SeedComp! 2023
	DT_ENTRY1("aftertheaccident", "230228", "cccb23dd3a52e0f79f8371c72f45f2a0", 977430),
	DT_ENTRY1("hismajesty", "230223", "c761ba668ff6107311b5c4e93a352b59", 2701290),
	DT_ENTRY1("hismajesty", "230305", "615014064a099b45861feac57868d91a", 2701802),
	DT_ENTRY1("magicword", "230226", "d8a4512ef0d952eecc1dbfcf5feeb810", 935362),

	// NarraScope 2020 Game Jam
	DT_ENTRY1("quicksketch", "200608", "51ddf89a462df94280c73b5914368fff", 1072392),
	DT_ENTRY1("movingon", "200609", "5a98b48e375ec43ce0317d7444a7ec81", 722120),
	DT_ENTRY1("narcissi", "200609", "67e7d31df1f20e211c93284721d04bfc", 661226),
	DT_ENTRY1("sohoekekalmoe", "200605/v1", "5966d3ae2603ab40c28412c26bb275f4", 715006),
	DT_ENTRY1("sohoekekalmoe", "200605/v2", "07c392a15a48c05ad22b4f6724db76ca", 715006),
	DT_ENTRY1("timeoutwasteland", "200621", "1ee84d99bf616af49fc6815da02e054a", 725472),

	// Single Choice Jam
	DT_ENTRY1("boing", "230818", "cd87674e7fe8418256513e8f67f96df4", 630178),
	DT_ENTRY1("chinesefamily", "230821", "8b746ac01eaea9ad679ec627664fa492", 609790),
	DT_ENTRY1("ifyouhadoneshot","230731", "466d18369d99d8d961c57ca03c25d2c3", 674536),

	DT_ENTRYL1("devours", Common::RU_RUS, "r2/220224", "65a51e53c1498823024dcec286971f19", 365312),

	DT_END_MARKER
};

} // End of namespace Glulx
} // End of namespace Glk
