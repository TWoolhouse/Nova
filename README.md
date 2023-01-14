# Nova
A C++ Game Engine.

## Configuration

`Nova/build.h` can be used to set global configuration variables directly in C++ as opposed to using premake.

### Build

#### Nova Build Self
`#define NOVA_BUILD_SELF`
Tells the engine it is building itself. Omitting this, Nova assumes it is being used as a library.

#### NOVA_BUILD_OPTIMISE
`#define NOVA_BUILD_OPTIMISE_<OPT>`
- `DEBUG`
- `RELEASE`

Specifies if the engine should add extra debugging information. If neither is specified, Nova will look for `DEBUG`.

#### NOVA_BUILD_LINK
`#define NOVA_BUILD_LINK_<OPT>`
- `STATIC`
- `DYNAMIC`

Is the engine being used as a static library or a dynamic library.

### APIs

#### NOVA_ABYSS
`#define NOVA_ABYSS_<API>`
- `VULKAN` - Recommend
- `DIRECTX`
- `OPENGL`

Selects the Graphics API the engine will use.

#### NOVA_MLB
`#define NOVA_MLB_<API>`
- `GLM` - Recommend
- `NOVA`

Selects the maths library to use.

#### NOVA_WINDOW
`#define NOVA_WINDOW_<API>`
- `NATIVE` - Recommend
- `GLFW`

Selects the API used to create the window / interact with the OS' windowing system.

### Bark

Configuration options for the logging subsystem.

#### __N_OVA_BARK_ASSERT
`#define __N_OVA_BARK_ASSERT <BOOL>`:
- `0`
- `1` - Default

Enables runtime assertions.

#### __N_OVA_BARK_FILE
`#define __N_OVA_BARK_FILE <BOOL>`:
- `0`
- `1` - Default

Writes the logging output to a file.

#### __N_OVA_BARK_CONSOLE
`#define __N_OVA_BARK_CONSOLE <BOOL>`:
- `0`
- `1` - Default

Writes the logging output to the console.

#### __N_OVA_BARK_WARN
`#define __N_OVA_BARK_WARN <BOOL>`:
- `0`
- `1` - Default

Enables warning messages.

#### __N_OVA_BARK_INFO
`#define __N_OVA_BARK_INFO <BOOL>`:
- `0`
- `1` - Default

Enables info messages.

#### __N_OVA_BARK_INIT
`#define __N_OVA_BARK_INIT <BOOL>`:
- `0`
- `1` - Default

Enables initialisation / termination messages.

#### __N_OVA_BARK_TRACE
`#define __N_OVA_BARK_TRACE <BOOL>`:
- `0`
- `1` - Default

Enables trace messages.

#### __N_OVA_BARK_DEBUG
`#define __N_OVA_BARK_DEBUG <BOOL>`:
- `0`
- `1` - Default

Enables debug messages.

### Abyss

Options for the backend graphics rendering subsystem.

#### __N_OVA_ABYSS_DEBUG
`#define __N_OVA_ABYSS_DEBUG <BOOL>`:
- `0`
- `1` - Default

Enables the GFX API's validation layers.

#### __N_OVA_ABYSS_CHECK
`#define __N_OVA_ABYSS_CHECK <BOOL>`:
- `0`
- `1` - Default

Check the result of every GFX API call.

#### __N_OVA_ABYSS_BARK_WARN
`#define __N_OVA_ABYSS_BARK_WARN <BOOL>`:
- `0`
- `1` - Default

Enables warning messages from the GFX API.

#### __N_OVA_ABYSS_BARK_INFO
`#define __N_OVA_ABYSS_BARK_INFO <BOOL>`:
- `0`
- `1` - Default

Enables info messages from the GFX API.

#### __N_OVA_ABYSS_BARK_DEBUG
`#define __N_OVA_ABYSS_BARK_DEBUG <BOOL>`:
- `0`
- `1` - Default

Enables debug messages from the GFX API.

## Systems

