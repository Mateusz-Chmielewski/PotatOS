# Simple real-time operating system for STM32F4 family microcontrollers.

### Running on docker with [Renode](https://github.com/renode/renode) emulator. 

1. ` docker build -t stm ./`

2. `docker create --name stm-container -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix -v ./build:/app/build -ti -p 3333:3333 --mount  type=bind,source=./stm32f4.resc,target=/renode/stm32f4.resc stm`

3.  `docker start -ai stm-container`

