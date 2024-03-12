import mysql from 'mysql2/promise';
import fs from 'fs/promises';

// Database connection configuration
const connection = await mysql.createPool({
  host: 'localhost',
  user: 'root',
  password: '',
  database: 'db_liceon'
});

// Table to export
const tableName = 'RECORD';
// Output file name
const outputFile = 'output.csv';

try {
  // Querying database
  const [rows] = await connection.query(`SELECT * FROM ${tableName}`);

  // Convert rows to CSV format
  let csvData = '';
  const columns = Object.keys(rows[0]);
  csvData += columns.join(',') + '\n';
  rows.forEach(row => {
    const values = columns.map(col => row[col]);
    csvData += values.join(',') + '\n';
  });

  // Write data to CSV file
  await fs.writeFile(outputFile, csvData);

  console.log(`Data exported to ${outputFile}`);

} catch (err) {
  console.error('Error:', err);
} finally {
  // Close the database connection
  await connection.end();
  console.log('Database connection closed');
}
