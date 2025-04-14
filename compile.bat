@echo off
set GLSLC=C:\VulkanSDK\1.4.309.0\Bin\glslc.exe

if not exist compiledShaders mkdir compiledShaders

for %%f in (shaders\*.vert) do (
    %GLSLC% %%f -o compiledShaders\%%~nf_vert.spv
)

for %%f in (shaders\*.frag) do (
    %GLSLC% %%f -o compiledShaders\%%~nf_frag.spv
)

echo All shaders compiled successfully!