The Python Interface to LINDO API.

This package requires LINDO API 13.0 and a valid license key. Please refer to INSTALL for installation details.
An environment variable named LINDOAPI_HOME needs to be created before building, and using the Lindo API.
### Using Windows
On the command line
```dos
> set LINDOAPI_HOME="c:/lindoapi"
```
### Using Mac or Linux
On the command line
```sh
$ export LINDOAPI_HOME="/opt/lindoapi"
```

## How to download

This python package can be downloaded with pip

```bash
> pip install lindo
```

## How to Build Wheel and Install 

To build the python package on any operating system first start by creating a whl file. form the top of the lindoapi-python directory run the command.

```bash
> python -m build
```

If the command is successful a new directory named `dist` is created in the lindoapi-python directory. The new directory will have a two files with extension `.whl` and `.tat.gz`. For example, if you built it on Mac OS using Python 3.10 the new directory will look like this.

```bash
├── dist
│  ├── lindo-1.0.2-cp310-cp310-macosx_10_9_universal2.whl
│  └── lindo-1.0.2.tar.gz
```

The package can now be installed locally using the command.
```bash
> pip install dist/*.whl
```

## Testing installation
A quick way to test the installation is to run
```bash
> python -m lindo_test
```

If the test is successful, you can now import the lindo python library and start using it.
```python
import lindo
```
