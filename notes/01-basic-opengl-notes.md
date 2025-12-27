# chapter 1: basic openGL notes

This file contains basic openGL notes

openGL is a state machine. meaning it maintains a large set of states that
affect how commands are processed. for example, the command to draw something
will behave differently depending on what shader program is currently active,
what textures are bound, what the blend mode is, etc.

There are many states in openGL, and they can be changed by calling various
openGL is specification functions.

openGL does not have a concept of a "default" state. when a context is
created, all states are initialized to default values defined by the openGL
specification. however, these default values may not be what you want for your
application, so it is important to explicitly set the states you care about.

openGL is a set of state and commands that operate on that state.

The openGL specification defines a large number of states that can be set and
queried, as well as a large number of commands that operate on those states.

Some examples of openGL states include:

- The current shader program
- The current bound textures
- The current blend mode
- The current depth test function
- The current viewport size

Some examples of openGL commands include:

- Drawing commands (e.g. glDrawArrays, glDrawElements)
- State-setting commands (e.g. glEnable, glDisable, glBlendFunc)
- Resource management commands (e.g. glGenBuffers, glBindBuffer, glBufferData)

In order to use openGL effectively, it is important to understand how to
manage its state and how to use its commands to achieve the desired rendering
effects.

opengl is a low-level graphics API that provides a set of functions for rendering
2D and 3D graphics. it is designed to be platform-independent and hardware-
agnostic, allowing developers to create graphics applications that can run on
a wide range of devices.

opengl is often used in conjunction with other libraries and frameworks,
such as glfw for window management and input handling, and glad for loading
openGL function pointers.

opengl is widely used in the development of video games, simulations,
and other graphics-intensive applications.

it provides a powerful and flexible set of tools for creating high-quality
graphics, but it also requires a good understanding of computer graphics
concepts and programming techniques.

opengl is a state machine, meaning that it maintains a large set of states
that affect how commands are processed. for example, the command to draw
something will behave differently depending on what shader program is
currently active, what textures are bound, what the blend mode is, etc.
