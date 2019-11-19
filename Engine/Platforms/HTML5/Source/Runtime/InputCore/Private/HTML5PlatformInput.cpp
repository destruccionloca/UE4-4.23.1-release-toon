// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "HTML5PlatformInput.h"

THIRD_PARTY_INCLUDES_START
#ifdef HTML5_USE_SDL2
	#include <SDL.h>
#else
	#include "emscripten/key_codes.h"
#endif
THIRD_PARTY_INCLUDES_END

uint32 FHTML5PlatformInput::GetKeyMap(uint32* KeyCodes, FString* KeyNames, uint32 MaxMappings)
{
#define ADDKEYMAP(KeyCode, KeyName)		if (NumMappings<MaxMappings) { KeyCodes[NumMappings]=KeyCode; KeyNames[NumMappings]=KeyName; ++NumMappings; };

	uint32 NumMappings = 0;

	if (KeyCodes && KeyNames && (MaxMappings > 0))
	{
#ifdef HTML5_USE_SDL2
		ADDKEYMAP(SDL_SCANCODE_BACKSPACE, TEXT("BackSpace"));
		ADDKEYMAP(SDL_SCANCODE_TAB, TEXT("Tab"));
		ADDKEYMAP(SDL_SCANCODE_RETURN, TEXT("Enter"));
		ADDKEYMAP(SDL_SCANCODE_RETURN2, TEXT("Enter"));
		ADDKEYMAP(SDL_SCANCODE_KP_ENTER, TEXT("Enter"));
		ADDKEYMAP(SDL_SCANCODE_PAUSE, TEXT("Pause"));

		ADDKEYMAP(SDL_SCANCODE_ESCAPE, TEXT("Escape"));
		ADDKEYMAP(SDL_SCANCODE_SPACE, TEXT("SpaceBar"));
		ADDKEYMAP(SDL_SCANCODE_PAGEUP, TEXT("PageUp"));
		ADDKEYMAP(SDL_SCANCODE_PAGEDOWN, TEXT("PageDown"));
		ADDKEYMAP(SDL_SCANCODE_END, TEXT("End"));
		ADDKEYMAP(SDL_SCANCODE_HOME, TEXT("Home"));

		ADDKEYMAP(SDL_SCANCODE_LEFT, TEXT("Left"));
		ADDKEYMAP(SDL_SCANCODE_UP, TEXT("Up"));
		ADDKEYMAP(SDL_SCANCODE_RIGHT, TEXT("Right"));
		ADDKEYMAP(SDL_SCANCODE_DOWN, TEXT("Down"));

		ADDKEYMAP(SDL_SCANCODE_INSERT, TEXT("Insert"));
		ADDKEYMAP(SDL_SCANCODE_DELETE, TEXT("Delete"));

		ADDKEYMAP(SDL_SCANCODE_F1, TEXT("F1"));
		ADDKEYMAP(SDL_SCANCODE_F2, TEXT("F2"));
		ADDKEYMAP(SDL_SCANCODE_F3, TEXT("F3"));
		ADDKEYMAP(SDL_SCANCODE_F4, TEXT("F4"));
		ADDKEYMAP(SDL_SCANCODE_F5, TEXT("F5"));
		ADDKEYMAP(SDL_SCANCODE_F6, TEXT("F6"));
		ADDKEYMAP(SDL_SCANCODE_F7, TEXT("F7"));
		ADDKEYMAP(SDL_SCANCODE_F8, TEXT("F8"));
		ADDKEYMAP(SDL_SCANCODE_F9, TEXT("F9"));
		ADDKEYMAP(SDL_SCANCODE_F10, TEXT("F10"));
		ADDKEYMAP(SDL_SCANCODE_F11, TEXT("F11"));
		ADDKEYMAP(SDL_SCANCODE_F12, TEXT("F12"));

		ADDKEYMAP(SDL_SCANCODE_LCTRL, TEXT("LeftControl"));
		ADDKEYMAP(SDL_SCANCODE_LSHIFT, TEXT("LeftShift"));
		ADDKEYMAP(SDL_SCANCODE_LALT, TEXT("LeftAlt"));
		ADDKEYMAP(SDL_SCANCODE_LGUI, TEXT("LeftCommand"));
		ADDKEYMAP(SDL_SCANCODE_RCTRL, TEXT("RightControl"));
		ADDKEYMAP(SDL_SCANCODE_RSHIFT, TEXT("RightShift"));
		ADDKEYMAP(SDL_SCANCODE_RALT, TEXT("RightAlt"));
		ADDKEYMAP(SDL_SCANCODE_RGUI, TEXT("RightCommand"));

		ADDKEYMAP(SDL_SCANCODE_KP_0, TEXT("NumPadZero"));
		ADDKEYMAP(SDL_SCANCODE_KP_1, TEXT("NumPadOne"));
		ADDKEYMAP(SDL_SCANCODE_KP_2, TEXT("NumPadTwo"));
		ADDKEYMAP(SDL_SCANCODE_KP_3, TEXT("NumPadThree"));
		ADDKEYMAP(SDL_SCANCODE_KP_4, TEXT("NumPadFour"));
		ADDKEYMAP(SDL_SCANCODE_KP_5, TEXT("NumPadFive"));
		ADDKEYMAP(SDL_SCANCODE_KP_6, TEXT("NumPadSix"));
		ADDKEYMAP(SDL_SCANCODE_KP_7, TEXT("NumPadSeven"));
		ADDKEYMAP(SDL_SCANCODE_KP_8, TEXT("NumPadEight"));
		ADDKEYMAP(SDL_SCANCODE_KP_9, TEXT("NumPadNine"));
		ADDKEYMAP(SDL_SCANCODE_KP_MULTIPLY, TEXT("Multiply"));
		ADDKEYMAP(SDL_SCANCODE_KP_PLUS, TEXT("Add"));
		ADDKEYMAP(SDL_SCANCODE_KP_MINUS, TEXT("Subtract"));
		ADDKEYMAP(SDL_SCANCODE_KP_DECIMAL, TEXT("Decimal"));
		ADDKEYMAP(SDL_SCANCODE_KP_DIVIDE, TEXT("Divide"));
		ADDKEYMAP(SDL_SCANCODE_KP_PERIOD, TEXT("Period"));

		ADDKEYMAP(SDL_SCANCODE_CAPSLOCK, TEXT("CapsLock"));
		ADDKEYMAP(SDL_SCANCODE_NUMLOCKCLEAR, TEXT("NumLock"));
		ADDKEYMAP(SDL_SCANCODE_SCROLLLOCK, TEXT("ScrollLock"));
		ADDKEYMAP(SDL_SCANCODE_CANCEL, TEXT("Cancel")); // UE-58441 -- CTRL+Pause/Break and CTRL+ScrollLock
		ADDKEYMAP(SDL_SCANCODE_APPLICATION, TEXT("Menu")); // UE-58441 -- contextual menu
#else
		ADDKEYMAP(DOM_VK_BACK_SPACE, TEXT("BackSpace"));
		ADDKEYMAP(DOM_VK_TAB, TEXT("Tab"));
		ADDKEYMAP(DOM_VK_RETURN, TEXT("Enter"));
//		ADDKEYMAP(DOM_VK_RETURN2, TEXT("Enter"));
		ADDKEYMAP(DOM_VK_ENTER, TEXT("Enter"));
		ADDKEYMAP(DOM_VK_PAUSE, TEXT("Pause"));

		ADDKEYMAP(DOM_VK_ESCAPE, TEXT("Escape"));
		ADDKEYMAP(DOM_VK_SPACE, TEXT("SpaceBar"));
		ADDKEYMAP(DOM_VK_PAGE_UP, TEXT("PageUp"));
		ADDKEYMAP(DOM_VK_PAGE_DOWN, TEXT("PageDown"));
		ADDKEYMAP(DOM_VK_END, TEXT("End"));
		ADDKEYMAP(DOM_VK_HOME, TEXT("Home"));

		ADDKEYMAP(DOM_VK_LEFT, TEXT("Left"));
		ADDKEYMAP(DOM_VK_UP, TEXT("Up"));
		ADDKEYMAP(DOM_VK_RIGHT, TEXT("Right"));
		ADDKEYMAP(DOM_VK_DOWN, TEXT("Down"));

		ADDKEYMAP(DOM_VK_INSERT, TEXT("Insert"));
		ADDKEYMAP(DOM_VK_DELETE, TEXT("Delete"));

		ADDKEYMAP(DOM_VK_F1, TEXT("F1"));
		ADDKEYMAP(DOM_VK_F2, TEXT("F2"));
		ADDKEYMAP(DOM_VK_F3, TEXT("F3"));
		ADDKEYMAP(DOM_VK_F4, TEXT("F4"));
		ADDKEYMAP(DOM_VK_F5, TEXT("F5"));
		ADDKEYMAP(DOM_VK_F6, TEXT("F6"));
		ADDKEYMAP(DOM_VK_F7, TEXT("F7"));
		ADDKEYMAP(DOM_VK_F8, TEXT("F8"));
		ADDKEYMAP(DOM_VK_F9, TEXT("F9"));
		ADDKEYMAP(DOM_VK_F10, TEXT("F10"));
		ADDKEYMAP(DOM_VK_F11, TEXT("F11"));
		ADDKEYMAP(DOM_VK_F12, TEXT("F12"));

		ADDKEYMAP(DOM_VK_CONTROL, TEXT("Control"));
		ADDKEYMAP(DOM_VK_SHIFT, TEXT("Shift"));
		ADDKEYMAP(DOM_VK_ALT, TEXT("Alt"));
		ADDKEYMAP(DOM_VK_WIN, TEXT("Command"));
//		ADDKEYMAP(DOM_VK_CONTROL, TEXT("LeftControl"));
//		ADDKEYMAP(DOM_VK_SHIFT, TEXT("LeftShift"));
//		ADDKEYMAP(DOM_VK_ALT, TEXT("LeftAlt"));
//		ADDKEYMAP(DOM_VK_WIN, TEXT("LeftCommand"));
//		ADDKEYMAP(DOM_VK_CONTROL, TEXT("RightControl"));
//		ADDKEYMAP(DOM_VK_SHIFT, TEXT("RightShift"));
//		ADDKEYMAP(DOM_VK_ALT, TEXT("RightAlt"));
//		ADDKEYMAP(DOM_VK_WIN, TEXT("RightCommand"));

		ADDKEYMAP(DOM_VK_NUMPAD0, TEXT("NumPadZero"));
		ADDKEYMAP(DOM_VK_NUMPAD1, TEXT("NumPadOne"));
		ADDKEYMAP(DOM_VK_NUMPAD2, TEXT("NumPadTwo"));
		ADDKEYMAP(DOM_VK_NUMPAD3, TEXT("NumPadThree"));
		ADDKEYMAP(DOM_VK_NUMPAD4, TEXT("NumPadFour"));
		ADDKEYMAP(DOM_VK_NUMPAD5, TEXT("NumPadFive"));
		ADDKEYMAP(DOM_VK_NUMPAD6, TEXT("NumPadSix"));
		ADDKEYMAP(DOM_VK_NUMPAD7, TEXT("NumPadSeven"));
		ADDKEYMAP(DOM_VK_NUMPAD8, TEXT("NumPadEight"));
		ADDKEYMAP(DOM_VK_NUMPAD9, TEXT("NumPadNine"));
		ADDKEYMAP(DOM_VK_MULTIPLY, TEXT("Multiply"));
		ADDKEYMAP(DOM_VK_PLUS, TEXT("Add"));
		ADDKEYMAP(DOM_VK_SUBTRACT, TEXT("Subtract"));
		ADDKEYMAP(DOM_VK_DECIMAL, TEXT("Decimal"));
		ADDKEYMAP(DOM_VK_DIVIDE, TEXT("Divide"));
		ADDKEYMAP(DOM_VK_PERIOD, TEXT("Period"));

		ADDKEYMAP(DOM_VK_CAPS_LOCK, TEXT("CapsLock"));
		ADDKEYMAP(DOM_VK_NUM_LOCK, TEXT("NumLock"));
		ADDKEYMAP(DOM_VK_SCROLL_LOCK, TEXT("ScrollLock"));
		ADDKEYMAP(DOM_VK_CANCEL, TEXT("Cancel")); // UE-58441 -- CTRL+Pause/Break and CTRL+ScrollLock
		ADDKEYMAP(DOM_VK_CONTEXT_MENU, TEXT("Menu")); // UE-58441 -- contextual menu
#endif
	}
#undef ADDKEYMAP

	check(NumMappings < MaxMappings);
	return NumMappings;
}

uint32 FHTML5PlatformInput::GetCharKeyMap(uint32* KeyCodes, FString* KeyNames, uint32 MaxMappings)
{
	return FGenericPlatformInput::GetStandardPrintableKeyMap(KeyCodes, KeyNames, MaxMappings, false, true);
}