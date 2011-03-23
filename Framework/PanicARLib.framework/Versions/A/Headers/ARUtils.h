//
//  ARUtils.h
//  PanicAR
//
//  Created by Andreas Zeitler on 17.08.10.
//  Copyright 2010 doPanic. All rights reserved.
//

#import <OpenGLES/EAGLDrawable.h>
#import <OpenGLES/ES1/glext.h>
#include <stdint.h>
#include <cstddef>



#ifndef DISTRIBUTION

#define CHECK_GL_ERRORS() \
do {                                                                                            	\
GLenum error = glGetError();                                                                	\
if(error != GL_NO_ERROR) {                                                                   	\
NSLog(@"OpenGL: %s [error %d]", __FUNCTION__, (int)error);					\
assert(0); \
} \
} while(false)

#else

#define CHECK_GL_ERRORS()

#endif




@protocol EAGLDrawable;
@class EAGLContext;
@class UIImage;




	
#pragma mark -
#pragma mark Mesh & OBJ Loader
	const int Mesh_MaxVertices = 10000;
	const int Mesh_MaxIndices = 10000;
	struct Mesh_Vertex
	{
		float x, y, z;
		float nx, ny, nz;
		float u, v;
	};
	struct Mesh
	{
		Mesh() 
		: m_vertexCount(0)
		, m_indexCount(0)
		{}
		
		int m_vertexCount;
		int m_indexCount;
		
		Mesh_Vertex m_vertices[Mesh_MaxVertices];
		uint16_t m_indices[Mesh_MaxIndices];
	};

namespace MeshUtils		
{
	BOOL LoadMesh(Mesh& mesh, const char* filename);
	void UnloadMesh(Mesh& mesh);	
};

	
namespace ARUtils {
#pragma mark -
#pragma mark Render Tools
	void RenderModel(const Mesh& mesh, uint textureHandle);
	void PrintToTexture(uint textureHandle, CGRect destRect, NSString* txt, UIFont* font, UIImage* uiimage);
	
	
#pragma mark -
#pragma mark Texture Tools
	uint CreateTex(UIImage* uiimage);
	void UpdateTex(UIImage* uiimage, uint handle);
	void ReleaseTex(uint handle);
	void SaveTexToDocuments(UIImage* uiimage, NSString* filename);
	
	
#pragma mark -
#pragma mark FrameBuffer Tools
	struct FrameBuffer
	{
		uint m_frameBufferHandle;
		uint m_colorBufferHandle;
		uint m_depthBufferHandle;
		int m_width;
		int m_height;
	};
	
	void CreateFB(FrameBuffer& buffer, int width, int height);
	void CreateFB(FrameBuffer& buffer, EAGLContext* eaglContext, id<EAGLDrawable> drawable);
	void DestroyFB(FrameBuffer& buffer);
	void SetFB(const FrameBuffer& buffer);
	UIImage* CreateImageFromFB(int x, int y, int width, int height);
	
	
#pragma mark -
#pragma mark Hardware Timer
	class ARHardwareTimer
	{
	public:
		ARHardwareTimer();
		
		void Reset();
		void Update();
		
		float GetDeltaTime() const;
		double GetTime() const;		
		
	private:
		double m_clockToSeconds;
		
		uint64_t m_startAbsTime;
		uint64_t m_lastAbsTime;
		
		double m_time;
		float m_deltaTime;
	};
	
	
	
}
