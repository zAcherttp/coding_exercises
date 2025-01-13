#pragma once
#include "Debug.h"
#include <windows.h>
#include <d3d11.h>
#include <string>

class GameGraphics {
public:
    GameGraphics();
    ~GameGraphics();

    // Delete copy constructor and assignment operator
    GameGraphics(const GameGraphics&) = delete;
    GameGraphics& operator=(const GameGraphics&) = delete;

    bool Initialize(HINSTANCE hInstance, int nCmdShow, const wchar_t* windowTitle, int width, int height);
    void Shutdown();
    void BeginFrame();
    void EndFrame();
	void OnResize();

    // Getters
    HWND GetWindowHandle() const { return m_hwnd; }
    ID3D11Device* GetDevice() const { return m_device; }
    ID3D11DeviceContext* GetDeviceContext() const { return m_deviceContext; }
    int GetWindowWidth() const { return m_windowWidth; }
    int GetWindowHeight() const { return m_windowHeight; }

private:
    // Window Management
    HWND m_hwnd;
    int m_windowWidth;
    int m_windowHeight;
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    bool InitializeWindow(HINSTANCE hInstance, int nCmdShow, const wchar_t* windowTitle);

    // DirectX Components
    ID3D11Device* m_device;
    ID3D11DeviceContext* m_deviceContext;
    IDXGISwapChain* m_swapChain;
    ID3D11RenderTargetView* m_renderTargetView;
    bool InitializeDirectX();
    void CreateRenderTargetView();

    static GameGraphics* s_gGraphics;
};

