# Lightning

A client/server side modification for Call of Duty 4.

## Build instructions

### Requirements

* Git
* Microsoft Visual Studio 2013

### Clone the repository

```
git clone https://github.com/twizre/lightning.git
cd lightning
```

### Set up Premake

1. Download the latest Premake nightly build from [here](http://www.mirrorservice.org/sites/ftp.sourceforge.net/pub/sourceforge/p/pr/premake/Premake/nightlies/premake-dev-windows.zip).
2. Extract `premake5.exe` to the directory you cloned this repository to.

### Generate project files

```
cd lightning
premake5 vs2013
```

### Build the project

1. Open the project folder and open `iw3cli.sln`.
2. Build the project using Visual Studio 2013.
