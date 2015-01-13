#pragma once

class vec2_t
{
private: float x, y;
public:
	vec2_t() : x(0), y(0) {}
	vec2_t(float xc, float yc) : x(xc), y(yc) { }
	vec2_t(float(&axis)[2]) : x(axis[0]), y(axis[1]) { }

	//-vec2_t, invert
	vec2_t& operator- ()
	{
		return vec2_t(-x, -y);
	}

	vec2_t& operator++ ()
	{
		++x, ++y;
		return *this;
	}

	vec2_t& operator++ (int unused)
	{
		vec2_t result = *this;
		operator++();
		return result;
	}

	vec2_t& operator-- ()
	{
		--x, --y;
		return *this;
	}

	vec2_t& operator-- (int unused)
	{
		vec2_t result = *this;
		operator--();
		return result;
	}

#pragma region vec2_t input
	vec2_t& operator- (vec2_t &vec)
	{
		return vec2_t(x - vec.x, y - vec.y);
	}

	vec2_t& operator+ (vec2_t &vec)
	{
		return vec2_t(x + vec.x, y + vec.y);
	}

	vec2_t& operator* (vec2_t &vec)
	{
		return vec2_t(x*vec.x, y*vec.y);
	}

	vec2_t& operator/ (vec2_t &vec)
	{
		return vec2_t(x / vec.x, y / vec.y);
	}

	vec2_t& operator= (vec2_t &vec)
	{
		x = vec.x, y = vec.y;
		return *this;
	}

	bool operator== (vec2_t &vec)
	{
		return x == vec.x && y == vec.y;
	}

	bool operator!= (vec2_t &vec)
	{
		return x != vec.x || y != vec.y;
	}

	bool operator> (vec2_t &vec)
	{
		return x > vec.x && y > vec.y;
	}

	bool operator< (vec2_t &vec)
	{
		return x < vec.x && y < vec.y;
	}

	bool operator>= (vec2_t &vec)
	{
		return x >= vec.x && y >= vec.y;
	}

	bool operator<= (vec2_t &vec)
	{
		return x <= vec.x && y <= vec.y;
	}

	vec2_t& operator+= (vec2_t &vec)
	{
		x += vec.x, y += vec.y;
		return *this;
	}

	vec2_t& operator-= (vec2_t &vec)
	{
		x -= vec.x, y -= vec.y;
		return *this;
	}

	vec2_t& operator*= (vec2_t &vec)
	{
		x *= vec.x, y *= vec.y;
		return *this;
	}

	vec2_t& operator/= (vec2_t &vec)
	{
		x /= vec.x, y /= vec.y;
		return *this;
	}
#pragma endregion

#pragma region float input
	vec2_t& operator- (float vec)
	{
		return vec2_t(x - vec, y - vec);
	}

	vec2_t& operator+ (float vec)
	{
		return vec2_t(x + vec, y + vec);
	}

	vec2_t& operator* (float vec)
	{
		return vec2_t(x*vec, y*vec);
	}

	vec2_t& operator/ (float vec)
	{
		return vec2_t(x / vec, y / vec);
	}

	vec2_t& operator= (float vec)
	{
		x = vec, y = vec;
		return *this;
	}

	bool operator== (float vec)
	{
		return x == vec && y == vec;
	}

	bool operator!= (float vec)
	{
		return x != vec || y != vec;
	}

	bool operator> (float vec)
	{
		return x > vec && y > vec;
	}

	bool operator< (float vec)
	{
		return x < vec && y < vec;
	}

	bool operator>= (float vec)
	{
		return x >= vec && y >= vec;
	}

	bool operator<= (float vec)
	{
		return x <= vec && y <= vec;
	}

	vec2_t& operator+= (float vec)
	{
		x += vec, y += vec;
		return *this;
	}

	vec2_t& operator-= (float vec)
	{
		x -= vec, y -= vec;
		return *this;
	}

	vec2_t& operator*= (float vec)
	{
		x *= vec, y *= vec;
		return *this;
	}

	vec2_t& operator/= (float vec)
	{
		x /= vec, y /= vec;
		return *this;
	}
#pragma endregion

#pragma region float(*)[2] input
	vec2_t& operator- (float(&vec)[2])
	{
		return vec2_t(x - vec[0], y - vec[1]);
	}

	vec2_t& operator+ (float(&vec)[2])
	{
		return vec2_t(x + vec[0], y + vec[1]);
	}

	vec2_t& operator* (float(&vec)[2])
	{
		return vec2_t(x*vec[0], y*vec[1]);
	}

	vec2_t& operator/ (float(&vec)[2])
	{
		return vec2_t(x / vec[0], y / vec[1]);
	}

	vec2_t& operator= (float(&vec)[2])
	{
		x = vec[0], y = vec[1];
		return *this;
	}

