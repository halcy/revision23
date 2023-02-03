/**
 * basic "multiple loadable 3D objects" effect, originally a tunnel, now a platform
 * essentially a bone animation effect, neat for getting stuff from blender
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>

#include "Tools.h"
#include "Perlin.h"

#include "ModelObjects.h"
#include "ModelText.h"

#include "GraphicsLibrary/Font.h"
#include "SVatGSegmentedInv20.h"

extern C3D_Tex bg_tex;

// Global data: Matrices
static int uLocProjection;
static int uLocModelview;
static C3D_Mtx projection;

// Global data: Lighting
static C3D_LightEnv lightEnv;
static C3D_Light light;
static C3D_LightLut lutPhong;
static C3D_LightLut lutShittyFresnel;

// Global sync stuff
const struct sync_track* syncCutMode;
const struct sync_track* syncCutOff;
const struct sync_track* syncCutAlpha;
const struct sync_track* syncScroll;

// Boooones
static int uLocBone[21];

// Other uniforms
static int uLocTexoff;

// Segment struct
typedef struct segment segment;
typedef void (*load_fun_t)(segment* self);
typedef void (*update_fun_t)(segment* self, float row);
typedef void (*draw_fun_t)(segment* self, float row, C3D_Mtx baseView);
typedef void (*delete_fun_t)(segment* self);

static Pixel* scrollPixels;
static Bitmap scroller;
static C3D_Tex scrollTex;

static Pixel* cutPixels;
static Bitmap cut_bitmap;
static C3D_Tex cut_tex;

#define SCROLL_TEXT "              Guten Abend Berlin! @ here with our small contribution for the three-dee compo!" \
                    "              With music by Saga Musix, and code and gfx by halcy! &" \
                    "              How do you like our new font? I pixeled it specifically for this scroller! No more recycling! At least not for the font... >>>" \
                    "              Greets fly out to: T$ [ Dojoe [ xq [ Wursthupe [ alcatraz [ EOS [ K2 [ titan [ blackle [ violet [ rabenauge [ truck [ bacter [ mercury [ netpoet [ and everyone else at deadline! %" \
                    "              This is the end of the scroller - I hope we have not caused any new headaches! Enjoy the party, and see you next time! ~~ halcy out"
int textLen = 0;

struct segment {
    /*
     * filled by genSegments function
     */
    // Functions: Load, update, draw and unload
    load_fun_t load;
    update_fun_t update;
    draw_fun_t draw;
    delete_fun_t delete;
    
    // Segment size
    float length;

    // Alias to other segment
    int32_t alias;

    // Load tracking
    bool loaded;
    bool markLoad;

    /*
     * Filled by load functions
     */
    // Vertices
    vertex_rigged* vbo;
    int32_t vertCount;

    // Slots for two textures
    C3D_Tex texALinear;
    C3D_Tex texBLinear;
    C3D_Tex texCLinear;
    C3D_Tex texDLinear;
    C3D_Tex texELinear;
    C3D_Tex texA;
    C3D_Tex texB;
    C3D_Tex texC;

    // {'Platform': 0, 'CRT': 1, 'Keyboard': 2, 'Deadline': 3, 'SVatG': 4, 'Icosahedron': 5}

    // Slots for "frame" track and two other tracks
    const struct sync_track* syncA;
    const struct sync_track* syncB;
    const struct sync_track* syncC;
    const struct sync_track* syncD;
    const struct sync_track* syncE;
    const struct sync_track* syncF;
    const struct sync_track* syncG;
    const struct sync_track* syncH;
    const struct sync_track* syncI;
    const struct sync_track* syncLightR;
    const struct sync_track* syncLightG;
    const struct sync_track* syncLightB;
    const struct sync_track* syncLightAmbi;
    const struct sync_track* syncLightFresnel;


    // Slot for misc data
    void* other;
};

