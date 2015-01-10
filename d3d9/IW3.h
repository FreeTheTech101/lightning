#pragma once

/*
enum XAssetType(standard)
ASSET_TYPE_XMODELPIECES = 0
ASSET_TYPE_PHYSPRESET = 1
ASSET_TYPE_XANIMPARTS = 2
ASSET_TYPE_XMODEL = 3
ASSET_TYPE_MATERIAL = 4
ASSET_TYPE_PIXELSHADER = 5
ASSET_TYPE_TECHNIQUE_SET = 6
ASSET_TYPE_IMAGE = 7
ASSET_TYPE_SOUND = 8
ASSET_TYPE_SOUND_CURVE = 9
ASSET_TYPE_CLIPMAP = 0Ah
ASSET_TYPE_CLIPMAP_PVS = 0Bh
ASSET_TYPE_COMWORLD = 0Ch
ASSET_TYPE_GAMEWORLD_SP = 0Dh
ASSET_TYPE_GAMEWORLD_MP = 0Eh
ASSET_TYPE_MAP_ENTS = 0Fh
ASSET_TYPE_GFXWORLD = 10h
ASSET_TYPE_LIGHT_DEF = 11h
ASSET_TYPE_UI_MAP = 12h
ASSET_TYPE_FONT = 13h
ASSET_TYPE_MENULIST = 14h
ASSET_TYPE_MENU = 15h
ASSET_TYPE_LOCALIZE_ENTRY = 16h
ASSET_TYPE_WEAPON = 17h
ASSET_TYPE_SNDDRIVER_GLOBALS = 18h
ASSET_TYPE_FX = 19h
ASSET_TYPE_IMPACT_FX = 1Ah
ASSET_TYPE_AITYPE = 1Bh
ASSET_TYPE_MPTYPE = 1Ch
ASSET_TYPE_CHARACTER = 1Dh
ASSET_TYPE_XMODELALIAS = 1Eh
ASSET_TYPE_RAWFILE = 1Fh
ASSET_TYPE_STRINGTABLE = 20h
ASSET_TYPE_COUNT = 21h
ASSET_TYPE_STRING = 21h
ASSET_TYPE_ASSETLIST = 22h
*/

typedef enum assetType_e
{
	ASSET_TYPE_PHYSPRESET = 0,
	ASSET_TYPE_PHYS_COLLMAP = 1,
	ASSET_TYPE_XANIM = 2,
	ASSET_TYPE_XMODELSURFS = 3,
	ASSET_TYPE_XMODEL = 4,
	ASSET_TYPE_MATERIAL = 5,
	ASSET_TYPE_PIXELSHADER = 6,
	ASSET_TYPE_VERTEXSHADER = 7,
	ASSET_TYPE_VERTEXDECL = 8,
	ASSET_TYPE_TECHSET = 9,
	ASSET_TYPE_IMAGE = 10,
	ASSET_TYPE_SOUND = 11,
	ASSET_TYPE_SNDCURVE = 12,
	ASSET_TYPE_LOADED_SOUND = 13,
	ASSET_TYPE_COL_MAP_SP = 14,
	ASSET_TYPE_COL_MAP_MP = 15,
	ASSET_TYPE_COM_MAP = 16,
	ASSET_TYPE_GAME_MAP_SP = 17,
	ASSET_TYPE_GAME_MAP_MP = 18,
	ASSET_TYPE_MAP_ENTS = 19,
	ASSET_TYPE_FX_MAP = 20,
	ASSET_TYPE_GFX_MAP = 21,
	ASSET_TYPE_LIGHTDEF = 22,
	ASSET_TYPE_UI_MAP = 23,
	ASSET_TYPE_FONT = 24,
	ASSET_TYPE_MENUFILE = 25,
	ASSET_TYPE_MENU = 26,
	ASSET_TYPE_LOCALIZE = 27,
	ASSET_TYPE_WEAPON = 28,
	ASSET_TYPE_SNDDRIVERGLOBALS = 29,
	ASSET_TYPE_FX = 30,
	ASSET_TYPE_IMPACTFX = 31,
	ASSET_TYPE_AITYPE = 32,
	ASSET_TYPE_MPTYPE = 33,
	ASSET_TYPE_CHARACTER = 34,
	ASSET_TYPE_XMODELALIAS = 35,
	ASSET_TYPE_RAWFILE = 36,
	ASSET_TYPE_STRINGTABLE = 37,
	ASSET_TYPE_LEADERBOARDDEF = 38,
	ASSET_TYPE_STRUCTUREDDATADEF = 39,
	ASSET_TYPE_TRACER = 40,
	ASSET_TYPE_VEHICLE = 41,
	ASSET_TYPE_ADDON_MAP_ENTS = 42,
	ASSET_TYPE_MAX = 43
} assetType_t;

