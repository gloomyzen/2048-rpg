# swipe-rpg (2048-rpg)

#### First of all, be sure to clone all submodules:
```bash
git clone --recurse-submodules git@gitlab.com:gloomyzen/2048-rpg.git 2048-rpg 
cd 2048-rpg
```

#### Install cocos2d v4:
1. Install CMake on your system
2. Install VS for win32 or XCode for macOs
1. Download Cocos2d-x (cocos2d-x-4.0.zip) from www.cocos2d-x.org and unzip it in a folder that you want.
For example, for Win32 -> unzip to `C:/bin/cocos2dx`, for MacOs `/Application/Develpment/cocos2dx`
2. Install Python 2.7 on your system and just run `python setyp.py` in cocos2dx folder

#### Build from sources :
```bash
cd 2048-rpg
cmake .. -DDEBUG=1
make -j$(nproc)
```

#### Generate project file (VS, Xcode, Android studio) :
For XCode - mac project
```bash
cd 2084-rpg/proj.ios_mac/mac/
cmake ../.. -GXcode -DDEBUG=1
sudo xcode-select --reset
```
For XCode - ios project
```bash
cd 2084-rpg/proj.ios_mac/ios/
cmake ../.. -GXcode -DCMAKE_SYSTEM_NAME=iOS -DCMAKE_OSX_SYSROOT=iphoneos
sudo xcode-select --reset
```
For Visual Studio
```bash
cd 2084-rpg/proj.win32/
cmake .. -G "Visual Studio 16 2019" -AWin32 -DDEBUG=1
and open .sln file from `proj.win32` folder
```