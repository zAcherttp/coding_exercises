#include "GameGraphics.h"
#include <DirectXColors.h>
#include <stdexcept>

GameGraphics* GameGraphics::s_gGraphics = nullptr;

GameGraphics::GameGraphics()
    : m_hwnd(nullptr)
    , m_windowWidth(0)
    , m_windowHeight(0)
    , m_device(nullptr)
    , m_deviceContext(nullptr)
    , m_swapChain(nullptr)
    , m_renderTargetView(nullptr) {
    s_gGraphics = this;
}

GameGraphics::~GameGraphics() {
    Shutdown();
    s_gGraphics = nullptr;
}

bool GameGraphics::Initialize(HINSTANCE hInstance, int nCmdShow, const wchar_t* windowTitle, int width, int height) {
    m_windowWidth = width;
    m_windowHeight = height;

    if (!InitializeWindow(hInstance, nCmdShow, windowTitle)) {
		throw std::runtime_error("[" __FUNCTION__ "] Failed to initialize window");
        return false;
    }

    if (!InitializeDirectX()) {
		throw std::runtime_error("[" __FUNCTION__ "] Failed to initialize DirectX");
        return false;
    }

    return true;
}

void GameGraphics::CreateRenderTargetView() {
    if (m_renderTargetView) {
        m_renderTargetView->Release();
        m_renderTargetView = nullptr;
    }

    // Create render target view
    ID3D11Texture2D* backBuffer{};
    HRESULT hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
        reinterpret_cast<void**>(&backBuffer));

    if (FAILED(hr)) {
		throw std::runtime_error("[" __FUNCTION__ "] Failed to get swap chain buffer");
    }

    hr = m_device->CreateRenderTargetView(backBuffer, nullptr, &m_renderTargetView);
    backBuffer->Release();

    if (FAILED(hr)) {
		throw std::runtime_error("[" __FUNCTION__ "] Failed to create render target view");
    }

    // Set render target and viewport
    m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, nullptr);

    D3D11_VIEWPORT viewport = {};
    viewport.TopLeftX = 0.0f;
    viewport.TopLeftY = 0.0f;
    viewport.Width = static_cast<float>(m_windowWidth);
    viewport.Height = static_cast<float>(m_windowHeight);
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;

    m_deviceContext->RSSetViewports(1, &viewport);
}

bool GameGraphics::InitializeWindow(HINSTANCE hInstance, int nCmdShow, const wchar_t* windowTitle) {
    // Register window class
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.lpszClassName = L"GameWindowClass";

    if (!RegisterClassEx(&wc)) {
		throw std::runtime_error("[" __FUNCTION__ "] Failed to register window class");
        return false;
    }

    // Calculate window size based on desired client area
    RECT rc = { 0, 0, m_windowWidth, m_windowHeight };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    // Create window
    m_hwnd = CreateWindow(
        L"GameWindowClass", windowTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        rc.right - rc.left, rc.bottom - rc.top,
        nullptr, nullptr, hInstance, nullptr
    );

    if (!m_hwnd) {
		throw std::runtime_error("[" __FUNCTION__ "] Failed to create window");
        return false;
    }

    ShowWindow(m_hwnd, nCmdShow);
    UpdateWindow(m_hwnd);

    return true;
}

bool GameGraphics::InitializeDirectX() {
    DXGI_SWAP_CHAIN_DESC scd = {};
    scd.BufferCount = 1;
    scd.BufferDesc.Width = m_windowWidth;
    scd.BufferDesc.Height = m_windowHeight;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferDesc.RefreshRate.Numerator = 60;
    scd.BufferDesc.RefreshRate.Denominator = 1;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = m_hwnd;
    scd.SampleDesc.Count = 1;
    scd.SampleDesc.Quality = 0;
    scd.Windowed = TRUE;

    D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

    UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
    creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        creationFlags,
        &featureLevel,
        1,
        D3D11_SDK_VERSION,
        &scd,
        &m_swapChain,
        &m_device,
        nullptr,
        &m_deviceContext
    );

    if (FAILED(hr)) {
		throw std::runtime_error("[" __FUNCTION__ "] Failed to create device and swap chain");
        return false;
    }

    CreateRenderTargetView();
    return true;
}

void GameGraphics::BeginFrame() {
    m_deviceContext->ClearRenderTargetView(m_renderTargetView, DirectX::Colors::Blue);
}

void GameGraphics::EndFrame() {
    m_swapChain->Present(1, 0);
}

void GameGraphics::OnResize() {
    if (!m_device || !m_swapChain) {
        return;
    }

    // Release render target view
    if (m_renderTargetView) {
        m_renderTargetView->Release();
        m_renderTargetView = nullptr;
    }

    // Get the actual client area dimensions
    RECT clientRect;
    GetClientRect(m_hwnd, &clientRect);
    m_windowWidth = clientRect.right - clientRect.left;
    m_windowHeight = clientRect.bottom - clientRect.top;

    // Resize swap chain buffers
    HRESULT hr = m_swapChain->ResizeBuffers(
        1,
        m_windowWidth,
        m_windowHeight,
        DXGI_FORMAT_R8G8B8A8_UNORM,
        0
    );

    if (FAILED(hr)) {
		throw std::runtime_error("[" __FUNCTION__ "] Failed to resize swap chain buffers");
    }

    CreateRenderTargetView();
}

void GameGraphics::Shutdown() {
    if (m_deviceContext) m_deviceContext->ClearState();

    if (m_renderTargetView) {
        m_renderTargetView->Release();
        m_renderTargetView = nullptr;
    }
    if (m_swapChain) {
        m_swapChain->Release();
        m_swapChain = nullptr;
    }
    if (m_deviceContext) {
        m_deviceContext->Release();
        m_deviceContext = nullptr;
    }
    if (m_device) {
        m_device->Release();
        m_device = nullptr;
    }

    if (m_hwnd) {
        DestroyWindow(m_hwnd);
        m_hwnd = nullptr;
    }
}

LRESULT CALLBACK GameGraphics::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_SIZE:
        if (s_gGraphics && wParam != SIZE_MINIMIZED) {
            s_gGraphics->m_windowWidth = LOWORD(lParam);
            s_gGraphics->m_windowHeight = HIWORD(lParam);
        }
        return 0;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}