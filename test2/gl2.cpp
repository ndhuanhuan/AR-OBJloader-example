//-----------------------------------------------------------------------------
// Copyright (c) 2006-2007 dhpoware. All Rights Reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------
//
// Porting Notes:
//
// This source file was written in Visual C++ 2005 for the Windows platform.
//
// However the only platform specific code is in the GL2Init() function where
// a local GPA() macro is defined which expands to wglGetProcAddress().
//
// Porting this file to another platform should only involve updating the GPA()
// macro to whatever the target platform uses to retrieve OpenGL function
// pointers.
// 
// Everything else is just standard C++.
//
//-----------------------------------------------------------------------------

// Disable CRT deprecated function warnings for Visual C++ 2005 and higher.
#if defined(_WIN32) && defined(_MSC_VER)
#   if _MSC_VER >= 1400 && !defined(_CRT_SECURE_NO_DEPRECATE)
#       define _CRT_SECURE_NO_DEPRECATE
#   endif
#endif

#include <cstdio>
#include "gl2.h"

// OpenGL 1.2.
PFNGLCOPYTEXSUBIMAGE3DPROC              glCopyTexSubImage3D;
PFNGLDRAWRANGEELEMENTSPROC              glDrawRangeElements;
PFNGLTEXIMAGE3DPROC                     glTexImage3D;
PFNGLTEXSUBIMAGE3DPROC                  glTexSubImage3D;

// OpenGL 1.3.
PFNGLACTIVETEXTUREPROC                  glActiveTexture;
PFNGLCLIENTACTIVETEXTUREPROC            glClientActiveTexture;
PFNGLCOMPRESSEDTEXIMAGE1DPROC           glCompressedTexImage1D;
PFNGLCOMPRESSEDTEXIMAGE2DPROC           glCompressedTexImage2D;
PFNGLCOMPRESSEDTEXIMAGE3DPROC           glCompressedTexImage3D;
PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC        glCompressedTexSubImage1D;
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC        glCompressedTexSubImage2D;
PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC        glCompressedTexSubImage3D;
PFNGLGETCOMPRESSEDTEXIMAGEPROC          glGetCompressedTexImage;
PFNGLLOADTRANSPOSEMATRIXDPROC           glLoadTransposeMatrixd;
PFNGLLOADTRANSPOSEMATRIXFPROC           glLoadTransposeMatrixf;
PFNGLMULTITEXCOORD1DPROC                glMultiTexCoord1d;
PFNGLMULTITEXCOORD1DVPROC               glMultiTexCoord1dv;
PFNGLMULTITEXCOORD1FPROC                glMultiTexCoord1f;
PFNGLMULTITEXCOORD1FVPROC               glMultiTexCoord1fv;
PFNGLMULTITEXCOORD1IPROC                glMultiTexCoord1i;
PFNGLMULTITEXCOORD1IVPROC               glMultiTexCoord1iv;
PFNGLMULTITEXCOORD1SPROC                glMultiTexCoord1s;
PFNGLMULTITEXCOORD1SVPROC               glMultiTexCoord1sv;
PFNGLMULTITEXCOORD2DPROC                glMultiTexCoord2d;
PFNGLMULTITEXCOORD2DVPROC               glMultiTexCoord2dv;
PFNGLMULTITEXCOORD2FPROC                glMultiTexCoord2f;
PFNGLMULTITEXCOORD2FVPROC               glMultiTexCoord2fv;
PFNGLMULTITEXCOORD2IPROC                glMultiTexCoord2i;
PFNGLMULTITEXCOORD2IVPROC               glMultiTexCoord2iv;
PFNGLMULTITEXCOORD2SPROC                glMultiTexCoord2s;
PFNGLMULTITEXCOORD2SVPROC               glMultiTexCoord2sv;
PFNGLMULTITEXCOORD3DPROC                glMultiTexCoord3d;
PFNGLMULTITEXCOORD3DVPROC               glMultiTexCoord3dv;
PFNGLMULTITEXCOORD3FPROC                glMultiTexCoord3f;
PFNGLMULTITEXCOORD3FVPROC               glMultiTexCoord3fv;
PFNGLMULTITEXCOORD3IPROC                glMultiTexCoord3i;
PFNGLMULTITEXCOORD3IVPROC               glMultiTexCoord3iv;
PFNGLMULTITEXCOORD3SPROC                glMultiTexCoord3s;
PFNGLMULTITEXCOORD3SVPROC               glMultiTexCoord3sv;
PFNGLMULTITEXCOORD4DPROC                glMultiTexCoord4d;
PFNGLMULTITEXCOORD4DVPROC               glMultiTexCoord4dv;
PFNGLMULTITEXCOORD4FPROC                glMultiTexCoord4f;
PFNGLMULTITEXCOORD4FVPROC               glMultiTexCoord4fv;
PFNGLMULTITEXCOORD4IPROC                glMultiTexCoord4i;
PFNGLMULTITEXCOORD4IVPROC               glMultiTexCoord4iv;
PFNGLMULTITEXCOORD4SPROC                glMultiTexCoord4s;
PFNGLMULTITEXCOORD4SVPROC               glMultiTexCoord4sv;
PFNGLMULTTRANSPOSEMATRIXDPROC           glMultTransposeMatrixd;
PFNGLMULTTRANSPOSEMATRIXFPROC           glMultTransposeMatrixf;
PFNGLSAMPLECOVERAGEPROC                 glSampleCoverage;

