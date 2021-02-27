# 🧬 DNA's Not ASCII

Stats on the Human genome.

## Prerequisite

Please install [CMake][cmake]:

```bash
sudo apt-get install -y build-essential libssl-dev
cd /opt
sudo git clone https://github.com/Kitware/CMake.git cmake
sudo chown -R <user>: cmake
cd cmake
git checkout v3.18.6
./bootstrap
make
sudo make install
```

Then, install [Boost][boost]:

```bash
curl -fsSOL https://dl.bintray.com/boostorg/release/1.75.0/source/boost_1_75_0.tar.bz2
tar --bzip2 -xf boost_1_75_0.tar.bz2
sudo mv boost_1_75_0 /opt/boost
sudo chown -R <user>: /opt/boost
cd /opt/boost
./bootstrap.sh
./b2
sudo ./b2 install
```

Install [zlib][zlib]:

```bash
cd /opt
sudo git clone https://github.com/madler/zlib.git
sudo chown -R <user>: zlib
cd zlib
git checkout v1.2.11
./configure
make test
sudo make install
```

## Getting Started

First you need to install [PNGwriter](https://github.com/pngwriter/pngwriter) on your computer by following [this guide](https://github.com/pngwriter/pngwriter#installation).
You might need to install `libpng-dev`, `zlib1g-dev`, `libbz2-1.0` and `libbz2-dev` beforehand.

Then, to compile the project, use the following command:

```bash
make
```

If you want to compile it under a specific build type, you can use one of the following:

```bash
make compile CMAKE_BUILT_TYPE=Debug
make compile CMAKE_BUILT_TYPE=Release
```

The defaults build type is `Release`.

---

Finally, to launch the built executable, use either `make run` or `./build/dna-not-ascii`.


## Built With

* C/C++ 17
* [CMake][cmake]
* [Boost][boost]
* [zlib][zlib]
* [kduske/cpp-stopwatch][kduske-cpp-stopwatch]
* [htailor/cpp_progress_bar][htailor-cpp_progress_bar]
* [Visual Studio Code][vscode]

## Contributing

Contribution are not permitted yet, because this project is
really simple and should not be a real problem. You noticed a bug
in the source code? Feel free to post an issue
about it.

## Author

* **Valentin Berger ([Cynnexis](https://github.com/Cynnexis)):** developer

## License

This project is under the MIT License.
Please see the [LICENSE.txt](https://github.com/Cynnexis/dna-not-ascii/blob/master/LICENSE.txt)
file for more detail.

[cmake]: https://cmake.org/install/
[boost]: https://www.boost.org/
[zlib]: http://zlib.net/
[kduske-cpp-stopwatch]: https://github.com/kduske/cpp-stopwatch
[htailor-cpp_progress_bar]: https://github.com/htailor/cpp_progress_bar
[vscode]: https://code.visualstudio.com/