	bool operator== (float(&vec)[2])
	{
		return x == vec[0] && y == vec[1];
	}

	bool operator!= (float(&vec)[2])
	{
		return x != vec[0] || y != vec[1];
	}

	bool operator> (float(&vec)[2])
	{
		return x > vec[0] && y > vec[1];
	}

	bool operator< (float(&vec)[2])
	{
		return x < vec[0] && y < vec[1];
	}

	bool operator>= (float(&vec)[2])
	{
		return x >= vec[0] && y >= vec[1];
	}

	bool operator<= (float(&vec)[2])
	{
		return x <= vec[0] && y <= vec[1];
	}

	vec2_t& operator+= (float(&vec)[2])
	{
		x += vec[0], y += vec[1];
		return *this;
	}

	vec2_t& operator-= (float(&vec)[2])
	{
		x -= vec[0], y -= vec[1];
		return *this;
	}

	vec2_t& operator*= (float(&vec)[2])
	{
		x *= vec[0], y *= vec[1];
		return *this;
	}

	vec2_t& operator/= (float(&vec)[2])
	{
		x /= vec[0], y /= vec[1];
		return *this;
	}
#pragma endregion

	float operator[] (int xc)
	{
		return *(float*)((int)this + xc * 4);
	}

	vec2_t& Normalize()
	{
		float length = Length();
		*this /= length;
		return *this;
	}

	float Length()
	{
		return sqrt(x*x + y*y);
	}

	float LengthSq()
	{
		return (x*x + y*y);
	}

	float Distance(vec2_t &vec)
	{
		return sqrt(DistanceEx(vec));
	}

	float DistanceEx(vec2_t &vec)
	{
		float newX = x - vec.x;
		float newY = y - vec.y;
		return (newX * newX + newY * newY);
	}

	float Distance(float(&vec)[2])
	{
		return sqrt(DistanceEx(vec));
	}

	float DistanceEx(float(&vec)[2])
	{
		float newX = x - vec[0];
		float newY = y - vec[1];
		return (newX * newX + newY * newY);
	}
};

#pragma region sound structs
struct LoadedSoundStruct
{
	int size;
	char unknown[0x10];
	char *data;
};

struct LoadedSound
{
	const char *name;
	LoadedSoundStruct struct1;
};

#pragma pack(push, 4)
struct SndCurve
{
	const char *filename;
	int knotCount;
	vec2_t knots[8];
};
#pragma pack(pop)

struct SpeakerLevels
{
	int speaker;
	int numLevels;
	float levels[2];
};

struct ChannelMap
{
	int entryCount;	// how many entries are used
	SpeakerLevels speakers[6];
};

struct SpeakerMap
{
	bool isDefault;
	const char *name;
	ChannelMap channelMaps[2][2];
};

enum snd_alias_type_t : char
{
	SAT_UNKNOWN = 0x0,
	SAT_LOADED = 0x1,
	SAT_STREAMED = 0x2,
	SAT_PRIMED = 0x3,
	SAT_COUNT = 0x4,
};

struct StreamFileNamePacked
{
	unsigned __int64 offset;
	unsigned __int64 length;
};

struct StreamFileNameRaw
{
	const char *dir;
	const char *name;
};

union StreamFileInfo
{
	StreamFileNameRaw raw;
	StreamFileNamePacked packed;
};

struct StreamFileName
{
	unsigned __int16 isLocalized;
	unsigned __int16 fileIndex;
	StreamFileInfo info;
};

struct StreamedSound
{
	StreamFileName filename;
	unsigned int totalMsec;
};

struct PrimedSound
{
	StreamFileName filename;
	LoadedSound *loadedPart;
	int dataOffset;
	int totalSize;
	unsigned int primedCrc;
};

union SoundData
{
	LoadedSound *loadSnd;	// SoundFile->type == SAT_LOADED
	StreamedSound streamSnd;	// SoundFile->type == SAT_STREAMED
	PrimedSound primedSnd;	// SoundFile->type == SAT_PRIMED
};

typedef struct
{
	char type;
	char pad[3];
	const char* folder;
	const char* file;
} StreamFile;

typedef struct
{
	char pad[20];
	StreamFile* stream;
	char pad2[76];
} snd_alias_t;

struct snd_alias_list_t
{
	const char *aliasName;
	snd_alias_t *head;
	int count;
};
#pragma endregion

