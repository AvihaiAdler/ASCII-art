####ASCII art
Playing with some ASCII art. The program will convert the content of "input.txt" into ASCII art and display it in stdout. Note that the art is affected by the terminal max display characters (the terminal won't display long strings properly). The program supports ASCII only an don't support punctuations.

######Building and compiling
To build use `cmake -S <source_dir> -B <build_dir> -G <generator>` (`-G <generator>` can be left out if you don't care about it. CMake default generator is `GNU make`)
`<generator> -C <build_dir>`

for example, assuming your working directory is the project (root) directory:
`cmake -S . -B build -G Ninja`
`ninja -C build`
will create an executable named `glyph` in your working directory.