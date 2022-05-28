#include "pipeline.h"

const Matrix4f& Pipeline::GetVPTrans()
{
    Matrix4f CameraTranslationTrans, CameraRotateTrans, PersProjTrans;

    CameraTranslationTrans.InitTranslationTransform(-m_camera.Pos.x, -m_camera.Pos.y, -m_camera.Pos.z);
    CameraRotateTrans.InitCameraTransform(m_camera.Target, m_camera.Up);
    PersProjTrans.InitPersProjTransform(m_persProjInfo);
    
    m_VPTtransformation = PersProjTrans * CameraRotateTrans * CameraTranslationTrans;
    return m_VPTtransformation;
}

const Matrix4f& Pipeline::GetWorldTrans()
{
    Matrix4f ScaleTrans, RotateTrans, TranslationTrans;

    ScaleTrans.InitScaleTransform(m_scale.x, m_scale.y, m_scale.z);
    RotateTrans.InitRotateTransform(m_rotateInfo.x, m_rotateInfo.y, m_rotateInfo.z);
    TranslationTrans.InitTranslationTransform(m_worldPos.x, m_worldPos.y, m_worldPos.z);

    m_WorldTransformation = TranslationTrans * RotateTrans * ScaleTrans;
    return m_WorldTransformation;
}

const Matrix4f& Pipeline::GetWVPTrans()
{
    GetWorldTrans();
    GetVPTrans();

    m_WVPtransformation = m_VPTtransformation * m_WorldTransformation;
    return m_WVPtransformation;
}

const Matrix4f& Pipeline::GetWVTrans()
{
	GetWorldTrans();
	
	Matrix4f CameraTranslationTrans, CameraRotateTrans;

	CameraTranslationTrans.InitTranslationTransform(-m_camera.Pos.x, -m_camera.Pos.y, -m_camera.Pos.z);
	CameraRotateTrans.InitCameraTransform(m_camera.Target, m_camera.Up);
	
	m_WVtransformation = CameraRotateTrans * CameraTranslationTrans * m_WorldTransformation;
	return m_WVtransformation;
}



