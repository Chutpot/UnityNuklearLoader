#pragma once

#include "IUnityRenderer.h"

class D3D12Renderer : public IUnityRenderer
{
public:
	D3D12Renderer(IUnityInterfaces* unityInterfaces, nk_context** ctx);
	~D3D12Renderer();
	void Render() override;
	void Resize(int width, int height) override;

private:

};