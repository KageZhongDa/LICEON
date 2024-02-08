import express from 'express';
import cors from 'cors';
import http from 'http';
import { IP_ESP32_LICEON } from '../env.js';

// Use 'mysql2/promise' for async/await support
import mysql from 'mysql2/promise';

// ==================================================

/**
 *
 * A connection pool is a cache of database connections
 * that are reused, rather than being opened and closed
 * for each new request. The purpose of a connection
 * pool is to improve the efficiency and performance of
 *  database operations by reducing the overhead
 * associated with opening and closing database connections.
 *
 */

// MySQL pool configuration
const pool = mysql.createPool({
	host: 'localhost',
	port: 3306,
	user: 'root',
	password: 'password',
	database: 'db_liceon',
});

// Function to listen to the liceon-esp32 API server
async function listenToLiceon() {
	console.log('fetching data from liceon-esp32...');
	try {
		console.log('Ip Address of Esp32: ', IP_ESP32_LICEON);
		const response = await fetch(`http://${IP_ESP32_LICEON}/api/data`);
		const data = await response.json();
		console.log(data);

		// Insert the data into the database
		const { SERVER, ACDVAL, TRBVAL, TMPCELVAL, TMPFARVAL } = data;
		if (SERVER === 'LICEON') {
			const query = `
            INSERT INTO RECORD (id, acdval, trbval, tmpcelval, tmpfarval)
            VALUES (DEFAULT, ?, ?, ?, ?);
         `;

			// Get a connection from the pool
			const connection = await pool.getConnection();
			const [result] = await connection.execute(query, [ACDVAL, TRBVAL, TMPCELVAL, TMPFARVAL]);

			// Release the connection back to the pool
			connection.release();
			console.log(`Data inserted ${new Date().toLocaleString()} successfully.`);
		}
	} catch (error) {
		console.error(error);
	} finally {
		// Wait for 1 second before making the next request
		setTimeout(listenToLiceon, 500);
	}
}

// Initial call to start the process
listenToLiceon();

// express app
const app = express();

/**
 * Add this line to enable JSON parsing
 */
app.use(express.json());

/**
 * This is a proxy option for the dev server.
 * It will proxy /api from the client to the routes.
 * Handles Cross-Origin Resource Sharing (CORS) errors.
 */
app.use(cors());

// SSE Setup
const clients = [];
app.get('/api/realtime-data', (req, res) => {
	res.setHeader('Content-Type', 'text/event-stream');
	res.setHeader('Cache-Control', 'no-cache');
	res.setHeader('Connection', 'keep-alive');
	res.flushHeaders();

	clients.push(res);

	req.on('close', () => {
		clients.splice(clients.indexOf(res), 1);
	});
});

async function fetchLatestRecords() {
	const connection = await pool.getConnection();
	try {
		const query = 'SELECT * FROM RECORD ORDER BY id DESC LIMIT 8';
		const [rows] = await connection.execute(query);
		const records = rows.reverse(); // Reverse the order to get the latest first
		for (const client of clients) {
			client.write(`data: ${JSON.stringify(records)}\n\n`);
		}
	} catch (error) {
		console.error(error);
	} finally {
		connection.release();
	}
}

// Regularly fetch and push latest records
setInterval(fetchLatestRecords, 1000);

// app.get('/api/get_profile', User.get_profile);

const PORT = process.env.PORT || 5000;
app.listen(PORT, () => {
	console.log(`Server is running on port ${PORT}`);
});