// Texture loading: Load into linear memory
void loadTexCache(C3D_Tex* tex, C3D_TexCube* cube, const char* path) {
    FILE* f = fopen(path, "rb");
    if (!f) {
        printf("Texture file not found: %s\n", path);
        return;
    }
    
    Tex3DS_Texture t3x = Tex3DS_TextureImportStdio(f, tex, cube, false);
    fclose(f); 
    if (!t3x) {
        printf("Final texture load failure on %s\n", path);
        return;
    }
    
    // Delete the t3x object since we don't need it
    Tex3DS_TextureFree(t3x);

    //printf("Free linear memory after tex load: %d\n", linearSpaceFree());
}

// Texture loading: Linear to VRAM
void texToVRAM(C3D_Tex* linear, C3D_Tex* vram) {
    if(C3D_TexInitVRAM(vram, linear->width, linear->height, linear->fmt)) {
        C3D_TexLoadImage(vram, linear->data, GPU_TEXFACE_2D, 0);
    } 
    else {
        printf("Texture upload failed!");
    }
}
 
// The actual segments
#define SEGMENT_COUNT 1
segment tunnel[SEGMENT_COUNT];

// Tunnel segment 1: Doors
bool isTexAInVram = false;
int numPlatVerts = 0;
void loadSegmentDoors(segment* self) {
    // Load vertices
    //printf("allocing %d * %d = %d\n", sizeof(vertex_rigged), objectsNumVerts, objectsNumVerts * sizeof(vertex_rigged));
    //printf("Free linear memory after vert alloc: %d\n", linearSpaceFree());

    self->vbo = (vertex_rigged*)linearAlloc(sizeof(vertex_rigged) * objectsNumVerts);
    int copyIdx = 0;
    for(int i = 0; i < objectsNumVerts; i++) {
        if(objectsVerts[i].bones == 0) {
            self->vbo[copyIdx] = objectsVerts[i];
            copyIdx++;
            numPlatVerts++;
        }
    }
    for(int i = 0; i < objectsNumVerts; i++) {
        if(objectsVerts[i].bones != 0) {
            self->vbo[copyIdx] = objectsVerts[i];
            copyIdx++;
        }
    }
    // memcpy(&self->vbo[0], objectsVerts, objectsNumVerts * sizeof(vertex_rigged));
    self->vertCount = objectsNumVerts;

    // Load textures
    isTexAInVram = true;
    texToVRAM(&self->texALinear, &self->texA);
    
    C3D_TexSetFilter(&self->texA, GPU_LINEAR, GPU_LINEAR);
    C3D_TexSetWrap(&self->texA, GPU_REPEAT, GPU_REPEAT);

    // Set loaded
    self->loaded = true;
}

float lastrow = 0.0;
float rotval = 0.0;
void updateSegmentDoors(segment* self, float row) { 
    float delta = row - lastrow;
    float deltarot =  sync_get_val(self->syncH, row) * delta;
    rotval += deltarot;
    lastrow = row;
}

void setBonesFromSync(const struct sync_track* track, float row, int boneFirst, int boneLast) {
    float animPosFloat = sync_get_val(track, row);
    int animPos = (int)animPosFloat;
    float animPosRemainder = animPosFloat - (float)animPos;
    animPos = animPos % objectsNumFrames;
    int animPosNext = (animPos + 1) % objectsNumFrames;
    C3D_Mtx boneMat;   
    for(int i = boneFirst; i <= boneLast; i++) {
        Mtx_Identity(&boneMat);
        for(int j = 0; j < 4 * 3; j++) {
            boneMat.m[j] = objectsAnim[animPos][i][j] * (1.0 - animPosRemainder) + objectsAnim[animPosNext][i][j] * animPosRemainder;
        }
        C3D_FVUnifMtx3x4(GPU_VERTEX_SHADER, uLocBone[i], &boneMat);
    }
}

