/////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                   ///
///                                      THIS CODE IS PART OF:                                        ///
///                                       CryoMoon Engine (C)                                         ///
///                                                                                                   ///
///                                     WHICH IS LICENSED UNDER                                       ///
///                                          MIT License                                              ///
///                                      All Right Reserved.                                          ///
///                                                                                                   ///
/////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                   ///
///   Copyright (c) 2024 Myin Studios                                                                 ///
///                                                                                                   ///
///   Permission is hereby granted, free of charge,  to any person obtaining a copy of this software  ///
///   and associated documentation files (the "Software"), to deal in the Software without            ///
///   restriction, including without limitation the rights to use, copy, modify, merge, publish,      ///
///   distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the   ///
///   Software is furnished to do so, subject to the following conditions:                            ///
///                                                                                                   ///
///   The above copyright notice and this permission notice shall be included in all copies or        ///
///   substantial portions of the Software.                                                           ///
///                                                                                                   ///
///   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING   ///
///   BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND      ///
///   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,    ///
///   DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  ///
///   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.         ///
///                                                                                                   ///
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "CMTypes.h"
#include <Windows.h>

//mouse events

static constexpr CMUInt CMMouseMove = 0x0001;

CMUInt CMMouseLButtonDown = GetKeyState(VK_LBUTTON) & 0x8000;
static constexpr CMUInt CMMouseRButtonDown = 0x0003;

static constexpr CMUInt CMMouseLButtonUp = 0x0004;
static constexpr CMUInt CMMouseRButtonUp = 0x0005;

static constexpr CMUInt CMMouseLButtonDoubleClick = 0x0006;
static constexpr CMUInt CMMouseRButtonDoubleClick = 0x0007;

CMUInt getKey(CMUInt key)
{
	if (key > 0 && key < 256)
		if (GetKeyState(key) & 0x8001)
			return key;
}

struct CMKeyboardEvent
{
	static CMUInt A;
	static CMUInt B;
	static CMUInt C;
	static CMUInt D;
	static CMUInt E;
	static CMUInt F;
	static CMUInt G;
	static CMUInt H;
	static CMUInt I;
	static CMUInt J;
	static CMUInt K;
	static CMUInt L;
	static CMUInt M;
	static CMUInt N;
	static CMUInt O;
	static CMUInt P;
	static CMUInt Q;
	static CMUInt R;
	static CMUInt S;
	static CMUInt T;
	static CMUInt U;
	static CMUInt V;
	static CMUInt W;
	static CMUInt X;
	static CMUInt Y;
	static CMUInt Z;
	
	static CMUInt Space;
	static CMUInt Esc;
	static CMUInt BackSpace;
	
	static CMUInt Num1;
	static CMUInt Num2;
	static CMUInt Num3;
	static CMUInt Num4;
	static CMUInt Num5;
	static CMUInt Num6;
	static CMUInt Num7;
	static CMUInt Num8;
	static CMUInt Num9;
	static CMUInt Num0;

	static CMUInt NumPad1;
	static CMUInt NumPad2;
	static CMUInt NumPad3;
	static CMUInt NumPad4;
	static CMUInt NumPad5;
	static CMUInt NumPad6;
	static CMUInt NumPad7;
	static CMUInt NumPad8;
	static CMUInt NumPad9;
	static CMUInt NumPad0;
};