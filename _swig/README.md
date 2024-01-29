# SaraKIT Python Library

This repository contains the SaraKIT library, a SWIG-generated interface that allows Python users to access and control the functionalities of SaraKIT devices originally written in C++.

## Contents

- `devices.hpp`: The main header file for the C++ library.
- `devices.cpp`: The main file for the C++ library.
- `SaraKITDevices_wrap.c`: The SWIG-generated C++ source file for interfacing with Python.
- `sarakitdevices.py`: The Python module generated by SWIG.
- `SaraKITDevices.i`: SWIG file.
- `make_so.sh`: Script for building Python library.
- `../examples/`: Directory containing sample Python scripts demonstrating the use of the SaraKIT library.

## Prerequisites

Ensure you have the following installed on your system:

- Python 3.x
- SWIG (Simplified Wrapper and Interface Generator)
- A C++ compiler (e.g., GCC for Linux, Visual Studio for Windows)

sudo apt-get update
sudo apt-get install swig
sudo apt-get install python3-dev


## Installation

1. Clone the repository:
   ```bash
   git clone [repository URL]
   ```

2. Navigate to the cloned directory:
   ```bash
   cd [repository name]
   ```

## Usage

After installation, you can import the SaraKIT module in your Python scripts:

```python
import SaraKITDevices as sk
```

Refer to the examples in the `examples/` directory to get started with using the library.


## Contributing

Contributions to the SaraKIT Python library are welcome. Please refer to the `CONTRIBUTING.md` file for guidelines.

## License

This library is licensed under the [MIT License](LICENSE).

## Contact

For any queries or suggestions, please open an issue in this repository.