// OpenGL 1.4.
PFNGLBLENDFUNCSEPARATEPROC              glBlendFuncSeparate;
PFNGLMULTIDRAWARRAYSPROC                glMultiDrawArrays;
PFNGLMULTIDRAWELEMENTSPROC              glMultiDrawElements;
PFNGLPOINTPARAMETERFPROC                glPointParameterf;
PFNGLPOINTPARAMETERFVPROC               glPointParameterfv;
PFNGLSECONDARYCOLOR3BPROC               glSecondaryColor3b;
PFNGLSECONDARYCOLOR3BVPROC              glSecondaryColor3bv;
PFNGLSECONDARYCOLOR3DPROC               glSecondaryColor3d;
PFNGLSECONDARYCOLOR3DVPROC              glSecondaryColor3dv;
PFNGLSECONDARYCOLOR3FPROC               glSecondaryColor3f;
PFNGLSECONDARYCOLOR3FVPROC              glSecondaryColor3fv;
PFNGLSECONDARYCOLOR3IPROC               glSecondaryColor3i;
PFNGLSECONDARYCOLOR3IVPROC              glSecondaryColor3iv;
PFNGLSECONDARYCOLOR3SPROC               glSecondaryColor3s;
PFNGLSECONDARYCOLOR3SVPROC              glSecondaryColor3sv;
PFNGLSECONDARYCOLOR3UBPROC              glSecondaryColor3ub;
PFNGLSECONDARYCOLOR3UBVPROC             glSecondaryColor3ubv;
PFNGLSECONDARYCOLOR3UIPROC              glSecondaryColor3ui;
PFNGLSECONDARYCOLOR3UIVPROC             glSecondaryColor3uiv;
PFNGLSECONDARYCOLOR3USPROC              glSecondaryColor3us;
PFNGLSECONDARYCOLOR3USVPROC             glSecondaryColor3usv;
PFNGLSECONDARYCOLORPOINTERPROC          glSecondaryColorPointer;
PFNGLWINDOWPOS2DPROC                    glWindowPos2d;
PFNGLWINDOWPOS2DVPROC                   glWindowPos2dv;
PFNGLWINDOWPOS2FPROC                    glWindowPos2f;
PFNGLWINDOWPOS2FVPROC                   glWindowPos2fv;
PFNGLWINDOWPOS2IPROC                    glWindowPos2i;
PFNGLWINDOWPOS2IVPROC                   glWindowPos2iv;
PFNGLWINDOWPOS2SPROC                    glWindowPos2s;
PFNGLWINDOWPOS2SVPROC                   glWindowPos2sv;
PFNGLWINDOWPOS3DPROC                    glWindowPos3d;
PFNGLWINDOWPOS3DVPROC                   glWindowPos3dv;
PFNGLWINDOWPOS3FPROC                    glWindowPos3f;
PFNGLWINDOWPOS3FVPROC                   glWindowPos3fv;
PFNGLWINDOWPOS3IPROC                    glWindowPos3i;
PFNGLWINDOWPOS3IVPROC                   glWindowPos3iv;
PFNGLWINDOWPOS3SPROC                    glWindowPos3s;
PFNGLWINDOWPOS3SVPROC                   glWindowPos3sv;

// OpenGL 1.5.
PFNGLGENQUERIESPROC                     glGenQueries;
PFNGLDELETEQUERIESPROC                  glDeleteQueries;
PFNGLISQUERYPROC                        glIsQuery;
PFNGLBEGINQUERYPROC                     glBeginQuery;
PFNGLENDQUERYPROC                       glEndQuery;
PFNGLGETQUERYIVPROC                     glGetQueryiv;
PFNGLGETQUERYOBJECTIVPROC               glGetQueryObjectiv;
PFNGLGETQUERYOBJECTUIVPROC              glGetQueryObjectuiv;
PFNGLBINDBUFFERPROC                     glBindBuffer;
PFNGLDELETEBUFFERSPROC                  glDeleteBuffers;
PFNGLGENBUFFERSPROC                     glGenBuffers;
PFNGLISBUFFERPROC                       glIsBuffer;
PFNGLBUFFERDATAPROC                     glBufferData;
PFNGLBUFFERSUBDATAPROC                  glBufferSubData;
PFNGLGETBUFFERSUBDATAPROC               glGetBufferSubData;
PFNGLMAPBUFFERPROC                      glMapBuffer;
PFNGLUNMAPBUFFERPROC                    glUnmapBuffer;
PFNGLGETBUFFERPARAMETERIVPROC           glGetBufferParameteriv;
PFNGLGETBUFFERPOINTERVPROC              glGetBufferPointerv;

