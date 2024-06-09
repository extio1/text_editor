![workflow](https://github.com/extio1/text_editor/actions/workflows/on_pull_request.yml/badge.svg)   

# Overview
The project was inspired by [**Gang of Four Design Patterns**](https://springframework.guru/gang-of-four-design-patterns/) and implemented on **C++**. The prototype is *LeXI* from the book.    

Constructively MVC used.

Patterns are used:
* **Composite** ([include/document/glyphs](https://github.com/extio1/text_editor/tree/release/include/document/glyphs)) represents hierarchy of *glyph*s, so via only reference to *glyph* user manipulates with column, row, character, page, etc.
* **Compositor** ([include/compositor](https://github.com/extio1/text_editor/tree/release/include/compositor)) encapsulates algorithm of format document. This way, there is possibility to change it in runtime. Also there's low cohesion between algorithm (compositor) and data structure (document).
* **Command** ([include/executor](https://github.com/extio1/text_editor/tree/release/include/executor)) gives API to operate with document via *Executor* object executing *Command*. Encapsulates command history, so ctrl+z, ctrl+y commands are supported (current supported command list in [include/executor/command](https://github.com/extio1/text_editor/tree/release/include/executor/command))

## Requirements
* C++14 or newer
* Boost serialization library **1.8.0 or newer**. e.g. Download archive from [boostorg.jfrog.io](https://boostorg.jfrog.io/artifactory/main/release/1.80.0/source/boost_1_80_0.tar.gz)

## Installation
```shell
mkdir build; cd build
cmake ..
cmake —build .
```
## Usage
Cmake builds **text_editor** executable in build.

### Contacts
* [extio1](https://github.com/extio1)
* [tatyanakrivonogova](https://github.com/tatyanakrivonogova)
* [Sandy159](https://github.com/Sandy159)