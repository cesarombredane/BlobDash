# BlobDash 🎮

A 2D platformer game developed as a high school ISN (Informatique et Sciences du Numérique) project using C++ and SFML.

## 📖 About

BlobDash is a side-scrolling platformer game where players control a blob character through various levels. This project was created as part of our ISN curriculum to demonstrate programming skills, game development concepts, and collaborative software development.

**Note:** This is a high school project that may receive future updates and improvements as we continue learning and developing our programming skills.

## 👥 Authors

- **Cesar** - Programming
- **Julien** - Programming
- **Zinedeen** - Il a fait le powerpoint wsh

*Detailed documentation for each author's contributions can be found in the `documentation/` folder.*

## 🛠️ Installation & Setup

### Prerequisites

- **Linux (Ubuntu/Debian):**
  ```bash
  sudo apt update
  sudo apt install build-essential libsfml-dev
  ```

### Building the Game

#### Linux Build
```bash
# Clone the repository
git clone https://github.com/cesarombredane/BlobDash.git
cd BlobDash

# Build the game
make

# Run the game
./BlobDash
```

## 🎮 Controls

- **Q** - Move left
- **D** - Move right  
- **S** - Crouch/Down (still in progress...)
- **Space** - Jump
- **M** - Dash (still in progress...)
- **Escape** - Exit game

## 📁 Project Structure

```
BlobDash/
├── src/
│   ├── include/          # Header files (.h)
│   ├── object/           # Source files (.cpp)
│   └── assets/           # Game assets (graphics, sounds, maps)
├── build/                # Compiled object files
├── documentation/        # Project documentation (ISN reports)
├── Makefile             # Linux build configuration
└── README.md            # This file
```

## 🔧 Technical Details

- **Language:** C++11
- **Graphics Library:** SFML (Simple and Fast Multimedia Library)
- **Platform:** Linux (primary)
- **Build System:** Make

## 📚 Documentation

Detailed project documentation, including design decisions, implementation details, and individual contributions, can be found in the `documentation/` folder:

- `Dossier_ISN_Cesar.pdf` - Cesar's contribution report
- `Dossier_ISN_Julien.pdf` - Julien's contribution report  
- `Dossier_ISN_Zinedeen.pdf` - Zinedeen's contribution report

## 📄 License

This project is developed for educational purposes as part of the ISN curriculum.
