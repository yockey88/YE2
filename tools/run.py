import globals
import os , subprocess , sys

args = globals.ProcessArguments(sys.argv)
config = globals.GetArgValue(args , "c" , "Debug")
project = globals.GetArgValue(args , "p" , "TestBed")

exepath = "{}/bin/{}/{}".format(os.getcwd() , config , globals.LIB_NAME)
ret = 0

if globals.IsWindows():
    ret = subprocess.call(["cmd.exe" , "/c" , "{}\\run.bat".format(globals.TOOLS_DIR) , config , project] , cwd=os.getcwd())
else:
    ret = subprocess.call(["{}".format(exepath)] , cwd=exepath)

sys.exit(ret)