void drawSegmentDoors(segment* self, float row, C3D_Mtx baseView) {
    waitForA("draw doors");
    // Add VBO to draw buffer
    C3D_BufInfo* bufInfo = C3D_GetBufInfo();
    BufInfo_Init(bufInfo);
    BufInfo_Add(bufInfo, (void*)self->vbo, sizeof(vertex_rigged), 4, 0x3210);
    
    waitForA("load bones doors");

    // Get frame and push bones
    setBonesFromSync(self->syncB, row, 0, 0);
    setBonesFromSync(self->syncC, row, 1, 1);
    setBonesFromSync(self->syncD, row, 2, 2);
    setBonesFromSync(self->syncE, row, 3, 3);
    setBonesFromSync(self->syncF, row, 4, 4);
    setBonesFromSync(self->syncG, row, 5, 5);

    // Set texcoord offset
    float texoff = 0.0;
    C3D_FVUnifSet(GPU_VERTEX_SHADER, uLocTexoff, texoff, 0.0, 0.0, 0.0);

    // Send new modelview
    float rotation = sync_get_val(self->syncA, row);
    C3D_Mtx platView = baseView;
    Mtx_RotateX(&platView, M_PI * -0.4, true);
    Mtx_RotateZ(&platView, M_PI * rotation, true);
    C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, uLocModelview,  &platView);

    waitForA("tex bind doors");

    // Bind textures
    waitForA("tex bind doors 1");
    C3D_TexBind(0, &self->texA);
    waitForA("tex bind doors 1x");
    C3D_TexBind(1, &cut_tex);

    waitForA("lightenv doors");

    // Set up lightenv
    C3D_LightEnvInit(&lightEnv);
    C3D_LightEnvBind(&lightEnv);
    
    LightLut_Phong(&lutPhong, 100.0);
    C3D_LightEnvLut(&lightEnv, GPU_LUT_D0, GPU_LUTINPUT_LN, false, &lutPhong);
    
    float lightStrengthFresnel = sync_get_val(self->syncLightFresnel, row);
    LightLut_FromFunc(&lutShittyFresnel, badFresnel, lightStrengthFresnel, false);
    C3D_LightEnvLut(&lightEnv, GPU_LUT_FR, GPU_LUTINPUT_NV, false, &lutShittyFresnel);
    C3D_LightEnvFresnel(&lightEnv, GPU_PRI_SEC_ALPHA_FRESNEL);
    
    C3D_FVec lightVec = FVec4_New(0.0, 0.0, 0.0, 1.0);
    C3D_LightInit(&light, &lightEnv);

    float lightStrengthR = sync_get_val(self->syncLightR, row);
    float lightStrengthG = sync_get_val(self->syncLightG, row);
    float lightStrengthB = sync_get_val(self->syncLightB, row);
    float lightStrengthAmbi = sync_get_val(self->syncLightAmbi, row);

    C3D_LightColor(&light, lightStrengthR, lightStrengthG, lightStrengthB);
    C3D_LightPosition(&light, &lightVec);

    C3D_Material lightMaterial = {
        { lightStrengthAmbi, lightStrengthAmbi, lightStrengthAmbi }, //ambient
        { 1.0,  1.0,  1.0 }, //diffuse
        { 1.0f, 1.0f, 1.0f }, //specular0
        { 0.0f, 0.0f, 0.0f }, //specular1
        { 0.0f, 0.0f, 0.0f }, //emission
    };

    C3D_LightEnvMaterial(&lightEnv, &lightMaterial);

    // Set up draw env
    /*C3D_TexEnv* env = C3D_GetTexEnv(0);
    C3D_TexEnvInit(env);
    C3D_TexEnvSrc(env, C3D_Both, GPU_TEXTURE0, GPU_FRAGMENT_PRIMARY_COLOR, 0);
    C3D_TexEnvFunc(env, C3D_RGB, GPU_MODULATE);
    
    env = C3D_GetTexEnv(1);
    C3D_TexEnvInit(env);
    C3D_TexEnvSrc(env, C3D_Both, GPU_PREVIOUS, GPU_TEXTURE1, 0);
    C3D_TexEnvFunc(env, C3D_RGB, GPU_ADD);*/


    C3D_TexEnv* env = C3D_GetTexEnv(0);
    /*C3D_TexEnvSrc(env, C3D_RGB, GPU_FRAGMENT_PRIMARY_COLOR, GPU_FRAGMENT_SECONDARY_COLOR, 0);
    C3D_TexEnvOpRgb(env, 0, 0, 0);
    C3D_TexEnvFunc(env, C3D_RGB, GPU_ADD);*/

    env = C3D_GetTexEnv(0);
    C3D_TexEnvInit(env);
    C3D_TexEnvSrc(env, C3D_RGB, GPU_TEXTURE0, GPU_FRAGMENT_PRIMARY_COLOR, 0);
    C3D_TexEnvOpRgb(env, 0, 0, 0);
    C3D_TexEnvFunc(env, C3D_RGB, GPU_MODULATE);
    
    env = C3D_GetTexEnv(1);
    C3D_TexEnvInit(env);
    C3D_TexEnvSrc(env, C3D_RGB, GPU_FRAGMENT_SECONDARY_COLOR, GPU_PREVIOUS, 0);
    C3D_TexEnvOpRgb(env, GPU_TEVOP_RGB_SRC_ALPHA , 0, 0);
    C3D_TexEnvFunc(env, C3D_RGB, GPU_ADD);

    env = C3D_GetTexEnv(2);
    C3D_TexEnvInit(env);
    C3D_TexEnvSrc(env, C3D_Alpha, GPU_CONSTANT, GPU_PREVIOUS, 0);
    C3D_TexEnvFunc(env, C3D_Alpha, GPU_REPLACE);

    // GPU state for normal drawing
    C3D_DepthTest(true, GPU_GEQUAL, GPU_WRITE_ALL);
    C3D_AlphaBlend(GPU_BLEND_ADD, GPU_BLEND_ADD, GPU_SRC_ALPHA, GPU_ONE_MINUS_SRC_ALPHA, GPU_SRC_ALPHA, GPU_ONE_MINUS_SRC_ALPHA);

    waitForA("drawcall doors");

    // Now draw
    C3D_DrawArrays(GPU_TRIANGLES, 0, numPlatVerts);

    Mtx_RotateX(&baseView, M_PI * -0.4, true);
    Mtx_RotateZ(&baseView, M_PI * rotval, true);
    C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, uLocModelview,  &baseView);

    env = C3D_GetTexEnv(2);
    C3D_TexEnvInit(env);
    C3D_TexEnvSrc(env, C3D_Alpha, GPU_TEXTURE1, GPU_PREVIOUS, 0);
    C3D_TexEnvFunc(env, C3D_Alpha, GPU_REPLACE);

    C3D_DrawArrays(GPU_TRIANGLES, numPlatVerts, self->vertCount - numPlatVerts);
}

