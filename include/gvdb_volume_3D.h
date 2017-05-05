//--------------------------------------------------------------------------------
// NVIDIA(R) GVDB VOXELS
// Copyright 2017, NVIDIA Corporation. 
//
// Redistribution and use in source and binary forms, with or without modification, 
// are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer 
//    in the documentation and/or  other materials provided with the distribution.
// 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived 
//    from this software without specific prior written permission.
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
// BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
// SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// Version 1.0: Rama Hoetzlein, 5/1/2017
//----------------------------------------------------------------------------------


#ifndef DEF_VOL_3D
	#define DEF_VOL_3D

	#include "gvdb_volume_base.h"
	#include "gvdb_allocator.h"

	namespace nvdb {

	class Volume3D : public VolumeBase {
	public:
		Volume3D ( Scene* scn );
		~Volume3D ();
		
		void Clear ();
		void Resize ( char typ, Vector3DI res, Matrix4F* xform, bool bGL );
		void CommitFromCPU ( float* src );
		void SetDomain ( Vector3DF vmin, Vector3DF vmax );
		void Empty ();	
		void PrepareFill ( char how, bool start );				
		void getMemory ( float& voxels, float& overhead, float& effective );
		
		// OpenGL Poly-to-Voxels
		void PrepareRasterGL ( bool start );
		void SurfaceVoxelizeGL ( uchar  chan, Model* model, Matrix4F* xform );	
		void SurfaceVoxelizeFastGL ( Vector3DF vmin, Vector3DF vmax, Matrix4F* model );
		void RetrieveGL ( char* dest );	

		DataPtr	getPtr ()	{ return mPool->getAtlas(0); }
		Vector3DI getSize ()	{ return mPool->getAtlas(0).subdim; }
		bool hasSize ( Vector3DI i, uchar dt )	{ 
			Vector3DI sz = mPool->getAtlas(0).subdim;
			return (sz.x==i.x && sz.y==i.y && sz.z==i.z && mPool->getAtlas(0).type==dt);
		}
	
	public:				
		int				mMargin;		

		// Allocator
		Allocator*		mPool;

		static int		mVFBO[2];		
		static int		mVCLEAR;
	};

	}

#endif
