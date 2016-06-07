///////////////////////////////////////////////////////////////////////////////
// Filename: modellistclass.h
///////////////////////////////////////////////////////////////////////////////
#ifndef _MODELLISTCLASS_H_
#define _MODELLISTCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <vector>
#include <directxmath.h>
#include <string>
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
		XMMATRIX fixedRotationMatrix;
		float fixedRotX, fixedRotY, fixedRotZ;
		float variableRotX, variableRotY, variableRotZ;

		std::vector<std::string> rotVector;

		std::vector<float> rotXVector;
		std::vector<float> rotYVector;
		std::vector<float> rotZVector;

		std::string Xaxis, Yaxis, Zaxis;
		int id;
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

	void resetCubeRotation(int);

	XMFLOAT4 GetColor(int);

	float getFixedRotX(int);
	float getFixedRotY(int);
	float getFixedRotZ(int);

    void setFixedRotX(int, float);
	void setFixedRotY(int, float);
	void setFixedRotZ(int, float);

	float getVariableRotX(int);
	float getVariableRotY(int);
	float getVariableRotZ(int);

	void setVariableRotX(int, float);
	void setVariableRotY(int, float);
	void setVariableRotZ(int, float);

	//void getAxisAligned

	void appendRotationCode(int, std::string);
	std::string getRotationCode(int, int);

	void appendRotX(int, float);
	float getRotX(int, int);
	void appendRotY(int, float);
	float getRotY(int, int);
	void appendRotZ(int, float);
	float getRotZ(int, int);

	XMMATRIX GetRotation(int);
	void SetRotation(int,XMMATRIX);

	XMMATRIX GetFixedRotation(int);
	void SetFixedRotation(int, XMMATRIX);

	//AabbClass getBoundingBox(int);
	//void setBoundingBox(int, AabbClass);
	void updateBoundingBoxPos(XMFLOAT3);

private:
	int m_modelCount;
	ModelInfoType* m_ModelInfoList;
	
	
};

#endif