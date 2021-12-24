# raspberry-pi-os
此项目是对[raspberry-pi-os](https://github.com/s-matyukevich/raspberry-pi-os)的学习笔记，通过学习这个项目来学习ARM V8体系结构及操作系统知识。在我个人平常的学习中，一般都只是了解一下实现的过程，并没有具体的上手去写，俗话说的好，纸上得来终觉浅，也希望通过这个项目，能够真正上手，入门一个OS kernel的开发，作为kernel爱好者的lesson01。  
在项目实现过程中，也会参考linux的实现过程，例如linux各个子系统的布局，或是关键数据结构的设计，使用，在这些方面会尽量去学习linux的设计，然后在原作者的基础上，增加自己对linux理解的代码，实现一个二次创作，而不是仅仅把代码抄过来。  
此项目的各个lesson是一步一步的去实现一个kernel，从机器的boot到系统初始化，子系统的初始化。所以在这个项目的最后，raspberry-pi-os会与linux类似，包含不同的，简化版的子系统。

## 内容
* **Lesson 1: Kernel Initialization** 
    * 1.1 [Introducing RPi OS, or bare metal "Hello, world!"](document/lesson01/doc.md)
* **Lesson 2: Processor initialization**
* **Lesson 3: Interrupt handling**