#pragma region menu structs
enum operationEnum
{
	OP_NOOP = 0x0,
	OP_RIGHTPAREN = 0x1,
	OP_MULTIPLY = 0x2,
	OP_DIVIDE = 0x3,
	OP_MODULUS = 0x4,
	OP_ADD = 0x5,
	OP_SUBTRACT = 0x6,
	OP_NOT = 0x7,
	OP_LESSTHAN = 0x8,
	OP_LESSTHANEQUALTO = 0x9,
	OP_GREATERTHAN = 0xA,
	OP_GREATERTHANEQUALTO = 0xB,
	OP_EQUALS = 0xC,
	OP_NOTEQUAL = 0xD,
	OP_AND = 0xE,
	OP_OR = 0xF,
	OP_LEFTPAREN = 0x10,
	OP_COMMA = 0x11,
	OP_BITWISEAND = 0x12,
	OP_BITWISEOR = 0x13,
	OP_BITWISENOT = 0x14,
	OP_BITSHIFTLEFT = 0x15,
	OP_BITSHIFTRIGHT = 0x16,
	OP_SIN = 0x17,
	OP_FIRSTFUNCTIONCALL = 0x17,
	OP_COS = 0x18,
	OP_MIN = 0x19,
	OP_MAX = 0x1A,
	OP_MILLISECONDS = 0x1B,
	OP_DVARINT = 0x1C,
	OP_DVARBOOL = 0x1D,
	OP_DVARFLOAT = 0x1E,
	OP_DVARSTRING = 0x1F,
	OP_STAT = 0x20,
	OP_UIACTIVE = 0x21,
	OP_FLASHBANGED = 0x22,
	OP_SCOPED = 0x23,
	OP_SCOREBOARDVISIBLE = 0x24,
	OP_INKILLCAM = 0x25,
	OP_PLAYERFIELD = 0x26,
	OP_SELECTINGLOCATION = 0x27,
	OP_TEAMFIELD = 0x28,
	OP_OTHERTEAMFIELD = 0x29,
	OP_MARINESFIELD = 0x2A,
	OP_OPFORFIELD = 0x2B,
	OP_MENUISOPEN = 0x2C,
	OP_WRITINGDATA = 0x2D,
	OP_INLOBBY = 0x2E,
	OP_INPRIVATEPARTY = 0x2F,
	OP_PRIVATEPARTYHOST = 0x30,
	OP_PRIVATEPARTYHOSTINLOBBY = 0x31,
	OP_ALONEINPARTY = 0x32,
	OP_ADSJAVELIN = 0x33,
	OP_WEAPLOCKBLINK = 0x34,
	OP_WEAPATTACKTOP = 0x35,
	OP_WEAPATTACKDIRECT = 0x36,
	OP_SECONDSASTIME = 0x37,
	OP_TABLELOOKUP = 0x38,
	OP_LOCALIZESTRING = 0x39,
	OP_LOCALVARINT = 0x3A,
	OP_LOCALVARBOOL = 0x3B,
	OP_LOCALVARFLOAT = 0x3C,
	OP_LOCALVARSTRING = 0x3D,
	OP_TIMELEFT = 0x3E,
	OP_SECONDSASCOUNTDOWN = 0x3F,
	OP_TOINT = 0x40,
	OP_TOSTRING = 0x41,
	OP_TOFLOAT = 0x42,
	OP_GAMETYPENAME = 0x43,
	OP_GAMETYPE = 0x44,
	OP_GAMETYPEDESCRIPTION = 0x45,
	OP_SCORE = 0x46,
	OP_FRIENDSONLINE = 0x47,
	OP_FOLLOWING = 0x48,
	OP_STATRANGEBITSSET = 0x49,
	NUM_OPERATORS = 0x4A,
};

enum expDataType
{
	VAL_INT = 0x0,
	VAL_FLOAT = 0x1,
	VAL_STRING = 0x2,
};

struct columnInfo_s
{
	int pos;
	int width;
	int maxChars;
	int alignment;
};

struct listBoxDef_s
{
	int startPos[4];
	int endPos[4];
	int drawPadding;
	float elementWidth;
	float elementHeight;
	int elementStyle;
	int numColumns;
	columnInfo_s columnInfo[16];
	const char *doubleClick;
	int notselectable;
	int noScrollBars;
	int usePaging;
	float selectBorder[4];
	float disableColor[4];
	Material *selectIcon;
};

struct editFieldDef_s
{
	float minVal;
	float maxVal;
	float defVal;
	float range;
	int maxChars;
	int maxCharsGotoNext;
	int maxPaintChars;
	int paintOffset;
};

struct multiDef_s
{
	const char *dvarList[32];
	const char *dvarStr[32];
	float dvarValue[32];
	int count;
	int strDef;
};

union itemDefData_t
{
	listBoxDef_s *listBox;
	editFieldDef_s *editField;
	multiDef_s *multi;
	const char *enumDvarName;
	void *data;
};

union operandInternalDataUnion
{
	int intVal;
	float floatVal;
	const char *string;
};

struct Operand
{
	expDataType dataType;
	operandInternalDataUnion internals;
};

union entryInternalData
{
	operationEnum op;
	Operand operand;
};

