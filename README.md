# Dynamic_Static.Core provides general purpose C++ utilities.

`Dynamic_Static.Core` requires Visual Studio 2015 with the latest updates.
Ubuntu 16.04 support will be merged soon.

To build on Windows 10 (7 and 8 likely work but are untested), create a `/Dynamic_Static/` directory wherever it's convienient.
`Dynamic_Static.Core` should live in that directory...ie... `some/path/Dynamic_Static/Dynamic_Static.Core/`.
Then add the environment variable `DYNAMIC_STATIC_HOME` and point it at the `/Dynamic_Static/` directory.

[Rapid Environment Editor](https://www.rapidee.com/en/about) isn't required, but it's a great tool for editing environment variables on Windows.

Open `Dynamic_Static.Core.sln` in Visual Studio and use `[Alt] + [B], [Alt] + [T]`, then click `Select All`, then click `Build` to build all.

To run `Dynamic_Static.Core.Tests`, right click on the `Tests` project in the `Solution Explorer`, then click `Set as Startup Project` then run...some of the tests will fail.

Unless otherwise noted, all of the files in `Dynamic_Static.Core` are licensed under the [MIT License](https://opensource.org/licenses/MIT).<br />

____
3rd Party Libraries used by `Dynamic_Static.Core` :<br />
[glm](http://glm.g-truc.net/) : [The Happy Bunny License and MIT License](http://glm.g-truc.net/copying.txt)

// TODO : MORE BETTER README.
