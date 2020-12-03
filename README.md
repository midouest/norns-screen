# norns-screen

Javascript clone of the Norns `matron/hardware/screen` C module

**NOTE:** This library is in the prototype phase. Expect things to be broken.

## Usage

The library attempts to load the norns built-in font `04B_03__`. You will need to copy `04B_03__.TTF` from the norns repository to the root of your project. There may be issues using methods that rely on fonts.

```javascript
const NornsScreen = require("norns-screen");

screen.aa(1);
screen.level(15);
screen.line_width(2);
screen.move(0, 0);
screen.line(64, 32);
screen.stroke();
screen.update();

screen.export_png("example.png");
```

## Building

### macOS

This library depends on `cairo`. Currently it is configured to look in `/usr/local/lib` when linking static libraries.

```
> brew install cairo
> yarn
```

### Other

Platforms other than macOS are not supported at this time.
