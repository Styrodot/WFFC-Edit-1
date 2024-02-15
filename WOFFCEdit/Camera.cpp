#include "Camera.h"

#include "InputCommands.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Camera::Camera()
{
	//camera
	m_camPosition.x = 0.0f;
	m_camPosition.y = 3.7f;
	m_camPosition.z = -3.5f;

	m_camLookAt.x = 0.0f;
	m_camLookAt.y = 0.0f;
	m_camLookAt.z = 0.0f;

	m_camLookDirection.x = 0.0f;
	m_camLookDirection.y = 0.0f;
	m_camLookDirection.z = 0.0f;

	m_camRight.x = 0.0f;
	m_camRight.y = 0.0f;
	m_camRight.z = 0.0f;

	m_camOrientation.x = 0.0f;
	m_camOrientation.y = 0.0f;
	m_camOrientation.z = 0.0f;

	m_movespeed = 0.3f;
	m_camRotRate = 3.0f;
}

void Camera::Update(InputCommands* Input)
{

	if (m_camOrientation == Vector3(0.0f, 0.0f, 0.0f))
	{
		m_camOrientation = Vector3(0.1f, 0.1f, 0.1f);
	}

	if (m_camLookDirection == Vector3(0.0f, 0.0f, 0.0f))
	{
		m_camLookDirection = Vector3(0.1f, 0.1f, 0.1f);
	}

	//TODO  any more complex than this, and the camera should be abstracted out to somewhere else
//camera motion is on a plane, so kill the 7 component of the look direction
	Vector3 planarMotionVector = m_camLookDirection;
	planarMotionVector.y = 0.0;

	if (Input->rotRight)
	{
		m_camOrientation.y -= m_camRotRate;
	}
	if (Input->rotLeft)
	{
		m_camOrientation.y += m_camRotRate;
	}

	//create look direction from Euler angles in m_camOrientation
	m_camLookDirection.x = sin((m_camOrientation.y) * 3.1415 / 180);
	m_camLookDirection.z = cos((m_camOrientation.y) * 3.1415 / 180);

	//m_camLookDirection.x = cos((m_camOrientation.y) * 3.1415 / 180)*cos((m_displayList[i].m_orientation.x * 3.1415 / 180));
	//m_camLookDirection.y = sin((m_displayList[i].m_orientation.x * 3.1415 / 180));
	//m_camLookDirection.z = sin((m_camOrientation.y) * 3.1415 / 180)*cos((m_displayList[i].m_orientation.x * 3.1415 / 180));
	m_camLookDirection.Normalize();

	//create right vector from look Direction
	m_camLookDirection.Cross(Vector3::UnitY, m_camRight);

	//process input and update stuff
	if (Input->forward)
	{
		m_camPosition += m_camLookDirection * m_movespeed;
	}
	if (Input->back)
	{
		m_camPosition -= m_camLookDirection * m_movespeed;
	}
	if (Input->right)
	{
		m_camPosition += m_camRight * m_movespeed;
	}
	if (Input->left)
	{
		m_camPosition -= m_camRight * m_movespeed;
	}
	//update lookat point
	m_camLookAt = m_camPosition + m_camLookDirection;

	//apply camera vectors
	m_view = Matrix::CreateLookAt(m_camPosition, m_camLookAt, Vector3::UnitY);
}

DirectX::SimpleMath::Matrix Camera::GetView()
{
	return m_view;
}

