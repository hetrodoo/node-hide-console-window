# [node-hide-console-window](https://www.npmjs.com/package/node-hide-console-window)

[![Downloads](https://img.shields.io/npm/dt/node-hide-console-window)](https://www.npmjs.com/package/node-hide-console-window)
[![Issues](https://img.shields.io/github/issues/hetrodoo/node-hide-console-window)](https://github.com/hetrodoo/node-hide-console-window/issues)
[![Licence](https://img.shields.io/npm/l/node-hide-console-window)](https://github.com/hetrodoo/node-hide-console-window/blob/master/LICENSE)

A node module to toggle your app's console window visibility. (Can be used with compilers
like [pkg](https://www.npmjs.com/package/pkg))

### Platforms

- Windows

## What's new in 2.2.0

- Windows terminal support (thanks to GitHub user [titushm](https://github.com/titushm))

## Warning

Recently this package have been a victim of a typosquatting attack where some bad actors created a clone of this package
but appended a 's' at the end, **this package isn't and never was compromised**, but if you want you can take a look at the
source code or build it yourself, always check your packages before installing, take care out there!

## Installation

```bash
yarn add node-hide-console-window
```

or

```bash
npm install node-hide-console-window
```

## Usage

#### Using import syntax

```typescript
import {showConsole, hideConsole} from "node-hide-console-window";

//To hide your console just call:
hideConsole();

//To show it again use:
showConsole();
```

#### Using require syntax

```typescript
const ConsoleWindow = require("node-hide-console-window");

//To hide your console just call:
ConsoleWindow.hideConsole();

//To show it again use:
ConsoleWindow.showConsole();
```

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License

[MIT](https://choosealicense.com/licenses/mit/)
