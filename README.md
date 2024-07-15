![IMG_3949](https://github.com/user-attachments/assets/57ada3fe-cfe3-4fa6-bdfe-1e8170b1458a)

# keylogger

This project is a simple keylogger implemented in C++ that captures and logs keystrokes to a file named `log.txt`. The keylogger hides the console window to run silently in the background.

## How It Works

The keylogger sets a low-level keyboard hook to intercept keystrokes. It then logs these keystrokes to a file for later review.

### Features

- Logs all keystrokes including special keys like Enter.
- Runs silently by hiding the console window.
- Saves logs to `log.txt` in the same directory as the executable.

## Getting Started

### Prerequisites

- Windows operating system
- C++ compiler (e.g., MinGW, Visual Studio)

### Building the Keylogger

1. Clone the repository:

    ```sh
    git clone https://github.com/rootL0r/keylogger.git
    cd keylogger
    ```

2. Compile the code:

    ```sh
    g++ keylogger.cpp -o keylogger.exe -luser32
    ```

3. Run the executable:

    ```sh
    keylogger.exe
    ```
