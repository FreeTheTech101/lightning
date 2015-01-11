#pragma once

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

typedef float vec4_t[4];

struct MaterialConstantDef 
{
    int nameHash;
    char name[12];
    vec4_t literal;
};
 
struct GfxStateBits 
{
#ifdef XBOX
    int loadBits[2];
#elif defined PS3
    int (*loadBits)[2];
 #ifdef MW2 || MW3
    int unknown;
 #endif
#endif
};
 
struct WaterWritable
{
    float floatTime;
};
 
struct water_t 
{
    WaterWritable writable;
    float *H0X;     // Count = M * N
    float *H0Y;     // Count = M * N
    float *wTerm;       // Count = M * N
    int M;
    int N;
    float Lx;
    float Lz;
    float gravity;
    float windvel;
    float winddir[2];
    float amplitude;
    float codeConstant[4];
    GfxImage *image;
};
 
/* MaterialTextureDef->semantic */
#define TS_2D       0x0
#define TS_FUNCTION 0x1
#define TS_COLOR_MAP    0x2
#define TS_UNUSED_1 0x3
#define TS_UNUSED_2 0x4
#define TS_NORMAL_MAP   0x5
#define TS_UNUSED_3 0x6
#define TS_UNUSED_4 0x7
#define TS_SPECULAR_MAP 0x8
#define TS_UNUSED_5 0x9
#define TS_UNUSED_6 0xA
#define TS_WATER_MAP    0xB
 
union MaterialTextureDefInfo 
{
    GfxImage *image;    // MaterialTextureDef->semantic != TS_WATER_MAP
    water_t *water;     // MaterialTextureDef->semantic == TS_WATER_MAP
};
 
struct MaterialTextureDef
{
    unsigned int nameHash;
    char nameStart;
    char nameEnd;
    char sampleState;
    char semantic;
#ifdef WAW
    int unknown;
#endif
    MaterialTextureDefInfo u;
};
 
union GFxDrawSurfFields
{
    unsigned long long unused,
            primarySortKey,
            surfType,
            primaryLightIndex,
            prepass,
            materialSortedIndex,
            customIndex,
            reflectionProbeIndex,
            objectId;
};
 
union GfxDrawSurf 
{
    GFxDrawSurfFields fields;
    unsigned long long packed;
};
 
struct __declspec(align(8)) MaterialInfo
{
    const char *name;
    char gameFlags;
    char sortKey;
    char textureAtlasRowCount;
    char textureAtlasColumnCount;
    GfxDrawSurf drawSurf;
    int surfaceTypeBits;
};

