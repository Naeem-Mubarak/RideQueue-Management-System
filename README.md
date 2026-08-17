# RideDispatch-CPP 🚗

A console-based **Ride Dispatch and Booking System** built in C++, demonstrating core Object-Oriented Programming concepts (inheritance, polymorphism, abstract classes), custom linked-list data structures, and file-based data persistence.

## 📋 Features

- **Two user roles**: Admin and Customer, each with a dedicated menu
- **Vehicle hierarchy**: Abstract `Vehicle` base class with `Bike`, `Car`, and `Truck` derived classes, each with its own fuel rate and late-penalty logic
- **Dynamic billing**: Calculates fare based on fuel rate, fuel/oil used, toll tax (for cars/trucks), and late-arrival penalties
- **Custom queue system**: Linked-list based `servingQueue` class manages a registered (serving) list and a waiting list, with automatic promotion from waiting to serving when a slot frees up
- **Driver management**: Register, search, verify (via license + password), and remove drivers using a custom linked-list `Drivers` class
- **Persistent storage**: All data (customers, drivers, completed rides) is saved to and loaded from text files (`Serving.txt`, `Waiting.txt`, `Driver.txt`, `Done.txt`) so state survives across runs

## 🗂️ Admin Menu

1. Cancel a registration by ID
2. Display all registered participants
3. Display waiting list
4. Search by ID
5. Add driver
6. Check drivers
7. Search driver by license
8. Serve first customer (assigns a driver, records the bill, promotes next waiting customer)
9. Exit

## 🗂️ Customer Menu

1. Register a participant (choose vehicle type: Bike / Car / Truck)
2. Exit

## 🛠️ Built With

- **Language**: C++
- **Concepts used**: Classes & objects, inheritance, virtual/pure virtual functions, abstract classes, custom linked lists, `std::tuple` and `std::pair`, file I/O (`fstream`), header files & include guards

## 📁 Project Structure

The project is modularized into separate header files by responsibility, with `main.cpp` tying everything together:

```
RideQueue-Management-System/
├── main.cpp        # Program entry point — menus, control flow, driver/vehicle assignment logic
├── Vehicle.h        # Vehicle, Bike, Car, Truck classes (billing logic per vehicle type)
├── Queue.h           # queue node + servingQueue classes (serving list & waiting list management)
├── Driver.h           # node + Drivers classes (driver registration & lookup)
├── README.md
├── LICENSE
└── .gitignore
```

Files generated automatically at runtime (ignored by git — see `.gitignore`):
```
Serving.txt    # Currently registered/serving customers
Waiting.txt    # Customers on the waiting list
Driver.txt     # Registered drivers
Done.txt       # Completed rides with billing details
```

## 🚀 Getting Started

### Prerequisites
A C++ compiler (g++, clang++, or MSVC). On Ubuntu/Debian:
```bash
sudo apt update
sudo apt install build-essential
```

### Compile & Run
```bash
g++ main.cpp -o RideDispatch
./RideDispatch
```

`main.cpp` pulls in `Vehicle.h`, `Queue.h`, and `Driver.h` automatically via `#include`, so no separate compilation steps are needed — one command builds the whole project.

On first run, the program looks for `Serving.txt`, `Waiting.txt`, and `Driver.txt` in the working directory. If they don't exist yet, they'll be created automatically as you add data.

## 📌 Notes

This project was built as a hands-on exercise in applying OOP design and data structures (linked lists, queues) to a practical simulation, without relying on any external libraries or frameworks — everything from the queue logic to file parsing is implemented from scratch. The codebase was later refactored from a single monolithic file into separate header files to improve readability and maintainability.

## 👤 Author

Naeem — Computer Science undergraduate, focused on AI/ML and software engineering fundamentals.

## 📄 License

This project is open source and available under the [MIT License](LICENSE).