typedef enum
{
	DVAR_FLAG_NONE			= 0x0,			//no flags
	DVAR_FLAG_SAVED		    = 0x1,			//saves in config_mp.cfg for clients
	DVAR_FLAG_LATCHED		= 0x2,			//no changing apart from initial value (although it might apply on a map reload, I think)
	DVAR_FLAG_CHEAT			= 0x4,			//cheat
	DVAR_FLAG_REPLICATED	= 0x8,			//on change, this is sent to all clients (if you are host)
	DVAR_FLAG_UNKNOWN10		= 0x10,			//unknown
	DVAR_FLAG_UNKNOWN20		= 0x20,			//unknown
	DVAR_FLAG_UNKNOWN40		= 0x40,			//unknown
	DVAR_FLAG_UNKNOWN80		= 0x80,			//unknown
	DVAR_FLAG_USERCREATED	= 0x100,		//a 'set' type command created it
	DVAR_FLAG_USERINFO		= 0x200,		//userinfo?
	DVAR_FLAG_SERVERINFO	= 0x400,		//in the getstatus oob
	DVAR_FLAG_WRITEPROTECTED= 0x800,		//write protected
	DVAR_FLAG_UNKNOWN1000	= 0x1000,		//unknown
	DVAR_FLAG_READONLY		= 0x2000,		//read only (same as 0x800?)
	DVAR_FLAG_UNKNOWN4000	= 0x4000,		//unknown
	DVAR_FLAG_UNKNOWN8000	= 0x8000,		//unknown
	DVAR_FLAG_UNKNOWN10000  = 0x10000,		//unknown
	DVAR_FLAG_DEDISAVED		= 0x1000000,		//unknown
	DVAR_FLAG_NONEXISTENT	= 0xFFFFFFFF	//no such dvar
} dvar_flag;

typedef enum
{
	DVAR_TYPE_BOOL		= 0,
	DVAR_TYPE_FLOAT		= 1,
	DVAR_TYPE_FLOAT_2	= 2,
	DVAR_TYPE_FLOAT_3	= 3,
	DVAR_TYPE_FLOAT_4	= 4,
	DVAR_TYPE_INT		= 5,
	DVAR_TYPE_ENUM		= 6,
	DVAR_TYPE_STRING	= 7,
	DVAR_TYPE_COLOR		= 8,
	//DVAR_TYPE_INT64	= 9 only in Tx
} dvar_type;
// 67/72 bytes figured out
union dvar_value_t {
	char*	string;
	int		integer;
	float	value;
	bool	boolean;
	float	vec2[2];
	float	vec3[3];
	float	vec4[4];
	BYTE	color[4]; //to get float: multiply by 0.003921568859368563 - BaberZz
	//__int64 integer64; only in Tx
};
union dvar_maxmin_t {
	int i;
	float f;
};
typedef struct dvar_t
{
	//startbyte:endbyte
	const char*		name; //0:3
	const char*		description; //4:7
	unsigned int	flags; //8:11
	char			type; //12:12
	char			pad2[3]; //13:15
	dvar_value_t	current; //16:31
	dvar_value_t	latched; //32:47
	dvar_value_t	default; //48:64
	dvar_maxmin_t min; //65:67
	dvar_maxmin_t max; //68:72 woooo
} dvar_t;

