# PlatformIO pre-build script: 빌드 전 NanumGothic 폰트를 자동 생성한다.
# platformio.ini 에서 extra_scripts = pre:tools/pre_build_font.py 로 등록.
Import("env")
import os, subprocess, sys

def run_font_gen(source, target, env):
    project_dir = env.subst("$PROJECT_DIR")
    script = os.path.join(project_dir, "tools", "gen_nanum_font.py")
    # SCons 자체 Python 대신 시스템 python3 사용 (freetype 패키지 있음)
    python = "/usr/bin/python3"
    ret = subprocess.call([python, script], cwd=project_dir)
    if ret != 0:
        print(f"[NanumFont] 경고: 폰트 생성 실패 (종료코드 {ret}). 기존 .h 파일을 사용합니다.")

env.AddPreAction("$BUILD_DIR/${PROGNAME}.elf", run_font_gen)
