# Give Kasane Teto Her Baguettes 🥖

A small arcade-style game made with **C++** and **raylib**.
Your goal is simple: **catch as many falling baguettes as possible and give them to Kasane Teto!**

---

## 🎮 How to Play

* **A / D** – Move left and right
* **F11** – Toggle fullscreen / windowed mode
* Catch the falling **baguettes** to increase your score
* Missing a baguette resets your score

The game gets faster the more baguettes you catch!

---

## 📥 Downloading the Game

1. Click the green **Code** button on this page
2. Select **Download ZIP**
3. Extract the ZIP file anywhere on your computer

---

## ▶️ How to Run the Game (Windows)

1. Open the extracted folder
2. Open the `build` folder
3. Double-click:

   ```
   Give_Kasane_Teto_her_baguettes.exe
   ```

⚠️ **Important:**

* The `.exe` must stay in the **same folder** as the `resources` folder
* Do **not** move or delete the `resources` folder or the game will not load textures or sounds

---

## 🛠 Building From Source (Optional)

### Requirements

* **CMake 4.1+**
* **C++23 compatible compiler (MSVC recommended)**
* **Git**

### Steps

```bash
git clone https://github.com/XelpiSource/Teto-Catch.git
cd Teto-Catch
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

The executable will be generated in the `build` folder.

---

## 📁 Project Structure

```
Give_Kasane_Teto_her_baguettes/
├── build/
│   ├── resources/
│   └── Give_Kasane_Teto_her_baguettes.exe
├── resources/
│   ├── background.png
│   ├── background-music.mp3
│   ├── baguette.png
│   ├── miniTeto.png
│   ├── teto-oh-no.mp3
│   └── tetoo.mp3
├── src/
│   └── main.cpp
├── thirdparty/
│   └── raylib/
└── CMakeLists.txt
```

---

## ❤️ Credits

* **Game & Code:** XelpiSource
* **Engine:** raylib
* **Character:** Kasane Teto

---

Enjoy the game, and don’t forget to give Teto her baguettes 🥖✨
