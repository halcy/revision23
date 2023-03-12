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

// Global data: Matrices
static int uLocProjection;
static int uLocModelview;
static C3D_Mtx projection;

// Global data: Lighting
static C3D_LightEnv lightEnv;
static C3D_Light light;
static C3D_LightLut lutPhong;
static C3D_LightLut lutShittyFresnel;

// Boooones
static int uLocBone[21];

fbxBasedObject modelStreet;
fbxBasedObject modelCar;

// Texture loading helper using t3x format files and loading from romfs
void loadTexture(C3D_Tex* tex, C3D_TexCube* cube, const char* path) {
    FILE* f = fopen(path, "rb");
    if (!f) {
        printf("Texture file not found: %s\n", path);
        return;
    }
    
    Tex3DS_Texture t3x = Tex3DS_TextureImportStdio(f, tex, cube, true);
    fclose(f); 
    if (!t3x) {
        printf("Texture load failure on %s\n", path);
        return;
    }
    
    // Set basic options
    C3D_TexSetFilter(tex, GPU_LINEAR, GPU_LINEAR);
    C3D_TexSetWrap(tex, GPU_REPEAT, GPU_REPEAT);

    // Delete the t3x object since we don't need it
    Tex3DS_TextureFree(t3x);
}

// Set bone mat uniforms from sync value
// Lerps the matrices for nicer between frame interpolation
// Assumes loop from last to first frame
void setBonesFromSync(fbxBasedObject* model, float row) {
    int frameCount = model->frameCount;
    int boneCount = model->boneCount;
    printf("%d %d\n", frameCount, boneCount);

    // Figure out where in the animation we are
    float animPosFloat = sync_get_val(model->frameSync, row);
    int animPos = (int)animPosFloat;
    float animPosRemainder = animPosFloat - (float)animPos;
    animPos = animPos % frameCount;
    int animPosNext = (animPos + 1) % frameCount;

    // Set bones
    C3D_Mtx boneMat;   
    for(int i = 0; i < boneCount; i++) {
        Mtx_Identity(&boneMat);
        for(int j = 0; j < 4 * 3; j++) {
            int amimIdxA = FBX_FRAME_IDX(animPos, i, j, boneCount);
            int amimIdxB = FBX_FRAME_IDX(animPosNext, i, j, boneCount);
            boneMat.m[j] = model->animFrames[amimIdxA] * (1.0 - animPosRemainder) + model->animFrames[amimIdxB] * animPosRemainder;
        }
        C3D_FVUnifMtx3x4(GPU_VERTEX_SHADER, uLocBone[i], &boneMat);
    }
}

// Load an FBX file
// Will load the named object from the file, put the vertices in the vbo and the frames in frames, allocating both appropriately.
fbxBasedObject loadFBXObject(const char* filename, const char* textureFilename, const char* syncPrefix) {
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL) {
        fprintf(stderr, "Error: failed to open file for reading.\n");
        exit(1);
    }

    // Read the vertCount and frameCount from the file
    int32_t vertCount, boneCount, frameCount;
    fread(&vertCount, sizeof(int32_t), 1, fp);
    fread(&boneCount, sizeof(int32_t), 1, fp);
    fread(&frameCount, sizeof(int32_t), 1, fp);

    // Allocate memory for the object
    fbxBasedObject object;
    object.vertCount = vertCount;
    object.boneCount = boneCount;
    object.frameCount = frameCount;
    object.vbo = (vertex_rigged*)linearAlloc(sizeof(vertex_rigged) * vertCount);
    object.animFrames = (float*)malloc(sizeof(float) * frameCount * object.boneCount * 12);

    // Read the vbo from the file
    fread(object.vbo, sizeof(vertex_rigged), vertCount, fp);

    // Read the animFrames from the file
    fread(object.animFrames, sizeof(float), frameCount * object.boneCount * 12, fp);
    fclose(fp);

    for(int i = 0; i < object.vertCount; i++) {
        printf("%f %f %f\n", object.vbo[i].position[0], object.vbo[i].position[1], object.vbo[i].position[2]);
    }

    // Load sync track
    char trackName[255];
    sprintf(trackName, "%s.frame", syncPrefix);
    object.frameSync = sync_get_track(rocket, trackName);

    // Load texture into VRAM if requested
    if(textureFilename != NULL) {
        loadTexture(&object.tex, NULL, textureFilename);
    }
    
    return object;
}

void effectStreetInit() {
    // Prep general info: Shader (precompiled in main for important ceremonial reasons)
    C3D_BindProgram(&shaderProgramBones);

    // Prep general info: Uniform locs
    uLocProjection = shaderInstanceGetUniformLocation(shaderProgramBones.vertexShader, "projection");
    uLocModelview = shaderInstanceGetUniformLocation(shaderProgramBones.vertexShader, "modelView");
    
    // Prep general info: Bones 
    char boneName[255];
    for(int i = 0; i < 21; i++) {
        sprintf(boneName, "bone%02d", i);
        uLocBone[i] = shaderInstanceGetUniformLocation(shaderProgramBones.vertexShader, boneName);
    }

    // Load a model
    printf("try load\n");
    modelCar = loadFBXObject("romfs:/car.vbo", "romfs:/tex_platform.bin", "street.car");
    modelStreet = loadFBXObject("romfs:/street.vbo", "romfs:/tex_platform.bin", "street.street");
    printf("did load\n");
}

