<?php
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $code = $_POST['code'] ?? '';
    file_put_contents("input.txt", $code);

    // Compile lexer
    exec("g++ phase1.cpp -o lexer");

    // Run lexer on input.txt
    exec("./lexer", $output);

    echo implode("\n", $output);
} else {
    echo "Use POST with 'code' parameter.";
}
?>
