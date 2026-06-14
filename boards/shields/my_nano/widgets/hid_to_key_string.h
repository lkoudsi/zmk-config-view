/*
 * Helper: map HID usage + modifiers to printable chars or short names
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>
#include <stdio.h>
#include <dt-bindings/zmk/hid_usage.h>
#include <dt-bindings/zmk/hid_usage_pages.h>
#include <dt-bindings/zmk/modifiers.h>

static inline const char *zmk_hid_usage_to_string(uint16_t usage_page, uint32_t usage_id,
                                                  uint8_t mods) {
    static char tmp[6];

    if (usage_page != HID_USAGE_KEY) {
        return "<?>";
    }

    /* Letters a-z */
    if (usage_id >= HID_USAGE_KEY_KEYBOARD_A && usage_id <= HID_USAGE_KEY_KEYBOARD_Z) {
        char c = 'a' + (usage_id - HID_USAGE_KEY_KEYBOARD_A);
        if (mods & (MOD_LSFT | MOD_RSFT)) {
            c = c - 'a' + 'A';
        }
        tmp[0] = c;
        tmp[1] = '\0';
        return tmp;
    }

    /* Numbers 1..0 (with shift -> punctuation) */
    if (usage_id >= HID_USAGE_KEY_KEYBOARD_1_AND_EXCLAMATION &&
        usage_id <= HID_USAGE_KEY_KEYBOARD_0_AND_RIGHT_PARENTHESIS) {
        const char *unshift = "1234567890";
        const char *shifted = "!@#$%^&*()";
        int idx = usage_id - HID_USAGE_KEY_KEYBOARD_1_AND_EXCLAMATION;
        tmp[0] = (mods & (MOD_LSFT | MOD_RSFT)) ? shifted[idx] : unshift[idx];
        tmp[1] = '\0';
        return tmp;
    }

    /* Common printable punctuation */
    switch (usage_id) {
    case HID_USAGE_KEY_KEYBOARD_SPACEBAR:
        return " ";
    case HID_USAGE_KEY_KEYBOARD_MINUS_AND_UNDERSCORE:
        tmp[0] = (mods & (MOD_LSFT | MOD_RSFT)) ? '_' : '-';
        tmp[1] = '\0';
        return tmp;
    case HID_USAGE_KEY_KEYBOARD_EQUAL_AND_PLUS:
        tmp[0] = (mods & (MOD_LSFT | MOD_RSFT)) ? '+' : '=';
        tmp[1] = '\0';
        return tmp;
    case HID_USAGE_KEY_KEYBOARD_LEFT_BRACKET_AND_LEFT_BRACE:
        tmp[0] = (mods & (MOD_LSFT | MOD_RSFT)) ? '{' : '[';
        tmp[1] = '\0';
        return tmp;
    case HID_USAGE_KEY_KEYBOARD_RIGHT_BRACKET_AND_RIGHT_BRACE:
        tmp[0] = (mods & (MOD_LSFT | MOD_RSFT)) ? '}' : ']';
        tmp[1] = '\0';
        return tmp;
    case HID_USAGE_KEY_KEYBOARD_BACKSLASH_AND_PIPE:
        tmp[0] = (mods & (MOD_LSFT | MOD_RSFT)) ? '|' : '\\';
        tmp[1] = '\0';
        return tmp;
    case HID_USAGE_KEY_KEYBOARD_SEMICOLON_AND_COLON:
        tmp[0] = (mods & (MOD_LSFT | MOD_RSFT)) ? ':' : ';';
        tmp[1] = '\0';
        return tmp;
    case HID_USAGE_KEY_KEYBOARD_APOSTROPHE_AND_QUOTE:
        tmp[0] = (mods & (MOD_LSFT | MOD_RSFT)) ? '"' : '\'';
        tmp[1] = '\0';
        return tmp;
    case HID_USAGE_KEY_KEYBOARD_GRAVE_ACCENT_AND_TILDE:
        tmp[0] = (mods & (MOD_LSFT | MOD_RSFT)) ? '~' : '`';
        tmp[1] = '\0';
        return tmp;
    case HID_USAGE_KEY_KEYBOARD_COMMA_AND_LESS_THAN:
        tmp[0] = (mods & (MOD_LSFT | MOD_RSFT)) ? '<' : ',';
        tmp[1] = '\0';
        return tmp;
    case HID_USAGE_KEY_KEYBOARD_PERIOD_AND_GREATER_THAN:
        tmp[0] = (mods & (MOD_LSFT | MOD_RSFT)) ? '>' : '.';
        tmp[1] = '\0';
        return tmp;
    case HID_USAGE_KEY_KEYBOARD_SLASH_AND_QUESTION_MARK:
        tmp[0] = (mods & (MOD_LSFT | MOD_RSFT)) ? '?' : '/';
        tmp[1] = '\0';
        return tmp;

    /* Navigation, editing, function, and system keys -> short names */

    case HID_USAGE_KEY_KEYBOARD_RETURN_ENTER:
        return "<Ent>";
    case HID_USAGE_KEY_KEYBOARD_ESCAPE:
        return "<Esc>";
    case HID_USAGE_KEY_KEYBOARD_DELETE_BACKSPACE:
        return "<BS>";
    case HID_USAGE_KEY_KEYBOARD_TAB:
        return "<Tab>";
    case HID_USAGE_KEY_KEYBOARD_CAPS_LOCK:
        return "<CL>";
    case HID_USAGE_KEY_KEYBOARD_PRINTSCREEN:
        return "<PS>";
    case HID_USAGE_KEY_KEYBOARD_SCROLL_LOCK:
        return "<SL>";
    case HID_USAGE_KEY_KEYBOARD_PAUSE:
        return "<Pau>";
    case HID_USAGE_KEY_KEYBOARD_INSERT:
        return "<Ins>";
    case HID_USAGE_KEY_KEYBOARD_HOME:
        return "<Hm>";
    case HID_USAGE_KEY_KEYBOARD_PAGEUP:
        return "<PgU>";
    case HID_USAGE_KEY_KEYBOARD_DELETE_FORWARD:
        return "<Del>";
    case HID_USAGE_KEY_KEYBOARD_END:
        return "<End>";
    case HID_USAGE_KEY_KEYBOARD_PAGEDOWN:
        return "<PgD>";
    case HID_USAGE_KEY_KEYBOARD_RIGHTARROW:
        return "<Rgt>";
    case HID_USAGE_KEY_KEYBOARD_LEFTARROW:
        return "<Lft>";
    case HID_USAGE_KEY_KEYBOARD_DOWNARROW:
        return "<Dwn>";
    case HID_USAGE_KEY_KEYBOARD_UPARROW:
        return "<Up>";
    }

    /* Function keys F1..F12 */
    if (usage_id >= HID_USAGE_KEY_KEYBOARD_F1 && usage_id <= HID_USAGE_KEY_KEYBOARD_F12) {
        int fn = usage_id - HID_USAGE_KEY_KEYBOARD_F1 + 1;
        snprintf(tmp, sizeof(tmp), "<F%d>", fn);
        return tmp;
    }

    /* Default: show short hex code without angle brackets to fit 5 chars */
    snprintf(tmp, sizeof(tmp), "0x%02X", (unsigned)(usage_id & 0xFF));
    return tmp;
}
