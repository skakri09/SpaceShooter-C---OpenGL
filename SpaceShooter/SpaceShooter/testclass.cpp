////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//#include <tool_force_includes.h>
#include <lib3ds/atmosphere.h>
#include <lib3ds/background.h>
#include <lib3ds/camera.h>
#include <lib3ds/chunk.h>
#include <lib3ds/chunktable.h>
#include <lib3ds/ease.h>
#include <lib3ds/file.h>
#include <lib3ds/io.h>
#include <lib3ds/light.h>
#include <lib3ds/material.h>
#include <lib3ds/matrix.h>
#include <lib3ds/mesh.h>
#include <lib3ds/node.h>
#include <lib3ds/quat.h>
#include <lib3ds/shadow.h>
#include <lib3ds/tcb.h>
#include <lib3ds/tracks.h>
#include <lib3ds/types.h>
#include <lib3ds/vector.h>
#include <lib3ds/viewport.h>


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// lib3ds helpers

Lib3dsMesh*     lib3ds_file_get_meshes   (Lib3dsFile *file) { return file->meshes;    }
Lib3dsMaterial* lib3ds_file_get_materials(Lib3dsFile *file) { return file->materials; }
unsigned int    lib3ds_file_get_num_meshes(Lib3dsFile *file)
{
        unsigned int i = 0;
        for (Lib3dsMesh* m = file->meshes; m != null; m = m_->next, i++) ;
        return i;
}
unsigned int    lib3ds_file_get_num_materials(Lib3dsFile *file)
{
        unsigned int i = 0;
        for (Lib3dsMaterial* m = file->materials; m != null; m = m->next, i++) ;
        return i;
}

const char* lib3ds_texture_get_name(Lib3dsTextureMap* t) { return t->name; }

float*           lib3ds_material_get_ambient  (Lib3dsMaterial *mat) { return mat->ambient;      }
float*           lib3ds_material_get_diffuse  (Lib3dsMaterial *mat) { return mat->diffuse;      }
float*           lib3ds_material_get_specular (Lib3dsMaterial *mat) { return mat->specular;     }
float            lib3ds_material_get_shine    (Lib3dsMaterial *mat) { return mat->shininess;    }
Lib3dsTextureMap lib3ds_material_get_texture  (Lib3dsMaterial *mat) { return mat->texture1_map; }
Lib3dsMaterial*  lib3ds_material_get_next     (Lib3dsMaterial *mat) { return mat->next;         }

Lib3dsVector*    lib3ds_mesh_get_points       (Lib3dsMesh *mesh)    { return (Lib3dsVector*)(mesh->pointL); }
Lib3dsDword      lib3ds_mesh_get_num_points   (Lib3dsMesh *mesh)    { return mesh->points; }
Lib3dsDword      lib3ds_mesh_get_num_texcoords(Lib3dsMesh *mesh)    { return mesh->texels; }
Lib3dsTexel*     lib3ds_mesh_get_texcoords    (Lib3dsMesh *mesh)    { return mesh->texelL; }
Lib3dsDword      lib3ds_mesh_get_num_faces    (Lib3dsMesh *mesh)    { return mesh->faces;  }
Lib3dsFace*      lib3ds_mesh_get_faces        (Lib3dsMesh *mesh)    { return mesh->faceL;  }
const char*      lib3ds_mesh_get_name         (Lib3dsMesh *mesh)    { return mesh->name;   }
Lib3dsMesh*      lib3ds_mesh_get_next         (Lib3dsMesh *mesh)    { return mesh->next;   }
                                                                    
color            Lib3dsRgba_to_color          (Lib3dsRgba x)        { return color(x[3], x[0], x[1], x[2]); }

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

const unsigned int MAX_MATERIALS = 1024;
const unsigned int MAX_MESHES    = 1024;

static struct {
        char In[512];
        char Out[512];
        char Name[512];

        MES*H     Meshes[MAX_MESHES];
        unsigned int      NumMeshes;
} Data; 

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#define CHECK(x, msg) \
        if (x == null) { \
                Console::Print(msg "!\n", filename); \
                return null; \
        }

