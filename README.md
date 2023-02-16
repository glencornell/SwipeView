# QSwipeView Widget

The SwipeView is a c++ implementation of the QML widget of the same
name.

## Features

 - Manually move from/to any widget in the stack
 - Use mouse movement to swipe previous/next widgets in stack
 - Use flick gestures (mouse movement velocity) to go to previous/next widget in stack
 - Horizontal or vertical direction

## TODO

 - [ ] Create QTDesigner Plugin to view the widget in the layout
 - [ ] Refactor/Simplify code - I suspect that this can be made more efficient
 - [ ] Build PageViewIndicator, GoTo Page buttons, and SwipeView into one composite widget
 - [ ] Make install rules to build and install the project as a library
 - [ ] Create a packages (debian, Yum, buildroot, etc)

## Building

You have several options for including these widgets into your
project.  You can copy the widgets that you want into your project and
include the `.pri` file into your qmake project.  Alternatively, you
can install this project in your system as a ibrary.

Take a look at the various [examples](examples/README.md) available to
see how to incorporate these widgets into your projects.

## Bugs

Let me know if you see a bug and either submit a pull request or let
me know about it.  I would love to know who's using this in their
projects.

## Attribution

Copyright 2023, Glen Cornell <glen.m.cornell@gmail.com>

## License

MIT License, as found in the [LICENSE](LICENSE) file.
