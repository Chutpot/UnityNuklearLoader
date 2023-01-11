# UnityNuklearLoader

Unity Nuklear Loader is an dynamic library to load in Unity to create interface to integrate Nuklear Apps.

---
## What is Nuklear?

>This is a minimal-state, immediate-mode graphical user interface toolkit written in ANSI C and licensed under public domain. It was designed as a simple embeddable user interface for application and does not have any dependencies, a default render backend or OS window/input handling but instead provides a highly modular, library-based approach, with simple input state for input and draw commands describing primitive shapes as output. So instead of providing a layered library that tries to abstract over a number of platform and render backends, it focuses only on the actual UI.

##Motivation
Creating a cross platform ready to use IMGUI library with a minimal dependency. The library initializes itself without user interaction and Unity Editor(URP ,HDRP and etc).

##Support

| Platform                  |                    |
| -----------------         | ------------------ |
| Windows                   | :heavy_check_mark: |
| MacOS                     | :x:                |
| Linux                     | :x:                |

| API                  |                    |
| -----------------         | ------------------ |
| D3D11                     | :heavy_check_mark: |
| D3D12                     | :x:                |
| Vulkan                    | :x:                |
| Metal                   | :x:                |

## Gallery
![Screenshot](.github/images/loader_image.png)