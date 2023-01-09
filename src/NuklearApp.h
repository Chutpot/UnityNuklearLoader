#pragma once

#include "..\UnityNuklearLoader.h"

class NuklearApp
{
public:
	virtual void UNITY_INTERFACE_EXPORT Render(nk_context* context)=0;
};