
# Rust External - Full Chams for Players and All Gear Types

This repository provides a more complete tutorial on how to do full chams for players, including all gear types. Using `GetComponentsInChildren`, you can also apply chams to hands, weapons, and entities. Here is a brief tutorial on how to dump materials and use this feature. Note that the provided code can be further optimized, which will be up to you.

## Getting Material Addresses

1. **Start Rust without EAC:**
    - Open Steam.
    - Run `RustClient.exe`.
    - Host a server from your computer and connect to it. EAC will not be enabled in this setup, allowing you to use Cheat Engine safely.

2. **Using Cheat Engine:**
    - Once in the server, select `RustClient.exe` as the application for Cheat Engine.
    - Check "Hex" and type `DEADBEEFDEADBEEF` into the value field.
    - Set the value type to 8 bytes as shown in the image below:

      ![Searching DEADBEEFDEADBEEF](https://i.gyazo.com/9511221d994a25f27c58a5cea83f7b32.png)

    - You should find around 5000 addresses. Add every address you found to the address table by clicking the first one, scrolling to the bottom, holding shift, and clicking the last one to select them all. Then click the red arrow to add them to the table as shown in the image below:

      ![Adding All Addresses to Address Table](https://i.gyazo.com/d193b661833e521bb4adfded8e4f3fb4.png)

    - In the Cheat Engine navigation bar, click "Table" and then "Show cheat table lua script". Enter the provided Lua script, but first, ensure you edit the script to change the directory where it will save the `json.txt` file. This script will dump all addresses into `json.txt` as shown in the image below:

      ![Executing the Lua Script to Dump Addresses to json.txt](https://i.gyazo.com/561dcb1e6926906a2edebe7c3359c4f0.png)

3. **Building and Running the Material Scanner:**
    - Close Cheat Engine.
    - Build the material scanner source. Once built, place the executable file in the same directory as your `json.txt`.
    - Run the executable. You should get a file called `material_output.txt`, which will contain the names and IDs of available materials.
    - Note that some materials may cause your game to crash; this process involves trial and error.

## Credits

- **Cjweb:** GetComponentsInChildren / Helper functions / dumper.lua script
- **DarkEether:** GetAndAssignInstanciatedMaterial / Material scanner

## Preview Images

![Chams](https://i.gyazo.com/6c2321fcbe2d8826b016964957c0acc8.jpg)
![Chams through wall](https://i.gyazo.com/868eafa9c68b757fd9c496c7d465f90a.jpg)
