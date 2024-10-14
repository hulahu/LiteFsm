# LiteFsmDeom
A demo with simple state switching, it will show how to define states, events, guards and actions for your application.

## Build and run the demo
Here below is the steps to build within Linux. For embedded platform, copy the `example` and `include` folder to the embedded project, and change the compiler option to meet the requirement of platform.

```bash
$ cd example; cmake -B build -S .
$ cd build; make all
$ ./liteFsmDemo
```
