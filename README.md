# noiSENSOR: Noise Level Monitoring and Warning System

noiSENSOR is a web application designed to monitor noise levels and provide warnings when the noise exceeds a predefined threshold. This README file provides detailed instructions on how to run the noiSENSOR application.

## Demo
Refer to this link for live demonstartion of the web application: https://noise-level-bc62c.web.app/

## Prerequisites

Before running the Noisensor application, ensure that you have the following prerequisites installed on your system:

* Node.js (version 12 or higher)
* npm (Node Package Manager)
* Java (version 8 or higher)

## Installation
1. _Clone the repository to your local machine:_ **`git clone https://github.com/your-username/noisensor.git`**
2. _Navigate to the project directory:_ **`cd noisensor`**
3. _Install the dependencies using npm:_ **`npm install`**

## Configuration
1. _Rename the .env.example file to .env:_ **`mv .env.example .env`**
2. _Open the .env file in a text editor and configure the following variables:_
* **`PORT`**: The port on which the application will run (default is 3000).
* **`DB_URI`**: The URI of the MongoDB database.
* **`NOISE_THRESHOLD`**: The threshold value (in decibels) above which a warning will be triggered.
* **`API_KEY`**: An API key for external services (optional).

## Running the Application
1. _Start the application using the following command:_ **`npm start`**
2. Once the application has started, you can access it by opening a web browser and navigating to **`http://localhost:3000`** (replace **`3000`** with the **PORT** configured in the **`.env`** file). 

## Usage
 The Noisensor web application provides the following features:
* _Real-time noise level monitoring:_ The application displays the current noise level in decibels (dB) on the main page.
* _Threshold-based warning:_ When the noise level exceeds the predefined threshold, an LED light warning is displayed on the data read and lights up in the IoT hardware.
* _Historical data:_ The application stores and visualizes historical noise level data in the form of charts.

## Scan QR Code to freely Access the Web Application
![noisensor qr code](https://github.com/nissijeap/noiSENSOR/assets/115227551/88c4d346-f0b4-48ff-8659-7648032bec1c)

## Snippets of the Web App
### Home Page
The home page of the Noisensor web application provides a real-time display of the current noise level.

![image](https://github.com/nissijeap/noiSENSOR/assets/115227551/c7cb2415-48d7-437a-b546-7b7c8827edc1)

### Login Page
Users can log in to access the web application using email and password.

![image](https://github.com/nissijeap/noiSENSOR/assets/115227551/5edb3d80-77dd-4147-a364-d79c85724ea1)
#### Access Auth
Email: **`test@gmail.com`**
Password: **`test123`**

### Dashboard Page
After logging in, users are directed to the dashboard page where they can monitor the noise level and view historical data.

![image](https://github.com/nissijeap/noiSENSOR/assets/115227551/3262e69a-a535-4587-9f0b-1f9ac8752588)

### Data Records
The application stores and displays historical noise level data in a tabular format.

![image](https://github.com/nissijeap/noiSENSOR/assets/115227551/b343b6f1-8000-4961-b686-df080f687bb3)

### Historical Data Charts
The application provides charts to visualize historical noise level data over time.

![image](https://github.com/nissijeap/noiSENSOR/assets/115227551/05c6422c-7346-4193-b3bb-3b54fc59adc7)

## Contributing
Contributions are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request on the GitHub repository.

## License
This project is licensed under the MIT License.
