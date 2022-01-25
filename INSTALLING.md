# Installing passwordmanager

As of today passwordmanager is available for macOS and linux. 

## Installation on macOS

Installing passwordmanager on mac is really easy, we use homebrew. [Here to how to install Homebrew](https://docs.brew.sh/Installation)

You just have to: 

```

brew tap tax25/homebrew-passwordmanager
brew install passwordmanager

```

## Installation on linux

Since linux has so many distros and package managers, and making passwordmanager available for every one of them would be quite a struggle (at least with the experience i have now), I decided to create a make file
so that you can compile passwordmanager for you machine and then install it. It is a really basic Makefile and probably the installation process is as wrong as it can be, if you know how to do it better, please tell me!
So, to compile and install passwordmanager for your machine you have to:

```
// clone the repo
$ git clone --recursive https://github.com/tax25/homebrew-passwordmanager.git

// cd into the directory
$ cd homebrew-passwordmanager

// compile it (be sure to have make installed)
$ make

// install passwordmanager
$ sudo make install 

```

If you get an error and it's something like "cannot find -lsqlite3" try installing sqlite3 and libsqlite3-dev. 

```
sudo apt-get install sqlite3 libsqlite3-dev

```