void deleteSegmentDoors(segment* self) {
    self->loaded = false;
    linearFree(self->vbo);
    C3D_TexDelete(&self->texA);
}

void genSegmentDoors(segment* self, char* syncPrefix) {
    self->load = loadSegmentDoors;
    self->update = updateSegmentDoors;
    self->draw = drawSegmentDoors;
    self->delete = deleteSegmentDoors;
    self->length = 157.0;
    self->alias = -1;

    // Get sync params
    char paramName[255];
    sprintf(paramName, "%s.rot", syncPrefix);
    self->syncA = sync_get_track(rocket, paramName);
    
    sprintf(paramName, "%s.dobjrot", syncPrefix);
    self->syncH = sync_get_track(rocket, paramName);

    sprintf(paramName, "%s.platform", syncPrefix);
    self->syncB = sync_get_track(rocket, paramName);
    sprintf(paramName, "%s.crt", syncPrefix);
    self->syncC = sync_get_track(rocket, paramName);
    sprintf(paramName, "%s.keyboard", syncPrefix);
    self->syncD = sync_get_track(rocket, paramName);
    sprintf(paramName, "%s.deadline", syncPrefix);
    self->syncE = sync_get_track(rocket, paramName);
    sprintf(paramName, "%s.svatg", syncPrefix);
    self->syncF = sync_get_track(rocket, paramName);
    sprintf(paramName, "%s.icosa", syncPrefix);
    self->syncG = sync_get_track(rocket, paramName);
    sprintf(paramName, "%s.lightR", syncPrefix);
    self->syncLightR = sync_get_track(rocket, paramName);
    sprintf(paramName, "%s.lightG", syncPrefix);
    self->syncLightG = sync_get_track(rocket, paramName);
    sprintf(paramName, "%s.lightB", syncPrefix);
    self->syncLightB = sync_get_track(rocket, paramName);    
    sprintf(paramName, "%s.lightAmbi", syncPrefix);
    self->syncLightAmbi = sync_get_track(rocket, paramName);    
    sprintf(paramName, "%s.lightFresnel", syncPrefix);
    self->syncLightFresnel = sync_get_track(rocket, paramName);   
    self->loaded = false;
}


