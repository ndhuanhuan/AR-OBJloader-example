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

#include "WGL_ARB_multisample.h"

// GL_ARB_multisample
PFNGLSAMPLECOVERAGEARBPROC           glSampleCoverageARB;

// WGL_ARB_pixel_format
PFNWGLGETPIXELFORMATATTRIBIVARBPROC  wglGetPixelFormatAttribivARB;
PFNWGLGETPIXELFORMATATTRIBFVARBPROC  wglGetPixelFormatAttribfvARB;
PFNWGLCHOOSEPIXELFORMATARBPROC       wglChoosePixelFormatARB;

namespace
{
    WNDCLASSEX g_wcl;
    HWND g_hWnd;
    HDC g_hDC;
    HGLRC g_hRC;

    LRESULT CALLBACK DummyGLWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        switch (msg)
        {
        case WM_CREATE:
            if (!(g_hDC = GetDC(hWnd)))
                return -1;
            break;

        case WM_DESTROY:
            if (g_hDC)
            {
                if (g_hRC)
                {
                    wglMakeCurrent(g_hDC, 0);
                    wglDeleteContext(g_hRC);
                    g_hRC = 0;
                }

                ReleaseDC(hWnd, g_hDC);
                g_hDC = 0;
            }

            PostQuitMessage(0);
            return 0;

        default:
            break;
        }

        return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    bool CreateDummyGLWindow()
    {
        g_wcl.cbSize = sizeof(g_wcl);
        g_wcl.style = CS_OWNDC;
        g_wcl.lpfnWndProc = DummyGLWndProc;
        g_wcl.hInstance = reinterpret_cast<HINSTANCE>(GetModuleHandle(0));
        g_wcl.lpszClassName = "DummyGLWindowClass";

        if (!RegisterClassEx(&g_wcl))
            return false;

        g_hWnd = CreateWindow(g_wcl.lpszClassName, "", WS_OVERLAPPEDWINDOW,
                    0, 0, 0, 0, 0, 0, g_wcl.hInstance, 0);    

        if (!g_hWnd)
            return false;

        PIXELFORMATDESCRIPTOR pfd = {0};

        pfd.nSize = sizeof(pfd);
        pfd.nVersion = 1;
        pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.cColorBits = 24;
        pfd.cDepthBits = 16;
        pfd.iLayerType = PFD_MAIN_PLANE;

        int pf = ChoosePixelFormat(g_hDC, &pfd);

        if (!SetPixelFormat(g_hDC, pf, &pfd))
            return false;

        if (!(g_hRC = wglCreateContext(g_hDC)))
            return false;

        if (!wglMakeCurrent(g_hDC, g_hRC))
            return false;

        return true;
    }

    void DestroyDummyGLWindow()
    {
        if (g_hWnd)
        {
            PostMessage(g_hWnd, WM_CLOSE, 0, 0);

            BOOL bRet;
            MSG msg;

            while ((bRet = GetMessage(&msg, 0, 0, 0)) != 0)
            { 
                TranslateMessage(&msg); 
                DispatchMessage(&msg); 
            }
        }        

        UnregisterClass(g_wcl.lpszClassName, g_wcl.hInstance);
    }

    bool InitExtensions()
    {
        if (!glSampleCoverageARB)
        {
            glSampleCoverageARB = reinterpret_cast<PFNGLSAMPLECOVERAGEARBPROC>(
                wglGetProcAddress("glSampleCoverageARB"));

            if (!glSampleCoverageARB)
                return false;
        }

        if (!wglGetPixelFormatAttribivARB)
        {
            wglGetPixelFormatAttribivARB = reinterpret_cast<PFNWGLGETPIXELFORMATATTRIBIVARBPROC>(
                wglGetProcAddress("wglGetPixelFormatAttribivARB"));

            if (!wglGetPixelFormatAttribivARB)
                return false;
        }
               
        if (!wglGetPixelFormatAttribfvARB)
        {
            wglGetPixelFormatAttribfvARB = reinterpret_cast<PFNWGLGETPIXELFORMATATTRIBFVARBPROC>(
                wglGetProcAddress("wglGetPixelFormatAttribfvARB"));

            if (!wglGetPixelFormatAttribfvARB)
                return false;
        }
        
        if (!wglChoosePixelFormatARB)
        {
            wglChoosePixelFormatARB = reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>(
                wglGetProcAddress("wglChoosePixelFormatARB"));

            if (!wglChoosePixelFormatARB)
                return false;
        }
        
        return true;
    }
}

void ChooseBestMultiSampleAntiAliasingPixelFormat(int &pf, int &maxSamples)
{
    pf = 0;
    maxSamples = 1;       

    if (!CreateDummyGLWindow())
    {
        DestroyDummyGLWindow();
        return;
    }
    
    if (!InitExtensions())
    {
        DestroyDummyGLWindow();
        return;
    }

    BOOL bStatus = FALSE;
    UINT numFormats = 0;
    int pixelFormat = 0;
    int returnedPixelFormat = 0;
    int attributes[20];

    attributes[0] = WGL_DRAW_TO_WINDOW_ARB;
    attributes[1] = GL_TRUE;
    attributes[2] = WGL_ACCELERATION_ARB;
    attributes[3] = WGL_FULL_ACCELERATION_ARB;
    attributes[4] = WGL_COLOR_BITS_ARB;
    attributes[5] = 24;
    attributes[6] = WGL_ALPHA_BITS_ARB;
    attributes[7] = 8;
    attributes[8] = WGL_DEPTH_BITS_ARB;
    attributes[9] = 24;
    attributes[10] = WGL_STENCIL_BITS_ARB;
    attributes[11] = 8;
    attributes[12] = WGL_DOUBLE_BUFFER_ARB;
    attributes[13] = GL_TRUE;
    attributes[14] = WGL_SAMPLE_BUFFERS_ARB;
    attributes[15] = GL_TRUE;
    attributes[16] = WGL_SAMPLES_ARB;
    attributes[17] = 0;
    attributes[18] = 0;
    attributes[19] = 0;

    for (int samples = 16; samples > 0; samples /= 2)
    {
        attributes[17] = samples;

        bStatus = wglChoosePixelFormatARB(g_hDC, attributes,
                    0, 1, &returnedPixelFormat, &numFormats);

        if (bStatus == GL_TRUE && numFormats)
        {
            pf = returnedPixelFormat;
            maxSamples = attributes[17];
            break;
        }
    }

    DestroyDummyGLWindow();
}

void ChooseMultiSampleAntiAliasingPixelFormat(int &pf, int samples)
{
    pf = 0;

    if (!CreateDummyGLWindow())
    {
        DestroyDummyGLWindow();
        return;
    }

    if (!InitExtensions())
    {
        DestroyDummyGLWindow();
        return;
    }

    int attributes[] =
    {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB,
        WGL_COLOR_BITS_ARB,     24,
        WGL_ALPHA_BITS_ARB,     8,
        WGL_DEPTH_BITS_ARB,     24,
        WGL_STENCIL_BITS_ARB,   8,
        WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
        WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
        WGL_SAMPLES_ARB,        samples,
        0, 0
    };
    int pixelFormat = 0;
    int returnedPixelFormat = 0;
    UINT numFormats = 0;
    BOOL bStatus = wglChoosePixelFormatARB(g_hDC, attributes,
                    0, 1, &returnedPixelFormat, &numFormats);

    if (bStatus == GL_TRUE && numFormats)
        pf = returnedPixelFormat;

    DestroyDummyGLWindow();
}