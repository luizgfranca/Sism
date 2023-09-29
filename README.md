# SISM - Services manager for the GNU/Linux desktop

Sism is a tool to manage the services running on the background of your system. This includes for example the Docker runtime, web servers, daemons, system services, and many other things.

[Screencast from 2023-08-20 12-55-39.webm](https://github.com/luizgfranca/SISM/assets/19842670/e4979e4a-96aa-4b24-a829-ea132beae167)

This project is currently on the intial steps of development, so it's pretty barebones and doesn't have the best user experience, but I want to make many cool things with it!


## Motivation

GNU/Linux is a very powerful platform, it enables the users to have a more extensive control over the operating system behavior, but the interface for many  of those resources is hidden behind complicated interfaces with low discoverability, so even many power users don't even know some of them exist. 

One of those powers is the management of what runs in your system, we have many abstractions developed and perfected over the years for use on servers, but those are only discoverable when a person takes time to stop and study them in not so accessible documentation, this project aims to expose them, and give 
more power to users.

The Original inspiration was the Windows Services manager, but I think we can make a much more powerful tool with what the platform enables us to do!

## Installation

Current supported distributions are `Fedora 38` and `Ubuntu 23.04`.

### Fedora 38
The project has an RPM package that can be used for the fedora 38 installation:
 - Download the `sism-0.5.0-1.x86_64.rpm`
 - Run `sudo dnf install sism-0.5.0-1.x86_64.rpm`
 - To start the application use `sism` on the commmand line

### Ubuntu 23.04
 - Download the `sism-0.5.0.zip` release file
 - Uncompress it
 - Open the terminal on the uncompressed folder
 - Run `sudo ./install.sh`

## Current development progress

As is said above, the project is in its initial steps of development, it was writen in the most simple way until the `0.2.0` release (I call it an MVP), but now the aim is to progress
refactoring it, polishing current behavior, and improving the user experience, and adding more essential features. Feedback is very much wellcome!

Initially this project is implementing support only for Systemd managed operating systems, but the intention is supporting SysV and other init systems and service platforms in the future.

Currently the installation is only tested in `Fedora 38` (the system I currently use) and `Ubuntu 23.04`. It should work in other distributions and/or versions
but it may require fiddling with libraries if they are older. It is my intention supporting some of them, and thinking of a less distro specific way of distribution.

## Building and running it from source

### Dependencies
 - CMake >= 3.25
 - gtk-4
 - glibmm-2.68
 - cairomm
 - pangomm
 - gtkmm-4
 - sdbus-cpp

### Run from source

 - Clone this repository
 - Enter the project folder with the terminal
 - Run `./tools/run.sh`

### Build the release from source

 - Clone this repository
 - Enter the project folder with the terminal
 - Run `tools/release.sh <release-version>` where `release-version` can be `0.5.0` for instance`
 - The build files will be on the `dist` folder


