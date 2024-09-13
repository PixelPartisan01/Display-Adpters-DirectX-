#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")

#include <iostream>
#include <d3d12.h>
#include <dxgi1_4.h>
#include <vector>
#include <WindowsX.h>
#include <format>

void printAdapterInformation()
{
    IDXGIFactory4* mdxgiFactory = nullptr;
    UINT i = 0, j = 0;
    IDXGIAdapter* adapter = nullptr;
    IDXGIOutput* output = nullptr;
    DXGI_ADAPTER_DESC adapter_desc;
    DXGI_OUTPUT_DESC output_desc;

    HRESULT hr = CreateDXGIFactory1(IID_PPV_ARGS(&mdxgiFactory));
    if (FAILED(hr))
    {
        std::cerr << "Failed to create DXGI Factory" << std::endl;
        return;
    }

    while (mdxgiFactory->EnumAdapters(i, &adapter) != DXGI_ERROR_NOT_FOUND)
    {
        adapter->GetDesc(&adapter_desc);

        std::wstring text_adapter = std::format(L"Adapter {0}: {1}\n", i + 1, adapter_desc.Description);
        std::wprintf(L"%s", text_adapter.c_str());

        while (adapter->EnumOutputs(j, &output) != DXGI_ERROR_NOT_FOUND)
        {
            output->GetDesc(&output_desc);

            std::wstring text_output = std::format(L"*** Output {0}: {1}\n", j + 1, output_desc.DeviceName);
            std::wprintf(L"%s", text_output.c_str());
            ++j;
        }
        ++i;
    }
}

int main()
{
    printAdapterInformation();
    std::cout << "\n\nEnter to exit" << std::endl;
    std::cin.get();

    return 0;
}
