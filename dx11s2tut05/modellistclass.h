///////////////////////////////////////////////////////////////////////////////
// Filename: modellistclass.h
///////////////////////////////////////////////////////////////////////////////
#ifndef _MODELLISTCLASS_H_
#define _MODELLISTCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <directxmath.h>
#include <stdlib.h>
#include <time.h>
using namespace DirectX;

///////////////////////////////////////////////////////////////////////////////
// Class name: ModelListClass
///////////////////////////////////////////////////////////////////////////////
class ModelListClass
{
private:
	struct ModelInfoType
	{
		XMFLOAT4 color;
		float positionX, positionY, positionZ;
		XMMATRIX rotationMatrix;
		int id;
		//AabbClass boundingBox;
	};

public:
	ModelListClass();
	ModelListClass(const ModelListClass&);
	~ModelListClass();

	bool Initialize(int);
	void Shutdown();

	int GetModelCount();
	void GetData(int, float&, float&, float&, XMFLOAT4&, XMMATRIX&);
	void SetData(int, float, float, float);
	void SetColor(int, XMFLOAT4);
	XMFLOAT4 GetColor(int);

	XMMATRIX GetRotation(int);
	void SetRotation(int,XMMATRIX);
	//AabbClass getBoundingBox(int);
	//void setBoundingBox(int, AabbClass);
	void updateBoundingBoxPos(XMFLOAT3);

private:
	int m_modelCount;
	ModelInfoType* m_ModelInfoList;
	
	
};

#endif