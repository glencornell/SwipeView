# XDG Application Launcher

This program reads the `.menu` file compliant with the [XDG Menu
Specification](https://specifications.freedesktop.org/menu-spec/latest/)
and the `.directory` and `.desktop` files conformant with the [XDG
Desktop
Entry](https://specifications.freedesktop.org/desktop-entry-spec/latest/)
specifications to construct a swipeview with multiple pages.  Each
desktop entry is represented with an icon and text laid out on a page
within the swipeview.  The `.directory` entries support an extension
called `X-Background-Image`, which specifies the background image used
on that menu.

Although the code reads and writes the XDG files, it does not allow
the user to navigate into child menu entries in the Menu document
hierarchy.

## Build

```bash
qmake6
make
```

## Run

Because the files are stored locally, you need to set the
`XDG_DATA_HOME` environment variable in order for the application to
find the `home.menu` and all of it's referenced children.

```bash
XDG_DATA_HOME=$(pwd)/etc ./test-layout
```