// OpenGL 2.0
PFNGLBLENDEQUATIONSEPARATEPROC          glBlendEquationSeparate;
PFNGLDRAWBUFFERSPROC                    glDrawBuffers;
PFNGLSTENCILOPSEPARATEPROC              glStencilOpSeparate;
PFNGLSTENCILFUNCSEPARATEPROC            glStencilFuncSeparate;
PFNGLSTENCILMASKSEPARATEPROC            glStencilMaskSeparate;
PFNGLATTACHSHADERPROC                   glAttachShader;
PFNGLBINDATTRIBLOCATIONPROC             glBindAttribLocation;
PFNGLCOMPILESHADERPROC                  glCompileShader;
PFNGLCREATEPROGRAMPROC                  glCreateProgram;
PFNGLCREATESHADERPROC                   glCreateShader;
PFNGLDELETEPROGRAMPROC                  glDeleteProgram;
PFNGLDELETESHADERPROC                   glDeleteShader;
PFNGLDETACHSHADERPROC                   glDetachShader;
PFNGLDISABLEVERTEXATTRIBARRAYPROC       glDisableVertexAttribArray;
PFNGLENABLEVERTEXATTRIBARRAYPROC        glEnableVertexAttribArray;
PFNGLGETACTIVEATTRIBPROC                glGetActiveAttrib;
PFNGLGETACTIVEUNIFORMPROC               glGetActiveUniform;
PFNGLGETATTACHEDSHADERSPROC             glGetAttachedShaders;
PFNGLGETATTRIBLOCATIONPROC              glGetAttribLocation;
PFNGLGETPROGRAMIVPROC                   glGetProgramiv;
PFNGLGETPROGRAMINFOLOGPROC              glGetProgramInfoLog;
PFNGLGETSHADERIVPROC                    glGetShaderiv;
PFNGLGETSHADERINFOLOGPROC               glGetShaderInfoLog;
PFNGLGETSHADERSOURCEPROC                glGetShaderSource;
PFNGLGETUNIFORMLOCATIONPROC             glGetUniformLocation;
PFNGLGETUNIFORMFVPROC                   glGetUniformfv;
PFNGLGETUNIFORMIVPROC                   glGetUniformiv;
PFNGLGETVERTEXATTRIBDVPROC              glGetVertexAttribdv;
PFNGLGETVERTEXATTRIBFVPROC              glGetVertexAttribfv;
PFNGLGETVERTEXATTRIBIVPROC              glGetVertexAttribiv;
PFNGLGETVERTEXATTRIBPOINTERVPROC        glGetVertexAttribPointerv;
PFNGLISPROGRAMPROC                      glIsProgram;
PFNGLISSHADERPROC                       glIsShader;
PFNGLLINKPROGRAMPROC                    glLinkProgram;
PFNGLSHADERSOURCEPROC                   glShaderSource;
PFNGLUSEPROGRAMPROC                     glUseProgram;
PFNGLUNIFORM1FPROC                      glUniform1f;
PFNGLUNIFORM2FPROC                      glUniform2f;
PFNGLUNIFORM3FPROC                      glUniform3f;
PFNGLUNIFORM4FPROC                      glUniform4f;
PFNGLUNIFORM1IPROC                      glUniform1i;
PFNGLUNIFORM2IPROC                      glUniform2i;
PFNGLUNIFORM3IPROC                      glUniform3i;
PFNGLUNIFORM4IPROC                      glUniform4i;
PFNGLUNIFORM1FVPROC                     glUniform1fv;
PFNGLUNIFORM2FVPROC                     glUniform2fv;
PFNGLUNIFORM3FVPROC                     glUniform3fv;
PFNGLUNIFORM4FVPROC                     glUniform4fv;
PFNGLUNIFORM1IVPROC                     glUniform1iv;
PFNGLUNIFORM2IVPROC                     glUniform2iv;
PFNGLUNIFORM3IVPROC                     glUniform3iv;
PFNGLUNIFORM4IVPROC                     glUniform4iv;
PFNGLUNIFORMMATRIX2FVPROC               glUniformMatrix2fv;
PFNGLUNIFORMMATRIX3FVPROC               glUniformMatrix3fv;
PFNGLUNIFORMMATRIX4FVPROC               glUniformMatrix4fv;
PFNGLVALIDATEPROGRAMPROC                glValidateProgram;
PFNGLVERTEXATTRIB1DPROC                 glVertexAttrib1d;
PFNGLVERTEXATTRIB1DVPROC                glVertexAttrib1dv;
PFNGLVERTEXATTRIB1FPROC                 glVertexAttrib1f;
PFNGLVERTEXATTRIB1FVPROC                glVertexAttrib1fv;
PFNGLVERTEXATTRIB1SPROC                 glVertexAttrib1s;
PFNGLVERTEXATTRIB1SVPROC                glVertexAttrib1sv;
PFNGLVERTEXATTRIB2DPROC                 glVertexAttrib2d;
PFNGLVERTEXATTRIB2DVPROC                glVertexAttrib2dv;
PFNGLVERTEXATTRIB2FPROC                 glVertexAttrib2f;
PFNGLVERTEXATTRIB2FVPROC                glVertexAttrib2fv;
PFNGLVERTEXATTRIB2SPROC                 glVertexAttrib2s;
PFNGLVERTEXATTRIB2SVPROC                glVertexAttrib2sv;
PFNGLVERTEXATTRIB3DPROC                 glVertexAttrib3d;
PFNGLVERTEXATTRIB3DVPROC                glVertexAttrib3dv;
PFNGLVERTEXATTRIB3FPROC                 glVertexAttrib3f;
PFNGLVERTEXATTRIB3FVPROC                glVertexAttrib3fv;
PFNGLVERTEXATTRIB3SPROC                 glVertexAttrib3s;
PFNGLVERTEXATTRIB3SVPROC                glVertexAttrib3sv;
PFNGLVERTEXATTRIB4NBVPROC               glVertexAttrib4Nbv;
PFNGLVERTEXATTRIB4NIVPROC               glVertexAttrib4Niv;
PFNGLVERTEXATTRIB4NSVPROC               glVertexAttrib4Nsv;
PFNGLVERTEXATTRIB4NUBPROC               glVertexAttrib4Nub;
PFNGLVERTEXATTRIB4NUBVPROC              glVertexAttrib4Nubv;
PFNGLVERTEXATTRIB4NUIVPROC              glVertexAttrib4Nuiv;
PFNGLVERTEXATTRIB4NUSVPROC              glVertexAttrib4Nusv;
PFNGLVERTEXATTRIB4BVPROC                glVertexAttrib4bv;
PFNGLVERTEXATTRIB4DPROC                 glVertexAttrib4d;
PFNGLVERTEXATTRIB4DVPROC                glVertexAttrib4dv;
PFNGLVERTEXATTRIB4FPROC                 glVertexAttrib4f;
PFNGLVERTEXATTRIB4FVPROC                glVertexAttrib4fv;
PFNGLVERTEXATTRIB4IVPROC                glVertexAttrib4iv;
PFNGLVERTEXATTRIB4SPROC                 glVertexAttrib4s;
PFNGLVERTEXATTRIB4SVPROC                glVertexAttrib4sv;
PFNGLVERTEXATTRIB4UBVPROC               glVertexAttrib4ubv;
PFNGLVERTEXATTRIB4UIVPROC               glVertexAttrib4uiv;
PFNGLVERTEXATTRIB4USVPROC               glVertexAttrib4usv;
PFNGLVERTEXATTRIBPOINTERPROC            glVertexAttribPointer;

// OpenGL 2.1
PFNGLUNIFORMMATRIX2X3FVPROC             glUniformMatrix2x3fv;
PFNGLUNIFORMMATRIX3X2FVPROC             glUniformMatrix3x2fv;
PFNGLUNIFORMMATRIX2X4FVPROC             glUniformMatrix2x4fv;
PFNGLUNIFORMMATRIX4X2FVPROC             glUniformMatrix4x2fv;
PFNGLUNIFORMMATRIX3X4FVPROC             glUniformMatrix3x4fv;
PFNGLUNIFORMMATRIX4X3FVPROC             glUniformMatrix4x3fv;


