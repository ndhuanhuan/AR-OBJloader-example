#include "load_obj_model.h"

// Load the model from file
void LoadModel(const char *file_name, ModelOBJ *g_model, ModelTextures *g_modelTextures, float g_maxAnisotrophy)
{
  if(!g_model->import(file_name))
	{
		printf("error in load model\n");
	}

	g_model->normalize();
	printf("number of meshes: %d\n",g_model->getNumberOfMeshes());

	//Load any associated textures
	//Note the path where the textures are assumed to be located
	const ModelOBJ::Material *pMaterial = 0;
	GLuint textureId = 0;
	std::string::size_type offset = 0;
	std::string filename;

	for (int i = 0; i < g_model->getNumberOfMaterials(); ++i)
    {
        pMaterial = &g_model->getMaterial(i);

        // Look for and load any diffuse color map textures.

        if (pMaterial->colorMapFilename.empty()){
			printf("color map file empty\n");
            continue;
		}

        // Try load the texture using the path in the .MTL file.
        textureId = LoadTexture(pMaterial->colorMapFilename.c_str(), *g_modelTextures, g_maxAnisotrophy);

        if (!textureId)
        {
            offset = pMaterial->colorMapFilename.find_last_of('\\');

            if (offset != std::string::npos)
                filename = pMaterial->colorMapFilename.substr(++offset);
            else
                filename = pMaterial->colorMapFilename;

            // Try loading the texture from the same directory as the OBJ file.
            textureId = LoadTexture((g_model->getPath() + filename).c_str(), *g_modelTextures, g_maxAnisotrophy);
        }

        if (textureId)
            (*g_modelTextures)[pMaterial->colorMapFilename] = textureId;

        // Look for and load any normal map textures.

        if (pMaterial->bumpMapFilename.empty())
            continue;

        // Try load the texture using the path in the .MTL file.
        textureId = LoadTexture(pMaterial->bumpMapFilename.c_str(), *g_modelTextures, g_maxAnisotrophy);

        if (!textureId)
        {
            offset = pMaterial->bumpMapFilename.find_last_of('\\');

            if (offset != std::string::npos)
                filename = pMaterial->bumpMapFilename.substr(++offset);
            else
                filename = pMaterial->bumpMapFilename;

            // Try loading the texture from the same directory as the OBJ file.
            textureId = LoadTexture((g_model->getPath() + filename).c_str(), *g_modelTextures, g_maxAnisotrophy);
        }

        if (textureId)
            (*g_modelTextures)[pMaterial->bumpMapFilename] = textureId;
    }
}

GLuint LoadTexture(const char *file_name, ModelTextures g_modelTextures, float g_maxAnisotrophy)
{
	GLuint id = 0;
	Bitmap bitmap;

	if (bitmap.loadPicture(file_name))
	{
	    	bitmap.flipVertical();
		
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        if (g_maxAnisotrophy > 1.0f)
        {
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT,
                g_maxAnisotrophy);
        }

        gluBuild2DMipmaps(GL_TEXTURE_2D, 4, bitmap.width, bitmap.height,
            GL_BGRA_EXT, GL_UNSIGNED_BYTE, bitmap.getPixels());
    }

    return id;
}

void DrawModelUsingFixedFuncPipeline(ModelOBJ *g_model, ModelTextures *g_modelTextures, bool g_enableTextures,
	int windowWidth, int windowHeight, double *gl_para)
{
    const ModelOBJ::Mesh *pMesh = 0;
    const ModelOBJ::Material *pMaterial = 0;
    const ModelOBJ::Vertex *pVertices = 0;

    float g_cameraPos[3];
	  float g_targetPos[3];
	  GLfloat   light_position[]  = {100.0, 200.0, -600.0,0.0};
	  GLfloat   ambi[]            = {0.1, 0.1, 0.1, 0.1};
    GLfloat   lightZeroColor[]  = {0.9, 0.9, 0.9, 0.1};

    ModelTextures::const_iterator iter;

	  glEnable(GL_NORMALIZE);
	  glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);


	  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambi);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightZeroColor);


	  //get the center of the model
	  g_model->getCenter(g_targetPos[0], g_targetPos[1], g_targetPos[2]);
    g_cameraPos[0] = g_targetPos[0];
    g_cameraPos[1] = g_targetPos[1];
    g_cameraPos[2] = g_targetPos[2] + g_model->getRadius() + CAMERA_ZNEAR + 0.4f;

	  glMatrixMode(GL_MODELVIEW);
	  glLoadMatrixd(gl_para);
	  glTranslatef(0.0f-g_targetPos[0], 0.0f-g_targetPos[1]+25.0f, 0.0f-g_targetPos[2]+25.0f);
	  glScalef(120.0f,120.0f,120.0f);
	  glRotatef(90.0f, 1.0f, 0.0f,0.0f);
	  glRotatef(180.0f, 0.0f, 1.0f,0.0f);

    for (int i = 0; i < g_model->getNumberOfMeshes(); ++i)
    {
        pMesh = &g_model->getMesh(i);
        pMaterial = pMesh->pMaterial;
        pVertices = g_model->getVertexBuffer();

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, pMaterial->ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, pMaterial->diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, pMaterial->specular);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, pMaterial->shininess * 128.0f);

        if (g_enableTextures)
        {
            iter = g_modelTextures->find(pMaterial->colorMapFilename);

            if (iter == g_modelTextures->end())
            {
                glDisable(GL_TEXTURE_2D);
            }
            else
            {
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, iter->second);
            }
		}
        else
        {
            glDisable(GL_TEXTURE_2D);
        }

        if (g_model->hasPositions())
        {
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(3, GL_FLOAT, g_model->getVertexSize(),
                g_model->getVertexBuffer()->position);
        }

        if (g_model->hasTextureCoords())
        {
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer(2, GL_FLOAT, g_model->getVertexSize(),
                g_model->getVertexBuffer()->texCoord);
        }

        if (g_model->hasNormals())
        {
            glEnableClientState(GL_NORMAL_ARRAY);
            glNormalPointer(GL_FLOAT, g_model->getVertexSize(),
                g_model->getVertexBuffer()->normal);
        }

        glDrawElements(GL_TRIANGLES, pMesh->triangleCount * 3, GL_UNSIGNED_INT,
            g_model->getIndexBuffer() + pMesh->startIndex);

        if (g_model->hasNormals())
            glDisableClientState(GL_NORMAL_ARRAY);

        if (g_model->hasTextureCoords())
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);

        if (g_model->hasPositions())
            glDisableClientState(GL_VERTEX_ARRAY);
    }

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
	glDisable(GL_NORMALIZE);

	printf("model drawn\n");
}

void LoadModelInit(const char* filename, ModelOBJ *g_model, ModelTextures *g_modelTextures)
{
	  GL2Init();

	  LoadModel(filename, g_model, g_modelTextures, 1.0f);
	  printf("model loaded!\n");
}
