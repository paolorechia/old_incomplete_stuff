import sys
from cx_Freeze import setup, Executable

base = None
if sys.platform == "win32":
    base = "Win32GUI"

packages=["pygame", "sys"]
include_files=["media/"]

options={"build_exe":{"packages":packages,"include_files":include_files}}

exe = [Executable(script="battle.py", base=base)]



setup(
    name="board",
    version = "0.1",
    options=options,
    executables = exe
)
