# Chapter 1: Basic OpenGL Notes

## OpenGL as a State Machine

OpenGL is a **state machine**, meaning it maintains a large set of states that
affect how commands are processed.

For example, a draw command behaves differently depending on:

- The active shader program
- Bound textures
- Blend mode
- Depth testing state

## Important Concepts

- OpenGL does not have a single "default" state
- States are initialized by the OpenGL specification
- You should explicitly configure the states you rely on
- OpenGL consists of **state + commands**

## Examples of OpenGL States

- Current shader program
- Bound textures
- Blend mode
- Depth test function
- Viewport size

## Examples of OpenGL Commands

- Drawing:
  - `glDrawArrays`
  - `glDrawElements`
- State control:
  - `glEnable`
  - `glDisable`
  - `glBlendFunc`
- Resource management:
  - `glGenBuffers`
  - `glBindBuffer`
  - `glBufferData`

OpenGL is a low-level API that offers great control but requires a strong
understanding of graphics programming concepts.
