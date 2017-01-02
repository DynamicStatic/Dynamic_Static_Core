# Dynamic_Static_Core provides general purpose C++ utilities.

`Dynamic_Static_Core` requires Visual Studio 2015 with the latest updates.
Ubuntu 16.04 support will be merged soon.

To build on Windows 10 (7 and 8 likely work but are untested), create a `/Dynamic_Static/` directory wherever it's convienient.
`Dynamic_Static_Core` should live in that directory...ie... `some/path/Dynamic_Static/Dynamic_Static_Core/`.
Then add the environment variable `DYNAMIC_STATIC_HOME` and point it at the `/Dynamic_Static/` directory.

[Rapid Environment Editor](https://www.rapidee.com/en/about) isn't required, but it's a great tool for editing environment variables on Windows.

Open `Dynamic_Static_Core.sln` in Visual Studio and use `[Alt] + [B], [Alt] + [T]`, then click `Select All`, then click `Build` to build all.

To run `Dynamic_Static_Core.Tests`, right click on the `Tests` project in the `Solution Explorer`, then click `Set as Startup Project` then run...some of the tests will fail.

Unless otherwise noted, all of the files in `Dynamic_Static_Core` are licensed under the [MIT License](https://opensource.org/licenses/MIT).<br />
Any file in a `3rdParty` directory in the `Dynamic_Static_Core` project may have a different license.<br />
____
3rd Party Libraries used by `Dynamic_Static_Core` :<br />
[glm](http://glm.g-truc.net/0.9.8/index.html) : [The Happy Bunny License and MIT License](http://glm.g-truc.net/copying.txt)

// TODO : MORE BETTER README.
