🎮 Gaming Website (Poki-Style)

A gaming platform where users can play multiple lightweight browser-based games, inspired by Poki.

The project uses a web-based frontend (HTML, CSS, JS) for UI/UX, C++ for game logic (compiled for web execution), and in the future will be extended with Flask backend and MySQL database for user management, scores, and leaderboards.

⸻

🚀 Features
	•	🎨 Frontend (HTML, CSS, JS) for interactive UI and game hosting.
	•	🕹️ C++ Game Core for fast and efficient game logic (compiled to run in the browser via WebAssembly).
	•	🔌 Backend (Flask) for APIs, authentication, and server-side operations (future).
	•	💾 Database (MySQL) for storing player data, scores, and leaderboards (future).
	•	📱 Responsive design for desktop and mobile gaming.

⸻

🛠️ Tech Stack

Frontend
	•	HTML5, CSS3, JavaScript (Vanilla JS)

Game Logic
	•	C++ (compiled to WebAssembly / Emscripten)

Backend (Planned)
	•	Flask (Python)

Database (Planned)
	•	MySQL

📂 Project Structure
gaming-website/
│── frontend/
│   ├── index.html
│   ├── styles.css
│   ├── script.js
│   └── assets/ (images, sounds, icons)
│
│── games/
│   ├── flappy-bird/ 
│   ├── snake/
│   └── pong/
│
│── cpp_core/
│   ├── game.cpp
│   └── build/ (compiled WebAssembly files)
│
│── backend/ (future)
│   ├── app.py
│   └── routes/
│
│── database/ (future)
│   └── schema.sql
│
└── README.md