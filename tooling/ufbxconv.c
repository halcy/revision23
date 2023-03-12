#include <stdio.h>
#include <stdlib.h>
#include "ufbx.h"

#define TOOLS_BASICS_ONLY
#include "Tools.h"

fbxBasedObject loadFBXObject(const char* filename, const char* objectName) {
    // Output object
    fbxBasedObject objectNew;

    // Load data
    ufbx_load_opts opts = { 0 }; // Optional, pass NULL for defaults
    ufbx_error error; // Optional, pass NULL if you don't care about errors
    ufbx_scene *scene = ufbx_load_file(filename, &opts, &error);
    if (!scene) {
        fprintf(stderr, "Failed to load: %s\n", error.description.data);
        return objectNew;
    }

    // Go through all objects in the scene
    for (size_t i = 0; i < scene->nodes.count; i++) {
        ufbx_node *node = scene->nodes.data[i];
        if (node->is_root) continue;

        // Bail if not the right name
        if(strncmp(node->name.data, objectName, 255) != 0) {
            continue;
        }

        // We can only load meshes
        if (node->mesh) {
            // Mesh and skin objects for convenience
            ufbx_mesh* mesh = node->mesh;
            ufbx_skin_deformer* skin = mesh->skin_deformers.data[0];

            // Alloc VBO data struct
            int totalVerts = mesh->faces.count * 3;
            objectNew.vbo = (vertex_rigged*)malloc(sizeof(vertex_rigged) * totalVerts);
            objectNew.vertCount = totalVerts;

            // Go through all faces
            size_t setVertIdx = 0;
            for (size_t faceIdx = 0; faceIdx < mesh->faces.count; faceIdx++) {
                // We support only triangles, please triangulate on export Or Else
                if(mesh->faces.data[faceIdx].num_indices != 3) {
                    // Complain and skip
                    printf("Yikes! Non-tri face at %ld\n", faceIdx);
                    continue;
                }

                // Get the mesh data
                size_t faceFirstVertIdx = mesh->faces.data[faceIdx].index_begin;
                for (size_t vertIdx = faceFirstVertIdx; vertIdx < faceFirstVertIdx + 3; vertIdx++) {
                    // Standard geometry data
                    ufbx_vec3 pos = ufbx_get_vertex_vec3(&mesh->vertex_position, vertIdx);
                    ufbx_vec3 normal = ufbx_get_vertex_vec3(&mesh->vertex_normal, vertIdx);
                    ufbx_vec2 uv = ufbx_get_vertex_vec2(&mesh->vertex_uv, vertIdx);

                    // Them bones. Of which we support two. More are possible at increased cost.
                    ufbx_vec2 boneIdx;
                    ufbx_vec2 boneWgt;

                    ufbx_skin_vertex* vertSkinData = &skin->vertices.data[mesh->vertex_indices.data[vertIdx]];
                    int numBones = vertSkinData->num_weights;
                    if(numBones >= 1) {
                        boneIdx.x = skin->weights.data[vertSkinData->weight_begin].cluster_index;
                        boneWgt.x = skin->weights.data[vertSkinData->weight_begin].weight;
                    }
                    if(numBones >= 2) {
                        boneIdx.y = skin->weights.data[vertSkinData->weight_begin + 1].cluster_index;
                        boneWgt.y = skin->weights.data[vertSkinData->weight_begin + 1].weight;
                    }

                    // Set the vertex
                    objectNew.vbo[setVertIdx].position[0] = pos.x;
                    objectNew.vbo[setVertIdx].position[1] = pos.y;
                    objectNew.vbo[setVertIdx].position[2] = pos.z;
                    objectNew.vbo[setVertIdx].bones[0] = boneIdx.x * 3.0;
                    objectNew.vbo[setVertIdx].bones[1] = boneIdx.y * 3.0;
                    objectNew.vbo[setVertIdx].boneWeights[0] = boneWgt.x;
                    objectNew.vbo[setVertIdx].boneWeights[1] = boneWgt.y;
                    objectNew.vbo[setVertIdx].normal[0] = normal.x;
                    objectNew.vbo[setVertIdx].normal[1] = normal.y;
                    objectNew.vbo[setVertIdx].normal[2] = normal.z;
                    objectNew.vbo[setVertIdx].texcoord[0] = uv.x;
                    objectNew.vbo[setVertIdx].texcoord[1] = uv.y;
                    setVertIdx += 1;
                }
            }

            // Is there an animation?
            if(scene->anim_stacks.count == 1) {
                ufbx_anim_stack* anim_stack = scene->anim_stacks.data[0];
                
                // We assume 60fps
                float frameDur = 1.0 / 60.0;
                size_t frameCount = (size_t)((anim_stack->anim.time_end - anim_stack->anim.time_begin) * 60.0 + 0.5);
                size_t boneCount = skin->clusters.count;

                // Alloc data for frames
                objectNew.frameCount = frameCount;
                objectNew.boneCount = boneCount;
                objectNew.animFrames = (float*)malloc(sizeof(float) * frameCount * boneCount * 12);

                // Copy every frame
                for(size_t frame = 0; frame < frameCount; frame++) {
                    // Get every bones transform for the frame
                    for(size_t boneIdx = 0; boneIdx < boneCount; boneIdx++) {
                        ufbx_node* bone = skin->clusters.data[boneIdx]->bone_node;
                        float frameTime = anim_stack->anim.time_begin + frame * frameDur;
                        ufbx_transform transform = ufbx_evaluate_transform(&anim_stack->anim, bone, frameTime);
                        ufbx_matrix transformMatLocal = ufbx_transform_to_matrix(&transform);
                        ufbx_matrix transformMat = ufbx_matrix_mul(&transformMatLocal, &node->node_to_world);
                        
                        for(int i = 0; i < 12; i++) {
                            // The FBX matrices are not in the order in which we need them to be, fix that
                            int irev = 11 - i;
                            int x = irev % 4;
                            int y = irev / 4;
                            int yrev = 2 - y;
                            int itransp = x * 3 + yrev;

                            // Switch homogenous part around and flip sign of Y.
                            int iset = i;
                            float sign = 1.0;
                            if(iset == 0) {
                                iset = 4;                             
                            } else if(iset == 4) {
                                iset = 0;
                                sign = -1.0;                         
                            } else if(iset == 8) {
                                iset = 8;
                                sign = -1.0;                                
                            } else {
                                // Scale nonhomogenous part down by a factor of 100.
                                sign /= 100.0;
                            }

                            // Set transposed matrix
                            objectNew.animFrames[FBX_FRAME_IDX(frame, boneIdx, iset, boneCount)] = transformMat.v[itransp] * sign;
                        }
                        printf("%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n\n",
                            objectNew.animFrames[FBX_FRAME_IDX(frame, boneIdx, 0, boneCount)],
                            objectNew.animFrames[FBX_FRAME_IDX(frame, boneIdx, 1, boneCount)],
                            objectNew.animFrames[FBX_FRAME_IDX(frame, boneIdx, 2, boneCount)],
                            objectNew.animFrames[FBX_FRAME_IDX(frame, boneIdx, 3, boneCount)],
                            objectNew.animFrames[FBX_FRAME_IDX(frame, boneIdx, 4, boneCount)],
                            objectNew.animFrames[FBX_FRAME_IDX(frame, boneIdx, 5, boneCount)],
                            objectNew.animFrames[FBX_FRAME_IDX(frame, boneIdx, 6, boneCount)],
                            objectNew.animFrames[FBX_FRAME_IDX(frame, boneIdx, 7, boneCount)],
                            objectNew.animFrames[FBX_FRAME_IDX(frame, boneIdx, 8, boneCount)],
                            objectNew.animFrames[FBX_FRAME_IDX(frame, boneIdx, 9, boneCount)],
                            objectNew.animFrames[FBX_FRAME_IDX(frame, boneIdx, 10, boneCount)],
                            objectNew.animFrames[FBX_FRAME_IDX(frame, boneIdx, 11, boneCount)]
                        );
                    }
                }
            }
        }
    }
    
    return objectNew;
}

