#ifndef _NUKLEAR_APP_H_
#define _NUKLEAR_APP_H_

#include "UnityNuklearLoader.h"

class NuklearApp
{
public:
	virtual void UNITY_INTERFACE_EXPORT Render(nk_context* context)=0;
};
#endif