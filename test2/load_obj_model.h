#if !defined(LOAD_OBJ_MODEL_H)
#define LOAD_OBJ_MODEL_H

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>

#include "bitmap.h"
#include "gl2.h"
#include "model_obj.h"
#include "resource.h"
#include "WGL_ARB_multisample.h"

// GL_EXT_texture_filter_anisotropic
#define GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE

#define CAMERA_FOVY  60.0f
#define CAMERA_ZFAR  10.0f
#define CAMERA_ZNEAR 0.1f

typedef std::map<std::string, GLuint> ModelTextures;

//prototype
void    DrawModelUsingFixedFuncPipeline(ModelOBJ *g_model, ModelTextures *g_modelTextures, bool g_enableTextures,
  int windowWidth, int windowHeight, double *glpapa);

void	LoadModelInit(const char* filename,  ModelOBJ *g_model, ModelTextures *g_modelTextures);
void    LoadModel(const char *Filename, ModelOBJ *g_model, ModelTextures *g_modelTextures, float g_maxAnisotrophy);
GLuint  LoadTexture(const char *Filename, ModelTextures g_modelTextures, float g_maxAnisotrophy);

#endif
