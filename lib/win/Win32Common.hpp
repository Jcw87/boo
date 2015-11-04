#ifndef BOO_WIN32COMMON_HPP
#define BOO_WIN32COMMON_HPP

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS 1 /* STFU MSVC */
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#include <windows.h>
#include <unordered_map>

namespace boo {class IWindow;}

#if _WIN32_WINNT_WIN10
#include <dxgi1_4.h>
#include <d3d12.h>
#include <d3d11_1.h>

struct D3D12Context
{
    ComPtr<ID3D12Device> m_dev;
    ComPtr<ID3D12CommandAllocator> m_qalloc[2];
    ComPtr<ID3D12CommandQueue> m_q;
    ComPtr<ID3D12CommandAllocator> m_loadqalloc;
    ComPtr<ID3D12CommandQueue> m_loadq;
    ComPtr<ID3D12Fence> m_frameFence;
    ComPtr<ID3D12RootSignature> m_rs;
    struct Window
    {
        ComPtr<IDXGISwapChain3> m_swapChain;
        ComPtr<ID3D12Resource> m_fb[2]; /* Double-buffered */
        UINT m_backBuf = 0;
        size_t width, height;
    };
    std::unordered_map<boo::IWindow*, Window> m_windows;
};

#elif _WIN32_WINNT_WIN7
#include <dxgi1_2.h>
#include <d3d11_1.h>
#else
#error Unsupported Windows target
#endif

struct D3D11Context
{
    ComPtr<ID3D11Device1> m_dev;
    ComPtr<ID3D11DeviceContext1> m_devCtx;
    struct Window
    {
        IDXGISwapChain1* m_swapChain;
        size_t width, height;
    };
    std::unordered_map<boo::IWindow*, Window> m_windows;
};

#include "boo/System.hpp"

struct D3DAppContext
{
    D3D11Context m_ctx11;
#if _WIN32_WINNT_WIN10
    D3D12Context m_ctx12;
#endif
    ComPtr<IDXGIFactory2> m_dxFactory;
};

struct HWNDEvent
{
    UINT uMsg;
    WPARAM wParam;
    LPARAM lParam;
    HWNDEvent(UINT m, WPARAM w, LPARAM l)
    : uMsg(m), wParam(w), lParam(l) {}
};

#endif // BOO_WIN32COMMON_HPP