// material stuff
struct GfxImage
{
    char* texture;
    char unknown2;
    char a3;
    char a2;
    char unknown3;
    char unknown4;
    char unknown5;
    char unknown6;
    char a4;
    int dataLength1;
    int dataLength2;
    short height;
	short width;
    short depth;
    short unknown8;
    char* name;
};

struct MaterialTextureDef
{
    unsigned int typeHash; // asset hash of type
    char firstCharacter; // first character of image name
    char secondLastCharacter; // second-last character of image name (maybe only in CoD4?!)
    unsigned char unknown; // maybe 0xE2
    char unknown2; // likely 0x00
    GfxImage* image; // GfxImage* actually
};

struct VertexDecl
{
        const char* name;
        int unknown;
        char pad[28];
        IDirect3DVertexDeclaration9* declarations[16];
};

struct PixelShader
{
        const char* name;
        IDirect3DPixelShader9* shader;
        DWORD* bytecode;
        int flags;
};

struct VertexShader
{
        const char* name;
        IDirect3DVertexShader9* shader;
        DWORD* bytecode;
        int flags;
};

struct MaterialPass
{
        VertexDecl* vertexDecl;
        VertexShader* vertexShader;
        PixelShader* pixelShader;
        char pad[8];
};

struct MaterialTechnique
{
        int pad;
        short pad2;
        short numPasses;
        MaterialPass passes[1];
};

struct MaterialTechniqueSet
{
        const char* name;
        char pad[4];
        MaterialTechniqueSet* remappedTechniqueSet;
        MaterialTechnique* techniques[48];
};

struct MaterialStuff
{
        char unk;
        char sortKey;
};

struct Material
{
        const char* name;
        union
        {
                unsigned short flags; // 0x2F00 for instance
                MaterialStuff sort;
        };
        unsigned char animationX; // amount of animation frames in X
        unsigned char animationY; // amount of animation frames in Y
        char unknown1[4]; // 0x00
        unsigned int rendererIndex; // only for 3D models
        char unknown9[4];
        unsigned int surfaceTypeBits;
        unsigned int unknown2; // 0xFFFFFFFF
        unsigned int unknown3; // 0xFFFFFF00
        char unknown4[40]; // 0xFF
        char numMaps; // 0x01, possibly 'map count' (zone code confirms)
        char unknown5; // 0x00
        char unknownCount2; // 0x01, maybe map count actually
        char unknown6; // 0x03
        unsigned int unknown7; // 0x04
        MaterialTechniqueSet* techniqueSet; // '2d' techset; +80
        MaterialTextureDef* maps; // map references
        unsigned int unknown8;
        void* stateMap; // might be NULL, need to test
};

struct XModelAngle
{
        short x;
        short y;
        short z;
        short base; // defines the 90-degree point for the shorts
};

struct XModelTagPos
{
        float x;
        float y;
        float z;
};

struct XSurface
{
        short pad;
        short numVertices;
        short numPrimitives;
        unsigned char streamHandle; // something to do with buffers
        char pad2;
        int pad3;
        void* indexBuffer;
        char pad4[12];
        void* vertexBuffer;
        char pad5[32];
};

struct XModelSurfs
{
        const char* name;
        XSurface* surfaces;
        int numSurfaces;
        char pad[24];
};

struct XSurfaceLod
{
        char pad[8];
        XModelSurfs* surfaces;
        char pad2[32];
};

struct XModel
{
        char* name; // +0
        char numBones; // +4
        char numSubBones;
        char numMaterials;
        char pad2;
        char pad3[28]; // +8
        short* boneNames; // +36
        char* boneUnknown1; // +40
        XModelAngle* tagAngles; // +44, element size 8
        XModelTagPos* tagPositions; // +48, element size 12
        char* boneUnknown4; // +52
        char* boneUnknown5; // +56, element size 32
        Material** materials; // +60
        XSurfaceLod lods[4];
        int pad4; // +240
        char* stuffs; // +244
        int numStuffs; // +248
        int pad6;
        void* unknowns; // bone count, +256, element size 28
        char pad5[36];
        void* physPreset;
        void* physCollmap;
}; // total size 304

