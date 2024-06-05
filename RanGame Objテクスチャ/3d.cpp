#include"3d.h"
#include"map.h"
void sreedObject::SetComer()
{
	SetCameraNearFar(9.f, 100.0f);
	SetCameraPositionAndTarget_UpVecY(VGet(0, 10, -20), VGet(0.f, 10.0f, 10.0f));
	CamerPosition = VGet(0, 0, 0);
	

	
}
void sreedObject::SetModel()
{
	ModelHandle = MV1LoadModel("img/3dOBJ/building.mv1");
	
	MV1SetScale(ModelHandle, VGet(0.01f, 0.01f, 0.01f));
	ModelPosition = VGet(0.0f, 4.0f, -6.0f);
	  MV1SetPosition(ModelHandle,ModelPosition) ;
	/*LotModel();*/
}
void sreedObject::DrawModel()
{
	MV1DrawModel(ModelHandle);
}
void sreedObject::MoveComer()
{
	/*if (CamerPosition.z >10)
	{
		CamerPosition.z--;
	}
	else if (CamerPosition.z <40)
	{
		CamerPosition.z++;
	}*/
	CamerPosition.x--;
	MV1SetPosition(ModelHandle, CamerPosition);
}
sreedObject::~sreedObject()
{
	MV1DeleteModel(ModelHandle);
}
void sreedObject::LotModel()
{
	
	MV1SetRotationXYZ(ModelHandle, VGet(90.0f * DX_PI_F / 180.0f, 90.0f * DX_PI_F / 180.0f, 0.0f));

}
	void sreedObject::ScaleModel()
	{
		NowTime = GetNowCount();
		int time = NowTime - StatTime / 1000;
		if (time % 100 == 0)
		{
			Direction *= -1;
		}
		
	}
	void sreedObject::ResetModel()
	{
		/*MV1SetRotationXYZ(ModelHandle, VGet(1.0f , 1.0f, 0.0f));*/
		/*MV1SetScale(ModelHandle, VGet(1.0f, 1.0f, 1.0f));*/
		ModelPosition = VGet(0.0f, 4.0f, -6.0f);
		MV1SetPosition(ModelHandle, ModelPosition);

	}
	const int sreedObject::GetModelHandle()
	{
		return ModelHandle;
	}
	void sreedObject::UpdataModel()
	{
		VECTOR Move = VGet(-0.1f, 0, 0);
		if (ModelPosition.x <= -20)
		{
			ModelPosition.x =20;
		}
		ModelPosition = VAdd(ModelPosition, Move);
		/*MV1SetRotationXYZ(ModelHandle,VGet(0.f,1,0 ));*/
		MV1SetPosition(ModelHandle, ModelPosition);

	}