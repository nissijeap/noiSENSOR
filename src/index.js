// Import the functions you need from the SDKs you need
import { initializeApp } from "firebase/app";
import { getAnalytics } from "firebase/analytics";
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

// Your web app's Firebase configuration
// For Firebase JS SDK v7.20.0 and later, measurementId is optional
const firebaseConfig = {
  apiKey: "AIzaSyAXIQ1r-JR7HxOruM_h888o1wD0iNLrOLI",
  authDomain: "noise-level-bc62c.firebaseapp.com",
  projectId: "noise-level-bc62c",
  storageBucket: "noise-level-bc62c.appspot.com",
  messagingSenderId: "518482570617",
  appId: "1:518482570617:web:d38ec9553a6670c57613a8",
  measurementId: "G-V60YLL36CY"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const analytics = getAnalytics(app);
console.log(app)