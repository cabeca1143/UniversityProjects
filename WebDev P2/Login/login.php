<?php

session_start();

include '../db.php';

if ($conn->connect_error) {
    $_SESSION['error_message'] = "Database connection failed.";
    header('Location: index.php');
    exit();
}

$login = $_POST['login'];
$password = $_POST['password'];

$stmt = $conn->prepare("SELECT id, username, email, password FROM users WHERE username = ? OR email = ?");
$stmt->bind_param("ss", $login, $login);
$stmt->execute();
$result = $stmt->get_result();

if ($result->num_rows === 1) {
    $user = $result->fetch_assoc();
    if (password_verify($password, $user['password'])) {
        session_regenerate_id(true);

        $_SESSION['userId'] = $user['id'];
        $_SESSION['username'] = $user['username'];

        if (isset($_POST['remember_me'])) {
            $token = bin2hex(random_bytes(32));
            $hashed_token = hash('sha256', $token);

            $updateStmt = $conn->prepare("UPDATE users SET remember_token = ? WHERE id = ?");
            $updateStmt->bind_param("si", $hashed_token, $user['id']);
            $updateStmt->execute();

            $cookie_value = $user['id'] . ':' . $token;
            setcookie('remember_me', $cookie_value, time() + (86400 * 30), "/"); // 86400 = 1 day
        }
        header('Location: ../Menu');
        exit();

    }
}

$_SESSION['error_message'] = "Invalid username/email or password.";
header('Location: index.php');
exit();

$stmt->close();
$conn->close();
?>