// TODO: Split out shade setup
void drawModel(fbxBasedObject* model, float row) {
    // Update bone mats
    printf("set bones\n");
    setBonesFromSync(model, row);
    printf("got bones\n");

    // Set up attribute info
    C3D_AttrInfo* attrInfo = C3D_GetAttrInfo();
    AttrInfo_Init(attrInfo);
    AttrInfo_AddLoader(attrInfo, 0, GPU_FLOAT, 3); // v0 = position (float3)
    AttrInfo_AddLoader(attrInfo, 1, GPU_FLOAT, 2); // v1 = bone indices (float2)
    AttrInfo_AddLoader(attrInfo, 2, GPU_FLOAT, 2); // v2 = bone weights (float2)
    AttrInfo_AddLoader(attrInfo, 3, GPU_FLOAT, 3); // v3 = normal (float3)
    AttrInfo_AddLoader(attrInfo, 4, GPU_FLOAT, 2); // v4 = texcoords (float2)

    // Begin frame and bind shader
    C3D_BindProgram(&shaderProgramBones);

    // Add VBO to draw buffer
    C3D_BufInfo* bufInfo = C3D_GetBufInfo();
    BufInfo_Init(bufInfo);
    BufInfo_Add(bufInfo, (void*)model->vbo, sizeof(vertex_rigged), 5, 0x43210);

    // Bind texture
    C3D_TexBind(0, &model->tex);    

    // Set up lighting
    C3D_LightEnvInit(&lightEnv);
    C3D_LightEnvBind(&lightEnv);
    
    LightLut_Phong(&lutPhong, 100.0);
    C3D_LightEnvLut(&lightEnv, GPU_LUT_D0, GPU_LUTINPUT_LN, false, &lutPhong);
    
    // Add funny edge lighting that makes 3D pop
    float lightStrengthFresnel = 1.0;
    LightLut_FromFunc(&lutShittyFresnel, badFresnel, lightStrengthFresnel, false);
    C3D_LightEnvLut(&lightEnv, GPU_LUT_FR, GPU_LUTINPUT_NV, false, &lutShittyFresnel);
    C3D_LightEnvFresnel(&lightEnv, GPU_PRI_SEC_ALPHA_FRESNEL);
    
    // Basic shading with diffuse + specular
    C3D_FVec lightVec = FVec4_New(0.0, 0.0, 0.0, 1.0);
    C3D_LightInit(&light, &lightEnv);
    C3D_LightColor(&light, 1.0, 1.0, 1.0);
    C3D_LightPosition(&light, &lightVec);

    C3D_Material lightMaterial = {
        { 0.2, 0.2, 0.2 }, //ambient
        { 1.0,  1.0,  1.0 }, //diffuse
        { 1.0f, 1.0f, 1.0f }, //specular0
        { 0.0f, 0.0f, 0.0f }, //specular1
        { 0.0f, 0.0f, 0.0f }, //emission
    };
    C3D_LightEnvMaterial(&lightEnv, &lightMaterial);

    // Set up texture combiners
    C3D_TexEnv* env = C3D_GetTexEnv(0);
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

    // GPU state for normal drawing with transparency
    C3D_DepthTest(true, GPU_GEQUAL, GPU_WRITE_ALL);
    C3D_CullFace(GPU_CULL_BACK_CCW);
    C3D_AlphaBlend(GPU_BLEND_ADD, GPU_BLEND_ADD, GPU_SRC_ALPHA, GPU_ONE_MINUS_SRC_ALPHA, GPU_SRC_ALPHA, GPU_ONE_MINUS_SRC_ALPHA);

    // Actual drawcall
    C3D_DrawArrays(GPU_TRIANGLES, 0, model->vertCount);
}

void effectStreetRender(C3D_RenderTarget* targetLeft, C3D_RenderTarget* targetRight, float row, float iod) {
    // Frame starts (TODO pull out?)
    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

    // Send modelview
    C3D_Mtx modelview;
    Mtx_Identity(&modelview);
    Mtx_Translate(&modelview, 0.0, -1.0, -4.0, true);
    Mtx_RotateZ(&modelview, M_PI, true);
    Mtx_RotateY(&modelview, row * 0.1, true);
    C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, uLocModelview,  &modelview);

    // Left eye
    C3D_FrameDrawOn(targetLeft);
    C3D_RenderTargetClear(targetLeft, C3D_CLEAR_ALL, 0xff0000FF, 0);
    
    Mtx_PerspStereoTilt(&projection, 70.0f*M_PI/180.0f, 300.0f/240.0f, 0.01f, 6000.0f, -iod,  7.0f, false);
    C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, uLocProjection, &projection);

    // Dispatch drawcalls
    //waitForA("Dispatching");
    drawModel(&modelCar, row);
    drawModel(&modelStreet, row);

    // Do fading
    //fade();

    // Right eye?
    if(iod > 0.0) {
        C3D_FrameDrawOn(targetRight);
        C3D_RenderTargetClear(targetRight, C3D_CLEAR_ALL, 0x00ff00FF, 0); 
        
        Mtx_PerspStereoTilt(&projection, 70.0f*M_PI/180.0f, 300.0f/240.0f, 0.01f, 6000.0f, iod, 7.0f, false);
        C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, uLocProjection, &projection);

        // Dispatch drawcalls
        drawModel(&modelCar, row);
        drawModel(&modelStreet, row);

        // Perform fading
        //fade();
    }

    // Swap
    C3D_FrameEnd(0);
}

void effectStreetExit() {
    // TODO free ressources here okay
}
