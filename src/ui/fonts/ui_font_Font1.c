/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: --bpp 1 --size 16 --font /home/work/SquareLine/assets/NanumBrush.ttf -o /home/work/SquareLine/assets/ui_font_Font1.c --format lvgl -r 0x20-0x7f --no-compress --no-prefilter
 ******************************************************************************/

#include "../ui.h"

#ifndef UI_FONT_FONT1
#define UI_FONT_FONT1 1
#endif

#if UI_FONT_FONT1

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0x2d, 0x24, 0x90, 0x8,

    /* U+0022 "\"" */
    0x6, 0xc0,

    /* U+0023 "#" */
    0x10, 0x2, 0x20, 0x44, 0x1f, 0xf5, 0x10, 0x22,
    0x4, 0x40, 0xfc, 0x71, 0x2, 0x20, 0x0, 0x0,

    /* U+0024 "$" */
    0x10, 0x20, 0x41, 0xc5, 0xd2, 0x1c, 0xf, 0x13,
    0xf8, 0x40, 0x80,

    /* U+0025 "%" */
    0x2, 0x1, 0x39, 0x15, 0xc, 0x80, 0x98, 0x4c,
    0x20, 0x20, 0x10, 0x0,

    /* U+0026 "&" */
    0x71, 0x22, 0x44, 0x89, 0xc, 0x18, 0xba, 0x99,
    0xd8,

    /* U+0027 "'" */
    0xf0,

    /* U+0028 "(" */
    0x29, 0x49, 0x23,

    /* U+0029 ")" */
    0xc8, 0x92, 0x4a, 0x40,

    /* U+002A "*" */
    0x2b, 0xbc, 0xc2, 0x0,

    /* U+002B "+" */
    0x0, 0x20, 0x40, 0xbf, 0xc2, 0x4, 0x0,

    /* U+002C "," */
    0xe0,

    /* U+002D "-" */
    0x1, 0xf8,

    /* U+002E "." */
    0x50,

    /* U+002F "/" */
    0x12, 0x26, 0x44, 0xc8, 0x0,

    /* U+0030 "0" */
    0x69, 0x99, 0x9a, 0xc0,

    /* U+0031 "1" */
    0xff,

    /* U+0032 "2" */
    0x62, 0x82, 0x10, 0x8f, 0xc0,

    /* U+0033 "3" */
    0x70, 0x88, 0x72, 0x84, 0x42,

    /* U+0034 "4" */
    0x18, 0x28, 0x28, 0x48, 0x8e, 0xf8, 0x8, 0x8,

    /* U+0035 "5" */
    0x43, 0xe4, 0x2e, 0x48, 0x20, 0x84, 0x60,

    /* U+0036 "6" */
    0x24, 0xce, 0x99, 0xae,

    /* U+0037 "7" */
    0x38, 0xc8, 0xb, 0x1c, 0x28, 0x10, 0x10, 0x10,
    0x10,

    /* U+0038 "8" */
    0x6a, 0xaa, 0x6b, 0x9a, 0xc0,

    /* U+0039 "9" */
    0x6b, 0xbf, 0xd1, 0x11, 0x10,

    /* U+003A ":" */
    0x43, 0x40,

    /* U+003B ";" */
    0xc0, 0x4, 0x90,

    /* U+003C "<" */
    0x19, 0x88, 0x88, 0x61, 0x82, 0x8,

    /* U+003D "=" */
    0xfc, 0x1, 0xf0, 0x0,

    /* U+003E ">" */
    0xc0, 0xc0, 0x81, 0x8, 0x41, 0x8, 0x0,

    /* U+003F "?" */
    0x36, 0x62, 0x21, 0x10, 0x84, 0x1, 0x84,

    /* U+0040 "@" */
    0x0, 0x79, 0xd, 0xda, 0xb9, 0xbf, 0x64, 0x70,

    /* U+0041 "A" */
    0x8, 0x18, 0x14, 0x24, 0x24, 0x26, 0x7f, 0x42,
    0x42, 0x42, 0x41, 0x0,

    /* U+0042 "B" */
    0xf8, 0x48, 0x91, 0x43, 0xe4, 0x48, 0x92, 0x8,
    0x20,

    /* U+0043 "C" */
    0x3, 0xd1, 0x8, 0x42, 0xe,

    /* U+0044 "D" */
    0xf4, 0x63, 0x18, 0xa9, 0x88,

    /* U+0045 "E" */
    0xf8, 0x81, 0x7, 0xe4, 0x8, 0xde, 0x0,

    /* U+0046 "F" */
    0xf8, 0x81, 0x2, 0x3, 0xc4, 0x8, 0x10, 0x0,

    /* U+0047 "G" */
    0x38, 0x40, 0x80, 0x8f, 0xb4, 0x4c, 0x74, 0x4,

    /* U+0048 "H" */
    0x82, 0x18, 0x67, 0xf6, 0x18, 0x40,

    /* U+0049 "I" */
    0xff, 0x0,

    /* U+004A "J" */
    0x7e, 0x10, 0x20, 0x20, 0x40, 0x81, 0x76, 0x78,

    /* U+004B "K" */
    0x80, 0x84, 0x98, 0xb0, 0xa0, 0xf0, 0x8c, 0x82,
    0x0,

    /* U+004C "L" */
    0x81, 0x2, 0x4, 0x8, 0x10, 0xff, 0x70,

    /* U+004D "M" */
    0x80, 0xc3, 0xa5, 0x99, 0x89, 0x81, 0x1, 0x0,

    /* U+004E "N" */
    0x87, 0x99, 0x65, 0x8e, 0x38, 0x40,

    /* U+004F "O" */
    0x64, 0xe3, 0x18, 0xe9, 0x80,

    /* U+0050 "P" */
    0x8, 0xff, 0x89, 0x12, 0x47, 0x88, 0x10, 0x20,

    /* U+0051 "Q" */
    0x30, 0xf1, 0x12, 0x28, 0x53, 0xa3, 0x39,

    /* U+0052 "R" */
    0x7c, 0x62, 0x11, 0x9, 0x5, 0x81, 0x71, 0x6,
    0x0,

    /* U+0053 "S" */
    0x3c, 0x82, 0x2, 0x7, 0xc0, 0x40, 0x9e, 0x10,

    /* U+0054 "T" */
    0x7f, 0xc8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x0,

    /* U+0055 "U" */
    0x45, 0x18, 0x61, 0x8a, 0x2f, 0x0,

    /* U+0056 "V" */
    0x2, 0x14, 0x92, 0x49, 0x43, 0x8,

    /* U+0057 "W" */
    0x0, 0x71, 0x14, 0x69, 0x2a, 0x4a, 0x8c, 0xc3,
    0x10, 0x44,

    /* U+0058 "X" */
    0x3, 0xc6, 0x6c, 0x18, 0x1c, 0x14, 0x22, 0x20,

    /* U+0059 "Y" */
    0x3, 0x9, 0x31, 0xc3, 0x2, 0x4, 0x8, 0x10,
    0x0,

    /* U+005A "Z" */
    0x78, 0x2, 0x2, 0x3, 0xc3, 0x1, 0x1, 0x3c,
    0xe0,

    /* U+005B "[" */
    0xe8, 0x88, 0x88, 0x88, 0x88, 0xe0,

    /* U+005C "\\" */
    0x0, 0x20, 0x9, 0x19, 0x23, 0x67, 0xfe, 0x77,
    0xc, 0x60, 0x88, 0x10, 0x0,

    /* U+005D "]" */
    0x71, 0x11, 0x11, 0x11, 0x17,

    /* U+005E "^" */
    0x22, 0xa5, 0x10, 0x0,

    /* U+005F "_" */
    0x7f, 0x80,

    /* U+0060 "`" */
    0xa5,

    /* U+0061 "a" */
    0x32, 0x62, 0xf4, 0xbc, 0x0,

    /* U+0062 "b" */
    0x88, 0x8e, 0x99, 0xac,

    /* U+0063 "c" */
    0x68, 0x89, 0xe0,

    /* U+0064 "d" */
    0x10, 0x84, 0x21, 0x3a, 0x73, 0x70,

    /* U+0065 "e" */
    0x31, 0x27, 0x20, 0x78,

    /* U+0066 "f" */
    0x72, 0x90, 0x86, 0x7c, 0x84, 0x21, 0x0,

    /* U+0067 "g" */
    0x4e, 0xaa, 0xbd, 0x11, 0x36, 0x0,

    /* U+0068 "h" */
    0x84, 0x21, 0x8, 0x5b, 0x39, 0x40,

    /* U+0069 "i" */
    0xc0, 0x24, 0x80,

    /* U+006A "j" */
    0x60, 0x2, 0x11, 0x11, 0x1e,

    /* U+006B "k" */
    0x1, 0x2, 0x2, 0x86, 0xf, 0x13, 0x22,

    /* U+006C "l" */
    0xaa, 0xb5,

    /* U+006D "m" */
    0x80, 0x9b, 0xed, 0xc9, 0xc9,

    /* U+006E "n" */
    0x99, 0x96, 0x51,

    /* U+006F "o" */
    0x79, 0x9a, 0x60,

    /* U+0070 "p" */
    0xfa, 0x52, 0xe4, 0x21, 0x84, 0x20,

    /* U+0071 "q" */
    0x72, 0xa5, 0x2e, 0x84, 0x21, 0x0,

    /* U+0072 "r" */
    0x9d, 0x10, 0x84, 0x0,

    /* U+0073 "s" */
    0x72, 0x10, 0x78, 0xb8,

    /* U+0074 "t" */
    0x10, 0x82, 0x8, 0x23, 0xe2, 0xa, 0x30,

    /* U+0075 "u" */
    0x99, 0x9b, 0xd0,

    /* U+0076 "v" */
    0x9, 0x96, 0x60,

    /* U+0077 "w" */
    0x0, 0x81, 0x89, 0x5a, 0x66, 0x46, 0x4,

    /* U+0078 "x" */
    0x9, 0x63, 0xc, 0x49, 0x0,

    /* U+0079 "y" */
    0x2, 0x52, 0xb6, 0x84, 0x21, 0x11, 0x0,

    /* U+007A "z" */
    0x78, 0x23, 0xe1, 0x4, 0xce, 0x0,

    /* U+007B "{" */
    0x22, 0x10, 0x84, 0x21, 0x9c, 0x22, 0x12, 0x60,

    /* U+007C "|" */
    0xff, 0x80,

    /* U+007D "}" */
    0x65, 0x8, 0x42, 0x18, 0x84, 0x21, 0x18, 0x80,

    /* U+007E "~" */
    0x61, 0x92, 0xc
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 72, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 67, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 5, .adv_w = 72, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 7, .adv_w = 189, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 23, .adv_w = 141, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 34, .adv_w = 166, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 46, .adv_w = 142, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 55, .adv_w = 63, .box_w = 1, .box_h = 4, .ofs_x = 2, .ofs_y = 9},
    {.bitmap_index = 56, .adv_w = 90, .box_w = 3, .box_h = 8, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 59, .adv_w = 90, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 63, .adv_w = 97, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 67, .adv_w = 136, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 74, .adv_w = 59, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 75, .adv_w = 136, .box_w = 7, .box_h = 2, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 77, .adv_w = 51, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 78, .adv_w = 87, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 83, .adv_w = 95, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 87, .adv_w = 62, .box_w = 1, .box_h = 8, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 88, .adv_w = 97, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 93, .adv_w = 94, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 98, .adv_w = 133, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 106, .adv_w = 97, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 113, .adv_w = 92, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 117, .adv_w = 120, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 126, .adv_w = 84, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 131, .adv_w = 95, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 136, .adv_w = 78, .box_w = 2, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 138, .adv_w = 78, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 141, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 147, .adv_w = 136, .box_w = 7, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 151, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 158, .adv_w = 102, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 165, .adv_w = 141, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 173, .adv_w = 128, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 185, .adv_w = 118, .box_w = 7, .box_h = 10, .ofs_x = -1, .ofs_y = 1},
    {.bitmap_index = 194, .adv_w = 105, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 199, .adv_w = 97, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 204, .adv_w = 118, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 211, .adv_w = 110, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 219, .adv_w = 136, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 227, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 233, .adv_w = 66, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 235, .adv_w = 110, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 243, .adv_w = 136, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 252, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 259, .adv_w = 146, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 267, .adv_w = 123, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 273, .adv_w = 105, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 278, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 286, .adv_w = 110, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 293, .adv_w = 136, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 302, .adv_w = 120, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 310, .adv_w = 125, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 318, .adv_w = 115, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 324, .adv_w = 100, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 330, .adv_w = 175, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 340, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 348, .adv_w = 123, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 357, .adv_w = 133, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 366, .adv_w = 95, .box_w = 4, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 372, .adv_w = 207, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 385, .adv_w = 95, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 390, .adv_w = 102, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 394, .adv_w = 140, .box_w = 9, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 396, .adv_w = 64, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 397, .adv_w = 92, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 402, .adv_w = 79, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 406, .adv_w = 79, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 409, .adv_w = 82, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 415, .adv_w = 84, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 419, .adv_w = 87, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 426, .adv_w = 82, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 432, .adv_w = 93, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 438, .adv_w = 54, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 441, .adv_w = 66, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 446, .adv_w = 105, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 453, .adv_w = 57, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 455, .adv_w = 141, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 460, .adv_w = 103, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 463, .adv_w = 74, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 466, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 472, .adv_w = 87, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 478, .adv_w = 92, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 482, .adv_w = 87, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 486, .adv_w = 105, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 493, .adv_w = 87, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 496, .adv_w = 72, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 499, .adv_w = 133, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 506, .adv_w = 97, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 511, .adv_w = 84, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 518, .adv_w = 110, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 524, .adv_w = 93, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 532, .adv_w = 62, .box_w = 1, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 534, .adv_w = 86, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 542, .adv_w = 150, .box_w = 8, .box_h = 3, .ofs_x = 1, .ofs_y = 5}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t ui_font_Font1 = {
#else
lv_font_t ui_font_Font1 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 15,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -4,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if UI_FONT_FONT1*/