enum MaterialTechniqueType
{
  TECHNIQUE_DEPTH_PREPASS = 0x0,
  TECHNIQUE_BUILD_FLOAT_Z = 0x1,
  TECHNIQUE_BUILD_SHADOWMAP_DEPTH = 0x2,
  TECHNIQUE_BUILD_SHADOWMAP_COLOR = 0x3,
  TECHNIQUE_UNLIT = 0x4,
  TECHNIQUE_EMISSIVE = 0x5,
  TECHNIQUE_EMISSIVE_SHADOW = 0x6,
  TECHNIQUE_LIT_BEGIN = 0x7,
  TECHNIQUE_LIT = 0x7,
  TECHNIQUE_LIT_SUN = 0x8,
  TECHNIQUE_LIT_SUN_SHADOW = 0x9,
  TECHNIQUE_LIT_SPOT = 0xA,
  TECHNIQUE_LIT_SPOT_SHADOW = 0xB,
  TECHNIQUE_LIT_OMNI = 0xC,
  TECHNIQUE_LIT_OMNI_SHADOW = 0xD,
  TECHNIQUE_LIT_END = 0xE,
  TECHNIQUE_LIGHT_SPOT = 0xE,
  TECHNIQUE_LIGHT_OMNI = 0xF,
  TECHNIQUE_LIGHT_SPOT_SHADOW = 0x10,
  TECHNIQUE_FAKELIGHT_NORMAL = 0x11,
  TECHNIQUE_FAKELIGHT_VIEW = 0x12,
  TECHNIQUE_SUNLIGHT_PREVIEW = 0x13,
  TECHNIQUE_CASE_TEXTURE = 0x14,
  TECHNIQUE_WIREFRAME_SOLID = 0x15,
  TECHNIQUE_WIREFRAME_SHADED = 0x16,
  TECHNIQUE_SHADOWCOOKIE_CASTER = 0x17,
  TECHNIQUE_SHADOWCOOKIE_RECEIVER = 0x18,
  TECHNIQUE_DEBUG_BUMPMAP = 0x19,
  TECHNIQUE_COUNT = 0x1A,
  TECHNIQUE_TOTAL_COUNT = 0x1B,
  TECHNIQUE_NONE = 0x1C,
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
 
struct Material
{
    MaterialInfo info;
    char stateBitsEntry[TECHNIQUE_COUNT];   // see MaterialTechniqueType
    char textureCount;
    char constantCount;
    char stateBitsCount;
    char stateFlags;
    char cameraRegion;
    MaterialTechniqueSet *techniqueSet;
    MaterialTextureDef *textureTable;
    MaterialConstantDef *constantTable;
    GfxStateBits *stateBitTable;
};

#pragma pack(push, 2)
struct Glyph
{
  unsigned __int16 letter;
  char x0;
  char y0;
  char dx;
  char pixelWidth;
  char pixelHeight;
  float s0;
  float t0;
  float s1;
  float t1;
};
#pragma pack(pop)
 
struct Font
{
  const char * name;
  int pixelHeight;
  int glyphCount;
  Material * material;
  Material * glowMaterial;
  Glyph * glyphs;
};

enum netadrtype_t
{
  NA_BOT = 0x0,
  NA_BAD = 0x1,
  NA_LOOPBACK = 0x2,
  NA_BROADCAST = 0x3,
  NA_IP = 0x4,
};

#pragma pack(push, 4)
struct netadr_t
{
  netadrtype_t type;
  char ip[4];
  unsigned __int16 port;
};
#pragma pack(pop)

enum connstate_t
{
  CA_DISCONNECTED = 0x0,
  CA_CINEMATIC = 0x1,
  CA_LOGO = 0x2,
  CA_CONNECTING = 0x3,
  CA_CHALLENGING = 0x4,
  CA_CONNECTED = 0x5,
  CA_SENDINGSTATS = 0x6,
  CA_LOADING = 0x7,
  CA_PRIMED = 0x8,
  CA_ACTIVE = 0x9,
};

#pragma pack(push, 4)
struct clientUIActive_t
{
  bool active;
  bool isRunning;
  bool cgameInitialized;
  bool cgameInitCalled;
  int keyCatchers;
  bool displayHUDWithKeycatchUI;
  connstate_t connectionState;
  int nextScrollTime;
  bool invited;
  int numVoicePacketsSent;
};
#pragma pack(pop)

typedef enum
{
    DVAR_FLAG_NONE          = 0x0,          //no flags
    DVAR_FLAG_SAVED         = 0x1,          //saves in config_mp.cfg for clients
    DVAR_FLAG_LATCHED       = 0x2,          //no changing apart from initial value (although it might apply on a map reload, I think)
    DVAR_FLAG_CHEAT         = 0x4,          //cheat
    DVAR_FLAG_REPLICATED    = 0x8,          //on change, this is sent to all clients (if you are host)
    DVAR_FLAG_UNKNOWN10     = 0x10,         //unknown
    DVAR_FLAG_UNKNOWN20     = 0x20,         //unknown
    DVAR_FLAG_UNKNOWN40     = 0x40,         //unknown
    DVAR_FLAG_UNKNOWN80     = 0x80,         //unknown
    DVAR_FLAG_USERCREATED   = 0x100,        //a 'set' type command created it
    DVAR_FLAG_USERINFO      = 0x200,        //userinfo?
    DVAR_FLAG_SERVERINFO    = 0x400,        //in the getstatus oob
    DVAR_FLAG_WRITEPROTECTED= 0x800,        //write protected
    DVAR_FLAG_UNKNOWN1000   = 0x1000,       //unknown
    DVAR_FLAG_READONLY      = 0x2000,       //read only (same as 0x800?)
    DVAR_FLAG_UNKNOWN4000   = 0x4000,       //unknown
    DVAR_FLAG_UNKNOWN8000   = 0x8000,       //unknown
    DVAR_FLAG_UNKNOWN10000  = 0x10000,      //unknown
    DVAR_FLAG_DEDISAVED     = 0x1000000,        //unknown
    DVAR_FLAG_NONEXISTENT   = 0xFFFFFFFF    //no such dvar
} dvar_flag;

typedef enum
{
    DVAR_TYPE_BOOL      = 0,
    DVAR_TYPE_FLOAT     = 1,
    DVAR_TYPE_FLOAT_2   = 2,
    DVAR_TYPE_FLOAT_3   = 3,
    DVAR_TYPE_FLOAT_4   = 4,
    DVAR_TYPE_INT       = 5,
    DVAR_TYPE_ENUM      = 6,
    DVAR_TYPE_STRING    = 7,
    DVAR_TYPE_COLOR     = 8,
    //DVAR_TYPE_INT64   = 9 only in Tx
} dvar_type;
// 67/72 bytes figured out
union dvar_value_t {
    char*   string;
    int     integer;
    float   value;
    bool    boolean;
    float   vec2[2];
    float   vec3[3];
    float   vec4[4];
    BYTE    color[4]; //to get float: multiply by 0.003921568859368563 - BaberZz
};
union dvar_maxmin_t {
    int i;
    float f;
};
typedef struct dvar_t
{
    //startbyte:endbyte
    const char*     name; //0:3
    const char*     description; //4:7
    unsigned int    flags; //8:11
    char            type; //12:12
    char            pad2[3]; //13:15
    dvar_value_t    current; //16:31
    dvar_value_t    latched; //32:47
    dvar_value_t    default; //48:64
    dvar_maxmin_t min; //65:67
    dvar_maxmin_t max; //68:72 woooo
} dvar_t;

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