void doMaterial(Lib3dsMaterial* m, MATERIAL* mat)
{
        assert_pointer(m);
        assert_pointer(mat);
        Console::Print("material : %s\n\t"
                       "texture1_map : %s\n\t"
                       "texture1_mask : %s\n\t"
                       "texture2_map : %s\n\t"
                       "texture2_mask : %s\n\t"
                       "opacity_map : %s\n\t"
                       "opacity_mask : %s\n\t"
                       "bump_map : %s\n\t"
                       "bump_mask : %s\n\t"
                       "specular_map : %s\n\t"
                       "specular_mask : %s\n\t"
                       "shininess_map : %s\n\t"
                       "shininess_mask : %s\n\t"
                       "self_illum_map : %s\n\t"
                       "self_illum_mask : %s\n\t"
                       "reflection_map : %s\n\t"
                       "reflection_mask : %s\n\t"
                       , m->name,
                       m->texture1_map.name,
                       m->texture1_mask.name,
                       m->texture2_map.name,
                       m->texture2_mask.name,
                       m->opacity_map.name,
                       m->opacity_mask.name,
                       m->bump_map.name,
                       m->bump_mask.name,
                       m->specular_map.name,
                       m->specular_mask.name,
                       m->shininess_map.name,
                       m->shininess_mask.name,
                       m->self_illum_map.name,
                       m->self_illum_mask.name,
                       m->reflection_map.name,
                       m->reflection_mask.name);


        color ambient        = Lib3dsRgba_to_color( lib3ds_material_get_ambient(m)  );
        color diffuse        = Lib3dsRgba_to_color( lib3ds_material_get_diffuse(m)  );
        color specular       = Lib3dsRgba_to_color( lib3ds_material_get_specular(m) );
        float shine          = lib3ds_material_get_shine(m);
        ident tex(m->texture1_map.name);

        mat->Set(ambient, diffuse, specular, shine, tex);
}

void doMesh(Lib3dsMesh* m, Lib3dsMaterial* material, VERTEX* vertices, INDEX* indices, unsigned int* vertexOffset, unsigned int* indexOffset)
{
        assert_pointer(m);
        assert_pointer(material);
        assert_pointer(vertices);
        assert_pointer(indices);
        assert_pointer(vertexOffset);
        assert_pointer(indexOffset);

        // make vertices
        unsigned int numVertices;
        {
                vector3* points    = (vector3*)lib3ds_mesh_get_points(m);
                unsigned int     numPoints = (unsigned int)lib3ds_mesh_get_num_points(m);
                numVertices        = numPoints;

                if ((points == null) || (numPoints < 1)) {
                        Console::Print("error: points == null\n");
                        return;
                }

                vector2* texCoords    = (vector2*)lib3ds_mesh_get_texcoords(m);
                unsigned int     numTexCoords = (unsigned int)lib3ds_mesh_get_num_texcoords(m);

                bool useTexCoords = (numPoints == numTexCoords) ? true : false;

                for (int i=0; i<numPoints; i++) {
                        vertices[i + *vertexOffset].Pos      = points[i];
                        vertices[i + *vertexOffset].TexCoord = (useTexCoords) ? texCoords[i] : vector2(0,0);
                        vertices[i + *vertexOffset].Normal   = vector3(0,0,0);
                        vertices[i + *vertexOffset].Color    = 0;
                }
        }

        // make indices
        unsigned int numIndices;
        {
                unsigned int     numFaces     = (unsigned int)lib3ds_mesh_get_num_faces(m);
                Lib3dsFace* faces     = lib3ds_mesh_get_faces(m);
                numIndices = numFaces * 3;

                if (numFaces == 0) {
                        Console::Print("error: numFaces is zero in mesh %s!\n", lib3ds_mesh_get_name(m));
                        return;
                }

                for (int i=0; i<numFaces; i++) {
                        indices[i*3 + 0 + *indexOffset] = (INDEX) faces[i].points[0] + *vertexOffset;
                        indices[i*3 + 1 + *indexOffset] = (INDEX) faces[i].points[1] + *vertexOffset;
                        indices[i*3 + 2 + *indexOffset] = (INDEX) faces[i].points[2] + *vertexOffset;
                }
        }

        // set vertex colors
        {
                unsigned int     numFaces     = (unsigned int)lib3ds_mesh_get_num_faces(m);
                Lib3dsFace* faces     = lib3ds_mesh_get_faces(m);

                for (u32 x=0; x<numVertices; x++) {
                        unsigned int count = 0;
                        color c(0,0,0,0);

                        for (int i=0; i<numFaces; i++) {
                                if ( ((INDEX) faces[i].points[0] == x) ||
                                     ((INDEX) faces[i].points[1] == x) ||
                                     ((INDEX) faces[i].points[2] == x) ) {
                                        // avg color
                                        c += color(material->diffuse[3],
                                                   material->diffuse[0],
                                                   material->diffuse[1],
                                                   material->diffuse[2]);
                                        count++;
                                }
                        }

                        c *= 1.0 / (float)count;
                        vertices[x + *vertexOffset].Color = c.GetAsU32();
                }
        }

        *vertexOffset += numVertices;
        *indexOffset  += numIndices;
}

