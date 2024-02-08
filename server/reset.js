import mysql from 'mysql2/promise';

const pool = mysql.createPool({
	host: 'localhost',
	port: 3306,
	user: 'root',
	password: 'password',
	database: 'db_liceon',
});

console.log('Clearing records of the liceon-esp32 database...');

try {
	// Truncate the RECORD table
	const query = 'TRUNCATE TABLE RECORD;';

	// Get a connection from the pool
	const connection = await pool.getConnection();

	// Execute the query
	await connection.execute(query);

	// Release the connection back to the pool
	connection.release();

	console.log('Table RECORD cleared successfully.');
} catch (error) {
	console.error(error);
}
