# Simple real-time operating system for STM32F4 family microcontrollers.


### Building code
1. create a build folder in os directory
2. in build directory run
```sh
cmake ..
```
3. then run
```sh
make
```
  it creates a firmware.bin file </br>
4. to launch code, you can use docker container descibed in next section

### Running on docker with [Renode](https://github.com/renode/renode) emulator. 

If on windows run these commands from wsl </br>
In os directory run:
1. `docker build -t stm ./`

2. `docker create --name stm-container -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix -v ./build:/app/build -ti -p 3333:3333 --mount  type=bind,source=./stm32f4.resc,target=/renode/stm32f4.resc stm`

3.  `docker start -ai stm-container`

then next container startup with: `docker start -ai stm-container` </br>
to update software just build code and enter machine Reset in emulator

### Operating Renode eumulator

commands in emulator:
- s, start - starts emulator
- p, pause - stops emulator
- machine Reset - loads new buit firmware
- q, quit - quits emulator
- showAnalyzer usart1 - shows uart1 terminal monitor 

### Flashing board

https://github.com/stlink-org/stlink </br>
can be install in debian based distros with: `sudo apt install stlink-tools` </br>

in build folder to flash board use run:
`st-flash --reset write firmware.bin 0x8000000`

to see terminal monitor communication one can use cu command
`cu -l /dev/ttyACM0 -s 9600`
