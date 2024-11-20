machine GetClockSourceInfo
machine Reset

s, start - odpala
p, pause - stopuje
machine Reset - wgrywa nowy firmware

./renode --console ./stm32.resc

można debugować przy użyciu w launch. Renode debug
działa na dockerze i lokalnie

## odpalenie na dockerze

//budowane na wsl, bo na windowsie nie wyświetla okienka xd

1.  docker build -t stm ./

2.  docker create --name stm-container -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix -ti -p 3333:3333 stm

3.  docker start -ai stm-container
