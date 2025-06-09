# RPP-imp

RPP-imp is a C++ evolutionary computation framework for optimization and problem-solving, featuring OpenCV-based visualization capabilities.

This project aims solve the problem Robot Path Planning with optimize multi object.

## Overview

You can read more about the project and its objectives in the [project documentation](https://vtzy137.github.io/RPP-imp).

This project implements evolutionary computation algorithms with a focus on:

- Population-based optimization
- Interactive visualization using OpenCV
- Modular and extensible architecture
- Real-time solution visualization

## Project Structure

```plaintext
RPP-imp/
├── assets/         # Static assets and resources
├── docs/          # Documentation files
├── include/       # Header files
├── library/       # Core library implementation
├── src/           # Application source code
├── scripts/       # Utility scripts
└── target/        # Build output directory
```

## Prerequisites

- C++17 compatible compiler
- CMake (version 3.14 or higher)
- OpenCV library
- Git

## Building the Project

### Using CMake (Manual)

1. Clone the repository

    ```sh
    git clone https://github.com/VTzy137/RPP-imp.git
    cd RPP-imp
    ```

2. Create and enter build directory

    ```sh
    mkdir build && cd build
    ```

3. Configure and build:

    ```sh
    cmake ..
    make
    ```

### Using Build Scripts

The project includes several utility scripts in the `scripts/` directory to simplify common tasks:

- `install.sh`: Install dependencies
- `buildCmake.sh`: Build the project using CMake
- `docker.sh`: Build and run using Docker

To use the build script:

```sh
./scripts/buildCmake.sh
```

## Running the Application

### Using Docker

The project includes Docker support for easy deployment and consistent environments. To run using Docker:

1. Build and run using the Docker script:

    ```sh
    ./scripts/docker.sh
    ```

2. Or manually using Docker commands:

    ```sh
    # Build the Docker image
    docker build -t rpp-imp .

    # Run the container
    docker run rpp-imp:latest
    ```

The Docker setup includes:

- Multi-stage build for optimized image size
- OpenCV and all required dependencies
- Non-root user for security
- Ubuntu 22.04 base image

## Features

- **Evolutionary Computation**: Implements various evolutionary algorithms for optimization
- **OpenCV Integration**: Real-time visualization of solutions and optimization process
- **Modular Design**: Easy to extend with new algorithms and strategies
- **Performance Monitoring**: Execution time tracking and performance metrics

## Development

### Code Style

The project uses `.clang-format` for consistent code formatting. To format your code:

```sh
clang-format -i <file>
```

### Adding New Features

1. Add new algorithm implementations in the `library/` directory
2. Update header files in `include/`
3. Modify `src/app.cpp` to integrate new features
4. Update visualization in `include/UI/opencv.hpp`

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the terms specified in the LICENSE file.

## Author

- **Truong Nguyen**
  - Website: [https://vtzy137.github.io/](https://vtzy137.github.io/)
  - Email: <vtzy137@gmail.com>

## Acknowledgments

- OpenCV community for visualization capabilities
- Contributors and users of the project

---

*RPP-imp - DATN-20242*  
*Copyright (C) 2025-2025*