void GL2Init()
{
    #define GPA(x) wglGetProcAddress(x)

    // OpenGL 1.2.
    glCopyTexSubImage3D         = reinterpret_cast<PFNGLCOPYTEXSUBIMAGE3DPROC>(GPA("glCopyTexSubImage3D"));
    glDrawRangeElements         = reinterpret_cast<PFNGLDRAWRANGEELEMENTSPROC>(GPA("glDrawRangeElements"));
    glTexImage3D                = reinterpret_cast<PFNGLTEXIMAGE3DPROC>(GPA("glTexImage3D"));
    glTexSubImage3D             = reinterpret_cast<PFNGLTEXSUBIMAGE3DPROC>(GPA("glTexSubImage3D"));

    // OpenGL 1.3.
    glActiveTexture             = reinterpret_cast<PFNGLACTIVETEXTUREPROC>(GPA("glActiveTexture"));
    glClientActiveTexture       = reinterpret_cast<PFNGLCLIENTACTIVETEXTUREPROC>(GPA("glClientActiveTexture"));
    glMultiTexCoord1d           = reinterpret_cast<PFNGLMULTITEXCOORD1DPROC>(GPA("glMultiTexCoord1d"));
    glMultiTexCoord1dv          = reinterpret_cast<PFNGLMULTITEXCOORD1DVPROC>(GPA("glMultiTexCoord1dv"));
    glMultiTexCoord1f           = reinterpret_cast<PFNGLMULTITEXCOORD1FPROC>(GPA("glMultiTexCoord1f"));
    glMultiTexCoord1fv          = reinterpret_cast<PFNGLMULTITEXCOORD1FVPROC>(GPA("glMultiTexCoord1fv"));
    glMultiTexCoord1i           = reinterpret_cast<PFNGLMULTITEXCOORD1IPROC>(GPA("glMultiTexCoord1i"));
    glMultiTexCoord1iv          = reinterpret_cast<PFNGLMULTITEXCOORD1IVPROC>(GPA("glMultiTexCoord1iv"));
    glMultiTexCoord1s           = reinterpret_cast<PFNGLMULTITEXCOORD1SPROC>(GPA("glMultiTexCoord1s"));
    glMultiTexCoord1sv          = reinterpret_cast<PFNGLMULTITEXCOORD1SVPROC>(GPA("glMultiTexCoord1sv"));
    glMultiTexCoord2d           = reinterpret_cast<PFNGLMULTITEXCOORD2DPROC>(GPA("glMultiTexCoord2d"));
    glMultiTexCoord2dv          = reinterpret_cast<PFNGLMULTITEXCOORD2DVPROC>(GPA("glMultiTexCoord2dv"));
    glMultiTexCoord2f           = reinterpret_cast<PFNGLMULTITEXCOORD2FPROC>(GPA("glMultiTexCoord2f"));
    glMultiTexCoord2fv          = reinterpret_cast<PFNGLMULTITEXCOORD2FVPROC>(GPA("glMultiTexCoord2fv"));
    glMultiTexCoord2i           = reinterpret_cast<PFNGLMULTITEXCOORD2IPROC>(GPA("glMultiTexCoord2i"));
    glMultiTexCoord2iv          = reinterpret_cast<PFNGLMULTITEXCOORD2IVPROC>(GPA("glMultiTexCoord2iv"));
    glMultiTexCoord2s           = reinterpret_cast<PFNGLMULTITEXCOORD2SPROC>(GPA("glMultiTexCoord2s"));
    glMultiTexCoord2sv          = reinterpret_cast<PFNGLMULTITEXCOORD2SVPROC>(GPA("glMultiTexCoord2sv"));
    glMultiTexCoord3d           = reinterpret_cast<PFNGLMULTITEXCOORD3DPROC>(GPA("glMultiTexCoord3d"));
    glMultiTexCoord3dv          = reinterpret_cast<PFNGLMULTITEXCOORD3DVPROC>(GPA("glMultiTexCoord3dv"));
    glMultiTexCoord3f           = reinterpret_cast<PFNGLMULTITEXCOORD3FPROC>(GPA("glMultiTexCoord3f"));
    glMultiTexCoord3fv          = reinterpret_cast<PFNGLMULTITEXCOORD3FVPROC>(GPA("glMultiTexCoord3fv"));
    glMultiTexCoord3i           = reinterpret_cast<PFNGLMULTITEXCOORD3IPROC>(GPA("glMultiTexCoord3i"));
    glMultiTexCoord3iv          = reinterpret_cast<PFNGLMULTITEXCOORD3IVPROC>(GPA("glMultiTexCoord3iv"));
    glMultiTexCoord3s           = reinterpret_cast<PFNGLMULTITEXCOORD3SPROC>(GPA("glMultiTexCoord3s"));
    glMultiTexCoord3sv          = reinterpret_cast<PFNGLMULTITEXCOORD3SVPROC>(GPA("glMultiTexCoord3sv"));
    glMultiTexCoord4d           = reinterpret_cast<PFNGLMULTITEXCOORD4DPROC>(GPA("glMultiTexCoord4d"));
    glMultiTexCoord4dv          = reinterpret_cast<PFNGLMULTITEXCOORD4DVPROC>(GPA("glMultiTexCoord4dv"));
    glMultiTexCoord4f           = reinterpret_cast<PFNGLMULTITEXCOORD4FPROC>(GPA("glMultiTexCoord4f"));
    glMultiTexCoord4fv          = reinterpret_cast<PFNGLMULTITEXCOORD4FVPROC>(GPA("glMultiTexCoord4fv"));
    glMultiTexCoord4i           = reinterpret_cast<PFNGLMULTITEXCOORD4IPROC>(GPA("glMultiTexCoord4i"));
    glMultiTexCoord4iv          = reinterpret_cast<PFNGLMULTITEXCOORD4IVPROC>(GPA("glMultiTexCoord4iv"));
    glMultiTexCoord4s           = reinterpret_cast<PFNGLMULTITEXCOORD4SPROC>(GPA("glMultiTexCoord4s"));
    glMultiTexCoord4sv          = reinterpret_cast<PFNGLMULTITEXCOORD4SVPROC>(GPA("glMultiTexCoord4sv"));
    glLoadTransposeMatrixf      = reinterpret_cast<PFNGLLOADTRANSPOSEMATRIXFPROC>(GPA("glLoadTransposeMatrixf"));
    glLoadTransposeMatrixd      = reinterpret_cast<PFNGLLOADTRANSPOSEMATRIXDPROC>(GPA("glLoadTransposeMatrixd"));
    glMultTransposeMatrixf      = reinterpret_cast<PFNGLMULTTRANSPOSEMATRIXFPROC>(GPA("glMultTransposeMatrixf"));
    glMultTransposeMatrixd      = reinterpret_cast<PFNGLMULTTRANSPOSEMATRIXDPROC>(GPA("glMultTransposeMatrixd"));
    glSampleCoverage            = reinterpret_cast<PFNGLSAMPLECOVERAGEPROC>(GPA("glSampleCoverage"));
    glCompressedTexImage3D      = reinterpret_cast<PFNGLCOMPRESSEDTEXIMAGE3DPROC>(GPA("glCompressedTexImage3D"));
    glCompressedTexImage2D      = reinterpret_cast<PFNGLCOMPRESSEDTEXIMAGE2DPROC>(GPA("glCompressedTexImage2D"));
    glCompressedTexImage1D      = reinterpret_cast<PFNGLCOMPRESSEDTEXIMAGE1DPROC>(GPA("glCompressedTexImage1D"));
    glCompressedTexSubImage3D   = reinterpret_cast<PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC>(GPA("glCompressedTexSubImage3D"));
    glCompressedTexSubImage2D   = reinterpret_cast<PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC>(GPA("glCompressedTexSubImage2D"));
    glCompressedTexSubImage1D   = reinterpret_cast<PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC>(GPA("glCompressedTexSubImage1D"));
    glGetCompressedTexImage     = reinterpret_cast<PFNGLGETCOMPRESSEDTEXIMAGEPROC>(GPA("glGetCompressedTexImage"));

    // OpenGL 1.4.
    glMultiDrawArrays           = reinterpret_cast<PFNGLMULTIDRAWARRAYSPROC>(GPA("glMultiDrawArrays"));
    glMultiDrawElements         = reinterpret_cast<PFNGLMULTIDRAWELEMENTSPROC>(GPA("glMultiDrawElements"));
    glPointParameterf           = reinterpret_cast<PFNGLPOINTPARAMETERFPROC>(GPA("glPointParameterf"));
    glPointParameterfv          = reinterpret_cast<PFNGLPOINTPARAMETERFVPROC>(GPA("glPointParameterfv"));
    glSecondaryColor3b          = reinterpret_cast<PFNGLSECONDARYCOLOR3BPROC>(GPA("glSecondaryColor3b"));
    glSecondaryColor3bv         = reinterpret_cast<PFNGLSECONDARYCOLOR3BVPROC>(GPA("glSecondaryColor3bv"));
    glSecondaryColor3d          = reinterpret_cast<PFNGLSECONDARYCOLOR3DPROC>(GPA("glSecondaryColor3d"));
    glSecondaryColor3dv         = reinterpret_cast<PFNGLSECONDARYCOLOR3DVPROC>(GPA("glSecondaryColor3dv"));
    glSecondaryColor3f          = reinterpret_cast<PFNGLSECONDARYCOLOR3FPROC>(GPA("glSecondaryColor3f"));
    glSecondaryColor3fv         = reinterpret_cast<PFNGLSECONDARYCOLOR3FVPROC>(GPA("glSecondaryColor3fv"));
    glSecondaryColor3i          = reinterpret_cast<PFNGLSECONDARYCOLOR3IPROC>(GPA("glSecondaryColor3i"));
    glSecondaryColor3iv         = reinterpret_cast<PFNGLSECONDARYCOLOR3IVPROC>(GPA("glSecondaryColor3iv"));
    glSecondaryColor3s          = reinterpret_cast<PFNGLSECONDARYCOLOR3SPROC>(GPA("glSecondaryColor3s"));
    glSecondaryColor3sv         = reinterpret_cast<PFNGLSECONDARYCOLOR3SVPROC>(GPA("glSecondaryColor3sv"));
    glSecondaryColor3ub         = reinterpret_cast<PFNGLSECONDARYCOLOR3UBPROC>(GPA("glSecondaryColor3ub"));
    glSecondaryColor3ubv        = reinterpret_cast<PFNGLSECONDARYCOLOR3UBVPROC>(GPA("glSecondaryColor3ubv"));
    glSecondaryColor3ui         = reinterpret_cast<PFNGLSECONDARYCOLOR3UIPROC>(GPA("glSecondaryColor3ui"));
    glSecondaryColor3uiv        = reinterpret_cast<PFNGLSECONDARYCOLOR3UIVPROC>(GPA("glSecondaryColor3uiv"));
    glSecondaryColor3us         = reinterpret_cast<PFNGLSECONDARYCOLOR3USPROC>(GPA("glSecondaryColor3us"));
    glSecondaryColor3usv        = reinterpret_cast<PFNGLSECONDARYCOLOR3USVPROC>(GPA("glSecondaryColor3usv"));
    glSecondaryColorPointer     = reinterpret_cast<PFNGLSECONDARYCOLORPOINTERPROC>(GPA("glSecondaryColorPointer"));
    glBlendFuncSeparate         = reinterpret_cast<PFNGLBLENDFUNCSEPARATEPROC>(GPA("glBlendFuncSeparate"));
    glWindowPos2d               = reinterpret_cast<PFNGLWINDOWPOS2DPROC>(GPA("glWindowPos2d"));
    glWindowPos2f               = reinterpret_cast<PFNGLWINDOWPOS2FPROC>(GPA("glWindowPos2f"));
    glWindowPos2i               = reinterpret_cast<PFNGLWINDOWPOS2IPROC>(GPA("glWindowPos2i"));
    glWindowPos2s               = reinterpret_cast<PFNGLWINDOWPOS2SPROC>(GPA("glWindowPos2s"));
    glWindowPos2dv              = reinterpret_cast<PFNGLWINDOWPOS2DVPROC>(GPA("glWindowPos2dv"));
    glWindowPos2fv              = reinterpret_cast<PFNGLWINDOWPOS2FVPROC>(GPA("glWindowPos2fv"));
    glWindowPos2iv              = reinterpret_cast<PFNGLWINDOWPOS2IVPROC>(GPA("glWindowPos2iv"));
    glWindowPos2sv              = reinterpret_cast<PFNGLWINDOWPOS2SVPROC>(GPA("glWindowPos2sv"));
    glWindowPos3d               = reinterpret_cast<PFNGLWINDOWPOS3DPROC>(GPA("glWindowPos3d"));
    glWindowPos3f               = reinterpret_cast<PFNGLWINDOWPOS3FPROC>(GPA("glWindowPos3f"));
    glWindowPos3i               = reinterpret_cast<PFNGLWINDOWPOS3IPROC>(GPA("glWindowPos3i"));
    glWindowPos3s               = reinterpret_cast<PFNGLWINDOWPOS3SPROC>(GPA("glWindowPos3s"));
    glWindowPos3dv              = reinterpret_cast<PFNGLWINDOWPOS3DVPROC>(GPA("glWindowPos3dv"));
    glWindowPos3fv              = reinterpret_cast<PFNGLWINDOWPOS3FVPROC>(GPA("glWindowPos3fv"));
    glWindowPos3iv              = reinterpret_cast<PFNGLWINDOWPOS3IVPROC>(GPA("glWindowPos3iv"));
    glWindowPos3sv              = reinterpret_cast<PFNGLWINDOWPOS3SVPROC>(GPA("glWindowPos3sv"));

    // OpenGL 1.5.
    glGenQueries                = reinterpret_cast<PFNGLGENQUERIESPROC>(GPA("glGenQueries"));
    glDeleteQueries             = reinterpret_cast<PFNGLDELETEQUERIESPROC>(GPA("glDeleteQueries"));
    glIsQuery                   = reinterpret_cast<PFNGLISQUERYPROC>(GPA("glIsQuery"));
    glBeginQuery                = reinterpret_cast<PFNGLBEGINQUERYPROC>(GPA("glBeginQuery"));
    glEndQuery                  = reinterpret_cast<PFNGLENDQUERYPROC>(GPA("glEndQuery"));
    glGetQueryiv                = reinterpret_cast<PFNGLGETQUERYIVPROC>(GPA("glGetQueryiv"));
    glGetQueryObjectiv          = reinterpret_cast<PFNGLGETQUERYOBJECTIVPROC>(GPA("glGetQueryObjectiv"));
    glGetQueryObjectuiv         = reinterpret_cast<PFNGLGETQUERYOBJECTUIVPROC>(GPA("glGetQueryObjectuiv"));
    glBindBuffer                = reinterpret_cast<PFNGLBINDBUFFERPROC>(GPA("glBindBuffer"));
    glDeleteBuffers             = reinterpret_cast<PFNGLDELETEBUFFERSPROC>(GPA("glDeleteBuffers"));
    glGenBuffers                = reinterpret_cast<PFNGLGENBUFFERSPROC>(GPA("glGenBuffers"));
    glIsBuffer                  = reinterpret_cast<PFNGLISBUFFERPROC>(GPA("glIsBuffer"));
    glBufferData                = reinterpret_cast<PFNGLBUFFERDATAPROC>(GPA("glBufferData"));
    glBufferSubData             = reinterpret_cast<PFNGLBUFFERSUBDATAPROC>(GPA("glBufferSubData"));
    glGetBufferSubData          = reinterpret_cast<PFNGLGETBUFFERSUBDATAPROC>(GPA("glGetBufferSubData"));
    glMapBuffer                 = reinterpret_cast<PFNGLMAPBUFFERPROC>(GPA("glMapBuffer"));
    glUnmapBuffer               = reinterpret_cast<PFNGLUNMAPBUFFERPROC>(GPA("glUnmapBuffer"));
    glGetBufferParameteriv      = reinterpret_cast<PFNGLGETBUFFERPARAMETERIVPROC>(GPA("glGetBufferParameteriv"));
    glGetBufferPointerv         = reinterpret_cast<PFNGLGETBUFFERPOINTERVPROC>(GPA("glGetBufferPointerv"));

    // OpenGL 2.0.
    glBlendEquationSeparate     = reinterpret_cast<PFNGLBLENDEQUATIONSEPARATEPROC>(GPA("glBlendEquationSeparate"));
    glDrawBuffers               = reinterpret_cast<PFNGLDRAWBUFFERSPROC>(GPA("glDrawBuffers"));
    glStencilOpSeparate         = reinterpret_cast<PFNGLSTENCILOPSEPARATEPROC>(GPA("glStencilOpSeparate"));
    glStencilFuncSeparate       = reinterpret_cast<PFNGLSTENCILFUNCSEPARATEPROC>(GPA("glStencilFuncSeparate"));
    glStencilMaskSeparate       = reinterpret_cast<PFNGLSTENCILMASKSEPARATEPROC>(GPA("glStencilMaskSeparate"));
    glAttachShader              = reinterpret_cast<PFNGLATTACHSHADERPROC>(GPA("glAttachShader"));
    glBindAttribLocation        = reinterpret_cast<PFNGLBINDATTRIBLOCATIONPROC>(GPA("glBindAttribLocation"));
    glCompileShader             = reinterpret_cast<PFNGLCOMPILESHADERPROC>(GPA("glCompileShader"));
    glCreateProgram             = reinterpret_cast<PFNGLCREATEPROGRAMPROC>(GPA("glCreateProgram"));
    glCreateShader              = reinterpret_cast<PFNGLCREATESHADERPROC>(GPA("glCreateShader"));
    glDeleteProgram             = reinterpret_cast<PFNGLDELETEPROGRAMPROC>(GPA("glDeleteProgram"));
    glDeleteShader              = reinterpret_cast<PFNGLDELETESHADERPROC>(GPA("glDeleteShader"));
    glDetachShader              = reinterpret_cast<PFNGLDETACHSHADERPROC>(GPA("glDetachShader"));
    glDisableVertexAttribArray  = reinterpret_cast<PFNGLDISABLEVERTEXATTRIBARRAYPROC>(GPA("glDisableVertexAttribArray"));
    glEnableVertexAttribArray   = reinterpret_cast<PFNGLENABLEVERTEXATTRIBARRAYPROC>(GPA("glEnableVertexAttribArray"));
    glGetActiveAttrib           = reinterpret_cast<PFNGLGETACTIVEATTRIBPROC>(GPA("glGetActiveAttrib"));
    glGetActiveUniform          = reinterpret_cast<PFNGLGETACTIVEUNIFORMPROC>(GPA("glGetActiveUniform"));
    glGetAttachedShaders        = reinterpret_cast<PFNGLGETATTACHEDSHADERSPROC>(GPA("glGetAttachedShaders"));
    glGetAttribLocation         = reinterpret_cast<PFNGLGETATTRIBLOCATIONPROC>(GPA("glGetAttribLocation"));
    glGetProgramiv              = reinterpret_cast<PFNGLGETPROGRAMIVPROC>(GPA("glGetProgramiv"));
    glGetProgramInfoLog         = reinterpret_cast<PFNGLGETPROGRAMINFOLOGPROC>(GPA("glGetProgramInfoLog"));
    glGetShaderiv               = reinterpret_cast<PFNGLGETSHADERIVPROC>(GPA("glGetShaderiv"));
    glGetShaderInfoLog          = reinterpret_cast<PFNGLGETSHADERINFOLOGPROC>(GPA("glGetShaderInfoLog"));
    glGetShaderSource           = reinterpret_cast<PFNGLGETSHADERSOURCEPROC>(GPA("glGetShaderSource"));
    glGetUniformLocation        = reinterpret_cast<PFNGLGETUNIFORMLOCATIONPROC>(GPA("glGetUniformLocation"));
    glGetUniformfv              = reinterpret_cast<PFNGLGETUNIFORMFVPROC>(GPA("glGetUniformfv"));
    glGetUniformiv              = reinterpret_cast<PFNGLGETUNIFORMIVPROC>(GPA("glGetUniformiv"));
    glGetVertexAttribdv         = reinterpret_cast<PFNGLGETVERTEXATTRIBDVPROC>(GPA("glGetVertexAttribdv"));
    glGetVertexAttribfv         = reinterpret_cast<PFNGLGETVERTEXATTRIBFVPROC>(GPA("glGetVertexAttribfv"));
    glGetVertexAttribiv         = reinterpret_cast<PFNGLGETVERTEXATTRIBIVPROC>(GPA("glGetVertexAttribiv"));
    glGetVertexAttribPointerv   = reinterpret_cast<PFNGLGETVERTEXATTRIBPOINTERVPROC>(GPA("glGetVertexAttribPointerv"));
    glIsProgram                 = reinterpret_cast<PFNGLISPROGRAMPROC>(GPA("glIsProgram"));
    glIsShader                  = reinterpret_cast<PFNGLISSHADERPROC>(GPA("glIsShader"));
    glLinkProgram               = reinterpret_cast<PFNGLLINKPROGRAMPROC>(GPA("glLinkProgram"));
    glShaderSource              = reinterpret_cast<PFNGLSHADERSOURCEPROC>(GPA("glShaderSource"));
    glUseProgram                = reinterpret_cast<PFNGLUSEPROGRAMPROC>(GPA("glUseProgram"));
    glUniform1f                 = reinterpret_cast<PFNGLUNIFORM1FPROC>(GPA("glUniform1f"));
    glUniform2f                 = reinterpret_cast<PFNGLUNIFORM2FPROC>(GPA("glUniform2f"));
    glUniform3f                 = reinterpret_cast<PFNGLUNIFORM3FPROC>(GPA("glUniform3f"));
    glUniform4f                 = reinterpret_cast<PFNGLUNIFORM4FPROC>(GPA("glUniform4f"));
    glUniform1i                 = reinterpret_cast<PFNGLUNIFORM1IPROC>(GPA("glUniform1i"));
    glUniform2i                 = reinterpret_cast<PFNGLUNIFORM2IPROC>(GPA("glUniform2i"));
    glUniform3i                 = reinterpret_cast<PFNGLUNIFORM3IPROC>(GPA("glUniform3i"));
    glUniform4i                 = reinterpret_cast<PFNGLUNIFORM4IPROC>(GPA("glUniform4i"));
    glUniform1fv                = reinterpret_cast<PFNGLUNIFORM1FVPROC>(GPA("glUniform1fv"));
    glUniform2fv                = reinterpret_cast<PFNGLUNIFORM2FVPROC>(GPA("glUniform2fv"));
    glUniform3fv                = reinterpret_cast<PFNGLUNIFORM3FVPROC>(GPA("glUniform3fv"));
    glUniform4fv                = reinterpret_cast<PFNGLUNIFORM4FVPROC>(GPA("glUniform4fv"));
    glUniform1iv                = reinterpret_cast<PFNGLUNIFORM1IVPROC>(GPA("glUniform1iv"));
    glUniform2iv                = reinterpret_cast<PFNGLUNIFORM2IVPROC>(GPA("glUniform2iv"));
    glUniform3iv                = reinterpret_cast<PFNGLUNIFORM3IVPROC>(GPA("glUniform3iv"));
    glUniform4iv                = reinterpret_cast<PFNGLUNIFORM4IVPROC>(GPA("glUniform4iv"));
    glUniformMatrix2fv          = reinterpret_cast<PFNGLUNIFORMMATRIX2FVPROC>(GPA("glUniformMatrix2fv"));
    glUniformMatrix3fv          = reinterpret_cast<PFNGLUNIFORMMATRIX3FVPROC>(GPA("glUniformMatrix3fv"));
    glUniformMatrix4fv          = reinterpret_cast<PFNGLUNIFORMMATRIX4FVPROC>(GPA("glUniformMatrix4fv"));
    glValidateProgram           = reinterpret_cast<PFNGLVALIDATEPROGRAMPROC>(GPA("glValidateProgram"));
    glVertexAttrib1d            = reinterpret_cast<PFNGLVERTEXATTRIB1DPROC>(GPA("glVertexAttrib1d"));
    glVertexAttrib1dv           = reinterpret_cast<PFNGLVERTEXATTRIB1DVPROC>(GPA("glVertexAttrib1dv"));
    glVertexAttrib1f            = reinterpret_cast<PFNGLVERTEXATTRIB1FPROC>(GPA("glVertexAttrib1f"));
    glVertexAttrib1fv           = reinterpret_cast<PFNGLVERTEXATTRIB1FVPROC>(GPA("glVertexAttrib1fv"));
    glVertexAttrib1s            = reinterpret_cast<PFNGLVERTEXATTRIB1SPROC>(GPA("glVertexAttrib1s"));
    glVertexAttrib1sv           = reinterpret_cast<PFNGLVERTEXATTRIB1SVPROC>(GPA("glVertexAttrib1sv"));
    glVertexAttrib2d            = reinterpret_cast<PFNGLVERTEXATTRIB2DPROC>(GPA("glVertexAttrib2d"));
    glVertexAttrib2dv           = reinterpret_cast<PFNGLVERTEXATTRIB2DVPROC>(GPA("glVertexAttrib2dv"));
    glVertexAttrib2f            = reinterpret_cast<PFNGLVERTEXATTRIB2FPROC>(GPA("glVertexAttrib2f"));
    glVertexAttrib2fv           = reinterpret_cast<PFNGLVERTEXATTRIB2FVPROC>(GPA("glVertexAttrib2fv"));
    glVertexAttrib2s            = reinterpret_cast<PFNGLVERTEXATTRIB2SPROC>(GPA("glVertexAttrib2s"));
    glVertexAttrib2sv           = reinterpret_cast<PFNGLVERTEXATTRIB2SVPROC>(GPA("glVertexAttrib2sv"));
    glVertexAttrib3d            = reinterpret_cast<PFNGLVERTEXATTRIB3DPROC>(GPA("glVertexAttrib3d"));
    glVertexAttrib3dv           = reinterpret_cast<PFNGLVERTEXATTRIB3DVPROC>(GPA("glVertexAttrib3dv"));
    glVertexAttrib3f            = reinterpret_cast<PFNGLVERTEXATTRIB3FPROC>(GPA("glVertexAttrib3f"));
    glVertexAttrib3fv           = reinterpret_cast<PFNGLVERTEXATTRIB3FVPROC>(GPA("glVertexAttrib3fv"));
    glVertexAttrib3s            = reinterpret_cast<PFNGLVERTEXATTRIB3SPROC>(GPA("glVertexAttrib3s"));
    glVertexAttrib3sv           = reinterpret_cast<PFNGLVERTEXATTRIB3SVPROC>(GPA("glVertexAttrib3sv"));
    glVertexAttrib4Nbv          = reinterpret_cast<PFNGLVERTEXATTRIB4NBVPROC>(GPA("glVertexAttrib4Nbv"));
    glVertexAttrib4Niv          = reinterpret_cast<PFNGLVERTEXATTRIB4NIVPROC>(GPA("glVertexAttrib4Niv"));
    glVertexAttrib4Nsv          = reinterpret_cast<PFNGLVERTEXATTRIB4NSVPROC>(GPA("glVertexAttrib4Nsv"));
    glVertexAttrib4Nub          = reinterpret_cast<PFNGLVERTEXATTRIB4NUBPROC>(GPA("glVertexAttrib4Nub"));
    glVertexAttrib4Nubv         = reinterpret_cast<PFNGLVERTEXATTRIB4NUBVPROC>(GPA("glVertexAttrib4Nubv"));
    glVertexAttrib4Nuiv         = reinterpret_cast<PFNGLVERTEXATTRIB4NUIVPROC>(GPA("glVertexAttrib4Nuiv"));
    glVertexAttrib4Nusv         = reinterpret_cast<PFNGLVERTEXATTRIB4NUSVPROC>(GPA("glVertexAttrib4Nusv"));
    glVertexAttrib4bv           = reinterpret_cast<PFNGLVERTEXATTRIB4BVPROC>(GPA("glVertexAttrib4bv"));
    glVertexAttrib4d            = reinterpret_cast<PFNGLVERTEXATTRIB4DPROC>(GPA("glVertexAttrib4d"));
    glVertexAttrib4dv           = reinterpret_cast<PFNGLVERTEXATTRIB4DVPROC>(GPA("glVertexAttrib4dv"));
    glVertexAttrib4f            = reinterpret_cast<PFNGLVERTEXATTRIB4FPROC>(GPA("glVertexAttrib4f"));
    glVertexAttrib4fv           = reinterpret_cast<PFNGLVERTEXATTRIB4FVPROC>(GPA("glVertexAttrib4fv"));
    glVertexAttrib4iv           = reinterpret_cast<PFNGLVERTEXATTRIB4IVPROC>(GPA("glVertexAttrib4iv"));
    glVertexAttrib4s            = reinterpret_cast<PFNGLVERTEXATTRIB4SPROC>(GPA("glVertexAttrib4s"));
    glVertexAttrib4sv           = reinterpret_cast<PFNGLVERTEXATTRIB4SVPROC>(GPA("glVertexAttrib4sv"));
    glVertexAttrib4ubv          = reinterpret_cast<PFNGLVERTEXATTRIB4UBVPROC>(GPA("glVertexAttrib4ubv"));
    glVertexAttrib4uiv          = reinterpret_cast<PFNGLVERTEXATTRIB4UIVPROC>(GPA("glVertexAttrib4uiv"));
    glVertexAttrib4usv          = reinterpret_cast<PFNGLVERTEXATTRIB4USVPROC>(GPA("glVertexAttrib4usv"));
    glVertexAttribPointer       = reinterpret_cast<PFNGLVERTEXATTRIBPOINTERPROC>(GPA("glVertexAttribPointer"));

    // OpenGL 2.1.
    glUniformMatrix2x3fv        = reinterpret_cast<PFNGLUNIFORMMATRIX2X3FVPROC>(GPA("glUniformMatrix2x3fv"));
    glUniformMatrix3x2fv        = reinterpret_cast<PFNGLUNIFORMMATRIX3X2FVPROC>(GPA("glUniformMatrix3x2fv"));
    glUniformMatrix2x4fv        = reinterpret_cast<PFNGLUNIFORMMATRIX2X4FVPROC>(GPA("glUniformMatrix2x4fv"));
    glUniformMatrix4x2fv        = reinterpret_cast<PFNGLUNIFORMMATRIX4X2FVPROC>(GPA("glUniformMatrix4x2fv"));
    glUniformMatrix3x4fv        = reinterpret_cast<PFNGLUNIFORMMATRIX3X4FVPROC>(GPA("glUniformMatrix3x4fv"));
    glUniformMatrix4x3fv        = reinterpret_cast<PFNGLUNIFORMMATRIX4X3FVPROC>(GPA("glUniformMatrix4x3fv"));

    #undef GPA
}

