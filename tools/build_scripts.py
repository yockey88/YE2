import globals
import os , subprocess , sys
import shutil

args = globals.ProcessArguments(sys.argv)

if (os.path.exists("bin/Debug/TestBed/res")):
    shutil.rmtree("bin/Debug/TestBed/res")
if (os.path.exists("bin/Debug/TestBed/config")):
    shutil.rmtree("bin/Debug/TestBed/config")

if (os.path.exists("TestBed/other/res") & os.path.exists("TestBed/other/config")):
    shutil.copytree("TestBed/other/res" , "bin/Debug/TestBed/res")
    shutil.copytree("TestBed/other/config" , "bin/Debug/TestBed/config")
else:
    print("[< Missing Resource Folder for Build Process | Build Corrupted >]")
    sys.exit(1)

sys.exit(0)