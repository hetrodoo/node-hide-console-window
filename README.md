# node-hide-console-window

A node module to toggle your app's console window visibility. (Can be used with compilers like [pkg](https://www.npmjs.com/package/pkg))

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
import { ShowConsole, HideConsole } from "node-hide-console-window";

//To hide your console just call:
HideConsole();

//To show it again use:
ShowConsole();
```

#### Using require syntax
```typescript
const ConsoleWindow = require("node-hide-console-window");

//To hide your console just call:
ConsoleWindow.HideConsole();

//To show it again use:
ConsoleWindow.ShowConsole();
```
## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License
[MIT](https://choosealicense.com/licenses/mit/)