**Project FDF**

**Overview**

Project FDF is a dynamic 3D wireframe renderer that visualizes map files in a captivating, interactive way. Breathe life into your maps with this powerful tool.

**Features**

* Interactively visualize 3D wireframe models from map files.
* Explore and manipulate rendered maps. 
* Customize rendering styles (e.g., colors, line thickness).

**Getting Started**

**Prerequisites**

* The same prerequisites as [MLX42](https://github.com/codam-coding-college/MLX42).
* All submodules are included in the project repository.

**Compile**

Just run the following command to compile the project:
```bash
make
```

**Running**

To run the project, execute the program (fdf) with a map file as an argument. For example, to render the map `42.fdf`, run the following command:

```bash
./fdf test_maps/42.fdf
```

**Test Maps**

The `test_maps` folder includes sample maps to get you started. Experiment and discover!

**TODO**

* Improve map loading efficiency using `get_next_line`.
* Refactor code for better readability and maintainability.
* Add a control section to the README.
* Add a screenshot to the top of the README.