// netadr_t
typedef enum {
        NA_BOT,
        NA_BAD,                                        // an address lookup failed
        NA_LOOPBACK,
        NA_BROADCAST,
        NA_IP,
        NA_IP6, // custom type
} netadrtype_t;

typedef enum {
        NS_CLIENT,
        NS_SERVER
} netsrc_t;

typedef enum {
        FS_READ,
        FS_WRITE,
        FS_APPEND,
        FS_APPEND_SYNC
} fsMode_t;

typedef struct {
        netadrtype_t        type;

        BYTE        ip[4];

        unsigned short        port;

        BYTE        ipx[10];
} netadr_t;


/*#pragma pack(push, 1)
typedef struct
{
        netadrtype_t type;

        union
        {
                BYTE ip[4];
                BYTE ip6[16];
        };

        unsigned short port;
} netadr_t;
#pragma pack(pop)*/

typedef struct  
{
        int unknown1;
        int unknown2;
        char* data;
        int unknown3;
        int maxsize; // 16
        int cursize;
        int unknown4;
        int readcount; // 28
} msg_t;

typedef struct  
{
        int curClients;
        int maxClients;
        char map[128];
} svstatus_t;

struct XZoneInfo {
        const char* name;
        int type1;
        int type2;
};

typedef struct fontEntry_s
{
        unsigned short character;
        unsigned char padLeft;
        unsigned char padTop;
        unsigned char padRight;
        unsigned char width;
        unsigned char height;
        unsigned char const0;
        float uvLeft;
        float uvTop;
        float uvRight;
        float uvBottom;
} fontEntry_t;

typedef struct Font_s
{
        char* name;
        int size;
        int entries;
        Material* image;
        Material* glowImage;
        fontEntry_t* characters;
} Font;

typedef float vec4_t[4];

/*typedef struct
{
        float x;
        float y;
        float w;
        float h;
} rectangleDef_t;

typedef rectangleDef_t Rectangle;*/

typedef struct  
{
        int type;
        int id;
        void* extraData;
} menuExpToken_t;

typedef struct  
{
        int count;
        menuExpToken_t* tokens;
} menuExpression_t;

typedef struct  
{
        void* data;
        int type;
} menuStatement_t;

typedef struct  
{
        int numStatements;
        menuStatement_t** statements;
} menuScript_t;

typedef struct
{
        char* name;
        vec4_t rect;
        char rectAlignX;
        char rectAlignY;
        // 22
        char pad[2];
        // 24
        float originX;
        float originY;
        // 32
        char pad2[12];
        // 44
        char* group;
        // 48
        int style;
        int border;
        int ownerDraw;
        int ownerDrawFlags;
        float borderSize;
        // 68
        int flags1;
        int flags2;
        int unknown1;
        // 80
        vec4_t foreColor;
        vec4_t backColor;
        vec4_t borderColor;
        vec4_t outlineColor;
        // 144
        vec4_t unknownColor;
        // 160
        Material* background;
} windowDef_t;

typedef windowDef_t Window;

#define MAX_LB_COLUMNS 16

typedef struct columnInfo_s {
        int pos;
        int width;
        int maxChars;
        int unknown;
} columnInfo_t;

typedef struct listBoxDef_s {
        int cursorPos;
        int unk;
        int startPos;
        int endPos;
        float elementWidth;
        float elementHeight;
        int elementStyle;
        int numColumns;
        columnInfo_t columnInfo[MAX_LB_COLUMNS];
        menuScript_t* doubleClick;
        int notselectable;
        int noscrollbars;
        int usepaging;
} listBoxDef_t;

typedef struct  
{
        int type;
        menuExpression_t* expression;
} componentExpression_t;

typedef struct
{
        int expression;
        char* comp1;
        char* comp2;
} componentExpressionDef_t;

