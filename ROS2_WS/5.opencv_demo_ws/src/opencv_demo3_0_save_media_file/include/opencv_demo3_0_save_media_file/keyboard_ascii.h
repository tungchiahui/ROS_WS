/*
FIle Name: keyboard_ascii.h
Version: v0.5
State: Pre-Release
Author: Tung Chia-hui
Website: https://github.com/tungchiahui
E-mail: tungchiahui@gmail.com
Organization: VinciRobot
Date: 2023-12-05
*/
#ifndef __KEYBOARD_ASCII_H_
#define __KEYBOARD_ASCII_H_

namespace keyboard_ascii
{
    typedef enum
    {
        BackSpace = 8,
        Tab = 9,

        Clear = 12,
        Enter = 13,

        Shift = 16,
        Control = 17,
        Alt = 18,

        CapeLock = 20,

        Esc = 27,

        Spacebar = 32,
        PageUp = 33,
        PageDown = 34,
        End = 35,
        Home = 36,
        LeftArrow = 37,
        UpArrow = 38,
        RightArrow = 39,
        DwArrow = 40,

        Insert = 45,
        Delete = 46,

        NumMain0 = 48,
        NumMain1 = 49,
        NumMain2 = 50,
        NUmMain3 = 51,
        NUmMain4 = 52,
        NUmMain5 = 53,
        NUmMain6 = 54,
        NUmMain7 = 55,
        NUmMain8 = 56,
        NUmMain9 = 57,

        A = 65,
        B = 66,
        C = 67,
        D = 68,
        E = 69,
        F = 70,
        G = 71,
        H = 72,
        I = 73,
        J = 74,
        K = 75,
        L = 76,
        M = 77,
        N = 78,
        O = 79,
        P = 80,
        Q = 81,
        R = 82,
        S = 83,
        T = 84,
        U = 85,
        V = 86,
        W = 87,
        X = 88,
        Y = 89,
        Z = 90,

        Num0 = 96,
        Num1 = 97,
        Num2 = 98,
        Num3 = 99,
        Num4 = 100,
        Num5 = 101,
        Num6 = 102,
        Num7 = 103,
        Num8 = 104,
        Num9 = 105,

        F1 = 112,
        F2 = 113,
        F3 = 114,
        F4 = 115,
        F5 = 116,
        F6 = 117,
        F7 = 118,
        F8 = 119,
        F9 = 120,
        F10 = 121,
        F11 = 122,
        F12 = 123

    } KeyboardASCII;
}

#endif