void GL2GetGLVersion(int &major, int &minor)
{
    static int majorGL = 0;
    static int minorGL = 0;

    if (!majorGL && !minorGL)
    {
        const char *pszVersion = reinterpret_cast<const char *>(glGetString(GL_VERSION));
        
        if (pszVersion)
            sscanf(pszVersion, "%d.%d", &majorGL, &minorGL);
    }
    
    major = majorGL;
    minor = minorGL;
}

void GL2GetGLSLVersion(int &major, int &minor)
{
    static int majorGLSL = 0;
    static int minorGLSL = 0;

    if (!majorGLSL && !minorGLSL)
    {
        int majorGL = 0;
        int minorGL = 0;

        GL2GetGLVersion(majorGL, minorGL);

        if (majorGL >= 2)
        {
            const char *pszShaderVersion = reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION));

            if (pszShaderVersion)
                sscanf(pszShaderVersion, "%d.%d", &majorGLSL, &minorGLSL);
        }
        else
        {
            const char *pszExtension = reinterpret_cast<const char *>(glGetString(GL_EXTENSIONS));

            if (pszExtension)
            {
                if (strstr(pszExtension, "GL_ARB_shading_language_100"))
                {
                    majorGLSL = 1;
                    minorGLSL = 0;
                }
            }
        }
    }

    major = majorGLSL;
    minor = minorGLSL;
}

bool GL2SupportsGLVersion(int major, int minor)
{
    static int majorGL = 0;
    static int minorGL = 0;

    if (!majorGL && !minorGL)
        GL2GetGLVersion(majorGL, minorGL);

    if (majorGL > major)
        return true;

    if (majorGL == major && minorGL >= minor)
        return true;

    return false;
}

bool GL2SupportsGLSLVersion(int major, int minor)
{
    static int majorGLSL = 0;
    static int minorGLSL = 0;

    if (!majorGLSL && !minorGLSL)
        GL2GetGLSLVersion(majorGLSL, minorGLSL);

    if (majorGLSL > major)
        return true;

    if (majorGLSL == major && minorGLSL >= minor)
        return true;

    return false;
}
