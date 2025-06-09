# Simple real-time operating system for STM32F4 family microcontrollers.


## Building the code

Before you can build the firmware, make sure you have the required cross-compiler installed:

1. Install the ARM cross-compiler </br>
On Debian/Ubuntu-based systems: </br>
```sh
sudo apt install gcc-arm-none-eabi
```

2. Create a build directory </br>
Navigate to the os project directory and create a build folder: </br>
```sh
cd os
mkdir build
cd build
```

3. Generate build files using CMake </br>
Inside the build directory, run: </br>
```sh
cmake ..
```

4. Compile the project </br>
Still inside the build directory, compile the code: </br>

```sh
make
```
After a successful build, this will produce a firmware.bin file — the final binary ready to run on the board or simulator. </br>

5. Run the firmware </br>
To launch the firmware in a simulator (like Renode), you can use a preconfigured Docker container. Instructions for that are provided in the next section. </br></br>
To launch the firmare on board see Flashing board section </br>

## Running on docker with [Renode](https://github.com/renode/renode) emulator. 

Note for Windows users: Run these commands from WSL </br>
1. Build the Docker image </br>
From the os directory, build the Docker image:
```
docker build -t stm ./
```

2. Create the Docker container
```
docker create --name stm-container \
  -e DISPLAY=$DISPLAY \
  -v /tmp/.X11-unix:/tmp/.X11-unix \
  -v ./build:/app/build \
  -p 3333:3333 \
  --mount type=bind,source="$(pwd)/stm32f4.resc",target=/renode/stm32f4.resc \
  -ti stm
```

3. Start the container and launch Renode </br>
Run the container interactively:
```
docker start -ai stm-container
```

Restarting the container
For future runs, simply use:
```
docker start -ai stm-container
```

Updating the firmware
1. Rebuild the code with make (in the build directory).
2. In the Renode terminal, enter the following command:
```
machine Reset
```
This reloads the new firmware.bin without restarting the container.

## Operating Renode eumulator

commands in emulator:
- s, start - starts emulator
- p, pause - stops emulator
- machine Reset - loads new buit firmware
- q, quit - quits emulator
- showAnalyzer usart1 - shows uart1 terminal monitor 

## Flashing board

https://github.com/stlink-org/stlink </br>
can be install in debian based distros with: `sudo apt install stlink-tools` </br>

in build folder to flash board use run:
`st-flash --reset write firmware.bin 0x8000000`

to see terminal monitor communication one can use cu command
`cu -l /dev/ttyACM0 -s 9600`


## Debuging code
To debug your code using Visual Studio Code (with a launch.json configuration), you'll need to install the GDB multi-architecture debugger:
```
sudo apt install gdb-multiarch
```