extern componentExpressionDef_t* componentExpressions;

typedef struct execKey_s
{
        union
        {
                char key[4];
                int keyInt;
        };
        menuScript_t* script;
        execKey_s* next;
} execKey_t;

typedef struct  
{
        Window window;
        // 164
        char pad1[20];
        // 184
        int type;
        int unknownType;
        int align;
        int textFont;
        int textAlign;
        float textAlignX;
        float textAlignY;
        float textScale;
        int textStyle;
        int unknown;
        int unknown2;
        char* text;
        int unknown3;
        int unknown4;
        menuScript_t* mouseEnterText;
        menuScript_t* mouseExitText;
        menuScript_t* mouseEnter;
        menuScript_t* mouseExit;
        menuScript_t* action;
        menuScript_t* accept;
        menuScript_t* onFocus;
        menuScript_t* leaveFocus;
        char* dvar;
        char* dvarTest;
        execKey_t* execKeys;
        void* testDvarValue;
        char* localVar;
        int testDvarType;
        char** focusSound;
        float feeder;
        int cursorPos;
        void* typeData;
        char pad2[4];
        int numExpressions;
        componentExpression_t* expressions;
        menuExpression_t* visibleExp;
        menuExpression_t* disabledExp;
        menuExpression_t* textExp;
        menuExpression_t* materialExp;
} itemDef_t;

typedef struct
{
        Window window;
        int unknown2;
        int fullscreen;
        int numItems;
        int unknown3;
        int unknown4;
        int fadeCycle;
        float fadeClamp;
        float fadeAmount;
        float fadeInAmount;
        float blurWorld;
        menuScript_t* onOpen;
        menuScript_t* onRequestClose;
        menuScript_t* onClose;
        menuScript_t* onESC;
        execKey_t* execKeys;
        void* visibleExp;
        char* allowedBinding;
        char* soundLoop;
        int unknown5;
        vec4_t focusColor;
        void* rectXExp;
        void* rectYExp;
        void* rectHExp;
        void* rectWExp;
        void* openSoundExp;
        void* closeSoundExp;
        itemDef_t** items;
} menuDef_t;

