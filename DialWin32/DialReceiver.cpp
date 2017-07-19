#include"stdafx.h"

// Vector.hに必要
#include<cassert>

// DialReceiverヘッダ
#include"DialReceiver.h"

// IVectorの実装と特殊化定義
#include"win2d/Vector.h"
#include"Vector_h.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::Windows::Foundation;

DialWin32::DialReceiver::DialReceiver() {
	// 初期化
	Windows::Foundation::Initialize(RO_INIT_MULTITHREADED);

	// ActivationFactoryの取得
	Windows::Foundation::GetActivationFactory(
		HStringReference(RuntimeClass_Windows_UI_Input_RadialController).Get(),
		&_controllerInterop);
	Windows::Foundation::GetActivationFactory(
		HStringReference(RuntimeClass_Windows_UI_Input_RadialControllerConfiguration).Get(),
		&_configurationInterop);
	Windows::Foundation::GetActivationFactory(
		HStringReference(RuntimeClass_Windows_UI_Input_RadialControllerMenuItem).Get(),
		&_menuItemStatics);
	_menuItemStatics->QueryInterface(IID_PPV_ARGS(&_menuItemStatics2));
}

HRESULT DialWin32::DialReceiver::Init(HWND hwnd) {
	// HWNDに対するインスタンスの取得
	_controllerInterop->CreateForWindow(hwnd, IID_PPV_ARGS(&_controller));
	_configurationInterop->GetForWindow(hwnd, IID_PPV_ARGS(&_configuration));
	// 派生型を取得
	_controller->QueryInterface(_controller2.GetAddressOf());
	_configuration->QueryInterface(_configuration2.GetAddressOf());
	// メニューを取得
	_controller->get_Menu(&_menu);
	return S_OK;
}

HRESULT DialWin32::DialReceiver::SetSystemIcon(ABI::Windows::UI::Input::RadialControllerSystemMenuItemKind kind) {
	// ここでIVectorのインスタンスを作る
	auto v = Microsoft::WRL::Make<collections::Vector<ABI::Windows::UI::Input::RadialControllerSystemMenuItemKind>>();
	// アイコンを設定する
	v->Append(kind);
	return _configuration->SetDefaultMenuItems(v.Get());
}

HRESULT DialWin32::DialReceiver::ClearSystemIcons() {
	auto v = Microsoft::WRL::Make<collections::Vector<ABI::Windows::UI::Input::RadialControllerSystemMenuItemKind>>();
	return _configuration->SetDefaultMenuItems(v.Get());
}

HRESULT DialWin32::DialReceiver::AddItemFronFontGlyph(wchar_t* label, wchar_t* glyph) {
	Microsoft::WRL::ComPtr<ABI::Windows::UI::Input::IRadialControllerMenuItem> menuItem;
	// Create MenuItem from Glyph
	_menuItemStatics2->CreateFromFontGlyph(HStringReference(label).Get(), HStringReference(glyph).Get(),
		HStringReference(L"Segoe UI Emoji").Get(), &menuItem);
	// Append MenuItem
	Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::Windows::UI::Input::RadialControllerMenuItem*>> items;
	_menu->get_Items(&items);
	return items->Append(menuItem.Get());
}

HRESULT DialWin32::DialReceiver::AddItemFromKnownIcon(wchar_t* label, ABI::Windows::UI::Input::RadialControllerMenuKnownIcon icon) {
	Microsoft::WRL::ComPtr<ABI::Windows::UI::Input::IRadialControllerMenuItem> menuItem;
	// Create MenuItem from KnownIcon
	_menuItemStatics->CreateFromKnownIcon(HStringReference(label).Get(), icon, &menuItem);
	// Append MenuItem
	Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::Windows::UI::Input::RadialControllerMenuItem*>> items;
	_menu->get_Items(&items);
	return items->Append(menuItem.Get());
}