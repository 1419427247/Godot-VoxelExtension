cd ./src
scons target=template_debug dev_build=yes
scons target=template_release dev_build=yes
cd ..
copy .\bin\* .\demo\bin\

pause