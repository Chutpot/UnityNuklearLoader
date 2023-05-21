#pragma once

#include "IUnityRenderer.h"

class D3D11Renderer : public IUnityRenderer
{
public:
	D3D11Renderer(IUnityInterfaces* unityInterfaces, nk_context** ctx);
	~D3D11Renderer();
	void Render() override;
	void Resize(int width, int height) override;

private:

};