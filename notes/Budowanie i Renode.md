## vsc extensions

w pliku extensions.json

## budowanie ręcznie

w folderze os/build (najlepiej tak bo task do debugowania uzywa folderu os/build)

```sh
mkdir build
cd build
cmake ..
```

## budowanie z extension cmake

ctrl+shift+p i wybrać Cmake: build

## jakies komendy renode

machine GetClockSourceInfo
machine Reset

s, start - odpala
p, pause - stopuje
machine Reset - wgrywa nowy firmware
q, quit - aby wyjść
showAnalyzer usart1

## odpalenie renode lokalnie

./renode --console ./stm32.resc

## odpalenie na dockerze

1.  docker build -t stm ./

2.  docker create --name stm-container -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix -v ./build:/app/build -ti -p 3333:3333 --mount type=bind,source=./stm32f4.resc,target=/renode/stm32f4.resc stm

3.  docker start -ai stm-container

startowanie kontenera pozniej: docker start -ai stm-container

aby wgrac nowy soft należy zbudowac nowy soft i wpisać machine Reset w terminalu renode

Debugowanie działa z launch vsc, potrzebuje pakietu gdb-multiarch (sudo apt install gdb-multiarch)
