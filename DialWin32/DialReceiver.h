#pragma once

#include<wrl.h>
#include<wrl/implements.h>
#include<windows.foundation.h>
#include<windows.ui.input.h>

#include<RadialControllerInterop.h>

namespace DialWin32 {
	class DialReceiver {
	private:
		// Interop
		Microsoft::WRL::ComPtr<IRadialControllerInterop> _controllerInterop;
		Microsoft::WRL::ComPtr<IRadialControllerConfigurationInterop> _configurationInterop;
		// Instance
		Microsoft::WRL::ComPtr<ABI::Windows::UI::Input::IRadialController> _controller;
		Microsoft::WRL::ComPtr<ABI::Windows::UI::Input::IRadialController2> _controller2;
		Microsoft::WRL::ComPtr<ABI::Windows::UI::Input::IRadialControllerConfiguration> _configuration;
		Microsoft::WRL::ComPtr<ABI::Windows::UI::Input::IRadialControllerConfiguration2> _configuration2;
		Microsoft::WRL::ComPtr<ABI::Windows::UI::Input::IRadialControllerMenuItemStatics> _menuItemStatics;
		Microsoft::WRL::ComPtr<ABI::Windows::UI::Input::IRadialControllerMenuItemStatics2> _menuItemStatics2;
		Microsoft::WRL::ComPtr<ABI::Windows::UI::Input::IRadialControllerMenu> _menu;

	public:
		DialReceiver();
		HRESULT Init(HWND hwnd);
		HRESULT SetSystemIcon(ABI::Windows::UI::Input::RadialControllerSystemMenuItemKind);
		HRESULT ClearSystemIcons();
		HRESULT AddItemFronFontGlyph(wchar_t* label, wchar_t* glyph);
		HRESULT AddItemFromKnownIcon(wchar_t* label, ABI::Windows::UI::Input::RadialControllerMenuKnownIcon icon);
	};
}