### Abyss
A graphics API abstraction layer, implementing a generic specification, upheld using `concepts`.

GFX API's:
- Vulkan
- *DirectX 12* - TODO
- ~~OpenGL~~

#### Tower
The tower controls the distrobution of frames in flight as well as submitting the frame to the present queue.

```c++
Nova::abyss::Tower tower;
auto& flight = tower.acquire();
// Use the active frame ...
tower.release(flight);
```

#### Buffers

##### Raw Buffer
A raw buffer, which the following buffers are composed of. A buffer requests certain [`scopes`](#scopes) which determine which operations are available / which memory the buffer is allocated in.

```c++
Nova::abyss::buffer::Buffer buffer_raw{
	size_in_bytes,
	Nova::abyss::buffer::Type::Vertex,
	Nova::abyss::buffer::Scope::Bind | Nova::abyss::buffer::Scope::Write
};
```

Writing into host memory directly by acquiring a local ptr;
```c++
auto ptr = buffer.acquire();
memcpy(ptr, stuff.data(), stuff.size())
buffer_raw.release();
```

##### Scopes
Buffer Scopes are the memory / access requirements of a buffer. They allow for certain operations to be performed and these are validated during the runtime of debug builds.

##### Vertex Buffer

There are two types of vertex buffer, both of which are [raw buffers](#raw-buffer). There is a template vertex buffer, with the type of a single vertex, and a generic vertex buffer which stores the number of elements. It is possible to cast between the two, there is a debug test to ensure the buffers are compatible.

```c++
struct Vertex {
	using Spec = Nova::meta::pack<Nova::mlb::vec2, Nova::mlb::vec3>;
	Nova::mlb::vec2 position;
	Nova::mlb::vec3 colour;
};
std::vector<Vertex> vertices;
Nova::abyss::buffer::Vertex<Vertex> buffer_vertex{ vertices.size() };

Nova::abyss::buffer::VertexI buffer_generic_vertex{ std::move(buffer_vertex) };
```

#### Shader

```c++
Nova::abyss::shader::Graphics pipeline{
	nova_abyss_app->tower.renderpass,
	{
		{ Nova::abyss::Shader::Stage::Vertex, "path/to/shader/.vert" },
		{ Nova::abyss::Shader::Stage::Fragment, "path/to/shader/.frag" },
	},
	Nova::meta::pack<decltype(buffer_vertex)>{}
};
```

### Bark

A logging system using `std::format` syntax.

#### Logging

Messages are sent to either `std::cout` or `std::cerr` depending on the severity of the message. Furthermore, the output is sent to a log file which includes the file & line the message came from.

```c++
nova_bark_debug("Message: {}", parameter);
nova_bark_trace("Message: {}", parameter);
nova_bark_info("Message: {} - {}", parameter1, parameter2);
nova_bark_warn("Message: {}", parameter);
nova_bark_error("Message: {}", parameter);
nova_bark_fatal("Message: {}", parameter);
```

#### Assertion

Debug runtime assertion. Causes the debugger to break, if connected.

```c++
nova_assert(condition, "Assertion Message");
```

#### Timer

A scope based timer. `nova_bark_debug` the time elapsed from initialisation to destruction.

```c++
nova_bark_timer("Timer Name");
```

### Blip

Time.

#### Delta

Tracks the time between each call to `update`.

#### Timer

Contains the elapsed between object initialisation and the last call to the `update` method.

#### Clock

A combination of both Timer & Delta

### Eden

An event system.

### Event

Mouse & Keyboard & Window Events
Subject to change

### Input

Current state of Mouse & Keyboard. e.g. is a key currently pressed.

### Meta

C++ Macros / Meta-Templates

#### Pack

A variadic template parameter pack as a single type with many helper methods / attributes.

### Mlb

Maths library. GLM + extra utility.

### Nvtl

Nova Template Library.

#### Weave

#### Cache

#### CacheConstructor

### Platform

OS specific implementations.

### Verglas

Frontend Renderer.
