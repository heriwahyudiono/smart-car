import React, { useState } from "react";
import { ref, set } from "firebase/database";
import { database } from "./firebaseConfig";

const App = () => {
  const [activeDirection, setActiveDirection] = useState("stop");

  const sendCommand = (direction) => {
    set(ref(database, "/robot_control"), {
      direction,
    })
      .then(() => {
        console.log(`Sent command: ${direction}`);
        setActiveDirection(direction);
      })
      .catch((error) => console.error("Firebase write failed", error));
  };

  return (
    <div className="min-h-screen flex flex-col items-center justify-center bg-gray-100 px-4">
      <h2 className="text-3xl font-bold mb-6 text-gray-800">SmartCar</h2>

      <div className="space-y-3">
        <div className="flex justify-center">
          <button
            onClick={() => sendCommand("forward")}
            className={`px-6 py-2 rounded-md text-white font-semibold transition duration-150 ease-in-out cursor-pointer bg-blue-500 hover:bg-blue-600 ${
              activeDirection === "forward" ? "ring-4 ring-blue-300" : ""
            }`}
          >
            ↑ Maju
          </button>
        </div>

        <div className="flex justify-center space-x-4">
          <button
            onClick={() => sendCommand("left")}
            className={`px-6 py-2 rounded-md text-white font-semibold transition duration-150 ease-in-out cursor-pointer bg-green-500 hover:bg-green-600 ${
              activeDirection === "left" ? "ring-4 ring-green-300" : ""
            }`}
          >
            ← Kiri
          </button>

          <button
            onClick={() => sendCommand("stop")}
            className={`px-6 py-2 rounded-md text-white font-semibold transition duration-150 ease-in-out cursor-pointer bg-red-500 hover:bg-red-600 ${
              activeDirection === "stop" ? "ring-4 ring-red-300" : ""
            }`}
          >
            ■ Stop
          </button>

          <button
            onClick={() => sendCommand("right")}
            className={`px-6 py-2 rounded-md text-black font-semibold transition duration-150 ease-in-out cursor-pointer bg-yellow-500 hover:bg-yellow-600 ${
              activeDirection === "right" ? "ring-4 ring-yellow-300" : ""
            }`}
          >
            → Kanan
          </button>
        </div>
      </div>
    </div>
  );
};

export default App;
