#include "GameGraphics.h"
#include <stdexcept>
#include <chrono>
#include <thread>

constexpr auto FPS = 60;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    try {
        GameGraphics gGraphics;
        if (!gGraphics.Initialize(hInstance, nCmdShow, L"DirectX Window", 800, 600)) {
            return -1;
        }

        // Message loop
        MSG msg = {};
        bool running = true;
        auto lastTime = std::chrono::high_resolution_clock::now();

        while (running) {
            auto currentTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> deltaTime = currentTime - lastTime;
            lastTime = currentTime;

            while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);

                if (msg.message == WM_QUIT) {
                    running = false;
                }
            }

            // Render frame
            gGraphics.BeginFrame();
            // Rendering would go here
            gGraphics.EndFrame();

            // Cap frame rate
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 / FPS));
        }

        return static_cast<int>(msg.wParam);
    }
    catch (const std::exception& e) {
        MessageBoxA(nullptr, e.what(), "Error", MB_OK | MB_ICONERROR);
        return -1;
    }
    catch (...) {
        MessageBoxA(nullptr, "An unknown error occurred", "Error", MB_OK | MB_ICONERROR);
        return -1;
    }
}