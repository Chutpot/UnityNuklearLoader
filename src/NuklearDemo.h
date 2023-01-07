#ifndef _NUKLEAR_DEMO_H_
#define _NUKLEAR_DEMO_H_

#include "UnityNuklearLoader.h"

class NuklearDemo : public NuklearApp
{
public:
	NuklearDemo();
	~NuklearDemo();
	void UNITY_INTERFACE_EXPORT Render(nk_context* context) override;
};

#endif // !_NUKLEAR_DEMO_H_
