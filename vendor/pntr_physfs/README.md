# pntr_physfs

[PhysicsFS](https://github.com/icculus/physfs) support for [pntr](https://github.com/RobLoach/pntr) to load and save images with PhysFS.

## Usage

Include [`pntr_physfs.h`](pntr_physfs.h) before including `pntr.h`. This will define `PNTR_LOAD_FILE` and `PNTR_SAVE_FILE` to have pntr load/save files with PhysicsFS.

``` c
#include "physfs.h"

#define PNTR_PHYSFS_IMPLEMENTATION
#include "pntr_physfs.h"

#define PNTR_IMPLEMENTATION
#include "pntr.h"

int main() {
    // Initialize PhysFS
    PHYSFS_init(0);
    PHYSFS_mount("resources.zip", "res", 1);

    // Load an image from the resources.zip file.
    pntr_image* image = pntr_load_image("res/hello.png");

    // Deinitialize PhysFS
    PHYSFS_deinit();
}
```

## License

Unless stated otherwise, all works are:

- Copyright (c) 2023 [Rob Loach](https://robloach.net)

... and licensed under:

- [zlib License](LICENSE)
