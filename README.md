# SISM - Services manager for the GNU/Linux desktop

Sism is a tool to discover and manage the services running on the background of your system: web servers, daemons, system services, and many other things.



https://github.com/luizgfranca/Sism/assets/19842670/35c1fb3c-a55d-41e1-ae51-90a55a6365ea


This project is currently on the intial steps of development, so it's pretty barebones and doesn't have the best user experience, but I want to make many cool things with it!


### Motivation

GNU/Linux is a very powerful platform, it enables the users to have a more extensive control over the operating system behavior, but the interface for many of those resources is hidden behind complicated interfaces with low discoverability, so even many power users don't know some of them exist. 

One of those powers is the management of what runs in your system, we have many abstractions developed and perfected over the years (used mainly for servers, but also very useful in other environments), but those are only discoverable when a person takes time to stop and study them in not so accessible documentation, this project aims to expose them, and give 
more power to users.

The Original inspiration was the Windows Services manager, but I think we can make a much more powerful tool with what the platform enables us to do!


## Getting Started

You can install using the provided DEB and RPM packages, manually install using the provided binary, or build thhe project from source


### Normal Installation

Current supported distributions are `Fedora >= 38` and `Ubuntu >= 23.04`.

#### Fedora >= 38
The project has an RPM package that can be used for the fedora 38 installation:
 - Download the `sism-0.7.0-1.x86_64.rpm` release file
 - On the download folder run `sudo dnf install sism-0.7.0-1.x86_64.rpm`
 - Search for the application in your main menu

#### Ubuntu >= 23.04
 - Download the `sism-0.7.0-1_amd64.deb` release file
 - On the download folder run `sudo apt install sism-0.7.0-1_amd64.deb`
 - Search for the application in your main menu

It is in my intentions to support older releases, and other distributions, I will just have to wrestle against some dependencies.


### Building and running it from source

#### Dependencies
 - CMake >= 3.25
 - conan
 - gtk-4
 - glibmm-2.68
 - cairomm
 - pangomm
 - gtkmm-4
 - sdbus-cpp

#### Run from source

 - Clone this repository
 - Enter the project folder with the terminal
 - Run `./tools/run.sh`

#### Build the release from source

 - Clone this repository
 - Enter the project folder with the terminal
 - Run `tools/release.sh <release-version>` where `release-version` can be `0.7.0` for instance`
 - The build files will be on the `dist` folder


## Current development progress

As is said above, the project is in its initial steps of development, it was writen in the most simple way until the `0.2.0` release (I call it the MVP), but now the aim is to progress
refactoring it, polishing current behavior, improving the user experience, and adding more essential features. Feedback is very much wellcome!

Initially this project is implementing support only for Systemd managed operating systems, but the intention is supporting SysV and other init systems and service platforms in the future.