struct RawFile
{
        char* name;
        int compressedSize; // no trailing \0 in the string
        int size; // excludes the trailing \0
        char* data;
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

typedef struct  
{
        const char* name;
        snd_alias_t* aliases;
        int numAliases;
} snd_alias_list_t;

typedef struct
{
        char                        pakFilename[256];                        // c:\quake3\baseq3\pak0.pk3
        char                        pakBasename[256];                        // pak0
        char                        pakGamename[256];                        // baseq3
        int                                handle;                                                // handle to zip file
        int                                checksum;
} pack_t;

typedef struct {
        char                path[256];                // c:\quake3
        char                gamedir[256];        // baseq3
} directory_t;

typedef struct searchpath_s
{
        searchpath_s* next;
        pack_t* pack;
        directory_t* dir;
} searchpath_t;

typedef struct gclient_s {
        unsigned char pad[12764];
        unsigned int team;
        char pad2[1164];
} gclient_t;

typedef struct  
{
        int trType;
        int trTime;
        int trDuration;
        float trBase[3];
        float trDelta[3];
} trajectory_t;

typedef struct  
{
        int entityNum; // 0
        int eType; // 4
        char pad[4]; // 8
        trajectory_t pos; // 12
        trajectory_t apos; // 48
        char pad2[60]; // 84
        int itemIndex; // 144 (actually index.item)
        char pad3[16];
        int eventParm; // 164
        int pad4; // 168
        int events[4]; // 172
        int eventParms[4]; // 188
        char pad5[12]; // 204
        int un1; // 216
} entityState_t;
        
typedef struct gentity_s {
        unsigned char pad[312]; // 0
        float origin[3]; // 312
        float angles[3]; // 324
        char pad2[8];
        gclient_t* client; // 344
        unsigned char pad3[28];
        short classname;
        short pad4;
        unsigned char pad5[248];
} gentity_t;

#pragma pack(push, 1)
typedef struct client_s
{
        // 0
        int state;
        // 4
        char pad[36];
        // 40
        netadr_t adr;
        // 60
        char pad1[1568];
        // 1628
        char connectInfoString[1024];
        // 2652
        char pad2[133192];
        // 135844
        char name[16];
        // 135860
        char pad3[12];
        // 135872
        int snapNum;
        // 135876
        int pad4;
        // 135880
        short ping;
        // 135882
        //char pad5[142390];
        char pad5[133158];
        // 269040
        int isBot;
        // 269044
        char pad6[9228];
        // 278272
        __int64 steamid;
        // 278280
        char pad7[403592];
} client_t;
#pragma pack(pop)

enum scriptType_e
{
        SCRIPT_NONE = 0,
        SCRIPT_OBJECT = 1,
        SCRIPT_STRING = 2,
        SCRIPT_VECTOR = 4,
        SCRIPT_FLOAT = 5,
        SCRIPT_INTEGER = 6
};

typedef struct  
{
        union
        {
                void* entity;
                float number;
                unsigned short string;
                float* vector;
                int integer;
        };
        scriptType_e type;
} VariableValue;

// types
typedef void (__cdecl * CommandCB_t)(void);

typedef struct cmd_function_s
{
    cmd_function_s *next;
    const char *name;
    const char *autoCompleteDir;
    const char *autoCompleteExt;
    CommandCB_t function;
} cmd_function_t;

// original functions
typedef void (__cdecl * Com_Error_t)(int type, const char* message, ...);
extern Com_Error_t Com_Error;

typedef void (__cdecl *Com_Printf_t)(int, const char*, ...);
extern Com_Printf_t Com_Printf;

typedef void (__cdecl * Com_PrintError_t)(int, const char*, ...);
extern Com_PrintError_t Com_PrintError;

typedef void (__cdecl * Cmd_AddServerCommand_t)(const char* cmdName, CommandCB_t callback, cmd_function_t* data);
extern Cmd_AddServerCommand_t Cmd_AddServerCommand;

typedef void* (__cdecl * DB_FindXAssetHeader_t)(int type, const char* filename);
extern DB_FindXAssetHeader_t DB_FindXAssetHeader;

typedef dvar_t* (__cdecl * Dvar_RegisterBool_t)(const char* name, bool default, int flags, const char* description);
extern Dvar_RegisterBool_t Dvar_RegisterBool;

typedef dvar_t* (__cdecl * Dvar_RegisterInt_t)(const char* name, int default, int min, int max, int flags, const char* description);
extern Dvar_RegisterInt_t Dvar_RegisterInt;


typedef char* (__cdecl* Dvar_InfoString_Big_t)(int typeMask);
extern Dvar_InfoString_Big_t Dvar_InfoString_Big;

typedef dvar_t* (__cdecl * Dvar_FindVar_t)(void);
extern Dvar_FindVar_t _Dvar_FindVar;
dvar_t* Dvar_FindVar(char* name);


typedef int(__cdecl * FS_ReadFile_t)(const char* path, char** buffer);
extern FS_ReadFile_t FS_ReadFile; // fix needed

typedef int (__cdecl * FS_Read_t)(void* buffer, size_t size, int file);
extern FS_Read_t FS_Read;

typedef int (__cdecl * FS_FOpenFileRead_t)(const char* file, int* fh, int uniqueFile);
extern FS_FOpenFileRead_t FS_FOpenFileRead;

typedef int (__cdecl * FS_FCloseFile_t)(int fh);
extern FS_FCloseFile_t FS_FCloseFile;


typedef bool (__cdecl * NET_StringToAdr_t)(netadr_t*);
bool NET_StringToAdr(const char* address, netadr_t* adr);
extern NET_StringToAdr_t NET_StringToAdr_CoD4;

void NET_OutOfBandPrint(int type, netadr_t adr, const char* message, ...);

extern int* svs_numclients;

char* GetStringConvar(char* key);

void Cmd_AddCommand(const char *name, CommandCB_t function);