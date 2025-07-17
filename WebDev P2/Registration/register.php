<?php

session_start();

require '../db.php';

if (empty($_POST['username']) || empty($_POST['email']) || empty($_POST['password'])) {
    $_SESSION['error_message'] = "Username, email, and password are required.";
    header('Location: index.php');
    exit();
}

if ($_POST['password'] !== $_POST['password_confirmation']) {
    $_SESSION['error_message'] = "The passwords don't match!";
    header('Location: index.php');
    exit();
}

//Input Sanitization
$username = $_POST['username'];
$email = filter_var($_POST['email'], FILTER_SANITIZE_EMAIL);
$password_hash = password_hash($_POST['password'], PASSWORD_BCRYPT);

if (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
    $_SESSION['error_message'] = "Invalid email format.";
    header('Location: index.php');
    exit();
}

//Check if user is already registered
$stmt = $conn->prepare("SELECT id FROM users WHERE username = ? OR email = ?");
$stmt->bind_param("ss", $username, $email);
$stmt->execute();
if ($stmt->get_result()->num_rows > 0) {
    $_SESSION['error_message'] = "Username or email is already registered.";
    header('Location: index.php');
    $stmt->close();
    $conn->close();
    exit();
}
$stmt->close();

//Actually register the user and redirect to login page
$stmt = $conn->prepare("INSERT INTO users (username, email, password) VALUES (?, ?, ?)");
$stmt->bind_param("sss", $username, $email, $password_hash);

if ($stmt->execute()) {
    header('Location: ../Login');
    exit();
} else {
    $_SESSION['error_message'] = "An unexpected error occurred. Please try again.";
    header('Location: index.php');
    exit();
}

$stmt->close();
$conn->close();
?>