struct expressionEntry
{
	int type;
	entryInternalData data;
};

struct statement_s
{
	int numEntries;
	expressionEntry **entries;
};

struct ItemKeyHandler
{
	int key;
	const char *action;
	ItemKeyHandler *next;
};

typedef struct
{
	float x;
	float y;
	float w;
	float h;
	int horzAlign;
	int vertAlign;
} rectDef_t;

typedef struct
{
	const char *name;
	rectDef_t rect;
	rectDef_t rectClient;
	const char *group;
	int style;
	int border;
	int ownerDraw;
	int ownerDrawFlags;
	float borderSize;
	int staticFlags;
	int dynamicFlags[4];
	int nextTime;
	float foreColor[4];
	float backColor[4];
	float borderColor[4];
	float outlineColor[4];
	Material *background;
} windowDef_t;

struct menuDef_t;

struct itemDef_t
{
	windowDef_t window;
	rectDef_t textRect[4];
	int type;
	int dataType;
	int alignment;
	int fontEnum;
	int textAlignMode;
	float textalignx;
	float textaligny;
	float textscale;
	int textStyle;
	int gameMsgWindowIndex;
	int gameMsgWindowMode;
	const char *text;
	int textSavegameInfo;
	menuDef_t *parent;
	const char *mouseEnterText;
	const char *mouseExitText;
	const char *mouseEnter;
	const char *mouseExit;
	const char *action;
	const char *onAccept;
	const char *onFocus;
	const char *leaveFocus;
	const char *dvar;
	const char *dvarTest;
	ItemKeyHandler *onKey;
	const char *enableDvar;
	int dvarFlags;
	snd_alias_list_t *focusSound;
	float special;
	int cursorPos[4];
	itemDefData_t typeData;
	int imageTrack;
	statement_s visibleExp;
	statement_s textExp;
	statement_s materialExp;
	statement_s rectXExp;
	statement_s rectYExp;
	statement_s rectWExp;
	statement_s rectHExp;
};

struct menuDef_t
{
	windowDef_t window;
	const char *font;
	int fullScreen;
	int numItems;
	int fontIndex;
	int cursorItem[4];
	int fadeCycle;
	float fadeClamp;
	float fadeAmount;
	float fadeInAmount;
	float blurRadius;
	const char *onOpen;
	const char *onClose;
	const char *onESC;
	ItemKeyHandler *onKey;
	statement_s visibleExp;
	const char *allowedBinding;
	const char *soundName;
	int imageTrack;
	float focusColor[4];
	float disableColor[4];
	statement_s rectXExp;
	statement_s rectYExp;
	itemDef_t **items;
};
#pragma endregion

#pragma region Cmd_AddCommand
typedef void(__cdecl * CommandCB_t)(void);

typedef struct cmd_function_s
{
	cmd_function_s *next;
	const char *name;
	const char *autoCompleteDir;
	const char *autoCompleteExt;
	CommandCB_t function;
} cmd_function_t;
#pragma endregion

typedef void (__cdecl * Cmd_AddServerCommand_t)(const char* cmdName, CommandCB_t callback, cmd_function_t* data);

typedef void (__cdecl * Com_Printf_t)(int, const char*, ...);
typedef void (__cdecl * Com_PrintError_t)(int, const char*, ...);
typedef void (__cdecl * Com_Error_t)(int type, const char* message, ...);

typedef void* (__cdecl * DB_FindXAssetHeader_t)(int type, const char* filename);
typedef void (*DB_LoadXAssets_t)(XZoneInfo* data, int count, int unknown);

typedef int (__cdecl * _Reader_t)(int, int); // defaulting to int for now
typedef bool (__cdecl * Image_LoadFromFileWithReader_t)(GfxImage* image, _Reader_t reader);
typedef void (__cdecl * Image_Release_t)(GfxImage* image);

typedef menuDef_t* (__cdecl * Menus_FindByName_t)(void* uiInfoArray, const char* name);

typedef void* (__cdecl * R_RegisterFont_t)(const char* asset, int);

class GameEngine
{
public:
	static void CG_GameMessage(char* text);

	static void Cmd_AddCommand(const char *name, CommandCB_t function);
	static Cmd_AddServerCommand_t Cmd_AddServerCommand;

	static Com_Printf_t Com_Printf;
	static Com_PrintError_t Com_PrintError;
	static Com_Error_t Com_Error;

	static DB_FindXAssetHeader_t DB_FindXAssetHeader;
	static DB_LoadXAssets_t DB_LoadXAssets;

	static Image_LoadFromFileWithReader_t Image_LoadFromFileWithReader;
	static Image_Release_t Image_Release;

	static Menus_FindByName_t Menus_FindByName;

	static R_RegisterFont_t R_RegisterFont;
};