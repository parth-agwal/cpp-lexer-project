import React, { useEffect, useState } from 'react';
import './App.css';

function App() {
  const [code, setCode] = useState('');

  useEffect(() => {
    fetch('https://raw.githubusercontent.com/parth-agwal/cpp-lexer-project/refs/heads/main/phase1.cpp') 
      .then(res => res.text())
      .then(data => setCode(data))
      .catch(err => console.error('Failed to load code:', err));
  }, []);

  return (
    <div className="App">
      <h1>phase1.cpp Code Viewer</h1>
      <pre style={{
        backgroundColor: '#f4f4f4',
        padding: '1rem',
        textAlign: 'left',
        whiteSpace: 'pre-wrap',
        borderRadius: '8px',
        maxHeight: '80vh',
        overflowY: 'auto',
      }}>
        {code || 'Loading...'}
      </pre>
    </div>
  );
}

export default App;
