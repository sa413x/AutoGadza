#include <mmdeviceapi.h>
#include <endpointvolume.h>

int main()
{
	HRESULT hResult = 0;
	hResult = CoInitialize(nullptr);
	
	if (FAILED(hResult))
		return EXIT_FAILURE;

	IMMDeviceEnumerator* pDeviceEnum = nullptr;
	hResult = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID*)&pDeviceEnum);

	if (FAILED(hResult))
		return EXIT_FAILURE;

	IMMDevice* pDevice = nullptr;
	hResult = pDeviceEnum->GetDefaultAudioEndpoint(eCapture, eMultimedia, &pDevice);
	pDeviceEnum->Release();
	pDeviceEnum = nullptr;

	if (FAILED(hResult))
		return EXIT_FAILURE;

	IAudioEndpointVolume* pVolume = nullptr;
	hResult = pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, nullptr, (LPVOID*)&pVolume);
	pDevice->Release();
	pDevice = nullptr;

	if (FAILED(hResult))
		return EXIT_FAILURE;
	
	while (true)
	{
		if (GetAsyncKeyState(VK_LMENU))
		{
			pVolume->SetMasterVolumeLevelScalar(1.f, nullptr);
			Sleep(50);
			pVolume->SetMasterVolumeLevelScalar(0.f, nullptr);
			Sleep(50);
		} else pVolume->SetMasterVolumeLevelScalar(1.f, nullptr);
	}

	pVolume->Release();
	pVolume = nullptr;

	CoUninitialize();

	return EXIT_SUCCESS;
}