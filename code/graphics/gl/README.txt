To regenerate these files run the following commands in your glloadgen directory:

lua "LoadGen.lua" -spec=gl -version=2.1 -style=pointer_c -extfile="<path to this directory>/exts.txt" out/2_1
lua "LoadGen.lua" -spec=wgl -style=pointer_c -stdext=wgl_common.txt out/2_1
lua "LoadGen.lua" -spec=glX -style=pointer_c -stdext=glx_common.txt out/2_1

Then copy the contents of the out directory into this directory