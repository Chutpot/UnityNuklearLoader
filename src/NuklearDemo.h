#pragma once

#include "..\UnityNuklearLoader.h"
#include "UnityLogger.h"

class NuklearDemo : public NuklearApp
{
public:
	NuklearDemo();
	~NuklearDemo();
	void UNITY_INTERFACE_EXPORT Render(nk_context* context) override;
	void SetRender(bool isRendering);
private:
	struct nk_colorf m_bg;
	bool m_isRendering;
};

