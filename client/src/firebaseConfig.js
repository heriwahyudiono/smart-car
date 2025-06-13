import { initializeApp } from "firebase/app";
import { getDatabase } from "firebase/database";

const firebaseConfig = {
  apiKey: "AIzaSyBzwFjTAbBI4cLrYXiw03A2VG48_YEbVwE",
  authDomain: "smartcar-f2205.firebaseapp.com",
  databaseURL: "https://smartcar-f2205-default-rtdb.asia-southeast1.firebasedatabase.app",
  projectId: "smartcar-f2205",
  storageBucket: "smartcar-f2205.appspot.com",
  messagingSenderId: "352309673652",
  appId: "1:352309673652:web:c5ef6240c4456d3a63a1e1",
  measurementId: "G-PVZFVYCPL7"
};

const app = initializeApp(firebaseConfig);
const database = getDatabase(app);

export { database };