void setBonesFromSyncB(const struct sync_track* track, float row, int boneFirst, int boneLast) {
    float animPosFloat = sync_get_val(track, row);
    int animPos = (int)animPosFloat;
    float animPosRemainder = animPosFloat - (float)animPos;
    animPos = animPos % textNumFrames;
    int animPosNext = (animPos + 1) % textNumFrames;
    C3D_Mtx boneMat;   
    for(int i = boneFirst; i <= boneLast; i++) {
        Mtx_Identity(&boneMat);
        for(int j = 0; j < 4 * 3; j++) {
            boneMat.m[j] = textAnim[animPos][i][j] * (1.0 - animPosRemainder) + textAnim[animPosNext][i][j] * animPosRemainder;
        }
        C3D_FVUnifMtx3x4(GPU_VERTEX_SHADER, uLocBone[i], &boneMat);
    }
}

void effectTunnelInit() {
    // Text info
    textLen = WidthOfSimpleString((Font*)&SVatGSegmentedInv, SCROLL_TEXT);
    //printf("string: %d\n", textLen);

    // Prep general info: Shader
    C3D_BindProgram(&shaderProgramBones);

    // Prep general info: Uniform locs
    uLocProjection = shaderInstanceGetUniformLocation(shaderProgramBones.vertexShader, "projection");
    uLocModelview = shaderInstanceGetUniformLocation(shaderProgramBones.vertexShader, "modelView");
    uLocTexoff = shaderInstanceGetUniformLocation(shaderProgramBones.vertexShader, "texoff");
    
    // Prep general info: Bones 
    char boneName[255];
    for(int i = 0; i < 21; i++) {
        sprintf(boneName, "bone%02d", i);
        uLocBone[i] = shaderInstanceGetUniformLocation(shaderProgramBones.vertexShader, boneName);
    }

    // Prep general info: Z pos sync
    syncCutMode = sync_get_track(rocket, "global.cutmode");
    syncCutOff = sync_get_track(rocket, "global.cutoff");
    syncCutAlpha = sync_get_track(rocket, "global.cutalpha");
    syncScroll = sync_get_track(rocket, "global.scroll");

    // Init tunnel segments
    genSegmentDoors(&tunnel[0], "doors");
    loadTexCache(&tunnel[0].texALinear, NULL, "romfs:/tex_platform.bin");
    tunnel[0].load(&tunnel[0]);

    // prep scroller
    C3D_TexInit(&scrollTex, 128, 128, GPU_RGBA8);
    scrollPixels = (Pixel*)linearAlloc(128 * 128 * sizeof(Pixel));
    InitialiseBitmap(&scroller, 128, 128, BytesPerRowForWidth(128), scrollPixels);

    // prep cutting stuff
    C3D_TexInit(&cut_tex, 128, 128, GPU_RGBA8);
    cutPixels = (Pixel*)linearAlloc(128 * 128 * sizeof(Pixel));
    InitialiseBitmap(&cut_bitmap, 128, 128, BytesPerRowForWidth(128), cutPixels);
}