MESH* doMeshList(Lib3dsMesh* m, Lib3dsMaterial* mat)
{
        assert_pointer(m);
        assert_pointer(mat);

        // figure out size
        unsigned int numVertices=0, numIndices=0;
        for (Lib3dsMesh* i=m; i != null; i=i->next) {
                numVertices += (unsigned int)lib3ds_mesh_get_num_points(i);
                numIndices  += (unsigned int)lib3ds_mesh_get_num_faces (i) * 3;
        }

        // alloc temp memory
        VERTEX* vertices = (VERTEX*) MEM::Alloc(sizeof(VERTEX) * numVertices);
        INDEX*  indices  = (INDEX* ) MEM::Alloc(sizeof(INDEX)  * numIndices );
        assert_pointer(vertices);
        assert_pointer(indices);

        // for each mesh
        //   extract data
        unsigned int vertexOffset=0, indexOffset=0;
        for (Lib3dsMesh* i=m; i != null; i=i->next) {
                doMesh(i, mat, vertices, indices, &vertexOffset, &indexOffset);
        }
        assert(vertexOffset == numVertices);
        assert(indexOffset  == numIndices );

        // convert the material data
        MATERIAL mat2;
        doMaterial(mat, &mat2);

        // create mesh
        MESH* rtn = MESH::Create(&mat2, numVertices, vertices, numIndices, indices);

        MEM::Free(vertices);
        MEM::Free(indices);

        if (rtn == null) {
                Console::Print("error: unable to create MESH!\n");
                return null;
        } else {
                rtn->GenerateNormals();
//PNC: add this as some type of extra info output like +info_level:1
//              Console::Print("processed mesh %s.\n", lib3ds_mesh_get_name(m));
                return rtn;
        }
}

Lib3dsMesh* buildList(Lib3dsMesh* meshes, Lib3dsMaterial* material)
{
        Lib3dsMesh* rtn = null;

        //
        // for each mesh
        //   if the first face uses this material
        //     remove from main list
        //     add to new list
        //
        for (Lib3dsMesh* i=meshes->next; i != null;) {
                if (MEM::StringCompare(material->name, i->faceL->material)) {
                        // remove from list
                        meshes->next = i->next;
                        i->next      = null;

                        // add to end of new list
                        if (rtn == null) {
                                rtn = i;
                        } else {
                                Lib3dsMesh* end;
                                for (end=rtn; end->next != null; end=end->next) ;
                                end->next = i;
                        }

                        i = meshes->next;
                } else {
                        i      = i->next;
                        meshes = meshes->next;
                }
        }

        return rtn;
}

