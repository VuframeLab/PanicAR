//
//  ARUtils.h
//  PanicAR
//
//  Created by Andreas Zeitler on 17.08.10.
//  Copyright 2010 doPanic. All rights reserved.
//

#import <OpenGLES/EAGLDrawable.h>
#import <OpenGLES/ES1/glext.h>
#import <stdint.h>
#import <cstddef>



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
    : _vertexCount(0)
    , _indexCount(0)
    {}
    
    int _vertexCount;
    int _indexCount;
    
    Mesh_Vertex _vertices[Mesh_MaxVertices];
    uint16_t _indices[Mesh_MaxIndices];
};

namespace MeshUtils		
{
	BOOL LoadMesh(Mesh& mesh, const char* filename);
	void UnloadMesh(Mesh& mesh);	
    void PrintMesh(Mesh& mesh);
	uint64_t GetVertexKey(int p, int t, int n);
	void GetVertexData(Mesh_Vertex& vertex, int p, int t, int n);
	void AddVertexAndIndex(int p, int t, int n, Mesh& mesh);
	void Clear();
};


namespace ARUtils {
#pragma mark -
#pragma mark Render Tools
	void RenderModel(const Mesh& mesh, uint textureHandle);
	void PrintToTexture(uint textureHandle, CGRect destRect, NSString* txt, UIFont* font, UIImage* uiimage);
	
	
#pragma mark -
#pragma mark Texture Tools
	uint CreateTex(UIImage* uiimage);
	uint CreateTex(UIImage* uiimage, uint8_t* textureData, uint tWidth, uint tHeight);
	void UpdateTex(UIImage* uiimage, uint handle);
	void UpdateTex(uint8_t* textureData, uint handle, uint tWidth, uint tHeight);
	void ReleaseTex(uint handle);
	void SaveTexToDocuments(UIImage* uiimage, NSString* filename);
	
	
#pragma mark -
#pragma mark FrameBuffer Tools
	struct FrameBuffer
	{
		GLuint _frameBufferHandle;
		GLuint _colorBufferHandle;
		GLuint _depthBufferHandle;
		GLuint _stencilBufferHandle;
		int _width;
        BOOL seperateStencilBuffer;
		int _height;
	};
	
	//void CreateFB(FrameBuffer& buffer, int width, int height);
	void CreateFB(FrameBuffer& buffer, EAGLContext* eaglContext, id<EAGLDrawable> drawable);
    void CreateFB(FrameBuffer& buffer, int width, int height);
	void DestroyFB(FrameBuffer& buffer);
	void SetFB(const FrameBuffer& buffer);
	void ResizeFB(FrameBuffer& buffer, EAGLContext* eaglContext, id<EAGLDrawable> drawable);
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
		double _clockToSeconds;
		
		uint64_t _startAbsTime;
		uint64_t _lastAbsTime;
		
		double _time;
		float _deltaTime;
	};
	
	
	
}
