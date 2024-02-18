# pyLindo -- The Python interface to LINDO API


## Requirements

1. GCC toolchain or Visual Studio (Community)

2. LINDO API 13.0 [(https://www.lindo.com)](https://www.lindo.com/index.php/ls-downloads/try-lindo-api).

3. Python 3.5 or later [(https://www.python.org)](https://www.python.org)

4. Numpy [(http://www.numpy.org)](http://www.numpy.org).

A C/C++ toolchain is required to build pyLindo from source code. This is the preferred method of installation. 


## Windows: Installing GCC/MinGW toolchain 

**NOTE** This distribution of LINDO API contains precompiled binaries of pyLindo for Python 3.5, 3.6 3.7 or 3.8 (32-bit and 64-bit platforms). If you are on Windows and have these versions of Python installed, you can skip the rest and proceed to Step 5 in section [pyLindo for Windows] to complete the installation pyLindo.
    
1. Download the preferred toolchain/compiler from one of these sites
    - MinGW 32-bit toolchain (LINDO API 32-bit) [(http://www.mingw.org)](http://www.mingw.org)
    - MinGW 64-bit toolchain (LINDO API 64-bit) [(https://mingw-w64.org)](https://mingw-w64.org)
	- Visual Stuidio Community [(https://visualstudio.microsoft.com/vs/community)](https://visualstudio.microsoft.com/vs/community)
2. During MinGW installation, make sure to include gcc compiler toolchain
3. After the installation is completed, prepend *c:/MinGW/path/to/gcc* directory to your *%PATH%* environment variable. Typically gcc is located under    
 
        c:/MinGW/mingw32/bin   
        
    or               
    
        c:/MinGW/mingw64/bin
        
	Windows allows environment variables to be configured permanently at both the User level and the System level, or temporarily in a command prompt.    
 
    To temporarily set environment variables, open Command Prompt and use the set command:
    
        C:\> set PATH=c:/MinGW/mingw32/bin;%PATH%    
        
    or  
    
        C:\> set PATH=c:/MinGW/mingw64/bin;%PATH%
    
    To permanently modify the default environment variables, click Start and search for 
    *edit environment variables*, or open System properties, Advanced system settings and 
    click the Environment Variables button. In this dialog, you can add or modify User and 
    System variables. To change System variables, you need non-restricted access to your 
    machine (i.e. Administrator rights).
    

## Linux: Installing GCC

Linux operating systems usually comes with GCC pre installed. To verify if the compiler is installed on the machine, run the following command in the terminal:

    $ gcc --version

After executing this command if the gcc is installed on the machine then it will return the information about the compiler version. Otherwise, use the following commands to install gcc
    
1. On Ubuntu/Debian 
        
        $ sudo apt-get update
        $ sudo apt-get install build-essential manpages-dev
        
2. On Fedora/RedHat

        $ yum groupinstall 'Development Tools'


## Mac/OSX: Installing GCC / CLang

To set up a 'C' programming environment on Mac/OSX system, you have two options:

1. Command Line Tools for Xcode

	- Download *Command Line Tools for XCode* from [https://developer.apple.com/downloads/index.action](https://developer.apple.com/downloads/index.action). You will need an Apple developer ID.

	- After the file is downloaded on the machine, double click and follow the wizard and install the file. Always keep the default settings as suggested by the installation wizard.

	- After the installation process, open a terminal and run gcc -v command to check if everything is successfully installed.

2. Homebrew package manager 
        
	- Install homebrew (if not already installed)

			$ /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
    
    - Run the following brew commands
    
            $ brew update
            $ brew upgrade
            $ brew info gcc
            $ brew install gcc
            $ brew cleanup 
            
            
## pyLindo for Windows

0. Open a Dos command prompt. 

    **NOTE**: If you are the system administrator and LINDO API is installed for all users, make sure you opened the Dos prompt with administrative (elevated) privileges.

1. Check whether environment variable LINDOAPI_HOME has been set to the installation path of LINDO API. 
   If not, set it with the following command
   
        > set LINDOAPI_HOME="c:/lindoapi"

2. Navigate to the %LINDOAPI_HOME%/python folder

3. Run the following command to build the pyLindo package.

        > python setup.py build -c mingw32

   Possible errors due to misconfiguration
   
   
		   ERROR   :  gcc: error: unrecognized command line option '-mno-cygwin'
		   CAUSE   :  incorrect %path% configuration, cygwin/gcc is being used instead of mingw32/gcc
		   SOLUTION:  update %path% such that 'mingw32/bin' appears before 'cygwin/bin'
					  run c:> set path=c:\MinGW\mingw32\bin;%path%   

		   ERROR   :  error: Cygwin gcc cannot be used with --compiler=mingw32
		   CAUSE   :  incorrect %path% configuration, cygwin/gcc is being used instead of mingw32/gcc
		   SOLUTION:  update %path% such that 'mingw32/bin' appears before 'cygwin/bin'
					  run c:> set path=c:\MinGW\mingw32\bin;%path%   

		   ERROR   :  cannot find -lmsvcr140
		   CAUSE   :  File msvcr140.dll does not exist in Microsoft Visual C++ 2015 Redistributable or Visual Studio 2015
		   SOLUTION:  Edit %PYTHON_HOME%\Lib\distutils\cygwinccompiler.py and change 'msvcr140' to 'vcruntime140'
   
		   ERROR   :  cannot find -lvcruntime140
		   CAUSE   :  Linker cannot find vcruntime140.dll
		   SOLUTION:  Edit setup.py and extend `library_dirs` entry for Windows to include Python root
		                 library_dirs = [LibPath, LibPath.replace("bin","lib"), 'c:/path/to/Python']
						 
		   ERROR   :  ValueError: Unknown MS Compiler version 1928						 
		   CAUSE   :  The appropriate MSVC runtime library used to build this python distribution cannot be detected.
		   SOLUTION:  Edit %PYTHON_HOME%\Lib\distutils\cygwinccompiler.py and append the following to get_msvcr() function		   
						..
						elif msc_ver == '1928':
							# VS2015 / MSVC 1x.0
							return ['vcruntime140'] 						
		   
4. Run the following command to install the pyLindo package.
   
    For administrative users:

        > python setup.py install
        
    For standard (non-administrative) users:
    
        > python setup.py install --user
   
5. Run the samples in python/samples folder

        > cd %LINDOAPI_HOME%/python
        > python samples/lp.py

        
## pyLindo for Linux and Mac/OSX


0. Open a shell terminal. 
    
    **NOTE**: If you are the system administrator and LINDO API is installed for all users, switch user to root.

        $ su

1. Set environment variable $LINDOAPI_HOME to the installation path of LINDO API. e.g. 

	For administrative users:
      
        $ export LINDOAPI_HOME="/opt/lindoapi"	
    
    For standard (non-administrative) users:
    
        $ export LINDOAPI_HOME="~/opt/lindoapi"	
   
   To have this variable set automatically, add the above line to your `~/.bashrc` or `~/.bash_profile file`.   

2. Navigate to the `$LINDOAPI_HOME/python` folder

3. Run the following command to build the pyLindo package.
     
        $ python setup.py build 

4. Run the following command to install the pyLindo package.
   
    For administrative users:

        $ python setup.py install
        
    For standard (non-administrative) users:
    
        $ python setup.py install --user

5. Run the samples in python/samples folder

        $ cd $LINDOAPI_HOME/python
        $ python samples/lp.py