MODEL_RESOURCE* do3ds(const char* filename)
{
        Console::SetPrintHeader("|3dsconvert| [File:%s] ", filename);
        
        Lib3dsFile*     file = lib3ds_file_load(filename);
        Lib3dsMaterial* mat  = lib3ds_file_get_materials(file);
        Lib3dsMesh*     mesh = lib3ds_file_get_meshes(file);
        CHECK(file, "could not open 3ds file");
        CHECK(mat , "no material list in file");
        CHECK(mesh, "no mesh list in file");

        // add a dummy head to the mesh list so we can delete easier
        Lib3dsMesh tmp; 
        zero(&tmp);
        tmp.next = mesh;
        mesh = &tmp;

        //
        // for each material
        //   build a list of all the meshes associated with it
        //   build dest mesh data from meshes list
        //
        
        int i;
        for (i=0; (mat != null) && (i<MAX_MESHES); mat = mat->next) {
                Lib3dsMesh* list = buildList(mesh, mat);
                if (list == null) continue;

                Data.Meshes[Data.NumMeshes] = doMeshList(list, mat);
                if (Data.Meshes[Data.NumMeshes] != null) {
                        Data.NumMeshes++;
                } else {
                        Console::Print("Unable to process mesh list for material %s!!\n", mat->name);
                }
        }

        if (i >= MAX_MESHES) {
                Console::Print("Error: model has more materials than the max %d in it!\n", MAX_MESHES);
                return null;
        }

        if (Data.NumMeshes == 0) {
                Console::Print("No valid meshes in file %s to save!\n", filename);
                return null;
        }

        //
        // add in all meshes without a material to a default material dest mesh
        //

        if (mesh->next != null) {
                Lib3dsMaterial defaultMaterial;
                zero(&defaultMaterial);
                MEM::StringCopy(defaultMaterial.name, "default", 64);
                defaultMaterial.diffuse[0] = 0.6;
                defaultMaterial.diffuse[1] = 0.6;
                defaultMaterial.diffuse[2] = 0.6;
                defaultMaterial.diffuse[3] = 1.0;
                defaultMaterial.shininess  = 1.0;

                Data.Meshes[Data.NumMeshes] = doMeshList(mesh->next, &defaultMaterial);
                if (Data.Meshes[Data.NumMeshes] != null) {
                        Data.NumMeshes++;
                } else {
                        Console::Print("Unable to process mesh list for default material!!\n");
                }
        }

        //
        // now save off all created data to a resource
        //

        // figure out the size for the meshes
        unsigned int meshSize = 0;
        for (int i=0; i<Data.NumMeshes; i++) {
                meshSize += Data.Meshes[i]->GetStorageSize();
        }

        // allocate and store the mesh
        void* meshArray = MEM::Alloc(meshSize);
        for (int i=0, off=0; i<Data.NumMeshes; i++) {
                MEM::Copy((u8*)meshArray + off, Data.Meshes[i], Data.Meshes[i]->GetStorageSize());
                off+=Data.Meshes[i]->GetStorageSize();
        }

        MODEL_RESOURCE* rtn = MODEL_RESOURCE::Create(Data.Name, Data.NumMeshes, (MESH*)meshArray, meshSize);

        return rtn;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

TOOL_DATA ToolData;

bool SetInput(const char* in)
{
        MEM::StringCopy(Data.In, in, 512);
        return true;
}

bool SetOutput(const char* in)
{
        MEM::StringCopy(Data.Out, in, 512);
        return true;
}

bool SetName(const char* in)
{
        MEM::StringCopy(Data.Name, in, 512);
        return true;
}

TOOL_CMD Cmds[] = {
        // { name, default, description, required, allow multi, callback }
        { "in", null, "input file", true, false, SetInput },
        { "out", null, "output file", true, false, SetOutput },
        { "name", null, "model name", true, false, SetName },
        { null, null, null, false, false, null },
};

void InitTool()
{
        zero(&Data);
        ToolData.CmdList = Cmds;
}

bool ToolMain()
{
        MODEL_RESOURCE* m = do3ds(Data.In);

        if (m == null) {
                return false;
        } else {
                // save this model out to a resource file
                if (!RESOURCE::SaveResourcesToFile(Data.Out, (RESOURCE*)m)) {
                        Console::Print("Could not save to file %s!\n", Data.Out);
                        return false;
                }
//              Console::Print("Number of Meshes %d\n", Data.NumMeshes);
                Console::Print("Built File Sucessfully\n");
                return true;
        }
}