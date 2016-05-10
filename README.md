# watermelonOS
Personal project to learn how to build a kernel and an OS from scratch.


## Structure
For the moment, this project has two main parts:
* The kernel, which provides basic functionalities
* The LibC, which provides tools for hosted programs

Actually, the Kernel only provides boot instruction and VGA driver functions.

LibC is compiled twice: the first time, only a subpart is compiled as `libK` (aka lib kernel). The second time, it is compiled entirely as `libC`.

LibK is used to provide the kernel access to libC functions with kernel specific implementation.


## Building
Simply run the `./build.sh` script at the root of the repository.

This script will:
* Create the sysroot directory
* Populate the sysroot directory of the kernel and libC includes
* Build the libK, libC and kernel binaries
* Populate the sysroot directory with the built libraries


## Running
Simply run the `./qemu.sh` script at the root of the repository.

This script will:
* Build the project
* Create the operating system iso using grub
* Run the iso using `Qemu`


## Author
[Simon Ninon](http://simon-ninon.fr)


## Acknowledgement
I'm building this Operating System from scratch by reading the [OSDev Tutorials](http://wiki.osdev.org/Tutorials).

This website is just insane and is a very good source of documentation.
Everyone interested in discovering kernel development should definitively start by looking at this website which is a very good starting point!
