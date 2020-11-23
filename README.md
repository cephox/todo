# todo
A simple command line tool to manage your own todo lists for different projects

## Installation
```bash
# Clone this repository
git clone https://github.com/cephox/todo
cd todo

# Build the binary file
make

# Install the executable
sudo make install

# To uninstall
sudo make uninstall
```

## Usage
```bash
# Prints the helpmessage (if no todo-list exists)
todo

# Creates a todo list if necessary and adds the "thing to do"
todo add <"Thing to do"> [Priority (default: 1)]

# Removes an entry to the list
todo remove <line (starting index: 1)>

# Marks an entry as `done`
todo done <line (starting index: 1)>
```

### Symbol explanation:
| Symbol | Description       |
|--------|-------------------|
| <...>  | Required Argument |   
| [...]  | Optional Argument |
