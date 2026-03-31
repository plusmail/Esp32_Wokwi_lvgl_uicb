#!/usr/bin/env python3
"""
NanumGothic VLW font generator for TFT_eSPI (PROGMEM array)

src/ 디렉터리의 소스 파일을 자동 스캔하여 사용된 한글 글자를 추출한 뒤
include/NanumGothic{size}px.h 를 생성합니다.

Usage:
  python3 tools/gen_nanum_font.py            # 16px, 20px 모두 생성
  python3 tools/gen_nanum_font.py 24         # 24px만 생성
  python3 tools/gen_nanum_font.py 16 20 24   # 여러 사이즈 동시 생성

VLW format (big-endian int32):
  Header   (24 bytes)       : gCount, 0, yAdvance, 0, ascent, descent
  Metadata (28 bytes/glyph) : unicode, height, width, xAdvance, dY, dX, 0
  Bitmaps  (w×h bytes)      : 8-bit alpha, row-major
"""

import struct
import sys
import os
import glob
import freetype

FONT_PATH    = "/usr/share/fonts/truetype/nanum/NanumGothic.ttf"
DEFAULT_SIZES = [16, 20]

# ── 소스 스캔 ──────────────────────────────────────────────────────────────

def scan_korean_chars(project_dir):
    """src/ 아래 모든 소스 파일에서 사용된 한글 음절을 수집한다."""
    patterns = ["src/**/*.cpp", "src/**/*.h", "src/**/*.ino",
                "src/**/*.c",   "lib/**/*.cpp", "lib/**/*.h"]
    paths = []
    for pat in patterns:
        paths.extend(glob.glob(os.path.join(project_dir, pat), recursive=True))

    korean = set()
    for path in paths:
        try:
            text = open(path, encoding="utf-8", errors="ignore").read()
        except OSError:
            continue
        for ch in text:
            cp = ord(ch)
            if 0xAC00 <= cp <= 0xD7A3:    # 한글 음절
                korean.add(cp)
            elif 0x3130 <= cp <= 0x318F:  # 한글 자모 (ㄱ~ㅣ)
                korean.add(cp)

    return korean

def get_charset(project_dir):
    ascii_chars  = set(range(0x20, 0x7F))
    korean_chars = scan_korean_chars(project_dir)
    return sorted(ascii_chars | korean_chars)

# ── 렌더링 ─────────────────────────────────────────────────────────────────

def render_glyphs(face, char_list, size_px):
    face.set_pixel_sizes(0, size_px)
    glyphs = []
    for cp in char_list:
        try:
            face.load_char(cp, freetype.FT_LOAD_RENDER)
        except freetype.FT_Exception:
            continue
        slot   = face.glyph
        bm     = slot.bitmap
        w, h   = bm.width, bm.rows
        glyphs.append(dict(
            unicode  = cp,
            width    = w,
            height   = h,
            xAdvance = (slot.advance.x + 32) >> 6,
            dX       = slot.bitmap_left,
            dY       = slot.bitmap_top,
            pixels   = bytes(bm.buffer) if (w > 0 and h > 0) else b"",
        ))
    return glyphs

# ── VLW 바이너리 조립 ──────────────────────────────────────────────────────

def build_vlw(glyphs):
    ascent   = max((g["dY"]             for g in glyphs if g["height"] > 0), default=1)
    descent  = max((g["height"]-g["dY"] for g in glyphs if g["height"] > 0), default=1)
    yAdvance = ascent + descent
    gCount   = len(glyphs)

    data = bytearray()
    for v in (gCount, 0, yAdvance, 0, ascent, descent):
        data += struct.pack(">i", v)
    for g in glyphs:
        for v in (g["unicode"], g["height"], g["width"],
                  g["xAdvance"], g["dY"], g["dX"], 0):
            data += struct.pack(">i", v)
    for g in glyphs:
        data += g["pixels"]

    return bytes(data), ascent, descent, yAdvance

# ── 헤더 파일 출력 ─────────────────────────────────────────────────────────

def write_header(path, data, size_px, glyphs, ascent, descent, yadvance):
    varname = f"NanumGothic{size_px}"
    korean  = [g for g in glyphs if g["unicode"] >= 0xAC00]
    chars_str = "".join(chr(g["unicode"]) for g in korean)

    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w", encoding="utf-8") as f:
        f.write(f"#pragma once\n")
        f.write(f"// NanumGothic {size_px}px — VLW PROGMEM array for TFT_eSPI\n")
        f.write(f"// 글리프 : {len(glyphs)}개  (ASCII {len(glyphs)-len(korean)}개 + 한글 {len(korean)}개)\n")
        f.write(f"// 한글   : {chars_str}\n")
        f.write(f"// ascent : {ascent}  descent: {descent}  yAdvance: {yadvance}\n")
        f.write(f"// 크기   : {len(data)} bytes ({len(data)/1024:.1f} KB)\n")
        f.write(f"// 사용법 : tft.loadFont({varname});\n")
        f.write(f"//          tft.drawString(\"한글\", x, y);\n\n")
        f.write(f"#include <pgmspace.h>\n\n")
        f.write(f"static const uint8_t {varname}[] PROGMEM = {{\n")
        for i in range(0, len(data), 16):
            chunk = data[i:i+16]
            f.write("  " + ", ".join(f"0x{b:02X}" for b in chunk) + ",\n")
        f.write("};\n")

# ── 메인 ──────────────────────────────────────────────────────────────────

def generate(project_dir, sizes):
    face    = freetype.Face(FONT_PATH)
    charset = get_charset(project_dir)
    korean  = [c for c in charset if c >= 0xAC00]
    print(f"[NanumFont] 스캔 완료: ASCII {len(charset)-len(korean)}개 + 한글 {len(korean)}개")
    if korean:
        print(f"           한글: {''.join(chr(c) for c in korean)}")

    for size_px in sizes:
        glyphs = render_glyphs(face, charset, size_px)
        vlw, ascent, descent, yadvance = build_vlw(glyphs)
        out = os.path.join(project_dir, f"include/NanumGothic{size_px}.h")
        write_header(out, vlw, size_px, glyphs, ascent, descent, yadvance)
        print(f"[NanumFont] {size_px}px → {os.path.basename(out)}  "
              f"({len(vlw)//1024} KB, {len(glyphs)} 글리프)")

def main():
    sizes = [int(a) for a in sys.argv[1:]] if len(sys.argv) > 1 else DEFAULT_SIZES
    project_dir = os.path.normpath(os.path.join(os.path.dirname(__file__), ".."))
    generate(project_dir, sizes)

if __name__ == "__main__":
    main()