void tunnelShadeEnv() {
    // Set up attribute info
    C3D_AttrInfo* attrInfo = C3D_GetAttrInfo();
    AttrInfo_Init(attrInfo);
    AttrInfo_AddLoader(attrInfo, 0, GPU_FLOAT, 3); // v0 = position
    AttrInfo_AddLoader(attrInfo, 1, GPU_FLOAT, 1); // v1 = bone indices
    AttrInfo_AddLoader(attrInfo, 2, GPU_FLOAT, 3); // v3 = normal        
    AttrInfo_AddLoader(attrInfo, 3, GPU_FLOAT, 4); // v4 = texcoords

    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

    C3D_BindProgram(&shaderProgramBones);
    C3D_CullFace(GPU_CULL_NONE);
}

void effectTunnelDraw(C3D_RenderTarget* targetLeft, C3D_RenderTarget* targetRight, float row, float iod) {
    waitForA("etd called");  

    // Update scroll texture
    float sshift = sync_get_val(syncScroll, row);
    FillBitmap(&scroller, RGBAf(0.0, 0.0, 0.0, 0.0));
    for(int i = 0; i < 5; i++) {
        DrawSimpleString(&scroller, (Font*)&SVatGSegmentedInv, -i * 128 - sshift, 22 * i, 0, SCROLL_TEXT);
    }

    GSPGPU_FlushDataCache(scrollPixels, 128 * 128 * sizeof(Pixel));
    GX_DisplayTransfer((u32*)scrollPixels, GX_BUFFER_DIM(128, 128), (u32*)scrollTex.data, GX_BUFFER_DIM(128, 128), TEXTURE_TRANSFER_FLAGS);
    gspWaitForPPF();

    C3D_TexSetFilter(&scrollTex, GPU_LINEAR, GPU_LINEAR);
    C3D_TexSetWrap(&scrollTex, GPU_REPEAT, GPU_REPEAT);

    // Update cutter texture
    FillBitmap(&cut_bitmap, RGBA(255, 255, 255, 255));
    int cutMode = sync_get_val(syncCutMode, row);
    float cutOffset = sync_get_val(syncCutOff, row);
    int stripe_size = 8;
    float cutAlpha = sync_get_val(syncCutAlpha, row);
    if(cutMode == 1) {
        int32_t offset = (int32_t)(cutOffset) % (stripe_size * 2);
        for(int y = 0; y < 128; y += (stripe_size * 2)) {
            DrawFilledRectangle(&cut_bitmap, 0, y + offset, 128, stripe_size, RGBAf(cutAlpha, cutAlpha, cutAlpha, cutAlpha));
        }
    }

    int cut_radius = 20;
    if(cutMode == 2) {
        for(int i = 0; i < 15; i++) {
            srand(i);
            int dx = (rand() % 10) + 5;
            int dy = (rand() % 10) + 5;
            int x = (int)(dx * cutOffset + (rand() % 128)) % (128 + cut_radius * 2) - cut_radius;
            int y = (int)(dy * cutOffset + (rand() % 128)) % (128 + cut_radius * 2) - cut_radius;
            x = rand() % 2 == 0 ? x : (128 + cut_radius * 2) - x;
            y = rand() % 2 == 0 ? y : (128 + cut_radius * 2) - y;
            DrawFilledCircle(&cut_bitmap, x, y, cut_radius, RGBAf(cutAlpha, cutAlpha, cutAlpha, cutAlpha));
        }
    }    

    GSPGPU_FlushDataCache(cutPixels, 128 * 128 * sizeof(Pixel));
    GX_DisplayTransfer((u32*)cutPixels, GX_BUFFER_DIM(128, 128), (u32*)cut_tex.data, GX_BUFFER_DIM(128, 128), TEXTURE_TRANSFER_FLAGS);
    gspWaitForPPF();

    C3D_TexSetFilter(&cut_tex, GPU_LINEAR, GPU_LINEAR);
    C3D_TexSetWrap(&cut_tex, GPU_REPEAT, GPU_REPEAT);

    // Get Z for overall effect
    float tunnelZ = 100.0;
    waitForA("mark load");  

    // Reset load marker for everything
    for(int i = 0; i < SEGMENT_COUNT; i++) {
        tunnel[i].markLoad = false;
    }

    // If behind cam, unload
    float tunnelLoadPos = -tunnelZ;
    for(int i = 0; i < SEGMENT_COUNT; i++) {
        tunnelLoadPos += tunnel[i].length;
        if(tunnelLoadPos < -16.0) {
            tunnel[i].markLoad = false;
        }
    }

    // Set active segments
    tunnelLoadPos = -tunnelZ;
    int loaded = 0;
    for(int i = 0; i < SEGMENT_COUNT; i++) {
        tunnelLoadPos += tunnel[i].length;

        // Load if in front of cam and less than 2 loaded
        if(tunnelLoadPos > -16.0 && loaded < 2) {
            tunnel[i].markLoad = true;
            loaded++;
        }
    }

    tunnel[0].update(&tunnel[0], row);

    waitForA("before drawcalls");        

    // Left eye
    tunnelShadeEnv();
    C3D_Mtx modelview;
    Mtx_Identity(&modelview);
    Mtx_Translate(&modelview, 0.0, -1.5, -5.0, true);

    C3D_FrameDrawOn(targetLeft);
    C3D_RenderTargetClear(targetLeft, C3D_CLEAR_ALL, 0x000000FF, 0);

    C3D_AlphaBlend(GPU_BLEND_ADD, GPU_BLEND_ADD, GPU_SRC_ALPHA, GPU_ONE_MINUS_SRC_ALPHA, GPU_SRC_ALPHA, GPU_ONE_MINUS_SRC_ALPHA);
    fullscreenQuad(bg_tex, 0.0, 1.01);
    
    tunnelShadeEnv();
    Mtx_PerspStereoTilt(&projection, 70.0f*M_PI/180.0f, 300.0f/240.0f, 0.01f, 6000.0f, -iod,  7.0f, false);
    C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, uLocProjection, &projection);

    // Dispatch drawcalls
    for(int i = 0; i < SEGMENT_COUNT; i++) {
        if(tunnel[i].markLoad == true) {
            waitForA("dispatch");
            tunnel[i].draw(&tunnel[i], row, modelview);
        }
    }
    fade();

    // Right eye?
    if(iod > 0.0) {
        Mtx_Identity(&modelview);
        Mtx_Translate(&modelview, 0.0, -1.5, -5.0, true);

        C3D_FrameDrawOn(targetRight);
        C3D_RenderTargetClear(targetRight, C3D_CLEAR_ALL, 0x000000FF, 0); 

        C3D_AlphaBlend(GPU_BLEND_ADD, GPU_BLEND_ADD, GPU_SRC_ALPHA, GPU_ONE_MINUS_SRC_ALPHA, GPU_SRC_ALPHA, GPU_ONE_MINUS_SRC_ALPHA);
        fullscreenQuad(bg_tex, 2.0, 1.01);
        tunnelShadeEnv();

        Mtx_PerspStereoTilt(&projection, 70.0f*M_PI/180.0f, 300.0f/240.0f, 0.01f, 6000.0f, iod, 7.0f, false);
        C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, uLocProjection, &projection);

        // Dispatch drawcalls
        for(int i = 0; i < SEGMENT_COUNT; i++) {
            if(tunnel[i].markLoad == true) {
                tunnel[i].draw(&tunnel[i], row, modelview);
            }
        }
        fade();
    }

    // Swap
    C3D_FrameEnd(0);
}