void serializeObject(fbxBasedObject* object, const char* filename) {
    FILE* fp = fopen(filename, "wb");
    if (fp == NULL) {
        fprintf(stderr, "Error: failed to open file for writing.\n");
        exit(1);
    }

    // Write the vertCount and frameCount to the file
    fwrite(&object->vertCount, sizeof(int32_t), 1, fp);
    fwrite(&object->boneCount, sizeof(int32_t), 1, fp);
    fwrite(&object->frameCount, sizeof(int32_t), 1, fp);

    // Write the vbo to the file
    fwrite(object->vbo, sizeof(vertex_rigged), object->vertCount, fp);

    // Write the animFrames to the file
    fwrite(object->animFrames, sizeof(float), object->frameCount * object->boneCount * 12, fp);

    fclose(fp);
}

int main(int argc, char** argv) {
    if(argc < 4) {
        printf("usage: ufbxconv infile.fbs outfile.bin\n");
        exit(1);
    }
    const char* infile = argv[1];
    const char* name = argv[2];
    const char* outfile = argv[3];
    printf("Converting: %s from %s to %s.\n", name, infile, outfile);

    fbxBasedObject object = loadFBXObject(infile, name);
    printf("Have %d vertices, %d anim frames.\n", object.vertCount, object.frameCount);

    serializeObject(&object, outfile);
}
