import React, { useState, useEffect } from 'react';
import './DeadlockDashboard.css';
const DeadlockDashboard = () => {
  const [deadlocks, setDeadlocks] = useState([]);

  useEffect(() => {
    // Fetch data or simulate a deadlock detection algorithm
    const fetchDeadlockData = () => {
      // Example of deadlock data; replace with actual data fetching logic
      const data = [
        { process: 'P1', status: 'Waiting', resources: ['R1'] },
        { process: 'P2', status: 'Blocked', resources: ['R2'] },
        { process: 'P3', status: 'Waiting', resources: ['R1', 'R2'] },
      ];
      setDeadlocks(data);
    };

    fetchDeadlockData();
  }, []);

  return (
    <div>
      <h1>Deadlock Detection Dashboard</h1>
      <table>
        <thead>
          <tr>
            <th>Process</th>
            <th>Status</th>
            <th>Resources</th>
          </tr>
        </thead>
        <tbody>
          {deadlocks.map((deadlock, index) => (
            <tr key={index}>
              <td>{deadlock.process}</td>
              <td>{deadlock.status}</td>
              <td>{deadlock.resources.join(', ')}</td>
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
};

export default DeadlockDashboard;
