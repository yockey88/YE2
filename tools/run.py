import globals
import os , subprocess , sys

args = globals.ProcessArguments(sys.argv)
config = globals.GetArgValue(args , "config" , "Debug")

exepath = "{}/bin/{}/{}".format(os.getcwd() , config , globals.LIB_NAME)
ret = 0

if globals.IsWindows():
    ret = subprocess.call(["cmd.exe" , "/c" , "{}\\run.bat".format(globals.TOOLS_DIR) , config , globals.EXE_NAME] , cwd=os.getcwd())
else:
    ret = subprocess.call(["{}".format(exepath)] , cwd=exepath)

sys.exit(ret)