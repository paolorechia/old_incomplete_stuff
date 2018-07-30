import sys
from cx_Freeze import setup, Executable

base = None
if sys.platform == "win32":
    base = "Win32GUI"

packages=["pygame", "random", "sys"]
include_files=["sprites/", "font/"]

options={"build_exe":{"packages":packages,"include_files":include_files}}

exe = [Executable(script="snake_main_menu.py", base=base)]



setup(
    name="snake",
    version = "1.0",
    options=options,
    executables = exe
)
