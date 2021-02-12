# DNA's Not ASCII

Stats on the Human genome.

## Prerequisite

Please install [CMake](https://cmake.org/install/):

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

Then, install [Boost](https://www.boost.org/):

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

Install [zlib](http://zlib.net/):

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

Compile the project:

```bash
make
```
