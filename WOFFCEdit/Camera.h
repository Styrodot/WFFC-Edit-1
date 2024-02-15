#pragma once

#include "DisplayChunk.h"

class InputCommands; 

class Camera
{

private:
	//functionality
	float m_movespeed;

	//camera
	DirectX::SimpleMath::Vector3 m_camPosition;
	DirectX::SimpleMath::Vector3 m_camOrientation;
	DirectX::SimpleMath::Vector3 m_camLookAt;
	DirectX::SimpleMath::Vector3 m_camLookDirection;
	DirectX::SimpleMath::Vector3 m_camRight;
	float m_camRotRate;

	DirectX::SimpleMath::Matrix	m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_projection;


public:
	Camera();
	~Camera();



	void Update(InputCommands* Input);


	DirectX::SimpleMath::Matrix GetView();
	DirectX::SimpleMath::Vector3 GetCameraPos();
};

