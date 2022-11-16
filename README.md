## Katsudon Optimizer

### Setup for Windows Visual Studio

<ol>
<li>
Clone this repo and submodules
<br>
<code>
git clone --recursive https://github.com/DLi7077/Katsudon-Optimizer.git</code>
<br>
then navigate to the folder
<br>
<code>
cd .\Katsudon-Optimizer\
</code>
</li>

<li>
Install vcpkg stuff
<br>
<code>.\vcpkg\bootstrap-vcpkg.bat</code>
</li>

<li>
Install Crow
<br>
<i>This should take around 7 minutes and will take up probably 1GB of space</i>
<br>
<code>
 .\vcpkg\vcpkg install crow:x64-windows
</code>
<br>
vcpkg installs x86 libraries by default. If you are using a x86 system, omit the <code>:x64-windows</code> suffix like so:
<br>
<code>
 .\vcpkg\vcpkg install crow
</code>
<br>
read more here: <a href="https://github.com/microsoft/vcpkg">https://github.com/microsoft/vcpkg</a>
</li>
<li>
Allow Visual Studio to use vcpkg
<br>
<code>.\vcpkg\vcpkg integrate install</code>
</li>
</ol>
