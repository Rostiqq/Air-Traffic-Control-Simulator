#  Air Traffic Control Simulator

![C++](https://img.shields.io/badge/C%2B%2B-17%2B-00599C?logo=cplusplus&logoColor=white)
![SFML](https://img.shields.io/badge/SFML-3-8CC445?logo=sfml&logoColor=white)
![Status](https://img.shields.io/badge/status-in%20development-orange)

A 2D air traffic control simulator written in C++ with SFML 3. Follow aircraft on screen, select one to guide it toward an airport, and keep an eye on traffic separation warnings.

## Preview

<div align="center">
  <img src="assets/preview.png" alt="Simulator overview showing aircraft and airports" width="800">
  <p><em>Simulator overview with sample aircraft and the LZIB and LZIT airports.</em></p>
</div>

<div align="center">
  <img src="assets/tcas-warning.png" alt="Aircraft displaying a TCAS warning" width="500">
  <p><em>Aircraft separation warning shown when the sample traffic is too close.</em></p>
</div>

## Contents

- [Features](#features)
- [Built with](#built-with)
- [Getting started](#getting-started)
- [Controls](#controls)
- [Project status](#project-status)
- [License](#license)

## Features

- Displays aircraft and airports in a 2D window.
- Selects an aircraft with the left mouse button.
- Moves the selected aircraft toward the runway of its assigned destination airport.
- Shows aircraft details such as callsign, speed, heading, altitude, destination, and state.
- Checks nearby aircraft and displays a TCAS warning when they are too close and their altitude difference is below 1,000 feet.
- Includes two sample airports, identified as `LZIB` and `LZIT`, and three sample aircraft.

## Built with

- C++
- [SFML 3](https://www.sfml-dev.org/)

## Getting started

Open `Air Traffic Control Simulator.sln` in Visual Studio and build the project with SFML 3 configured for your environment. The application also loads `GeistMono-Regular.ttf` by filename, so keep that font file in the working directory when running the program.

The exact SFML package setup and Visual Studio configuration may depend on how SFML was installed on your machine.

## Controls

- **Left mouse button** — select an aircraft.

The selected aircraft follows its assigned destination when that destination matches one of the airports in the current demo (`LZIB` or `LZIT`).

## Project status

This is an early prototype. Aircraft, airports, and their initial values are currently created directly in the application. The simulation is under active development.

## License

This project is licensed under the MIT License. See [`LICENSE.txt`](LICENSE.txt).
